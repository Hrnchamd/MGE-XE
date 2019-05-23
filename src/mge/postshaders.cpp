
#include "proxydx/d3d8header.h"
#include "support/log.h"
#include "configuration.h"
#include "mwbridge.h"
#include "postshaders.h"

#include <algorithm>
#include <cstdio>
#include <cstring>



// Must match enum EffectVariableID in postshaders.h
const char* effectVariableList[] = {
    "lastshader", "lastpass", "depthframe", "watertexture",
    "eyevec", "eyepos", "sunvec", "suncol", "sunamb", "sunpos", "sunvis", "HDR",
    "mview", "mproj", "fogcol", "fogstart", "fogrange", "fognearstart", "fognearrange",
    "rcpres", "fov", "time", "waterlevel", "isInterior", "isUnderwater"
};

const int effectVariableCount = sizeof(effectVariableList) / sizeof(const char*);
const char* compatibleShader = "MGE XE 0";

const DWORD fvfPost = D3DFVF_XYZRHW | D3DFVF_TEX2;  // XYZRHW -> skips vertex shader
const DWORD fvfBlend = D3DFVF_XYZW | D3DFVF_TEX2;

IDirect3DDevice9* PostShaders::device;
std::vector<MGEShader> PostShaders::shaders;
std::vector<D3DXMACRO> PostShaders::features;
IDirect3DTexture9* PostShaders::texLastShader;
IDirect3DSurface9* PostShaders::surfaceLastShader;
SurfaceDoubleBuffer PostShaders::doublebuffer;
IDirect3DVertexBuffer9* PostShaders::vbPost;
IDirect3DSurface9* PostShaders::surfReadqueue, *PostShaders::surfReadback;
D3DXVECTOR4 PostShaders::adaptPoint;
float PostShaders::rcpRes[2];



// init - Initialize post-processing shader system
bool PostShaders::init(IDirect3DDevice9* realDevice) {
    LOG::logline(">> Post Process shader init");
    device = realDevice;

    if (!initBuffers()) {
        return false;
    }

    if (!initShaderChain()) {
        return false;
    }

    LOG::logline("<< Post Process shader init");
    return true;
}

static const D3DXMACRO macroExpFog = { "USE_EXPFOG", "" };
static const D3DXMACRO macroTerminator = { 0, 0 };

// initShaderChain - Load and prepare all shaders, ignoring invalid shaders
bool PostShaders::initShaderChain() {
    char path[MAX_PATH];

    // Set shader defines corresponding to required features
    if (Configuration.MGEFlags & EXP_FOG) {
        features.push_back(macroExpFog);
    }
    features.push_back(macroTerminator);

    for (const char* p = Configuration.ShaderChain; *p;  p += strlen(p) + 1) {
        WIN32_FILE_ATTRIBUTE_DATA fileAttrs;
        MGEShader shader;
        ID3DXBuffer* errors;

        std::snprintf(path, sizeof(path), "Data Files\\shaders\\XEshaders\\%s.fx", p);
        if (!GetFileAttributesEx(path, GetFileExInfoStandard, &fileAttrs)) {
            LOG::logline("!! Post shader %s missing", path);
            continue;
        }

        HRESULT hr = D3DXCreateEffectFromFile(device, path, &*features.begin(), 0, D3DXFX_LARGEADDRESSAWARE, 0, &shader.effect, &errors);

        if (hr == D3D_OK) {
            if (checkShaderVersion(&shader)) {
                shader.name = p;
                shader.timestamp = fileAttrs.ftLastWriteTime.dwLowDateTime;
                shader.enabled = true;

                initShader(&shader);
                loadShaderDependencies(&shader);
                shaders.push_back(shader);
                LOG::logline("-- Post shader %s loaded", path);
            } else {
                shader.effect->Release();
                LOG::logline("## Post shader %s is not version compatible, not loaded", path);
            }
        } else {
            LOG::logline("!! Post shader %s failed to load/compile", path);
            if (errors) {
                LOG::logline("!! Shader errors: %s", errors->GetBufferPointer());
                errors->Release();
            }
        }
    }

    LOG::logline("-- Shader chain indicates HDR %s", (Configuration.MGEFlags & USE_HDR) ? "On" : "Off");

    if (Configuration.MGEFlags & NO_MW_SUNGLARE) {
        MWBridge::get()->disableSunglare();
        LOG::logline("-- Shader chain replaces standard Morrowind sun glare");
    }

    return true;
}

// updateShaderChain
// Reloads shaders that have changed
bool PostShaders::updateShaderChain() {
    char path[MAX_PATH];
    bool updated = false;

    for (auto& s : shaders) {
        WIN32_FILE_ATTRIBUTE_DATA fileAttrs;
        ID3DXEffect* effect;
        ID3DXBuffer* errors;

        std::snprintf(path, sizeof(path), "Data Files\\shaders\\XEshaders\\%s.fx", s.name.c_str());
        if (!GetFileAttributesEx(path, GetFileExInfoStandard, &fileAttrs)) {
            continue;
        }

        if (s.timestamp != fileAttrs.ftLastWriteTime.dwLowDateTime) {
            HRESULT hr = D3DXCreateEffectFromFile(device, path, &*features.begin(), 0, D3DXFX_LARGEADDRESSAWARE, 0, &effect, &errors);

            if (hr == D3D_OK) {
                s.effect->Release();
                s.effect = effect;
                s.timestamp = fileAttrs.ftLastWriteTime.dwLowDateTime;

                initShader(&s);
                loadShaderDependencies(&s);
                LOG::logline("-- Post shader %s reloaded", path);
                updated = true;
            } else {
                LOG::logline("!! Post shader %s failed to load/compile", path);
                if (errors) {
                    LOG::logline("!! Shader errors: %s", errors->GetBufferPointer());
                    errors->Release();
                }
            }
        }
    }

    return updated;
}

// checkShaderVersion
// Checks effect annotation to see if the shader was designed for MGE XE,
// as MGE shaders use an incompatible set of variables
bool PostShaders::checkShaderVersion(MGEShader* shader) {
    ID3DXEffect* effect = shader->effect;
    D3DXHANDLE tech, ver;
    const char* verstr;

    tech = effect->GetTechnique(0);
    if (tech == 0) {
        return false;
    }

    ver = effect->GetAnnotationByName(tech, "MGEinterface");
    if (ver == 0) {
        return false;
    }

    if (effect->GetString(ver, &verstr) == D3D_OK) {
        if (std::strcmp(verstr, compatibleShader) == 0) {
            return true;
        }
    }
    return false;
}

// initShader - Binds standard game environment variables
void PostShaders::initShader(MGEShader* shader) {
    ID3DXEffect* effect = shader->effect;
    D3DXHANDLE tech, hdr, glare;

    // Variable handles
    for (int i = 0; i != effectVariableCount; ++i) {
        shader->ehVars[i] = effect->GetParameterByName(0, effectVariableList[i]);
    }

    // Read environment activation flags
    shader->disableFlags = 0;
    D3DXHANDLE ehMGEflags = effect->GetParameterByName(0, "mgeflags");
    if (ehMGEflags) {
        effect->GetInt(ehMGEflags, &shader->disableFlags);
    }

    // Read feature flags
    tech = effect->GetTechnique(0);
    hdr = effect->GetAnnotationByName(tech, "requiresHDR");
    if (hdr) {
        Configuration.MGEFlags |= USE_HDR;
    }
    glare = effect->GetAnnotationByName(tech, "disableSunglare");
    if (glare) {
        Configuration.MGEFlags |= NO_MW_SUNGLARE;
    }

    // Constants
    shader->SetFloatArray(EV_rcpres, rcpRes, 2);
}

// loadShaderDependencies - Loads textures referenced inside a shader
void PostShaders::loadShaderDependencies(MGEShader* shader) {
    ID3DXEffect* effect = shader->effect;
    char texturepath[MAX_PATH];
    const char* texturesrc;

    for (UINT i = 0; true; ++i) {
        D3DXHANDLE ehTextureRef = effect->GetParameter(0, i);
        if (ehTextureRef == 0) {
            break;
        }

        D3DXHANDLE ehTextureSrc = effect->GetAnnotationByName(ehTextureRef, "src");
        if (ehTextureSrc == 0) {
            continue;
        }

        if (effect->GetString(ehTextureSrc, &texturesrc) == D3D_OK) {
            IDirect3DTexture9* tex;
            std::snprintf(texturepath, sizeof(texturepath), "Data Files\\textures\\%s", texturesrc);

            if (D3DXCreateTextureFromFile(device, texturepath, &tex) == D3D_OK) {
                effect->SetTexture(ehTextureRef, tex);
            } else {
                LOG::logline("!! Post shader %s failed to load texture %s", shader->name.c_str(), texturepath);
            }
        }
    }
}

// initBuffers - Create ping-pong buffers and HDR resolve surfaces
bool PostShaders::initBuffers() {
    // Check view dimensions
    D3DVIEWPORT9 vp;
    device->GetViewport(&vp);

    // Shaders need to know rcpres
    rcpRes[0] = 1.0f / vp.Width;
    rcpRes[1] = 1.0f / vp.Height;

    // Set up texture buffers
    IDirect3DTexture9* texDoubleBuffer[2];
    UINT w = vp.Width, h = vp.Height;
    HRESULT hr;

    hr = device->CreateTexture(w, h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texLastShader, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create post-process render target");
        return false;
    }
    hr = device->CreateTexture(w, h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texDoubleBuffer[0], NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create post-process render target");
        return false;
    }
    hr = device->CreateTexture(w, h, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texDoubleBuffer[1], NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create post-process render target");
        return false;
    }

    // Buffering setup
    IDirect3DSurface9* surfaceDoubleBuffer[2];

    texLastShader->GetSurfaceLevel(0, &surfaceLastShader);
    texDoubleBuffer[0]->GetSurfaceLevel(0, &surfaceDoubleBuffer[0]);
    texDoubleBuffer[1]->GetSurfaceLevel(0, &surfaceDoubleBuffer[1]);
    doublebuffer.init(texDoubleBuffer, surfaceDoubleBuffer);

    // Skip vertex shader with post-transform vertex buffer
    hr = device->CreateVertexBuffer(4 * 32, 0, 0, D3DPOOL_MANAGED, &vbPost, 0);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create post-process verts");
        return false;
    }

    // Format: Post-transform position, texture xy, normalized device xy
    D3DXVECTOR4* v;
    vbPost->Lock(0, 0, (void**)&v, 0);
    v[0] = D3DXVECTOR4(-0.5f, h - 0.5f, 0.0f, 1.0f);
    v[1] = D3DXVECTOR4(0, 1, -1, -1);
    v[2] = D3DXVECTOR4(-0.5f, -0.5f, 0.0f, 1.0f);
    v[3] = D3DXVECTOR4(0, 0, -1, 1);
    v[4] = D3DXVECTOR4(w - 0.5f, h - 0.5f, 0.0f, 1.0f);
    v[5] = D3DXVECTOR4(1, 1, 1, -1);
    v[6] = D3DXVECTOR4(w - 0.5f, -0.5f, 0.0f, 1.0f);
    v[7] = D3DXVECTOR4(1, 0, 1, 1);
    vbPost->Unlock();

    // HDR readback system
    hr = device->CreateRenderTarget(1, 1, D3DFMT_A8R8G8B8, D3DMULTISAMPLE_NONE, 0, false, &surfReadqueue, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create HDR surface queue");
        return false;
    }
    hr = device->CreateOffscreenPlainSurface(1, 1, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &surfReadback, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create HDR surface queue");
        return false;
    }
    adaptPoint = D3DXVECTOR4(1.0, 1.0, 1.0, 1.0);

    return true;
}

// release - Cleans up Direct3D resources
void PostShaders::release() {
    for (auto& s : shaders) {
        s.effect->Release();
    }
    shaders.clear();

    surfaceLastShader->Release();
    texLastShader->Release();
    doublebuffer.sourceSurface()->Release();
    doublebuffer.sourceTexture()->Release();
    doublebuffer.sinkSurface()->Release();
    doublebuffer.sinkTexture()->Release();
    vbPost->Release();
    surfReadqueue->Release();
    surfReadback->Release();
}

// evalAdaptHDR - Downsample and readback a frame to get an averaged luminance for HDR
void PostShaders::evalAdaptHDR(IDirect3DSurface9* source, int environmentFlags, float dt) {
    D3DLOCKED_RECT lock;
    RECT rectSrc = { 0, 0, 0, 0 };
    RECT rectDownsample = { 0, 0, 0, 0 };
    float r, g, b;

    // Read resolved data from last frame
    surfReadback->LockRect(&lock, NULL, D3DLOCK_READONLY);
    BYTE* data = (BYTE*)lock.pBits;
    r = data[0] / 255.0f;
    g = data[1] / 255.0f;
    b = data[2] / 255.0f;
    surfReadback->UnlockRect();

    // Convert to environment-weighted luminance and average over time
    // x = normalized weighted lumi, y = unweighted lumi, z = unnormalized weighted lumi, w = immediate unweighted lumi
    float environmentScaling = (environmentFlags & 6) ? 2.5f : 1.0f;
    float lambda = exp(-dt / Configuration.HDRReactionSpeed);
    adaptPoint.w = 0.27f*r + 0.67f*g + 0.06f*b;
    adaptPoint.z = adaptPoint.w * environmentScaling + (adaptPoint.z - adaptPoint.w * environmentScaling) * lambda;
    adaptPoint.y = adaptPoint.w + (adaptPoint.y - adaptPoint.w) * lambda;
    adaptPoint.x = adaptPoint.z / environmentScaling;

    // Shrink this frame down to a 1x1 texture
    rectDownsample.right = 512;
    rectDownsample.bottom = 512;
    device->StretchRect(source, 0, doublebuffer.sinkSurface(), &rectDownsample, D3DTEXF_LINEAR);
    doublebuffer.cycle();

    while (rectDownsample.right > 1 || rectDownsample.bottom > 1) {
        rectSrc = rectDownsample;
        rectDownsample.right = std::max(1L, rectSrc.right >> 1);
        rectDownsample.bottom = std::max(1L, rectSrc.bottom >> 1);
        device->StretchRect(doublebuffer.sourceSurface(), &rectSrc, doublebuffer.sinkSurface(), &rectDownsample, D3DTEXF_LINEAR);
        doublebuffer.cycle();
    }

    // Copy and queue readback
    device->StretchRect(doublebuffer.sourceSurface(), &rectDownsample, surfReadqueue, 0, D3DTEXF_NONE);
    device->GetRenderTargetData(surfReadqueue, surfReadback);
}

// shaderTime - Applies all post processing shaders for the current frame
void PostShaders::shaderTime(MGEShaderUpdateFunc updateVarsFunc, int environmentFlags, float frameTime) {
    IDirect3DSurface9* backbuffer, *depthstencil;

    // Turn off depth stencil use
    device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
    device->GetDepthStencilSurface(&depthstencil);
    device->SetDepthStencilSurface(NULL);

    // Turn off useless states
    device->SetRenderState(D3DRS_ZENABLE, 0);
    device->SetRenderState(D3DRS_ZWRITEENABLE, 0);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
    device->SetRenderState(D3DRS_ALPHATESTENABLE, 0);

    // Make sure fogging is off, drivers are not consistent in applying fog to post-transform vertices
    device->SetRenderState(D3DRS_FOGENABLE, 0);

    // Bypass texgen and texture matrix for compatibility with WINE
    // Normally texgen does not run on post-transform vertices, but WINE incorrectly does this
    D3DXMATRIX ident;
    D3DXMatrixIdentity(&ident);
    device->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
    device->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
    device->SetTransform(D3DTS_TEXTURE0, &ident);
    device->SetTransform(D3DTS_TEXTURE1, &ident);

    // Resolve back buffer to lastshader surface
    device->StretchRect(backbuffer, 0, surfaceLastShader, 0, D3DTEXF_NONE);

    // Set vertex buffer
    device->SetFVF(fvfPost);
    device->SetStreamSource(0, vbPost, 0, 32);
    device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // Evaluate HDR if required
    if (Configuration.MGEFlags & USE_HDR) {
        evalAdaptHDR(surfaceLastShader, environmentFlags, frameTime);
    }

    // Render all those shaders
    for (auto& s : shaders) {
        ID3DXEffect* effect = s.effect;
        UINT passes;

        if (!s.enabled) {
            continue;
        }
        if (s.disableFlags & environmentFlags) {
            continue;
        }

        updateVarsFunc(&s);
        s.SetFloatArray(EV_HDR, adaptPoint, 4);
        s.SetTexture(EV_lastshader, texLastShader);
        effect->Begin(&passes, 0);

        for (UINT p = 0; p != passes; ++p) {
            device->SetRenderTarget(0, doublebuffer.sinkSurface());
            s.SetTexture(EV_lastpass, doublebuffer.sourceTexture());

            effect->BeginPass(p);
            device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
            effect->EndPass();

            doublebuffer.cycle();
        }

        effect->End();

        // Avoid another copy by exchanging which surfaces are buffers
        doublebuffer.exchangeSource(&texLastShader, &surfaceLastShader);
    }

    // Copy result to back buffer
    device->StretchRect(surfaceLastShader, 0, backbuffer, 0, D3DTEXF_NONE);

    // Restore render target
    device->SetRenderTarget(0, backbuffer);
    device->SetDepthStencilSurface(depthstencil);
    backbuffer->Release();
    depthstencil->Release();
}

// borrowBuffer - Utility function for distant land to temporarily use a ping-pong buffer
IDirect3DTexture9* PostShaders::borrowBuffer(int n) {
    IDirect3DSurface9* backbuffer;

    // Make a backbuffer copy for temporary use
    doublebuffer.select(n);
    device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
    device->StretchRect(backbuffer, 0, doublebuffer.sourceSurface(), 0, D3DTEXF_NONE);
    backbuffer->Release();

    return doublebuffer.sourceTexture();
}

// applyBlend - Utility function for distant land to render a full-screen shader
void PostShaders::applyBlend() {
    // Render with vertex shader by using a different FVF for the same buffer
    device->SetFVF(fvfBlend);
    device->SetStreamSource(0, vbPost, 0, 32);
    device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}



// Scripting interface for shaders
MGEShader* PostShaders::findShader(const char* shaderName) {
    for (auto& s : shaders) {
        if (s.name == shaderName) {
            return &s;
        }
    }
    return nullptr;
}

bool PostShaders::setShaderVar(const char* shaderName, const char* varName, int x) {
    MGEShader* shader = findShader(shaderName);
    if (!shader) {
        return false;
    }

    D3DXHANDLE ehVar = shader->effect->GetParameterByName(0, varName);
    if (!ehVar) {
        return false;
    }

    shader->effect->SetInt(ehVar, x);
    return true;
}

bool PostShaders::setShaderVar(const char* shaderName, const char* varName, float x) {
    MGEShader* shader = findShader(shaderName);
    if (!shader) {
        return false;
    }

    D3DXHANDLE ehVar = shader->effect->GetParameterByName(0, varName);
    if (!ehVar) {
        return false;
    }

    shader->effect->SetFloat(ehVar, x);
    return true;
}

bool PostShaders::setShaderVar(const char* shaderName, const char* varName, float* v) {
    MGEShader* shader = findShader(shaderName);
    if (!shader) {
        return false;
    }

    D3DXHANDLE ehVar = shader->effect->GetParameterByName(0, varName);
    if (!ehVar) {
        return false;
    }

    shader->effect->SetFloatArray(ehVar, v, 4);
    return true;
}

bool PostShaders::setShaderEnable(const char* shaderName, bool enable) {
    MGEShader* shader = findShader(shaderName);
    if (!shader) {
        return false;
    }

    shader->enabled = enable;
    return true;
}



// Effect helpers, silently ignores attempts to set non-existing shader variables
void MGEShader::SetTexture(EffectVariableID id, LPDIRECT3DBASETEXTURE9 tex) {
    if (ehVars[id]) {
        effect->SetTexture(ehVars[id], tex);
    }
}

void MGEShader::SetMatrix(EffectVariableID id, const D3DXMATRIX* m) {
    if (ehVars[id]) {
        effect->SetMatrix(ehVars[id], m);
    }
}

void MGEShader::SetFloatArray(EffectVariableID id, const float* x, int n) {
    if (ehVars[id]) {
        effect->SetFloatArray(ehVars[id], x, n);
    }
}

void MGEShader::SetFloat(EffectVariableID id, float x) {
    if (ehVars[id]) {
        effect->SetFloat(ehVars[id], x);
    }
}

void MGEShader::SetInt(EffectVariableID id, int x) {
    if (ehVars[id]) {
        effect->SetInt(ehVars[id], x);
    }
}

void MGEShader::SetBool(EffectVariableID id, bool b) {
    if (ehVars[id]) {
        effect->SetBool(ehVars[id], b);
    }
}
