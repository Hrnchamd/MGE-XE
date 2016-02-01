
#include "proxydx/d3d8header.h"
#include "support/log.h"

#include "configuration.h"
#include "distantland.h"
#include "distantshader.h"
#include "mwbridge.h"

static const float shadowNearRadius = 1000.0;
static const float shadowFarRadius = 4000.0;



// renderShadowMap
// Renders multiple shadow map layers to channels in one texture
// Applies filtering to soften shadow edges
// This *must* restore render state on return
void DistantLand::renderShadowMap()
{
    IDirect3DSurface9 *target, *targetSoft;
    texShadow->GetSurfaceLevel(0, &target);
    texSoftShadow->GetSurfaceLevel(0, &targetSoft);

    // Switch to render target
    RenderTargetSwitcher rtsw(targetSoft, surfShadowZ);
    D3DVIEWPORT9 vp;
    device->GetViewport(&vp);

    // Unbind shadow samplers
    effect->SetTexture(ehTex0, 0);
    effect->SetTexture(ehTex2, 0);

    // Clear floating point buffer to far depth
    device->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0, 0);
    effectShadow->BeginPass(PASS_CLEARSHADOWMAP);
    effect->SetBool(ehHasAlpha, false);
    effectShadow->CommitChanges();
    device->SetVertexDeclaration(WaterDecl);
    device->SetStreamSource(0, vbFullFrame, 0, 12);
    device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    effectShadow->EndPass();

    // Render near layer (changes viewport)
    renderShadowLayer(0, shadowNearRadius);

    // Render far layer (changes viewport)
    renderShadowLayer(1, shadowFarRadius);

    // Reset viewport
    device->SetViewport(&vp);

    // Soften shadow map
    device->SetRenderTarget(0, target);
    effectShadow->BeginPass(PASS_SOFTENSHADOWMAP);
    effect->SetTexture(ehTex3, texSoftShadow);
    effect->SetBool(ehHasAlpha, false);     // flag as horizontal filter pass
    effectShadow->CommitChanges();

    device->SetVertexDeclaration(WaterDecl);
    device->SetStreamSource(0, vbFullFrame, 0, 12);
    device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    device->SetRenderTarget(0, targetSoft);
    effect->SetTexture(ehTex3, texShadow);
    effect->SetBool(ehHasAlpha, true);      // flag as vertical filter pass
    effectShadow->CommitChanges();

    device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    effectShadow->EndPass();

    // Clean up surface pointers
    target->Release();
    targetSoft->Release();
}

// renderShadowLayer - Calculates projection for, and renders, one shadow layer
void DistantLand::renderShadowLayer(int layer, float radius)
{
    DECLARE_MWBRIDGE
    D3DXVECTOR3 lookAt, nearPos;
    D3DXVECTOR3 up(0, 0, 1);
    D3DXMATRIX *view = &smView[layer], *proj = &smProj[layer], *viewproj = &smViewproj[layer];

    // Select light vector, sunPos during daytime, sunVec during night
    D3DXVECTOR4 lightVec = (sunPos.z > 0) ? -sunPos : sunVec;

    // Centre of projection is ahead of the player
    // Not as far in z direction as player is likely looking at the ground plane rather than below
    lookAt.x = eyePos.x + radius * eyeVec.x;
    lookAt.y = eyePos.y + radius * eyeVec.y;
    lookAt.z = eyePos.z + 0.5 * radius * eyeVec.z;

    // Quantize projection centre to reduce texture swimming
    lookAt.x = 16.0 * floor(lookAt.x / 16.0);
    lookAt.y = 16.0 * floor(lookAt.y / 16.0);
    lookAt.z = 16.0 * floor(lookAt.z / 16.0);

    // Create shadow frustum centred on lookAt, looking along lightVec
    const float zrange = kCellSize;
    nearPos.x = lookAt.x - zrange * lightVec.x;
    nearPos.y = lookAt.y - zrange * lightVec.y;
    nearPos.z = lookAt.z - zrange * lightVec.z;

    D3DXMatrixLookAtRH(view, &nearPos, &lookAt, &up);
    D3DXMatrixOrthoRH(proj, 2 * radius, (1 + fabs(lightVec.z)) * radius, 0, 2.0 * zrange);
    *viewproj = (*view) * (*proj);

    // Texel quantization produces hideous temporal aliasing
    //viewproj->_41 = floor(viewproj->_41 * 512.0) / 512.0;
    //viewproj->_42 = floor(viewproj->_42 * 512.0) / 512.0;

    effect->SetMatrixArray(ehShadowViewproj, viewproj, 1);
    effectShadow->CommitChanges();

    // Cull
    ViewFrustum range_frustum(viewproj);
    VisibleSet visible_set;

    currentWorldSpace->NearStatics->GetVisibleMeshesCoarse(range_frustum, visible_set);
    currentWorldSpace->FarStatics->GetVisibleMeshesCoarse(range_frustum, visible_set);
    currentWorldSpace->VeryFarStatics->GetVisibleMeshesCoarse(range_frustum, visible_set);

    // Clip to atlas region with viewport
    const DWORD res = Configuration.DL.ShadowResolution;
    D3DVIEWPORT9 vp = { layer * res, 0, res, res, 0.0f, 1.0f };
    device->SetViewport(&vp);

    // Render land and statics
    effectShadow->BeginPass(PASS_RENDERSHADOWMAP);

    if(mwBridge->IsExterior())
        renderDistantLand(effectShadow, view, proj);

    device->SetVertexDeclaration(StaticDecl);
    visible_set.Render(device, effectShadow, effect, &ehTex0, &ehHasAlpha, &ehWorld, SIZEOFSTATICVERT);

    effectShadow->EndPass();
}

// renderShadow - Renders shadows (using blending) over Morrowind shadow receivers
void DistantLand::renderShadow()
{
    effect->SetMatrixArray(ehShadowViewproj, smViewproj, 2);
    effect->SetTexture(ehTex3, texSoftShadow);

    for(std::vector<RenderedState>::const_iterator i = recordMW.begin(); i != recordMW.end(); ++i)
    {
        if(i->blendEnable && i->destBlend == D3DBLEND_ONE)
            continue;

        if((i->alphaTest || i->blendEnable) && i->texture)
        {
            effect->SetTexture(ehTex0, i->texture);
            effect->SetBool(ehHasAlpha, true);
            effect->SetFloat(ehAlphaRef, i->alphaTest ? (i->alphaRef / 255.0f) : 0.01f);
        }
        else
        {
            effect->SetTexture(ehTex0, 0);
            effect->SetBool(ehHasAlpha, false);
            effect->SetFloat(ehAlphaRef, -1.0f);
        }

        effect->SetBool(ehHasBones, i->vertexBlendState != 0);
        effect->SetInt(ehVertexBlendState, i->vertexBlendState);
        effect->SetMatrixArray(ehVertexBlendPalette, i->worldTransforms, 4);
        effect->CommitChanges();

        // Ignore two-sided poly (cull none) mode, shadow casters are drawn with CW culling only,
        // which causes false shadows when cast on the reverse side (wrt normals) of a two-sided poly
        DWORD cull = (i->cullMode != D3DCULL_NONE) ? i->cullMode : (DWORD)D3DCULL_CW;
        device->SetRenderState(D3DRS_CULLMODE, cull);
        device->SetStreamSource(0, i->vb, i->vbOffset, i->vbStride);
        device->SetIndices(i->ib);
        device->SetFVF(i->fvf);
        device->DrawIndexedPrimitive(i->primType, i->baseIndex, i->minIndex, i->vertCount, i->startIndex, i->primCount);
    }
}

// renderShadowDebug - display shadow layers
void DistantLand::renderShadowDebug()
{
    UINT passes;

    // Create shadow clip space -> camera clip space matrices
    D3DXMATRIX inverseShadowViewProj, cameraViewProj, shadowToCameraProj[2];

    D3DXMatrixMultiply(&cameraViewProj, &mwView, &mwProj);
    D3DXMatrixInverse(&inverseShadowViewProj, NULL, &smViewproj[0]);
    D3DXMatrixMultiply(&shadowToCameraProj[0], &inverseShadowViewProj, &cameraViewProj);
    D3DXMatrixInverse(&inverseShadowViewProj, NULL, &smViewproj[1]);
    D3DXMatrixMultiply(&shadowToCameraProj[1], &inverseShadowViewProj, &cameraViewProj);

    // Display shadow layers in top right corner
    effect->Begin(&passes, D3DXFX_DONOTSAVESTATE);
    effect->BeginPass(PASS_DEBUGSHADOW);
    device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    effect->SetTexture(ehTex3, texSoftShadow);
    effect->SetMatrixArray(ehVertexBlendPalette, shadowToCameraProj, 2);
    effect->CommitChanges();
    device->SetVertexDeclaration(WaterDecl);
    device->SetStreamSource(0, vbFullFrame, 0, 12);
    device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    effect->EndPass();
    effect->End();
}
