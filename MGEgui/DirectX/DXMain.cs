using System;
using Point=System.Drawing.Point;
using Control=System.Windows.Forms.Control;
using SlimDX;
using SlimDX.Direct3D9;

namespace MGEgui.DirectX {
    static class DXMain {
        public struct MGECaps {
            public int MaxWindowedAA;
            public int MaxFullscreenAA;
            public int MaxAF;
            public bool SupportsSM1;
            public bool SupportsSM2;
            public bool SupportsSM3;
            public int MaxTexSize;
            public int MaxPrimitives;
            public int MaxIndicies;
        }
        private static Format _format;
        private static Capabilities caps;
        private static int adapter;

        public static MGECaps mCaps = new MGECaps();
        public static readonly System.Drawing.Rectangle Rect = new System.Drawing.Rectangle(0, 0, 1024, 1024);
        public static int Adapter { get { return adapter; } }
        public static Format format { get { return _format; } private set { _format=value; } }

  		private static Direct3D d3d;
        private static Device _device;
        public static Device device { get { return _device; } private set { _device=value; } }
        private static Surface _backbuffer;
        public static Surface BackBuffer { get { return _backbuffer; } private set { _backbuffer=value; } }

        private static readonly PresentParameters devParams;

        static DXMain() {
        	d3d = new Direct3D();
        	
            try {
                format = d3d.Adapters[adapter].CurrentDisplayMode.Format;
            } catch {
                format = Format.X8R8G8B8;
            }

            devParams=new PresentParameters();
            devParams.BackBufferCount=1;
            devParams.BackBufferFormat=format;
            devParams.BackBufferHeight=1024;
            devParams.BackBufferWidth=1024;
            devParams.EnableAutoDepthStencil=false;
            devParams.Multisample=MultisampleType.None;
            devParams.SwapEffect=SwapEffect.Discard;
            devParams.Windowed=true;
            devParams.PresentationInterval=PresentInterval.One;
        }

        public static void GetDeviceCaps() {
            //Device.IsUsingEventHandlers=false;

            adapter=(int)Microsoft.Win32.Registry.GetValue(@"HKEY_LOCAL_MACHINE\SOFTWARE\Bethesda Softworks\Morrowind", "Adapter", 0);
            if(d3d.AdapterCount <= adapter) throw new ApplicationException("Morrowind is set up to use an adapter which could not be found on your system");

            for(int i=2;i<=16;i++) {
                if(d3d.CheckDeviceMultisampleType(adapter, DeviceType.Hardware, Format.X8R8G8B8, false, (MultisampleType)i))
                    mCaps.MaxFullscreenAA=i;
                if(d3d.CheckDeviceMultisampleType(adapter, DeviceType.Hardware, Format.X8R8G8B8, true, (MultisampleType)i))
                    mCaps.MaxWindowedAA=i;
            }

            caps = d3d.GetDeviceCaps(adapter, DeviceType.Hardware);

            mCaps.MaxAF=caps.MaxAnisotropy;
            mCaps.SupportsSM1=(caps.VertexShaderVersion>=new Version(1,1))&&(caps.PixelShaderVersion>=new Version(1,4));
            mCaps.SupportsSM2=(caps.VertexShaderVersion.Major>=2)&&(caps.PixelShaderVersion.Major>=2);
            mCaps.SupportsSM3=(caps.VertexShaderVersion.Major>=3)&&(caps.PixelShaderVersion.Major>=3);
            mCaps.MaxTexSize=Math.Min(caps.MaxTextureHeight, caps.MaxTextureWidth);
            mCaps.MaxPrimitives=caps.MaxPrimitiveCount;
            mCaps.MaxIndicies=caps.MaxVertexIndex;
        }

        public static int[] GetRefreshRates(int width, int height) {
            System.Collections.Generic.List<int> rates=new System.Collections.Generic.List<int>();
            foreach(DisplayMode ds in d3d.Adapters[adapter].GetDisplayModes(Format.X8R8G8B8)) {
                if(ds.Width==width && ds.Height==height) rates.Add(ds.RefreshRate);
            }
            return rates.ToArray();
        }

        public static Point[] GetResolutions() {
            System.Collections.Generic.List<Point> resolutions=new System.Collections.Generic.List<Point>();
            foreach(DisplayMode ds in d3d.Adapters[adapter].GetDisplayModes(Format.X8R8G8B8)) {
                if(!resolutions.Contains(new Point(ds.Width, ds.Height)))
                    resolutions.Add(new Point(ds.Width, ds.Height));
            }
            return resolutions.ToArray();
        }

        public static void CreateDevice(Control window) {
            CloseDevice();

            device = new Device(d3d, adapter, DeviceType.Hardware, window.Handle, CreateFlags.FpuPreserve|CreateFlags.Multithreaded|CreateFlags.HardwareVertexProcessing, devParams);

            //BackBuffer=device.GetBackBuffer(0, 0, BackBufferType.Mono);
            BackBuffer=device.GetRenderTarget(0);

            device.SetRenderState(RenderState.Lighting, false);
            device.SetRenderState(RenderState.ZEnable, false);
            device.SetRenderState(RenderState.StencilEnable, false);
            device.SetRenderState(RenderState.Ambient, int.MinValue);
        }

        public static void CloseDevice() {
            BackBuffer=null;
            if(device!=null) {
                device.Dispose();
                device=null;
            }
        }

        public static bool CheckAALevel(int level, bool windowed) {
            return d3d.CheckDeviceMultisampleType(adapter, DeviceType.Hardware, Format.X8R8G8B8, windowed, (MultisampleType)level);
        }
    }
}