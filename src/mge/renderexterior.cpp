
#include "proxydx/d3d8header.h"
#include "distantland.h"
#include "distantshader.h"
#include "configuration.h"
#include "mwbridge.h"



// renderSky - Render atmosphere scattering sky layer and other recorded draw calls on top
void DistantLand::renderSky()
{
    // Recorded renders
    for(vector<RenderedState>::iterator i = recordSky.begin(); i != recordSky.end(); ++i)
    {
        // Set variables in main effect; variables are shared via effect pool
        if(i->texture)
        {
            // Textured object; draw as normal in shader
            effect->SetTexture(ehTex0, i->texture);
            effect->SetBool(ehHasAlpha, true);
            device->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
            device->SetRenderState(D3DRS_SRCBLEND, i->srcBlend);
            device->SetRenderState(D3DRS_DESTBLEND, i->destBlend);
        }
        else
        {
            // Sky; perform atmosphere scattering in shader
            effect->SetBool(ehHasAlpha, false);
            device->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
        }

        effect->SetMatrix(ehWorld, &i->worldTransforms[0]);
        effect->CommitChanges();

        device->SetStreamSource(0, i->vb, i->vbOffset, i->vbStride);
        device->SetIndices(i->ib);
        device->SetFVF(i->fvf);
        device->DrawIndexedPrimitive(i->primType, i->baseIndex, i->minIndex, i->vertCount, i->startIndex, i->primCount);
    }
}

void DistantLand::renderDistantLand(ID3DXEffect *e, const D3DXMATRIX *view, const D3DXMATRIX *proj)
{
    D3DXMATRIX world, viewproj = (*view) * (*proj);
    D3DXVECTOR4 viewsphere(eyePos.x, eyePos.y, eyePos.z, Configuration.DL.DrawDist * 8192.0f);

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

void DistantLand::renderDistantLandZ()
{
    D3DXMATRIX world;

    D3DXMatrixIdentity(&world);
    effect->SetMatrix(DistantLand::ehWorld, &world);
    effectDepth->CommitChanges();

    // Draw with cached vis set
    device->SetVertexDeclaration(LandDecl);
    visLand.Render(device, 0, 0, 0, 0, 0, SIZEOFLANDVERT);
}

void DistantLand::cullDistantStatics(const D3DXMATRIX *view, const D3DXMATRIX *proj)
{
    D3DXMATRIX ds_proj = *proj, ds_viewproj;
    D3DXVECTOR4 viewsphere(eyePos.x, eyePos.y, eyePos.z, 0);
    float zn = 6400.0, zf = zn;
    float cullDist = fogEnd;

    visDistant.RemoveAll();

    zf = min(Configuration.DL.NearStaticEnd * 8192.0f, cullDist);
    if(zn < zf)
    {
        editProjectionZ(&ds_proj, zn, zf);
        ds_viewproj = (*view) * ds_proj;
        ViewFrustum range_frustum(&ds_viewproj);
        viewsphere.w = zf;
        currentWorldSpace->NearStatics->GetVisibleMeshes(range_frustum, viewsphere, visDistant);
    }

    zf = min(Configuration.DL.FarStaticEnd * 8192.0f, cullDist);
    if(zn < zf)
    {
        editProjectionZ(&ds_proj, zn, zf);
        ds_viewproj = (*view) * ds_proj;
        ViewFrustum range_frustum(&ds_viewproj);
        viewsphere.w = zf;
        currentWorldSpace->FarStatics->GetVisibleMeshes(range_frustum, viewsphere, visDistant);
    }

    zf = min(Configuration.DL.VeryFarStaticEnd * 8192.0f, cullDist);
    if(zn < zf)
    {
        editProjectionZ(&ds_proj, zn, zf);
        ds_viewproj = (*view) * ds_proj;
        ViewFrustum range_frustum(&ds_viewproj);
        viewsphere.w = zf;
        currentWorldSpace->VeryFarStatics->GetVisibleMeshes(range_frustum, viewsphere, visDistant);
    }

    visDistant.SortByState();
}

void DistantLand::renderDistantStatics()
{
    DECLARE_MWBRIDGE

    if(!mwBridge->IsExterior())
    {
        // Set clipping to stop large architectural meshes (that don't match exactly)
        // from visible overdrawing and causing z-buffer occlusion
        float clipAt = 6400.0;
        D3DXPLANE clipPlane(0, 0, clipAt, -(mwProj._33 * clipAt + mwProj._43));
        device->SetClipPlane(0, clipPlane);
        device->SetRenderState(D3DRS_CLIPPLANEENABLE, 1);
    }

    device->SetVertexDeclaration(StaticDecl);
    visDistant.Render(device, effect, effect, &ehTex0, 0, &ehWorld, SIZEOFSTATICVERT);

    device->SetRenderState(D3DRS_CLIPPLANEENABLE, 0);
}
