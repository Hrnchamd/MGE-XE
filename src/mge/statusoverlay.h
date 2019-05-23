#pragma once

#include "proxydx/d3d9header.h"



class StatusOverlay {
    static char statusText[512];
    static char fpsText[16];
    static DWORD statusTimeout;

    static ID3DXFont* font;
    static RECT statusRect, fpsRect;

public:
    static bool init(IDirect3DDevice9* device);
    static void release();
    static void show(IDirect3DDevice9* device);
    static void setStatus(const char* s);
    static void setFPS(float fps);
    static void showLastStatus();
};
