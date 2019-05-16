#pragma once

#include "d3d9header.h"

// Direct3D8 definitions (since SDK includes are DX9)

#define IDirect3DIndexBuffer8 void
#define IDirect3DVertexBuffer8 void
#define IDirect3DSwapChain8 void
#define IDirect3DBaseTexture8 IDirect3DTexture8
#define IDirect3DVolumeTexture8 void
#define IDirect3DCubeTexture8 void

#define D3DSURFACE_DESC9 D3DSURFACE_DESC
#define D3DPRESENT_PARAMETERS9 D3DPRESENT_PARAMETERS

interface IDirect3D8;
interface IDirect3DDevice8;
interface IDirect3DTexture8;
interface IDirect3DSurface8;

// DX8 D3DTEXTURESTAGESTATETYPE enum
#define D3DTSS_ADDRESSU       13
#define D3DTSS_ADDRESSV       14
#define D3DTSS_BORDERCOLOR    15
#define D3DTSS_MAGFILTER      16
#define D3DTSS_MINFILTER      17
#define D3DTSS_MIPFILTER      18
#define D3DTSS_MIPMAPLODBIAS  19
#define D3DTSS_MAXMIPLEVEL    20
#define D3DTSS_MAXANISOTROPY  21
#define D3DTSS_ADDRESSW       25

// DX8 structs
typedef struct _D3DADAPTER_IDENTIFIER8 {
    char            Driver[MAX_DEVICE_IDENTIFIER_STRING];
    char            Description[MAX_DEVICE_IDENTIFIER_STRING];

    LARGE_INTEGER   DriverVersion;

    DWORD           VendorId;
    DWORD           DeviceId;
    DWORD           SubSysId;
    DWORD           Revision;

    GUID            DeviceIdentifier;

    DWORD           WHQLLevel;

} D3DADAPTER_IDENTIFIER8;

typedef struct _D3DPRESENT_PARAMETERS8 {
    UINT                BackBufferWidth;
    UINT                BackBufferHeight;
    D3DFORMAT           BackBufferFormat;
    UINT                BackBufferCount;

    D3DMULTISAMPLE_TYPE MultiSampleType;

    D3DSWAPEFFECT       SwapEffect;
    HWND                hDeviceWindow;
    BOOL                Windowed;
    BOOL                EnableAutoDepthStencil;
    D3DFORMAT           AutoDepthStencilFormat;
    DWORD               Flags;

    /* Following elements must be zero for Windowed mode */
    UINT                FullScreen_RefreshRateInHz;
    UINT                FullScreen_PresentationInterval;

} D3DPRESENT_PARAMETERS8;

typedef struct _D3DSURFACE_DESC8 {
    D3DFORMAT           Format;
    D3DRESOURCETYPE     Type;
    DWORD               Usage;
    D3DPOOL             Pool;
    UINT                Size;

    D3DMULTISAMPLE_TYPE MultiSampleType;
    UINT                Width;
    UINT                Height;
} D3DSURFACE_DESC8;

typedef IDirect3DVertexBuffer9 IDirect3DVertexBuffer;
typedef IDirect3DIndexBuffer9 IDirect3DIndexBuffer;
typedef IDirect3DSurface9 IDirect3DSurface;
typedef IDirect3DTexture9 IDirect3DTexture;
typedef IDirect3D9 IDirect3D;
typedef IDirect3DDevice9 IDirect3DDevice;
typedef D3DLIGHT9 D3DLIGHT8;
typedef D3DMATERIAL9 D3DMATERIAL8;
typedef D3DVIEWPORT9 D3DVIEWPORT8;
typedef D3DCLIPSTATUS9 D3DCLIPSTATUS8;

typedef struct RGBVECTOR {
public:
    RGBVECTOR() {}
    RGBVECTOR( DWORD rgb );
    RGBVECTOR( CONST FLOAT*);
    RGBVECTOR( CONST D3DXFLOAT16*);
    RGBVECTOR( CONST RGBVECTOR*);
    RGBVECTOR( CONST RGBVECTOR&);
    RGBVECTOR( CONST D3DCOLORVALUE&);
    RGBVECTOR( CONST D3DXCOLOR&);
    RGBVECTOR( FLOAT r, FLOAT g, FLOAT b );

    // casting
    operator DWORD () const;

    operator FLOAT* ();
    operator CONST FLOAT* () const;

    // assignment operators
    RGBVECTOR& operator += (CONST RGBVECTOR&);
    RGBVECTOR& operator -= (CONST RGBVECTOR&);
    RGBVECTOR& operator += (CONST D3DXCOLOR&);
    RGBVECTOR& operator -= (CONST D3DXCOLOR&);
    RGBVECTOR& operator *= (FLOAT);
    RGBVECTOR& operator /= (FLOAT);

    // unary operators
    RGBVECTOR operator + () const;
    RGBVECTOR operator - () const;

    // binary operators
    RGBVECTOR operator + (CONST RGBVECTOR&) const;
    RGBVECTOR operator - (CONST RGBVECTOR&) const;
    RGBVECTOR operator + (CONST D3DXCOLOR&) const;
    RGBVECTOR operator - (CONST D3DXCOLOR&) const;
    RGBVECTOR operator * (FLOAT) const;
    RGBVECTOR operator / (FLOAT) const;

    friend RGBVECTOR operator * (FLOAT, CONST RGBVECTOR&);

    BOOL operator == (CONST RGBVECTOR&) const;
    BOOL operator != (CONST RGBVECTOR&) const;
    BOOL operator == (CONST D3DXCOLOR&) const;
    BOOL operator != (CONST D3DXCOLOR&) const;

    FLOAT r, g, b;
} RGBVECTOR, *LPRGBVECTOR;

// RGBVECTOR method definitions
#include "d3d8header.inl"

typedef struct _D3DCAPS8 {
    /* Device Info */
    D3DDEVTYPE  DeviceType;
    UINT    AdapterOrdinal;

    /* Caps from DX7 Draw */
    DWORD   Caps;
    DWORD   Caps2;
    DWORD   Caps3;
    DWORD   PresentationIntervals;

    /* Cursor Caps */
    DWORD   CursorCaps;

    /* 3D Device Caps */
    DWORD   DevCaps;

    DWORD   PrimitiveMiscCaps;
    DWORD   RasterCaps;
    DWORD   ZCmpCaps;
    DWORD   SrcBlendCaps;
    DWORD   DestBlendCaps;
    DWORD   AlphaCmpCaps;
    DWORD   ShadeCaps;
    DWORD   TextureCaps;
    DWORD   TextureFilterCaps;          // D3DPTFILTERCAPS for IDirect3DTexture8's
    DWORD   CubeTextureFilterCaps;      // D3DPTFILTERCAPS for IDirect3DCubeTexture8's
    DWORD   VolumeTextureFilterCaps;    // D3DPTFILTERCAPS for IDirect3DVolumeTexture8's
    DWORD   TextureAddressCaps;         // D3DPTADDRESSCAPS for IDirect3DTexture8's
    DWORD   VolumeTextureAddressCaps;   // D3DPTADDRESSCAPS for IDirect3DVolumeTexture8's

    DWORD   LineCaps;                   // D3DLINECAPS

    DWORD   MaxTextureWidth, MaxTextureHeight;
    DWORD   MaxVolumeExtent;

    DWORD   MaxTextureRepeat;
    DWORD   MaxTextureAspectRatio;
    DWORD   MaxAnisotropy;
    float   MaxVertexW;

    float   GuardBandLeft;
    float   GuardBandTop;
    float   GuardBandRight;
    float   GuardBandBottom;

    float   ExtentsAdjust;
    DWORD   StencilCaps;

    DWORD   FVFCaps;
    DWORD   TextureOpCaps;
    DWORD   MaxTextureBlendStages;
    DWORD   MaxSimultaneousTextures;

    DWORD   VertexProcessingCaps;
    DWORD   MaxActiveLights;
    DWORD   MaxUserClipPlanes;
    DWORD   MaxVertexBlendMatrices;
    DWORD   MaxVertexBlendMatrixIndex;

    float   MaxPointSize;

    DWORD   MaxPrimitiveCount;          // max number of primitives per DrawPrimitive call
    DWORD   MaxVertexIndex;
    DWORD   MaxStreams;
    DWORD   MaxStreamStride;            // max stride for SetStreamSource

    DWORD   VertexShaderVersion;
    DWORD   MaxVertexShaderConst;       // number of vertex shader constant registers

    DWORD   PixelShaderVersion;
    float   MaxPixelShaderValue;        // max value of pixel shader arithmetic component

} D3DCAPS8;
