
#include "distantland.h"
#include "distantshader.h"
#include "configuration.h"
#include "mwbridge.h"
#include "proxydx/d3d8header.h"

#include <algorithm>



// renderSky - Render atmosphere scattering sky layer and other recorded draw calls on top
void DistantLand::renderSky() {
    // Recorded renders
    const auto& recordSky_const = recordSky;
    for (const auto& i : recordSky_const) {
        // Set variables in main effect; variables are shared via effect pool
        effect->SetTexture(ehTex0, i.texture);
        if (i.texture) {
            // Textured object; draw as normal in shader,
            // except moon shadow (prevents stars shining through moons) which
            // requires colour to be replaced with atmosphere scattering colour
            bool isMoonShadow = i.destBlend == D3DBLEND_INVSRCALPHA && !i.useLighting;

            effect->SetBool(ehHasAlpha, true);
            effect->SetBool(ehHasBones, isMoonShadow);
            device->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
            device->SetRenderState(D3DRS_SRCBLEND, i.srcBlend);
            device->SetRenderState(D3DRS_DESTBLEND, i.destBlend);
        } else {
            // Sky; perform atmosphere scattering in shader
            effect->SetBool(ehHasAlpha, false);
            effect->SetBool(ehHasBones, true);
            device->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
        }

        effect->SetMatrix(ehWorld, &i.worldTransforms[0]);
        effect->CommitChanges();

        device->SetStreamSource(0, i.vb, i.vbOffset, i.vbStride);
        device->SetIndices(i.ib);
        device->SetFVF(i.fvf);
        device->DrawIndexedPrimitive(i.primType, i.baseIndex, i.minIndex, i.vertCount, i.startIndex, i.primCount);
    }
}

void DistantLand::renderDistantLand(ID3DXEffect* e, const D3DXMATRIX* view, const D3DXMATRIX* proj) {
    D3DXMATRIX world, viewproj = (*view) * (*proj);
    D3DXVECTOR4 viewsphere(eyePos.x, eyePos.y, eyePos.z, Configuration.DL.DrawDist * kCellSize);

    D3DXMatrixIdentity(&world);
    effect->SetMatrix(ehWorld, &world);

    effect->SetTexture(ehTex0, texWorldColour);
    effect->SetTexture(ehTex1, texWorldNormals);
    effect->SetTexture(ehTex2, texWorldDetail);
    e->CommitChanges();

    // Cull and draw
    ViewFrustum frustum(&viewproj);
    visLand.RemoveAll();
    LandQuadTree.GetVisibleMeshes(frustum, viewsphere, visLand);

    device->SetVertexDeclaration(LandDecl);
    visLand.Render(device, 0, 0, 0, 0, 0, SIZEOFLANDVERT);
}

void DistantLand::renderDistantLandZ() {
    D3DXMATRIX world;

    D3DXMatrixIdentity(&world);
    effect->SetMatrix(DistantLand::ehWorld, &world);
    effectDepth->CommitChanges();

    // Draw with cached vis set
    device->SetVertexDeclaration(LandDecl);
    visLand.Render(device, 0, 0, 0, 0, 0, SIZEOFLANDVERT);
}

void DistantLand::cullDistantStatics(const D3DXMATRIX* view, const D3DXMATRIX* proj) {
    D3DXMATRIX ds_proj = *proj, ds_viewproj;
    D3DXVECTOR4 viewsphere(eyePos.x, eyePos.y, eyePos.z, 0);
    float zn = nearViewRange - 768.0f, zf = zn;
    float cullDist = fogEnd;

    visDistant.RemoveAll();

    zf = std::min(Configuration.DL.NearStaticEnd * kCellSize, cullDist);
    if (zn < zf) {
        editProjectionZ(&ds_proj, zn, zf);
        ds_viewproj = (*view) * ds_proj;
        ViewFrustum range_frustum(&ds_viewproj);
        viewsphere.w = zf;
        currentWorldSpace->NearStatics->GetVisibleMeshes(range_frustum, viewsphere, visDistant);
    }

    zf = std::min(Configuration.DL.FarStaticEnd * kCellSize, cullDist);
    if (zn < zf) {
        editProjectionZ(&ds_proj, zn, zf);
        ds_viewproj = (*view) * ds_proj;
        ViewFrustum range_frustum(&ds_viewproj);
        viewsphere.w = zf;
        currentWorldSpace->FarStatics->GetVisibleMeshes(range_frustum, viewsphere, visDistant);
    }

    zf = std::min(Configuration.DL.VeryFarStaticEnd * kCellSize, cullDist);
    if (zn < zf) {
        editProjectionZ(&ds_proj, zn, zf);
        ds_viewproj = (*view) * ds_proj;
        ViewFrustum range_frustum(&ds_viewproj);
        viewsphere.w = zf;
        currentWorldSpace->VeryFarStatics->GetVisibleMeshes(range_frustum, viewsphere, visDistant);
    }

    visDistant.SortByState();
}

void DistantLand::renderDistantStatics() {
    if (!MWBridge::get()->IsExterior()) {
        // Set clipping to stop large architectural meshes (that don't match exactly)
        // from visible overdrawing and causing z-buffer occlusion
        float clipAt = nearViewRange - 768.0f;
        D3DXPLANE clipPlane(0, 0, clipAt, -(mwProj._33 * clipAt + mwProj._43));
        device->SetClipPlane(0, clipPlane);
        device->SetRenderState(D3DRS_CLIPPLANEENABLE, 1);
    }

    device->SetVertexDeclaration(StaticDecl);
    visDistant.Render(device, effect, effect, &ehTex0, 0, &ehWorld, SIZEOFSTATICVERT);

    device->SetRenderState(D3DRS_CLIPPLANEENABLE, 0);
}
