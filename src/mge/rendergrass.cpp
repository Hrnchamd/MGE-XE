
#include "distantland.h"
#include "distantshader.h"
#include "configuration.h"
#include "mged3d8device.h"
#include "support/log.h"

#include <algorithm>



void DistantLand::cullGrass(const D3DXMATRIX* view, const D3DXMATRIX* proj) {
    D3DXMATRIX ds_proj = *proj, ds_viewproj;
    float zn = 4.0f, zf = nearViewRange;

    // Don't draw beyond fully fogged distance; early out if frustum is empty
    if (~Configuration.MGEFlags & EXP_FOG) {
        zf = std::min(fogEnd, zf);
    }
    if (zf <= zn) {
        return;
    }

    // Create a clipping frustum for visibility determination
    editProjectionZ(&ds_proj, zn, zf);
    ds_viewproj = (*view) * ds_proj;

    // Cull and sort
    ViewFrustum range_frustum(&ds_viewproj);
    visGrass.RemoveAll();
    currentWorldSpace->GrassStatics->GetVisibleMeshesCoarse(range_frustum, visGrass);
    visGrass.SortByState();

    buildGrassInstanceVB();
}


void DistantLand::buildGrassInstanceVB() {
    batchedGrass.clear();

	if (visGrass.visible_set.empty()) {
		return;
	}

    if (visGrass.visible_set.size() > MaxGrassElements) {
        static bool warnOnce = true;
        if (warnOnce) {
            LOG::logline("!! Too many grass instances. (%d elements, limit %d)", visGrass.visible_set.size(), MaxGrassElements);
            LOG::logline("!! Reduce grass density to avoid flickering grass.");
            warnOnce = false;
        }
        visGrass.visible_set.resize(MaxGrassElements);
    }

    const QuadTreeMesh* mesh = *visGrass.visible_set.begin();
    float* vbwrite = 0;
    int nz = 0;

    HRESULT hr = vbGrassInstances->Lock(0, GrassInstStride * visGrass.visible_set.size(), (void**)&vbwrite, D3DLOCK_DISCARD);
    if (hr != D3D_OK || vbwrite == 0) {
        return;
    }

    // Write all grass transforms into one buffer
    // Record how many instances belong to each different mesh
    const auto& visible_set_const = visGrass.visible_set;
    for (const auto& m : visible_set_const) {
        if (mesh->vBuffer != m->vBuffer) {
            batchedGrass.push_back(std::make_pair(mesh, nz));
            mesh = m;
            nz = 0;
        }

        // Pack into 4x3 transposed matrix
        const D3DMATRIX* world = &m->transform;
        vbwrite[0] = world->_11;
        vbwrite[1] = world->_21;
        vbwrite[2] = world->_31;
        vbwrite[3] = world->_41;
        vbwrite[4] = world->_12;
        vbwrite[5] = world->_22;
        vbwrite[6] = world->_32;
        vbwrite[7] = world->_42;
        vbwrite[8] = world->_13;
        vbwrite[9] = world->_23;
        vbwrite[10] = world->_33;
        vbwrite[11] = world->_43;
        vbwrite += 12;
        nz++;
    }
    batchedGrass.push_back(std::make_pair(mesh, nz));
    vbGrassInstances->Unlock();
}


// renderGrassInst - instanced grass with shadows
void DistantLand::renderGrassInst() {
    if (visGrass.visible_set.empty()) {
        return;
    }

    effect->SetMatrixArray(ehShadowViewproj, smViewproj, 2);
    effect->SetTexture(ehTex3, texSoftShadow);
    device->SetVertexDeclaration(GrassDecl);

    renderGrassCommon(effect);
}

// renderGrassInstZ - Z only pass
void DistantLand::renderGrassInstZ() {
    if (visGrass.visible_set.empty()) {
        return;
    }

    effect->SetBool(ehHasAlpha, true);
    effect->SetFloat(ehAlphaRef, 128.0f / 255.0f);
    device->SetVertexDeclaration(GrassDecl);

    renderGrassCommon(effectDepth);
}

void DistantLand::renderGrassCommon(ID3DXEffect* e) {
    int nz = 0;
    for (const auto& grass : batchedGrass) {
        effect->SetTexture(ehTex0, grass.first->tex);
        e->CommitChanges();

        device->SetIndices(grass.first->iBuffer);
        device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | grass.second);
        device->SetStreamSource(0, grass.first->vBuffer, 0, SIZEOFSTATICVERT);
        device->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
        device->SetStreamSource(1, vbGrassInstances, GrassInstStride * nz, GrassInstStride);
        device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, grass.first->verts, 0, grass.first->faces);

        nz += grass.second;
    }

    device->SetStreamSourceFreq(0, 1);
    device->SetStreamSourceFreq(1, 1);
    device->SetStreamSource(1, NULL, 0, 0);
}
