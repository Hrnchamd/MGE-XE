#pragma once

#include "d3d8interface.h"

class ProxyTexture : public IDirect3DTexture8 {
public:
    IDirect3DTexture9* realTexture;
    ProxyDevice* proxDevice;

    ProxyTexture(IDirect3DTexture9* real, ProxyDevice* device);

    //-----------------------------------------------------------------------------
    /*** IUnknown methods ***/
    //-----------------------------------------------------------------------------
    HRESULT _stdcall QueryInterface(REFIID riid, void** ppvObj);
    ULONG _stdcall AddRef();
    ULONG _stdcall Release();

    //-----------------------------------------------------------------------------
    /*** IDirect3DBaseTexture8 methods ***/
    //-----------------------------------------------------------------------------
    HRESULT _stdcall GetDevice(IDirect3DDevice8** ppDevice);
    HRESULT _stdcall SetPrivateData(REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags);
    HRESULT _stdcall GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData);
    HRESULT _stdcall FreePrivateData(REFGUID refguid);
    DWORD _stdcall SetPriority(DWORD PriorityNew);
    DWORD _stdcall GetPriority();
    void _stdcall PreLoad();
    D3DRESOURCETYPE _stdcall GetType();
    DWORD _stdcall SetLOD(DWORD LODNew);
    DWORD _stdcall GetLOD();
    DWORD _stdcall GetLevelCount();
    HRESULT _stdcall GetLevelDesc(UINT Level, D3DSURFACE_DESC8* pDesc);
    HRESULT _stdcall GetSurfaceLevel(UINT Level, IDirect3DSurface8** ppSurfaceLevel);
    HRESULT _stdcall LockRect(UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags);
    HRESULT _stdcall UnlockRect(UINT Level);
    HRESULT _stdcall AddDirtyRect(CONST RECT* pDirtyRect);

    // Proxy methods
    static ProxyTexture* getProxyFromDX(IDirect3DBaseTexture9* real);
};
