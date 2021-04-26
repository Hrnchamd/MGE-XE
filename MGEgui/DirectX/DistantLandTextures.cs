using System;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Direct3D9;
using TexCache = System.Collections.Generic.Dictionary<string, SlimDX.Direct3D9.Texture>;
using MGEgui.DistantLand;

namespace MGEgui.DirectX {
    public class LTEX {
        private static readonly TexCache texCache = new TexCache();

        public static void ReleaseCache() {
            foreach (Texture t in texCache.Values) {
                try {
                    if (!t.Disposed) {
                        t.Dispose();
                    }
                } catch {
                }
            }
            texCache.Clear();
        }

        private string filePath;
        public string FilePath {
            set { filePath = value.ToLowerInvariant(); }
            get { return filePath; }
        }
        public int index;
        public Texture tex;

        public void LoadTexture() {
            if (texCache.ContainsKey(filePath)) {
                tex = texCache[filePath];
            } else {
                try {
                    byte[] data = MGEgui.DistantLand.BSA.GetTexture(filePath);

                    // Work around a loading issue with TGA headers
                    // When ColorMapType == no_palette && ImageType == truecolor, set word ColorMapLength to 0
                    if (data.Length > 6 && data[1] == 0 && (data[2] == 2 || data[2] == 10)) {
                        data[5] = data[6] = 0;
                    }

                    // Scale down widest texture dimension to 256 to conserve memory
                    ImageInformation imginf = ImageInformation.FromMemory(data);
                    Filter dxf = Filter.Box | Filter.Srgb;
                    int maximal = Math.Max(imginf.Width, imginf.Height);
                    int skiplevels = 0, w = 0, h = 0;
                    while (maximal > 256) {
                        maximal /= 2;
                        skiplevels += 1;
                    }

                    if (skiplevels < imginf.MipLevels) {
                        // Skip loading mips larger than 256 pixels
                        // Filter bits 27-31 specify the number of mip levels to be skipped
                        dxf = (Filter)((skiplevels << 26) | (int)dxf);
                    } else {
                        // Rescale base level to fit inside 256 pixels
                        w = imginf.Width >> skiplevels;
                        h = imginf.Height >> skiplevels;
                    }

                    tex = Texture.FromMemory(DXMain.device, data, w, h, 0, Usage.None, Format.Unknown, Pool.Managed, Filter.Triangle | Filter.Dither, dxf, 0);
                    texCache[filePath] = tex;
                } catch {
                    tex = null;
                    throw;
                }
            }
        }
    }

    class StaticTexCreator {
        private readonly System.Collections.Generic.List<string> texCache;
        private readonly int div;

        public StaticTexCreator(int skip) {
            div = (1 << skip);
            texCache = new System.Collections.Generic.List<string>();
        }

        public void Dispose() {
            texCache.Clear();
        }

        public bool LoadTexture(string path) {
            if (texCache.Contains(path)) {
                return true;
            }
            texCache.Add(path);

            byte[] data = MGEgui.DistantLand.BSA.GetTexture(path);
            if (data == null) {
                return false;
            }

            // Work around a loading issue with TGA headers
            // When ColorMapType == no_palette && ImageType == truecolor, set word ColorMapLength to 0
            if (data.Length > 6 && data[1] == 0 && (data[2] == 2 || data[2] == 10)) {
                data[5] = data[6] = 0;
            }

            path = System.IO.Path.ChangeExtension(path, ".dds");
            ImageInformation imginfo;
            Format format;

            try {
                imginfo = ImageInformation.FromMemory(data);
            } catch (SlimDXException) {
                return false;
            }

            int newWidth = imginfo.Width / div, newHeight = imginfo.Height / div;
            if (newWidth < 4 || newHeight < 4) {
                return true;
            }

            if (imginfo.Format == Format.Dxt1) {
                format = isDXT1a(imginfo, data) ? Format.Dxt3 : Format.Dxt1;
            } else if (imginfo.Format == Format.Dxt3 || imginfo.Format == Format.Dxt5) {
                format = imginfo.Format;
            } else if (imginfo.Format == Format.X8R8G8B8) {
                format = Format.Dxt1;
            } else {
                format = Format.Dxt3;
            }

            if (div > 1 || format != imginfo.Format) {
                Texture t = null;
                System.IO.Directory.CreateDirectory(System.IO.Path.GetDirectoryName(System.IO.Path.Combine(@"data files\distantland\statics\textures\", path)));

                try {
                    if (format == imginfo.Format) {
                        // Load reduced size texture
                        t = Texture.FromMemory(DXMain.device, data, newWidth, newHeight, 0, Usage.None, format, Pool.Scratch, Filter.Triangle | Filter.Dither, Filter.Triangle, 0);
                    } else {
                        // Recalculate mipmaps
                        Texture srctex = Texture.FromMemory(DXMain.device, data, newWidth, newHeight, 0, Usage.None, Format.A8B8G8R8, Pool.Scratch, Filter.Triangle | Filter.Dither, Filter.Triangle, 0);
                        t = new Texture(DXMain.device, newWidth, newHeight, 0, Usage.None, format, Pool.Scratch);

                        srctex.FilterTexture(0, Filter.Triangle | Filter.Srgb);
                        for (int i = 0; i != t.LevelCount; ++i) {
                            Surface dest = t.GetSurfaceLevel(i);
                            Surface src = srctex.GetSurfaceLevel(i);
                            Surface.FromSurface(dest, src, Filter.Point, 0);
                            src.Dispose();
                            dest.Dispose();
                        }

                        srctex.Dispose();
                    }
                    Texture.ToFile(t, System.IO.Path.Combine(@"data files\distantland\statics\textures\", path), ImageFileFormat.Dds);
                    t.Dispose();
                } catch (SlimDXException) {
                    if (t != null) {
                        t.Dispose();
                    }
                    return false;
                }
            }

            return true;
        }

        private bool isDXT1a(ImageInformation imginfo, byte[] data) {
            int blocks = (imginfo.Width * imginfo.Height) >> 4;

            for (int i = 0; i != blocks; ++i) {
                int k = 128 + 8 * i;
                uint c0 = (uint)(data[k + 0] | (data[k + 1] << 8));
                uint c1 = (uint)(data[k + 2] | (data[k + 3] << 8));
                uint b = (uint)(data[k + 4] | (data[k + 5] << 8) | (data[k + 6] << 16) | (data[k + 7] << 24));

                if (c0 <= c1 && ((b & 0x55555555) & (b >> 1)) != 0) {
                    return true;
                }
            }

            return false;
        }
    }

    class TextureBank {
        public LTEX t1, t2, t3, t4;
        public VertexBuffer wBuffer;

        public struct WeightVertex {
            public byte w1, w2, w3, w4;

            public const VertexFormat Format = VertexFormat.Diffuse;
            public const int Stride = 4;
        };

        public TextureBank() {
            wBuffer = new VertexBuffer(DXMain.device, WeightVertex.Stride * 4225, Usage.WriteOnly, WeightVertex.Format, Pool.Managed);
        }

        public void SetSingleTexture(LTEX tex1) {
            // There this will create a default bank which can be used for default land which has one texture
            t1 = tex1;

            DataStream WeightData = wBuffer.Lock(0, 0, LockFlags.None);
            WeightVertex defaultw;
            defaultw.w1 = 255;
            defaultw.w2 = 0;
            defaultw.w3 = 0;
            defaultw.w4 = 0;

            for (int y = 0; y <= 64; y++) {
                for (int x = 0; x <= 64; x++) {
                    WeightData.Write(defaultw);
                }
            }

            wBuffer.Unlock();
        }

        private WeightVertex SampleWeightData(ref WeightVertex[] array, int x, int y) {

            // Ensure that x and y do not escape the bounds of the array.
            if (x < 0) {
                x = 0;
            }
            if (y < 0) {
                y = 0;
            }
            if (x > 64) {
                x = 64;
            }
            if (y > 64) {
                y = 64;
            }

            // Return the value at the constrained location
            return array[y * 65 + x];
        }
        public void CalcWeights(LAND cell) {

            WeightVertex[] WeightData = new WeightVertex[65 * 65];

            for (int y = 0; y <= 64; y++) {
                for (int x = 0; x <= 64; x++) {
                    // Figure out which index to use
                    int i = y * 65 + x;

                    // Figure out which texture is used here
                    int cell_x = cell.xpos;
                    int cell_y = cell.ypos;
                    int tex_x = (int)Math.Floor(((float)x - 2.0f) / 4.0f);
                    int tex_y = (int)Math.Floor(((float)y - 2.0f) / 4.0f);

                    DistantLandForm.ModCell(ref cell_x, ref tex_x);
                    DistantLandForm.ModCell(ref cell_y, ref tex_y);

                    LTEX tmp = DistantLandForm.GetTex(cell_x, cell_y, tex_x, tex_y);
                    string tex_index = tmp.FilePath;

                    // Write values
                    if (t1 != null && t1.FilePath == tex_index) {
                        WeightData[i].w1 = 255;
                        continue;
                    } else {
                        WeightData[i].w1 = 0;
                    }

                    if (t2 != null && t2.FilePath == tex_index) {
                        WeightData[i].w2 = 255;
                        continue;
                    } else {
                        WeightData[i].w2 = 0;
                    }

                    if (t3 != null && t3.FilePath == tex_index) {
                        WeightData[i].w3 = 255;
                        continue;
                    } else {
                        WeightData[i].w3 = 0;
                    }

                    if (t4 != null && t4.FilePath == tex_index) {
                        WeightData[i].w4 = 255;
                        continue;
                    } else {
                        WeightData[i].w4 = 0;
                    }
                }
            }

            // Blur the weights as we transfer them so the transitions aren't quite so blocky and horrible.

            // // Normal Gaussian
            // float bf1 = 0.00081723f;
            // float bf2 = 0.02804153f;
            // float bf3 = 0.23392642f;
            // float bf4 = 0.47442968f;

            // Reduced center influence
            const float bf1 = 0.1f;
            const float bf2 = 0.15f;
            const float bf3 = 0.2f;
            const float bf4 = 0.1f;

            // Horizontal Pass
            WeightVertex[] FirstPassWD = new WeightVertex[65 * 65];
            for (int y = 0; y <= 64; y++) {
                for (int x = 0; x <= 64; x++) {
                    // Figure out which index to use
                    int i = y * 65 + x;

                    if (x == 0 || x == 64 || y == 0 || y == 64) {
                        // We're at the edge, so just copy the value (don't want to interfere with the way the edges of cells look
                        FirstPassWD[i] = WeightData[i];
                        continue;
                    }

                    // We're not at the edge, so add some influence from the surrounding weights
                    // Additional incides
                    WeightVertex wv0, wv1, wv2, wv3, wv4, wv5, wv6;

                    wv0 = SampleWeightData(ref WeightData, x - 3, y);
                    wv1 = SampleWeightData(ref WeightData, x - 2, y);
                    wv2 = SampleWeightData(ref WeightData, x - 1, y);
                    wv3 = SampleWeightData(ref WeightData, x, y);
                    wv4 = SampleWeightData(ref WeightData, x + 1, y);
                    wv5 = SampleWeightData(ref WeightData, x + 2, y);
                    wv6 = SampleWeightData(ref WeightData, x + 3, y);

                    float value;
                    value = 0.0f;
                    value += (float)wv0.w1 * bf1;
                    value += (float)wv1.w1 * bf2;
                    value += (float)wv2.w1 * bf3;
                    value += (float)wv3.w1 * bf4;
                    value += (float)wv4.w1 * bf3;
                    value += (float)wv5.w1 * bf2;
                    value += (float)wv6.w1 * bf1;
                    FirstPassWD[i].w1 = (byte)value;

                    value = 0.0f;
                    value += (float)wv0.w2 * bf1;
                    value += (float)wv1.w2 * bf2;
                    value += (float)wv2.w2 * bf3;
                    value += (float)wv3.w2 * bf4;
                    value += (float)wv4.w2 * bf3;
                    value += (float)wv5.w2 * bf2;
                    value += (float)wv6.w2 * bf1;
                    FirstPassWD[i].w2 = (byte)value;

                    value = 0.0f;
                    value += (float)wv0.w3 * bf1;
                    value += (float)wv1.w3 * bf2;
                    value += (float)wv2.w3 * bf3;
                    value += (float)wv3.w3 * bf4;
                    value += (float)wv4.w3 * bf3;
                    value += (float)wv5.w3 * bf2;
                    value += (float)wv6.w3 * bf1;
                    FirstPassWD[i].w3 = (byte)value;

                    value = 0.0f;
                    value += (float)wv0.w4 * bf1;
                    value += (float)wv1.w4 * bf2;
                    value += (float)wv2.w4 * bf3;
                    value += (float)wv3.w4 * bf4;
                    value += (float)wv4.w4 * bf3;
                    value += (float)wv5.w4 * bf2;
                    value += (float)wv6.w4 * bf1;
                    FirstPassWD[i].w4 = (byte)value;
                }
            }

            // Vertical pass - writes to final vertex buffer
            DataStream FinalWeightData = wBuffer.Lock(0, 0, LockFlags.None);

            // Blur the weights as we transfer them so the transitions aren't quite so blocky and horrible.
            for (int y = 0; y <= 64; y++) {
                for (int x = 0; x <= 64; x++) {
                    if (x == 0 || x == 64 || y == 0 || y == 64) {
                        // We're at the edge, so just copy the value (don't want to interfere with the way the edges of cells look
                        FinalWeightData.Write(WeightData[65 * y + x]);
                        continue;
                    }

                    // We're not at the edge, so add some influence from the surrounding weights
                    // Additional incides
                    WeightVertex wv0, wv1, wv2, wv3, wv4, wv5, wv6, wvfinal;
                    wv0 = SampleWeightData(ref FirstPassWD, x, y - 3);
                    wv1 = SampleWeightData(ref FirstPassWD, x, y - 2);
                    wv2 = SampleWeightData(ref FirstPassWD, x, y - 1);
                    wv3 = SampleWeightData(ref FirstPassWD, x, y);
                    wv4 = SampleWeightData(ref FirstPassWD, x, y + 1);
                    wv5 = SampleWeightData(ref FirstPassWD, x, y + 2);
                    wv6 = SampleWeightData(ref FirstPassWD, x, y + 3);

                    float value;
                    value = 0.0f;
                    value += (float)wv0.w1 * bf1;
                    value += (float)wv1.w1 * bf2;
                    value += (float)wv2.w1 * bf3;
                    value += (float)wv3.w1 * bf4;
                    value += (float)wv4.w1 * bf3;
                    value += (float)wv5.w1 * bf2;
                    value += (float)wv6.w1 * bf1;
                    wvfinal.w1 = (byte)value;

                    value = 0.0f;
                    value += (float)wv0.w2 * bf1;
                    value += (float)wv1.w2 * bf2;
                    value += (float)wv2.w2 * bf3;
                    value += (float)wv3.w2 * bf4;
                    value += (float)wv4.w2 * bf3;
                    value += (float)wv5.w2 * bf2;
                    value += (float)wv6.w2 * bf1;
                    wvfinal.w2 = (byte)value;

                    value = 0.0f;
                    value += (float)wv0.w3 * bf1;
                    value += (float)wv1.w3 * bf2;
                    value += (float)wv2.w3 * bf3;
                    value += (float)wv3.w3 * bf4;
                    value += (float)wv4.w3 * bf3;
                    value += (float)wv5.w3 * bf2;
                    value += (float)wv6.w3 * bf1;
                    wvfinal.w3 = (byte)value;

                    value = 0.0f;
                    value += (float)wv0.w4 * bf1;
                    value += (float)wv1.w4 * bf2;
                    value += (float)wv2.w4 * bf3;
                    value += (float)wv3.w4 * bf4;
                    value += (float)wv4.w4 * bf3;
                    value += (float)wv5.w4 * bf2;
                    value += (float)wv6.w4 * bf1;
                    wvfinal.w4 = (byte)value;

                    FinalWeightData.Write(wvfinal);
                }
            }

            wBuffer.Unlock();
        }

        ~TextureBank() {
            wBuffer.Dispose();
        }

    };

    class CellTexCreator {
        private struct CellVertex {
            public float x, y, z, w;
            public float u, v;

            public const VertexFormat Format = VertexFormat.Position | VertexFormat.Texture1;
            public const int Stride = 24;
        };

        private struct NormalColorVertex {
            public float nx, ny, nz;
            public byte b, g, r, a;

            public const VertexFormat Format = VertexFormat.Normal | VertexFormat.Diffuse;
            public const int Stride = 16;
        };

        VertexElement[] Elements = new VertexElement[] {
            // Stream 0 - position and texture coordinates
            new VertexElement(0, 0, DeclarationType.Float4, DeclarationMethod.Default, DeclarationUsage.Position, 0),
            new VertexElement(0, 16, DeclarationType.Float2, DeclarationMethod.Default, DeclarationUsage.TextureCoordinate, 0),

            // Stream 1 - normals and vertex colors
            new VertexElement(1, 0, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.Normal, 0),
            new VertexElement(1, 12, DeclarationType.Color, DeclarationMethod.Default, DeclarationUsage.Color, 0),

            // Stream 2 - Texture weights
            new VertexElement(2, 0, DeclarationType.Color, DeclarationMethod.Default, DeclarationUsage.Color, 1),

            VertexElement.VertexDeclarationEnd
        };

        VertexElement[] NormalElements = new VertexElement[] {
            // Stream 0 - position and texture coordinates
            new VertexElement(0, 0, DeclarationType.Float4, DeclarationMethod.Default, DeclarationUsage.Position, 0),
            new VertexElement(0, 16, DeclarationType.Float2, DeclarationMethod.Default, DeclarationUsage.TextureCoordinate, 0),

            // Stream 1 - normals and vertex colors
            new VertexElement(1, 0, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.Normal, 0),
            new VertexElement(1, 12, DeclarationType.Color, DeclarationMethod.Default, DeclarationUsage.Color, 0),

            VertexElement.VertexDeclarationEnd
        };

        private const string EffectPath = @"data files\shaders\CellTexBlend.fx";
        private VertexBuffer vBuffer;
        private VertexBuffer colorBuffer;
        private System.Collections.Generic.List<TextureBank> texBanks;
        private IndexBuffer iBuffer;
        private Texture RenderTargetTex;
        private Texture CompressedTex;
        private Surface RenderTarget;
        private Effect effect;

        private EffectHandle m1h;
        private EffectHandle t1h;
        private EffectHandle t2h;
        private EffectHandle t3h;
        private EffectHandle t4h;

        public CellTexCreator(int Res) {
            texBanks = new System.Collections.Generic.List<TextureBank>();

            // Create basic vertex buffer that can be used for all cells which has positions and texture coordinates
            vBuffer = new VertexBuffer(DXMain.device, CellVertex.Stride * 65 * 65, Usage.WriteOnly, CellVertex.Format, Pool.Managed);
            DataStream CellData = vBuffer.Lock(0, 0, LockFlags.None);

            float mult = (float)(Res / 64);
            for (int y = 0; y <= 64; y++) {
                for (int x = 0; x <= 64; x++) {
                    CellVertex cv;

                    cv.x = ((float)x / 64.0f) * 2.0f - 1.0f;
                    cv.y = ((float)y / 64.0f) * 2.0f - 1.0f;
                    cv.z = 0.5f;
                    cv.w = 1.0f;
                    cv.u = (float)x / 16.0f;
                    cv.v = (float)y / 16.0f;

                    CellData.Write(cv);
                }
            }
            vBuffer.Unlock();

            // Create triangle strip index buffer
            // Size is 2r + 2rc + 2(r-1) where r is rows and c is colums (squares, not vertices)
            iBuffer = new IndexBuffer(DXMain.device, sizeof(Int16) * 8446, Usage.WriteOnly, Pool.Managed, true);
            DataStream iBuf = iBuffer.Lock(0, 0, LockFlags.None);
            for (int y = 0; y < 64; y++) {
                // If this is is a continuation strip, we need to add two extra vertices to create degenerat triangles
                // and get us back to the left side
                if (y > 0) {
                    iBuf.Write((Int16)(y * 65 + (63 + 1)));
                    iBuf.Write((Int16)(y * 65 + 0));
                }

                // Start the row off with a vertex in the lower left corner of the square
                iBuf.Write((Int16)(y * 65 + 0));

                for (int x = 0; x < 64; x++) {
                    // Add the top left and bottom right vertex of each square
                    iBuf.Write((Int16)((y + 1) * 65 + x));
                    iBuf.Write((Int16)(y * 65 + (x + 1)));
                }

                // End the row with the top right vertex
                iBuf.Write((Int16)((y + 1) * 65 + (63 + 1)));
            }

            iBuffer.Unlock();

            // Create the buffers that will contain different information during each render
            colorBuffer = new VertexBuffer(DXMain.device, NormalColorVertex.Stride * 65 * 65, Usage.WriteOnly, NormalColorVertex.Format, Pool.Managed);

            ResetColorsAndNormals();

            RenderTargetTex = new Texture(DXMain.device, Res, Res, 0, Usage.RenderTarget, Format.X8R8G8B8, Pool.Default);
            CompressedTex = new Texture(DXMain.device, Res, Res, 0, Usage.None, Format.Dxt1, Pool.SystemMemory);
            RenderTarget = RenderTargetTex.GetSurfaceLevel(0);
            effect = Effect.FromFile(DXMain.device, EffectPath, ShaderFlags.None);

            m1h = effect.GetParameter(null, "transform");
            t1h = effect.GetParameter(null, "t1");
            t2h = effect.GetParameter(null, "t2");
            t3h = effect.GetParameter(null, "t3");
            t4h = effect.GetParameter(null, "t4");

        }

        public void ResetColorsAndNormals() {
            // By default, the normal will be up and the color will be white
            DataStream ColorNormalData = colorBuffer.Lock(0, 0, LockFlags.None);
            NormalColorVertex defaultncv;
            defaultncv.r = 255;
            defaultncv.g = 255;
            defaultncv.b = 255;
            defaultncv.a = 255;

            defaultncv.nx = 0.0f;
            defaultncv.ny = 0.0f;
            defaultncv.nz = 1.0f;

            for (int y = 0; y <= 64; y++) {
                for (int x = 0; x <= 64; x++) {
                    ColorNormalData.Write(defaultncv);
                }
            }
            colorBuffer.Unlock();
        }

        public void SetDefaultCell(LTEX tex) {
            ResetColorsAndNormals();
            texBanks.Clear();
            TextureBank tb = new TextureBank();
            tb.SetSingleTexture(tex);
            texBanks.Add(tb);
        }

        public void SetCell(LAND cell) {
            // Write the new colors and normals into the color buffer
            DataStream ColorNormalData = colorBuffer.Lock(0, 0, LockFlags.None);
            NormalColorVertex ncv;

            for (int y = 0; y <= 64; y++) {
                for (int x = 0; x <= 64; x++) {
                    ncv.r = cell.Color[x, y].r;
                    ncv.g = cell.Color[x, y].g;
                    ncv.b = cell.Color[x, y].b;
                    ncv.a = 255;

                    ncv.nx = cell.Normals[x, y].X;
                    ncv.ny = cell.Normals[x, y].Y;
                    ncv.nz = cell.Normals[x, y].Z;

                    ColorNormalData.Write(ncv);
                }
            }
            colorBuffer.Unlock();

            // Dispose of any current texture banks
            texBanks.Clear();

            // Group the unique textures in this cell in fours

            // Find all the unique textures in this cell
            System.Collections.Generic.Dictionary<string, LTEX> tex_dict = new System.Collections.Generic.Dictionary<string, LTEX>();
            for (int y = 0; y <= 64; ++y) {
                for (int x = 0; x <= 64; ++x) {
                    int cell_x = cell.xpos;
                    int cell_y = cell.ypos;
                    int tex_x = (int)Math.Floor(((float)x - 1.0f) / 4.0f); // -2.0f
                    int tex_y = (int)Math.Floor(((float)y - 3.0f) / 4.0f); // -2.0f

                    DistantLandForm.ModCell(ref cell_x, ref tex_x);
                    DistantLandForm.ModCell(ref cell_y, ref tex_y);

                    LTEX tmp = DistantLandForm.GetTex(cell_x, cell_y, tex_x, tex_y);
                    string idx = tmp.FilePath;
                    tex_dict[idx] = tmp;
                }
            }

            // Create one bank for each group of 4 textures
            int index = 0;
            TextureBank tb = new TextureBank();
            foreach (LTEX tex in tex_dict.Values) {
                switch (index) {
                    case 0:
                        tb.t1 = tex;
                        ++index;
                        break;
                    case 1:
                        tb.t2 = tex;
                        ++index;
                        break;
                    case 2:
                        tb.t3 = tex;
                        ++index;
                        break;
                    case 3:
                        tb.t4 = tex;
                        texBanks.Add(tb);
                        tb = new TextureBank();
                        index = 0;
                        break;
                }
            }

            if (index != 0) {
                texBanks.Add(tb);
            }

            // Calculate weights for all banks
            foreach (TextureBank bank in texBanks) {
                bank.CalcWeights(cell);
            }
        }

        public void Dispose() {
            vBuffer.Dispose();
            iBuffer.Dispose();
            colorBuffer.Dispose();
            texBanks.Clear();
            RenderTarget.Dispose();
            RenderTargetTex.Dispose();
            CompressedTex.Dispose();
            effect.Dispose();
        }

        public void Begin() {
            DXMain.device.SetRenderState(RenderState.CullMode, Cull.Counterclockwise);
            DXMain.device.SetRenderState(RenderState.Clipping, true);
            DXMain.device.VertexFormat = CellVertex.Format;

            DXMain.device.SetStreamSource(0, vBuffer, 0, CellVertex.Stride);
            DXMain.device.SetStreamSource(1, colorBuffer, 0, NormalColorVertex.Stride);
            VertexDeclaration decl = new VertexDeclaration(DXMain.device, Elements);
            DXMain.device.Indices = iBuffer;
            DXMain.device.VertexDeclaration = decl;
        }

        public void BeginNormalMap() {
            DXMain.device.SetRenderState(RenderState.CullMode, Cull.Counterclockwise);
            DXMain.device.SetRenderState(RenderState.Clipping, true);
            DXMain.device.VertexFormat = CellVertex.Format;

            DXMain.device.SetStreamSource(0, vBuffer, 0, CellVertex.Stride);
            DXMain.device.SetStreamSource(1, colorBuffer, 0, NormalColorVertex.Stride);
            VertexDeclaration decl = new VertexDeclaration(DXMain.device, NormalElements);
            DXMain.device.Indices = iBuffer;
            DXMain.device.VertexDeclaration = decl;
        }

        public void Render(float pos_x, float pos_y, float scale_x, float scale_y) {
            SlimDX.Matrix mat = SlimDX.Matrix.Identity;
            mat.M41 = pos_x;
            mat.M42 = pos_y;
            mat.M11 = scale_x;
            mat.M22 = scale_y;

            effect.SetValue(m1h, mat);

            foreach (TextureBank bank in texBanks) {
                effect.SetTexture(t1h, bank.t1.tex);
                if (bank.t2 != null) {
                    effect.SetTexture(t2h, bank.t2.tex);
                } else {
                    effect.SetTexture(t2h, bank.t1.tex);
                }
                if (bank.t3 != null) {
                    effect.SetTexture(t3h, bank.t3.tex);
                } else {
                    effect.SetTexture(t3h, bank.t1.tex);
                }
                if (bank.t4 != null) {
                    effect.SetTexture(t4h, bank.t4.tex);
                } else {
                    effect.SetTexture(t4h, bank.t1.tex);
                }

                effect.CommitChanges();
                DXMain.device.SetStreamSource(2, bank.wBuffer, 0, TextureBank.WeightVertex.Stride);
                DXMain.device.BeginScene();
                effect.Begin(FX.None);
                effect.BeginPass(0);
                DXMain.device.DrawIndexedPrimitives(PrimitiveType.TriangleStrip, 0, 0, 4225, 0, 8444);
                effect.EndPass();
                effect.End();
                DXMain.device.EndScene();
            }

            DXMain.device.BeginScene();
            effect.Begin(FX.None);
            effect.BeginPass(2);
            DXMain.device.DrawIndexedPrimitives(PrimitiveType.TriangleStrip, 0, 0, 4225, 0, 8444);
            effect.EndPass();
            effect.End();
            DXMain.device.EndScene();
        }



        public void RenderNormalMap(float pos_x, float pos_y, float scale_x, float scale_y) {
            SlimDX.Matrix mat = SlimDX.Matrix.Identity;
            mat.M41 = pos_x;
            mat.M42 = pos_y;
            mat.M11 = scale_x;
            mat.M22 = scale_y;

            effect.SetValue(m1h, mat);

            effect.CommitChanges();
            DXMain.device.BeginScene();
            effect.Begin(FX.None);
            effect.BeginPass(1);
            DXMain.device.DrawIndexedPrimitives(PrimitiveType.TriangleStrip, 0, 0, 4225, 0, 8444);
            effect.EndPass();
            effect.End();
            DXMain.device.EndScene();
        }

        public void End() {
        }

        public void EndNormalMap() {
            End();
        }
    }

    class WorldTexCreator {
        private const string DefaultTex = @"data files\distantland\default.dds";

        private Texture CompressedTex;
        private Texture UncompressedTex;
        private Texture RenderTargetTex;
        private Surface RenderTarget;

        private int MapSpanX, MapSpanY;
        public float x_scale, y_scale, x_spacing, y_spacing;

        public WorldTexCreator(int Res, int map_span_x, int map_span_y) {
            RenderTargetTex = new Texture(DXMain.device, Res, Res, 0, Usage.RenderTarget, Format.X8R8G8B8, Pool.Default);
            CompressedTex = new Texture(DXMain.device, Res, Res, 0, Usage.None, Format.Dxt1, Pool.SystemMemory);
            UncompressedTex = new Texture(DXMain.device, Res, Res, 0, Usage.None, Format.X8R8G8B8, Pool.SystemMemory);
            RenderTarget = RenderTargetTex.GetSurfaceLevel(0);

            MapSpanX = map_span_x;
            MapSpanY = map_span_y;

            x_scale = 1.0f / (float)MapSpanX;
            y_scale = 1.0f / (float)MapSpanY;
            x_spacing = x_scale * 2.0f;
            y_spacing = y_scale * 2.0f;
        }

        public void Begin() {
            Surface rt = DXMain.device.GetRenderTarget(0);
            if (rt != RenderTarget) {
                DXMain.device.SetRenderTarget(0, RenderTarget);
            }
            rt.Dispose();

            DXMain.device.Clear(ClearFlags.Target, 0, 0.0f, 0);
        }

        public void FinishCompressed(string path, bool isSRGB) {
            Surface tmp = UncompressedTex.GetSurfaceLevel(0);
            Surface.FromSurface(tmp, RenderTarget, Filter.None, 0);
            tmp.Dispose();

            // Generate mips
            Filter filter = Filter.Triangle | (isSRGB ? Filter.Srgb : 0);
            UncompressedTex.FilterTexture(0, filter);

            // Compress mips
            for (int i = 0; i < CompressedTex.LevelCount; i++) {
                Surface dest = CompressedTex.GetSurfaceLevel(i);
                Surface src = UncompressedTex.GetSurfaceLevel(i);
                Surface.FromSurface(dest, src, Filter.None, 0);
            }

            Texture.ToFile(CompressedTex, path, ImageFileFormat.Dds);
        }

        public void FinishUncompressed(string path, bool isSRGB) {
            Surface tmp = UncompressedTex.GetSurfaceLevel(0);
            Surface.FromSurface(tmp, RenderTarget, Filter.None, 0);
            tmp.Dispose();

            // Generate mips
            Filter filter = Filter.Triangle | (isSRGB ? Filter.Srgb : 0);
            UncompressedTex.FilterTexture(0, filter);

            Texture.ToFile(UncompressedTex, path, ImageFileFormat.Dds);
        }

        public void Dispose() {
            RenderTarget.Dispose();
            CompressedTex.Dispose();
            UncompressedTex.Dispose();
            RenderTargetTex.Dispose();
        }
    };
}
