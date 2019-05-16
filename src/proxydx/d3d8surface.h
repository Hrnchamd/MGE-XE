#pragma once

#include "d3d8interface.h"

class ProxySurface : public IDirect3DSurface8 {
public:
    IDirect3DSurface9* realSurface;
    ProxyDevice* proxDevice;

    ProxySurface(IDirect3DSurface9* real, ProxyDevice* device);

    //-----------------------------------------------------------------------------
    /*** IUnknown methods ***/
    //-----------------------------------------------------------------------------
    HRESULT _stdcall QueryInterface(REFIID riid, void** ppvObj);
    ULONG _stdcall AddRef();
    ULONG _stdcall Release();

    //-----------------------------------------------------------------------------
    /*** IDirect3DSurface8 methods ***/
    //-----------------------------------------------------------------------------
    HRESULT _stdcall GetDevice(IDirect3DDevice8** ppDevice);
    HRESULT _stdcall SetPrivateData(REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags);
    HRESULT _stdcall GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData);
    HRESULT _stdcall FreePrivateData(REFGUID refguid);
    HRESULT _stdcall GetContainer(REFIID riid, void** ppContainer);
    HRESULT _stdcall GetDesc(D3DSURFACE_DESC8* pDesc);

    HRESULT _stdcall LockRect(D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags);
    HRESULT _stdcall UnlockRect();

    // Proxy methods
    static ProxySurface* getProxyFromDX(IDirect3DSurface9* real);
};
