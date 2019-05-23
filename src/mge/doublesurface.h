#pragma once

#include "proxydx/d3d9header.h"

#include <algorithm>



class SurfaceDoubleBuffer {
    int i;
    IDirect3DTexture9* t[2];
    IDirect3DSurface9* s[2];

public:
    void init(IDirect3DTexture9* textures[2], IDirect3DSurface9* surfaces[2]) {
        i = 0;
        t[0] = textures[0];
        t[1] = textures[1];
        s[0] = surfaces[0];
        s[1] = surfaces[1];
    }
    void init(IDirect3DTexture9* srcT, IDirect3DSurface9* srcS, IDirect3DTexture9* sinkT, IDirect3DSurface9* sinkS) {
        i = 0;
        t[0] = srcT;
        t[1] = sinkT;
        s[0] = srcS;
        s[1] = sinkS;
    }

    IDirect3DTexture9* sourceTexture() {
        return t[i];
    }
    IDirect3DSurface9* sourceSurface() {
        return s[i];
    }

    IDirect3DTexture9* sinkTexture() {
        return t[1 - i];
    }
    IDirect3DSurface9* sinkSurface() {
        return s[1 - i];
    }

    void cycle() {
        i = 1 - i;
    }
    void select(int _i) {
        i = _i;
    }

    void exchangeSource(IDirect3DTexture9** pptex, IDirect3DSurface9** ppsurf) {
        std::swap(t[i], *pptex);
        std::swap(s[i], *ppsurf);
    }
};
