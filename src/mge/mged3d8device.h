#pragma once

#include "proxydx/d3d8device.h"



class MGEProxyDevice : public ProxyDevice {
public:
    MGEProxyDevice(IDirect3DDevice9* real, ProxyD3D* d3d);
    ULONG _stdcall Release(void);

    HRESULT _stdcall Present(const RECT* a, const RECT* b, HWND c, const RGNDATA* d);
    HRESULT _stdcall SetRenderTarget(IDirect3DSurface8* a, IDirect3DSurface8* b);
    HRESULT _stdcall BeginScene();
    HRESULT _stdcall EndScene();
    HRESULT _stdcall Clear(DWORD a, const D3DRECT* b, DWORD c, D3DCOLOR d, float e, DWORD f);
    HRESULT _stdcall SetTransform(D3DTRANSFORMSTATETYPE a, const D3DMATRIX* b);
    HRESULT _stdcall SetMaterial(const D3DMATERIAL8* a);
    HRESULT _stdcall SetLight(DWORD a, const D3DLIGHT8* b);
    HRESULT _stdcall LightEnable(DWORD a, BOOL b);
    HRESULT _stdcall SetRenderState(D3DRENDERSTATETYPE a, DWORD b);
    HRESULT _stdcall SetTextureStageState(DWORD a, D3DTEXTURESTAGESTATETYPE b, DWORD c);
    HRESULT _stdcall SetTexture(DWORD a, IDirect3DBaseTexture8* b);
    HRESULT _stdcall DrawIndexedPrimitive(D3DPRIMITIVETYPE a, UINT b, UINT c, UINT d, UINT e);
    HRESULT _stdcall SetVertexShader(DWORD a);
    HRESULT _stdcall SetStreamSource(UINT a, IDirect3DVertexBuffer8* b, UINT c);
    HRESULT _stdcall SetIndices(IDirect3DIndexBuffer8* a, UINT b);
};
