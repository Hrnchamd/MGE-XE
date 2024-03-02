
Builds with CMake 2.8 or later.

This project is primarily written for GCC; an MSVC solution is also maintained. There are no compiler specific defines or inline assembler used, but attention should be paid to abstracting calling conventions and the C++ ABI properly.

Build outputs:

d3d8.dll, intercepts standard Morrowind D3D functions and adds features.
dinput8.dll, a shim dll that redirects input to d3d8.dll, as all input processing functions are in d3d8.dll.
MGEXEgui, a .net GUI that configures MGE and generates the distant world files that allows long view ranges.
MGEfuncs.dll, a helper dll for MGEXEgui that processes Morrowind format models with niflib/tootlelib.

Build dependencies required:

DirectX SDK June 2010 or later: <http://msdn.microsoft.com/en-us/directx/>
SlimDX: <https://code.google.com/archive/p/slimdx/downloads>

Runtime dependencies required:

DirectX 9 June 2010, for the d3dx runtime library
SlimDX redistributable, for MGEXEgui
