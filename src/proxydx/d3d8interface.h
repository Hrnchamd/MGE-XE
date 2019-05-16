#pragma once

#include "d3d8header.h"

#define UnusedFunction() D3DERR_INVALIDCALL

// DX8 interface declarations
DECLARE_INTERFACE_(IDirect3DSurface8, IUnknown) {
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)() PURE;
    STDMETHOD_(ULONG,Release)() PURE;

    /*** IDirect3DSurface8 methods ***/
    STDMETHOD(GetDevice)(IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(REFGUID refguid) PURE;
    STDMETHOD(GetContainer)(REFIID riid,void** ppContainer) PURE;
    STDMETHOD(GetDesc)(D3DSURFACE_DESC8 *pDesc) PURE;
    STDMETHOD(LockRect)(D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) PURE;
    STDMETHOD(UnlockRect)() PURE;
};

DECLARE_INTERFACE_(IDirect3DTexture8, IUnknown) {
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)() PURE;
    STDMETHOD_(ULONG,Release)() PURE;

    /*** IDirect3DBaseTexture8 methods ***/
    STDMETHOD(GetDevice)(IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)() PURE;
    STDMETHOD_(void, PreLoad)() PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)() PURE;
    STDMETHOD_(DWORD, SetLOD)(DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)() PURE;
    STDMETHOD_(DWORD, GetLevelCount)() PURE;
    STDMETHOD(GetLevelDesc)(UINT Level,D3DSURFACE_DESC8 *pDesc) PURE;
    STDMETHOD(GetSurfaceLevel)(UINT Level,IDirect3DSurface8** ppSurfaceLevel) PURE;
    STDMETHOD(LockRect)(UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) PURE;
    STDMETHOD(UnlockRect)(UINT Level) PURE;
    STDMETHOD(AddDirtyRect)(CONST RECT* pDirtyRect) PURE;
};

DECLARE_INTERFACE_(IDirect3DDevice8, IUnknown) {
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)() PURE;
    STDMETHOD_(ULONG,Release)() PURE;

    /*** IDirect3DDevice8 methods ***/
    STDMETHOD(TestCooperativeLevel)() PURE;
    STDMETHOD_(UINT, GetAvailableTextureMem)() PURE;
    STDMETHOD(ResourceManagerDiscardBytes)(DWORD Bytes) PURE;
    STDMETHOD(GetDirect3D)(IDirect3D8** ppD3D8) PURE;
    STDMETHOD(GetDeviceCaps)(D3DCAPS8* pCaps) PURE;
    STDMETHOD(GetDisplayMode)(D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(GetCreationParameters)(D3DDEVICE_CREATION_PARAMETERS *pParameters) PURE;
    STDMETHOD(SetCursorProperties)(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface8* pCursorBitmap) PURE;
    STDMETHOD_(void, SetCursorPosition)(int X,int Y,DWORD Flags) PURE;
    STDMETHOD_(BOOL, ShowCursor)(BOOL bShow) PURE;
    STDMETHOD(CreateAdditionalSwapChain)(D3DPRESENT_PARAMETERS8* pPresentationParameters,IDirect3DSwapChain8** pSwapChain) PURE;
    STDMETHOD(Reset)(D3DPRESENT_PARAMETERS8* pPresentationParameters) PURE;
    STDMETHOD(Present)(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) PURE;
    STDMETHOD(GetBackBuffer)(UINT BackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface8** ppBackBuffer) PURE;
    STDMETHOD(GetRasterStatus)(D3DRASTER_STATUS* pRasterStatus) PURE;
    STDMETHOD_(void, SetGammaRamp)(DWORD Flags,CONST D3DGAMMARAMP* pRamp) PURE;
    STDMETHOD_(void, GetGammaRamp)(D3DGAMMARAMP* pRamp) PURE;
    STDMETHOD(CreateTexture)(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture8** ppTexture) PURE;
    STDMETHOD(CreateVolumeTexture)(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture8** ppVolumeTexture) PURE;
    STDMETHOD(CreateCubeTexture)(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture8** ppCubeTexture) PURE;
    STDMETHOD(CreateVertexBuffer)(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer8** ppVertexBuffer) PURE;
    STDMETHOD(CreateIndexBuffer)(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer8** ppIndexBuffer) PURE;
    STDMETHOD(CreateRenderTarget)(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,BOOL Lockable,IDirect3DSurface8** ppSurface) PURE;
    STDMETHOD(CreateDepthStencilSurface)(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,IDirect3DSurface8** ppSurface) PURE;
    STDMETHOD(CreateImageSurface)(UINT Width,UINT Height,D3DFORMAT Format,IDirect3DSurface8** ppSurface) PURE;
    STDMETHOD(CopyRects)(IDirect3DSurface8* pSourceSurface,CONST RECT* pSourceRectsArray,UINT cRects,IDirect3DSurface8* pDestinationSurface,CONST POINT* pDestPointsArray) PURE;
    STDMETHOD(UpdateTexture)(IDirect3DBaseTexture8* pSourceTexture,IDirect3DBaseTexture8* pDestinationTexture) PURE;
    STDMETHOD(GetFrontBuffer)(IDirect3DSurface8* pDestSurface) PURE;
    STDMETHOD(SetRenderTarget)(IDirect3DSurface8* pRenderTarget,IDirect3DSurface8* pNewZStencil) PURE;
    STDMETHOD(GetRenderTarget)(IDirect3DSurface8** ppRenderTarget) PURE;
    STDMETHOD(GetDepthStencilSurface)(IDirect3DSurface8** ppZStencilSurface) PURE;
    STDMETHOD(BeginScene)() PURE;
    STDMETHOD(EndScene)() PURE;
    STDMETHOD(Clear)(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil) PURE;
    STDMETHOD(SetTransform)(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) PURE;
    STDMETHOD(GetTransform)(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix) PURE;
    STDMETHOD(MultiplyTransform)(D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*) PURE;
    STDMETHOD(SetViewport)(CONST D3DVIEWPORT9* pViewport) PURE;
    STDMETHOD(GetViewport)(D3DVIEWPORT9* pViewport) PURE;
    STDMETHOD(SetMaterial)(CONST D3DMATERIAL9* pMaterial) PURE;
    STDMETHOD(GetMaterial)(D3DMATERIAL9* pMaterial) PURE;
    STDMETHOD(SetLight)(DWORD Index,CONST D3DLIGHT9*) PURE;
    STDMETHOD(GetLight)(DWORD Index,D3DLIGHT9*) PURE;
    STDMETHOD(LightEnable)(DWORD Index,BOOL Enable) PURE;
    STDMETHOD(GetLightEnable)(DWORD Index,BOOL* pEnable) PURE;
    STDMETHOD(SetClipPlane)(DWORD Index,CONST float* pPlane) PURE;
    STDMETHOD(GetClipPlane)(DWORD Index,float* pPlane) PURE;
    STDMETHOD(SetRenderState)(D3DRENDERSTATETYPE State,DWORD Value) PURE;
    STDMETHOD(GetRenderState)(D3DRENDERSTATETYPE State,DWORD* pValue) PURE;
    STDMETHOD(BeginStateBlock)() PURE;
    STDMETHOD(EndStateBlock)(DWORD* pToken) PURE;
    STDMETHOD(ApplyStateBlock)(DWORD Token) PURE;
    STDMETHOD(CaptureStateBlock)(DWORD Token) PURE;
    STDMETHOD(DeleteStateBlock)(DWORD Token) PURE;
    STDMETHOD(CreateStateBlock)(D3DSTATEBLOCKTYPE Type,DWORD* pToken) PURE;
    STDMETHOD(SetClipStatus)(CONST D3DCLIPSTATUS9* pClipStatus) PURE;
    STDMETHOD(GetClipStatus)(D3DCLIPSTATUS9* pClipStatus) PURE;
    STDMETHOD(GetTexture)(DWORD Stage,IDirect3DBaseTexture8** ppTexture) PURE;
    STDMETHOD(SetTexture)(DWORD Stage,IDirect3DBaseTexture8* pTexture) PURE;
    STDMETHOD(GetTextureStageState)(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue) PURE;
    STDMETHOD(SetTextureStageState)(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value) PURE;
    STDMETHOD(ValidateDevice)(DWORD* pNumPasses) PURE;
    STDMETHOD(GetInfo)(DWORD DevInfoID,void* pDevInfoStruct,DWORD DevInfoStructSize) PURE;
    STDMETHOD(SetPaletteEntries)(UINT PaletteNumber,CONST PALETTEENTRY* pEntries) PURE;
    STDMETHOD(GetPaletteEntries)(UINT PaletteNumber,PALETTEENTRY* pEntries) PURE;
    STDMETHOD(SetCurrentTexturePalette)(UINT PaletteNumber) PURE;
    STDMETHOD(GetCurrentTexturePalette)(UINT *PaletteNumber) PURE;
    STDMETHOD(DrawPrimitive)(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount) PURE;
    STDMETHOD(DrawIndexedPrimitive)(D3DPRIMITIVETYPE,UINT minIndex,UINT NumVertices,UINT startIndex,UINT primCount) PURE;
    STDMETHOD(DrawPrimitiveUP)(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) PURE;
    STDMETHOD(DrawIndexedPrimitiveUP)(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertexIndices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) PURE;
    STDMETHOD(ProcessVertices)(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer8* pDestBuffer,DWORD Flags) PURE;
    STDMETHOD(CreateVertexShader)(CONST DWORD* pDeclaration,CONST DWORD* pFunction,DWORD* pHandle,DWORD Usage) PURE;
    STDMETHOD(SetVertexShader)(DWORD Handle) PURE;
    STDMETHOD(GetVertexShader)(DWORD* pHandle) PURE;
    STDMETHOD(DeleteVertexShader)(DWORD Handle) PURE;
    STDMETHOD(SetVertexShaderConstant)(DWORD Register,CONST void* pConstantData,DWORD ConstantCount) PURE;
    STDMETHOD(GetVertexShaderConstant)(DWORD Register,void* pConstantData,DWORD ConstantCount) PURE;
    STDMETHOD(GetVertexShaderDeclaration)(DWORD Handle,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(GetVertexShaderFunction)(DWORD Handle,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(SetStreamSource)(UINT StreamNumber,IDirect3DVertexBuffer8* pStreamData,UINT Stride) PURE;
    STDMETHOD(GetStreamSource)(UINT StreamNumber,IDirect3DVertexBuffer8** ppStreamData,UINT* pStride) PURE;
    STDMETHOD(SetIndices)(IDirect3DIndexBuffer8* pIndexData,UINT BaseVertexIndex) PURE;
    STDMETHOD(GetIndices)(IDirect3DIndexBuffer8** ppIndexData,UINT* pBaseVertexIndex) PURE;
    STDMETHOD(CreatePixelShader)(CONST DWORD* pFunction,DWORD* pHandle) PURE;
    STDMETHOD(SetPixelShader)(DWORD Handle) PURE;
    STDMETHOD(GetPixelShader)(DWORD* pHandle) PURE;
    STDMETHOD(DeletePixelShader)(DWORD Handle) PURE;
    STDMETHOD(SetPixelShaderConstant)(DWORD Register,CONST void* pConstantData,DWORD ConstantCount) PURE;
    STDMETHOD(GetPixelShaderConstant)(DWORD Register,void* pConstantData,DWORD ConstantCount) PURE;
    STDMETHOD(GetPixelShaderFunction)(DWORD Handle,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(DrawRectPatch)(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo) PURE;
    STDMETHOD(DrawTriPatch)(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo) PURE;
    STDMETHOD(DeletePatch)(UINT Handle) PURE;
};

DECLARE_INTERFACE_(IDirect3D8, IUnknown) {
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)() PURE;
    STDMETHOD_(ULONG,Release)() PURE;

    /*** IDirect3D8 methods ***/
    STDMETHOD(RegisterSoftwareDevice)(void* pInitializeFunction) PURE;
    STDMETHOD_(UINT, GetAdapterCount)() PURE;
    STDMETHOD(GetAdapterIdentifier)(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER8* pIdentifier) PURE;
    STDMETHOD_(UINT, GetAdapterModeCount)(UINT Adapter) PURE;
    STDMETHOD(EnumAdapterModes)(UINT Adapter,UINT Mode,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(GetAdapterDisplayMode)(UINT Adapter,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(CheckDeviceType)(UINT Adapter,D3DDEVTYPE CheckType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL Windowed) PURE;
    STDMETHOD(CheckDeviceFormat)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat) PURE;
    STDMETHOD(CheckDeviceMultiSampleType)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType) PURE;
    STDMETHOD(CheckDepthStencilMatch)(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) PURE;
    STDMETHOD(GetDeviceCaps)(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS8* pCaps) PURE;
    STDMETHOD_(HMONITOR, GetAdapterMonitor)(UINT Adapter) PURE;
    STDMETHOD(CreateDevice)(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS8* pPresentationParameters,IDirect3DDevice8** ppReturnedDeviceInterface) PURE;
};

static const GUID guid_proxydx =
{ 0x7c204fb1, 0x9cac, 0x4b8d, { 0xba, 0xed, 0x7b, 0xf4, 0x8b, 0xf6, 0x3b, 0xb2 } };

class ProxySurface;
class ProxyTexture;
class ProxyDevice;
class ProxyD3D;
