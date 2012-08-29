
#include "configuration.h"
#include "distantland.h"
#include "distantshader.h"
#include "postshaders.h"
#include "doublesurface.h"
#include "mwbridge.h"


void DistantLand::renderWaterReflection(const D3DXMATRIX *view, const D3DXMATRIX *proj)
{
    DECLARE_MWBRIDGE

    // Switch to render target (borrow shadow z-buffer)
    RenderTargetSwitcher rtsw(texReflection, surfShadowZ);
    device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, horizonCol, 1.0, 0);

    // Calculate reflected view matrix, mirror plane at water mesh level
    D3DXMATRIX reflView;
    D3DXPLANE plane(0, 0, 1.0, -(mwBridge->WaterLevel() - 1.0));
    D3DXMatrixReflect(&reflView, &plane);
    D3DXMatrixMultiply(&reflView, &reflView, view);
    effect->SetMatrix(ehView, &reflView);

    // Calculate new projection
    D3DXMATRIX reflProj = *proj;
    editProjectionZ(&reflProj, 4.0, Configuration.DL.DrawDist * 8192.0);
    effect->SetMatrix(ehProj, &reflProj);

    // Clipping setup
    D3DXMATRIX clipMat;

    // Clip geometry on opposite side of water plane
    plane *= mwBridge->IsUnderwater(eyePos.z) ? -1.0 : 1.0;

    // If using dynamic ripples, the water level can be lowered by up to 0.5 * waveheight
    // so move clip plane downwards at the cost of some reflection errors
    if(Configuration.MGEFlags & DYNAMIC_RIPPLES)
        plane.d += 0.5 * Configuration.DL.WaterWaveHeight;

    // Doing inverses separately is a lot more numerically stable
    D3DXMatrixInverse(&clipMat, 0, &reflView);
    D3DXMatrixTranspose(&clipMat, &clipMat);
    D3DXPlaneTransform(&plane, &plane, &clipMat);

    D3DXMatrixInverse(&clipMat, 0, &reflProj);
    D3DXMatrixTranspose(&clipMat, &clipMat);
    D3DXPlaneTransform(&plane, &plane, &clipMat);

    device->SetClipPlane(0, plane);
    device->SetRenderState(D3DRS_CLIPPLANEENABLE, 1);

    if(mwBridge->IsExterior() && (Configuration.MGEFlags & REFLECTIVE_WATER))
    {
        // Draw land reflection, with opposite culling
        effect->BeginPass(PASS_RENDERLANDREFL);
        device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        renderDistantLand(effect, &reflView, &reflProj);
        effect->EndPass();
    }

    if(isDistantCell() && (Configuration.MGEFlags & REFLECT_NEAR))
    {
        // Draw statics reflection, with opposite culling and no dissolve
        DWORD p = (mwBridge->CellHasWeather() && !mwBridge->IsUnderwater(eyePos.z)) ? PASS_RENDERSTATICSEXTERIOR : PASS_RENDERSTATICSINTERIOR;
        effect->SetFloat(ehDissolveRange, 0);
        effect->BeginPass(p);
        device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        renderReflectedStatics(&reflView, &reflProj);
        effect->EndPass();
    }

    if((Configuration.MGEFlags & REFLECT_SKY) && !recordSky.empty() && !mwBridge->IsUnderwater(eyePos.z))
    {
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

void DistantLand::renderReflectedSky()
{
    float adjustZ = -2.0 * eyePos.z;

    for(vector<RenderedState>::iterator i = recordSky.begin(); i != recordSky.end(); ++i)
    {
        // Adjust world transform, as skydome is positioned in eye space instead of world space
        i->worldTransforms[0]._43 += adjustZ;

        // Re-adjust sky to approximate change in visible normal distribution with distance
        // Normals pointing away are obscured by waves, so median normal will change
        if(i->texture == 0)
            i->worldTransforms[0]._43 += 600.0;

        effect->SetMatrix(ehWorld, &i->worldTransforms[0]);
        effect->SetBool(ehHasAlpha, i->texture != 0);
        effect->SetTexture(ehTex0, i->texture);
        effect->CommitChanges();
        device->SetRenderState(D3DRS_ALPHABLENDENABLE, i->texture ? 1 : 0);

        device->SetStreamSource(0, i->vb, i->vbOffset, i->vbStride);
        device->SetIndices(i->ib);
        device->SetFVF(i->fvf);
        device->DrawIndexedPrimitive(i->primType, i->baseIndex, i->minIndex, i->vertCount, i->startIndex, i->primCount);
    }
}

void DistantLand::renderReflectedStatics(const D3DXMATRIX *view, const D3DXMATRIX *proj)
{
    // Select appropriate static clipping distance
    D3DXMATRIX ds_proj = *proj, ds_viewproj;
    float zn = 4.0f, zf = Configuration.DL.NearStaticEnd * 8192.0f;

    // Don't draw beyond fully fogged distance; early out if frustum is empty
    zf = min(fogEnd, zf);
    if(zf <= zn)
        return;

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

void DistantLand::clearReflection()
{
    DECLARE_MWBRIDGE
    IDirect3DSurface9 *target;
    DWORD baseColour;

    texReflection->GetSurfaceLevel(0, &target);
    if(mwBridge->CellHasWeather() || mwBridge->IsUnderwater(eyePos.z))
    {
        // Use fog colour as reflection
        baseColour = (DWORD)horizonCol;
    }
    else
    {
        // Interior fog colour is typically too bright
        // Guess a reflection colour based on cell lighting parameters
        const BYTE *sun = mwBridge->getInteriorSun();
        RGBVECTOR c(sun[0] / 255.0, sun[1] / 255.0, sun[2] / 255.0);
        c += ambCol;
        baseColour = (DWORD)c;
    }
    device->ColorFill(target, 0, baseColour);
    target->Release();
}

void DistantLand::simulateDynamicWaves()
{
    DECLARE_MWBRIDGE

    static bool resetRippleSurface = true;
    static float remainingWaveTime = 0;
    static const float waveStep = 0.0125f;  // time per wave simulation step (1/80 sec)

    device->SetFVF(fvfWave);
    device->SetStreamSource(0, vbWaveSim, 0, 32);

    // Calc number of wave iterations to run this frame
    float frameTime = std::min(mwBridge->frameTime(), 0.5f);
    remainingWaveTime += frameTime;
    int numWaveSteps = (int)(remainingWaveTime / waveStep);
    remainingWaveTime -= numWaveSteps * waveStep;

    // Preciptation (rain/snow) ripples
    if(mwBridge->CellHasWeather())
    {
        static float remainingRipples = 0;

        // Reset surface when not needed next time
        resetRippleSurface = true;

        // Weather types: rain = 4; thunderstorm = 5; snow = 8; blizzard = 9
        // Thunderstorm causes 50% more ripples
        int w0 = mwBridge->GetCurrentWeather(), w1 = mwBridge->GetNextWeather();
        float precipitation0 = (w0 == 4 || w0 == 5 || w0 == 8 || w0 == 9) ? 1.0 : -1.5;
        float precipitation1 = (w1 == 4 || w1 == 5 || w1 == 8 || w1 == 9) ? 1.0 : -1.5;
        precipitation0 += (w0 == 5) ? 0.5 : 0;
        precipitation1 += (w1 == 5) ? 0.5 : 0;

        // 150 drops per second for normal precipitation
        float precipitation = (1.0 - mwBridge->GetWeatherRatio()) * precipitation0 + mwBridge->GetWeatherRatio() * precipitation1;
        float rippleFrequency = 150.0 * precipitation;

        if(rippleFrequency > 0)
        {
            static double randomizer = 0.546372819;
            int ripplePos[2];
            RECT drop;

            remainingRipples += rippleFrequency * frameTime;

            while(remainingRipples >= 1.0f)
            {
                // Place rain ripple at random location
                for(int i = 0; i != 2; ++i)
                {
                    randomizer = randomizer * (1337.134511337451 + 0.0001 * rand()) + 0.12351523;
                    randomizer -= floor(randomizer);
                    ripplePos[i] = (int)(randomizer * waveTexResolution);
                }

                drop.left = ripplePos[0] - 2;
                drop.right = ripplePos[0] + 2;
                drop.top = ripplePos[1] - 1;
                drop.bottom = ripplePos[1] + 1;
                device->ColorFill(surfRain, &drop, 0x80806060);

                drop.left = ripplePos[0] - 1;
                drop.right = ripplePos[0] + 1;
                drop.top = ripplePos[1] - 2;
                drop.bottom = ripplePos[1] + 2;
                device->ColorFill(surfRain, &drop, 0x80806060);

                drop.left = ripplePos[0] - 1;
                drop.right = ripplePos[0] + 1;
                drop.top = ripplePos[1] - 1;
                drop.bottom = ripplePos[1] + 1;
                device->ColorFill(surfRain, &drop, 0x80804040);

                remainingRipples -= 1.0f;
            }
        }

        // Apply wave equation numWaveSteps times
        // Uses double buffering to avoid reads and writes on the same target
        RenderTargetSwitcher rtsw(surfRippleBuffer, NULL);
        SurfaceDoubleBuffer doublebuffer;
        doublebuffer.init(texRain, surfRain, texRippleBuffer, surfRippleBuffer);

        effect->BeginPass(PASS_WAVESTEP);
        for(int i = 0; i != numWaveSteps; ++i)
        {
            device->SetRenderTarget(0, doublebuffer.sinkSurface());
            effect->SetTexture(ehTex4, doublebuffer.sourceTexture());
            effect->CommitChanges();

            device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);
            doublebuffer.cycle();
        }
        effect->EndPass();

        if(doublebuffer.sourceSurface() != surfRain)
            device->StretchRect(surfRippleBuffer, 0, surfRain, 0, D3DTEXF_NONE);
    }
    else if(resetRippleSurface)
    {
        // No weather - clear rain ripples
        device->ColorFill(surfRain, 0, 0x80808080);
        resetRippleSurface = false;
    }

    // Player local ripples
    // Move ripple texture with player; lock to texel alignment to prevent visible jitter
    const D3DXVECTOR3 *playerPos = (const D3DXVECTOR3 *)mwBridge->PlayerPositionPointer();
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

    device->ColorFill(surfRippleBuffer, 0, 0x80808080);
    device->StretchRect(surfRipples, &source, surfRippleBuffer, &target, D3DTEXF_NONE);

    // Water simulation; realigned water starts in surfRippleBuffer
    // Uses double buffering to avoid reads and writes on the same target
    RenderTargetSwitcher rtsw(surfRipples, NULL);
    SurfaceDoubleBuffer doublebuffer;
    doublebuffer.init(texRippleBuffer, surfRippleBuffer, texRipples, surfRipples);

    float rippleOrigin[2];
    float dz = playerPos->z - mwBridge->WaterLevel();
    if(dz < 0 && dz > -128.0f * mwBridge->PlayerHeight())
    {
        // Create waves around the player
        effect->BeginPass(PASS_PLAYERWAVE);
        for(int i = 0; i != numWaveSteps; ++i)
        {
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
    for(int i = 0; i != numWaveSteps; ++i)
    {
        device->SetRenderTarget(0, doublebuffer.sinkSurface());
        effect->SetTexture(ehTex4, doublebuffer.sourceTexture());
        effect->CommitChanges();

        device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);
        doublebuffer.cycle();
    }
    effect->EndPass();

    if(doublebuffer.sourceSurface() != surfRipples)
        device->StretchRect(surfRippleBuffer, 0, surfRipples, 0, D3DTEXF_NONE);

    // Set wave texture world origin
    static float halfWaveTexWorldSize = 0.5f * waveTexWorldRes * waveTexResolution;
    rippleOrigin[0] = lastXpos*waveTexWorldRes - halfWaveTexWorldSize;
    rippleOrigin[1] = lastYpos*waveTexWorldRes - halfWaveTexWorldSize;
    effect->SetFloatArray(ehRippleOrigin, rippleOrigin, 2);

    // Set weather-dependent wave height
    effect->SetFloat(ehWaveHeight, (float)Configuration.DL.WaterWaveHeight);
}

void DistantLand::renderWaterPlane()
{
    DECLARE_MWBRIDGE
    D3DXMATRIX m;

    IDirect3DTexture9 *texRefract = PostShaders::borrowBuffer(0);

    D3DXMatrixTranslation(&m, eyePos.x, eyePos.y, mwBridge->WaterLevel());
    effect->SetMatrix(ehWorld, &m);
    effect->SetTexture(ehTex0, texReflection);
    effect->SetTexture(ehTex1, texWater);
    effect->SetTexture(ehTex2, texRefract);
    effect->SetTexture(ehTex3, texDepthFrame);
    if(Configuration.MGEFlags & DYNAMIC_RIPPLES)
    {
        effect->SetTexture(ehTex4, texRain);
        effect->SetTexture(ehTex5, texRipples);
    }
    effect->CommitChanges();

    device->SetVertexDeclaration(WaterDecl);
    device->SetStreamSource(0, vbWater, 0, 12);
    device->SetIndices(ibWater);
    device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numWaterVerts, 0, numWaterTris);
}
