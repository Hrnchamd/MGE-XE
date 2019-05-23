
#include "d3d8device.h"
#include "d3d8surface.h"
#include "d3d8texture.h"



const GUID IID_IDirect3DDevice8 = { 0x7385e5df, 0x8fe8, 0x41d5, 0x86, 0xb6, 0xd7, 0xb4, 0x85, 0x47, 0xb6, 0xcf };
const GUID IID_IDirect3DTexture8 = { 0xe4cdd575, 0x2866, 0x4f01, 0xb1, 0x2e, 0x7e, 0xec, 0xe1, 0xec, 0x93, 0x58 };
const GUID IID_IDirect3DDevice9 = { 0xd0223b96, 0xbf7a, 0x43fd, 0x92, 0xbd, 0xa4, 0x3b, 0xd, 0x82, 0xb9, 0xeb };
const GUID IID_IDirect3DTexture9 = { 0x85c31227, 0x3de5, 0x4f00, 0x9b, 0x3a, 0xf1, 0x1a, 0xc3, 0x8c, 0x18, 0xb5 };


ProxySurface::ProxySurface(IDirect3DSurface9* real, ProxyDevice* device) : realSurface(real), proxDevice(device) {
    ProxySurface* proxy = this;
    real->SetPrivateData(guid_proxydx, (void*)&proxy, sizeof(proxy), 0);
}

//-----------------------------------------------------------------------------
/*** IUnknown methods ***/
//-----------------------------------------------------------------------------
HRESULT _stdcall ProxySurface::QueryInterface(REFIID riid, void** ppvObj) {
    return realSurface->QueryInterface(riid, ppvObj);
}
ULONG _stdcall ProxySurface::AddRef() {
    return realSurface->AddRef();
}

ULONG _stdcall ProxySurface::Release() {
    ULONG refcount = realSurface->Release();
    if (!refcount) {
        delete this;
        return 0;
    }
    return refcount;
}

//-----------------------------------------------------------------------------
/*** IDirect3DSurface8 methods ***/
//-----------------------------------------------------------------------------

HRESULT _stdcall ProxySurface::GetDevice(IDirect3DDevice8** ppDevice) {
    *ppDevice = proxDevice;
    return D3D_OK;
}
HRESULT _stdcall ProxySurface::SetPrivateData(REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) {
    return realSurface->SetPrivateData(refguid, pData, SizeOfData, Flags);
}
HRESULT _stdcall ProxySurface::GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData) {
    return realSurface->GetPrivateData(refguid, pData, pSizeOfData);
}
HRESULT _stdcall ProxySurface::FreePrivateData(REFGUID refguid) {
    return realSurface->FreePrivateData(refguid);
}

HRESULT _stdcall ProxySurface::GetContainer(REFIID riid, void** ppContainer) {
    if (riid == IID_IDirect3DTexture8) {
        IDirect3DTexture9* tex = NULL;
        HRESULT hr = realSurface->GetContainer(IID_IDirect3DTexture9, (void**)&tex);
        *ppContainer = (hr == D3D_OK) ? ProxyTexture::getProxyFromDX(tex) : NULL;
        return hr;
    } else if (riid == IID_IDirect3DDevice8) {
        proxDevice->AddRef();
        *ppContainer = proxDevice;
        return D3D_OK;
    }
    return D3DERR_INVALIDCALL;
}

HRESULT _stdcall ProxySurface::GetDesc(D3DSURFACE_DESC8* pDesc) {
    D3DSURFACE_DESC a2;
    HRESULT hr = realSurface->GetDesc(&a2);
    if (hr == D3D_OK) {
        pDesc->Format = a2.Format;
        pDesc->Height = a2.Height;
        pDesc->MultiSampleType = a2.MultiSampleType;
        pDesc->Pool = a2.Pool;
        pDesc->Size = 0; // TODO: Fix;
        pDesc->Type = a2.Type;
        pDesc->Usage = a2.Usage;
        pDesc->Width = a2.Width;
    }
    return hr;
}

HRESULT _stdcall ProxySurface::LockRect(D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags) {
    return realSurface->LockRect(pLockedRect, pRect, Flags);
}
HRESULT _stdcall ProxySurface::UnlockRect() {
    return realSurface->UnlockRect();
}

// Proxy methods
ProxySurface* ProxySurface::getProxyFromDX(IDirect3DSurface9* real) {
    ProxySurface* surface;
    DWORD data_sz = sizeof(surface);

    HRESULT hr = real->GetPrivateData(guid_proxydx, (void*)&surface, &data_sz);
    if (hr == D3D_OK) {
        return surface;
    }

    return 0;
}
