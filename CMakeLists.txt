cmake_minimum_required (VERSION 2.6)

project (MGEXE)

include_directories (${MGEXE_SOURCE_DIR}/src)
link_directories (${MGEXE_SOURCE_DIR}/lib)
set (LIBRARY_OUTPUT_PATH ${MGEXE_BINARY_DIR}/bin)

# d3d8.dll to be installed to Morrowind directory
add_library (d3d8 SHARED src/support/log.cpp src/support/strsec.cpp src/mge/configuration.cpp src/mge/distantinit.cpp src/mge/distantland.cpp src/mge/DLMath.cpp src/mge/macrofunctions.cpp src/mge/MemoryPool.cpp src/mge/mged3d8device.cpp src/mge/mgedinput.cpp src/mge/mgedirect3d8.cpp src/mge/mgedxwrap.cpp src/mge/MorrowindBSA.cpp src/mge/mwbridge.cpp src/mge/postshaders.cpp src/mge/QuadTree.cpp src/mge/renderdepth.cpp src/mge/renderexterior.cpp src/mge/rendergrass.cpp src/mge/rendershadow.cpp src/mge/renderwater.cpp src/mge/statusoverlay.cpp src/mge/userhud.cpp src/mwse/funcgeneral.cpp src/mwse/funcgmst.cpp src/mwse/funchud.cpp src/mwse/funczoom.cpp src/mwse/mgebridge.cpp src/mwse/mwseinstruction.cpp src/proxydx/d3d8device.cpp src/proxydx/d3d8surface.cpp src/proxydx/d3d8texture.cpp src/proxydx/dinput8.cpp src/proxydx/direct3d8.cpp src/proxydx/dxguid.cpp src/main.cpp src/exports.def)

target_link_libraries (d3d8 kernel32 gdi32 user32 d3d9 d3dx9)

# dinput8.dll to be installed to Morrowind directory
add_library (dinput8 SHARED src/dinput_shim/dinput.cpp src/dinput_shim/exports.def)

target_link_libraries (dinput8 kernel32)

# Make sure dll does not have lib- prefix
set_target_properties (d3d8 PROPERTIES PREFIX "")

if (CMAKE_COMPILER_IS_GNUCXX)
    # Compile options; optimize, strip symbols and kill stdcall decoration
    set (CMAKE_CXX_FLAGS "-O2 -march=pentium4")
    set (CMAKE_EXE_LINKER_FLAGS "-s --kill-at")
endif (CMAKE_COMPILER_IS_GNUCXX)

if (MSVC_VERSION)
    # Compile options; optimize
    set (CMAKE_CXX_FLAGS "/O2 /arch:SSE2")
endif (MSVC_VERSION)

# TODO: mgefuncs.dll build (install to Morrowind/mge3 directory)
# TODO: MGEXEgui build (install to Morrowind directory)
