
#include "proxydx/d3d8header.h"
#include "mgedinput.h"
#include "configuration.h"
#include "distantland.h"
#include "distantshader.h"
#include "postshaders.h"
#include "mwbridge.h"


const float kDistantZBias = 5e-6;



// renderStage0 - Render distant land at beginning of scene 0, after sky
void DistantLand::renderStage0()
{
    DECLARE_MWBRIDGE
    IDirect3DStateBlock9 *stateSaved;
    UINT passes;

    // Get Morrowind camera matrices
    device->GetTransform(D3DTS_VIEW, &mwView);
    device->GetTransform(D3DTS_PROJECTION, &mwProj);

    // Set variables derived from current camera configuration
    setView(&mwView);
    adjustFog();
    setupCommonEffect(&mwView, &mwProj);

    // Select distant static set
    selectDistantCell();
    isRenderCached &= (Configuration.MGEFlags & USE_MENU_CACHING) && mwBridge->IsMenu();

    if(!isRenderCached)
    {
        ///LOG::logline("Sky prims: %d", recordSky.size());

        static DWORD lastcell = 0;
        DWORD celladdr = mwBridge->IntCurCellAddr();
        bool cell_changed = celladdr != lastcell;
        lastcell = celladdr;

        if(isDistantCell())
        {
            // Save state block manually since we can change FVF/decl
            device->CreateStateBlock(D3DSBT_ALL, &stateSaved);
            effect->BeginPass(PASS_SETUP);
            effect->EndPass();

            // Shadow map early render
            if(Configuration.MGEFlags & USE_SHADOWS)
            {
                if(mwBridge->CellHasWeather() && !mwBridge->IsMenu())
                {
                    effectShadow->Begin(&passes, D3DXFX_DONOTSAVESTATE);
                    renderShadowMap();
                    effectShadow->End();
                }
            }

            // Distant everything; bias the projection matrix such that
            // distant land gets drawn behind anything Morrowind would draw
            D3DXMATRIX distProj = mwProj;
            distProj._33 += kDistantZBias;
            effect->SetMatrix(ehProj, &distProj);

            effect->Begin(&passes, D3DXFX_DONOTSAVESTATE);

            // Sky scattering
            if((Configuration.MGEFlags & USE_ATM_SCATTER) && mwBridge->CellHasWeather())
            {
                effect->BeginPass(PASS_RENDERSKY);
                renderSky();
                effect->EndPass();
            }

            if(!mwBridge->IsUnderwater(eyePos.z))
            {
                // Draw distant landscape
                if(mwBridge->IsExterior())
                {
                    effect->BeginPass(PASS_RENDERLAND);
                    renderDistantLand(effect, &mwView, &distProj);
                    effect->EndPass();
                }

                // Draw distant statics
                DWORD p = mwBridge->CellHasWeather() ? PASS_RENDERSTATICSEXTERIOR : PASS_RENDERSTATICSINTERIOR;
                effect->BeginPass(p);
                cullDistantStatics(&mwView, &distProj);
                renderDistantStatics();
                effect->EndPass();
            }

            // Update reflection
            if(mwBridge->CellHasWater())
                renderWaterReflection(&mwView, &distProj);

            // Update water simulation
            if(Configuration.MGEFlags & DYNAMIC_RIPPLES)
                simulateDynamicWaves();

            effect->End();

            // Save distant land only frame to texture
            if(~Configuration.MGEFlags & NO_MW_MGE_BLEND)
                texDistantBlend = PostShaders::borrowBuffer(1);

            // Restore render state
            stateSaved->Apply();
            stateSaved->Release();
        }
        else
        {
            // Clear water reflection on change to non-distant cell
            if(cell_changed || (~Configuration.MGEFlags & USE_DISTANT_LAND))
                clearReflection();

            // Update water simulation
            if(Configuration.MGEFlags & DYNAMIC_RIPPLES)
            {
                // Save state block manually since we can change FVF/decl
                device->CreateStateBlock(D3DSBT_ALL, &stateSaved);

                effect->Begin(&passes, D3DXFX_DONOTSAVESTATE);
                simulateDynamicWaves();
                effect->End();

                // Restore render state
                stateSaved->Apply();
                stateSaved->Release();
            }
        }
    }

    // Clear stray recordings
    recordMW.clear();
    recordSky.clear();
}

// renderStage1 - Render grass and shadows over near features, and write depth texture for scene 0
void DistantLand::renderStage1()
{
    DECLARE_MWBRIDGE
    IDirect3DStateBlock9 *stateSaved;
    UINT passes;

    ///LOG::logline("Stage 1 prims: %d", recordMW.size());

    if(!isRenderCached)
    {
        // Save state block manually since we can change FVF/decl
        device->CreateStateBlock(D3DSBT_ALL, &stateSaved);

        // Reset matrices used in stage 0
        effect->SetMatrix(ehView, &mwView);
        effect->SetMatrix(ehProj, &mwProj);

        // TODO: Locate this properly
        if(isDistantCell())
            cullGrass(&mwView, &mwProj);

        // Depth texture from recorded renders and distant land
        effectDepth->Begin(&passes, D3DXFX_DONOTSAVESTATE);
        renderDepth();
        effectDepth->End();

        if(isDistantCell())
        {
            // Render over Morrowind domain
            effect->Begin(&passes, D3DXFX_DONOTSAVESTATE);

            // Draw grass with shadows
            if(Configuration.MGEFlags & USE_GRASS)
            {
                effect->BeginPass(PASS_RENDERGRASSINST);
                renderGrassInst();
                effect->EndPass();
            }

            // Overlay shadow onto Morrowind objects
            if((Configuration.MGEFlags & USE_SHADOWS) && mwBridge->CellHasWeather())
            {
                effect->BeginPass(PASS_RENDERSHADOW);
                renderShadow();
                effect->EndPass();
            }

            effect->End();
        }

        // Restore render state
        stateSaved->Apply();
        stateSaved->Release();
    }

    recordMW.clear();
}

// renderStage2 - Render shadows and depth texture for other scenes (post-stencil redraw/alpha/1st person)
void DistantLand::renderStage2()
{
    DECLARE_MWBRIDGE
    IDirect3DStateBlock9 *stateSaved;
    UINT passes;

    ///LOG::logline("Stage 2 prims: %d", recordMW.size());

    // Early out if nothing is happening
    if(recordMW.empty())
        return;

    if(!isRenderCached)
    {
        // Save state block manually since we can change FVF/decl
        device->CreateStateBlock(D3DSBT_ALL, &stateSaved);

        // Reset matrices used in stage 0
        effect->SetMatrix(ehView, &mwView);
        effect->SetMatrix(ehProj, &mwProj);

        if(isDistantCell())
        {
            // Shadowing onto recorded renders
            if((Configuration.MGEFlags & USE_SHADOWS) && mwBridge->CellHasWeather())
            {
                effect->Begin(&passes, D3DXFX_DONOTSAVESTATE);

                effect->BeginPass(PASS_RENDERSHADOW);
                renderShadow();
                effect->EndPass();

                effect->End();
            }
        }

        // Depth texture from recorded renders
        effectDepth->Begin(&passes, D3DXFX_DONOTSAVESTATE);
        renderDepthAdditional();
        effectDepth->End();

        // Restore state
        stateSaved->Apply();
        stateSaved->Release();
    }

    recordMW.clear();
}

// renderBlend - Blend between MGE distant land and Morrowind, and render water plane
void DistantLand::renderBlend()
{
    DECLARE_MWBRIDGE
    IDirect3DStateBlock9 *stateSaved;
    UINT passes;

    if(isRenderCached)
        return;

    // Save state block manually since we can change FVF/decl
    device->CreateStateBlock(D3DSBT_ALL, &stateSaved);
    effect->Begin(&passes, D3DXFX_DONOTSAVESTATE);

    // Render caustics
    if(mwBridge->IsExterior() && Configuration.DL.WaterCaustics > 0)
    {
        D3DXMATRIX m;
        IDirect3DTexture9 *tex = PostShaders::borrowBuffer(0);
        D3DXMatrixTranslation(&m, eyePos.x, eyePos.y, mwBridge->WaterLevel());

        effect->SetTexture(ehTex0, tex);
        effect->SetTexture(ehTex1, texWater);
        effect->SetTexture(ehTex3, texDepthFrame);
        effect->SetMatrix(ehWorld, &m);
        effect->SetFloat(ehAlphaRef, Configuration.DL.WaterCaustics);
        effect->CommitChanges();

        effect->BeginPass(PASS_RENDERCAUSTICS);
        PostShaders::applyBlend();
        effect->EndPass();
    }

    // Blend MW/MGE
    if(isDistantCell() && (~Configuration.MGEFlags & NO_MW_MGE_BLEND))
    {
        effect->SetTexture(ehTex0, texDistantBlend);
        effect->SetTexture(ehTex3, texDepthFrame);
        effect->CommitChanges();

        effect->BeginPass(PASS_BLENDMGE);
        PostShaders::applyBlend();
        effect->EndPass();
    }

    // Draw water afterwards
    // As depth texture doesn't contain water plane, it cannot be blended
    if(mwBridge->CellHasWater())
    {
        bool u = mwBridge->IsUnderwater(eyePos.z);
        bool i = !mwBridge->IsExterior();

        if(u || i)
        {
            // Set up clip plane at fog end for certain environments to save fillrate
            float clipAt = Configuration.DL.InteriorFogEnd * 8192.0;
            D3DXPLANE clipPlane(0, 0, -clipAt, mwProj._33 * clipAt + mwProj._43);
            device->SetClipPlane(0, clipPlane);
            device->SetRenderState(D3DRS_CLIPPLANEENABLE, 1);
        }

        // Switch to appropriate shader and render
        effect->BeginPass(u ? PASS_RENDERUNDERWATER : PASS_RENDERWATER);
        renderWaterPlane();
        effect->EndPass();
    }

    effect->End();
    stateSaved->Apply();
    stateSaved->Release();
}

// setupCommonEffect - Set shared shader variables for this frame
void DistantLand::setupCommonEffect(const D3DXMATRIX *view, const D3DXMATRIX *proj)
{
    DECLARE_MWBRIDGE

    // View position
    effect->SetMatrix(ehView, view);
    effect->SetMatrix(ehProj, proj);
    effect->SetFloatArray(ehEyePos, eyePos,3);

    // Sunlight
    RGBVECTOR totalAmb = sunAmb + ambCol;
    effect->SetFloatArray(ehSunVec, sunVec, 3);
    effect->SetFloatArray(ehSunCol, sunCol, 3);
    effect->SetFloatArray(ehSunAmb, totalAmb, 3);
    effect->SetFloatArray(ehSunPos, sunPos, 3);
    effect->SetFloat(ehSunVis, sunVis);

    // Sky/fog
    float fogS = (Configuration.MGEFlags & EXP_FOG) ? (fogStart / Configuration.DL.ExpFogDistMult) : fogStart;
    float fogE = (Configuration.MGEFlags & EXP_FOG) ? (fogEnd / Configuration.DL.ExpFogDistMult) : fogEnd;
    float *sky = mwBridge->CellHasWeather() ?  (float*)mwBridge->CurSkyColVector() : (float*)&horizonCol;
    effect->SetFloat(ehFogStart, fogS);
    effect->SetFloat(ehFogRange, fogE);
    effect->SetFloat(ehFogNearStart, fogNearStart);
    effect->SetFloat(ehFogNearRange, fogNearEnd);
    effect->SetFloatArray(ehSkyCol, sky, 3);
    effect->SetFloatArray(ehFogCol1, nearfogCol, 3);
    effect->SetFloatArray(ehFogCol2, horizonCol, 3);
    effect->SetFloat(ehNiceWeather, niceWeather);

    // Wind, requires smoothing as it is very noisy
    static float smoothWind[2];
    if(!mwBridge->IsMenu())
    {
        const float f = 0.02;
        const float *wind = mwBridge->GetWindVector();
        smoothWind[0] += f * (windScaling * wind[0] - smoothWind[0]);
        smoothWind[1] += f * (windScaling * wind[1] - smoothWind[1]);
        effect->SetFloatArray(ehWindVec, smoothWind, 2);
    }

    // Other
    effect->SetFloatArray(ehFootPos, (float*)mwBridge->PlayerPositionPointer(), 3);
    effect->SetFloat(ehTime, mwBridge->simulationTime());
}

static float lerp(float x0, float x1, float t)
{
    return (1-t)*x0 + t*x1;
}

static float saturate(float x)
{
    return std::min(std::max(0.0f, x), 1.0f);
}

// adjustFog - Set fog distance, wind speed adjust and fog colour for this frame
void DistantLand::adjustFog()
{
    DECLARE_MWBRIDGE

    if(!ready) return;

    // Get fog cell ranges based on environment and weather
    if(mwBridge->IsUnderwater(eyePos.z)) {
        fogStart = Configuration.DL.BelowWaterFogStart;
        fogEnd = Configuration.DL.BelowWaterFogEnd;
    }
    else if(mwBridge->CellHasWeather()) {
        int wthr1 = mwBridge->GetCurrentWeather(), wthr2 = mwBridge->GetNextWeather();
        float ratio = mwBridge->GetWeatherRatio(), ff = 1.0, fo = 0.0, ws = 0.0;

        if (ratio != 0 && wthr2 >= 0 && wthr2 <= 9) {
            ff = lerp(Configuration.DL.FogD[wthr1], Configuration.DL.FogD[wthr2], ratio);
            fo = lerp(Configuration.DL.FgOD[wthr1], Configuration.DL.FgOD[wthr2], ratio) / 100.0;
            ws = lerp(Configuration.DL.Wind[wthr1], Configuration.DL.Wind[wthr2], ratio);
            niceWeather = lerp((wthr1 <= 1) ? 1.0 : 0.0, (wthr2 <= 1) ? 1.0 : 0.0, ratio);
            niceWeather *= niceWeather;
        }
        else if (wthr1 >= 0 && wthr1 <= 9) {
            ff = Configuration.DL.FogD[wthr1];
            fo = Configuration.DL.FgOD[wthr1] / 100.0;
            ws = Configuration.DL.Wind[wthr1];
            niceWeather = (wthr1 <= 1) ? 1.0 : 0.0;
        }

        fogStart = ff * (Configuration.DL.AboveWaterFogStart - fo * Configuration.DL.AboveWaterFogEnd);
        fogEnd = ff * (1 - fo) * Configuration.DL.AboveWaterFogEnd;
        windScaling = ws;
    }
    else {
        // Avoid density == 0, as when fogstart and fogend are equal or too close it can cause problems
        float density = std::max(0.01f, mwBridge->getInteriorFogDens());
        fogStart = lerp(Configuration.DL.InteriorFogEnd, Configuration.DL.InteriorFogStart, density);
        fogEnd = Configuration.DL.InteriorFogEnd;
        windScaling = 0;
    }

    // Convert from cells to in-game units
    fogStart *= 8192.0;
    fogEnd *= 8192.0;

    if(Configuration.MGEFlags & USE_DISTANT_LAND)
    {
        // Set hardware fog for Morrowind's use
        if(Configuration.MGEFlags & EXP_FOG)
        {
            if(mwBridge->IsUnderwater(eyePos.z) || !mwBridge->CellHasWeather())
            {
                // Leave fog ranges as set, shaders use all linear fogging in this case
                fogNearStart = fogStart;
                fogNearEnd = fogEnd;
            }
            else
            {
                // Adjust near region linear Morrowind fogging to approximation of exp fog curve
                fogNearStart = fogStart / Configuration.DL.ExpFogDistMult;
                fogNearEnd = fogEnd / Configuration.DL.ExpFogDistMult;
                float expEnd = exp(-(7168.0 - fogNearStart) / (fogNearEnd - fogNearStart));
                fogNearEnd =  (7168.0 - expEnd * fogNearStart) / (1.0 - expEnd);
            }

            device->SetRenderState(D3DRS_FOGSTART, *(DWORD *)&fogNearStart);
            device->SetRenderState(D3DRS_FOGEND, *(DWORD *)&fogNearEnd);
        }
        else
        {
            device->SetRenderState(D3DRS_FOGSTART, *(DWORD *)&fogStart);
            device->SetRenderState(D3DRS_FOGEND, *(DWORD *)&fogEnd);
        }
    }
    else
    {
        // Read Morrowind-set fog range
        device->GetRenderState(D3DRS_FOGSTART, (DWORD *)&fogNearStart);
        device->GetRenderState(D3DRS_FOGEND, (DWORD *)&fogNearEnd);

        // Reset fog end on toggling distant land as Morrowind assumes it doesn't get changed
        if(fogNearEnd > 7168.0)
        {
            fogNearEnd = 7168.0;
            device->SetRenderState(D3DRS_FOGEND, *(DWORD *)&fogNearEnd);
        }
    }

    // Adjust Morrowind fog colour towards scatter colour if necessary
    DWORD c;
    device->GetRenderState(D3DRS_FOGCOLOR, &c);

    if((Configuration.MGEFlags & USE_DISTANT_LAND) && (Configuration.MGEFlags & USE_ATM_SCATTER) && mwBridge->CellHasWeather() && !mwBridge->IsUnderwater(eyePos.z))
    {
        D3DXCOLOR c0(c), c1(c);

        // Simplified version of scattering from the shader
        const D3DXVECTOR3 scatter(0.07, 0.36, 0.76);
        const D3DXVECTOR3 scatter2(0.16, 0.37, 0.62);
        const RGBVECTOR *skyCol = mwBridge->CurSkyColVector();
        const D3DXVECTOR3 newSkyCol = 0.38 * D3DXVECTOR3(skyCol->r, skyCol->g, skyCol->b) + D3DXVECTOR3(0.23, 0.39, 0.68);
        const float sunaltitude = pow(1 + sunPos.z, 10);
        const float sunaltitude_a = 2.8 + 4.3 / sunaltitude;
        const float sunaltitude_b = saturate(1 - exp2(-1.9 * sunaltitude));
        const float sunaltitude2 = saturate(exp(-2 * sunPos.z)) * saturate(sunaltitude);

        // Calculate scatter colour at Morrowind draw distance boundary
        float fogS = fogStart / Configuration.DL.ExpFogDistMult;
        float fogE = fogEnd / Configuration.DL.ExpFogDistMult;
        float fogdist = (7168.0 - fogS) / (fogE - fogS);
        float fog = saturate(exp(-fogdist));
        fogdist = saturate(0.19 * fogdist);

        float mie = 1.246 * sunaltitude2;
        float rayl = 1 - 0.09 * mie;
        float atmdep = 1.33;

        D3DXVECTOR3 att = atmdep * scatter2 * (sunaltitude_a + mie);
        att.x = (1 - exp(-fogdist * att.x)) / att.x;
        att.y = (1 - exp(-fogdist * att.y)) / att.y;
        att.z = (1 - exp(-fogdist * att.z)) / att.z;

        D3DXVECTOR3 k0 = mie * D3DXVECTOR3(0.125, 0.125, 0.125) + rayl * newSkyCol;
        D3DXVECTOR3 k1 = att * (1.1*atmdep + 0.5) * sunaltitude_b;
        c1.r = k0.x * k1.x; c1.g = k0.y * k1.y; c1.b = k0.z * k1.z;

        // Convert from additive inscatter to Direct3D fog model
        c1 /= 1.0 - fog;

        // Scattering fog only occurs in nice weather
        c0 = (1.0f - niceWeather) * c0 + niceWeather * c1;

        // Save colour for matching near fog in shaders
        nearfogCol = RGBVECTOR(c0);

        // Alter Morrowind's fog colour through its scenegraph
        // This way it automatically restores the correct colour if it has to switch fog modes mid-frame
        mwBridge->setSceneFogCol((DWORD)nearfogCol);
    }
    else
    {
        // Save colour for matching near fog in shaders
        nearfogCol = RGBVECTOR(c);
    }
}

// postProcess - Calls post process module, or captures and applies frame cache to avoid rendering
void DistantLand::postProcess()
{
    IDirect3DStateBlock9 *stateSaved;

    // Save state block
    device->CreateStateBlock(D3DSBT_ALL, &stateSaved);

    if(!isRenderCached)
    {
        DECLARE_MWBRIDGE

        if(Configuration.MGEFlags & USE_HW_SHADER)
        {
            // Set flags to reflect cell environment
            int envFlags = 0;

            if(!mwBridge->CellHasWeather()) envFlags |= 1;
            if(mwBridge->IsExterior()) envFlags |= 2;
            if(mwBridge->IntLikeExterior()) envFlags |= 4;
            if(mwBridge->IsUnderwater(eyePos.z)) envFlags |= 8; else envFlags |= 16;
            if(sunVis >= 0.001) envFlags |= 32; else envFlags |= 64;

            // Run all shaders (with callback to set changed vars)
            PostShaders::shaderTime(&updatePostShader, envFlags, mwBridge->frameTime());
        }

        // Cache render for first frame of menu mode
        if(mwBridge->IsMenu())
        {
            texDistantBlend = PostShaders::borrowBuffer(0);
            isRenderCached = true;
        }
    }
    else
    {
        // Blit cached frame to screen
        IDirect3DSurface9 *backbuffer, *surfDistant;
        device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
        texDistantBlend->GetSurfaceLevel(0, &surfDistant);
        device->StretchRect(surfDistant, 0, backbuffer, 0, D3DTEXF_NONE);
        surfDistant->Release();
        backbuffer->Release();

        // Cache expires for frame after mouse click, so as not to affect click response time
        isRenderCached &= !MGEProxyDirectInput::mouseClick;
    }

    // Shadow map inset
    ///renderShadowDebug();

    // Restore state
    stateSaved->Apply();
    stateSaved->Release();
}

// updatePostShader - callback for setting post shader variables based on environment
void DistantLand::updatePostShader(MGEShader *shader)
{
    DECLARE_MWBRIDGE

    ID3DXEffect *effect = shader->effect;

    // Internal textures
    // TODO: Should be set once at init time
    effect->SetTexture(shader->ehVars[EV_depthframe], texDepthFrame);
    effect->SetTexture(shader->ehVars[EV_watertexture], texWater);

    // View position
    float zoom = (Configuration.MGEFlags & ZOOM_ASPECT) ? Configuration.Zoom.zoom : 1.0;
    effect->SetMatrix(shader->ehVars[EV_mview], &mwView);
    effect->SetMatrix(shader->ehVars[EV_mproj], &mwProj);
    effect->SetFloatArray(shader->ehVars[EV_eyevec], eyeVec,3);
    effect->SetFloatArray(shader->ehVars[EV_eyepos], eyePos,3);
    effect->SetFloat(shader->ehVars[EV_fov], Configuration.ScreenFOV / zoom);

    // Lighting
    RGBVECTOR totalAmb = sunAmb + ambCol;
    effect->SetFloatArray(shader->ehVars[EV_sunvec], sunVec,3);
    effect->SetFloatArray(shader->ehVars[EV_suncol], sunCol,3);
    effect->SetFloatArray(shader->ehVars[EV_sunamb], totalAmb,3);
    effect->SetFloatArray(shader->ehVars[EV_sunpos], sunPos,3);
    effect->SetFloat(shader->ehVars[EV_sunvis], lerp(sunVis, 1.0f, 0.333 * niceWeather));

    // Sky/fog
    float fogS = (Configuration.MGEFlags & EXP_FOG) ? (fogStart / Configuration.DL.ExpFogDistMult) : fogStart;
    float fogE = (Configuration.MGEFlags & EXP_FOG) ? (fogEnd / Configuration.DL.ExpFogDistMult) : fogEnd;
    effect->SetFloat(shader->ehVars[EV_fogstart], fogS);
    effect->SetFloat(shader->ehVars[EV_fogrange], fogE);
    effect->SetFloatArray(shader->ehVars[EV_fogcol], horizonCol, 3);

    // Other
    // In cells without water, set very low waterlevel for shaders that clip against water
    float water = mwBridge->CellHasWater() ? mwBridge->WaterLevel() : -1e9;
    effect->SetFloat(shader->ehVars[EV_time], mwBridge->simulationTime());
    effect->SetFloat(shader->ehVars[EV_waterlevel], water);
    effect->SetBool(shader->ehVars[EV_isinterior], !mwBridge->CellHasWeather());
    effect->SetBool(shader->ehVars[EV_isunderwater], mwBridge->IsUnderwater(eyePos.z));
}

//------------------------------------------------------------

bool DistantLand::selectDistantCell()
{
    DECLARE_MWBRIDGE

    if(Configuration.MGEFlags & USE_DISTANT_LAND)
    {
        if(mwBridge->IsExterior())
        {
            currentWorldSpace = &mapWorldSpaces.find(string())->second;
            return true;
        }

        string cellname = mwBridge->getInteriorName();
        unordered_map<string, WorldSpace>::const_iterator iWS = mapWorldSpaces.find(cellname);
        if(iWS != mapWorldSpaces.end())
        {
            currentWorldSpace = &iWS->second;
            return true;
        }
    }

    currentWorldSpace = 0;
    return false;
}

bool DistantLand::isDistantCell()
{
    return currentWorldSpace != 0;
}

void DistantLand::editProjectionZ(D3DMATRIX *m, float zn, float zf)
{
    // Override near and far clip planes
    m->_33 = zf / (zf - zn);
    m->_43 = -zn * zf / (zf - zn);
}

void DistantLand::setView(const D3DMATRIX *m)
{
    DECLARE_MWBRIDGE

    // Calculate eyePos, eyeVec for shaders
    D3DXVECTOR4 origin(0.0, 0.0, 0.0, 1.0);
    D3DXMATRIX invView, view = *m;

    D3DXMatrixInverse(&invView, 0, &view);
    D3DXVec4Transform(&eyePos, &origin, &invView);
    eyeVec.x = m->_13; eyeVec.y = m->_23; eyeVec.z = m->_33;

    // Set sun disc position
    if(mwBridge->IsLoaded() && mwBridge->CellHasWeather())
    {
        mwBridge->GetSunDir(sunPos.x, sunPos.y, sunPos.z);
        sunPos.w = 1;
        sunPos /= sqrt(sunPos.x * sunPos.x + sunPos.y * sunPos.y + sunPos.z * sunPos.z);

        // Sun position "bounces" at the horizon to follow night lighting instead of setting
        // Sun visibility goes to zero at night, so use this to correct the sun position so it sets
        sunVis = mwBridge->GetSunVis() / 255.0;
        if(sunVis == 0) sunPos.z = -sunPos.z;
    }
    else
    {
        sunPos = D3DXVECTOR4(0, 0, -1, 1);
        sunVis = 0;
    }
}

void DistantLand::setProjection(D3DMATRIX *proj)
{
    // Move near plane from 1.0 to 4.0 for more z accuracy
    // Move far plane back to edge of draw distance
    if(Configuration.MGEFlags & USE_DISTANT_LAND)
        editProjectionZ(proj, 4.0, Configuration.DL.DrawDist * 8192.0);
}

void DistantLand::setHorizonColour(const D3DCOLOR c)
{
    horizonCol = RGBVECTOR(c);
}

void DistantLand::setAmbientColour(const D3DCOLOR c)
{
    ambCol = RGBVECTOR(c);
}

void DistantLand::setSunLight(const D3DLIGHT8 *s)
{
    DECLARE_MWBRIDGE

    if(!ready) return;

    if(mwBridge->CellHasWeather())
    {
        sunVec.x = s->Direction.x;
        sunVec.y = s->Direction.y;
        sunVec.z = s->Direction.z;
        D3DXVec3Normalize((D3DXVECTOR3 *)&sunVec, (D3DXVECTOR3 *)&sunVec);
    }
    else
    {
        sunVec.x = 0.0f;
        sunVec.y = 0.0f;
        sunVec.z = 1.0f;
    }

    sunCol = s->Diffuse;
    sunAmb = s->Ambient;
}

bool DistantLand::inspectIndexedPrimitive(int sceneCount, const RenderedState* rs)
{
    if(!ready) return true;

    DECLARE_MWBRIDGE

    // Capture all writes to z-buffer
    // Only capture alpha blends in alpha scene, otherwise we record extraneous land splatting tiles
    // Interiors are okay to record everything, though technically alpha blending in scene 0 causes some artifacts
    if(rs->zWrite && !(rs->blendEnable && !rs->alphaTest && sceneCount == 0 && mwBridge->IsExterior()))
    {
        recordMW.push_back(*rs);

        // Unify alpha test operator to GREATEREQUAL
        if(rs->alphaFunc == D3DCMP_GREATER)
            recordMW.back().alphaRef++;
    }

    // Special case, capture sky
    if(recordMW.empty() && rs->blendEnable && sceneCount == 0 && mwBridge->CellHasWeather())
    {
        recordSky.push_back(*rs);

        // If using atmosphere scattering, draw sky later in stage 0
        if((Configuration.MGEFlags & USE_DISTANT_LAND) && (Configuration.MGEFlags & USE_ATM_SCATTER))
            return false;
    }

    return true;
}

IDirect3DSurface9 * DistantLand::captureScreen()
{
    IDirect3DTexture9 *t;
    IDirect3DSurface9 *s;

    t = PostShaders::borrowBuffer(0);
    t->GetSurfaceLevel(0, &s);

    return s;
}
