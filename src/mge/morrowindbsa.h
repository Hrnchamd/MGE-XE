#pragma once

struct IDirect3DDevice9;
struct IDirect3DTexture9;


void BSAInit();
IDirect3DTexture9* BSALoadTexture(IDirect3DDevice9* dev, const char* filename);
void BSAClearTextureCache();
void BSACacheStats(int* total, int* memuse);
