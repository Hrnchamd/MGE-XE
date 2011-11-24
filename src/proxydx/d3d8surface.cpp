
#include "d3d8surface.h"

ProxySurface::ProxySurface(IDirect3DSurface9 *real, IDirect3DDevice8 *ob) : realSurface(real), fakeDevice(ob)
{
    void *This = this;
    real->SetPrivateData(guid, (void *)&This, 4, 0);
}

//-----------------------------------------------------------------------------
/*** IUnknown methods ***/
//-----------------------------------------------------------------------------
HRESULT _stdcall ProxySurface::QueryInterface(REFIID riid, void **ppvObj) { return realSurface->QueryInterface(riid, ppvObj); }
ULONG _stdcall ProxySurface::AddRef() { return realSurface->AddRef(); }

ULONG _stdcall ProxySurface::Release()
{
    ULONG refcount = realSurface->Release();
    if(!refcount)
    {
        delete this;
        return 0;
    }
    return refcount;
}

//-----------------------------------------------------------------------------
/*** IDirect3DSurface8 methods ***/
//-----------------------------------------------------------------------------

HRESULT _stdcall ProxySurface::GetDevice(IDirect3DDevice8 **ppDevice) { *ppDevice = fakeDevice; return D3D_OK; }
HRESULT _stdcall ProxySurface::SetPrivateData(REFGUID refguid, CONST void *pData, DWORD SizeOfData, DWORD Flags) { return realSurface->SetPrivateData(refguid, pData, SizeOfData, Flags); }
HRESULT _stdcall ProxySurface::GetPrivateData(REFGUID refguid, void *pData, DWORD *pSizeOfData) { return realSurface->GetPrivateData(refguid, pData, pSizeOfData); }
HRESULT _stdcall ProxySurface::FreePrivateData(REFGUID refguid) { return realSurface->FreePrivateData(refguid); }
HRESULT _stdcall ProxySurface::GetContainer(REFIID riid, void **ppContainer) { return realSurface->GetContainer(riid, ppContainer); }

HRESULT _stdcall ProxySurface::GetDesc(D3DSURFACE_DESC8 *pDesc)
{
    D3DSURFACE_DESC a2;
    HRESULT hr = realSurface->GetDesc(&a2);
    if(hr == D3D_OK)
    {
        pDesc->Format = a2.Format;
        pDesc->Height = a2.Height;
        pDesc->MultiSampleType = a2.MultiSampleType;
        pDesc->Pool = a2.Pool;
        pDesc->Size = 0; //TODO: Fix;
        pDesc->Type = a2.Type;
        pDesc->Usage = a2.Usage;
        pDesc->Width = a2.Width;
    }
    return hr;
}

HRESULT _stdcall ProxySurface::LockRect(D3DLOCKED_RECT *pLockedRect, CONST RECT *pRect, DWORD Flags) { return realSurface->LockRect(pLockedRect, pRect, Flags); }
HRESULT _stdcall ProxySurface::UnlockRect() { return realSurface->UnlockRect(); }
