
#include "d3d8interface.h"
#pragma once

class ProxyD3D : public IDirect3D8 {
public:
    DWORD refcount;
    IDirect3D9* realD3D;
    D3DCAPS8 d3d8Caps;

    ProxyD3D(IDirect3D9* real, UINT d3d8version);

    //-----------------------------------------------------------------------------
    /*** IUnknown methods ***/
    //-----------------------------------------------------------------------------
    HRESULT _stdcall QueryInterface(REFIID a, LPVOID* b);
    ULONG _stdcall AddRef(void);
    ULONG _stdcall Release(void);

    //-----------------------------------------------------------------------------
    /*** IDirect3D8 methods ***/
    //-----------------------------------------------------------------------------
    HRESULT _stdcall RegisterSoftwareDevice(void* a);
    UINT _stdcall GetAdapterCount(void);
    HRESULT _stdcall GetAdapterIdentifier(UINT a, DWORD b, D3DADAPTER_IDENTIFIER8* c);
    UINT _stdcall GetAdapterModeCount(UINT a);
    HRESULT _stdcall EnumAdapterModes(UINT a, UINT b, D3DDISPLAYMODE* c);
    HRESULT _stdcall GetAdapterDisplayMode(UINT a, D3DDISPLAYMODE* b);
    HRESULT _stdcall CheckDeviceType(UINT a, D3DDEVTYPE b, D3DFORMAT c, D3DFORMAT d, BOOL e);
    HRESULT _stdcall CheckDeviceFormat(UINT a, D3DDEVTYPE b, D3DFORMAT c, DWORD d, D3DRESOURCETYPE e, D3DFORMAT f);
    HRESULT _stdcall CheckDeviceMultiSampleType(UINT a, D3DDEVTYPE b, D3DFORMAT c, BOOL d, D3DMULTISAMPLE_TYPE e);
    HRESULT _stdcall CheckDepthStencilMatch(UINT a, D3DDEVTYPE b, D3DFORMAT c, D3DFORMAT d, D3DFORMAT e);
    HRESULT _stdcall GetDeviceCaps(UINT a, D3DDEVTYPE b, D3DCAPS8* c);
    HMONITOR _stdcall GetAdapterMonitor(UINT a);
    HRESULT _stdcall CreateDevice(UINT a, D3DDEVTYPE b, HWND c, DWORD d, D3DPRESENT_PARAMETERS8* e, IDirect3DDevice8** f);

    // Proxy factory methods
    virtual IDirect3DDevice8* factoryProxyDevice(IDirect3DDevice9* d);
};
