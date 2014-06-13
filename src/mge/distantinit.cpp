
#include "proxydx/d3d8header.h"
#include "support/strsec.h"
#include "support/log.h"
#include "configuration.h"
#include "distantland.h"
#include "distantshader.h"
#include "dlformat.h"
#include "postshaders.h"
#include "morrowindbsa.h"
#include "mwbridge.h"

#define READ_FROM_BUFFER(src, dest, size) memcpy((void*)dest, (void*)src, size); src += size;


bool DistantLand::ready = false;
bool DistantLand::isRenderCached = false;
int DistantLand::numWaterVerts, DistantLand::numWaterTris;

IDirect3DDevice9 *DistantLand::device;
ID3DXEffect *DistantLand::effect;
ID3DXEffect *DistantLand::effectShadow;
ID3DXEffect *DistantLand::effectDepth;
ID3DXEffectPool *DistantLand::effectPool;
IDirect3DVertexDeclaration9 *DistantLand::LandDecl;
IDirect3DVertexDeclaration9 *DistantLand::StaticDecl;
IDirect3DVertexDeclaration9 *DistantLand::WaterDecl;
IDirect3DVertexDeclaration9 *DistantLand::GrassDecl;

VendorSpecificRendering DistantLand::vsr;

unordered_map<string, DistantLand::WorldSpace> DistantLand::mapWorldSpaces;
const DistantLand::WorldSpace *DistantLand::currentWorldSpace;
QuadTree DistantLand::LandQuadTree;
VisibleSet DistantLand::visLand;
VisibleSet DistantLand::visDistant;
VisibleSet DistantLand::visGrass;

vector<RenderedState> DistantLand::recordMW;
vector<RenderedState> DistantLand::recordSky;
vector<pair<const QuadTreeMesh*, int> > DistantLand::batchedGrass;

IDirect3DTexture9 *DistantLand::texWorldColour, *DistantLand::texWorldNormals, *DistantLand::texWorldDetail;
IDirect3DTexture9 *DistantLand::texDepthFrame;
IDirect3DSurface9 *DistantLand::surfDepthDepth;
IDirect3DTexture9 *DistantLand::texDistantBlend;
IDirect3DTexture9 *DistantLand::texReflection;
IDirect3DSurface9 *DistantLand::surfReflectionZ;
IDirect3DVolumeTexture9 *DistantLand::texWater;
IDirect3DVertexBuffer9 *DistantLand::vbWater;
IDirect3DIndexBuffer9 *DistantLand::ibWater;
IDirect3DVertexBuffer9 *DistantLand::vbGrassInstances;

IDirect3DTexture9 *DistantLand::texRain;
IDirect3DTexture9 *DistantLand::texRipples;
IDirect3DTexture9 *DistantLand::texRippleBuffer;
IDirect3DSurface9 *DistantLand::surfRain;
IDirect3DSurface9 *DistantLand::surfRipples;
IDirect3DSurface9 *DistantLand::surfRippleBuffer;
IDirect3DVertexBuffer9 *DistantLand::vbWaveSim;

IDirect3DTexture9 *DistantLand::texShadow;
IDirect3DTexture9 *DistantLand::texSoftShadow;
IDirect3DSurface9 *DistantLand::surfShadowZ;
IDirect3DVertexBuffer9 *DistantLand::vbFullFrame;

D3DXMATRIX DistantLand::mwView, DistantLand::mwProj;
D3DXMATRIX DistantLand::smView[2], DistantLand::smProj[2];
D3DXMATRIX DistantLand::smViewproj[2];
D3DXVECTOR4 DistantLand::eyeVec, DistantLand::eyePos;
D3DXVECTOR4 DistantLand::sunVec, DistantLand::sunPos;
float DistantLand::sunVis;
RGBVECTOR DistantLand::sunCol, DistantLand::sunAmb, DistantLand::ambCol;
RGBVECTOR DistantLand::nearfogCol, DistantLand::horizonCol;
RGBVECTOR DistantLand::atmOutscatter, DistantLand::atmInscatter;
float DistantLand::fogStart, DistantLand::fogEnd;
float DistantLand::fogNearStart, DistantLand::fogNearEnd;
float DistantLand::nearViewRange;
float DistantLand::windScaling, DistantLand::niceWeather;
float DistantLand::lightSunMult, DistantLand::lightAmbMult;

D3DXHANDLE DistantLand::ehRcpRes;
D3DXHANDLE DistantLand::ehShadowRcpRes;
D3DXHANDLE DistantLand::ehWorld;
D3DXHANDLE DistantLand::ehView;
D3DXHANDLE DistantLand::ehProj;
D3DXHANDLE DistantLand::ehShadowViewproj;
D3DXHANDLE DistantLand::ehVertexBlendState;
D3DXHANDLE DistantLand::ehVertexBlendPalette;
D3DXHANDLE DistantLand::ehAlphaRef;
D3DXHANDLE DistantLand::ehHasAlpha;
D3DXHANDLE DistantLand::ehHasBones;
D3DXHANDLE DistantLand::ehTex0;
D3DXHANDLE DistantLand::ehTex1;
D3DXHANDLE DistantLand::ehTex2;
D3DXHANDLE DistantLand::ehTex3;
D3DXHANDLE DistantLand::ehTex4;
D3DXHANDLE DistantLand::ehTex5;
D3DXHANDLE DistantLand::ehEyePos;
D3DXHANDLE DistantLand::ehFootPos;
D3DXHANDLE DistantLand::ehSunCol;
D3DXHANDLE DistantLand::ehSunAmb;
D3DXHANDLE DistantLand::ehSunVec;
D3DXHANDLE DistantLand::ehSunPos;
D3DXHANDLE DistantLand::ehSunVis;
D3DXHANDLE DistantLand::ehOutscatter;
D3DXHANDLE DistantLand::ehInscatter;
D3DXHANDLE DistantLand::ehSkyCol;
D3DXHANDLE DistantLand::ehFogCol1;
D3DXHANDLE DistantLand::ehFogCol2;
D3DXHANDLE DistantLand::ehFogStart;
D3DXHANDLE DistantLand::ehFogRange;
D3DXHANDLE DistantLand::ehFogNearStart;
D3DXHANDLE DistantLand::ehFogNearRange;
D3DXHANDLE DistantLand::ehNearViewRange;
D3DXHANDLE DistantLand::ehWindVec;
D3DXHANDLE DistantLand::ehNiceWeather;
D3DXHANDLE DistantLand::ehTime;
D3DXHANDLE DistantLand::ehRippleOrigin;
D3DXHANDLE DistantLand::ehWaveHeight;

void (*DistantLand::captureScreenFunc)(IDirect3DSurface9 *);


static vector<DistantStatic> DistantStatics;
static unordered_map< string, vector<UsedDistantStatic> > UsedDistantStatics;

struct MeshResources
{
    IDirect3DVertexBuffer9 *vb;
    IDirect3DIndexBuffer9 *ib;
    IDirect3DTexture9 *tex;

    MeshResources(IDirect3DVertexBuffer9 *_vb, IDirect3DIndexBuffer9 *_ib, IDirect3DTexture9 *_tex) : vb(_vb), ib(_ib), tex(_tex) {}
};
static vector<MeshResources> meshCollectionLand;
static vector<MeshResources> meshCollectionStatics;




// Water plane vertex declaration
const D3DVERTEXELEMENT9 WaterElem[] = {
    {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    D3DDECL_END()
};

// World mesh vertex declaration
const D3DVERTEXELEMENT9 LandElem[] = {
    {0, 0,  D3DDECLTYPE_FLOAT3,  D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    {0, 12, D3DDECLTYPE_SHORT2N, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
};

// Distant static vertex declaration
const D3DVERTEXELEMENT9 StaticElem[] = {
    {0, 0,  D3DDECLTYPE_FLOAT16_4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    {0, 8,  D3DDECLTYPE_UBYTE4N,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
    {0, 12, D3DDECLTYPE_D3DCOLOR,  D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0},
    {0, 16, D3DDECLTYPE_FLOAT16_2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
};

// Instanced grass vertex declaration
const D3DVERTEXELEMENT9 GrassElem[] =
{
    {0, 0,  D3DDECLTYPE_FLOAT16_4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    {0, 8,  D3DDECLTYPE_UBYTE4N,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
    {0, 12, D3DDECLTYPE_D3DCOLOR,  D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0},
    {0, 16, D3DDECLTYPE_FLOAT16_2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    {1, 0,  D3DDECLTYPE_FLOAT4,    D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
    {1, 16, D3DDECLTYPE_FLOAT4,    D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},
    {1, 32, D3DDECLTYPE_FLOAT4,    D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3},
    D3DDECL_END()
};



bool DistantLand::init(IDirect3DDevice9 *realDevice)
{
    if(ready) return true;
    if(device) return false;

    device = realDevice;
    LOG::logline(">> Distant Land init");
    vsr.init(device);

    LOG::logline(">> Distant Land init BSAs");
    BSAInit();

    LOG::logline(">> Distant Land init shader");
    if(!initShader())
        return false;

    LOG::logline(">> Distant Land init fixed function emu");
    if(!FixedFunctionShader::init(device, effectPool))
        return false;

    LOG::logline(">> Distant Land init post shaders");
    if(!PostShaders::init(device))
        return false;

    LOG::logline(">> Distant Land init depth");
    if(!initDepth())
        return false;

    LOG::logline(">> Distant Land init shadow");
    if(!initShadow())
        return false;

    LOG::logline(">> Distant Land init water");
    if(!initWater())
        return false;

    LOG::logline(">> Distant Land init world");
    if (!initLandscape())
        return false;

    LOG::logline(">> Distant Land init statics");
    if(!initDistantStatics())
        return false;

    LOG::logline(">> Distant Land init grass");
    if(!initGrass())
        return false;

    LOG::logline("<< Distant Land init");
    ready = true;
    isRenderCached = false;
    return true;
}

static void logShaderError(const char *shaderID, ID3DXBuffer *errors)
{
    LOG::logline("!! %s shader error", shaderID);
    if(errors)
    {
        LOG::logline("!! Shader errors: %s", errors->GetBufferPointer());
        errors->Release();
    }
}

static const D3DXMACRO macroExpFog = { "USE_EXPFOG", "" };
static const D3DXMACRO macroScattering = { "USE_SCATTERING", "" };
static const D3DXMACRO macroFilterReflection = { "FILTER_WATER_REFLECTION", "" };
static const D3DXMACRO macroDynamicRipples = { "DYNAMIC_RIPPLES", "" };
static const D3DXMACRO macroTerminator = { 0, 0 };

bool DistantLand::initShader()
{
    ID3DXBuffer *errors;
    std::vector<D3DXMACRO> features;

    // Set shader defines corresponding to required features
    if(Configuration.MGEFlags & EXP_FOG)
        features.push_back(macroExpFog);
    if(Configuration.MGEFlags & USE_ATM_SCATTER)
        features.push_back(macroScattering);
    if(Configuration.MGEFlags & BLUR_REFLECTIONS)
        features.push_back(macroFilterReflection);
    if(Configuration.MGEFlags & DYNAMIC_RIPPLES)
        features.push_back(macroDynamicRipples);
    features.push_back(macroTerminator);

    HRESULT hr = D3DXCreateEffectPool(&effectPool);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Effect pool creation failure");
        return false;
    }

    hr = D3DXCreateEffectFromFile(device, "Data files\\shaders\\XE Main.fx", &*features.begin(), 0, D3DXSHADER_OPTIMIZATION_LEVEL3|D3DXFX_LARGEADDRESSAWARE, effectPool, &effect, &errors);
    if(hr != D3D_OK)
    {
        logShaderError("XE Main", errors);
        return false;
    }

    ehRcpRes = effect->GetParameterByName(0, "rcpres");
    ehShadowRcpRes = effect->GetParameterByName(0, "shadowRcpRes");
    ehView = effect->GetParameterByName(0, "view");
    ehProj = effect->GetParameterByName(0, "proj");
    ehShadowViewproj = effect->GetParameterByName(0, "shadowviewproj");
    ehWorld = effect->GetParameterByName(0, "world");
    ehVertexBlendState = effect->GetParameterByName(0, "vertexblendstate");
    ehVertexBlendPalette = effect->GetParameterByName(0, "vertexblendpalette");
    ehAlphaRef = effect->GetParameterByName(0, "alpharef");
    ehHasAlpha = effect->GetParameterByName(0, "hasalpha");
    ehHasBones = effect->GetParameterByName(0, "hasbones");
    ehTex0 = effect->GetParameterByName(0, "tex0");
    ehTex1 = effect->GetParameterByName(0, "tex1");
    ehTex2 = effect->GetParameterByName(0, "tex2");
    ehTex3 = effect->GetParameterByName(0, "tex3");
    ehEyePos = effect->GetParameterByName(0, "EyePos");
    ehFootPos = effect->GetParameterByName(0, "FootPos");
    ehSunCol = effect->GetParameterByName(0, "SunCol");
    ehSunAmb = effect->GetParameterByName(0, "SunAmb");
    ehSunVec = effect->GetParameterByName(0, "SunVec");
    ehSunPos = effect->GetParameterByName(0, "SunPos");
    ehSunVis = effect->GetParameterByName(0, "SunVis");
    ehSkyCol = effect->GetParameterByName(0, "SkyCol");
    ehFogCol1 = effect->GetParameterByName(0, "FogCol1");
    ehFogCol2 = effect->GetParameterByName(0, "FogCol2");
    ehFogStart = effect->GetParameterByName(0, "FogStart");
    ehFogRange = effect->GetParameterByName(0, "FogRange");
    ehFogNearStart = effect->GetParameterByName(0, "nearFogStart");
    ehFogNearRange = effect->GetParameterByName(0, "nearFogRange");
    ehNearViewRange = effect->GetParameterByName(0, "nearViewRange");
    ehWindVec = effect->GetParameterByName(0, "WindVec");
    ehNiceWeather = effect->GetParameterByName(0, "niceWeather");
    ehTime = effect->GetParameterByName(0, "time");

    D3DVIEWPORT9 vp;
    device->GetViewport(&vp);
    float rcpres[2] = { 1.0 / vp.Width, 1.0 / vp.Height };
    effect->SetFloatArray(ehRcpRes, rcpres, 2);
    effect->SetFloat(ehShadowRcpRes, 1.0 / Configuration.DL.ShadowResolution);

    LOG::logline("-- Shader compiled OK");

    hr = D3DXCreateEffectFromFile(device, "Data files\\shaders\\XE Shadowmap.fx", &*features.begin(), 0, D3DXSHADER_OPTIMIZATION_LEVEL3|D3DXFX_LARGEADDRESSAWARE, effectPool, &effectShadow, &errors);
    if(hr != D3D_OK)
    {
        logShaderError("XE Shadowmap", errors);
        return false;
    }

    LOG::logline("-- Shadow map shader compiled OK");

    hr = D3DXCreateEffectFromFile(device, "Data files\\shaders\\XE Depth.fx", &*features.begin(), 0, D3DXSHADER_OPTIMIZATION_LEVEL3|D3DXFX_LARGEADDRESSAWARE, effectPool, &effectDepth, &errors);
    if(hr != D3D_OK)
    {
        logShaderError("XE Depth", errors);
        return false;
    }

    LOG::logline("-- Depth shader compiled OK");

    if(Configuration.MGEFlags & USE_ATM_SCATTER)
    {
        // Default scatter coefficients
        atmOutscatter = RGBVECTOR(0.07, 0.36, 0.76);
        atmInscatter = RGBVECTOR(0.25, 0.38, 0.48);

        ehOutscatter = effect->GetParameterByName(0, "outscatter");
        ehInscatter = effect->GetParameterByName(0, "inscatter");

        // Mark moon geometry for detection
        DECLARE_MWBRIDGE
        mwBridge->markMoonNodes(kMoonTag);
    }

    return true;
}

bool DistantLand::initDepth()
{
    HRESULT hr;
    D3DVIEWPORT9 vp;

    // Set up depth frame texture, requires its own z-buffer (my card fails to support INTZ/DF24)
    device->GetViewport(&vp);

    hr = device->CreateTexture(vp.Width, vp.Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &texDepthFrame, NULL);
    if (hr != D3D_OK)
    {
        LOG::logline("!! Failed to create depth frame render target");
        return false;
    }

    hr = device->CreateDepthStencilSurface(vp.Width, vp.Height, D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, FALSE, &surfDepthDepth, NULL);
    if (hr != D3D_OK)
    {
        LOG::logline("!! Failed to create depth target z-buffer");
        return false;
    }

    return true;
}

bool DistantLand::initWater()
{
    HRESULT hr;
    const UINT reflRes = 1024;

    // Reflection render target
    hr = device->CreateTexture(reflRes, reflRes, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texReflection, NULL);
    if (hr != D3D_OK)
    {
        LOG::logline("!! Failed to create reflection render target");
        return false;
    }

    // Reflection Z-buffer
    if(Configuration.DL.ShadowResolution == reflRes)
    {
        // Re-use shadow Z-buffer
        surfShadowZ->AddRef();
        surfReflectionZ = surfShadowZ;
    }
    else
    {
        hr = device->CreateDepthStencilSurface(reflRes, reflRes, D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, TRUE, &surfReflectionZ, NULL);
        if(hr != D3D_OK)
        {
            LOG::logline("!! Failed to create reflection Z buffer");
            return false;
        }
    }

    // Water normals and geometry
    const int resS = (Configuration.MGEFlags & DYNAMIC_RIPPLES) ? 150 : 16;
    const int resT = (Configuration.MGEFlags & DYNAMIC_RIPPLES) ? 120 : 15;
    numWaterVerts = resS * resT + 1;
    numWaterTris = 2 * resS * resT - resS;

    hr = D3DXCreateVolumeTextureFromFile(device, "Data Files\\textures\\MGE\\water_NRM.dds", &texWater);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to load water texture");
        return false;
    }
    hr = device->CreateVertexDeclaration(WaterElem, &WaterDecl);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create water decl");
        return false;
    }
    hr = device->CreateVertexBuffer(numWaterVerts * 12, 0, 0, D3DPOOL_MANAGED, &vbWater, 0);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create water verts");
        return false;
    }
    hr = device->CreateIndexBuffer(numWaterTris * 6, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ibWater, 0);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create water indices");
        return false;
    }

    // Build radial water mesh
    D3DXVECTOR3 *v;
    vbWater->Lock(0, 0, (void**)&v, 0);

    // Water plane lies at water level - 1.0 (not -4.0, which is the fog transition)
    const float dS = (2.0*M_PI) / resS;
    int s, t;
    float r, w = -1.0f;

    *v++ = D3DXVECTOR3(0, 0, w);
    for(t = 0; t < resT; ++t)
    {
        if(Configuration.MGEFlags & DYNAMIC_RIPPLES)
        {
            // Higher mesh density near player
            // The mesh requires density past 8192 units to cover the z discontinuity at distant land
            r = float(t) / float(resT);
            r = 9600.0f * (0.9f * powf(r, 3) + 0.1f * r);
            // Extend last ring past horizon
            if((t+1) == resT) r = 500000.0f;
        }
        else
        {
            r = 4096.0f * (1.0f + t * t);
        }

        for(s = 0; s < resS; ++s)
            *v++ = D3DXVECTOR3(r * cos(dS * s), r * sin(dS * s), w);
    }

    vbWater->Unlock();

    USHORT *i;
    ibWater->Lock(0, 0, (void**)&i, 0);

    // Centre triangles
    for(s = 0; s < resS; ++s)
    {
        *i++ = 0; *i++ = 1 + s; *i++ = 1 + (s+1) % resS;
    }
    // Rings
    for(t = 1; t < resT; ++t)
    {
        for(s = 0; s < resS; ++s)
        {
            USHORT tbase = 1 + resS*(t-1), s2 = (s+1) % resS;
            *i++ = tbase + s; *i++ = resS + tbase + s; *i++ = tbase + s2;
            *i++ = resS + tbase+ s; *i++ = resS + tbase + s2; *i++ = tbase + s2;
        }
    }

    ibWater->Unlock();

    if(Configuration.MGEFlags & DYNAMIC_RIPPLES)
    {
        LOG::logline("-- Distant Land init dynamic water");

        // Setup water simulation
        if(!initDynamicWaves())
            return false;

        // Disable Morrowind generated ripples
        DECLARE_MWBRIDGE
        mwBridge->toggleRipples(false);
    }

    return true;
}

bool DistantLand::initDynamicWaves()
{
    HRESULT hr;

    hr = device->CreateTexture(waveTexResolution, waveTexResolution, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &texRain, NULL);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create rain simulation texture");
        return false;
    }
    texRain->GetSurfaceLevel(0, &surfRain);
    device->ColorFill(surfRain, 0, 0x80808080);

    hr = device->CreateTexture(waveTexResolution, waveTexResolution, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &texRipples, NULL);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create ripple simulation texture");
        return false;
    }
    texRipples->GetSurfaceLevel(0, &surfRipples);
    device->ColorFill(surfRipples, 0, 0x80808080);

    hr = device->CreateTexture(waveTexResolution, waveTexResolution, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &texRippleBuffer, NULL);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create ripple simulation texture");
        return false;
    }
    texRippleBuffer->GetSurfaceLevel(0, &surfRippleBuffer);
    device->ColorFill(surfRippleBuffer, 0, 0x80808080);

    // Vertex buffer for wave texture
    static float waveVertices[] = {
/*     -0.5f,                    -0.5f,                                               0,1,   0,0,0,0,
        -0.5f,                    waveTexResolution-0.5f,                 0,1,   0,1,0,1,
        waveTexResolution-0.5f,    -0.5f,                                  0,1,   1,0,1,0,
        waveTexResolution-0.5f,    waveTexResolution-0.5f,    0,1,   1,1,1,1 */

        // Use only one tri over the whole texture to prevent simulation seams at tri edges
        // Rendering to a surface that is bound as a source texture updates the texture after
        // each primitive, causing artifacts to appear at primitive boundaries
        -waveTexResolution/2  -0.5f,    waveTexResolution/2  -0.5f,  0,  1,     -0.5, 0.5,     0,0,
        waveTexResolution        -0.5f,    2*waveTexResolution  -0.5f,  0,  1,      1.0, 2.0,      0,1,
        waveTexResolution        -0.5f,    -waveTexResolution    -0.5f,  0,  1,     1.0, -1.0,     1,1
    };

    void *vp;
    hr = device->CreateVertexBuffer(3 * 32, D3DUSAGE_WRITEONLY, fvfWave, D3DPOOL_DEFAULT, &vbWaveSim, 0);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create wave simulation vb");
        return false;
    }
    if(vbWaveSim->Lock(0, 0, (void**)&vp, 0) != D3D_OK)
    {
        LOG::logline("!! Failed to lock wave simulation vb");
        return false;
    }
    memcpy(vp, waveVertices, sizeof(waveVertices));
    vbWaveSim->Unlock();

    // Extra shader variables required
    ehTex4 = effect->GetParameterByName(0, "tex4");
    ehTex5 = effect->GetParameterByName(0, "tex5");
    ehRippleOrigin = effect->GetParameterByName(0, "rippleOrigin");
    ehWaveHeight = effect->GetParameterByName(0, "waveHeight");

    return true;
}

bool DistantLand::initShadow()
{
    // Use *16F since *32F may not be filtered
    const D3DFORMAT shadowFormat = D3DFMT_G16R16F;
    const D3DFORMAT shadowZFormat = D3DFMT_D24X8;
    const UINT shadowSize = Configuration.DL.ShadowResolution;
    HRESULT hr;

    hr = device->CreateTexture(shadowSize, shadowSize, 1, D3DUSAGE_RENDERTARGET, shadowFormat, D3DPOOL_DEFAULT, &texShadow, NULL);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create shadow render target");
        return false;
    }
    hr = device->CreateTexture(shadowSize, shadowSize, 1, D3DUSAGE_RENDERTARGET, shadowFormat, D3DPOOL_DEFAULT, &texSoftShadow, NULL);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create shadow render target");
        return false;
    }
    hr = device->CreateDepthStencilSurface(shadowSize, shadowSize, shadowZFormat, D3DMULTISAMPLE_NONE, 0, TRUE, &surfShadowZ, NULL);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create shadow Z buffer");
        return false;
    }
    hr = device->CreateVertexBuffer(4 * 12, 0, 0, D3DPOOL_MANAGED, &vbFullFrame, 0);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create shadow processing verts");
        return false;
    }

    D3DXVECTOR3* v;
    vbFullFrame->Lock(0, 0, (void**)&v, 0);
    v[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
    v[1] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
    v[2] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
    v[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
    vbFullFrame->Unlock();

    return true;
}

bool DistantLand::initDistantStatics()
{
    if(FAILED(device->CreateVertexDeclaration(StaticElem, &StaticDecl)))
    {
        LOG::logline("!! Failed to to create static vertex declaration");
        return false;
    }

    if(!loadDistantStatics())
        return false;

    if(!initDistantStaticsBVH())
        return false;

    // Remove UsedDistantStatic, DistantStatic, and DistantStaticSubset objects
    UsedDistantStatics.clear();

    for(vector<DistantStatic>::iterator i = DistantStatics.begin(); i != DistantStatics.end(); ++i)
    {
        delete [] i->subsets;
        i->subsets = 0;
    }

    DistantStatics.clear();

    currentWorldSpace = 0;
    return true;
}

bool DistantLand::loadDistantStatics()
{
    DWORD unused;

    if(GetFileAttributes("data files/distantland/statics") == INVALID_FILE_ATTRIBUTES)
    {
        LOG::logline("!! Distant statics have not been generated");
        return true;
    }

    HANDLE h = CreateFile("data files/distantland/statics/usage.data", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    if (h == INVALID_HANDLE_VALUE)
    {
        LOG::logline("!! Required distant statics data is missing or corrupted");
        return false;
    }

    size_t DistantStaticCount;
    ReadFile(h, &DistantStaticCount, 4, &unused, 0);
    DistantStatics.resize(DistantStaticCount);

    HANDLE h2 = CreateFile("data files/distantland/statics/static_meshes", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    if (h2 == INVALID_HANDLE_VALUE)
    {
        LOG::logline("!! Required distant statics data is missing or corrupted");
        return false;
    }

    // Bright yellow error texture
    IDirect3DTexture9 *errorTexture;
    device->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &errorTexture, NULL);

    D3DLOCKED_RECT yellow;
    errorTexture->LockRect(0, &yellow, NULL, 0);
    *(DWORD *)yellow.pBits = 0xffffff00;
    errorTexture->UnlockRect(0);

    // Read entire file into one big memory buffer
    DWORD file_size = GetFileSize(h2, NULL);
    unsigned char *file_buffer = new unsigned char[file_size];
    unsigned char *pos = file_buffer;
    ReadFile(h2, file_buffer, file_size, &unused, NULL);
    CloseHandle(h2);

    for(vector<DistantStatic>::iterator i = DistantStatics.begin(); i != DistantStatics.end(); ++i)
    {
        READ_FROM_BUFFER(pos, &i->numSubsets, 4);
        READ_FROM_BUFFER(pos, &i->radius, 4);
        READ_FROM_BUFFER(pos, &i->center, 12);
        READ_FROM_BUFFER(pos, &i->type, 1);

        i->subsets = new DistantSubset[i->numSubsets];

        for(int j = 0; j != i->numSubsets; j++)
        {
            DistantSubset *subset = &i->subsets[j];

            // Get bounding sphere
            READ_FROM_BUFFER(pos, &subset->radius, 4);
            READ_FROM_BUFFER(pos, &subset->center, 12);

            // Get AABB min and max
            READ_FROM_BUFFER(pos, &subset->min, 12);
            READ_FROM_BUFFER(pos, &subset->max, 12);

            // Get vertex and face count
            READ_FROM_BUFFER(pos, &subset->verts, 4);
            READ_FROM_BUFFER(pos, &subset->faces, 4);

            // Load mesh data
            IDirect3DVertexBuffer9 *vb;
            IDirect3DIndexBuffer9 *ib;
            void *lockdata;

            device->CreateVertexBuffer(subset->verts * SIZEOFSTATICVERT, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vb, 0);
            vb->Lock(0, 0, &lockdata, 0);
            READ_FROM_BUFFER(pos, lockdata, subset->verts * SIZEOFSTATICVERT);
            vb->Unlock();

            device->CreateIndexBuffer(subset->faces * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, 0);
            ib->Lock(0, 0, &lockdata, 0);
            READ_FROM_BUFFER(pos, lockdata, subset->faces * 6); // Morrowind nifs don't support 32 bit indices?
            ib->Unlock();

            subset->vbuffer = vb;
            subset->ibuffer = ib;

            // Load referenced texture
            unsigned short pathsize;
            READ_FROM_BUFFER(pos, &pathsize, 2);
            const char *texname = (const char *)pos;
            pos += pathsize;

            IDirect3DTexture9 *tex = BSALoadTexture(device, texname);
            if(!tex)
            {
                LOG::logline("Cannot load texture %s", texname);
                tex = errorTexture;
            }
            subset->tex = tex;

            // Keep resource pointers for deallocation
            meshCollectionStatics.push_back(MeshResources(vb, ib, tex));
        }
    }

    // Finished with the meshes file
    delete [] file_buffer;

    // Texture memory reporting
    int texturesLoaded, texMemUsage;
    BSACacheStats(&texturesLoaded, &texMemUsage);

    LOG::logline("-- Distant static textures loaded, %d textures", texturesLoaded);
    LOG::logline("-- Distant static texture memory use: %d MB", texMemUsage);


    // Load statics references
    mapWorldSpaces.clear();
    for(size_t nWorldSpace = 0; true; ++nWorldSpace)
    {
        size_t UsedDistantStaticCount;
        unordered_map< string, vector<UsedDistantStatic> >::iterator iCell;

        ReadFile(h, &UsedDistantStaticCount, 4, &unused, 0);
        if(nWorldSpace != 0 && UsedDistantStaticCount == 0) break;

        if(nWorldSpace == 0)
        {
            mapWorldSpaces.insert(make_pair(string(), WorldSpace()));
            iCell = UsedDistantStatics.insert(make_pair(string(), vector<UsedDistantStatic>())).first;
            if(UsedDistantStaticCount == 0) continue;
        }
        else
        {
            char cellname[64];
            ReadFile(h, &cellname, 64, &unused, 0);
            iCell = UsedDistantStatics.insert(make_pair(string(cellname), vector<UsedDistantStatic>())).first;
            mapWorldSpaces.insert(make_pair(string(cellname), WorldSpace()));
        }

        unsigned char *UsedDistantStaticData = new unsigned char[UsedDistantStaticCount * 32];
        unsigned char *dataPos = UsedDistantStaticData;
        ReadFile(h, UsedDistantStaticData, UsedDistantStaticCount * 32, &unused, 0);

        vector<UsedDistantStatic> *ThisWorldStatics = &iCell->second;
        ThisWorldStatics->reserve(UsedDistantStaticCount);

        for(size_t i = 0; i < UsedDistantStaticCount; ++i)
        {
            UsedDistantStatic NewUsedStatic;
            float yaw, pitch, roll, scale;

            READ_FROM_BUFFER(dataPos, &NewUsedStatic.staticRef, 4);
            READ_FROM_BUFFER(dataPos, &NewUsedStatic.pos, 12);

            READ_FROM_BUFFER(dataPos, &yaw, 4);
            READ_FROM_BUFFER(dataPos, &pitch, 4);
            READ_FROM_BUFFER(dataPos, &roll, 4);
            READ_FROM_BUFFER(dataPos, &scale, 4);
            if(scale == 0.0f) scale = 1.0f;

            NewUsedStatic.radius = DistantStatics[NewUsedStatic.staticRef].radius * scale;
            NewUsedStatic.center = DistantStatics[NewUsedStatic.staticRef].center + NewUsedStatic.pos;
            NewUsedStatic.scale = scale;

            D3DXMATRIX transmat, rotmatx, rotmaty, rotmatz, scalemat;
            D3DXMatrixTranslation(&transmat, NewUsedStatic.pos.x, NewUsedStatic.pos.y, NewUsedStatic.pos.z);
            D3DXMatrixRotationX(&rotmatx, -yaw);
            D3DXMatrixRotationY(&rotmaty, -pitch);
            D3DXMatrixRotationZ(&rotmatz, -roll);
            D3DXMatrixScaling(&scalemat, scale, scale, scale);
            NewUsedStatic.transform = scalemat * rotmatz * rotmaty * rotmatx * transmat;

            ThisWorldStatics->push_back(NewUsedStatic);
        }

        delete [] UsedDistantStaticData;
    }

    CloseHandle(h);
    LOG::logline("-- Distant Land finished loading distant statics");
    return true;
}

bool DistantLand::initDistantStaticsBVH()
{
    unordered_map<string, WorldSpace>::iterator iWS;
    for(iWS = mapWorldSpaces.begin(); iWS != mapWorldSpaces.end(); ++iWS)
    {
        vector<UsedDistantStatic> *uds = &UsedDistantStatics.find(iWS->first)->second;
        vector<UsedDistantStatic>::iterator i;

        // Initialize quadtrees
        QuadTree *NQTR = iWS->second.NearStatics = new QuadTree();
        QuadTree *FQTR =iWS->second.FarStatics = new QuadTree();
        QuadTree *VFQTR = iWS->second.VeryFarStatics = new QuadTree();
        QuadTree *GQTR = iWS->second.GrassStatics = new QuadTree();

        // Calclulate optimal initial quadtree size
        D3DXVECTOR2 max = D3DXVECTOR2(FLT_MIN, FLT_MIN);
        D3DXVECTOR2 min = D3DXVECTOR2(FLT_MAX, FLT_MAX);

        // Find xyz bounds
        for(i = uds->begin(); i != uds->end(); ++i)
        {
            float x = i->pos.x, y = i->pos.y;

            max.x = std::max(x, max.x);
            max.y = std::max(y, max.y);
            min.x = std::min(min.x, x);
            min.y = std::min(min.y, y);
        }

        float box_size = std::max(max.x - min.x, max.y - min.y);
        D3DXVECTOR2 box_center = 0.5 * (max + min);

        NQTR->SetBox(box_size, box_center);
        FQTR->SetBox(box_size, box_center);
        VFQTR->SetBox(box_size, box_center);
        GQTR->SetBox(box_size, box_center);

        for(i = uds->begin(); i != uds->end(); ++i)
        {
            DistantStatic *stat = &DistantStatics[i->staticRef];
            QuadTree *targetQTR;

            // Buildings are treated as larger objects, as they are typically
            // smaller component meshes combined to make a single building
            float radius = stat->radius;
            if(stat->type == STATIC_BUILDING)
                radius *= 2.0f;

            // Select quadtree to place object in
            switch(stat->type)
            {
            case STATIC_AUTO:
            case STATIC_TREE:
            case STATIC_BUILDING:
                if(radius <= Configuration.DL.FarStaticMinSize)
                    targetQTR = NQTR;
                else if(radius <= Configuration.DL.VeryFarStaticMinSize)
                    targetQTR = FQTR;
                else
                    targetQTR = VFQTR;
                break;

            case STATIC_GRASS:
                targetQTR = GQTR;
                break;

            case STATIC_NEAR:
                targetQTR = NQTR;
                break;

            case STATIC_FAR:
                targetQTR = FQTR;
                break;

            case STATIC_VERY_FAR:
                targetQTR = VFQTR;
                break;

            default:
                continue;
            }

            // Add sub-meshes to appropriate quadtree
            for(int s = 0; s != stat->numSubsets; ++s)
            {
                targetQTR->AddMesh(
                    i->GetBoundingSphere(stat->subsets[s]),
                    i->GetBoundingBox(stat->subsets[s]),
                    i->transform,
                    stat->subsets[s].tex,
                    stat->subsets[s].verts,
                    stat->subsets[s].vbuffer,
                    stat->subsets[s].faces,
                    stat->subsets[s].ibuffer
                );
            }
        }

        NQTR->Optimize(); NQTR->CalcVolume();
        FQTR->Optimize(); FQTR->CalcVolume();
        VFQTR->Optimize(); VFQTR->CalcVolume();
        GQTR->Optimize(); GQTR->CalcVolume();

        uds->clear();
    }

    return true;
}

bool DistantLand::initLandscape()
{
    HRESULT hr;
    LOG::logline(">> Landscape Load");

    hr = device->CreateVertexDeclaration(LandElem, &LandDecl);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to to create world vertex declaration");
        return false;
    }

    if(GetFileAttributes("data files\\distantland\\world") == INVALID_FILE_ATTRIBUTES)
    {
        LOG::logline("!! Distant land has not been generated");
        return true;
    }

    hr = D3DXCreateTextureFromFileEx(device, "Data files\\distantland\\world.dds", 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &texWorldColour);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Could not load world texture for distant land");
        return false;
    }

    hr = D3DXCreateTextureFromFileEx(device, "Data files\\distantland\\world_n.tga", 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &texWorldNormals);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Could not load world normal map texture for distant land");
        return false;
    }

    hr = D3DXCreateTextureFromFileEx(device, "Data files\\textures\\MGE\\world_detail.dds", 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &texWorldDetail);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Could not load world detail texture for distant land");
        return false;
    }

    LOG::logline("-- Landscape textures loaded");

    HANDLE file = CreateFile("data files\\distantland\\world", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    if(file == INVALID_HANDLE_VALUE) return false;

    DWORD mesh_count, unused;
    ReadFile(file, &mesh_count, 4, &unused, 0);

    vector<LandMesh> meshesLand;
    meshesLand.resize(mesh_count);

    if(!meshesLand.empty())
    {
        D3DXVECTOR2 qtmin(FLT_MAX, FLT_MAX), qtmax(FLT_MIN, FLT_MIN);
        vector<LandMesh>::iterator  i;
        D3DXMATRIX world;
        D3DXMatrixIdentity(&world);

        // Load meshes and calculate max size of quadtree
        for(i = meshesLand.begin(); i != meshesLand.end(); ++i)
        {
            ReadFile(file, &i->sphere.radius, 4, &unused,0);
            ReadFile(file, &i->sphere.center, 12, &unused,0);

            D3DXVECTOR3 min, max;
            ReadFile(file, &min, 12, &unused, 0);
            ReadFile(file, &max, 12, &unused, 0);
            i->box.Set(min, max);

            ReadFile(file, &i->verts, 4, &unused, 0);
            ReadFile(file, &i->faces, 4, &unused, 0);

            bool large = (i->verts > 0xFFFF || i->faces > 0xFFFF);
            IDirect3DVertexBuffer9 *vb;
            IDirect3DIndexBuffer9 *ib;
            void *lockdata;

            device->CreateVertexBuffer(i->verts * SIZEOFLANDVERT, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vb, 0);
            vb->Lock(0, 0, &lockdata, 0);
            ReadFile(file, lockdata, i->verts * SIZEOFLANDVERT, &unused, 0);
            vb->Unlock();

            device->CreateIndexBuffer(i->faces * (large ? 12 : 6), D3DUSAGE_WRITEONLY, large ? D3DFMT_INDEX32 : D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, 0);
            ib->Lock(0, 0, &lockdata, 0);
            ReadFile(file, lockdata, i->faces * (large ? 12 : 6), &unused, 0);
            ib->Unlock();

            i->vbuffer = vb;
            i->ibuffer = ib;

            qtmin.x = std::min(qtmin.x, i->sphere.center.x - i->sphere.radius);
            qtmin.y = std::min(qtmin.y, i->sphere.center.y - i->sphere.radius);
            qtmax.x = std::max(qtmax.x, i->sphere.center.x + i->sphere.radius);
            qtmax.y = std::max(qtmax.y, i->sphere.center.y + i->sphere.radius);
        }

        LandQuadTree.SetBox(std::max(qtmax.x - qtmin.x, qtmax.y - qtmin.y), 0.5 * (qtmax + qtmin));

        // Add meshes to the quadtree
        for(i = meshesLand.begin(); i != meshesLand.end(); ++i)
        {
            meshCollectionLand.push_back(MeshResources(i->vbuffer, i->ibuffer, 0));
            LandQuadTree.AddMesh(i->sphere, i->box, world, texWorldColour, i->verts, i->vbuffer, i->faces, i->ibuffer);
        }
    }

    CloseHandle(file);
    LandQuadTree.CalcVolume();

    LOG::logline("<< Landscape Load");
    return true;
}

bool DistantLand::initGrass()
{
    HRESULT hr;

    hr = device->CreateVertexDeclaration(GrassElem, &GrassDecl);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create grass decl");
        return false;
    }

    hr = device->CreateVertexBuffer(MaxGrassElements * GrassInstStride, D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vbGrassInstances, NULL);
    if(hr != D3D_OK)
    {
        LOG::logline("!! Failed to create grass instance buffer");
        return false;
    }

    return true;
}

void DistantLand::release()
{
    if(!ready) return;

    LOG::logline(">> Distant Land release");

    PostShaders::release();
    FixedFunctionShader::release();

    unordered_map<string, WorldSpace>::iterator iWS;
    for(iWS = mapWorldSpaces.begin(); iWS != mapWorldSpaces.end(); ++iWS)
    {
        WorldSpace *w = &iWS->second;
        delete w->NearStatics;
        delete w->FarStatics;
        delete w->VeryFarStatics;
        delete w->GrassStatics;
    }
    mapWorldSpaces.clear();

    vector<MeshResources>::iterator iM;
    for(iM = meshCollectionStatics.begin(); iM != meshCollectionStatics.end(); ++iM)
    {
        iM->vb->Release();
        iM->ib->Release();
        iM->tex->Release();
    }
    meshCollectionStatics.clear();

    LandQuadTree.Clear();
    for(iM = meshCollectionLand.begin(); iM != meshCollectionLand.end(); ++iM)
    {
        iM->vb->Release();
        iM->ib->Release();
        // A shared texture is used for land, and is released below
    }
    meshCollectionLand.clear();

    if(texWorldColour)
    {
        texWorldColour->Release(); texWorldColour = 0;
        texWorldNormals->Release(); texWorldNormals = 0;
        texWorldDetail->Release(); texWorldDetail = 0;
    }

    BSAClearTextureCache();

    if(Configuration.MGEFlags & DYNAMIC_RIPPLES)
    {
        surfRain->Release(); surfRain = 0;
        texRain->Release(); texRain = 0;
        surfRipples->Release(); surfRipples = 0;
        texRipples->Release(); texRipples = 0;
        surfRippleBuffer->Release(); surfRippleBuffer = 0;
        texRippleBuffer->Release(); texRippleBuffer = 0;
        vbWaveSim->Release(); vbWaveSim = 0;
    }

    LandDecl->Release(); LandDecl = 0;
    StaticDecl->Release(); StaticDecl = 0;
    WaterDecl->Release(); WaterDecl = 0;
    GrassDecl->Release(); GrassDecl = 0;

    texShadow->Release(); texShadow = 0;
    texSoftShadow->Release(); texSoftShadow = 0;
    surfShadowZ->Release(); surfShadowZ = 0;

    texWater->Release(); texWater = 0;
    texReflection->Release(); texReflection = 0;
    surfReflectionZ->Release(); surfReflectionZ = 0;
    vbWater->Release(); vbWater = 0;
    ibWater->Release(); ibWater = 0;
    vbGrassInstances->Release(); vbGrassInstances = 0;
    vbFullFrame->Release(); vbFullFrame = 0;

    texDepthFrame->Release(); texDepthFrame = 0;
    surfDepthDepth->Release(); surfDepthDepth = 0;

    effectPool->Release(); effectPool = 0;
    effectShadow->Release(); effectShadow = 0;
    effectDepth->Release(); effectDepth = 0;
    effect->Release(); effect = 0;

    LOG::logline("<< Distant Land release");

    device = 0;
    ready = false;
}
