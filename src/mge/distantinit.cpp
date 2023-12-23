
#include "proxydx/d3d8header.h"
#include "support/log.h"
#include "configuration.h"
#include "distantland.h"
#include "distantshader.h"
#include "dlformat.h"
#include "postshaders.h"
#include "morrowindbsa.h"
#include "mwbridge.h"
#include "mgeversion.h"
#include "statusoverlay.h"
#include <memory>
#include <optional>



using std::string;
using std::string_view;
using std::vector;
using std::unordered_map;

bool DistantLand::ready = false;
bool DistantLand::isRenderCached = false;
bool DistantLand::isPPLActive = false;
int DistantLand::numWaterVerts, DistantLand::numWaterTris;

IDirect3DDevice9* DistantLand::device;
ID3DXEffect* DistantLand::effect;
ID3DXEffect* DistantLand::effectShadow;
ID3DXEffect* DistantLand::effectDepth;
ID3DXEffectPool* DistantLand::effectPool;
IDirect3DVertexDeclaration9* DistantLand::LandDecl;
IDirect3DVertexDeclaration9* DistantLand::StaticDecl;
IDirect3DVertexDeclaration9* DistantLand::WaterDecl;
IDirect3DVertexDeclaration9* DistantLand::GrassDecl;

VendorSpecificRendering DistantLand::vsr;

unordered_map<std::string, DistantLand::WorldSpace> DistantLand::mapWorldSpaces;
const DistantLand::WorldSpace* DistantLand::currentWorldSpace;
std::vector<DistantLand::DynamicVisGroup> DistantLand::dynamicVisGroups;
void* DistantLand::lastDistantVisCell;
QuadTree DistantLand::LandQuadTree;
VisibleSet DistantLand::visLand;
VisibleSet DistantLand::visDistant;
VisibleSet DistantLand::visGrass;

vector<DistantLand::RecordedState> DistantLand::recordMW;
vector<DistantLand::RecordedState> DistantLand::recordSky;
vector< std::pair<const QuadTreeMesh*, int> > DistantLand::batchedGrass;

IDirect3DTexture9* DistantLand::texWorldColour, *DistantLand::texWorldNormals, *DistantLand::texWorldDetail;
IDirect3DTexture9* DistantLand::texDepthFrame;
IDirect3DSurface9* DistantLand::surfDepthDepth;
IDirect3DTexture9* DistantLand::texDistantBlend;
IDirect3DTexture9* DistantLand::texReflection;
IDirect3DSurface9* DistantLand::surfReflectionZ;
IDirect3DVolumeTexture9* DistantLand::texWater;
IDirect3DVertexBuffer9* DistantLand::vbWater;
IDirect3DIndexBuffer9* DistantLand::ibWater;
IDirect3DVertexBuffer9* DistantLand::vbGrassInstances;

IDirect3DTexture9* DistantLand::texRain;
IDirect3DTexture9* DistantLand::texRipples;
IDirect3DTexture9* DistantLand::texRippleBuffer;
IDirect3DSurface9* DistantLand::surfRain;
IDirect3DSurface9* DistantLand::surfRipples;
IDirect3DSurface9* DistantLand::surfRippleBuffer;
IDirect3DVertexBuffer9* DistantLand::vbWaveSim;

IDirect3DTexture9* DistantLand::texShadow;
IDirect3DTexture9* DistantLand::texSoftShadow;
IDirect3DSurface9* DistantLand::surfShadowZ;
IDirect3DVertexBuffer9* DistantLand::vbFullFrame;
IDirect3DVertexBuffer9* DistantLand::vbClipCube;

D3DXMATRIX DistantLand::mwView, DistantLand::mwProj;
D3DXMATRIX DistantLand::smView[2], DistantLand::smProj[2];
D3DXMATRIX DistantLand::smViewproj[2];
D3DXVECTOR4 DistantLand::eyeVec, DistantLand::eyePos;
D3DXVECTOR4 DistantLand::sunVec, DistantLand::sunPos;
float DistantLand::sunVis;
RGBVECTOR DistantLand::sunCol, DistantLand::sunAmb, DistantLand::ambCol;
RGBVECTOR DistantLand::nearFogCol, DistantLand::horizonCol;
RGBVECTOR DistantLand::atmOutscatter(0.07, 0.36, 0.76);
RGBVECTOR DistantLand::atmInscatter(0.25, 0.38, 0.48);
D3DXVECTOR4 DistantLand::atmSkylightScatter(0.4456, 0.6194, 1.0, 0.44);
float DistantLand::fogStart, DistantLand::fogEnd;
float DistantLand::fogExpStart, DistantLand::fogExpDivisor;
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
D3DXHANDLE DistantLand::ehMaterialAlpha;
D3DXHANDLE DistantLand::ehHasAlpha;
D3DXHANDLE DistantLand::ehHasBones;
D3DXHANDLE DistantLand::ehHasVCol;
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
D3DXHANDLE DistantLand::ehSunVecView;
D3DXHANDLE DistantLand::ehSunPos;
D3DXHANDLE DistantLand::ehSunVis;
D3DXHANDLE DistantLand::ehOutscatter;
D3DXHANDLE DistantLand::ehInscatter;
D3DXHANDLE DistantLand::ehSkyScatterFar;
D3DXHANDLE DistantLand::ehSkyCol;
D3DXHANDLE DistantLand::ehFogColNear;
D3DXHANDLE DistantLand::ehFogColFar;
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

std::function<void(IDirect3DSurface9*)> DistantLand::captureScreenHandler = nullptr;
bool DistantLand::captureScreenWithUI;


struct MeshResources {
    IDirect3DVertexBuffer9* vb;
    IDirect3DIndexBuffer9* ib;
    IDirect3DTexture9* tex;

    MeshResources(IDirect3DVertexBuffer9* _vb, IDirect3DIndexBuffer9* _ib, IDirect3DTexture9* _tex) : vb(_vb), ib(_ib), tex(_tex) {}
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
const D3DVERTEXELEMENT9 GrassElem[] = {
    {0, 0,  D3DDECLTYPE_FLOAT16_4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    {0, 8,  D3DDECLTYPE_UBYTE4N,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
    {0, 12, D3DDECLTYPE_D3DCOLOR,  D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0},
    {0, 16, D3DDECLTYPE_FLOAT16_2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    {1, 0,  D3DDECLTYPE_FLOAT4,    D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
    {1, 16, D3DDECLTYPE_FLOAT4,    D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},
    {1, 32, D3DDECLTYPE_FLOAT4,    D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3},
    D3DDECL_END()
};



bool DistantLand::init() {
    if (ready) {
        return true;
    }
    if (!device) {
        return false;
    }

    LOG::logline(">> Starting Distant Land init");
    vsr.init(device);
    BSA::init();

    if (!initShader()) {
        return false;
    }

    if (!FixedFunctionShader::init(device, effectPool)) {
        return false;
    }

    if (!PostShaders::init(device)) {
        return false;
    }

    if (!initDepth()) {
        return false;
    }

    if (!initShadow()) {
        return false;
    }

    if (!initWater()) {
        return false;
    }

    if (!initLandscape()) {
        return false;
    }

    if (!initDistantStatics()) {
        return false;
    }

    if (!initGrass()) {
        return false;
    }

    MWBridge::get()->patchResolveDuringInit(&resolveDynamicVisGroups);

    LOG::logline("<< Completed Distant Land init");
    ready = true;
    isRenderCached = false;
    return true;
}

bool DistantLand::reloadShaders() {
    LOG::logline(">> Distant Land reloading");
    if (!initShader()) {
        return false;
    }

    FixedFunctionShader::release();
    if (!FixedFunctionShader::init(device, effectPool)) {
        return false;
    }

    return true;
}

static const string shaderCoreModPrefix = "XE Mod";
static const string pathCoreShaders = "Data Files\\shaders\\core\\";
static const string pathCoreMods = "Data Files\\shaders\\core-mods\\";

struct CoreModInclude : public ID3DXInclude {
    vector<string> modsFound;
    std::optional<string> testSingleMod;

    STDMETHOD(Open)(D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes) {
        string filename(pFileName), shaderPath = filename;
        bool isMod = false;
        char *buffer = nullptr;
        HANDLE h;

        // Check if it uses the core shader path prefix, if not, add the prefix
        if (filename.compare(0, pathCoreShaders.length(), pathCoreShaders) != 0) {
            shaderPath = pathCoreShaders + filename;
        }

        if (!testSingleMod) {
            // Check if this file is moddable, and if a core-mod exists, use its path
            if (filename.substr(0, shaderCoreModPrefix.length()) == shaderCoreModPrefix) {
                string modShaderPath = pathCoreMods + filename;
                if (GetFileAttributes(modShaderPath.c_str()) != INVALID_FILE_ATTRIBUTES) {
                    isMod = true;
                    shaderPath = modShaderPath;
                }
            }
        }
        else {
            // Only load the specified mod for testing, ignoring others
            if (testSingleMod.value() == filename) {
                isMod = true;
                shaderPath = pathCoreMods + filename;
            }
        }

        // Read file contents for the effect compiler
        h = CreateFile(shaderPath.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
        if (h != INVALID_HANDLE_VALUE) {
            DWORD bytesRead, bufferSize = GetFileSize(h, NULL);

            buffer = new char[bufferSize];
            ReadFile(h, buffer, bufferSize, &bytesRead, 0);
            CloseHandle(h);

            if (isMod) {
                modsFound.push_back(filename);
            }

            *ppData = buffer;
            *pBytes = bufferSize;
            return S_OK;
        }
        return E_FAIL;
    }

    STDMETHOD(Close)(LPCVOID pData) {
        char *buffer = (char*)(pData);
        delete [] buffer;
        return S_OK;
    }
};

static void logShaderError(ID3DXBuffer* errors) {
    if (errors) {
        LOG::write("!! Shader compile errors:\n");
        LOG::write(reinterpret_cast<const char*>(errors->GetBufferPointer()));
        LOG::write("\n");
        errors->Release();
    }
    LOG::flush();
}

static bool createCoreEffectWithMods(const char *name, IDirect3DDevice9* device, vector<D3DXMACRO>& features, ID3DXEffectPool *effectPool, ID3DXEffect **pEffect, bool reportMods) {
    string path = pathCoreShaders + name;
    ID3DXBuffer* errors;
    CoreModInclude includer;
    HRESULT hr;

    // Attempt to compile with core mods first
    hr = D3DXCreateEffectFromFile(device, path.c_str(), &*features.begin(), &includer, D3DXSHADER_OPTIMIZATION_LEVEL3|D3DXFX_LARGEADDRESSAWARE, effectPool, pEffect, &errors);
    if (hr == D3D_OK) {
        if (reportMods) {
            for (auto& m : includer.modsFound) {
                LOG::logline("-- Using core mod %s", m.c_str());
            }
        }
        return true;
    } else {
        LOG::logline("!! Core shader %s failed to compile with core-mods. All core-mods are disabled. Checking for errors...", name);
        StatusOverlay::setStatus("Shader core mod error. Core mods are disabled for this session. Check mgeXE.log for error details.", StatusOverlay::PriorityError);
        if (errors) {
            errors->Release();
        }
    }

    // Individually test each core mod for errors
    auto modsFound = includer.modsFound;
    for(const auto& mod : modsFound) {
        ID3DXEffect *testEffect;
        includer.testSingleMod = mod;

        hr = D3DXCreateEffectFromFile(device, path.c_str(), &*features.begin(), &includer, D3DXSHADER_OPTIMIZATION_LEVEL0|D3DXFX_LARGEADDRESSAWARE, effectPool, &testEffect, &errors);
        if (hr == D3D_OK) {
            testEffect->Release();
        }
        else {
            LOG::logline("!! Shader core mod %s%s failed to compile. Disable or remove it until it is fixed.", pathCoreMods.c_str(), mod.c_str());
            logShaderError(errors);
        }
    }

    // Fallback to compiling without core mods
    hr = D3DXCreateEffectFromFile(device, path.c_str(), &*features.begin(), 0, D3DXSHADER_OPTIMIZATION_LEVEL3|D3DXFX_LARGEADDRESSAWARE, effectPool, pEffect, &errors);
    if (hr == D3D_OK) {
        return true;
    } else {
        LOG::logline("!! Core shader %s failed to compile. Do not replace core shaders. Reinstall MGE XE.", name);
        logShaderError(errors);
    }
    return false;
}

static const D3DXMACRO macroExpFog = { "USE_EXPFOG", "" };
static const D3DXMACRO macroScattering = { "USE_SCATTERING", "" };
static const D3DXMACRO macroFilterReflection = { "FILTER_WATER_REFLECTION", "" };
static const D3DXMACRO macroDynamicRipples = { "DYNAMIC_RIPPLES", "" };
static const D3DXMACRO macroTerminator = { 0, 0 };

bool DistantLand::initShader() {
    vector<D3DXMACRO> features;
    HRESULT hr;

    // Disable exponential fog if distant land is initially off
    if (~Configuration.MGEFlags & USE_DISTANT_LAND) {
        Configuration.MGEFlags &= ~(EXP_FOG | USE_ATM_SCATTER);
    }

    // Set shader defines corresponding to required features
    if (Configuration.MGEFlags & EXP_FOG) {
        features.push_back(macroExpFog);

        // Requires exp. fog
        if (Configuration.MGEFlags & USE_ATM_SCATTER) {
            features.push_back(macroScattering);
        }
    }
    if (Configuration.MGEFlags & BLUR_REFLECTIONS) {
        features.push_back(macroFilterReflection);
    }
    if (Configuration.MGEFlags & DYNAMIC_RIPPLES) {
        features.push_back(macroDynamicRipples);
    }
    features.push_back(macroTerminator);

    if (!effectPool) {
        hr = D3DXCreateEffectPool(&effectPool);
        if (hr != D3D_OK) {
            LOG::logline("!! Effect pool creation failure");
            return false;
        }
    }

    if (!createCoreEffectWithMods("XE Main.fx", device, features, effectPool, &effect, true)) {
        return false;
    }

    ehRcpRes = effect->GetParameterByName(0, "rcpRes");
    ehShadowRcpRes = effect->GetParameterByName(0, "shadowRcpRes");
    ehWorld = effect->GetParameterByName(0, "world");
    ehView = effect->GetParameterByName(0, "view");
    ehProj = effect->GetParameterByName(0, "proj");
    ehShadowViewproj = effect->GetParameterByName(0, "shadowViewProj");
    ehVertexBlendState = effect->GetParameterByName(0, "vertexBlendState");
    ehVertexBlendPalette = effect->GetParameterByName(0, "vertexBlendPalette");
    ehAlphaRef = effect->GetParameterByName(0, "alphaRef");
    ehMaterialAlpha = effect->GetParameterByName(0, "materialAlpha");
    ehHasAlpha = effect->GetParameterByName(0, "hasAlpha");
    ehHasBones = effect->GetParameterByName(0, "hasBones");
    ehHasVCol = effect->GetParameterByName(0, "hasVCol");
    ehTex0 = effect->GetParameterByName(0, "tex0");
    ehTex1 = effect->GetParameterByName(0, "tex1");
    ehTex2 = effect->GetParameterByName(0, "tex2");
    ehTex3 = effect->GetParameterByName(0, "tex3");
    ehEyePos = effect->GetParameterByName(0, "eyePos");
    ehFootPos = effect->GetParameterByName(0, "footPos");
    ehSunCol = effect->GetParameterByName(0, "sunCol");
    ehSunAmb = effect->GetParameterByName(0, "sunAmb");
    ehSunVec = effect->GetParameterByName(0, "sunVec");
    ehSunVecView = effect->GetParameterByName(0, "sunVecView");
    ehSunPos = effect->GetParameterByName(0, "sunPos");
    ehSunVis = effect->GetParameterByName(0, "sunVis");
    ehSkyCol = effect->GetParameterByName(0, "skyCol");
    ehFogColNear = effect->GetParameterByName(0, "fogColNear");
    ehFogColFar = effect->GetParameterByName(0, "fogColFar");
    ehFogStart = effect->GetParameterByName(0, "fogStart");
    ehFogRange = effect->GetParameterByName(0, "fogRange");
    ehFogNearStart = effect->GetParameterByName(0, "nearFogStart");
    ehFogNearRange = effect->GetParameterByName(0, "nearFogRange");
    ehNearViewRange = effect->GetParameterByName(0, "nearViewRange");
    ehWindVec = effect->GetParameterByName(0, "windVec");
    ehNiceWeather = effect->GetParameterByName(0, "niceWeather");
    ehTime = effect->GetParameterByName(0, "time");

    D3DVIEWPORT9 vp;
    device->GetViewport(&vp);
    float rcpres[2] = { 1.0f / vp.Width, 1.0f / vp.Height };
    effect->SetFloatArray(ehRcpRes, rcpres, 2);
    effect->SetFloat(ehShadowRcpRes, 1.0f / Configuration.DL.ShadowResolution);

    if (!createCoreEffectWithMods("XE Shadowmap.fx", device, features, effectPool, &effectShadow, false)) {
        return false;
    }
    if (!createCoreEffectWithMods("XE Depth.fx", device, features, effectPool, &effectDepth, false)) {
        return false;
    }

    // Atmosphere scattering specific parameters
    if (Configuration.MGEFlags & USE_ATM_SCATTER) {

        ehOutscatter = effect->GetParameterByName(0, "outscatter");
        ehInscatter = effect->GetParameterByName(0, "inscatter");
        ehSkyScatterFar = effect->GetParameterByName(0, "skyScatterColFar");

        // Mark moon geometry for detection
        MWBridge::get()->markMoonNodes(kMoonTag);
    }
    else {
        ehOutscatter = 0;
        ehInscatter = 0;
        ehSkyScatterFar = 0;
    }

    // Dynamic ripples specific parameters
    if (Configuration.MGEFlags & DYNAMIC_RIPPLES) {
        ehTex4 = effect->GetParameterByName(0, "tex4");
        ehTex5 = effect->GetParameterByName(0, "tex5");
        ehRippleOrigin = effect->GetParameterByName(0, "rippleOrigin");
        ehWaveHeight = effect->GetParameterByName(0, "waveHeight");
    }

    return true;
}

bool DistantLand::initDepth() {
    HRESULT hr;
    D3DVIEWPORT9 vp;

    // Set up depth frame texture, requires its own z-buffer (my card fails to support INTZ/DF24)
    device->GetViewport(&vp);

    hr = device->CreateTexture(vp.Width, vp.Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &texDepthFrame, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create depth frame render target");
        return false;
    }

    hr = device->CreateDepthStencilSurface(vp.Width, vp.Height, D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, FALSE, &surfDepthDepth, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create depth target z-buffer");
        return false;
    }

    return true;
}

bool DistantLand::initWater() {
    HRESULT hr;
    const UINT reflRes = 1024;

    // Reflection render target
    hr = device->CreateTexture(reflRes, reflRes, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texReflection, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create reflection render target");
        return false;
    }

    // Reflection Z-buffer
    hr = device->CreateDepthStencilSurface(reflRes, reflRes, D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, TRUE, &surfReflectionZ, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create reflection Z buffer");
        return false;
    }

    // Water normals and geometry
    const int resS = (Configuration.MGEFlags & DYNAMIC_RIPPLES) ? 150 : 16;
    const int resT = (Configuration.MGEFlags & DYNAMIC_RIPPLES) ? 120 : 15;
    numWaterVerts = resS * resT + 1;
    numWaterTris = 2 * resS * resT - resS;

    hr = D3DXCreateVolumeTextureFromFile(device, "Data Files\\textures\\MGE\\water_NRM.dds", &texWater);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to load water texture");
        return false;
    }
    hr = device->CreateVertexDeclaration(WaterElem, &WaterDecl);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create water decl");
        return false;
    }
    hr = device->CreateVertexBuffer(numWaterVerts * 12, 0, 0, D3DPOOL_MANAGED, &vbWater, 0);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create water verts");
        return false;
    }
    hr = device->CreateIndexBuffer(numWaterTris * 6, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ibWater, 0);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create water indices");
        return false;
    }

    // Build radial water mesh
    D3DXVECTOR3* v;
    vbWater->Lock(0, 0, (void**)&v, 0);

    // Water plane lies at water level - 1.0 (not -4.0, which is the fog transition)
    const float dS = float(6.28318530717958647692 / resS);
    int s, t;
    float r, w = -1.0f;

    *v++ = D3DXVECTOR3(0, 0, w);
    for (t = 0; t < resT; ++t) {
        if (Configuration.MGEFlags & DYNAMIC_RIPPLES) {
            // Higher mesh density near player
            // The mesh requires density past 8192 units to cover the z discontinuity at distant land
            r = float(t) / float(resT);
            r = 9600.0f * (0.9f * powf(r, 3) + 0.1f * r);
            // Extend last ring past horizon
            if ((t+1) == resT) {
                r = 500000.0f;
            }
        } else {
            r = 4096.0f * (1.0f + t * t);
        }

        for (s = 0; s < resS; ++s) {
            *v++ = D3DXVECTOR3(r * cos(dS * s), r * sin(dS * s), w);
        }
    }

    vbWater->Unlock();

    USHORT* i;
    ibWater->Lock(0, 0, (void**)&i, 0);

    // Centre triangles
    for (s = 0; s < resS; ++s) {
        *i++ = 0;
        *i++ = 1 + s;
        *i++ = 1 + (s+1) % resS;
    }
    // Rings
    for (t = 1; t < resT; ++t) {
        for (s = 0; s < resS; ++s) {
            USHORT tbase = 1 + resS*(t-1), s2 = (s+1) % resS;
            *i++ = tbase + s;
            *i++ = resS + tbase + s;
            *i++ = tbase + s2;
            *i++ = resS + tbase+ s;
            *i++ = resS + tbase + s2;
            *i++ = tbase + s2;
        }
    }

    ibWater->Unlock();

    if (Configuration.MGEFlags & DYNAMIC_RIPPLES) {
        // Setup water simulation
        if (!initDynamicWaves()) {
            return false;
        }

        // Disable Morrowind generated ripples
        MWBridge::get()->toggleRipples(false);
    }

    return true;
}

bool DistantLand::initDynamicWaves() {
    HRESULT hr;

    hr = device->CreateTexture(waveTexResolution, waveTexResolution, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &texRain, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create rain simulation texture");
        return false;
    }
    texRain->GetSurfaceLevel(0, &surfRain);
    device->ColorFill(surfRain, 0, 0);

    hr = device->CreateTexture(waveTexResolution, waveTexResolution, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &texRipples, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create ripple simulation texture");
        return false;
    }
    texRipples->GetSurfaceLevel(0, &surfRipples);
    device->ColorFill(surfRipples, 0, 0);

    hr = device->CreateTexture(waveTexResolution, waveTexResolution, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &texRippleBuffer, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create ripple simulation texture");
        return false;
    }
    texRippleBuffer->GetSurfaceLevel(0, &surfRippleBuffer);
    device->ColorFill(surfRippleBuffer, 0, 0);

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

    void* vp;
    hr = device->CreateVertexBuffer(3 * 32, D3DUSAGE_WRITEONLY, fvfWave, D3DPOOL_DEFAULT, &vbWaveSim, 0);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create wave simulation vb");
        return false;
    }
    if (vbWaveSim->Lock(0, 0, (void**)&vp, 0) != D3D_OK) {
        LOG::logline("!! Failed to lock wave simulation vb");
        return false;
    }
    memcpy(vp, waveVertices, sizeof(waveVertices));
    vbWaveSim->Unlock();

    return true;
}

bool DistantLand::initShadow() {
    const D3DFORMAT shadowFormat = D3DFMT_R16F, shadowZFormat = D3DFMT_D24S8;
    const UINT shadowSize = Configuration.DL.ShadowResolution, cascades = 2;
    HRESULT hr;

    // The shadow texture holds a horizontal-packed shadow atlas
    hr = device->CreateTexture(cascades * shadowSize, shadowSize, 1, D3DUSAGE_RENDERTARGET, shadowFormat, D3DPOOL_DEFAULT, &texShadow, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create shadow render target");
        return false;
    }
    hr = device->CreateTexture(cascades * shadowSize, shadowSize, 1, D3DUSAGE_RENDERTARGET, shadowFormat, D3DPOOL_DEFAULT, &texSoftShadow, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create shadow render target");
        return false;
    }
    hr = device->CreateDepthStencilSurface(cascades * shadowSize, shadowSize, shadowZFormat, D3DMULTISAMPLE_NONE, 0, TRUE, &surfShadowZ, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create shadow Z buffer");
        return false;
    }
    hr = device->CreateVertexBuffer(4 * 12, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vbFullFrame, 0);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create shadow processing verts");
        return false;
    }
    hr = device->CreateVertexBuffer(14 * 12, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vbClipCube, 0);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create shadow processing verts");
        return false;
    }

    // Used to cover an entire render target of any dimension
    D3DXVECTOR3* v;
    vbFullFrame->Lock(0, 0, (void**)&v, 0);
    v[0] = D3DXVECTOR3( -1.0f, 1.0f,  1.0f);
    v[1] = D3DXVECTOR3(-1.0f, -1.0f,  1.0f);
    v[2] = D3DXVECTOR3( 1.0f,  1.0f,  1.0f);
    v[3] = D3DXVECTOR3( 1.0f, -1.0f,  1.0f);
    vbFullFrame->Unlock();

    // Used to project the view frustum in world space
    // Slightly expanded from the canonical cube to allow for rasterization and filtering
    const float u = 1.01f;
    vbClipCube->Lock(0, 0, (void**)&v, 0);
    v[0] = D3DXVECTOR3(-u,  u, 0.0f);
    v[1] = D3DXVECTOR3(-u, -u, 0.0f);
    v[2] = D3DXVECTOR3( u,  u, 0.0f);
    v[3] = D3DXVECTOR3( u, -u, 0.0f);
    v[4] = D3DXVECTOR3( u, -u, 1.0f);
    v[5] = D3DXVECTOR3(-u, -u, 0.0f);
    v[6] = D3DXVECTOR3(-u, -u, 1.0f);
    v[7] = D3DXVECTOR3(-u,  u, 0.0f);
    v[8] = D3DXVECTOR3(-u,  u, 1.0f);
    v[9] = D3DXVECTOR3( u,  u, 0.0f);
    v[10] = D3DXVECTOR3( u,  u, 1.0f);
    v[11] = D3DXVECTOR3( u, -u, 1.0f);
    v[12] = D3DXVECTOR3(-u,  u, 1.0f);
    v[13] = D3DXVECTOR3(-u, -u, 1.0f);
    vbClipCube->Unlock();

    return true;
}

bool DistantLand::initDistantStatics() {
    if (FAILED(device->CreateVertexDeclaration(StaticElem, &StaticDecl))) {
        LOG::logline("!! Failed to to create static vertex declaration");
        return false;
    }

    if (!loadDistantStatics()) {
        return false;
    }

    currentWorldSpace = nullptr;
    return true;
}

class membuf_reader {
    char* ptr;

public:
    membuf_reader(char* buf) : ptr(buf) {}

    template <typename T>
    inline void read(T* dest, size_t size) {
        memcpy((char*)dest, ptr, size);
        ptr += size;
    }

    inline char* get() {
        return ptr;
    }

    inline void advance(size_t size) {
        ptr += size;
    }
};

static size_t initDistantStaticsQT(DistantLand::WorldSpace& worldSpace, vector<DistantStatic>& distantStatics, vector<UsedDistantStatic>& uds);

bool DistantLand::loadDistantStatics() {
    DWORD unused;
    HANDLE h;

    if (GetFileAttributes("Data Files\\distantland\\statics") == INVALID_FILE_ATTRIBUTES) {
        LOG::logline("!! Distant statics have not been generated");
        LOG::flush();
        return !(Configuration.MGEFlags & USE_DISTANT_LAND);
    }

    h = CreateFile("Data Files\\distantland\\version", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    if (h == INVALID_HANDLE_VALUE) {
        LOG::logline("!! Required distant statics files are missing, regeneration required - distantland/version");
        LOG::flush();
        return false;
    }
    BYTE version = 0;
    ReadFile(h, &version, sizeof(version), &unused, 0);
    if (version != MGE_DL_VERSION) {
        LOG::logline("!! Distant statics data is from an old version and needs to be regenerated");
        LOG::flush();
        return false;
    }
    CloseHandle(h);

    h = CreateFile("Data Files\\distantland\\statics\\usage.data", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    if (h == INVALID_HANDLE_VALUE) {
        LOG::logline("!! Required distant statics files are missing, regeneration required - distantland/statics/usage.data");
        LOG::flush();
        return false;
    }

    vector<DistantStatic> distantStatics;
    size_t DistantStaticCount;
    ReadFile(h, &DistantStaticCount, 4, &unused, 0);
    distantStatics.resize(DistantStaticCount);

    HANDLE h2 = CreateFile("Data Files\\distantland\\statics\\static_meshes", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    if (h2 == INVALID_HANDLE_VALUE) {
        LOG::logline("!! Required distant statics files are missing, regeneration required - distantland/statics/static_meshes");
        LOG::flush();
        return false;
    }

    // Bright yellow error texture
    IDirect3DTexture9* errorTexture;
    device->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &errorTexture, NULL);

    D3DLOCKED_RECT yellow;
    errorTexture->LockRect(0, &yellow, NULL, 0);
    *(DWORD*)yellow.pBits = 0xffffff00;
    errorTexture->UnlockRect(0);

    // Read entire file into one big memory buffer
    DWORD file_size = GetFileSize(h2, NULL);
    auto file_buffer = std::make_unique<char[]>(file_size);
    ReadFile(h2, file_buffer.get(), file_size, &unused, NULL);
    membuf_reader reader(file_buffer.get());
    CloseHandle(h2);

    for (auto& i : distantStatics) {
        int numSubsets;
        reader.read(&numSubsets, 4);
        reader.read(&i.sphere.radius, 4);
        reader.read(&i.sphere.center, 12);
        reader.read(&i.type, 1);

        i.subsets.resize(numSubsets);
        i.aabbMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
        i.aabbMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

        for (auto& subset : i.subsets) {
            // Get bounding sphere
            reader.read(&subset.sphere.radius, 4);
            reader.read(&subset.sphere.center, 12);

            // Get AABB min and max
            reader.read(&subset.aabbMin, 12);
            reader.read(&subset.aabbMax, 12);

            // Get vertex and face count
            reader.read(&subset.verts, 4);
            reader.read(&subset.faces, 4);

            // Update parent AABB
            i.aabbMin.x = std::min(i.aabbMin.x, subset.aabbMin.x);
            i.aabbMin.y = std::min(i.aabbMin.y, subset.aabbMin.y);
            i.aabbMin.z = std::min(i.aabbMin.z, subset.aabbMin.z);
            i.aabbMax.x = std::max(i.aabbMax.x, subset.aabbMax.x);
            i.aabbMax.y = std::max(i.aabbMax.y, subset.aabbMax.y);
            i.aabbMax.z = std::max(i.aabbMax.z, subset.aabbMax.z);

            // Load mesh data
            IDirect3DVertexBuffer9* vb;
            IDirect3DIndexBuffer9* ib;
            void* lockdata;

            device->CreateVertexBuffer(subset.verts * SIZEOFSTATICVERT, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vb, 0);
            vb->Lock(0, 0, &lockdata, 0);
            reader.read(lockdata, subset.verts * SIZEOFSTATICVERT);
            vb->Unlock();

            device->CreateIndexBuffer(subset.faces * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, 0);
            ib->Lock(0, 0, &lockdata, 0);
            reader.read(lockdata, subset.faces * 6); // Morrowind nifs don't support 32 bit indices?
            ib->Unlock();

            subset.vbuffer = vb;
            subset.ibuffer = ib;

            // Texturing flags
            bool texturingFlags[2];
            reader.read(&texturingFlags, 2);
            subset.hasAlpha = texturingFlags[0];
            subset.hasUVController = texturingFlags[1];

            // Load referenced texture
            unsigned short pathsize;
            reader.read(&pathsize, 2);
            const char* texname = reader.get();
            reader.advance(pathsize);

            IDirect3DTexture9* tex = BSA::loadTexture(device, texname);
            if (!tex) {
                LOG::logline("Cannot load texture %s", texname);
                errorTexture->AddRef();
                tex = errorTexture;
            }
            subset.tex = tex;

            // Keep resource pointers for deallocation
            meshCollectionStatics.push_back(MeshResources(vb, ib, tex));
        }
    }
    file_buffer.reset();
    errorTexture->Release();


    // Texture memory reporting
    int texturesLoaded, texMemUsage;
    BSA::cacheStats(&texturesLoaded, &texMemUsage);

    LOG::logline("-- Distant static geometry memory use: %d MB", file_size / (1 << 20));
    LOG::logline("-- Distant textures loaded, %d textures", texturesLoaded);
    LOG::logline("-- Distant texture memory use: %d MB", texMemUsage);
    LOG::flush();


    // Load dynamic vis groups
    size_t dynamicVisGroupCount;
    ReadFile(h, &dynamicVisGroupCount, 4, &unused, 0);
    dynamicVisGroups.clear();

    if (dynamicVisGroupCount > 0) {
        const size_t visGroupRecordSize = 130;
        size_t visDataSize = visGroupRecordSize * dynamicVisGroupCount;
        auto visData = std::make_unique<char[]>(visDataSize);
        ReadFile(h, visData.get(), visDataSize, &unused, 0);
        membuf_reader visReader(visData.get());

        // VisGroup indexes use a 1-based index, group 0 is reserved for testing
        dynamicVisGroups.resize(dynamicVisGroupCount + 1);

        for (size_t nVisGroup = 1; nVisGroup <= dynamicVisGroupCount; ++nVisGroup) {
            DynamicVisGroup& dvg = dynamicVisGroups[nVisGroup];
            visReader.read(&dvg.source, 1);
            dvg.enabled = true;
            dvg.gameObject = nullptr;

            char id[64];
            visReader.read(&id, sizeof(id));
            dvg.id = id;

            uint8_t rangeCount;
            visReader.read(&rangeCount, sizeof(rangeCount));

            DynamicVisGroup::Range ranges[8];
            visReader.read(&ranges, sizeof(ranges));
            dvg.ranges.assign(ranges, ranges + rangeCount);
        }

        visData.reset();
    }

    // Load statics references
    const size_t UsedDistantStaticRecordSize = 34;
    const size_t UsedDistantStaticChunkCount = 250000;
    size_t worldvis_memory_use = 0;
    auto UsedDistantStaticData = std::make_unique<char[]>(UsedDistantStaticChunkCount * UsedDistantStaticRecordSize);

    mapWorldSpaces.clear();
    for (size_t nWorldSpace = 0; true; ++nWorldSpace) {
        vector<UsedDistantStatic> worldSpaceStatics;
        WorldSpace* currentWorldSpace;
        size_t UsedDistantStaticCount;

        ReadFile(h, &UsedDistantStaticCount, 4, &unused, 0);
        if (nWorldSpace != 0 && UsedDistantStaticCount == 0) {
            break;
        }

        if (nWorldSpace == 0) {
            auto iterWS = mapWorldSpaces.insert(make_pair(string(), WorldSpace())).first;
            currentWorldSpace = &iterWS->second;
            if (UsedDistantStaticCount == 0) {
                continue;
            }
        } else {
            char cellname[64];
            ReadFile(h, &cellname, 64, &unused, 0);
            auto iterWS = mapWorldSpaces.insert(make_pair(string(cellname), WorldSpace())).first;
            currentWorldSpace = &iterWS->second;
        }

        worldSpaceStatics.reserve(UsedDistantStaticCount);

        while (UsedDistantStaticCount > 0) {
            size_t staticsToRead = std::min(UsedDistantStaticChunkCount, UsedDistantStaticCount);
            UsedDistantStaticCount -= staticsToRead;

            ReadFile(h, UsedDistantStaticData.get(), staticsToRead * UsedDistantStaticRecordSize, &unused, 0);
            membuf_reader udsReader(UsedDistantStaticData.get());

            for (size_t i = 0; i < staticsToRead; ++i) {
                UsedDistantStatic NewUsedStatic;
                float yaw, pitch, roll, scale;

                udsReader.read(&NewUsedStatic.staticRef, 4);
                udsReader.read(&NewUsedStatic.visIndex, 2);
                udsReader.read(&NewUsedStatic.pos, 12);
                udsReader.read(&yaw, 4);
                udsReader.read(&pitch, 4);
                udsReader.read(&roll, 4);
                udsReader.read(&scale, 4);
                NewUsedStatic.scale = scale;

                D3DXMATRIX transmat, rotmatx, rotmaty, rotmatz, scalemat;
                D3DXMatrixTranslation(&transmat, NewUsedStatic.pos.x, NewUsedStatic.pos.y, NewUsedStatic.pos.z);
                D3DXMatrixRotationX(&rotmatx, -yaw);
                D3DXMatrixRotationY(&rotmaty, -pitch);
                D3DXMatrixRotationZ(&rotmatz, -roll);
                D3DXMatrixScaling(&scalemat, scale, scale, scale);

                const DistantStatic* stat = &distantStatics[NewUsedStatic.staticRef];
                NewUsedStatic.transform = scalemat * rotmatz * rotmaty * rotmatx * transmat;
                NewUsedStatic.sphere = NewUsedStatic.GetBoundingSphere(stat->sphere);
                NewUsedStatic.box = NewUsedStatic.GetBoundingBox(stat->aabbMin, stat->aabbMax);

                worldSpaceStatics.push_back(NewUsedStatic);
            }
        }

        worldvis_memory_use += initDistantStaticsQT(*currentWorldSpace, distantStatics, worldSpaceStatics);
    }

    CloseHandle(h);

    // Log approximate memory use
    LOG::logline("-- Distant worldspaces memory use: %d MB", worldvis_memory_use / (1 << 20));

    return true;
}

static size_t initDistantStaticsQT(DistantLand::WorldSpace& worldSpace, vector<DistantStatic>& distantStatics, vector<UsedDistantStatic>& uds) {
    // Initialize quadtrees
    worldSpace.NearStatics = std::make_unique<QuadTree>();
    worldSpace.FarStatics = std::make_unique<QuadTree>();
    worldSpace.VeryFarStatics = std::make_unique<QuadTree>();
    worldSpace.GrassStatics = std::make_unique<QuadTree>();
    QuadTree* NQTR = worldSpace.NearStatics.get();
    QuadTree* FQTR = worldSpace.FarStatics.get();
    QuadTree* VFQTR = worldSpace.VeryFarStatics.get();
    QuadTree* GQTR = worldSpace.GrassStatics.get();

    // Calclulate optimal initial quadtree size
    D3DXVECTOR2 aabbMax = D3DXVECTOR2(-FLT_MAX, -FLT_MAX);
    D3DXVECTOR2 aabbMin = D3DXVECTOR2(FLT_MAX, FLT_MAX);

    // Find xyz bounds
    for (const auto& i : uds) {
        float x = i.pos.x, y = i.pos.y, r = i.sphere.radius;

        aabbMax.x = std::max(x + r, aabbMax.x);
        aabbMax.y = std::max(y + r, aabbMax.y);
        aabbMin.x = std::min(aabbMin.x, x - r);
        aabbMin.y = std::min(aabbMin.y, y - r);
    }

    size_t total_instances = 0;
    float box_size = std::max(aabbMax.x - aabbMin.x, aabbMax.y - aabbMin.y);
    D3DXVECTOR2 box_center = 0.5 * (aabbMax + aabbMin);

    NQTR->SetBox(box_size, box_center);
    FQTR->SetBox(box_size, box_center);
    VFQTR->SetBox(box_size, box_center);
    GQTR->SetBox(box_size, box_center);

    for (const auto& i : uds) {
        DistantStatic* stat = &distantStatics[i.staticRef];
        QuadTree* targetQTR;

        // Use post-transform (include scale) radius
        float radius = i.sphere.radius;

        // Buildings are treated as larger objects, as they are typically
        // smaller component meshes combined to make a single building
        if (stat->type == STATIC_BUILDING) {
            radius *= 2.0f;
        }

        // Select quadtree to place object in
        switch (stat->type) {
        case STATIC_AUTO:
        case STATIC_TREE:
        case STATIC_BUILDING:
            if (radius <= Configuration.DL.FarStaticMinSize) {
                targetQTR = NQTR;
            } else if (radius <= Configuration.DL.VeryFarStaticMinSize) {
                targetQTR = FQTR;
            } else {
                targetQTR = VFQTR;
            }
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
        for (auto& s : stat->subsets) {
            BoundingSphere boundSphere;
            BoundingBox boundBox;

            if (stat->type == STATIC_BUILDING) {
                // Use model bound so that all building parts have coherent visibility
                boundSphere = i.sphere;
                boundBox = i.box;
            } else {
                // Use individual mesh bounds
                boundSphere = i.GetBoundingSphere(s.sphere);
                boundBox = i.GetBoundingBox(s.aabbMin, s.aabbMax);
            }

            auto mesh = targetQTR->AddMesh(
                boundSphere,
                boundBox,
                i.transform,
                s.hasAlpha,
                s.hasUVController,
                s.tex,
                s.verts,
                s.vbuffer,
                s.faces,
                s.ibuffer
            );
            if (i.visIndex > 0) {
                DistantLand::dynamicVisGroups[i.visIndex].references.push_back(mesh);
            }
        }

        total_instances += stat->subsets.size();
    }

    NQTR->Optimize();
    NQTR->CalcVolume();
    FQTR->Optimize();
    FQTR->CalcVolume();
    VFQTR->Optimize();
    VFQTR->CalcVolume();
    GQTR->Optimize();
    GQTR->CalcVolume();

    // Return total memory use of leaves only, non-leaf nodes barely use much memory
    return total_instances * sizeof(QuadTreeMesh);
}

bool DistantLand::initLandscape() {
    HRESULT hr;

    hr = device->CreateVertexDeclaration(LandElem, &LandDecl);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to to create world vertex declaration");
        return false;
    }

    if (GetFileAttributes("Data Files\\distantland\\world") == INVALID_FILE_ATTRIBUTES) {
        LOG::logline("!! Distant land files have not been generated");
        LOG::flush();
        return !(Configuration.MGEFlags & USE_DISTANT_LAND);
    }

    hr = D3DXCreateTextureFromFileEx(device, "Data Files\\distantland\\world.dds", 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &texWorldColour);
    if (hr != D3D_OK) {
        LOG::logline("!! Could not load world texture for distant land - distantland/world.dds");
        LOG::flush();
        return false;
    }

    hr = D3DXCreateTextureFromFileEx(device, "Data Files\\distantland\\world_n.dds", 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &texWorldNormals);
    if (hr != D3D_OK) {
        LOG::logline("!! Could not load world normal map texture for distant land - distantland/world_n.dds");
        LOG::flush();
        return false;
    }

    hr = D3DXCreateTextureFromFileEx(device, "Data Files\\textures\\MGE\\world_detail.dds", 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &texWorldDetail);
    if (hr != D3D_OK) {
        LOG::logline("!! Could not load world detail texture for distant land - textures/MGE/world_detail.dds");
        LOG::flush();
        return false;
    }

    LOG::logline("-- Landscape textures loaded");

    HANDLE file = CreateFile("Data Files\\distantland\\world", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    if (file == INVALID_HANDLE_VALUE) {
        return false;
    }

    DWORD file_size = GetFileSize(file, NULL);
    DWORD mesh_count, unused;
    ReadFile(file, &mesh_count, 4, &unused, 0);

    vector<LandMesh> meshesLand;
    meshesLand.resize(mesh_count);

    if (!meshesLand.empty()) {
        D3DXVECTOR2 qtmin(FLT_MAX, FLT_MAX), qtmax(-FLT_MAX, -FLT_MAX);
        D3DXMATRIX world;
        D3DXMatrixIdentity(&world);

        // Load meshes and calculate max size of quadtree
        for (auto& i : meshesLand) {
            ReadFile(file, &i.sphere.radius, 4, &unused,0);
            ReadFile(file, &i.sphere.center, 12, &unused,0);

            D3DXVECTOR3 boxMin, boxMax;
            ReadFile(file, &boxMin, 12, &unused, 0);
            ReadFile(file, &boxMax, 12, &unused, 0);
            i.box.Set(boxMin, boxMax);

            ReadFile(file, &i.verts, 4, &unused, 0);
            ReadFile(file, &i.faces, 4, &unused, 0);

            bool large = (i.verts > 0xFFFF || i.faces > 0xFFFF);
            IDirect3DVertexBuffer9* vb;
            IDirect3DIndexBuffer9* ib;
            void* lockdata;

            device->CreateVertexBuffer(i.verts * SIZEOFLANDVERT, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vb, 0);
            vb->Lock(0, 0, &lockdata, 0);
            ReadFile(file, lockdata, i.verts * SIZEOFLANDVERT, &unused, 0);
            vb->Unlock();

            device->CreateIndexBuffer(i.faces * (large ? 12 : 6), D3DUSAGE_WRITEONLY, large ? D3DFMT_INDEX32 : D3DFMT_INDEX16, D3DPOOL_DEFAULT, &ib, 0);
            ib->Lock(0, 0, &lockdata, 0);
            ReadFile(file, lockdata, i.faces * (large ? 12 : 6), &unused, 0);
            ib->Unlock();

            i.vbuffer = vb;
            i.ibuffer = ib;

            qtmin.x = std::min(qtmin.x, i.sphere.center.x - i.sphere.radius);
            qtmin.y = std::min(qtmin.y, i.sphere.center.y - i.sphere.radius);
            qtmax.x = std::max(qtmax.x, i.sphere.center.x + i.sphere.radius);
            qtmax.y = std::max(qtmax.y, i.sphere.center.y + i.sphere.radius);
        }

        LandQuadTree.SetBox(std::max(qtmax.x - qtmin.x, qtmax.y - qtmin.y), 0.5 * (qtmax + qtmin));

        // Add meshes to the quadtree
        for (auto& i : meshesLand) {
            meshCollectionLand.push_back(MeshResources(i.vbuffer, i.ibuffer, 0));
            LandQuadTree.AddMesh(i.sphere, i.box, world, false, false, texWorldColour, i.verts, i.vbuffer, i.faces, i.ibuffer);
        }
    }

    CloseHandle(file);
    LandQuadTree.CalcVolume();

    // Log approximate memory use
    LOG::logline("-- Distant landscape memory use: %d MB", file_size / (1 << 20));

    return true;
}

bool DistantLand::initGrass() {
    HRESULT hr;

    hr = device->CreateVertexDeclaration(GrassElem, &GrassDecl);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create grass decl");
        return false;
    }

    hr = device->CreateVertexBuffer(MaxGrassElements * GrassInstStride, D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vbGrassInstances, NULL);
    if (hr != D3D_OK) {
        LOG::logline("!! Failed to create grass instance buffer");
        return false;
    }

    return true;
}

void DistantLand::release() {
    if (!ready) {
        return;
    }

    LOG::logline("-- Renderer unloading");

    recordMW.clear();
    recordSky.clear();

    PostShaders::release();
    FixedFunctionShader::release();

    mapWorldSpaces.clear();

    for (auto& iM : meshCollectionStatics) {
        iM.vb->Release();
        iM.ib->Release();
        iM.tex->Release();
    }
    meshCollectionStatics.clear();

    LandQuadTree.Clear();
    for (auto& iM : meshCollectionLand) {
        iM.vb->Release();
        iM.ib->Release();
        // A shared texture is used for land, and is released below
    }
    meshCollectionLand.clear();

    if (texWorldColour) {
        texWorldColour->Release();
        texWorldColour = nullptr;
        texWorldNormals->Release();
        texWorldNormals = nullptr;
        texWorldDetail->Release();
        texWorldDetail = nullptr;
    }

    BSA::clearTextureCache();

    if (Configuration.MGEFlags & DYNAMIC_RIPPLES) {
        surfRain->Release();
        surfRain = nullptr;
        texRain->Release();
        texRain = nullptr;
        surfRipples->Release();
        surfRipples = nullptr;
        texRipples->Release();
        texRipples = nullptr;
        surfRippleBuffer->Release();
        surfRippleBuffer = nullptr;
        texRippleBuffer->Release();
        texRippleBuffer = nullptr;
        vbWaveSim->Release();
        vbWaveSim = nullptr;
    }

    LandDecl->Release();
    LandDecl = nullptr;
    StaticDecl->Release();
    StaticDecl = nullptr;
    WaterDecl->Release();
    WaterDecl = nullptr;
    GrassDecl->Release();
    GrassDecl = nullptr;

    texShadow->Release();
    texShadow = nullptr;
    texSoftShadow->Release();
    texSoftShadow = nullptr;
    surfShadowZ->Release();
    surfShadowZ = nullptr;

    texWater->Release();
    texWater = nullptr;
    texReflection->Release();
    texReflection = nullptr;
    surfReflectionZ->Release();
    surfReflectionZ = nullptr;
    vbWater->Release();
    vbWater = nullptr;
    ibWater->Release();
    ibWater = nullptr;
    vbGrassInstances->Release();
    vbGrassInstances = nullptr;
    vbFullFrame->Release();
    vbFullFrame = nullptr;
    vbClipCube->Release();
    vbClipCube = nullptr;

    texDepthFrame->Release();
    texDepthFrame = nullptr;
    surfDepthDepth->Release();
    surfDepthDepth = nullptr;

    effectPool->Release();
    effectPool = nullptr;
    effectShadow->Release();
    effectShadow = nullptr;
    effectDepth->Release();
    effectDepth = nullptr;
    effect->Release();
    effect = nullptr;

    LOG::logline("-- Renderer unloaded");
    LOG::flush();

    fogNearEnd = 0;
    device = nullptr;
    ready = false;
}
