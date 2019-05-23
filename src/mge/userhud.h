#pragma once

#include <string>



struct IDirect3DDevice9;
struct IDirect3DTexture9;
struct ID3DXEffect;

class MGEhud {
private:
    struct Element {
        bool enabled;
        float x, y, w, h;
        float xscale, yscale;
        IDirect3DTexture9* texture;
        ID3DXEffect* effect;
        std::string textureFilename, effectFilename;
    };

    static IDirect3DDevice9* device;
    static const int max_elements = 256;
    static Element elements[max_elements];

public:
    typedef int hud_id;
    static const hud_id invalid_hud_id = -1;

public:
    static bool init(IDirect3DDevice9* d);
    static void release();
    static void draw();
    static int getScreenWidth();
    static int getScreenHeight();

    static void reset();
    static void reload();
    static hud_id load(const char* name, const char* texture);
    static hud_id resolveName(const char* name);
    static void free(hud_id hud);
    static void enable(hud_id hud);
    static void disable(hud_id hud);
    static void setPosition(hud_id hud, float x, float y);
    static void setScale(hud_id hud, float xscale, float yscale);
    static void setFullscreen(hud_id hud);
    static void setTexture(hud_id hud, const char* texturePath);
    static void setEffect(hud_id hud, const char* effectPath);
    static void setEffectInt(hud_id hud, const char* varName, int x);
    static void setEffectFloat(hud_id hud, const char* varName, float x);
    static void setEffectVec4(hud_id hud, const char* varName, const float* v);
};
