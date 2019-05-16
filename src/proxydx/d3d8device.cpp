
#include "direct3d8.h"
#include "d3d8device.h"
#include "d3d8surface.h"
#include "d3d8texture.h"



ProxyDevice::ProxyDevice(IDirect3DDevice9* real, ProxyD3D* d3d) : refcount(1), realDevice(real), proxD3D8(d3d), baseVertexIndex(0) {
    GetGammaRamp(&gammaDefault);
}

//-----------------------------------------------------------------------------
/*** IUnknown methods ***/
//-----------------------------------------------------------------------------
HRESULT _stdcall ProxyDevice::QueryInterface(REFIID a, LPVOID* b) {
    return realDevice->QueryInterface(a, b);
}

ULONG _stdcall ProxyDevice::AddRef(void) {
    return ++refcount;
}

ULONG _stdcall ProxyDevice::Release(void) {
    if (--refcount == 0) {
        SetGammaRamp(0, &gammaDefault);
        realDevice->Release();
        return 0;
    }
    return refcount;
}

//-----------------------------------------------------------------------------
/*** IDirect3DDevice8 methods ***/
//-----------------------------------------------------------------------------
HRESULT _stdcall ProxyDevice::TestCooperativeLevel(void) {
    return realDevice->TestCooperativeLevel();
}
UINT _stdcall ProxyDevice::GetAvailableTextureMem(void) {
    return realDevice->GetAvailableTextureMem();
}
HRESULT _stdcall ProxyDevice::ResourceManagerDiscardBytes(DWORD a) {
    return D3D_OK;
}
HRESULT _stdcall ProxyDevice::GetDirect3D(IDirect3D8** a) {
    *a = proxD3D8;
    proxD3D8->AddRef();
    return D3D_OK;
}
HRESULT _stdcall ProxyDevice::GetDeviceCaps(D3DCAPS8* a) {
    return proxD3D8->GetDeviceCaps(0, D3DDEVTYPE_HAL, a);
}
HRESULT _stdcall ProxyDevice::GetDisplayMode(D3DDISPLAYMODE* a) {
    return realDevice->GetDisplayMode(0, a);
}
HRESULT _stdcall ProxyDevice::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* a) {
    return realDevice->GetCreationParameters(a);
}

HRESULT _stdcall ProxyDevice::SetCursorProperties(UINT a, UINT b, IDirect3DSurface8* c) {
    return 1;
}
void _stdcall ProxyDevice::SetCursorPosition(int X, int Y, DWORD c) { }
BOOL _stdcall ProxyDevice::ShowCursor(BOOL a) {
    return 1;
}

HRESULT _stdcall ProxyDevice::Present(const RECT* a, const RECT* b, HWND c, const RGNDATA* d) {
    return realDevice->Present(a, b, c, d);
}

HRESULT _stdcall ProxyDevice::GetBackBuffer(UINT a, D3DBACKBUFFER_TYPE b, IDirect3DSurface8** c) {
    IDirect3DSurface9* c_real = NULL;
    *c = NULL;

    HRESULT hr = realDevice->GetBackBuffer(0, a, b, &c_real);
    if (hr != D3D_OK || c_real == NULL) {
        return hr;
    }

    ProxySurface* surface = ProxySurface::getProxyFromDX(c_real);
    if (surface) {
        *c = surface;
    } else {
        *c = factoryProxySurface(c_real);
    }

    return D3D_OK;
}

HRESULT _stdcall ProxyDevice::GetRasterStatus(D3DRASTER_STATUS* a) {
    return realDevice->GetRasterStatus(0, a);
}

void _stdcall ProxyDevice::SetGammaRamp(DWORD a, const D3DGAMMARAMP* b) {
    IDirect3DSwapChain9* sc;
    D3DPRESENT_PARAMETERS pp;

    realDevice->GetSwapChain(0, &sc);
    sc->GetPresentParameters(&pp);
    sc->Release();

    if (pp.Windowed) {
        SetDeviceGammaRamp(GetDC(pp.hDeviceWindow), (void*)b);
    } else {
        realDevice->SetGammaRamp(0, a, b);
    }
}

void _stdcall ProxyDevice::GetGammaRamp(D3DGAMMARAMP* a) {
    IDirect3DSwapChain9* sc;
    D3DPRESENT_PARAMETERS pp;

    realDevice->GetSwapChain(0, &sc);
    sc->GetPresentParameters(&pp);
    sc->Release();

    if (pp.Windowed) {
        GetDeviceGammaRamp(GetDC(pp.hDeviceWindow), (void*)a);
    } else {
        realDevice->GetGammaRamp(0, a);
    }
}

HRESULT _stdcall ProxyDevice::CreateTexture(UINT a, UINT b, UINT c, DWORD d, D3DFORMAT e, D3DPOOL f, IDirect3DTexture8** g) {
    IDirect3DTexture9* g_real = NULL;
    HRESULT hr = realDevice->CreateTexture(a, b, c, d, e, f, &g_real, NULL);
    if (hr != D3D_OK || g_real == NULL) {
        return hr;
    }

    *g = factoryProxyTexture(g_real);
    return D3D_OK;
}

HRESULT _stdcall ProxyDevice::CreateVertexBuffer(UINT a, DWORD b, DWORD c, D3DPOOL d, IDirect3DVertexBuffer8** e) {
    return realDevice->CreateVertexBuffer(a, b, c, d, (IDirect3DVertexBuffer9**)e, NULL);
}

HRESULT _stdcall ProxyDevice::CreateIndexBuffer(UINT a, DWORD b, D3DFORMAT c, D3DPOOL d, IDirect3DIndexBuffer8** e) {
    return realDevice->CreateIndexBuffer(a, b, c, d, (IDirect3DIndexBuffer9**)e, NULL);
}

HRESULT _stdcall ProxyDevice::CreateRenderTarget(UINT a, UINT b, D3DFORMAT c, D3DMULTISAMPLE_TYPE d, BOOL e, IDirect3DSurface8** f) {
    IDirect3DSurface9* f_real = NULL;
    HRESULT hr = realDevice->CreateRenderTarget(a, b, c, d, 0, e, &f_real, NULL);
    if (hr != D3D_OK || f_real == NULL) {
        return hr;
    }

    *f = factoryProxySurface(f_real);
    return D3D_OK;
}

HRESULT _stdcall ProxyDevice::CreateDepthStencilSurface(UINT a, UINT b, D3DFORMAT c, D3DMULTISAMPLE_TYPE d, IDirect3DSurface8** e) {
    // Not sure if Discard should be true or false
    IDirect3DSurface9* e_real = NULL;
    HRESULT hr = realDevice->CreateDepthStencilSurface(a, b, c, d, 0, FALSE, &e_real, NULL);
    if (hr != D3D_OK) {
        return hr;
    }

    *e = factoryProxySurface(e_real);
    return D3D_OK;
}

HRESULT _stdcall ProxyDevice::CreateImageSurface(UINT a, UINT b, D3DFORMAT c, IDirect3DSurface8** d) {
    IDirect3DSurface9* d_real = NULL;
    HRESULT hr = realDevice->CreateOffscreenPlainSurface(a, b, c, D3DPOOL_SYSTEMMEM, &d_real, NULL);
    if (hr != D3D_OK || d_real == NULL) {
        return hr;
    }

    *d = factoryProxySurface(d_real);
    return D3D_OK;
}

HRESULT _stdcall ProxyDevice::CopyRects(IDirect3DSurface8* a, const RECT* b, UINT c, IDirect3DSurface8* d, const POINT* e) {
    IDirect3DSurface9* a_real = static_cast<ProxySurface*>(a)->realSurface;
    IDirect3DSurface9* d_real = static_cast<ProxySurface*>(d)->realSurface;

    if (b == NULL && e == NULL) {
        D3DSURFACE_DESC9 source;
        D3DSURFACE_DESC9 dest;

        if (a_real->GetDesc(&source) != D3D_OK || d_real->GetDesc(&dest) != D3D_OK) {
            return UnusedFunction();
        } else if (source.Usage == 1 && dest.Usage == 0) {
            return realDevice->GetRenderTargetData(a_real, d_real);
        } else if (source.Usage == 0 && dest.Usage == 1) {
            return realDevice->UpdateSurface(a_real, NULL, d_real, NULL);
        } else {
            return realDevice->StretchRect(a_real, NULL, d_real, NULL, D3DTEXF_NONE);
        }
    } else {
        // Really cant be bothered to get this working unless absolutely neccessery
    }

    return UnusedFunction();
}

HRESULT _stdcall ProxyDevice::UpdateTexture(IDirect3DBaseTexture8* a, IDirect3DBaseTexture8* b) {
    IDirect3DTexture9* a_real = static_cast<ProxyTexture*>(a)->realTexture;
    IDirect3DTexture9* b_real = static_cast<ProxyTexture*>(b)->realTexture;
    return realDevice->UpdateTexture(a_real, b_real);
}

HRESULT _stdcall ProxyDevice::SetRenderTarget(IDirect3DSurface8* a, IDirect3DSurface8* b) {
    IDirect3DSurface9* a_real = NULL;
    IDirect3DSurface9* b_real = NULL;
    if (a != NULL) {
        a_real = static_cast<ProxySurface*>(a)->realSurface;
    }
    if (b != NULL) {
        b_real = static_cast<ProxySurface*>(b)->realSurface;
    }

    HRESULT hr1 = D3D_OK, hr2 = D3D_OK;
    if (a_real != NULL) {
        hr1 = realDevice->SetRenderTarget(0, a_real);
    }
    hr2 = realDevice->SetDepthStencilSurface(b_real);

    return (hr1 != D3D_OK) ? hr1 : hr2;
}

HRESULT _stdcall ProxyDevice::GetRenderTarget(IDirect3DSurface8** a) {
    IDirect3DSurface9* a_real = NULL;
    *a = NULL;

    HRESULT hr = realDevice->GetRenderTarget(0, &a_real);
    if (hr != D3D_OK || a_real == NULL) {
        return hr;
    }

    ProxySurface* surface = ProxySurface::getProxyFromDX(a_real);
    if (surface) {
        *a = surface;
    } else {
        *a = factoryProxySurface(a_real);
    }

    return D3D_OK;
}

HRESULT _stdcall ProxyDevice::GetDepthStencilSurface(IDirect3DSurface8** a) {
    IDirect3DSurface9* a_real = NULL;
    *a = NULL;

    HRESULT hr = realDevice->GetDepthStencilSurface(&a_real);
    if (hr != D3D_OK || a_real == NULL) {
        return hr;
    }

    ProxySurface* surface = ProxySurface::getProxyFromDX(a_real);
    if (surface) {
        *a = surface;
    } else {
        *a = factoryProxySurface(a_real);
    }

    return D3D_OK;
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyDevice::BeginScene() {
    return realDevice->BeginScene();
}

HRESULT _stdcall ProxyDevice::EndScene() {
    return realDevice->EndScene();
}

HRESULT _stdcall ProxyDevice::Clear(DWORD a, const D3DRECT* b, DWORD c, D3DCOLOR d, float e, DWORD f) {
    return realDevice->Clear(a, b, c, d, e, f);
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyDevice::SetTransform(D3DTRANSFORMSTATETYPE a, const D3DMATRIX* b) {
    return realDevice->SetTransform(a, b);
}
HRESULT _stdcall ProxyDevice::GetTransform(D3DTRANSFORMSTATETYPE a, D3DMATRIX* b) {
    return realDevice->GetTransform(a, b);
}
HRESULT _stdcall ProxyDevice::MultiplyTransform(D3DTRANSFORMSTATETYPE a, const D3DMATRIX* b) {
    return realDevice->MultiplyTransform(a, b);
}
HRESULT _stdcall ProxyDevice::SetViewport(const D3DVIEWPORT8* a) {
    return realDevice->SetViewport(a);
}
HRESULT _stdcall ProxyDevice::GetViewport(D3DVIEWPORT8* a) {
    return realDevice->GetViewport(a);
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyDevice::SetMaterial(const D3DMATERIAL8* a) {
    return realDevice->SetMaterial(a);
}
HRESULT _stdcall ProxyDevice::GetMaterial(D3DMATERIAL8* a) {
    return realDevice->GetMaterial(a);
}
HRESULT _stdcall ProxyDevice::SetLight(DWORD a, const D3DLIGHT8* b) {
    return realDevice->SetLight(a, b);
}
HRESULT _stdcall ProxyDevice::GetLight(DWORD a, D3DLIGHT8* b) {
    return realDevice->GetLight(a, b);
}
HRESULT _stdcall ProxyDevice::LightEnable(DWORD a, BOOL b) {
    return realDevice->LightEnable(a, b);
}
HRESULT _stdcall ProxyDevice::GetLightEnable(DWORD a, BOOL* b) {
    return realDevice->GetLightEnable(a, b);
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyDevice::SetClipPlane(DWORD a, const float* b) {
    return realDevice->SetClipPlane(a, b);
}
HRESULT _stdcall ProxyDevice::GetClipPlane(DWORD a, float* b) {
    return realDevice->GetClipPlane(a, b);
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyDevice::SetRenderState(D3DRENDERSTATETYPE a, DWORD b) {
    return realDevice->SetRenderState(a, b);
}

HRESULT _stdcall ProxyDevice::GetRenderState(D3DRENDERSTATETYPE a, DWORD* b) {
    return realDevice->GetRenderState(a, b);
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyDevice::SetTexture(DWORD a, IDirect3DBaseTexture8* b) {
    IDirect3DTexture9* currentTexture = (b != NULL) ? static_cast<ProxyTexture*>(b)->realTexture : NULL;
    return realDevice->SetTexture(a, currentTexture);
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyDevice::GetTextureStageState(DWORD a, D3DTEXTURESTAGESTATETYPE b, DWORD* c) {
    D3DSAMPLERSTATETYPE sampler;
    switch (b) {
    case D3DTSS_ADDRESSU:
        sampler = D3DSAMP_ADDRESSU;
        break;
    case D3DTSS_ADDRESSV:
        sampler = D3DSAMP_ADDRESSV;
        break;
    case D3DTSS_BORDERCOLOR:
        sampler = D3DSAMP_BORDERCOLOR;
        break;
    case D3DTSS_MAGFILTER:
        sampler = D3DSAMP_MAGFILTER;
        break;
    case D3DTSS_MINFILTER:
        sampler = D3DSAMP_MINFILTER;
        break;
    case D3DTSS_MIPFILTER:
        sampler = D3DSAMP_MIPFILTER;
        break;
    case D3DTSS_MIPMAPLODBIAS:
        sampler = D3DSAMP_MIPMAPLODBIAS;
        break;
    case D3DTSS_MAXMIPLEVEL:
        sampler = D3DSAMP_MAXMIPLEVEL;
        break;
    case D3DTSS_MAXANISOTROPY:
        sampler = D3DSAMP_MAXANISOTROPY;
        break;
    case D3DTSS_ADDRESSW:
        sampler = D3DSAMP_ADDRESSW;
        break;
    default:
        return realDevice->GetTextureStageState(a, b, c);
    }
    return realDevice->GetSamplerState(a, sampler, c);
}

HRESULT _stdcall ProxyDevice::SetTextureStageState(DWORD a, D3DTEXTURESTAGESTATETYPE b, DWORD c) {
    D3DSAMPLERSTATETYPE sampler;
    switch (b) {
    case D3DTSS_ADDRESSU:
        sampler = D3DSAMP_ADDRESSU;
        break;
    case D3DTSS_ADDRESSV:
        sampler = D3DSAMP_ADDRESSV;
        break;
    case D3DTSS_BORDERCOLOR:
        sampler = D3DSAMP_BORDERCOLOR;
        break;
    case D3DTSS_MAGFILTER:
        sampler = D3DSAMP_MAGFILTER;
        break;
    case D3DTSS_MINFILTER:
        sampler = D3DSAMP_MINFILTER;
        break;
    case D3DTSS_MIPFILTER:
        sampler = D3DSAMP_MIPFILTER;
        break;
    case D3DTSS_MIPMAPLODBIAS:
        sampler = D3DSAMP_MIPMAPLODBIAS;
        break;
    case D3DTSS_MAXMIPLEVEL:
        sampler = D3DSAMP_MAXMIPLEVEL;
        break;
    case D3DTSS_MAXANISOTROPY:
        sampler = D3DSAMP_MAXANISOTROPY;
        break;
    case D3DTSS_ADDRESSW:
        sampler = D3DSAMP_ADDRESSW;
        break;
    default:
        return realDevice->SetTextureStageState(a, b, c);
    }
    return realDevice->SetSamplerState(a, sampler, c);
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyDevice::ValidateDevice(DWORD* a) {
    return realDevice->ValidateDevice(a);
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyDevice::SetPaletteEntries(UINT a, const PALETTEENTRY* b) {
    return realDevice->SetPaletteEntries(a, b);
}
HRESULT _stdcall ProxyDevice::GetPaletteEntries(UINT a, PALETTEENTRY* b) {
    return realDevice->GetPaletteEntries(a, b);
}
HRESULT _stdcall ProxyDevice::SetCurrentTexturePalette(UINT a) {
    return realDevice->SetCurrentTexturePalette(a);
}
HRESULT _stdcall ProxyDevice::GetCurrentTexturePalette(UINT* a) {
    return realDevice->GetCurrentTexturePalette(a);
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyDevice::DrawPrimitive(D3DPRIMITIVETYPE a, UINT b, UINT c) {
    return realDevice->DrawPrimitive(a, b, c);
}

HRESULT _stdcall ProxyDevice::DrawIndexedPrimitive(D3DPRIMITIVETYPE a, UINT b, UINT c, UINT d, UINT e) {
    return realDevice->DrawIndexedPrimitive(a, (INT)baseVertexIndex, b, c, d, e);
}

HRESULT _stdcall ProxyDevice::DrawPrimitiveUP(D3DPRIMITIVETYPE a, UINT b, const void* c, UINT d) {
    return realDevice->DrawPrimitiveUP(a, b, c, d);
}

HRESULT _stdcall ProxyDevice::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE a, UINT b, UINT c, UINT d, const void* e, D3DFORMAT f, const void* g, UINT h) {
    return realDevice->DrawIndexedPrimitiveUP(a, b, c, d, e, f, g, h);
}

HRESULT _stdcall ProxyDevice::ProcessVertices(UINT a, UINT b, UINT c, IDirect3DVertexBuffer8* d, DWORD e) {
    return realDevice->ProcessVertices(a, b, c, (IDirect3DVertexBuffer9*)d, NULL, e);
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyDevice::SetVertexShader(DWORD a) {
    return realDevice->SetFVF(a);
}

//-----------------------------------------------------------------------------

HRESULT _stdcall ProxyDevice::SetStreamSource(UINT a, IDirect3DVertexBuffer8* b, UINT c) {
    return realDevice->SetStreamSource(a, (IDirect3DVertexBuffer9*)b, 0, c);
}

HRESULT _stdcall ProxyDevice::GetStreamSource(UINT a, IDirect3DVertexBuffer8** b, UINT* c) {
    UINT unused;
    return realDevice->GetStreamSource(a, (IDirect3DVertexBuffer9**)b, &unused, c);
}

HRESULT _stdcall ProxyDevice::SetIndices(IDirect3DIndexBuffer8* a, UINT b) {
    baseVertexIndex = b;
    return realDevice->SetIndices((IDirect3DIndexBuffer9*)a);
}

HRESULT _stdcall ProxyDevice::GetIndices(IDirect3DIndexBuffer8** a, UINT* b) {
    *b = baseVertexIndex;
    return realDevice->GetIndices((IDirect3DIndexBuffer9**)a);
}

//-----------------------------------------------------------------------------

// Proxy methods
IDirect3DTexture8* ProxyDevice::factoryProxyTexture(IDirect3DTexture9* tex) {
    return new ProxyTexture(tex, this);
}

IDirect3DSurface8* ProxyDevice::factoryProxySurface(IDirect3DSurface9* surface) {
    return new ProxySurface(surface, this);
}
