
#include "mge/mwinitpatch.h"
#include "mge/configuration.h"
#include "mge/mwbridge.h"
#include "support/timing.h"

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

// Disable intro movies on initialization as the logo appears before game init
void MWInitPatch::disableIntroMovies() {
    MWBridge::get()->disableIntroMovies();
}


// Patch texture loading to reduce process memory footprint
void MWInitPatch::patchTextureLoading() {
    MWBridge::get()->patchLoadTexture2D();
}


// Override UI scaling callback: set new UI scaling and mouse bounds, setup borderless window
static void _stdcall onUIScaleInit() {
    auto mwBridge = MWBridge::get();
    auto hMainWnd = mwBridge->getWindowHandle();
    auto gameOptions = (TES3GameOptions*)mwBridge->getGameOptionsStruct();

    // Setup borderless window, if selected
    if (!gameOptions->fullscreen && Configuration.Borderless) {
        int wx = std::max(0, (GetSystemMetrics(SM_CXSCREEN) - gameOptions->windowWidth) / 2);
        int wy = std::max(0, (GetSystemMetrics(SM_CYSCREEN) - gameOptions->windowHeight) / 2);

        // Remove non-client window parts and move window flush to screen edge / centre if smaller than display
        SetWindowLong(hMainWnd, GWL_STYLE, WS_VISIBLE);
        SetWindowPos(hMainWnd, NULL, wx, wy, gameOptions->windowWidth, gameOptions->windowHeight, SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
    }

    mwBridge->setUIScale(Configuration.UIScale);
}

void MWInitPatch::patchUIInit() {
    // User interface still needs to be scaled, normally done by the D3DDevice proxy
    // Without the proxy, patch Morrowind UI creation instead
    MWBridge::get()->patchUIConfigure(onUIScaleInit);
}


// Patches certain calls to timeGetTime to redirect to a better time.
void MWInitPatch::patchFrameTimer() {
    HighResolutionTimer::init();
    MWBridge::get()->patchFrameTimer(&HighResolutionTimer::getMilliseconds);
}
