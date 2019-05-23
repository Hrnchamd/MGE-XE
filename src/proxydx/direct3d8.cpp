
#include "direct3d8.h"
#include "d3d8device.h"

#include <cstdio>



typedef IDirect3D8* (_stdcall* D3DProc8)(UINT);


ProxyD3D::ProxyD3D(IDirect3D9* real, UINT d3d8version) : refcount(1), realD3D(real) {
    char syspath[MAX_PATH], path[MAX_PATH];
    GetSystemDirectoryA(syspath, sizeof(syspath));
    std::snprintf(path, sizeof(path), "%s\\%s", syspath, "d3d8.dll");

    // Cache a D3D8-specific caps set, which may vary by version parameter
    HMODULE d3ddll = LoadLibrary(path);
    D3DProc8 func8 = (D3DProc8)GetProcAddress(d3ddll, "Direct3DCreate8");
    IDirect3D8* d3d8 = (func8)(d3d8version);
    d3d8->GetDeviceCaps(0, D3DDEVTYPE_HAL, &d3d8Caps);
    d3d8->Release();
    FreeLibrary(d3ddll);
}

//-----------------------------------------------------------------------------
/*** IUnknown methods ***/
//-----------------------------------------------------------------------------
HRESULT _stdcall ProxyD3D::QueryInterface(REFIID a, LPVOID* b) {
    return realD3D->QueryInterface(a, b);
}
ULONG _stdcall ProxyD3D::AddRef(void) {
    return ++refcount;
}

ULONG _stdcall ProxyD3D::Release(void) {
    if (--refcount == 0) {
        realD3D->Release();
        delete this;
        return 0;
    }
    return refcount;
}

//-----------------------------------------------------------------------------
/*** IDirect3D8 methods ***/
//-----------------------------------------------------------------------------
HRESULT _stdcall ProxyD3D::RegisterSoftwareDevice(void* a) {
    return realD3D->RegisterSoftwareDevice(a);
}
UINT _stdcall ProxyD3D::GetAdapterCount(void) {
    return realD3D->GetAdapterCount();
}

HRESULT _stdcall ProxyD3D::GetAdapterIdentifier(UINT a, DWORD b, D3DADAPTER_IDENTIFIER8* c) {
    D3DADAPTER_IDENTIFIER9 c2;
    HRESULT hr = realD3D->GetAdapterIdentifier(a, 0, &c2);
    if (hr == D3D_OK) {
        // Strings, so use copymemory instead of assignment
        ::CopyMemory(c, &c2, 1024);
        c->DeviceId = c2.DeviceId;
        c->DeviceIdentifier = c2.DeviceIdentifier;
        c->DriverVersion = c2.DriverVersion;
        c->Revision = c2.Revision;
        c->SubSysId = c2.SubSysId;
        c->VendorId = c2.VendorId;
        c->WHQLLevel = c2.WHQLLevel;
    }
    return hr;
}

UINT _stdcall ProxyD3D::GetAdapterModeCount(UINT a) {
    return realD3D->GetAdapterModeCount(a, D3DFMT_X8R8G8B8);
}
HRESULT _stdcall ProxyD3D::EnumAdapterModes(UINT a, UINT b, D3DDISPLAYMODE* c) {
    return realD3D->EnumAdapterModes(a, D3DFMT_X8R8G8B8, b, c);
}

HRESULT _stdcall ProxyD3D::GetAdapterDisplayMode(UINT a, D3DDISPLAYMODE* b) {
    // Hide the fact that windows is using a 16-bit colour depth
    HRESULT hr = realD3D->GetAdapterDisplayMode(a, b);
    b->Format = D3DFMT_X8R8G8B8;
    return hr;
}

HRESULT _stdcall ProxyD3D::CheckDeviceType(UINT a, D3DDEVTYPE b, D3DFORMAT c, D3DFORMAT d, BOOL e) {
    return realD3D->CheckDeviceType(a, b, c, d, e);
}
HRESULT _stdcall ProxyD3D::CheckDeviceFormat(UINT a, D3DDEVTYPE b, D3DFORMAT c, DWORD d, D3DRESOURCETYPE e, D3DFORMAT f) {
    return realD3D->CheckDeviceFormat(a, b, c, d, e, f);
}
HRESULT _stdcall ProxyD3D::CheckDeviceMultiSampleType(UINT a, D3DDEVTYPE b, D3DFORMAT c, BOOL d, D3DMULTISAMPLE_TYPE e) {
    return realD3D->CheckDeviceMultiSampleType(a, b, c, d, e, NULL);
}
HRESULT _stdcall ProxyD3D::CheckDepthStencilMatch(UINT a, D3DDEVTYPE b, D3DFORMAT c, D3DFORMAT d, D3DFORMAT e) {
    return realD3D->CheckDepthStencilMatch(a, b, c, d, e);
}
HRESULT _stdcall ProxyD3D::GetDeviceCaps(UINT a, D3DDEVTYPE b, D3DCAPS8* c) {
    *c = d3d8Caps;
    return D3D_OK;
}
HMONITOR _stdcall ProxyD3D::GetAdapterMonitor(UINT a) {
    return realD3D->GetAdapterMonitor(a);
}

HRESULT _stdcall ProxyD3D::CreateDevice(UINT a, D3DDEVTYPE b, HWND c, DWORD d, D3DPRESENT_PARAMETERS8* e, IDirect3DDevice8** f) {
    D3DPRESENT_PARAMETERS9 e2;

    e2.BackBufferWidth = e->BackBufferWidth;
    e2.BackBufferHeight = e->BackBufferHeight;
    e2.BackBufferFormat = e->BackBufferFormat;
    e2.BackBufferCount = e->BackBufferCount;
    e2.MultiSampleType = e->MultiSampleType;
    e2.MultiSampleQuality = 0;
    e2.SwapEffect = e->SwapEffect;
    e2.hDeviceWindow = e->hDeviceWindow;
    e2.Windowed = e->Windowed;
    e2.Flags = e->Flags;
    e2.EnableAutoDepthStencil = e->EnableAutoDepthStencil;
    e2.AutoDepthStencilFormat = e->AutoDepthStencilFormat;
    e2.FullScreen_RefreshRateInHz = e->FullScreen_RefreshRateInHz;
    e2.PresentationInterval = e->FullScreen_PresentationInterval;

    IDirect3DDevice9* RealDevice = NULL;
    HRESULT hr = realD3D->CreateDevice(a, b, c, d, &e2, &RealDevice);

    if (hr != D3D_OK || RealDevice == NULL) {
        return hr;
    }

    *f = factoryProxyDevice(RealDevice);
    return D3D_OK;
}

// Proxy factory methods
IDirect3DDevice8* ProxyD3D::factoryProxyDevice(IDirect3DDevice9* d) {
    return new ProxyDevice(d, this);
}
