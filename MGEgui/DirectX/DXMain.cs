using System;
using Point = System.Drawing.Point;
using Control = System.Windows.Forms.Control;
using SlimDX;
using SlimDX.Direct3D9;

namespace MGEgui.DirectX {
    static class DXMain {
        public struct MGECaps {
            public int MaxWindowedAA;
            public int MaxFullscreenAA;
            public int MaxAF;
            public int MaxTexSize;
            public int MaxPrimitives;
            public int MaxIndicies;
        }
        private static Format _format;
        private static Capabilities caps;
        private static int adapter;

        public static MGECaps mCaps = new MGECaps();
        public static int Adapter { get { return adapter; } }
        public static Format format { get { return _format; } private set { _format = value; } }

        private static Direct3D d3d;
        private static Device _device;
        public static Device device { get { return _device; } private set { _device = value; } }
        private static Surface _backbuffer;
        public static Surface BackBuffer { get { return _backbuffer; } private set { _backbuffer = value; } }

        private static readonly PresentParameters devParams;

        static DXMain() {
            d3d = new Direct3D();
            format = Format.A8R8G8B8;

            devParams = new PresentParameters();
            devParams.BackBufferCount = 1;
            devParams.BackBufferFormat = format;
            devParams.BackBufferWidth = 960;
            devParams.BackBufferHeight = 540;
            devParams.EnableAutoDepthStencil = false;
            devParams.Multisample = MultisampleType.None;
            devParams.SwapEffect = SwapEffect.Discard;
            devParams.Windowed = true;
            devParams.PresentationInterval = PresentInterval.One;
        }

        public static bool CheckAdapter() {
            object value = Microsoft.Win32.Registry.GetValue(@"HKEY_LOCAL_MACHINE\SOFTWARE\Bethesda Softworks\Morrowind", "Adapter", 0);
            adapter = (value != null) ? (int)value : 0;
            return adapter < d3d.AdapterCount;
        }
        
        public static void ResetAdapter() {
            adapter = 0;
            Microsoft.Win32.Registry.SetValue(@"HKEY_LOCAL_MACHINE\SOFTWARE\Bethesda Softworks\Morrowind", "Adapter", adapter);
        }

        public static void GetDeviceCaps() {
            object value = Microsoft.Win32.Registry.GetValue(@"HKEY_LOCAL_MACHINE\SOFTWARE\Bethesda Softworks\Morrowind", "Adapter", 0);
            adapter = (value != null) ? (int)value : 0;

            if (d3d.AdapterCount <= adapter) {
                throw new ApplicationException("Morrowind is set up to use a graphics card which could not be found on your system.");
            }

            for (int i = 2; i <= 16; i++) {
                if (d3d.CheckDeviceMultisampleType(adapter, DeviceType.Hardware, Format.X8R8G8B8, false, (MultisampleType)i)) {
                    mCaps.MaxFullscreenAA = i;
                }
                if (d3d.CheckDeviceMultisampleType(adapter, DeviceType.Hardware, Format.X8R8G8B8, true, (MultisampleType)i)) {
                    mCaps.MaxWindowedAA = i;
                }
            }

            caps = d3d.GetDeviceCaps(adapter, DeviceType.Hardware);

            mCaps.MaxAF = caps.MaxAnisotropy;
            mCaps.MaxTexSize = Math.Min(caps.MaxTextureHeight, caps.MaxTextureWidth);
            mCaps.MaxPrimitives = caps.MaxPrimitiveCount;
            mCaps.MaxIndicies = caps.MaxVertexIndex;
        }

        public static int[] GetRefreshRates(int width, int height) {
            System.Collections.Generic.List<int> rates = new System.Collections.Generic.List<int>();
            foreach (DisplayMode ds in d3d.Adapters[adapter].GetDisplayModes(Format.X8R8G8B8)) {
                if (ds.Width == width && ds.Height == height) {
                    rates.Add(ds.RefreshRate);
                }
            }
            return rates.ToArray();
        }

        public static Point[] GetResolutions() {
            System.Collections.Generic.List<Point> resolutions = new System.Collections.Generic.List<Point>();
            foreach (DisplayMode ds in d3d.Adapters[adapter].GetDisplayModes(Format.X8R8G8B8)) {
                if (!resolutions.Contains(new Point(ds.Width, ds.Height))) {
                    resolutions.Add(new Point(ds.Width, ds.Height));
                }
            }
            return resolutions.ToArray();
        }

        public static void CreateDevice(Control window) {
            CloseDevice();

            device = new Device(d3d, adapter, DeviceType.Hardware, window.Handle, CreateFlags.FpuPreserve | CreateFlags.Multithreaded | CreateFlags.HardwareVertexProcessing, devParams);

            // BackBuffer = device.GetBackBuffer(0, 0, BackBufferType.Mono);
            BackBuffer = device.GetRenderTarget(0);

            device.SetRenderState(RenderState.Lighting, false);
            device.SetRenderState(RenderState.ZEnable, false);
            device.SetRenderState(RenderState.StencilEnable, false);
            device.SetRenderState(RenderState.Ambient, int.MinValue);
        }

        public static void CloseDevice() {
            if (BackBuffer != null) {
                BackBuffer.Dispose();
                BackBuffer = null;
            }
            if (device != null) {
                device.Dispose();
                device = null;
            }
        }

        public static bool CheckAALevel(int level, bool windowed) {
            if (level < 4) {
                // <= 8x MSAA
                return d3d.CheckDeviceMultisampleType(adapter, DeviceType.Hardware, Format.X8R8G8B8, windowed, (MultisampleType)(1 << level));
            } else {
                // 16x is a special case, map to 16x CSAA (8 samples, quality 2)
                Int32 qualityLevels;
                bool result = d3d.CheckDeviceMultisampleType(adapter, DeviceType.Hardware, Format.X8R8G8B8, windowed, MultisampleType.EightSamples, out qualityLevels);
                return result && (qualityLevels >= 3);
            }
        }
    }
}