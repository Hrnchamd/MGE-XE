
#include "d3d8device.h"
#include "d3d8surface.h"
#include "d3d8texture.h"



ProxyTexture::ProxyTexture(IDirect3DTexture9* real, ProxyDevice* device) : realTexture(real), proxDevice(device) {
    ProxyTexture* proxy = this;
    real->SetPrivateData(guid_proxydx, (void*)&proxy, sizeof(proxy), 0);
}

//-----------------------------------------------------------------------------
/*** IUnknown methods ***/
//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyTexture::QueryInterface(REFIID riid, void** ppvObj) {
    return realTexture->QueryInterface(riid, ppvObj);
}
ULONG _stdcall ProxyTexture::AddRef() {
    return realTexture->AddRef();
}
ULONG _stdcall ProxyTexture::Release() {
    ULONG refcount = realTexture->Release();
    if (!refcount) {
        delete this;
        return 0;
    }
    return refcount;
}

//-----------------------------------------------------------------------------
/*** IDirect3DBaseTexture8 methods ***/
//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyTexture::GetDevice(IDirect3DDevice8** ppDevice) {
    *ppDevice = proxDevice;
    return D3D_OK;
}

HRESULT _stdcall ProxyTexture::SetPrivateData(REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) {
    return realTexture->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

HRESULT _stdcall ProxyTexture::GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData) {
    return realTexture->GetPrivateData(refguid, pData, pSizeOfData);
}

HRESULT _stdcall ProxyTexture::FreePrivateData(REFGUID refguid) {
    return realTexture->FreePrivateData(refguid);
}

//-----------------------------------------------------------------------------

DWORD _stdcall ProxyTexture::SetPriority(DWORD PriorityNew) {
    return realTexture->SetPriority(PriorityNew);
}
DWORD _stdcall ProxyTexture::GetPriority() {
    return realTexture->GetPriority();
}
void _stdcall ProxyTexture::PreLoad() {
    return realTexture->PreLoad();
}
D3DRESOURCETYPE _stdcall ProxyTexture::GetType() {
    return realTexture->GetType();
}

//-----------------------------------------------------------------------------

DWORD _stdcall ProxyTexture::SetLOD(DWORD LODNew) {
    return realTexture->SetLOD(LODNew);
}
DWORD _stdcall ProxyTexture::GetLOD() {
    return realTexture->GetLOD();
}

//-----------------------------------------------------------------------------

DWORD _stdcall ProxyTexture::GetLevelCount() {
    return realTexture->GetLevelCount();
}

HRESULT _stdcall ProxyTexture::GetLevelDesc(UINT Level, D3DSURFACE_DESC8* pDesc) {
    D3DSURFACE_DESC b2;
    HRESULT hr = realTexture->GetLevelDesc(Level, &b2);
    if (hr == D3D_OK) {
        pDesc->Format = b2.Format;
        pDesc->Height = b2.Height;
        pDesc->MultiSampleType = b2.MultiSampleType;
        pDesc->Pool = b2.Pool;
        pDesc->Size = 0; // TODO: Fix;
        pDesc->Type = b2.Type;
        pDesc->Usage = b2.Usage;
        pDesc->Width = b2.Width;
    }
    return hr;
}

HRESULT _stdcall ProxyTexture::GetSurfaceLevel(UINT Level, IDirect3DSurface8** ppSurfaceLevel) {
    IDirect3DSurface9* surface_real = NULL;
    *ppSurfaceLevel = NULL;

    HRESULT hr = realTexture->GetSurfaceLevel(Level, &surface_real);
    if (hr != D3D_OK || surface_real == NULL) {
        return hr;
    }

    ProxySurface* surface = ProxySurface::getProxyFromDX(surface_real);
    if (surface) {
        *ppSurfaceLevel = surface;
    } else {
        *ppSurfaceLevel = proxDevice->factoryProxySurface(surface_real);
    }

    return D3D_OK;
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyTexture::LockRect(UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags) {
    return realTexture->LockRect(Level, pLockedRect, pRect, Flags);
}
HRESULT _stdcall ProxyTexture::UnlockRect(UINT Level) {
    return realTexture->UnlockRect(Level);
}
HRESULT _stdcall ProxyTexture::AddDirtyRect(CONST RECT* pDirtyRect ) {
    return realTexture->AddDirtyRect(pDirtyRect);
}

//-----------------------------------------------------------------------------

// Proxy methods
ProxyTexture* ProxyTexture::getProxyFromDX(IDirect3DBaseTexture9* real) {
    ProxyTexture* tex;
    DWORD data_sz = sizeof(tex);

    HRESULT hr = real->GetPrivateData(guid_proxydx, (void*)&tex, &data_sz);
    if (hr == D3D_OK) {
        return tex;
    }

    return 0;
}
