using System;
using System.Runtime.InteropServices;

namespace MGEgui {
    /// <summary>
    /// This class contains all imported unmanaged functions.
    /// </summary>
    /// <remarks>
    /// It's easier to keep them in one place if I'm going to keep changing names around
    /// </remarks>
    internal class NativeMethods {
        [DllImport("MGE3/MGEfuncs.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "BeginStaticCreation")]
        internal static extern void BeginStaticCreation(IntPtr device, string outpath);
        [DllImport("MGE3/MGEfuncs.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "EndStaticCreation")]
        internal static extern void EndStaticCreation();
        [DllImport("MGE3/MGEfuncs.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "ProcessNif")]
        internal static extern float ProcessNif(
            [MarshalAs(UnmanagedType.LPArray)] byte[] data, int datasize, float simplify, float cutoff, byte static_type, byte oldAlgorithm);
        [DllImport("MGE3/MGEfuncs.dll", CallingConvention = CallingConvention.StdCall,
            CharSet = CharSet.Ansi, EntryPoint = "TessellateLandscape")]
        internal static extern void TessellateLandscape([MarshalAs(UnmanagedType.LPStr)] string file_path, [MarshalAs(UnmanagedType.LPArray)] float[] height_data, uint data_height, uint data_width, float top, float left, float bottom, float right, float error_tolerance);

        [DllImport("MGE3/MGEfuncs.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "GetVertSize")]
        internal static extern int GetVertSize();
        [DllImport("MGE3/MGEfuncs.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "GetCompressedVertSize")]
        internal static extern int GetCompressedVertSize();
        [DllImport("MGE3/MGEfuncs.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi, EntryPoint = "GetLandVertSize")]
        internal static extern int GetLandVertSize();
    }
}
