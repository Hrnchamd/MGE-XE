
#include "mge/mwinitpatch.h"
#include "mge/configuration.h"
#include "mge/mwbridge.h"
#include "support/timing.h"
#include <algorithm>

struct TES3GameOptions {
    void *vtbl;
    const char *registryKey;
    int windowWidth;
    int windowHeight;
    int screenDepth;
    int backBuffers;
    int multiSamples;
    char fullscreen;
    // ...
};

// Override UI scaling callback: set new UI scaling and mouse bounds, setup borderless window
static void _stdcall onUIScaleInit() {
    auto mwBridge = MWBridge::get();
    auto hMainWnd = mwBridge->getWindowHandle();
    auto gameOptions = (TES3GameOptions*)mwBridge->getGameOptionsStruct();

    // Setup borderless window, if selected
    if (!gameOptions->fullscreen && Configuration.Borderless) {
        int wx = std::max(0, Configuration.WindowAlignX * (GetSystemMetrics(SM_CXSCREEN) - gameOptions->windowWidth) / 2);
        int wy = std::max(0, Configuration.WindowAlignY * (GetSystemMetrics(SM_CYSCREEN) - gameOptions->windowHeight) / 2);

        // Remove non-client window parts and move window flush to screen edge / centre if smaller than display
        SetWindowLong(hMainWnd, GWL_STYLE, WS_VISIBLE);
        SetWindowPos(hMainWnd, NULL, wx, wy, gameOptions->windowWidth, gameOptions->windowHeight, SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
    }

    mwBridge->setUIScale(Configuration.UIScale);
}

void MWInitPatch::patch() {
    auto mwBridge = MWBridge::get();

    if ((Configuration.MGEFlags & MGE_DISABLED) || Configuration.OnlyProxyD3D8To9) {
        // User interface still needs to be scaled, normally done by the D3DDevice proxy
        // Without the proxy, patch Morrowind UI creation instead
        mwBridge->patchUIConfigure(onUIScaleInit);
    }

    if (Configuration.MGEFlags & SKIP_INTRO) {
        // Disable intro movies on initialization as the logo appears before game init
        mwBridge->disableIntroMovies();
    }

    if (Configuration.UseDefaultTexturePool) {
        // Patch texture loading to reduce process memory footprint
        mwBridge->patchLoadTexture2D();
    }

    // Patches certain calls to timeGetTime to redirect to a better time.
    HighResolutionTimer::init();
    mwBridge->patchFrameTimer(&HighResolutionTimer::getMilliseconds);

    // Patch engine issue with light emissive particle material that affects particle rendering
    mwBridge->patchLightParticleMaterialModifier();
}
