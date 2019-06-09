
#include "distantland.h"
#include "distantshader.h"
#include "configuration.h"
#include "mwbridge.h"
#include "proxydx/d3d8header.h"
#include "support/log.h"

#include <cmath>



static const float shadowNearRadius = 1000.0;
static const float shadowFarRadius = 4000.0;



// renderShadowMap
// Renders multiple shadow map layers to channels in one texture
// Applies filtering to soften shadow edges
// This *must* restore render state on return
void DistantLand::renderShadowMap() {
    IDirect3DSurface9* target, *targetSoft;
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
    device->Clear(0, 0, D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 0, 1.0, 0);
    effectShadow->BeginPass(PASS_CLEARSHADOWMAP);
    effect->SetBool(ehHasAlpha, false);
    effectShadow->CommitChanges();
    device->SetVertexDeclaration(WaterDecl);
    device->SetStreamSource(0, vbFullFrame, 0, 12);
    device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    effectShadow->EndPass();

    // Calculate transform to map view frustum into world space
    D3DXMATRIX inverseCameraProj, cameraViewProj;
    D3DXMatrixMultiply(&cameraViewProj, &mwView, &mwProj);
    D3DXMatrixInverse(&inverseCameraProj, NULL, &cameraViewProj);

    // Render near layer (changes viewport)
    renderShadowLayer(0, shadowNearRadius, &inverseCameraProj);

    // Render far layer (changes viewport)
    renderShadowLayer(1, shadowFarRadius, &inverseCameraProj);

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
void DistantLand::renderShadowLayer(int layer, float radius, const D3DXMATRIX* inverseCameraProj) {
    auto mwBridge = MWBridge::get();
    D3DXVECTOR3 lookAt, lookAtEye, shadowCameraPos, up(0, 0, 1);
    D3DXMATRIX* view = &smView[layer], *proj = &smProj[layer], *viewproj = &smViewproj[layer];

    // Select light vector, sunPos during daytime, sunVec during night
    D3DXVECTOR4 lightVec = (sunPos.z > 0) ? -sunPos : sunVec;

    // Centre of projection is one radius ahead of the player
    // Not as far in z direction as player is likely looking at the ground plane rather than below
    // This will be split into a non-texel-quantized but temporally stable view position part,
    // and a texel-quantized view rotation part with small magnitude
    lookAt.x = eyePos.x + radius * eyeVec.x;
    lookAt.y = eyePos.y + radius * eyeVec.y;
    lookAt.z = eyePos.z + 0.5f * radius * eyeVec.z;

    // Quantize eye position to partially reduce texture swimming during camera movement
    lookAtEye.x = float(16.0 * std::floor(0.0625 * eyePos.x));
    lookAtEye.y = float(16.0 * std::floor(0.0625 * eyePos.y));
    lookAtEye.z = float(16.0 * std::floor(0.0625 * eyePos.z));

    // Create shadow frustum centred on lookAtEye, looking along lightVec
    const float zrange = kCellSize;
    shadowCameraPos.x = lookAtEye.x - zrange * lightVec.x;
    shadowCameraPos.y = lookAtEye.y - zrange * lightVec.y;
    shadowCameraPos.z = lookAtEye.z - zrange * lightVec.z;

    D3DXMatrixLookAtRH(view, &shadowCameraPos, &lookAtEye, &up);
    D3DXMatrixOrthoRH(proj, 2 * radius, (1 + std::fabs(lightVec.z)) * radius, 0, 2.0 * zrange);
    *viewproj = (*view) * (*proj);

    // Transform remainder into shadow clip space and quantize
    // Prevents all shimmer during camera rotation
    D3DXVECTOR3 dv, deltaLookAt = lookAtEye - lookAt;
    D3DXVec3TransformNormal(&dv, &deltaLookAt, viewproj);

    // Quantize clip space range [-1, +1] over ShadowResolution texels
    const float quantizer = 2.0f / Configuration.DL.ShadowResolution;
    viewproj->_41 += quantizer * floor(dv.x / quantizer);
    viewproj->_42 += quantizer * floor(dv.y / quantizer);
    viewproj->_43 += dv.z;

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

    // Render view frustum to stencil, which limits rendering to visible texels
    effect->SetMatrix(ehWorld, inverseCameraProj);
    effectShadow->BeginPass(PASS_SHADOWSTENCIL);
    device->SetVertexDeclaration(WaterDecl);
    device->SetStreamSource(0, vbClipCube, 0, 12);
    device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);
    effectShadow->EndPass();

    // Render land and statics
    effectShadow->BeginPass(PASS_RENDERSHADOWMAP);

    if (mwBridge->IsExterior()) {
        renderDistantLand(effectShadow, view, proj);
    }

    device->SetVertexDeclaration(StaticDecl);
    visible_set.Render(device, effectShadow, effect, &ehTex0, &ehHasAlpha, &ehWorld, SIZEOFSTATICVERT);

    effectShadow->EndPass();
}

// renderShadow - Renders shadows (using blending) over Morrowind shadow receivers
void DistantLand::renderShadow() {
    // Supply view space -> shadow clip space matrix
    D3DXMATRIX inverseView, viewToShadow[2];
    D3DXMatrixInverse(&inverseView, NULL, &mwView);
    viewToShadow[0] = inverseView * smViewproj[0];
    viewToShadow[1] = inverseView * smViewproj[1];
    effect->SetMatrixArray(ehShadowViewproj, viewToShadow, 2);

    // Bind filtered ESM
    effect->SetTexture(ehTex3, texSoftShadow);

    const auto& recordMW_const = recordMW;
    for (const auto& i : recordMW_const) {
        // Additive alphas do not receive shadows
        if (i.blendEnable && i.destBlend == D3DBLEND_ONE) {
            continue;
        }

        // Only bind texture for alphas
        if ((i.alphaTest || i.blendEnable) && i.texture) {
            effect->SetTexture(ehTex0, i.texture);
            effect->SetBool(ehHasAlpha, true);
            effect->SetFloat(ehAlphaRef, i.alphaTest ? (i.alphaRef / 255.0f) : 0.01f);
        } else {
            effect->SetTexture(ehTex0, 0);
            effect->SetBool(ehHasAlpha, false);
            effect->SetFloat(ehAlphaRef, -1.0f);
        }

        // Skin using worldview matrices for numerical accuracy
        effect->SetBool(ehHasBones, i.vertexBlendState != 0);
        effect->SetInt(ehVertexBlendState, i.vertexBlendState);
        effect->SetMatrixArray(ehVertexBlendPalette, i.worldViewTransforms, 4);
        effect->CommitChanges();

        // Ignore two-sided poly (cull none) mode, shadow casters are drawn with CW culling only,
        // which causes false shadows when cast on the reverse side (wrt normals) of a two-sided poly
        DWORD cull = (i.cullMode != D3DCULL_NONE) ? i.cullMode : (DWORD)D3DCULL_CW;
        device->SetRenderState(D3DRS_CULLMODE, cull);
        device->SetStreamSource(0, i.vb, i.vbOffset, i.vbStride);
        device->SetIndices(i.ib);
        device->SetFVF(i.fvf);
        device->DrawIndexedPrimitive(i.primType, i.baseIndex, i.minIndex, i.vertCount, i.startIndex, i.primCount);
    }
}

// renderShadowDebug - display shadow layers
void DistantLand::renderShadowDebug() {
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
