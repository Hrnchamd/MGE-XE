using System;
using System.Collections.Generic;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D9;
using MGEgui.INI;

namespace MGEgui.DirectX {

    public static class Shaders {
        private static Texture thisFrame;
        private static Texture depthFrame;
        private static Texture lastShader;
        private static Texture lastPass;

        private static Surface thisFrameSurface;
        private static Surface lastShaderSurface;
        private static Surface lastPassSurface;

        private static int frameWidth, frameHeight;
        private static VertexBuffer vBuffer;
        private static Int64 basetime;

        private struct GenericVertex {
            float x, y, z, w;
            float u1, v1, u2, v2, u3, v3, u4, v4, u5, v5, u6, v6;

            public GenericVertex(float _x, float _y, float _z, float _w, float _u, float _v) {
                x=_x; y=_y; z=_z; w=_w;
                u1=_u; v1=_v;
                u2=_u; v2=_v;
                u3=_u; v3=_v;
                u4=_u; v4=_v;
                u5=_u; v5=_v;
                u6=_u; v6=_v;
            }

            public const VertexFormat format=VertexFormat.PositionRhw|VertexFormat.Texture6;
            public const int Stride=64;
        }

        private struct shader {
            public EffectHandle ehTime, ehHDR;

            public Effect effect;
        }

        private static readonly List<shader> effects=new List<shader>();

        private static void Reset() {
            foreach(shader e in effects) e.effect.Dispose();
            effects.Clear();
            if(thisFrameSurface!=null) {
                thisFrameSurface.Dispose();
                thisFrameSurface=null;
            }
            if(lastShaderSurface!=null) {
                lastShaderSurface.Dispose();
                lastShaderSurface=null;
            }
            if(lastPassSurface!=null) {
                lastPassSurface.Dispose();
                lastPassSurface=null;
            }
            if(thisFrame!=null) {
                thisFrame.Dispose();
                thisFrame=null;
            }
            if(lastShader!=null) {
                lastShader.Dispose();
                lastShader=null;
            }
            if(lastPass!=null) {
                lastPass.Dispose();
                lastPass=null;
			}
			if (depthFrame != null)
			{
				depthFrame.Dispose();
				depthFrame = null;
			}
            if(vBuffer!=null) {
                vBuffer.Dispose();
                vBuffer=null;
            }
            GC.Collect();
        }

        private static shader LoadShaderTextures(Effect effect) {
            try { effect.SetTexture("lastpass", lastPass); } catch { } //throws an exception if this parameter doesn't exist :(
            try { effect.SetTexture("lastshader", lastShader); } catch { }
            try { effect.SetTexture("depthframe", depthFrame); } catch { }
            try { effect.SetValue("rcpres", new Vector4(1f/frameWidth, 1f/frameHeight, 0, 1)); } catch { }
            try { effect.SetValue("fov", 85f); } catch { }
            try { effect.SetValue("fogstart", 819.2f); } catch { }
            try { effect.SetValue("fogrange", 65536.0f); } catch { }
            try { effect.SetValue("waterlevel", 0f); } catch { }
			try { effect.SetValue("HDR", new Vector4(0.25f, 0.25f, 0.25f, 02.5f)); } catch { }
			try { effect.SetValue("eyepos", new Vector3(0f, 0f, 128f)); } catch { }
			try { effect.SetValue("eyevec", new Vector3(1f, 0f, 0f)); } catch { }

            int count=1;
            while(true) {
                string texpath;
                try { texpath=effect.GetString("texname"+count.ToString()); } catch { break; }
                if(texpath!=null) {
                    try {
                        Texture tex=Texture.FromFile(DXMain.device, Statics.runDir + "\\data files\\textures\\"+texpath);
                        effect.SetTexture("tex"+count.ToString(), tex);
                    } catch { }
                } else break;
                count++;
            }

            shader s = new shader();
            try {
                s.ehTime = effect.GetParameter(null, "time");
            } catch {
                s.ehTime = null;
            }
            try {
                s.ehHDR = effect.GetParameter(null, "HDR");
            } catch {
                s.ehHDR = null;
            }
            s.effect=effect;

            return s;
        }

        private static string Setup(string framepath, string depthpath) {
        	if(framepath == null) framepath = Statics.runDir + @"\mge3\preview_frame.dds";
        	if(depthpath == null) depthpath = Statics.runDir + @"\mge3\preview_depth.dds";
        	
            try {
                thisFrame = Texture.FromFile(DXMain.device, framepath, D3DX.FromFile, D3DX.FromFile, 1, Usage.None, Format.Unknown, Pool.Default, Filter.None, Filter.None, 0);
                depthFrame = Texture.FromFile(DXMain.device, depthpath, D3DX.FromFile, D3DX.FromFile, 1, Usage.None, Format.Unknown, Pool.Default, Filter.None, Filter.None, 0);
                if(thisFrame==null||depthFrame==null) throw new ApplicationException();
        		
        		frameWidth = thisFrame.GetLevelDescription(0).Width;
        		frameHeight = thisFrame.GetLevelDescription(0).Height;
                lastShader = new Texture(DXMain.device, frameWidth, frameHeight, 1, Usage.RenderTarget, Format.A8R8G8B8, Pool.Default);
                lastPass = new Texture(DXMain.device, frameWidth, frameHeight, 1, Usage.RenderTarget, Format.A8R8G8B8, Pool.Default);
                if(lastShader==null||lastPass==null) throw new ApplicationException();

                thisFrameSurface = thisFrame.GetSurfaceLevel(0);
                lastShaderSurface = lastShader.GetSurfaceLevel(0);
                lastPassSurface = lastPass.GetSurfaceLevel(0);
            } catch {
                return "Unable to create the required textures";
            }
        	
            try {
                vBuffer = new VertexBuffer(DXMain.device, GenericVertex.Stride*4, Usage.WriteOnly, GenericVertex.format, Pool.Default);
                DataStream verts = vBuffer.Lock(0, 0, LockFlags.None);
                verts.Write(new GenericVertex(-0.5f, -0.5f, 0, 1, 0, 0));
                verts.Write(new GenericVertex(-0.5f, frameHeight-0.5f, 0, 1, 0, 1));
                verts.Write(new GenericVertex(frameWidth-0.5f, -0.5f, 0, 1, 1, 0));
                verts.Write(new GenericVertex(frameWidth-0.5f, frameHeight-0.5f, 0, 1, 1, 1));
                vBuffer.Unlock();
            } catch {
                return "Unable to create vertex buffer";
            }

            try {
                DXMain.device.SetStreamSource(0, vBuffer, 0, 64);
                DXMain.device.VertexFormat=GenericVertex.format;
                DXMain.device.Indices=null;
        		DXMain.device.SetRenderState(RenderState.CullMode, Cull.None);
            } catch {
                return "Unable to set device state";
            }

            basetime = DateTime.Now.Ticks;
            return null;
        }

        internal static string CompileShader(bool Render, string framepath, string depthpath, string shaderpath) {
            Reset();

            Effect effect;
            string errors = null;
            try {
                effect=Effect.FromFile(DXMain.device, shaderpath, null, null, null, ShaderFlags.None, null, out errors);
                if(effect==null) throw new ApplicationException();
            } catch {
                if(errors!=null) return errors.Replace("\n",Environment.NewLine);
                else return "Effect load failed";
            }

            try {
                effect.Technique="T0";
                effect.ValidateTechnique("T0");
            } catch {
                return "Error setting effect technique, or shader validation error";
            }
            if(!Render) {
                effect.Dispose();
                return null;
            }

            string s = Setup(framepath, depthpath);
            if(s != null) return s;

            effects.Add(LoadShaderTextures(effect));
            return null;
        }

        internal static string PreviewShaderChain(string framepath, string depthpath) {
            Reset();
            string sp = Setup(framepath, depthpath);
            if(sp != null) return sp;

            INIFile iniFile = new INIFile(Statics.iniFileName, ShaderActive.iniShaderWhat, true);
            List<string> shaderList = new List<string>(iniFile.getSectList(ShaderActive.iniShaderChain));
            foreach (string s in shaderList) {
                string path = Statics.runDir + "\\" + Statics.pathShaders + "\\" + s + ".fx";
                Effect effect;

                try {
                    effect = Effect.FromFile(DXMain.device, path, ShaderFlags.None);
                    if(effect == null) throw new ApplicationException();
                } catch {
                    return "Shader '"+path+"' failed to load.";
                }

                try {
                    effect.Technique = "T0";
                    effect.ValidateTechnique("T0");
                } catch {
                    return "Shader '"+path+"' failed validation.";
                }

                effects.Add(LoadShaderTextures(effect));
            }

            return null;
        }

        internal static void EndShader() {
            Reset();
        }

        internal static void RenderFrame(bool UseShader, decimal HDR_val) {
            DXMain.device.Clear(ClearFlags.Target, 255, 0, 0);
            if (UseShader) {
                for (int i = 0; i < 6; i++) DXMain.device.SetTexture(i, lastShader);
                double t = (DateTime.Now.Ticks - basetime) / 10000000.0;
                
                DXMain.device.BeginScene();
                DXMain.device.StretchRectangle(thisFrameSurface, lastPassSurface, TextureFilter.None);
                
                for(int i=0; i<effects.Count; i++) {
                    DXMain.device.StretchRectangle(lastPassSurface, lastShaderSurface, TextureFilter.None);
                    
                    if(effects[i].ehTime != null) effects[i].effect.SetValue(effects[i].ehTime, t);
                    if(effects[i].ehHDR != null) effects[i].effect.SetValue(effects[i].ehHDR, new Vector4((float)HDR_val, (float)HDR_val, (float)HDR_val, (float)HDR_val));

                    int passes = effects[i].effect.Begin(FX.None);
                    for(int pass = 0;pass < passes;pass++) {
                        effects[i].effect.BeginPass(pass);
                        DXMain.device.DrawPrimitives(PrimitiveType.TriangleStrip, 0, 2);
                        DXMain.device.StretchRectangle(DXMain.BackBuffer, lastPassSurface, TextureFilter.None);
                        effects[i].effect.EndPass();
                    }
                    effects[i].effect.End();
                }
                
                DXMain.device.EndScene();
                DXMain.device.StretchRectangle(DXMain.BackBuffer, lastPassSurface, TextureFilter.None);
            } else {
                for (int i = 0; i < 6; i++) DXMain.device.SetTexture(i, thisFrame);
                DXMain.device.BeginScene();
                DXMain.device.DrawPrimitives(PrimitiveType.TriangleStrip, 0, 2);
                DXMain.device.EndScene();
            }
            DXMain.device.Present();
        }
    }
}
