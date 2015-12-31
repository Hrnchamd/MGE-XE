
#include "mged3d8device.h"
#include "proxydx/d3d8texture.h"
#include "proxydx/d3d8surface.h"

#include <algorithm>
#include "mgeversion.h"
#include "configuration.h"
#include "distantland.h"
#include "mwbridge.h"
#include "statusoverlay.h"
#include "userhud.h"
#include "videobackground.h"

static int sceneCount;
static bool rendertargetNormal, isHUDready;
static bool isMainView, isStencilScene, stage0Complete, isFrameComplete, isHUDComplete;
static bool isWaterMaterial, waterDrawn;

static bool zoomSensSaved;
static float zoomSensX, zoomSensY;
static float crosshairTimeout;

static RenderedState rs;
static FragmentState frs;
static LightState lightrs;

static bool detectMenu(const D3DMATRIX* m);
static void captureRenderState(D3DRENDERSTATETYPE a, DWORD b);
static void captureFragmentRenderState(DWORD a, D3DTEXTURESTAGESTATETYPE b, DWORD c);
static void captureTransform(D3DTRANSFORMSTATETYPE a, const D3DMATRIX *b);
static void captureLight(DWORD a, const D3DLIGHT8 *b);
static void captureMaterial(const D3DMATERIAL8 *a);
static float calcFPS();



MGEProxyDevice::MGEProxyDevice(IDirect3DDevice9 *real, ProxyD3D *d3d) : ProxyDevice(real, d3d)
{
    // Initialize state here, as the device is released and recreated on fullscreen Alt-Tab
    sceneCount = -1;
    rendertargetNormal = true;
    isHUDready = false;
    isMainView = isStencilScene = stage0Complete = isFrameComplete = isHUDComplete = false;
    isWaterMaterial = waterDrawn = false;

    Configuration.Zoom.zoom = 1.0;
    Configuration.Zoom.rate = 0;
    Configuration.Zoom.rateTarget = 0;

    // Initialize state recorder to D3D defaults
    memset(&rs, 0, sizeof(rs));
    rs.zWrite = true;
    rs.cullMode = D3DCULL_CCW;
    rs.useLighting = true;
    rs.matSrcDiffuse = D3DMCS_COLOR1;
    rs.matSrcEmissive = D3DMCS_MATERIAL;

    memset(&frs, 0, sizeof(frs));
    for(FragmentState::Stage *s = &frs.stage[0]; s != &frs.stage[8]; ++s)
    {
        s->colorOp = D3DTOP_DISABLE;
        s->alphaOp = D3DTOP_SELECTARG1;
        s->colorArg1 = s->alphaArg1 = D3DTA_TEXTURE;
        s->colorArg2 = s->alphaArg2 = D3DTA_CURRENT;
        s->colorArg0 = s->alphaArg0 = s->resultArg = D3DTA_CURRENT;
    }

    lightrs.lights.clear();
    lightrs.active.clear();
}

// Present - End of MW frame
// MGE end of frame processing
HRESULT _stdcall MGEProxyDevice::Present(const RECT *a, const RECT *b, HWND c, const RGNDATA *d)
{
    DECLARE_MWBRIDGE

    // Load Morrowind's dynamic memory pointers
    if(!mwBridge->IsLoaded() && mwBridge->CanLoad())
    {
        mwBridge->Load();
        mwBridge->disableScreenshotFunc();
        mwBridge->markWaterNode(99999.0f);
    }

    if(mwBridge->IsLoaded())
    {
        if(Configuration.Force3rdPerson && DistantLand::ready)
        {
            // Set 3rd person camera
            D3DXVECTOR3 *camera = mwBridge->PCam3Offset();
            if(camera)
            {
                camera->x = Configuration.Offset3rdPerson.x;
                camera->y = Configuration.Offset3rdPerson.y;
                camera->z = Configuration.Offset3rdPerson.z;
            }
        }

        if(Configuration.CrosshairAutohide && !mwBridge->IsLoadScreen())
        {
            // Update crosshair visibility
            float t = mwBridge->simulationTime();

            // Turn on if Morrowind ray cast picks up a target
            if(mwBridge->getPlayerTarget())
                crosshairTimeout = t + 1.5;

            // Turn on short duration if the player requires aim
            if(mwBridge->isPlayerCasting() || mwBridge->isPlayerAimingWeapon())
                crosshairTimeout = t + 0.5;

            // Turn off in menu mode
            if(mwBridge->IsMenu())
                crosshairTimeout = t;

            // Allow manual toggle of crosshair to work again from 0.5 seconds after timeout
            if(t < crosshairTimeout + 0.5)
                mwBridge->SetCrosshairEnabled(t < crosshairTimeout);
        }

        if(Configuration.Zoom.rateTarget != 0 && !mwBridge->IsMenu())
        {
            // Update zoom controller
            Configuration.Zoom.rate += 0.25 * Configuration.Zoom.rateTarget * mwBridge->frameTime();
            if(Configuration.Zoom.rate / Configuration.Zoom.rateTarget > 1.0)
                Configuration.Zoom.rate = Configuration.Zoom.rateTarget;

            Configuration.Zoom.zoom += Configuration.Zoom.rate * mwBridge->frameTime();
            Configuration.Zoom.zoom = std::max(1.0f, Configuration.Zoom.zoom);
            Configuration.Zoom.zoom = std::min(Configuration.Zoom.zoom, 8.0f);
        }

        float *mwSens = mwBridge->getMouseSensitivityYX();
        if((Configuration.MGEFlags & ZOOM_ASPECT) && !mwBridge->IsMenu())
        {
            // Adjust sensitivity to accommodate zoom level
            if(!zoomSensSaved)
            {
                zoomSensY = mwSens[0];
                zoomSensX = mwSens[1];
                zoomSensSaved = true;
            }
            mwSens[0] = zoomSensY / Configuration.Zoom.zoom;
            mwSens[1] = zoomSensX / Configuration.Zoom.zoom;
        }
        else if(zoomSensSaved)
        {
            // Restore unzoomed sensitivity
            mwSens[0] = zoomSensY;
            mwSens[1] = zoomSensX;
            zoomSensSaved = false;
        }

        // Main menu background video
        VideoPatch::monitor(realDevice);
    }

    // Reset scene identifiers
    sceneCount = -1;
    stage0Complete = false;
    waterDrawn = false;
    isFrameComplete = false;
    isHUDComplete = false;

    return ProxyDevice::Present(a, b, c, d);
}

// SetRenderTarget
// Remember if MW is rendering to back buffer
HRESULT _stdcall MGEProxyDevice::SetRenderTarget(IDirect3DSurface8 *a, IDirect3DSurface8 *b)
{
    if(a)
    {
        IDirect3DSurface9 *back;
        realDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back);
        rendertargetNormal = (static_cast<ProxySurface *>(a)->realSurface == back);
        back->Release();
    }

    return ProxyDevice::SetRenderTarget(a, b);
}

// BeginScene - Multiple scenes per frame, non-alpha / 2x stencil / post-stencil redraw / alpha / 1st person / UI
// Fogging needs to be set for Morrowind rendering at start of scene
HRESULT _stdcall MGEProxyDevice::BeginScene()
{
    DECLARE_MWBRIDGE

    HRESULT hr = ProxyDevice::BeginScene();
    if(hr != D3D_OK)
        return hr;

    if(mwBridge->IsLoaded() && rendertargetNormal)
    {
        if(!isHUDready)
        {
            // Initialize HUD
            StatusOverlay::init(realDevice);
            StatusOverlay::setStatus(XE_VERSION_STRING);
            MGEhud::init(realDevice);

            // Set scaling on Morrowind's UI system
            if(Configuration.UIScale != 1.0f)
                mwBridge->setUIScale(Configuration.UIScale);

            isHUDready = true;
        }

        if(isMainView)
        {
            // Track scene count here in BeginSene
            // isMainView is not always valid at EndScene if Morrowind draws sunglare
            ++sceneCount;

            // Set any custom FOV
            if(sceneCount == 0 && Configuration.ScreenFOV > 0)
                mwBridge->SetFOV(Configuration.ScreenFOV);

            if(!DistantLand::ready)
            {
                if(DistantLand::init(realDevice))
                {
                    // Initially force view distance to max, required for full extent shadows and grass
                    if(Configuration.MGEFlags & USE_DISTANT_LAND)
                        mwBridge->SetViewDistance(7168.0);
                }
                else
                {
                    StatusOverlay::setStatus("Serious error. Check mgeXE.log for details.");
                }
            }
        }
        else
        {
            // UI scene, apply post-process if there was anything drawn before it
            // Race menu will render an extra scene past this point
            if(DistantLand::ready && sceneCount > 0 && !isFrameComplete)
                DistantLand::postProcess();

            isFrameComplete = true;
        }
    }

    return D3D_OK;
}

// EndScene - Multiple scenes per frame, non-alpha / 2x stencil / post-stencil redraw / alpha / 1st person / UI
// MGE intercepts first scene to draw distant land before it finishes, others it applies shadows to
HRESULT _stdcall MGEProxyDevice::EndScene()
{
    if(DistantLand::ready && rendertargetNormal)
    {
        // The following Morrowind scenes get past the filters:
        // ~ Opaque meshes, plus alpha meshes with 'No Sorter' property (which should use alpha test)
        // ~ If stencil shadows are active, then shadow casters are deferred to be drawn in a scene after
        //    shadows are fully applied to avoid self-shadowing problems with simplified shadow meshes
        // ~ If any alpha meshes are visible, they are sorted and drawn in another scene (except those with 'No Sorter' property)
        // ~ If 1st person or sunglare is visible, they are drawn in another scene after a Z clear
        if(sceneCount == 0)
        {
            // Edge case, render distant land even if Morrowind has culled everything
            if(!stage0Complete)
            {
                DistantLand::renderStage0();
                stage0Complete = true;
            }

            // Opaque features
            DistantLand::renderStage1();

            // Blend close objects over distant land
            DistantLand::renderStageBlend();
        }
        else if(!isFrameComplete)
        {
            // Everything else except UI
            DistantLand::renderStage2();

            // Draw water if the Morrowind water plane doesn't appear in view
            // it may be too distant or stencil scene order is non-normative
            if(!waterDrawn && !isStencilScene)
            {
                DistantLand::renderStageWater();
                waterDrawn = true;
            }
        }
    }

    if(isFrameComplete && isHUDready && !isHUDComplete)
    {
        // Render user hud
        MGEhud::draw();

        // Render status overlay
        StatusOverlay::setFPS(calcFPS());
        StatusOverlay::show(realDevice);

        isHUDComplete = true;
    }

    return ProxyDevice::EndScene();
}

// Clear - Occurs at start of frame, and also a z-clear before rendering 1st person and sunglare
// Skybox mesh doesn't extend over whole background; cleared background colour is visible at horizon
HRESULT _stdcall MGEProxyDevice::Clear(DWORD a, const D3DRECT *b, DWORD c, D3DCOLOR d, float e, DWORD f)
{
    DistantLand::setHorizonColour(d);
    return ProxyDevice::Clear(a, b, c, d, e, f);
}

// SetTransform
// Projection needs modifying to allow room for distant land
HRESULT _stdcall MGEProxyDevice::SetTransform(D3DTRANSFORMSTATETYPE a, const D3DMATRIX *b)
{
    captureTransform(a, b);

    if(rendertargetNormal)
    {
        if(a == D3DTS_VIEW)
        {
            // Check for UI view
            isMainView = !detectMenu(b);
        }
        else if(a == D3DTS_PROJECTION)
        {
            // Only screw with main scene projection
            if(isMainView)
            {
                D3DXMATRIX proj = *b;
                DistantLand::setProjection(&proj);

                if(Configuration.MGEFlags & ZOOM_ASPECT)
                {
                    proj._11 *= Configuration.Zoom.zoom;
                    proj._22 *= Configuration.Zoom.zoom;
                }

                return ProxyDevice::SetTransform(a, &proj);
            }
        }
    }

    return ProxyDevice::SetTransform(a, b);
}

// SetMaterial
// Check for materials marked for hiding
HRESULT _stdcall MGEProxyDevice::SetMaterial(const D3DMATERIAL8 *a)
{
    captureMaterial(a);
    isWaterMaterial = (a->Power == 99999.0f);

    return ProxyDevice::SetMaterial(a);
}

// SetLight
// Capture what the sun is doing
HRESULT _stdcall MGEProxyDevice::SetLight(DWORD a, const D3DLIGHT8 *b)
{
    captureLight(a, b);

    // Exterior sunlight/interior "sun" appears to always be light 6
    if(a == 6 && DistantLand::ready)
        DistantLand::setSunLight(b);

    return ProxyDevice::SetLight(a, b);
}

// SetRenderState
// Ignore Morrowind fog settings, and run stage 0 rendering after lighting setup
HRESULT _stdcall MGEProxyDevice::SetRenderState(D3DRENDERSTATETYPE a, DWORD b)
{
    captureRenderState(a, b);

    if(a == D3DRS_FOGVERTEXMODE || a == D3DRS_FOGTABLEMODE)
        return D3D_OK;
    if((Configuration.MGEFlags & USE_DISTANT_LAND) && (a == D3DRS_FOGSTART || a == D3DRS_FOGEND))
        return D3D_OK;
    if(a == D3DRS_STENCILENABLE)
        isStencilScene = b;

    // Ambient is the final setting in Morrowind light setup, directly after sky rendering
    // Ignore pure white ambient, most likely to be menu mode setting
    if(a == D3DRS_AMBIENT && b != 0xffffffff)
    {
        // Ambient is also never set properly when high enough outside that Morrowind renders nothing
        // Avoid changing ambient to pure white in this case
        RGBVECTOR amb = D3DCOLOR(b);
        DistantLand::setAmbientColour(amb);
        lightrs.globalAmbient.r = amb.r; lightrs.globalAmbient.g = amb.g; lightrs.globalAmbient.b = amb.b;

        if(DistantLand::ready && !stage0Complete && sceneCount == 0)
        {
            // At this point, only the sky is rendered
            ProxyDevice::SetRenderState(a, b);
            DistantLand::renderStage0();
            stage0Complete = true;
        }
    }

    return ProxyDevice::SetRenderState(a, b);
}

// SetTextureStageState
// Override some sampler options
HRESULT _stdcall MGEProxyDevice::SetTextureStageState(DWORD a, D3DTEXTURESTAGESTATETYPE b, DWORD c)
{
    captureFragmentRenderState(a, b, c);

    // Sampler overrides
    // Note that DX8 had sampling state bound to texture stages instead of samplers
    if(a == 0)
    {
        if(b == D3DTSS_MINFILTER && c == D3DTEXF_LINEAR)
            return realDevice->SetSamplerState(0, D3DSAMP_MINFILTER, Configuration.ScaleFilter);

        if(b == D3DTSS_MIPMAPLODBIAS && Configuration.LODBias)
            return realDevice->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, *(DWORD *)&Configuration.LODBias);
    }

    return ProxyDevice::SetTextureStageState(a, b, c);
}

// DrawIndexedPrimitive - Where all the drawing happens
// Inspect draw calls for re-use later
HRESULT _stdcall MGEProxyDevice::DrawIndexedPrimitive(D3DPRIMITIVETYPE a, UINT b, UINT c, UINT d, UINT e)
{
    // Allow distant land to inspect draw calls
    if(DistantLand::ready && rendertargetNormal && isMainView && !isStencilScene)
    {
        rs.primType = a; rs.baseIndex = baseVertexIndex; rs.minIndex = b; rs.vertCount = c; rs.startIndex = d; rs.primCount = e;

        if(isWaterMaterial)
        {
            // Call distant land instead of drawing water grid
            if(!waterDrawn)
            {
                DistantLand::renderStageWater();
                waterDrawn = true;
            }
            return D3D_OK;
        }
        else
        {
            // Let distant land record call and skip if signalled
            if(!DistantLand::inspectIndexedPrimitive(sceneCount, &rs, &frs, &lightrs))
                return D3D_OK;
        }
    }

    return ProxyDevice::DrawIndexedPrimitive(a, b, c, d, e);
}

// Release - Free all resources when refcount hits 0
ULONG _stdcall MGEProxyDevice::Release()
{
    ULONG r = ProxyDevice::Release();

    if(r == 0)
    {
        DistantLand::release();
        MGEhud::release();
        StatusOverlay::release();
    }

    return r;
}

// --------------------------------------------------------

// detectMenu
// detects if view matrix is for UI / load bars
// the projection matrix is never set to ortho, making it unusable for detection
bool detectMenu(const D3DMATRIX* m)
{
    if(m->_41 != 0.0f || !(m->_42 == 0.0f || m->_42 == -600.0f) || m->_43 != 0.0f)
        return false;

    if((m->_11 == 0.0f || m->_11 == 1.0f) && m->_12 == 0.0f && (m->_13 == 0.0f || m->_13 == 1.0f) &&
        m->_21 == 0.0f && (m->_22 == 0.0f || m->_22 == 1.0f) && (m->_23 == 0.0f || m->_23 == 1.0f) &&
        (m->_31 == 0.0f || m->_31 == 1.0f) && (m->_32 == 0.0f || m->_32 == 1.0f) && m->_33 == 0.0f)
        return true;

    return false;
}

// --------------------------------------------------------
// State recording

HRESULT _stdcall MGEProxyDevice::SetTexture(DWORD a, IDirect3DBaseTexture8 *b)
{
    if(a == 0) { rs.texture = b ? static_cast<ProxyTexture*>(b)->realTexture : NULL; }
    return ProxyDevice::SetTexture(a, b);
}

HRESULT _stdcall MGEProxyDevice::SetVertexShader(DWORD a)
{
    rs.fvf = a;
    return ProxyDevice::SetVertexShader(a);
}

HRESULT _stdcall MGEProxyDevice::SetStreamSource(UINT a, IDirect3DVertexBuffer8 *b, UINT c)
{
    if(a == 0) { rs.vb = (IDirect3DVertexBuffer9*)b; rs.vbOffset = 0; rs.vbStride = c; }
    return ProxyDevice::SetStreamSource(a, b, c);
}

HRESULT _stdcall MGEProxyDevice::SetIndices(IDirect3DIndexBuffer8 *a, UINT b)
{
    rs.ib = (IDirect3DIndexBuffer9*)a;
    return ProxyDevice::SetIndices(a, b);
}

HRESULT _stdcall MGEProxyDevice::LightEnable(DWORD a, BOOL b)
{
    if(b)
    {
        if(std::find(lightrs.active.begin(), lightrs.active.end(), a) == lightrs.active.end())
            lightrs.active.push_back(a);
    }
    else
    {
        if(std::remove(lightrs.active.begin(), lightrs.active.end(), a) != lightrs.active.end())
            lightrs.active.pop_back();
    }
    return ProxyDevice::LightEnable(a, b);
}

void captureRenderState(D3DRENDERSTATETYPE a, DWORD b)
{
    switch(a)
    {
        case D3DRS_VERTEXBLEND: rs.vertexBlendState = b; break;
        case D3DRS_ZWRITEENABLE: rs.zWrite = b; break;
        case D3DRS_CULLMODE: rs.cullMode = b; break;
        case D3DRS_ALPHABLENDENABLE: rs.blendEnable = (BYTE)b; break;
        case D3DRS_SRCBLEND: rs.srcBlend = (BYTE)b; break;
        case D3DRS_DESTBLEND: rs.destBlend = (BYTE)b; break;
        case D3DRS_ALPHATESTENABLE: rs.alphaTest = (BYTE)b; break;
        case D3DRS_ALPHAFUNC: rs.alphaFunc = (BYTE)b; break;
        case D3DRS_ALPHAREF: rs.alphaRef = (BYTE)b; break;

        case D3DRS_LIGHTING: rs.useLighting = (BYTE)b; break;
        case D3DRS_DIFFUSEMATERIALSOURCE: rs.matSrcDiffuse = (BYTE)b; break;
        case D3DRS_EMISSIVEMATERIALSOURCE: rs.matSrcEmissive = (BYTE)b; break;
    }
}

void captureFragmentRenderState(DWORD a, D3DTEXTURESTAGESTATETYPE b, DWORD c)
{
    FragmentState::Stage *s = &frs.stage[a];

    switch(b)
    {
        case D3DTSS_COLOROP: s->colorOp = (BYTE)c; break;
        case D3DTSS_COLORARG1: s->colorArg1 = (BYTE)c; break;
        case D3DTSS_COLORARG2: s->colorArg2 = (BYTE)c; break;
        case D3DTSS_ALPHAOP: s->alphaOp = (BYTE)c; break;
        case D3DTSS_ALPHAARG1: s->alphaArg1 = (BYTE)c; break;
        case D3DTSS_ALPHAARG2: s->alphaArg2 = (BYTE)c; break;
        case D3DTSS_BUMPENVMAT00: s->bumpEnvMat[0][0] = reinterpret_cast<float&>(c); break;
        case D3DTSS_BUMPENVMAT01: s->bumpEnvMat[0][1] = reinterpret_cast<float&>(c); break;
        case D3DTSS_BUMPENVMAT10: s->bumpEnvMat[1][0] = reinterpret_cast<float&>(c); break;
        case D3DTSS_BUMPENVMAT11: s->bumpEnvMat[1][1] = reinterpret_cast<float&>(c); break;
        case D3DTSS_TEXCOORDINDEX: s->texcoordIndex = c; break;
        case D3DTSS_BUMPENVLSCALE: s->bumpLumiScale = reinterpret_cast<float&>(c); break;
        case D3DTSS_BUMPENVLOFFSET: s->bumpLumiBias = reinterpret_cast<float&>(c); break;
        case D3DTSS_TEXTURETRANSFORMFLAGS: s->texTransformFlags = c; break;
        case D3DTSS_COLORARG0: s->colorArg0 = (BYTE)c; break;
        case D3DTSS_ALPHAARG0: s->alphaArg0 = (BYTE)c; break;
        case D3DTSS_RESULTARG: s->resultArg = (BYTE)c; break;
    }
}

void captureTransform(D3DTRANSFORMSTATETYPE a, const D3DMATRIX *b)
{
    switch(a)
    {
        case D3DTS_WORLDMATRIX(0): rs.worldTransforms[0] = *b; break;
        case D3DTS_WORLDMATRIX(1): rs.worldTransforms[1] = *b; break;
        case D3DTS_WORLDMATRIX(2): rs.worldTransforms[2] = *b; break;
        case D3DTS_WORLDMATRIX(3): rs.worldTransforms[3] = *b; break;
    }
}

void captureLight(DWORD a, const D3DLIGHT8 *b)
{
    // Morrowind uses non-contigous light IDs up to a large number (>512)
    LightState::Light *light = &lightrs.lights[a];

    // Copy values relevant to Morrowind
    // i.e. Morrowind has no spotlights and always sets range to FLT_MAX
    // The only light source with ambient is sunlight
    light->type = b->Type;
    light->diffuse = b->Diffuse;

    if(b->Type == D3DLIGHT_POINT)
    {
        light->position = b->Position;
        light->falloff.x = b->Attenuation0;
        light->falloff.y = b->Attenuation1;
        light->falloff.z = b->Attenuation2;
    }
    else
    {
        D3DXVec3Normalize((D3DXVECTOR3*)&light->position, (D3DXVECTOR3*)&b->Direction);
        light->ambient.x = b->Ambient.r;
        light->ambient.y = b->Ambient.g;
        light->ambient.z = b->Ambient.b;
    }
}

void captureMaterial(const D3DMATERIAL8 *a)
{
    // Morrowind does not use specular lighting
    frs.material.diffuse = a->Diffuse;
    frs.material.ambient = a->Ambient;
    frs.material.emissive = a->Emissive;
    frs.material.emissive.a = a->Power;
}

// --------------------------------------------------------
// Cheap, nasty fps meter

float calcFPS()
{
    static DWORD lasttick, tick, f;
    static float fps;

    ++f;
    tick = GetTickCount();
    if((tick - lasttick) > 1000)
    {
        fps = 1000.0 * f / (tick - lasttick);
        lasttick = tick;
        f = 0;
    }

    return fps;
}
