#pragma once

struct IDirect3DDevice9;
struct IDirect3DTexture9;


namespace BSA {
    void init();
    IDirect3DTexture9* loadTexture(IDirect3DDevice9* dev, const char* filename);
    void clearTextureCache();
    void cacheStats(int* total, int* memuse);
}
