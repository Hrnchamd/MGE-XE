#pragma once

#ifdef DEBUG
#define D3D_DEBUG_INFO
#endif

#define D3DXFX_LARGEADDRESS_HANDLE

#include <d3d9.h>
#include <d3dx9.h>

// Remove annoying defines from windows.h
#undef near
#undef far
#undef NEAR
#undef FAR
#define NEAR
#define FAR