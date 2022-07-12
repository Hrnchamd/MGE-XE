
# Building

*How to build this project with `CMake 2.8+`.*

<br>

## Toolchain

This project is primarily written for **GCC**. <br>
A **MSVC** solution is also maintained.

<br>
<br>

## Decoupled

There are no compiler specific defines or inline assembler used, <br>
but attention should be paid to abstracting calling conventions <br>
and the C++ ABI properly.

<br>
<br>

## Output

*Files that are generated during compilation.*

<br>

### `d3d8.dll`

Intercepts standard Morrowind <br>
**D3D** functions and adds features.

<br>

### `dinput8.dll`

A shim `dll` that redirects input to `d3d8.dll`, as <br>
all input processing functions are in `d3d8.dll`.

<br>

### `MGEfuncs.dll`

A helper `dll` for **MGEXEgui** that processes <br>
**Morrowind** format models with niflib / tootlelib.

<br>

### `MGEXEgui`

A **.NET GUI** that configures **MGE** and generates the <br>
distant world files that allows long view ranges.

<br>




