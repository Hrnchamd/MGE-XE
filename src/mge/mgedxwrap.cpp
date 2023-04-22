
#include "mgedirect3d8.h"
#include "mge/configuration.h"
#include "support/log.h"


typedef IDirect3D9* (_stdcall* D3DProc9)(UINT);



static const UINT MorrowindRequiredD3DVersion = 120;

void* CreateD3DWrapper(UINT version) {
    HMODULE d3ddll = LoadLibrary("d3d9.dll");
    D3DProc9 func9 = (D3DProc9)GetProcAddress(d3ddll, "Direct3DCreate9");

    IDirect3D9* d3d = func9(D3D_SDK_VERSION);
    if (!Configuration.OnlyProxyD3D8To9) {
        return new MGEProxyD3D(d3d);
    }
    else {
        LOG::logline(">> Using D3D8To9 proxy mode");
        return new ProxyD3D(d3d, MorrowindRequiredD3DVersion);
    }
}
