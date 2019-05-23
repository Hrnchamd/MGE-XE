#pragma once

#include "proxydx/direct3d8.h"



class MGEProxyD3D : public ProxyD3D {
public:
    MGEProxyD3D(IDirect3D9* real);

    HRESULT _stdcall CreateDevice(UINT a, D3DDEVTYPE b, HWND c, DWORD d, D3DPRESENT_PARAMETERS8* e, IDirect3DDevice8** f);

    IDirect3DDevice8* factoryProxyDevice(IDirect3DDevice9* d);
};
