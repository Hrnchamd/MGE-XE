
#include "mgedirect3d8.h"
#include "mged3d8device.h"
#include "configuration.h"
#include "support/log.h"

#include <algorithm>



static const UINT MorrowindRequiredD3DVersion = 120;

MGEProxyD3D::MGEProxyD3D(IDirect3D9* real) : ProxyD3D(real, MorrowindRequiredD3DVersion) {
    // Force pixel shaders off, to simplify water override
    d3d8Caps.VertexShaderVersion = 0;
    d3d8Caps.PixelShaderVersion = 0;

    // Log adapter details
    D3DADAPTER_IDENTIFIER9 adapter;
    realD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &adapter);
    LOG::logline("GPU: %s (%d.%d.%d.%d)", adapter.Description,
                 HIWORD(adapter.DriverVersion.HighPart), LOWORD(adapter.DriverVersion.HighPart),
                 HIWORD(adapter.DriverVersion.LowPart), LOWORD(adapter.DriverVersion.LowPart));
}

HRESULT _stdcall MGEProxyD3D::CreateDevice(UINT a, D3DDEVTYPE b, HWND c, DWORD d, D3DPRESENT_PARAMETERS8* e, IDirect3DDevice8** f) {
    // Window positioning
    if (e->Windowed) {
        HWND hMainWnd = GetParent(c);
        int wx = std::max(0, Configuration.WindowAlignX * (GetSystemMetrics(SM_CXSCREEN) - (int)e->BackBufferWidth) / 2);
        int wy = std::max(0, Configuration.WindowAlignY * (GetSystemMetrics(SM_CYSCREEN) - (int)e->BackBufferHeight) / 2);

        if (Configuration.Borderless) {
            // Remove non-client window parts and move window flush to screen edge / centre if smaller than display
            SetWindowLong(hMainWnd, GWL_STYLE, WS_VISIBLE);
            SetWindowPos(hMainWnd, NULL, wx, wy, e->BackBufferWidth, e->BackBufferHeight, SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
        } else {
            // Move window to top, with client area centred on one axis
            RECT rect = { wx, wy, int(e->BackBufferWidth), int(e->BackBufferHeight) };
            AdjustWindowRect(&rect, GetWindowLong(hMainWnd, GWL_STYLE), FALSE);
            SetWindowPos(hMainWnd, NULL, rect.left, 0, 0, 0, SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
        }

        // Ensure that the render window appears on the taskbar, as it is a child window that may become hidden
        LONG style = GetWindowLong(hMainWnd, GWL_EXSTYLE);
        SetWindowLong(hMainWnd, GWL_EXSTYLE, style | WS_EX_APPWINDOW);

        // Windowed mode does not allow multiple frame vsync
        if (Configuration.VWait >= D3DPRESENT_INTERVAL_TWO && Configuration.VWait <= D3DPRESENT_INTERVAL_FOUR) {
            Configuration.VWait = D3DPRESENT_INTERVAL_ONE;
            LOG::logline("VWait greater than one is not supported in windowed mode.");
        }
    }

    // MSAA parameters
    D3DMULTISAMPLE_TYPE msaaSamples = (D3DMULTISAMPLE_TYPE)Configuration.AALevel;
    DWORD msaaQuality = 0;

    // Override device parameters
    // Note that Morrowind will look at the modified parameters
    if (e->Flags & D3DPRESENTFLAG_LOCKABLE_BACKBUFFER) {
        e->Flags ^= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
    }

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
    IDirect3DDevice9* realDevice = NULL;
    HRESULT hr = realD3D->CreateDevice(a, b, c, d, &pp, &realDevice);

    if (hr != D3D_OK) {
        LOG::logline("!! D3D Proxy CreateDevice failure");
        LOG::flush();
        return hr;
    }

    *f = factoryProxyDevice(realDevice);

    // Set up default render states
    Configuration.ScaleFilter = (Configuration.AnisoLevel > 0) ? D3DTEXF_ANISOTROPIC : D3DTEXF_LINEAR;

    for (int i = 0; i != 8; ++i) {
        realDevice->SetSamplerState(i, D3DSAMP_MINFILTER, Configuration.ScaleFilter);
        realDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
        realDevice->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, Configuration.AnisoLevel);
    }

    // Set variables dependent on configuration
    DWORD FogPixelMode, FogVertexMode, RangedFog;
    if (Configuration.FogMode == 2) {
        FogVertexMode = D3DFOG_LINEAR;
        FogPixelMode = D3DFOG_NONE;
        RangedFog = 1;
    } else if (Configuration.FogMode == 1) {
        FogVertexMode = D3DFOG_LINEAR;
        FogPixelMode = D3DFOG_NONE;
        RangedFog = 0;
    } else {
        FogVertexMode = D3DFOG_NONE;
        FogPixelMode = D3DFOG_LINEAR;
        RangedFog = 0;
    }

    realDevice->SetRenderState(D3DRS_FOGVERTEXMODE, FogVertexMode);
    realDevice->SetRenderState(D3DRS_FOGTABLEMODE, FogPixelMode);
    realDevice->SetRenderState(D3DRS_RANGEFOGENABLE, RangedFog);
    realDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, (Configuration.AALevel > 0));

    LOG::logline("-- D3D Proxy Device OK");
    return D3D_OK;
}

IDirect3DDevice8* MGEProxyD3D::factoryProxyDevice(IDirect3DDevice9* d) {
    return new MGEProxyDevice(d, this);
}
