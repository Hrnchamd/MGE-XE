
#include "distantland.h"
#include "distantshader.h"
#include "configuration.h"
#include "doublesurface.h"
#include "mwbridge.h"
#include "postshaders.h"



void DistantLand::renderWaterReflection(const D3DXMATRIX* view, const D3DXMATRIX* proj) {
    auto mwBridge = MWBridge::get();

    // Switch to render target
    RenderTargetSwitcher rtsw(texReflection, surfReflectionZ);
    device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, horizonCol, 1.0, 0);

    // Calculate reflected view matrix, mirror plane at water mesh level
    D3DXMATRIX reflView;
    D3DXPLANE plane(0, 0, 1.0f, -(mwBridge->WaterLevel() - 1.0f));
    D3DXMatrixReflect(&reflView, &plane);
    D3DXMatrixMultiply(&reflView, &reflView, view);
    effect->SetMatrix(ehView, &reflView);

    // Calculate new projection
    D3DXMATRIX reflProj = *proj;
    editProjectionZ(&reflProj, 4.0, Configuration.DL.DrawDist * kCellSize);
    effect->SetMatrix(ehProj, &reflProj);

    // Clipping setup
    D3DXMATRIX clipMat;

    // Clip geometry on opposite side of water plane
    plane *= mwBridge->IsUnderwater(eyePos.z) ? -1.0f : 1.0f;

    // If using dynamic ripples, the water level can be lowered by up to 0.5 * waveheight
    // so move clip plane downwards at the cost of some reflection errors
    if (Configuration.MGEFlags & DYNAMIC_RIPPLES) {
        plane.d += 0.5f * Configuration.DL.WaterWaveHeight;
    }

    // Doing inverses separately is a lot more numerically stable
    D3DXMatrixInverse(&clipMat, 0, &reflView);
    D3DXMatrixTranspose(&clipMat, &clipMat);
    D3DXPlaneTransform(&plane, &plane, &clipMat);

    D3DXMatrixInverse(&clipMat, 0, &reflProj);
    D3DXMatrixTranspose(&clipMat, &clipMat);
    D3DXPlaneTransform(&plane, &plane, &clipMat);

    if (visDistant.size() == 0) {
        // Workaround for a Direct3D bug with clipping planes, where SetClipPlane
        // has no effect on the shader pipeline if the last rendered draw call was using
        // the fixed function pipeline. This is usually covered by distant statics, but
        // not in compact interiors where all distant statics may be culled.
        // Provoking a DrawPrimitive with shader here makes the following SetClipPlane work.
        effect->BeginPass(PASS_WORKAROUND);
        device->SetVertexDeclaration(WaterDecl);
        device->SetStreamSource(0, vbFullFrame, 0, 12);
        device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
        effect->EndPass();
    }

    device->SetClipPlane(0, plane);
    device->SetRenderState(D3DRS_CLIPPLANEENABLE, 1);

    // Rendering
    if (mwBridge->IsExterior() && (Configuration.MGEFlags & REFLECTIVE_WATER)) {
        // Draw land reflection, with opposite culling
        effect->BeginPass(PASS_RENDERLANDREFL);
        device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        renderDistantLand(effect, &reflView, &reflProj);
        effect->EndPass();
    }

    if (isDistantCell() && (Configuration.MGEFlags & REFLECT_NEAR)) {
        // Draw statics reflection, with opposite culling and no dissolve
        DWORD p = (mwBridge->CellHasWeather() && !mwBridge->IsUnderwater(eyePos.z)) ? PASS_RENDERSTATICSEXTERIOR : PASS_RENDERSTATICSINTERIOR;
        effect->SetFloat(ehNearViewRange, 0);
        effect->BeginPass(p);
        device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        renderReflectedStatics(&reflView, &reflProj);
        effect->EndPass();
        effect->SetFloat(ehNearViewRange, nearViewRange);
    }

    if ((Configuration.MGEFlags & REFLECT_SKY) && !recordSky.empty() && !mwBridge->IsUnderwater(eyePos.z)) {
        // Draw sky reflection, with opposite culling
        effect->BeginPass(PASS_RENDERSKY);
        device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        renderReflectedSky();
        effect->EndPass();
    }

    // Restore view state
    device->SetRenderState(D3DRS_CLIPPLANEENABLE, 0);
    effect->SetMatrix(ehView, view);
    effect->SetMatrix(ehProj, proj);
}

void DistantLand::renderReflectedSky() {
    // Sky objects are not correctly positioned at infinity, so correction is required
    const float adjustZ = -2.0f * eyePos.z;

    const auto& recordSky_const = recordSky;
    for (const auto& i : recordSky_const) {
        // Adjust world transform, as skydome objects are positioned relative to the viewer
        D3DXMATRIX worldTransform = i.worldTransforms[0];
        worldTransform._43 += adjustZ;

        if (i.texture == 0) {
            // Inflate sky mesh towards infinity, makes skypos in shader calculate correctly
            D3DXMATRIX scale;
            D3DXMatrixScaling(&scale, 1e6, 1e6, 1e6);
            D3DXMatrixMultiply(&worldTransform, &scale, &worldTransform);
        }

        effect->SetMatrix(ehWorld, &worldTransform);
        effect->SetBool(ehHasAlpha, i.texture != 0);
        effect->SetBool(ehHasBones, i.texture == 0);
        effect->SetTexture(ehTex0, i.texture);
        effect->CommitChanges();
        device->SetRenderState(D3DRS_ALPHABLENDENABLE, i.texture ? 1 : 0);
        device->SetRenderState(D3DRS_SRCBLEND, i.srcBlend);
        device->SetRenderState(D3DRS_DESTBLEND, i.destBlend);

        device->SetStreamSource(0, i.vb, i.vbOffset, i.vbStride);
        device->SetIndices(i.ib);
        device->SetFVF(i.fvf);
        device->DrawIndexedPrimitive(i.primType, i.baseIndex, i.minIndex, i.vertCount, i.startIndex, i.primCount);
    }
}

void DistantLand::renderReflectedStatics(const D3DXMATRIX* view, const D3DXMATRIX* proj) {
    // Select appropriate static clipping distance
    D3DXMATRIX ds_proj = *proj, ds_viewproj;
    float zn = 4.0f, zf = Configuration.DL.NearStaticEnd * kCellSize;

    // Don't draw beyond fully fogged distance; early out if frustum is empty
    zf = std::min(fogEnd, zf);
    if (zf <= zn) {
        return;
    }

    // Create a clipping frustum for visibility determination
    editProjectionZ(&ds_proj, zn, zf);
    ds_viewproj = (*view) * ds_proj;

    // Cull sort and draw
    VisibleSet visReflected;
    ViewFrustum range_frustum(&ds_viewproj);
    D3DXVECTOR4 viewsphere(eyePos.x, eyePos.y, eyePos.z, zf);

    currentWorldSpace->NearStatics->GetVisibleMeshes(range_frustum, viewsphere, visReflected);
    currentWorldSpace->FarStatics->GetVisibleMeshes(range_frustum, viewsphere, visReflected);
    currentWorldSpace->VeryFarStatics->GetVisibleMeshes(range_frustum, viewsphere, visReflected);
    visReflected.SortByState();

    device->SetVertexDeclaration(StaticDecl);
    visReflected.Render(device, effect, effect, &ehTex0, 0, &ehWorld, SIZEOFSTATICVERT);
}

void DistantLand::clearReflection() {
    auto mwBridge = MWBridge::get();
    IDirect3DSurface9* target;
    DWORD baseColour;

    texReflection->GetSurfaceLevel(0, &target);
    if (mwBridge->CellHasWeather() || mwBridge->IsUnderwater(eyePos.z)) {
        // Use fog colour as reflection
        baseColour = (DWORD)horizonCol;
    } else {
        // Interior fog colour is typically too bright
        // Guess a reflection colour based on cell lighting parameters
        const BYTE* sun = mwBridge->getInteriorSun();
        RGBVECTOR c(sun[0] / 255.0f, sun[1] / 255.0f, sun[2] / 255.0f);
        c += ambCol;
        baseColour = (DWORD)c;
    }
    device->ColorFill(target, 0, baseColour);
    target->Release();
}

void DistantLand::simulateDynamicWaves() {
    auto mwBridge = MWBridge::get();

    static bool resetRippleSurface = true;
    static float remainingWaveTime = 0;
    static const float waveStep = 0.0125f;  // time per wave simulation step (1/80 sec)

    // Simulation paused in menu mode
    if (mwBridge->IsMenu()) {
        return;
    }

    device->SetFVF(fvfWave);
    device->SetStreamSource(0, vbWaveSim, 0, 32);

    // Calc number of wave iterations to run this frame
    float frameTime = std::min(mwBridge->frameTime(), 0.5f);
    remainingWaveTime += frameTime;
    int numWaveSteps = (int)(remainingWaveTime / waveStep);
    remainingWaveTime -= numWaveSteps * waveStep;

    // Preciptation (rain/snow) ripples
    if (mwBridge->CellHasWeather()) {
        static float remainingRipples = 0;

        // Reset surface when not needed next time
        resetRippleSurface = true;

        // Weather types: rain = 4; thunderstorm = 5; snow = 8; blizzard = 9
        // Thunderstorm causes 50% more ripples
        int w0 = mwBridge->GetCurrentWeather(), w1 = mwBridge->GetNextWeather();
        float precipitation0 = (w0 == 4 || w0 == 5 || w0 == 8 || w0 == 9) ? 1.0f : -1.5f;
        float precipitation1 = (w1 == 4 || w1 == 5 || w1 == 8 || w1 == 9) ? 1.0f : -1.5f;
        precipitation0 += (w0 == 5) ? 0.5f : 0;
        precipitation1 += (w1 == 5) ? 0.5f : 0;

        // 150 drops per second for normal precipitation
        float precipitation = (1.0f - mwBridge->GetWeatherRatio()) * precipitation0 + mwBridge->GetWeatherRatio() * precipitation1;
        float rippleFrequency = 150.0f * precipitation;

        if (rippleFrequency > 0) {
            static double randomizer = 0.546372819;
            int ripplePos[2];
            RECT drop;

            remainingRipples += rippleFrequency * frameTime;
            int n = int(std::floor(remainingRipples));
            remainingRipples -= n;

            while (n-- > 0) {
                // Place rain ripple at random location
                for (int i = 0; i != 2; ++i) {
                    randomizer = randomizer * (1337.134511337451 + 0.0001 * rand()) + 0.12351523;
                    randomizer -= floor(randomizer);
                    ripplePos[i] = (int)(randomizer * waveTexResolution);
                }

                drop.left = ripplePos[0] - 2;
                drop.right = ripplePos[0] + 2;
                drop.top = ripplePos[1] - 1;
                drop.bottom = ripplePos[1] + 1;
                device->ColorFill(surfRain, &drop, 0x6060);

                drop.left = ripplePos[0] - 1;
                drop.right = ripplePos[0] + 1;
                drop.top = ripplePos[1] - 2;
                drop.bottom = ripplePos[1] + 2;
                device->ColorFill(surfRain, &drop, 0x6060);

                drop.left = ripplePos[0] - 1;
                drop.right = ripplePos[0] + 1;
                drop.top = ripplePos[1] - 1;
                drop.bottom = ripplePos[1] + 1;
                device->ColorFill(surfRain, &drop, 0x4040);
            }
        }

        // Apply wave equation numWaveSteps times
        // Uses double buffering to avoid reads and writes on the same target
        RenderTargetSwitcher rtsw(surfRippleBuffer, NULL);
        SurfaceDoubleBuffer doublebuffer;
        doublebuffer.init(texRain, surfRain, texRippleBuffer, surfRippleBuffer);

        effect->BeginPass(PASS_WAVESTEP);
        for (int i = 0; i != numWaveSteps; ++i) {
            device->SetRenderTarget(0, doublebuffer.sinkSurface());
            effect->SetTexture(ehTex4, doublebuffer.sourceTexture());
            effect->CommitChanges();

            device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);
            doublebuffer.cycle();
        }
        effect->EndPass();

        if (doublebuffer.sourceSurface() != surfRain) {
            device->StretchRect(surfRippleBuffer, 0, surfRain, 0, D3DTEXF_NONE);
        }
    } else if (resetRippleSurface) {
        // No weather - clear rain ripples
        device->ColorFill(surfRain, NULL, 0);
        resetRippleSurface = false;
    }

    // Player local ripples
    // Move ripple texture with player; lock to texel alignment to prevent visible jitter
    const D3DXVECTOR3* playerPos = (const D3DXVECTOR3*)mwBridge->PlayerPositionPointer();
    static int lastXpos = (int)floor(playerPos->x / waveTexWorldRes);
    static int lastYpos = (int)floor(playerPos->y / waveTexWorldRes);

    int newXpos = (int)floor(playerPos->x / waveTexWorldRes);
    int newYpos = (int)floor(playerPos->y / waveTexWorldRes);

    int shiftX = newXpos - lastXpos;
    int shiftY = newYpos - lastYpos;

    lastXpos = newXpos;
    lastYpos = newYpos;

    int shiftXp = (shiftX > 0) ? +shiftX : 0;
    int shiftXn = (shiftX < 0) ? -shiftX : 0;
    int shiftYp = (shiftY > 0) ? +shiftY : 0;
    int shiftYn = (shiftY < 0) ? -shiftY : 0;

    // Shift texture by (shiftX, shiftY) pixels
    RECT source;
    source.left = 1 + shiftXp;
    source.right = waveTexResolution - shiftXn;
    source.top = 1 + shiftYp;
    source.bottom = waveTexResolution - shiftYn;

    RECT target;
    target.left = 1 + shiftXn;
    target.right = waveTexResolution - shiftXp;
    target.top = 1 + shiftYn;
    target.bottom = waveTexResolution - shiftYp;

    device->ColorFill(surfRippleBuffer, 0, 0);
    device->StretchRect(surfRipples, &source, surfRippleBuffer, &target, D3DTEXF_NONE);

    // Water simulation; realigned water starts in surfRippleBuffer
    // Uses double buffering to avoid reads and writes on the same target
    RenderTargetSwitcher rtsw(surfRipples, NULL);
    SurfaceDoubleBuffer doublebuffer;
    doublebuffer.init(texRippleBuffer, surfRippleBuffer, texRipples, surfRipples);

    float rippleOrigin[2];
    float dz = playerPos->z - mwBridge->WaterLevel();
    if (dz < 0 && dz > -128.0f * mwBridge->PlayerHeight()) {
        // Create waves around the player
        effect->BeginPass(PASS_PLAYERWAVE);
        for (int i = 0; i != numWaveSteps; ++i) {
            // Interpolate between starting and ending point, so that low framerates do not cause less waves
            float w = -(float)i / (float)numWaveSteps / (float)waveTexResolution;
            rippleOrigin[0] = w * shiftX + 0.5f;
            rippleOrigin[1] = w * shiftY + 0.5f;

            device->SetRenderTarget(0, doublebuffer.sinkSurface());
            effect->SetTexture(ehTex4, doublebuffer.sourceTexture());
            effect->SetFloatArray(ehRippleOrigin, rippleOrigin, 2);
            effect->CommitChanges();

            device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);
            doublebuffer.cycle();
        }
        effect->EndPass();
    }

    // Apply wave equation numWaveSteps times
    effect->BeginPass(PASS_WAVESTEP);
    for (int i = 0; i != numWaveSteps; ++i) {
        device->SetRenderTarget(0, doublebuffer.sinkSurface());
        effect->SetTexture(ehTex4, doublebuffer.sourceTexture());
        effect->CommitChanges();

        device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);
        doublebuffer.cycle();
    }
    effect->EndPass();

    if (doublebuffer.sourceSurface() != surfRipples) {
        device->StretchRect(surfRippleBuffer, 0, surfRipples, 0, D3DTEXF_NONE);
    }

    // Set wave texture world origin
    static float halfWaveTexWorldSize = 0.5f * waveTexWorldRes * waveTexResolution;
    rippleOrigin[0] = lastXpos*waveTexWorldRes - halfWaveTexWorldSize;
    rippleOrigin[1] = lastYpos*waveTexWorldRes - halfWaveTexWorldSize;
    effect->SetFloatArray(ehRippleOrigin, rippleOrigin, 2);

    // Set weather-dependent wave height
    effect->SetFloat(ehWaveHeight, (float)Configuration.DL.WaterWaveHeight);
}

void DistantLand::renderWaterPlane() {
    D3DXMATRIX m;
    IDirect3DTexture9* texRefract = PostShaders::borrowBuffer(0);

    D3DXMatrixTranslation(&m, eyePos.x, eyePos.y, MWBridge::get()->WaterLevel());
    effect->SetMatrix(ehWorld, &m);
    effect->SetTexture(ehTex0, texReflection);
    effect->SetTexture(ehTex1, texWater);
    effect->SetTexture(ehTex2, texRefract);
    effect->SetTexture(ehTex3, texDepthFrame);
    if (Configuration.MGEFlags & DYNAMIC_RIPPLES) {
        effect->SetTexture(ehTex4, texRain);
        effect->SetTexture(ehTex5, texRipples);
    }
    effect->CommitChanges();

    device->SetVertexDeclaration(WaterDecl);
    device->SetStreamSource(0, vbWater, 0, 12);
    device->SetIndices(ibWater);
    device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numWaterVerts, 0, numWaterTris);
}
