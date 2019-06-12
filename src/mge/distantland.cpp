
#include "proxydx/d3d8header.h"
#include "mgedinput.h"
#include "configuration.h"
#include "distantland.h"
#include "distantshader.h"
#include "postshaders.h"
#include "mwbridge.h"



using std::string;
using std::unordered_map;

// renderStage0 - Render distant land at beginning of scene 0, after sky
void DistantLand::renderStage0() {
    auto mwBridge = MWBridge::get();
    IDirect3DStateBlock9* stateSaved;
    UINT passes;

    // Get Morrowind camera matrices
    device->GetTransform(D3DTS_VIEW, &mwView);
    device->GetTransform(D3DTS_PROJECTION, &mwProj);

    // Set variables derived from current camera configuration
    setView(&mwView);
    adjustFog();
    setupCommonEffect(&mwView, &mwProj);
    FixedFunctionShader::updateLighting(lightSunMult, lightAmbMult);

    // Select distant static set
    selectDistantCell();
    isRenderCached &= (Configuration.MGEFlags & USE_MENU_CACHING) && mwBridge->IsMenu();
    isPPLActive = (Configuration.MGEFlags & USE_FFESHADER) && !(Configuration.PerPixelLightFlags == 1 && !mwBridge->IntCurCellAddr());

    if (!isRenderCached) {
        ///LOG::logline("Sky prims: %d", recordSky.size());

        if (isDistantCell()) {
            // Save state block manually since we can change FVF/decl
            device->CreateStateBlock(D3DSBT_ALL, &stateSaved);
            effect->BeginPass(PASS_SETUP);
            effect->EndPass();

            // Shadow map early render
            if (Configuration.MGEFlags & USE_SHADOWS) {
                if (mwBridge->CellHasWeather() && !mwBridge->IsMenu()) {
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

            if (!mwBridge->IsUnderwater(eyePos.z)) {
                // Draw distant landscape
                if (mwBridge->IsExterior()) {
                    effect->BeginPass(PASS_RENDERLAND);
                    renderDistantLand(effect, &mwView, &distProj);
                    effect->EndPass();
                }

                // Draw distant statics, with alpha dissolve as they pass the near view boundary
                DWORD p = mwBridge->CellHasWeather() ? PASS_RENDERSTATICSEXTERIOR : PASS_RENDERSTATICSINTERIOR;
                effect->BeginPass(p);
                vsr.beginAlphaToCoverage(device);

                cullDistantStatics(&mwView, &distProj);
                renderDistantStatics();

                vsr.endAlphaToCoverage(device);
                effect->EndPass();
            }

            // Sky scattering and sky objects (should be drawn late as possible)
            if ((Configuration.MGEFlags & USE_ATM_SCATTER) && mwBridge->CellHasWeather()) {
                effect->BeginPass(PASS_RENDERSKY);
                renderSky();
                effect->EndPass();
            }

            // Update reflection
            if (mwBridge->CellHasWater()) {
                renderWaterReflection(&mwView, &distProj);
            }

            // Update water simulation
            if (Configuration.MGEFlags & DYNAMIC_RIPPLES) {
                simulateDynamicWaves();
            }

            effect->End();

            // Reset matrices
            effect->SetMatrix(ehView, &mwView);
            effect->SetMatrix(ehProj, &mwProj);

            // Save distant land only frame to texture
            if (~Configuration.MGEFlags & NO_MW_MGE_BLEND) {
                texDistantBlend = PostShaders::borrowBuffer(1);
            }

            // Restore render state
            stateSaved->Apply();
            stateSaved->Release();
        } else {
            // Clear water reflection to avoid seeing previous cell environment reflected
            // Must be done every frame to react to lighting changes
            clearReflection();

            // Update water simulation
            if (Configuration.MGEFlags & DYNAMIC_RIPPLES) {
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
void DistantLand::renderStage1() {
    auto mwBridge = MWBridge::get();
    IDirect3DStateBlock9* stateSaved;
    UINT passes;

    ///LOG::logline("Stage 1 prims: %d", recordMW.size());

    if (!isRenderCached) {
        // Save state block manually since we can change FVF/decl
        device->CreateStateBlock(D3DSBT_ALL, &stateSaved);

        // TODO: Locate this properly
        if (isDistantCell()) {
            cullGrass(&mwView, &mwProj);
        }

        if (isDistantCell()) {
            // Render over Morrowind domain
            effect->Begin(&passes, D3DXFX_DONOTSAVESTATE);

            // Draw grass with shadows
            if (Configuration.MGEFlags & USE_GRASS) {
                effect->BeginPass(PASS_RENDERGRASSINST);
                vsr.beginAlphaToCoverage(device);
                renderGrassInst();
                vsr.endAlphaToCoverage(device);
                effect->EndPass();
            }

            // Overlay shadow onto Morrowind objects
            if ((Configuration.MGEFlags & USE_SHADOWS) && mwBridge->CellHasWeather()) {
                effect->BeginPass(PASS_RENDERSHADOW);
                renderShadow();
                effect->EndPass();

            }

            effect->End();
        }

        // Depth texture from recorded renders and distant land
        effectDepth->Begin(&passes, D3DXFX_DONOTSAVESTATE);
        renderDepth();
        effectDepth->End();

        // Restore render state
        stateSaved->Apply();
        stateSaved->Release();
    }

    recordMW.clear();
}

// renderStage2 - Render shadows and depth texture for scenes 1+ (post-stencil redraw/alpha/1st person)
void DistantLand::renderStage2() {
    auto mwBridge = MWBridge::get();
    IDirect3DStateBlock9* stateSaved;
    UINT passes;

    ///LOG::logline("Stage 2 prims: %d", recordMW.size());

    // Early out if nothing is happening
    if (recordMW.empty()) {
        return;
    }

    if (!isRenderCached) {
        // Save state block manually since we can change FVF/decl
        device->CreateStateBlock(D3DSBT_ALL, &stateSaved);

        if (isDistantCell()) {
            // Shadowing onto recorded renders
            if ((Configuration.MGEFlags & USE_SHADOWS) && mwBridge->CellHasWeather()) {
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


// renderStageBlend - Blend between MGE distant land and Morrowind, rendering caustics first so it blends out
void DistantLand::renderStageBlend() {
    auto mwBridge = MWBridge::get();
    IDirect3DStateBlock9* stateSaved;
    UINT passes;

    if (isRenderCached) {
        return;
    }

    // Save state block manually since we can change FVF/decl
    device->CreateStateBlock(D3DSBT_ALL, &stateSaved);
    effect->Begin(&passes, D3DXFX_DONOTSAVESTATE);

    // Render caustics
    if (mwBridge->IsExterior() && Configuration.DL.WaterCaustics > 0) {
        D3DXMATRIX m;
        IDirect3DTexture9* tex = PostShaders::borrowBuffer(0);
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
    if (isDistantCell() && (~Configuration.MGEFlags & NO_MW_MGE_BLEND)) {
        effect->SetTexture(ehTex0, texDistantBlend);
        effect->SetTexture(ehTex3, texDepthFrame);
        effect->CommitChanges();

        effect->BeginPass(PASS_BLENDMGE);
        PostShaders::applyBlend();
        effect->EndPass();
    }

    effect->End();
    stateSaved->Apply();
    stateSaved->Release();
}

// renderStageWater - Render replacement water plane
void DistantLand::renderStageWater() {
    auto mwBridge = MWBridge::get();
    IDirect3DStateBlock9* stateSaved;
    UINT passes;

    if (isRenderCached) {
        return;
    }

    if (mwBridge->CellHasWater()) {
        // Save state block manually since we can change FVF/decl
        device->CreateStateBlock(D3DSBT_ALL, &stateSaved);
        effect->Begin(&passes, D3DXFX_DONOTSAVESTATE);

        // Draw water plane
        bool u = mwBridge->IsUnderwater(eyePos.z);
        bool i = !mwBridge->IsExterior();

        if (u || i) {
            // Set up clip plane at fog end for certain environments to save fillrate
            float clipAt = Configuration.DL.InteriorFogEnd * kCellSize;
            D3DXPLANE clipPlane(0, 0, -clipAt, mwProj._33 * clipAt + mwProj._43);
            device->SetClipPlane(0, clipPlane);
            device->SetRenderState(D3DRS_CLIPPLANEENABLE, 1);
        }

        // Switch to appropriate shader and render
        effect->BeginPass(u ? PASS_RENDERUNDERWATER : PASS_RENDERWATER);
        renderWaterPlane();
        effect->EndPass();

        effect->End();
        stateSaved->Apply();
        stateSaved->Release();
    }
}

// setupCommonEffect - Set shared shader variables for this frame
void DistantLand::setupCommonEffect(const D3DXMATRIX* view, const D3DXMATRIX* proj) {
    auto mwBridge = MWBridge::get();

    // View position
    effect->SetMatrix(ehView, view);
    effect->SetMatrix(ehProj, proj);
    effect->SetFloatArray(ehEyePos, eyePos, 3);

    // Sunlight
    D3DXVECTOR3 sunVecView;
    RGBVECTOR totalAmb = sunAmb + ambCol;
    D3DXVec3TransformNormal(&sunVecView, (const D3DXVECTOR3*)&sunVec, view);

    effect->SetFloatArray(ehSunVec, sunVec, 3);
    effect->SetFloatArray(ehSunVecView, sunVecView, 3);
    effect->SetFloatArray(ehSunCol, sunCol, 3);
    effect->SetFloatArray(ehSunAmb, totalAmb, 3);
    effect->SetFloatArray(ehSunPos, sunPos, 3);
    effect->SetFloat(ehSunVis, sunVis);

    if (isPPLActive) {
        // Apply light multiplier settings to distant land
        RGBVECTOR s = lightSunMult * sunCol, a = lightAmbMult * totalAmb;
        effect->SetFloatArray(ehSunCol, s, 3);
        effect->SetFloatArray(ehSunAmb, a, 3);
    }

    // Sky/fog
    float fogS = (Configuration.MGEFlags & EXP_FOG) ? (fogStart / Configuration.DL.ExpFogDistMult) : fogStart;
    float fogE = (Configuration.MGEFlags & EXP_FOG) ? (fogEnd / Configuration.DL.ExpFogDistMult) : fogEnd;
    const RGBVECTOR* skyCol = mwBridge->CellHasWeather() ?  mwBridge->getCurrentWeatherSkyCol() : &horizonCol;
    effect->SetFloat(ehFogStart, fogS);
    effect->SetFloat(ehFogRange, fogE);
    effect->SetFloat(ehFogNearStart, fogNearStart);
    effect->SetFloat(ehFogNearRange, fogNearEnd);
    effect->SetFloatArray(ehSkyCol, *skyCol, 3);
    effect->SetFloatArray(ehFogCol1, nearFogCol, 3);
    effect->SetFloatArray(ehFogCol2, horizonCol, 3);
    effect->SetFloat(ehNearViewRange, nearViewRange);
    effect->SetFloat(ehNiceWeather, niceWeather);

    if (Configuration.MGEFlags & USE_ATM_SCATTER) {
        effect->SetFloatArray(ehOutscatter, atmOutscatter, 3);
        effect->SetFloatArray(ehInscatter, atmInscatter, 3);
    }

    // Wind, requires smoothing as it is very noisy
    static float smoothWind[2];
    if (!mwBridge->IsMenu()) {
        const float f = 0.02;
        const float* wind = mwBridge->GetWindVector();
        smoothWind[0] += f * (windScaling * wind[0] - smoothWind[0]);
        smoothWind[1] += f * (windScaling * wind[1] - smoothWind[1]);
        effect->SetFloatArray(ehWindVec, smoothWind, 2);
    }

    // Other
    effect->SetFloatArray(ehFootPos, (float*)mwBridge->PlayerPositionPointer(), 3);
    effect->SetFloat(ehTime, mwBridge->simulationTime());
}

// setScattering - Set scattering coefficients for atmospheric scattering shader
void DistantLand::setScattering(const RGBVECTOR& out, const RGBVECTOR& in) {
    atmOutscatter = out;
    atmInscatter = in;
}

static double lerp(double x0, double x1, double t) {
    return (1.0 - t) * x0 + t * x1;
}

static double saturate(double x) {
    return std::min(std::max(0.0, x), 1.0);
}

// adjustFog - Set fog distance, wind speed adjust and fog colour for this frame
void DistantLand::adjustFog() {
    auto mwBridge = MWBridge::get();

    nearViewRange = mwBridge->GetViewDistance();

    // Morrowind does not update weather during menu mode, except when time is changed
    // Therefore always run adjustment during menu mode, except if background caching is used
    if (isRenderCached) {
        return;
    }

    // Get fog cell ranges based on environment and weather
    if (mwBridge->IsUnderwater(eyePos.z)) {
        fogStart = Configuration.DL.BelowWaterFogStart;
        fogEnd = Configuration.DL.BelowWaterFogEnd;
    } else if (mwBridge->CellHasWeather()) {
        int wthr1 = mwBridge->GetCurrentWeather(), wthr2 = mwBridge->GetNextWeather();
        float ratio = mwBridge->GetWeatherRatio(), ff = 1.0, fo = 0.0, ws = 0.0;

        if (ratio != 0 && wthr2 >= 0 && wthr2 <= 9) {
            ff = float(lerp(Configuration.DL.FogD[wthr1], Configuration.DL.FogD[wthr2], ratio));
            fo = float(0.01 * lerp(Configuration.DL.FgOD[wthr1], Configuration.DL.FgOD[wthr2], ratio));
            ws = float(lerp(Configuration.DL.Wind[wthr1], Configuration.DL.Wind[wthr2], ratio));
            niceWeather = float(lerp((wthr1 <= 1) ? 1.0 : 0.0, (wthr2 <= 1) ? 1.0 : 0.0, ratio));
            niceWeather *= niceWeather;
            lightSunMult = float(lerp(Configuration.Lighting.SunMult[wthr1], Configuration.Lighting.SunMult[wthr2], ratio));
            lightAmbMult = float(lerp(Configuration.Lighting.AmbMult[wthr1], Configuration.Lighting.AmbMult[wthr2], ratio));
        } else if (wthr1 >= 0 && wthr1 <= 9) {
            ff = Configuration.DL.FogD[wthr1];
            fo = Configuration.DL.FgOD[wthr1] / 100.0f;
            ws = Configuration.DL.Wind[wthr1];
            niceWeather = (wthr1 <= 1) ? 1.0f : 0.0f;
            lightSunMult = Configuration.Lighting.SunMult[wthr1];
            lightAmbMult = Configuration.Lighting.AmbMult[wthr1];
        }

        fogStart = ff * (Configuration.DL.AboveWaterFogStart - fo * Configuration.DL.AboveWaterFogEnd);
        fogEnd = ff * (1 - fo) * Configuration.DL.AboveWaterFogEnd;
        windScaling = ws;
    } else {
        // Avoid density == 0, as when fogstart and fogend are equal, the fog equation denominator goes to infinity
        float density = std::max(0.01f, mwBridge->getInteriorFogDens());
        fogStart = float(lerp(Configuration.DL.InteriorFogEnd, Configuration.DL.InteriorFogStart, density));
        fogEnd = Configuration.DL.InteriorFogEnd;
        niceWeather = 0;
        windScaling = 0;
        lightSunMult = 1.0;
        lightAmbMult = 1.0;
    }

    // Convert from cells to in-game units
    fogStart *= kCellSize;
    fogEnd *= kCellSize;

    if (Configuration.MGEFlags & USE_DISTANT_LAND) {
        // Set hardware fog for Morrowind's use
        if (Configuration.MGEFlags & EXP_FOG) {
            if (mwBridge->IsUnderwater(eyePos.z) || !mwBridge->CellHasWeather()) {
                // Leave fog ranges as set, shaders use all linear fogging in this case
                fogNearStart = fogStart;
                fogNearEnd = fogEnd;
            } else {
                // Adjust near region linear Morrowind fogging to approximation of exp fog curve
                // Linear density matched to exp fog at dist = 1280 and dist = viewrange (or fog end if closer)
                fogNearStart = fogStart / Configuration.DL.ExpFogDistMult;
                fogNearEnd = fogEnd / Configuration.DL.ExpFogDistMult;

                float farIntercept = std::min(fogEnd, nearViewRange);
                float expStart = exp(-(1280.0f - fogNearStart) / (fogNearEnd - fogNearStart));
                float expEnd = exp(-(farIntercept - fogNearStart) / (fogNearEnd - fogNearStart));
                fogNearStart = 1280.0f + (farIntercept - 1280.0f) * (1.0f - expStart) / (expEnd - expStart);
                fogNearEnd = 1280.0f + (farIntercept - 1280.0f) * -expStart / (expEnd - expStart);
            }
        } else {
            fogNearStart = fogStart;
            fogNearEnd = fogEnd;
        }

        device->SetRenderState(D3DRS_FOGSTART, *(DWORD*)&fogNearStart);
        device->SetRenderState(D3DRS_FOGEND, *(DWORD*)&fogNearEnd);
    } else {
        // Reset fog end on toggling distant land as Morrowind assumes it doesn't get changed
        if (fogNearEnd > nearViewRange) {
            fogNearEnd = nearViewRange;
            device->SetRenderState(D3DRS_FOGEND, *(DWORD*)&fogNearEnd);
        }

        // Read Morrowind-set fog range
        fogNearEnd = nearViewRange;
        fogNearStart = fogNearEnd * std::min(1.0f - mwBridge->getScenegraphFogDensity(), 0.99f);
        fogStart = fogNearStart;
        fogEnd = fogNearEnd;
    }

    // Adjust Morrowind fog colour towards scatter colour if necessary
    if ((Configuration.MGEFlags & USE_DISTANT_LAND) && (Configuration.MGEFlags & USE_ATM_SCATTER) && mwBridge->CellHasWeather() && !mwBridge->IsUnderwater(eyePos.z)) {
        // Read unadjusted colour, as the scenegraph fog colour may not be updated during menu transitions
        RGBVECTOR c0 = *mwBridge->getCurrentWeatherFogCol();
        RGBVECTOR c1 = c0;

        // Simplified version of scattering from the shader
        const RGBVECTOR* skyCol = mwBridge->getCurrentWeatherSkyCol();
        const D3DXVECTOR3 newSkyCol = 0.38 * D3DXVECTOR3(skyCol->r, skyCol->g, skyCol->b) + D3DXVECTOR3(0.23, 0.39, 0.68);
        const float sunaltitude = powf(1 + sunPos.z, 10);
        const float sunaltitude_a = 2.8f + 4.3f / sunaltitude;
        const float sunaltitude_b = float(saturate(1.0 - exp2(-1.9 * sunaltitude)));
        const float sunaltitude2 = float(saturate(exp(-2.0 * sunPos.z)) * saturate(sunaltitude));

        // Calculate scatter colour at Morrowind draw distance boundary
        float fogS = fogStart / Configuration.DL.ExpFogDistMult;
        float fogE = fogEnd / Configuration.DL.ExpFogDistMult;
        float fogdist = (nearViewRange - fogS) / (fogE - fogS);
        float fog = float(saturate(exp(-fogdist)));
        fogdist = float(saturate(0.21 * fogdist));

        D3DXVECTOR2 horizonDir(eyeVec.x, eyeVec.y);
        D3DXVec2Normalize(&horizonDir, &horizonDir);
        float suncos =  horizonDir.x * sunPos.x + horizonDir.y * sunPos.y;
        float mie = (1.62f / (1.3f - suncos)) * sunaltitude2;
        float rayl = 1.0f - 0.09f * mie;
        float atmdep = 1.33f;

        RGBVECTOR midscatter = 0.5f * (atmInscatter + atmOutscatter);
        D3DXVECTOR3 scatter;
        scatter.x = float(lerp(midscatter.r, atmOutscatter.r, suncos));
        scatter.y = float(lerp(midscatter.g, atmOutscatter.g, suncos));
        scatter.z = float(lerp(midscatter.b, atmOutscatter.b, suncos));

        D3DXVECTOR3 att = atmdep * scatter * (sunaltitude_a + mie);
        att.x = (1 - exp(-fogdist * att.x)) / att.x;
        att.y = (1 - exp(-fogdist * att.y)) / att.y;
        att.z = (1 - exp(-fogdist * att.z)) / att.z;

        D3DXVECTOR3 k0 = mie * D3DXVECTOR3(0.125, 0.125, 0.125) + rayl * newSkyCol;
        D3DXVECTOR3 k1 = att * (1.1f * atmdep + 0.5f) * sunaltitude_b;
        c1.r = k0.x * k1.x;
        c1.g = k0.y * k1.y;
        c1.b = k0.z * k1.z;

        // Convert from additive inscatter to Direct3D fog model
        // The correction factor is clamped to avoid creating infinities
        c1 /= std::max(0.02f, 1.0f - fog);

        // Scattering fog only occurs in nice weather
        c0 = (1.0f - niceWeather) * c0 + niceWeather * c1;

        // Save colour for matching near fog in shaders
        nearFogCol = c0;

        // Alter Morrowind's fog colour through its scenegraph
        // This way it automatically restores the correct colour if it has to switch fog modes mid-frame
        DWORD fc = (DWORD)nearFogCol;
        mwBridge->setScenegraphFogCol(fc);

        // Set device fog colour to propagate change immediately
        device->SetRenderState(D3DRS_FOGCOLOR, fc);
    } else {
        // Save current fog colour for matching near fog in shaders
        nearFogCol = RGBVECTOR(mwBridge->getScenegraphFogCol());
    }
}

// postProcess - Calls post process module, or captures and applies frame cache to avoid rendering
void DistantLand::postProcess() {
    if (!isRenderCached) {
        auto mwBridge = MWBridge::get();

        // Save state block
        IDirect3DStateBlock9* stateSaved;
        device->CreateStateBlock(D3DSBT_ALL, &stateSaved);

        if (Configuration.MGEFlags & USE_HW_SHADER) {
            // Set flags to reflect cell environment
            int envFlags = 0;

            if (!mwBridge->CellHasWeather()) {
                envFlags |= 1;
            }
            if (mwBridge->IsExterior()) {
                envFlags |= 2;
            }
            if (mwBridge->IntLikeExterior()) {
                envFlags |= 4;
            }
            if (mwBridge->IsUnderwater(eyePos.z)) {
                envFlags |= 8;
            } else {
                envFlags |= 16;
            }
            if (sunVis >= 0.001) {
                envFlags |= 32;
            } else {
                envFlags |= 64;
            }

            // Run all shaders (with callback to set changed vars)
            PostShaders::shaderTime(&updatePostShader, envFlags, mwBridge->frameTime());
        }

        // Cache render for first frame of menu mode
        if ((Configuration.MGEFlags & USE_MENU_CACHING) && mwBridge->IsMenu()) {
            texDistantBlend = PostShaders::borrowBuffer(0);
            isRenderCached = true;
        } else if (captureScreenFunc) {
            IDirect3DSurface9* surface = captureScreen();
            (*captureScreenFunc)(surface);
            if (surface) {
                surface->Release();
            }
            captureScreenFunc = NULL;
        }

        // Shadow map inset
        ///if(!mwBridge->IsMenu()) { renderShadowDebug(); }

        // Restore state
        stateSaved->Apply();
        stateSaved->Release();
    } else {
        // Blit cached frame to screen
        IDirect3DSurface9* backbuffer, *surfDistant;
        device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
        texDistantBlend->GetSurfaceLevel(0, &surfDistant);
        device->StretchRect(surfDistant, 0, backbuffer, 0, D3DTEXF_NONE);
        surfDistant->Release();
        backbuffer->Release();

        // Cache expires for frame after mouse click, so as not to affect click response time
        isRenderCached &= !MGEProxyDirectInput::mouseClick;
    }
}

// updatePostShader - callback for setting post shader variables based on environment
void DistantLand::updatePostShader(MGEShader* shader) {
    auto mwBridge = MWBridge::get();

    // Internal textures
    // TODO: Should be set once at init time
    shader->SetTexture(EV_depthframe, texDepthFrame);
    shader->SetTexture(EV_watertexture, texWater);

    // View position
    float zoom = (Configuration.MGEFlags & ZOOM_ASPECT) ? Configuration.CameraEffects.zoom : 1.0f;
    shader->SetMatrix(EV_mview, &mwView);
    shader->SetMatrix(EV_mproj, &mwProj);
    shader->SetFloatArray(EV_eyevec, eyeVec, 3);
    shader->SetFloatArray(EV_eyepos, eyePos, 3);
    shader->SetFloat(EV_fov, Configuration.ScreenFOV / zoom);

    // Lighting
    RGBVECTOR totalAmb = sunAmb + ambCol;
    shader->SetFloatArray(EV_sunvec, sunVec, 3);
    shader->SetFloatArray(EV_suncol, sunCol, 3);
    shader->SetFloatArray(EV_sunamb, totalAmb, 3);
    shader->SetFloatArray(EV_sunpos, sunPos, 3);
    shader->SetFloat(EV_sunvis, float(lerp(sunVis, 1.0, 0.333 * niceWeather)));

    // Sky/fog
    float fogS = (Configuration.MGEFlags & EXP_FOG) ? (fogStart / Configuration.DL.ExpFogDistMult) : fogStart;
    float fogE = (Configuration.MGEFlags & EXP_FOG) ? (fogEnd / Configuration.DL.ExpFogDistMult) : fogEnd;
    shader->SetFloatArray(EV_fogcol, horizonCol, 3);
    shader->SetFloat(EV_fogstart, fogS);
    shader->SetFloat(EV_fogrange, fogE);
    shader->SetFloat(EV_fognearstart, fogNearStart);
    shader->SetFloat(EV_fognearrange, fogNearEnd);

    // Other
    // In cells without water, set very low waterlevel for shaders that clip against water
    float water = mwBridge->CellHasWater() ? mwBridge->WaterLevel() : -1e9f;
    shader->SetFloat(EV_time, mwBridge->simulationTime());
    shader->SetFloat(EV_waterlevel, water);
    shader->SetBool(EV_isinterior, !mwBridge->CellHasWeather());
    shader->SetBool(EV_isunderwater, mwBridge->IsUnderwater(eyePos.z));
}

//------------------------------------------------------------

// selectDistantCell - Select the correct set of distant land meshes for the current cell
bool DistantLand::selectDistantCell() {
    auto mwBridge = MWBridge::get();

    if (Configuration.MGEFlags & USE_DISTANT_LAND) {
        if (mwBridge->IsExterior()) {
            decltype(mapWorldSpaces)::const_iterator iWS = mapWorldSpaces.find(string());
            if (iWS != mapWorldSpaces.end()) {
                currentWorldSpace = &iWS->second;
                return true;
            }
        }
        else if (mwBridge->CellHasWeather() || (Configuration.MGEFlags & REFLECT_INTERIOR)) {
            string cellname = mwBridge->getInteriorName();
            decltype(mapWorldSpaces)::const_iterator iWS = mapWorldSpaces.find(cellname);
            if (iWS != mapWorldSpaces.end()) {
                currentWorldSpace = &iWS->second;
                return true;
            }
        }
    }

    currentWorldSpace = nullptr;
    return false;
}

// isDistantCell - Check if there is distant land selected for this cell
bool DistantLand::isDistantCell() {
    return currentWorldSpace != nullptr;
}

// setView - Called once per frame to setup view dependent data
void DistantLand::setView(const D3DMATRIX* m) {
    auto mwBridge = MWBridge::get();

    // Calculate eyePos, eyeVec for shaders
    D3DXVECTOR4 origin(0.0, 0.0, 0.0, 1.0);
    D3DXMATRIX invView, view = *m;

    D3DXMatrixInverse(&invView, 0, &view);
    D3DXVec4Transform(&eyePos, &origin, &invView);
    eyeVec.x = m->_13;
    eyeVec.y = m->_23;
    eyeVec.z = m->_33;

    // Set sun disc position
    if (mwBridge->IsLoaded() && mwBridge->CellHasWeather()) {
        mwBridge->GetSunDir(sunPos.x, sunPos.y, sunPos.z);
        sunPos.w = 1;
        sunPos /= sqrt(sunPos.x * sunPos.x + sunPos.y * sunPos.y + sunPos.z * sunPos.z);

        // Sun position "bounces" at the horizon to follow night lighting instead of setting
        // Sun visibility goes to zero at night, so use this to correct the sun position so it sets
        sunVis = mwBridge->GetSunVis() / 255.0f;
        if (sunVis == 0) {
            sunPos.z = -sunPos.z;
        }
    } else {
        sunPos = D3DXVECTOR4(0, 0, -1, 1);
        sunVis = 0;
    }
}

// setProjection - Called when a D3D projection matrix is set, and edits it
void DistantLand::setProjection(D3DMATRIX* proj) {
    // Move near plane from 1.0 to 4.0 for more z accuracy
    // Move far plane back to edge of draw distance
    if (Configuration.MGEFlags & USE_DISTANT_LAND) {
        editProjectionZ(proj, 4.0, Configuration.DL.DrawDist * kCellSize);
    }
}

// editProjectionZ - Alter the near and far clip planes of a projection matrix
void DistantLand::editProjectionZ(D3DMATRIX* m, float zn, float zf) {
    // Override near and far clip planes
    m->_33 = zf / (zf - zn);
    m->_43 = -zn * zf / (zf - zn);
}

void DistantLand::setHorizonColour(const RGBVECTOR& c) {
    horizonCol = c;
}

void DistantLand::setAmbientColour(const RGBVECTOR& c) {
    ambCol = c;
}

void DistantLand::setSunLight(const D3DLIGHT8* s) {
    auto mwBridge = MWBridge::get();

    if (mwBridge->CellHasWeather()) {
        sunVec.x = s->Direction.x;
        sunVec.y = s->Direction.y;
        sunVec.z = s->Direction.z;
        D3DXVec3Normalize((D3DXVECTOR3*)&sunVec, (D3DXVECTOR3*)&sunVec);
    } else {
        sunVec.x = 0.0f;
        sunVec.y = 0.0f;
        sunVec.z = 1.0f;
    }

    sunCol = s->Diffuse;
    sunAmb = s->Ambient;
}

// inspectIndexedPrimitive
// Filters and records DIP calls for later use; returning false should cause the draw call to be skipped
// Can also replace selected fixed function calls with an augmented shader
bool DistantLand::inspectIndexedPrimitive(int sceneCount, const RenderedState* rs, const FragmentState* frs, LightState* lightrs) {
    auto mwBridge = MWBridge::get();

    // Capture all writes to z-buffer
    // Only capture alpha blends in alpha scene, otherwise we record extraneous land splatting tiles
    // Interiors are okay to record everything, though technically alpha blending in scene 0 causes some artifacts
    if (rs->zWrite && !(rs->blendEnable && !rs->alphaTest && sceneCount == 0 && mwBridge->IsExterior())) {
        recordMW.push_back(*rs);

        // Unify alpha test operator/reference to be equivalent to GREATEREQUAL
        if (rs->alphaFunc == D3DCMP_GREATER) {
            recordMW.back().alphaRef++;
        }
    }

    // Special case, capture sky
    if (recordMW.empty() && rs->blendEnable && sceneCount == 0 && mwBridge->CellHasWeather()) {
        recordSky.push_back(*rs);

        // Check for moon geometry, and mark those records by setting lighting off
        if (frs->material.emissive.a == kMoonTag) {
            recordSky.back().useLighting = false;
        }

        // If using atmosphere scattering, draw sky later in stage 0
        if ((Configuration.MGEFlags & USE_DISTANT_LAND) && (Configuration.MGEFlags & USE_ATM_SCATTER)) {
            return false;
        }
    } else if (isPPLActive) {
        // Render Morrowind with replacement shaders
        FixedFunctionShader::renderMorrowind(rs, frs, lightrs);
        return false;
    }

    return true;
}

// requestCaptureNoUI - Set a function to be called with a screen capture
// just after post-processing and before the UI is drawn
void DistantLand::requestCaptureNoUI(void (*func)(IDirect3DSurface9*)) {
    captureScreenFunc = func;
}

// captureScreen - Capture a screenshot
IDirect3DSurface9* DistantLand::captureScreen() {
    IDirect3DTexture9* t;
    IDirect3DSurface9* s;

    // Resolve multisampled back buffer
    t = PostShaders::borrowBuffer(0);
    t->GetSurfaceLevel(0, &s);

    // Cancel render cache, borrowBuffer just overwrote it
    isRenderCached = false;

    // Copy buffer to system memory surface
    IDirect3DSurface9* surfSS;
    D3DSURFACE_DESC desc;

    s->GetDesc(&desc);
    DWORD hr = device->CreateOffscreenPlainSurface(desc.Width, desc.Height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &surfSS, NULL);
    if (hr != D3D_OK) {
        s->Release();
        return nullptr;
    }

    hr = device->GetRenderTargetData(s, surfSS);
    s->Release();
    if (hr != D3D_OK) {
        surfSS->Release();
        return nullptr;
    }

    return surfSS;
}



// RenderTargetSwitcher - Switch to a render target, restoring state at end of scope
RenderTargetSwitcher::RenderTargetSwitcher(IDirect3DSurface9* target, IDirect3DSurface9* targetDepthStencil) {
    init(target, targetDepthStencil);
}

// RenderTargetSwitcher - Switch to a render surface belonging to a texture, restoring state at end of scope
RenderTargetSwitcher::RenderTargetSwitcher(IDirect3DTexture9* targetTex, IDirect3DSurface9* targetDepthStencil) {
    // Note the device still holds a reference to the target while it's active
    IDirect3DSurface9* target;
    targetTex->GetSurfaceLevel(0, &target);
    init(target, targetDepthStencil);
    target->Release();
}

void RenderTargetSwitcher::init(IDirect3DSurface9* target, IDirect3DSurface9* targetDepthStencil) {
    DistantLand::device->GetRenderTarget(0, &savedTarget);
    DistantLand::device->GetDepthStencilSurface(&savedDepthStencil);

    DistantLand::device->SetRenderTarget(0, target);
    DistantLand::device->SetDepthStencilSurface(targetDepthStencil);
}

RenderTargetSwitcher::~RenderTargetSwitcher() {
    DistantLand::device->SetRenderTarget(0, savedTarget);
    DistantLand::device->SetDepthStencilSurface(savedDepthStencil);

    if (savedTarget) {
        savedTarget->Release();
    }
    if (savedDepthStencil) {
        savedDepthStencil->Release();
    }
}
