#pragma once

#include "d3d8interface.h"

class ProxyDevice : public IDirect3DDevice8 {
public:
    DWORD refcount;
    IDirect3DDevice9* realDevice;
    ProxyD3D* proxD3D8;
    UINT baseVertexIndex;
    D3DGAMMARAMP gammaDefault;

    ProxyDevice(IDirect3DDevice9* real, ProxyD3D* d3d);

    //-----------------------------------------------------------------------------
    /*** IUnknown methods ***/
    //-----------------------------------------------------------------------------
    HRESULT _stdcall QueryInterface(REFIID a, LPVOID* b);
    ULONG _stdcall AddRef(void);
    ULONG _stdcall Release(void);

    //-----------------------------------------------------------------------------
    /*** IDirect3DDevice8 methods ***/
    //-----------------------------------------------------------------------------
    HRESULT _stdcall TestCooperativeLevel(void);
    UINT _stdcall GetAvailableTextureMem(void);
    HRESULT _stdcall ResourceManagerDiscardBytes(DWORD a);
    HRESULT _stdcall GetDirect3D(IDirect3D8** a);
    HRESULT _stdcall GetDeviceCaps(D3DCAPS8* a);
    HRESULT _stdcall GetDisplayMode(D3DDISPLAYMODE* a);
    HRESULT _stdcall GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* a);

    HRESULT _stdcall SetCursorProperties(UINT a, UINT b, IDirect3DSurface8* c);
    void _stdcall SetCursorPosition(int X, int Y, DWORD c);
    BOOL _stdcall ShowCursor(BOOL a);

    HRESULT _stdcall CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS8* a, IDirect3DSwapChain8** b) { return UnusedFunction(); }
    HRESULT _stdcall Reset(D3DPRESENT_PARAMETERS8* a) { return UnusedFunction(); }
    HRESULT _stdcall Present(const RECT* a, const RECT* b, HWND c, const RGNDATA* d);
    HRESULT _stdcall GetBackBuffer(UINT a, D3DBACKBUFFER_TYPE b, IDirect3DSurface8** c);

    HRESULT _stdcall GetRasterStatus(D3DRASTER_STATUS* a);
    void _stdcall SetGammaRamp(DWORD a, const D3DGAMMARAMP* b);
    void _stdcall GetGammaRamp(D3DGAMMARAMP* a);

    HRESULT _stdcall CreateTexture(UINT a, UINT b, UINT c, DWORD d, D3DFORMAT e, D3DPOOL f, IDirect3DTexture8** g);
    HRESULT _stdcall CreateVolumeTexture(UINT a, UINT b, UINT c, UINT d, DWORD e, D3DFORMAT f, D3DPOOL g, IDirect3DVolumeTexture8** h) { return UnusedFunction(); }
    HRESULT _stdcall CreateCubeTexture(UINT a, UINT b, DWORD c, D3DFORMAT d, D3DPOOL e, IDirect3DCubeTexture8** f) { return UnusedFunction(); }

    HRESULT _stdcall CreateVertexBuffer(UINT a, DWORD b, DWORD c, D3DPOOL d, IDirect3DVertexBuffer8** e);
    HRESULT _stdcall CreateIndexBuffer(UINT a, DWORD b, D3DFORMAT c, D3DPOOL d, IDirect3DIndexBuffer8** e);
    HRESULT _stdcall CreateRenderTarget(UINT a, UINT b, D3DFORMAT c, D3DMULTISAMPLE_TYPE d, BOOL e, IDirect3DSurface8** f);
    HRESULT _stdcall CreateDepthStencilSurface(UINT a, UINT b, D3DFORMAT c, D3DMULTISAMPLE_TYPE d, IDirect3DSurface8** e);
    HRESULT _stdcall CreateImageSurface(UINT a, UINT b, D3DFORMAT c, IDirect3DSurface8** d);
    HRESULT _stdcall CopyRects(IDirect3DSurface8* a, const RECT* b, UINT c, IDirect3DSurface8* d, const POINT* e);

    HRESULT _stdcall UpdateTexture(IDirect3DBaseTexture8* a, IDirect3DBaseTexture8* b);
    HRESULT _stdcall GetFrontBuffer(IDirect3DSurface8* a) { return UnusedFunction(); }

    HRESULT _stdcall SetRenderTarget(IDirect3DSurface8* a, IDirect3DSurface8* b);
    HRESULT _stdcall GetRenderTarget(IDirect3DSurface8** a);
    HRESULT _stdcall GetDepthStencilSurface(IDirect3DSurface8** a);

    HRESULT _stdcall BeginScene();
    HRESULT _stdcall EndScene();
    HRESULT _stdcall Clear(DWORD a, const D3DRECT* b, DWORD c, D3DCOLOR d, float e, DWORD f);

    HRESULT _stdcall SetTransform(D3DTRANSFORMSTATETYPE a, const D3DMATRIX* b);
    HRESULT _stdcall GetTransform(D3DTRANSFORMSTATETYPE a, D3DMATRIX* b);
    HRESULT _stdcall MultiplyTransform(D3DTRANSFORMSTATETYPE a, const D3DMATRIX* b);
    HRESULT _stdcall SetViewport(const D3DVIEWPORT8* a);
    HRESULT _stdcall GetViewport(D3DVIEWPORT8* a);

    HRESULT _stdcall SetMaterial(const D3DMATERIAL8* a);
    HRESULT _stdcall GetMaterial(D3DMATERIAL8* a);
    HRESULT _stdcall SetLight(DWORD a, const D3DLIGHT8* b);
    HRESULT _stdcall GetLight(DWORD a, D3DLIGHT8* b);
    HRESULT _stdcall LightEnable(DWORD a, BOOL b);
    HRESULT _stdcall GetLightEnable(DWORD a, BOOL* b);

    HRESULT _stdcall SetClipPlane(DWORD a, const float* b);
    HRESULT _stdcall GetClipPlane(DWORD a, float* b);

    HRESULT _stdcall SetRenderState(D3DRENDERSTATETYPE a, DWORD b);
    HRESULT _stdcall GetRenderState(D3DRENDERSTATETYPE a, DWORD* b);

    HRESULT _stdcall BeginStateBlock(void) { return UnusedFunction(); }
    HRESULT _stdcall EndStateBlock(DWORD* a) { return UnusedFunction(); }
    HRESULT _stdcall ApplyStateBlock(DWORD a) { return UnusedFunction(); }
    HRESULT _stdcall CaptureStateBlock(DWORD a) { return UnusedFunction(); }
    HRESULT _stdcall DeleteStateBlock(DWORD a) { return UnusedFunction(); }
    HRESULT _stdcall CreateStateBlock(D3DSTATEBLOCKTYPE a, DWORD* b) { return UnusedFunction(); }

    HRESULT _stdcall SetClipStatus(const D3DCLIPSTATUS8* a) { return UnusedFunction(); }
    HRESULT _stdcall GetClipStatus(D3DCLIPSTATUS8* a) { return UnusedFunction(); }

    HRESULT _stdcall GetTexture(DWORD a, IDirect3DBaseTexture8** b) { return UnusedFunction(); }
    HRESULT _stdcall SetTexture(DWORD a, IDirect3DBaseTexture8* b);

    HRESULT _stdcall GetTextureStageState(DWORD a, D3DTEXTURESTAGESTATETYPE b, DWORD* c);
    HRESULT _stdcall SetTextureStageState(DWORD a, D3DTEXTURESTAGESTATETYPE b, DWORD c);

    HRESULT _stdcall ValidateDevice(DWORD* a);
    HRESULT _stdcall GetInfo(DWORD a, void* b, DWORD c) { return UnusedFunction(); }

    HRESULT _stdcall SetPaletteEntries(UINT a, const PALETTEENTRY* b);
    HRESULT _stdcall GetPaletteEntries(UINT a, PALETTEENTRY* b);

    HRESULT _stdcall SetCurrentTexturePalette(UINT a);
    HRESULT _stdcall GetCurrentTexturePalette(UINT* a);

    HRESULT _stdcall DrawPrimitive(D3DPRIMITIVETYPE a, UINT b, UINT c);
    HRESULT _stdcall DrawIndexedPrimitive(D3DPRIMITIVETYPE a, UINT b, UINT c, UINT d, UINT e);
    HRESULT _stdcall DrawPrimitiveUP(D3DPRIMITIVETYPE a, UINT b, const void* c, UINT d);
    HRESULT _stdcall DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE a, UINT b, UINT c, UINT d, const void* e, D3DFORMAT f, const void* g, UINT h);
    HRESULT _stdcall ProcessVertices(UINT a, UINT b, UINT c, IDirect3DVertexBuffer8* d, DWORD e);

    HRESULT _stdcall CreateVertexShader(const DWORD* a, const DWORD* b, DWORD* c, DWORD d) { return UnusedFunction(); }
    HRESULT _stdcall SetVertexShader(DWORD a);
    HRESULT _stdcall GetVertexShader(DWORD* a) { return UnusedFunction(); }
    HRESULT _stdcall DeleteVertexShader(DWORD a) { return UnusedFunction(); }

    HRESULT _stdcall SetVertexShaderConstant(DWORD a, const void* b, DWORD c) { return UnusedFunction(); }
    HRESULT _stdcall GetVertexShaderConstant(DWORD a, void* b, DWORD c) { return UnusedFunction(); }
    HRESULT _stdcall GetVertexShaderDeclaration(DWORD a, void* b, DWORD* c) { return UnusedFunction(); }
    HRESULT _stdcall GetVertexShaderFunction(DWORD a, void* b, DWORD* c) { return UnusedFunction(); }

    HRESULT _stdcall SetStreamSource(UINT a, IDirect3DVertexBuffer8* b, UINT c);
    HRESULT _stdcall GetStreamSource(UINT a, IDirect3DVertexBuffer8** b, UINT* c);
    HRESULT _stdcall SetIndices(IDirect3DIndexBuffer8* a, UINT b);
    HRESULT _stdcall GetIndices(IDirect3DIndexBuffer8** a, UINT* b);

    HRESULT _stdcall CreatePixelShader(const DWORD* a, DWORD* b) { return UnusedFunction(); }
    HRESULT _stdcall SetPixelShader(DWORD a) { return UnusedFunction(); }
    HRESULT _stdcall GetPixelShader(DWORD* a) { return UnusedFunction(); }
    HRESULT _stdcall DeletePixelShader(DWORD a) { return UnusedFunction(); }

    HRESULT _stdcall SetPixelShaderConstant(DWORD a, const void* b, DWORD c) { return UnusedFunction(); }
    HRESULT _stdcall GetPixelShaderConstant(DWORD a, void* b, DWORD c) { return UnusedFunction(); }
    HRESULT _stdcall GetPixelShaderFunction(DWORD a, void* b, DWORD* c) { return UnusedFunction(); }

    HRESULT _stdcall DrawRectPatch(UINT a, const float* b, const D3DRECTPATCH_INFO* c) { return UnusedFunction(); }
    HRESULT _stdcall DrawTriPatch(UINT a, const float* b, const D3DTRIPATCH_INFO* c) { return UnusedFunction(); }
    HRESULT _stdcall DeletePatch(UINT a) { return UnusedFunction(); }

    // Proxy methods
    virtual IDirect3DTexture8* factoryProxyTexture(IDirect3DTexture9* tex);
    virtual IDirect3DSurface8* factoryProxySurface(IDirect3DSurface9* surface);
};
