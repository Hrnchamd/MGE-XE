
#include "userhud.h"
#include "morrowindbsa.h"
#include "proxydx/d3d8header.h"
#include "support/log.h"

#include <cstdio>
#include <map>
#include <string>
#include <vector>



const DWORD fvfHUD = D3DFVF_XYZRHW | D3DFVF_TEX2;

static IDirect3DVertexBuffer9* vbHUD;
static ID3DXEffect* effectStandard;
static D3DVIEWPORT9 vp;

IDirect3DDevice9* MGEhud::device = 0;
MGEhud::Element MGEhud::elements[MGEhud::max_elements];

static std::vector<MGEhud::hud_id> elements_free;
static std::map<std::string, MGEhud::hud_id> element_names;



bool MGEhud::init(IDirect3DDevice9* d) {
    device = d;
    device->GetViewport(&vp);

    LOG::logline(">> HUD init");

    HRESULT hr = device->CreateVertexBuffer(max_elements * 4 * 32, D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY, fvfHUD, D3DPOOL_DEFAULT, &vbHUD, 0);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create HUD verts");
        return false;
    }

    ID3DXBuffer* errors;
    hr = D3DXCreateEffectFromFile(device, "Data Files\\shaders\\XE HUD.fx", 0, 0, D3DXFX_LARGEADDRESSAWARE, 0, &effectStandard, &errors);
    if (hr != D3D_OK) {
        LOG::logline("!! HUD Shader errors: %s", errors->GetBufferPointer());
        errors->Release();
        return false;
    }

    if (element_names.empty()) {
        reset();
    } else {
        reload();
    }

    LOG::logline("<< HUD init");
    return true;
}

void MGEhud::draw() {
    IDirect3DStateBlock9* stateSaved;
    device->CreateStateBlock(D3DSBT_ALL, &stateSaved);

    D3DXVECTOR4* vbase;
    HRESULT hr = vbHUD->Lock(0, 0, (void**)&vbase, D3DLOCK_DISCARD);
    if (hr != D3D_OK || vbase == 0) {
        return;
    }

    for (const auto& i : element_names) {
        const Element* e = &elements[i.second];

        if (e->enabled) {
            float x0 = e->x, x1 = e->x + e->xscale * e->w;
            float y0 = e->y, y1 = e->y + e->yscale * e->h;

            // Correct for D3D9 pixel offset
            x0 -= 0.5;
            y0 -= 0.5;
            x1 -= 0.5;
            y1 -= 0.5;

            D3DXVECTOR4* v = vbase + 8 * i.second;
            v[0] = D3DXVECTOR4(x0, y1, 0, 1);
            v[1] = D3DXVECTOR4(0, 1, 0, 0);
            v[2] = D3DXVECTOR4(x0, y0, 0, 1);
            v[3] = D3DXVECTOR4(0, 0, 0, 0);
            v[4] = D3DXVECTOR4(x1, y1, 0, 1);
            v[5] = D3DXVECTOR4(1, 1, 0, 0);
            v[6] = D3DXVECTOR4(x1, y0, 0, 1);
            v[7] = D3DXVECTOR4(1, 0, 0, 0);
        }
    }

    vbHUD->Unlock();

    device->SetFVF(fvfHUD);
    device->SetStreamSource(0, vbHUD, 0, 32);
    device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

    for (const auto& i : element_names) {
        const Element* e = &elements[i.second];

        if (e->enabled) {
            ID3DXEffect* effect = e->effect ? e->effect : effectStandard;
            D3DXHANDLE ehTex = effect->GetParameterByName(0, "tex");
            UINT passes;

            effect->SetTexture(ehTex, e->texture);
            effect->Begin(&passes, D3DXFX_DONOTSAVESTATE);
            effect->BeginPass(0);
            device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * i.second, 2);
            effect->EndPass();
            effect->End();
        }
    }

    stateSaved->Apply();
    stateSaved->Release();
}

void MGEhud::release() {
    LOG::logline(">> HUD release");

    // Only release D3D resources
    // HUD status must be remembered if the device restarts on alt-tab
    for (const auto& i : element_names) {
        Element* e = &elements[i.second];

        if (e->texture) {
            e->texture->Release();
        }

        if (e->effect) {
            e->effect->Release();
        }

        e->texture = 0;
        e->effect = 0;
    }

    effectStandard->Release();
    vbHUD->Release();

    LOG::logline("<< HUD release");
}

int MGEhud::getScreenWidth() {
    return vp.Width;
}

int MGEhud::getScreenHeight() {
    return vp.Height;
}

void MGEhud::reset() {
    for (auto& i : element_names) {
        MGEhud::free(i.second);
    }

    element_names.clear();
    elements_free.clear();

    for (int i = max_elements; i-- > 0; ) {
        elements_free.push_back(i);
    }
}

void MGEhud::reload() {
    LOG::logline("-- HUD reloading assets");

    for (auto& i : element_names) {
        hud_id hud = i.second;
        Element* e = &elements[hud];

        // Reload assets from source files
        // Copy filenames early, as the member variables are modified in the set functions
        std::string f = e->textureFilename;
        setTexture(hud, f.c_str());

        f = e->effectFilename;
        setEffect(hud, f.c_str());
    }
}

MGEhud::hud_id MGEhud::load(const char* name, const char* texture) {
    hud_id hud = resolveName(name);

    if (hud == MGEhud::invalid_hud_id) {
        hud = elements_free.back();
        elements_free.pop_back();
        element_names[name] = hud;
    }

    Element* e = &elements[hud];
    e->enabled = false;
    e->x = e->y = 0;
    e->xscale = e->yscale = 1.0;
    e->texture = 0;
    e->effect = 0;
    e->effectFilename.clear();

    setTexture(hud, texture);
    return hud;
}

MGEhud::hud_id MGEhud::resolveName(const char* name) {
    std::map<std::string, MGEhud::hud_id>::const_iterator i = element_names.find(name);
    if (i != element_names.end()) {
        return i->second;
    }

    return MGEhud::invalid_hud_id;
}

void MGEhud::free(hud_id hud) {
    Element* e = &elements[hud];

    if (e->texture) {
        e->texture->Release();
    }

    if (e->effect) {
        e->effect->Release();
    }

    e->enabled = false;
    e->texture = 0;
    e->textureFilename.clear();
    e->effect = 0;
    e->effectFilename.clear();
}

void MGEhud::enable(hud_id hud) {
    Element* e = &elements[hud];
    e->enabled = true;
}

void MGEhud::disable(hud_id hud) {
    Element* e = &elements[hud];
    e->enabled = false;
}

void MGEhud::setPosition(hud_id hud, float x, float y) {
    Element* e = &elements[hud];
    e->x = x;
    e->y = y;
}

void MGEhud::setScale(hud_id hud, float xscale, float yscale) {
    Element* e = &elements[hud];
    e->xscale = xscale;
    e->yscale = yscale;
}

void MGEhud::setFullscreen(hud_id hud) {
    Element* e = &elements[hud];

    e->x = e->y = 0;
    e->xscale = vp.Width / e->w;
    e->yscale = vp.Height / e->h;
}

void MGEhud::setTexture(hud_id hud, const char* texturePath) {
    Element* e = &elements[hud];

    if (e->texture) {
        e->texture->Release();
    }

    IDirect3DTexture9* tex = BSALoadTexture(device, texturePath);

    if (tex) {
        D3DSURFACE_DESC desc;
        tex->GetLevelDesc(0, &desc);

        e->w = float(desc.Width);
        e->h = float(desc.Height);
        e->texture = tex;

        // As the BSA cache cannot reload a texture after it is released, (it returns a pointer to the released texture)
        // we have to add a loose reference to keep the texture in memory and avoid a crash
        tex->AddRef();
        e->textureFilename = texturePath;
    } else {
        LOG::logline("LoadHUDTexture : Cannot load texture %s", texturePath);
        e->texture = 0;
        e->textureFilename.clear();
    }
}

void MGEhud::setEffect(hud_id hud, const char* effectPath) {
    Element* e = &elements[hud];
    char path[MAX_PATH];
    ID3DXBuffer* errors;

    // Clear current effect
    if (e->effect) {
        e->effect->Release();
    }

    e->effect = 0;
    e->effectFilename.clear();

    // Load new effect if string is not empty
    if (*effectPath) {
        std::snprintf(path, sizeof(path), "Data Files\\shaders\\%s.fx", effectPath);
        HRESULT hr = D3DXCreateEffectFromFile(device, path, 0, 0, D3DXFX_LARGEADDRESSAWARE, 0, &e->effect, &errors);

        if (hr == D3D_OK) {
            LOG::logline("-- HUD shader %s loaded", path);
            e->effectFilename = effectPath;
        } else {
            e->effect = 0;

            LOG::logline("!! HUD shader %s failed to load/compile", path);
            if (errors) {
                LOG::logline("!! Shader errors: %s", errors->GetBufferPointer());
                errors->Release();
            }
        }
    }
}

void MGEhud::setEffectInt(hud_id hud, const char* varName, int x) {
    ID3DXEffect* effect = elements[hud].effect;

    if (effect) {
        D3DXHANDLE ehVar = effect->GetParameterByName(0, varName);
        if (ehVar) {
            effect->SetInt(ehVar, x);
        }
    }
}

void MGEhud::setEffectFloat(hud_id hud, const char* varName, float x) {
    ID3DXEffect* effect = elements[hud].effect;

    if (effect) {
        D3DXHANDLE ehVar = effect->GetParameterByName(0, varName);
        if (ehVar) {
            effect->SetFloat(ehVar, x);
        }
    }
}

void MGEhud::setEffectVec4(hud_id hud, const char* varName, const float* v) {
    ID3DXEffect* effect = elements[hud].effect;

    if (effect) {
        D3DXHANDLE ehVar = effect->GetParameterByName(0, varName);
        if (ehVar) {
            effect->SetFloatArray(ehVar, v, 4);
        }
    }
}
