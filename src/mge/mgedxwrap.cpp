
#include "mgedirect3d8.h"
#include "support/log.h"



typedef IDirect3D9* (_stdcall* D3DProc9)(UINT);



void* CreateD3DWrapper(UINT version) {
    LOG::logline(">> CreateD3DWrapper");

    HMODULE d3ddll = LoadLibrary("d3d9.dll");
    D3DProc9 func9 = (D3DProc9)GetProcAddress(d3ddll, "Direct3DCreate9");
    LOG::logline("-- CreateD3DWrapper calling Direct3DCreate9");

    void* ret = new MGEProxyD3D((func9)(D3D_SDK_VERSION));
    LOG::logline("<< CreateD3DWrapper");
    return ret;
}
