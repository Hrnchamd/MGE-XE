#pragma once

#include "proxydx/d3d9header.h"



struct Bink;

class VideoBackground {
    Bink* video;
    IDirect3DSurface9* surface;

public:
    VideoBackground() : video(0), surface(0) {}

    bool begin(IDirect3DDevice9* device);
    void render(IDirect3DDevice9* device);
    void end();
};

class VideoPatch {
    static IDirect3DDevice9* d;
    static VideoBackground v;
    static int state;

public:
    static void monitor(IDirect3DDevice9* device);
    static void _stdcall patch(int x);
};
