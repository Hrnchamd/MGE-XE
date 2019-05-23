
#include "statusoverlay.h"
#include "configuration.h"
#include "mged3d8device.h"

#include <cstdio>



char StatusOverlay::statusText[512];
char StatusOverlay::fpsText[16];
DWORD StatusOverlay::statusTimeout;

ID3DXFont* StatusOverlay::font;
RECT StatusOverlay::statusRect, StatusOverlay::fpsRect;



bool StatusOverlay::init(IDirect3DDevice9* device) {
    D3DXCreateFont(device, 12, 0, 400, 1, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                   DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Lucida Console", &font);

    statusRect.left=5;
    statusRect.right=635;
    statusRect.top=5;
    statusRect.bottom=20;
    fpsRect.left=5;
    fpsRect.right=160;
    fpsRect.top=25;
    fpsRect.bottom=40;

    return true;
}

void StatusOverlay::release() {
    font->Release();
}

void StatusOverlay::show(IDirect3DDevice9* device) {
    if (!(Configuration.MGEFlags & DISPLAY_MESSAGES)) {
        return;
    }

    if ((Configuration.MGEFlags & FPS_COUNTER) || statusTimeout) {
        if (Configuration.MGEFlags & FPS_COUNTER) {
            font->DrawTextA(NULL, fpsText, -1, &fpsRect, DT_NOCLIP, 0xffffffff);
        }

        if (statusText) {
            if (GetTickCount() < statusTimeout) {
                font->DrawTextA(NULL, statusText, -1, &statusRect, DT_NOCLIP, 0xffffffff);
            } else {
                statusTimeout = 0;
            }
        }
    }
}

void StatusOverlay::setStatus(const char* s) {
    std::snprintf(statusText, sizeof(statusText), "%s", s);
    statusTimeout = GetTickCount() + Configuration.StatusTimeout;
}

void StatusOverlay::setFPS(float fps) {
    std::snprintf(fpsText, sizeof(fpsText), "%4.0f", fps);
}

void StatusOverlay::showLastStatus() {
    statusTimeout = GetTickCount() + Configuration.StatusTimeout;
}
