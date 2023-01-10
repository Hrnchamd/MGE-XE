
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

    // Update current cell and select distant static set
    selectDistantCell();

    // Get Morrowind camera matrices
    device->GetTransform(D3DTS_VIEW, &mwView);
    device->GetTransform(D3DTS_PROJECTION, &mwProj);

    // Set variables derived from current game state and camera configuration
    setView(&mwView);
    adjustFog();
    setupCommonEffect(&mwView, &mwProj);
    FixedFunctionShader::updateLighting(lightSunMult, lightAmbMult);

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
            editProjectionZ(&distProj, kDistantNearPlane - 1e-2, Configuration.DL.DrawDist * kCellSize);
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
                if (Configuration.MGEFlags & USE_DISTANT_STATICS) {
                    DWORD p = mwBridge->CellHasWeather() ? PASS_RENDERSTATICSEXTERIOR : PASS_RENDERSTATICSINTERIOR;
                    effect->BeginPass(p);
                    vsr.beginAlphaToCoverage(device);

                    cullDistantStatics(&mwView, &distProj);
                    renderDistantStatics();

                    vsr.endAlphaToCoverage(device);
                    effect->EndPass();
                }
                else {
                    visDistant.RemoveAll();
                }
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
                effect->BeginPass(isPPLActive ? PASS_RENDERSHADOWFFE : PASS_RENDERSHADOW);
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
                effect->BeginPass(isPPLActive ? PASS_RENDERSHADOWFFE : PASS_RENDERSHADOW);
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
    bool isExpFog = (Configuration.MGEFlags & EXP_FOG) != 0;
    const RGBVECTOR* skyCol = mwBridge->CellHasWeather() ?  mwBridge->getCurrentWeatherSkyCol() : &horizonCol;
    effect->SetFloat(ehFogStart, isExpFog ? fogExpStart : fogStart);
    effect->SetFloat(ehFogRange, isExpFog ? fogExpDivisor : fogEnd);
    effect->SetFloat(ehFogNearStart, fogNearStart);
    effect->SetFloat(ehFogNearRange, fogNearEnd);
    effect->SetFloatArray(ehSkyCol, *skyCol, 3);
    effect->SetFloatArray(ehFogColNear, nearFogCol, 3);
    effect->SetFloatArray(ehFogColFar, horizonCol, 3);
    effect->SetFloat(ehNearViewRange, nearViewRange);
    effect->SetFloat(ehNiceWeather, niceWeather);

    if (ehOutscatter) {
        effect->SetFloatArray(ehOutscatter, atmOutscatter, 3);
        effect->SetFloatArray(ehInscatter, atmInscatter, 3);
        effect->SetFloatArray(ehSkyScatterFar, atmSkylightScatter, 4);
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

        // Use considerably less fog offset in exp fog mode, to retain near visibility comparable to vanilla
        if ((Configuration.MGEFlags & USE_DISTANT_LAND) && (Configuration.MGEFlags & EXP_FOG)) {
            fo *= 0.25f;
        }

        // Fog distance scale calculation, ensure fogEnd does not scale closer than vanilla Morrowind
        fogEnd = std::max(0.875f, ff * Configuration.DL.AboveWaterFogEnd);
        fogStart = ff * Configuration.DL.AboveWaterFogStart - fo * fogEnd;
        windScaling = ws;
    } else {
        // Avoid density == 0, as when fogStart and fogEnd are equal, the fog equation denominator goes to infinity
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

    if ((Configuration.MGEFlags & USE_DISTANT_LAND) && isDistantCell()) {
        // Set hardware fog for Morrowind's use
        if (Configuration.MGEFlags & EXP_FOG) {
            // Exponential fog mode
            // Adjust exp curve so that at the fog end boundary, the same fog value is reached for all values of fogStart
            constexpr float expFogDistScale = 4.4f;
            fogExpStart = fogStart / expFogDistScale;
            fogExpDivisor = (fogEnd - fogExpStart) / expFogDistScale;

            if (mwBridge->IsUnderwater(eyePos.z) || !mwBridge->CellHasWeather()) {
                // Leave fog ranges as set, shaders use all linear fogging in this case
                fogNearStart = fogStart;
                fogNearEnd = fogEnd;
            } else {
                // Adjust near region linear Morrowind fogging to approximation of exp fog curve
                // Linear density matched to exp fog at dist = 1280 and dist = viewrange (or fog end if closer)
                // Note to self: Don't use saturate here or the denominators can become zero.
                float farIntercept = std::min(fogEnd, nearViewRange);
                float expFogNear = exp(-(1280.0f - fogExpStart) / fogExpDivisor);
                float expFogFar = exp(-(farIntercept - fogExpStart) / fogExpDivisor);
                fogNearStart = 1280.0f + (farIntercept - 1280.0f) * (1.0f - expFogNear) / (expFogFar - expFogNear);
                fogNearEnd = 1280.0f + (farIntercept - 1280.0f) * -expFogNear / (expFogFar - expFogNear);
            }
        } else {
            // Linear mode
            fogNearStart = fogStart;
            fogNearEnd = fogEnd;
        }

        device->SetRenderState(D3DRS_FOGSTART, *(DWORD*)&fogNearStart);
        device->SetRenderState(D3DRS_FOGEND, *(DWORD*)&fogNearEnd);
    } else {
        // Update fog when near render distance changes, and on startup when fogNearEnd == 0
        bool doFogUpdate = fogNearEnd != nearViewRange;

        // Read Morrowind-set fog range
        fogNearEnd = nearViewRange;
        fogNearStart = fogNearEnd * std::min(1.0f - mwBridge->getScenegraphFogDensity(), 0.99f);
        fogStart = fogNearStart;
        fogEnd = fogNearEnd;

        if (doFogUpdate) {
            device->SetRenderState(D3DRS_FOGSTART, *(DWORD*)&fogNearStart);
            device->SetRenderState(D3DRS_FOGEND, *(DWORD*)&fogNearEnd);
        }
    }

    // Adjust Morrowind fog colour towards scatter colour if necessary
    if ((Configuration.MGEFlags & USE_DISTANT_LAND) && (Configuration.MGEFlags & USE_ATM_SCATTER) && mwBridge->CellHasWeather() && !mwBridge->IsUnderwater(eyePos.z)) {
        // Read unadjusted colour, as the scenegraph fog colour may not be updated during menu transitions
        RGBVECTOR c0 = *mwBridge->getCurrentWeatherFogCol();
        RGBVECTOR c1 = c0;

        // Simplified version of scattering from the shader
        const RGBVECTOR* skyCol = mwBridge->getCurrentWeatherSkyCol();
        const D3DXVECTOR3 newSkyCol = {
            float(lerp(skyCol->r, atmSkylightScatter.x, atmSkylightScatter.w)),
            float(lerp(skyCol->g, atmSkylightScatter.y, atmSkylightScatter.w)),
            float(lerp(skyCol->b, atmSkylightScatter.z, atmSkylightScatter.w))
        };
        const float sunaltitude = powf(1 + sunPos.z, 10);
        const float sunaltitude_a = 2.8 + 4.3 / sunaltitude;
        const float sunaltitude_b = saturate(1.0 - exp2(-1.9 * sunaltitude));
        const float sunaltitude_c = saturate(exp(-4.0 * sunPos.z)) * saturate(sunaltitude);

        // Calculate scatter colour at Morrowind draw distance boundary
        float fogdist = (nearViewRange - fogExpStart) / fogExpDivisor;
        float fog = saturate(exp(-fogdist));
        fogdist = saturate(0.224 * fogdist);

        D3DXVECTOR2 horizonDir(eyeVec.x, eyeVec.y);
        D3DXVec2Normalize(&horizonDir, &horizonDir);
        float suncos =  horizonDir.x * sunPos.x + horizonDir.y * sunPos.y;
        float mie = (1.58 / (1.24 - suncos)) * sunaltitude_c;
        float rayl = 1.0 - 0.09 * mie;
        float atmdep = 1.33;

        D3DXVECTOR3 scatter;
        float scatterT = 0.5 * (1 + suncos);
        scatter.x = float(lerp(atmInscatter.r, atmOutscatter.r, scatterT));
        scatter.y = float(lerp(atmInscatter.g, atmOutscatter.g, scatterT));
        scatter.z = float(lerp(atmInscatter.b, atmOutscatter.b, scatterT));

        D3DXVECTOR3 att = atmdep * scatter * (sunaltitude_a + 0.7 * mie);
        att.x = (1 - exp(-fogdist * att.x)) / att.x;
        att.y = (1 - exp(-fogdist * att.y)) / att.y;
        att.z = (1 - exp(-fogdist * att.z)) / att.z;

        D3DXVECTOR3 k0 = mie * D3DXVECTOR3(0.125, 0.125, 0.125) + rayl * newSkyCol;
        D3DXVECTOR3 k1 = att * (1.17 * atmdep + 0.89) * sunaltitude_b;
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

        // Capture pre-UI screenshots here
        checkCaptureScreenshot(false);

        // Cache render for first frame of menu mode
        if ((Configuration.MGEFlags & USE_MENU_CACHING) && mwBridge->IsMenu()) {
            texDistantBlend = PostShaders::borrowBuffer(0);
            isRenderCached = true;
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
    bool isExpFog = (Configuration.MGEFlags & EXP_FOG) != 0;
    shader->SetFloatArray(EV_fogcol, horizonCol, 3);
    shader->SetFloatArray(EV_fognearcol, nearFogCol, 3);
    shader->SetFloat(EV_fogstart, isExpFog ? fogExpStart : fogStart);
    shader->SetFloat(EV_fogrange, isExpFog ? fogExpDivisor : fogEnd);
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
        // Scan dynamic vis on cell change
        void* playerCell = mwBridge->getPlayerCell();
        if (playerCell != lastDistantVisCell) {
            scanDynamicVisGroups();
            lastDistantVisCell = playerCell;
        }

        // Get worldspace key
        string cellname;
        if (mwBridge->IsExterior()) {
            cellname = string();
        }
        else {
            cellname = mwBridge->getInteriorName();
        }

        const auto iWS = mapWorldSpaces.find(cellname);
        if (iWS != mapWorldSpaces.end()) {
            currentWorldSpace = &iWS->second;
            return true;
        }
    }

    currentWorldSpace = nullptr;
    return false;
}

// isDistantCell - Check if there is distant land selected for this cell
bool DistantLand::isDistantCell() {
    return currentWorldSpace != nullptr;
}

// resolveDynamicVisGroups - Resolve pointers to game objects on load/reload
void DistantLand::resolveDynamicVisGroups() {
    auto mwBridge = MWBridge::get();
    const DynamicVisGroup *lastDVG = nullptr;

    for (auto& vis : dynamicVisGroups) {
        // Clear previous pointer
        vis.gameObject = nullptr;

        // Re-use previous result if the id matches
        if (lastDVG && vis.id == lastDVG->id) {
            vis.gameObject = lastDVG->gameObject;
            continue;
        }
        else {
            lastDVG = &vis;
        }

        // Resolve IDs to pointers
        switch (vis.source) {
        case DynamicVisGroup::DataSource::Journal:
            vis.gameObject = mwBridge->getDialogue(vis.id.c_str());
            break;
        case DynamicVisGroup::DataSource::Global:
            vis.gameObject = mwBridge->getGlobalVar(vis.id.c_str());
            break;
        case DynamicVisGroup::DataSource::UniqueObject:
            vis.gameObject = mwBridge->findFirstReferenceById(vis.id.c_str());
            break;
        }
    }

    // Ensure reloading into the same cell still triggers updates
    lastDistantVisCell = nullptr;
}

// scanDynamicVisGroups - Scan through game data for visibility changes
void DistantLand::scanDynamicVisGroups() {
    auto mwBridge = MWBridge::get();

    for (auto& vis : dynamicVisGroups) {
        int value;

        // Ignore unresolved objects
        if (!vis.gameObject) {
            continue;
        }

        switch (vis.source) {
        case DynamicVisGroup::DataSource::Journal:
            value = mwBridge->getJournalIndex(vis.gameObject);
            break;
        case DynamicVisGroup::DataSource::Global:
            value = int(mwBridge->getGlobalVarValue(vis.gameObject));
            break;
        case DynamicVisGroup::DataSource::UniqueObject:
            const int disabledRecordFlag = 0x800;
            value = (mwBridge->getRecordFlags(vis.gameObject) & disabledRecordFlag) == 0;
            break;
        }

        // Enable if value is inside any range
        bool enable = false;
        for (const auto& r : vis.ranges) {
            if (r.begin <= value && value < r.end) {
                enable = true;
                break;
            }
        }

        // If enable state has changed, propagate to distant land mesh instances
        if (enable ^ vis.enabled) {
            vis.enabled = enable;
            for (auto& m : vis.references) {
                m->enabled = enable;
            }
        }
    }
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
        editProjectionZ(proj, kDistantNearPlane, Configuration.DL.DrawDist * kCellSize);
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
    // Sun is used for both interiors and exteriors; the sun in interiors is a fixed light
    sunVec.x = s->Direction.x;
    sunVec.y = s->Direction.y;
    sunVec.z = s->Direction.z;
    D3DXVec3Normalize((D3DXVECTOR3*)&sunVec, (D3DXVECTOR3*)&sunVec);

    sunCol = s->Diffuse;
    sunAmb = s->Ambient;
}

// inspectIndexedPrimitive
// Filters and records DIP calls for later use; returning false should cause the draw call to be skipped
// Can also replace selected fixed function calls with an augmented shader
bool DistantLand::inspectIndexedPrimitive(int sceneCount, const RenderedState* rs, const FragmentState* frs, LightState* lightrs) {
    auto mwBridge = MWBridge::get();

    // Avoid recording landscape alpha blend drawcalls, a form of multi-pass splatting
    static IDirect3DVertexBuffer9* lastVB = nullptr;
    bool isLandSplat = sceneCount == 0 && rs->vb == lastVB && rs->blendEnable && (rs->fvf & D3DFVF_DIFFUSE) && mwBridge->IsExterior();
    lastVB = rs->vb;

    // Avoid recording decal passes from UV sets >0, shadow rendering only samples alpha from texture 0 with UV 0
    const auto& stage0 = frs->stage[0];
    bool isDecal = stage0.texcoordIndex != 0 && (stage0.colorArg1 == D3DTA_TEXTURE || stage0.colorArg2 == D3DTA_TEXTURE);

    // Capture all writes to z-buffer, except detectable second passes of multi-pass rendering
    if (rs->zWrite && !isLandSplat && !isDecal) {
        recordMW.emplace_back(*rs);

        // Unify alpha test operator/reference to be equivalent to GREATEREQUAL
        if (rs->alphaFunc == D3DCMP_GREATER) {
            recordMW.back().alphaRef++;
        }
    }

    // Special case, capture sky
    if (recordMW.empty() && rs->blendEnable && sceneCount == 0 && mwBridge->CellHasWeather()) {
        recordSky.emplace_back(*rs);

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

// requestCapture - Set a function to be called with a screen capture
// Either before the UI is drawn, or after UI and before MGE messages
void DistantLand::requestCapture(std::function<void(IDirect3DSurface9*)> handler, bool captureWithUI) {
    captureScreenHandler = handler;
    captureScreenWithUI = captureWithUI;
}

void DistantLand::checkCaptureScreenshot(bool isUIDrawn) {
    if (bool(captureScreenHandler) && captureScreenWithUI == isUIDrawn) {
        IDirect3DSurface9* surface = captureScreenshot();
        captureScreenHandler(surface);
        if (surface) {
            surface->Release();
        }
        captureScreenHandler = nullptr;
    }
}

// captureScreen - Capture a screenshot
IDirect3DSurface9* DistantLand::captureScreenshot() {
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


// ------------------------------------
// DistantLand::RecordedState

DistantLand::RecordedState::RecordedState(const RenderedState& state)
    : RenderedState(state) {
    vb->AddRef();
    ib->AddRef();
    if (texture) {
        texture->AddRef();
    }
}

DistantLand::RecordedState::~RecordedState() {
    if (vb) {
        vb->Release();
    }
    if (ib) {
        ib->Release();
    }
    if (texture) {
        texture->Release();
    }
}

DistantLand::RecordedState::RecordedState(RecordedState&& source) noexcept
    : RenderedState(source) {
    source.vb = nullptr;
    source.ib = nullptr;
    source.texture = nullptr;
}


// ------------------------------------
// RenderTargetSwitcher

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
