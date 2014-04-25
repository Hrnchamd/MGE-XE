
#include <algorithm>
#include "mgedirect3d8.h"
#include "mged3d8device.h"
#include "configuration.h"
#include "support/log.h"

MGEProxyD3D::MGEProxyD3D(IDirect3D9 *real) : ProxyD3D(real, 120) // Morrowind requires D3D version 120
{
    // Force pixel shaders off, to simplify water override
    d3d8Caps.VertexShaderVersion = 0;
    d3d8Caps.PixelShaderVersion = 0;
}

HRESULT _stdcall MGEProxyD3D::CreateDevice(UINT a, D3DDEVTYPE b, HWND c, DWORD d, D3DPRESENT_PARAMETERS8 *e, IDirect3DDevice8 **f)
{
    LOG::logline(">> D3D Proxy CreateDevice");

    if(e->Windowed)
    {
        if(Configuration.Borderless)
        {
            // Remove non-client window parts and move window flush to screen edge / centre if smaller than display
            int wx = std::max(0, (GetSystemMetrics(SM_CXSCREEN) - (int)e->BackBufferWidth) / 2);
            int wy = std::max(0, (GetSystemMetrics(SM_CYSCREEN) - (int)e->BackBufferHeight) / 2);

            SetWindowLong(GetParent(c), GWL_STYLE, WS_VISIBLE);
            SetWindowPos(GetParent(c), NULL, wx, wy, e->BackBufferWidth, e->BackBufferHeight, SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
        }
        else
        {
            // Move window to top left corner
            SetWindowPos(GetParent(c), NULL, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
        }
    }

    // Map 16x antialiasing to equivalent CSAA
    D3DMULTISAMPLE_TYPE msaaSamples = (Configuration.AALevel == 16) ? D3DMULTISAMPLE_8_SAMPLES : (D3DMULTISAMPLE_TYPE)Configuration.AALevel;
    DWORD msaaQuality = (Configuration.AALevel == 16) ? 2 : 0;

    // Override device parameters
    // Note that Morrowind will look at the modified parameters
    if(e->Flags & D3DPRESENTFLAG_LOCKABLE_BACKBUFFER)
        e->Flags ^= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

    e->MultiSampleType = msaaSamples;
    e->AutoDepthStencilFormat = (D3DFORMAT)Configuration.ZBufFormat;
    e->FullScreen_RefreshRateInHz = (!e->Windowed) ? Configuration.RefreshRate : 0;
    e->FullScreen_PresentationInterval = (Configuration.VWait == 255) ? D3DPRESENT_INTERVAL_IMMEDIATE : Configuration.VWait;

    // Convert presentation parameters to DX9
    D3DPRESENT_PARAMETERS9 pp;

    pp.BackBufferWidth = e->BackBufferWidth;
    pp.BackBufferHeight = e->BackBufferHeight;
    pp.BackBufferFormat = e->BackBufferFormat;
    pp.BackBufferCount = e->BackBufferCount;
    pp.MultiSampleType = e->MultiSampleType;
    pp.MultiSampleQuality = msaaQuality;
    pp.SwapEffect = e->SwapEffect;
    pp.hDeviceWindow = e->hDeviceWindow;
    pp.Windowed = e->Windowed;
    pp.Flags = e->Flags;
    pp.EnableAutoDepthStencil = e->EnableAutoDepthStencil;
    pp.AutoDepthStencilFormat = e->AutoDepthStencilFormat;
    pp.FullScreen_RefreshRateInHz = e->FullScreen_RefreshRateInHz;
    pp.PresentationInterval = e->FullScreen_PresentationInterval;

    // Create device in the same manner as the proxy
    IDirect3DDevice9 *realDevice = NULL;
    HRESULT hr = realD3D->CreateDevice(a, b, c, d, &pp, &realDevice);

    if(hr != D3D_OK)
    {
        LOG::logline("!! D3D Proxy CreateDevice failure");
        return hr;
    }

    *f = factoryProxyDevice(realDevice);

    // Set up default render states
    Configuration.ScaleFilter = (Configuration.AnisoLevel > 0) ? D3DTEXF_ANISOTROPIC : D3DTEXF_LINEAR;
    Configuration.MipFilter = D3DTEXF_LINEAR;

    for(int i = 0; i != 4; ++i)
    {
        realDevice->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, Configuration.AnisoLevel);
        realDevice->SetSamplerState(i, D3DSAMP_MINFILTER, Configuration.ScaleFilter);
        realDevice->SetSamplerState(i, D3DSAMP_MIPMAPLODBIAS, *(DWORD *)&Configuration.LODBias);
    }

    // Set variables dependent on configuration
    DWORD FogPixelMode, FogVertexMode, RangedFog;
    if(Configuration.FogMode == 2)
    {
            FogVertexMode = D3DFOG_LINEAR;
            FogPixelMode = D3DFOG_NONE;
            RangedFog = 1;
    }
    else if(Configuration.FogMode == 1)
    {
            FogVertexMode = D3DFOG_LINEAR;
            FogPixelMode = D3DFOG_NONE;
            RangedFog = 0;
    }
    else
    {
            FogVertexMode = D3DFOG_NONE;
            FogPixelMode = D3DFOG_LINEAR;
            RangedFog = 0;
    }

    realDevice->SetRenderState(D3DRS_FOGVERTEXMODE, FogVertexMode);
    realDevice->SetRenderState(D3DRS_FOGTABLEMODE, FogPixelMode);
    realDevice->SetRenderState(D3DRS_RANGEFOGENABLE, RangedFog);
    realDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, (Configuration.AALevel > 0));

    LOG::logline("<< D3D Proxy CreateDevice");
    return D3D_OK;
}

IDirect3DDevice8* MGEProxyD3D::factoryProxyDevice(IDirect3DDevice9* d)
{
    LOG::logline("-- D3D Proxy Factory OK");
    return new MGEProxyDevice(d, this);
}
