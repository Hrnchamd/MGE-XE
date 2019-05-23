
#include "specificrender.h"
#include "configuration.h"



// VendorSpecificRendering - Rendering state with vendor specific APIs
void VendorSpecificRendering::init(IDirect3DDevice9* device) {
    IDirect3D9* d3d;
    device->GetDirect3D(&d3d);

    // Check alpha to coverage support
    if (Configuration.AALevel == 0) {
        alphaToCoverageMode = ATOC_NONE;
    } else if (d3d->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, 0, D3DRTYPE_SURFACE, D3DFMT_ATOC) == S_OK) {
        alphaToCoverageMode = ATOC_ADAPTIVETESS;
    } else { // Assume AMD method, as no method of checking support is provided and other vendors may support it
        alphaToCoverageMode = ATOC_POINTSIZE;
    }

    d3d->Release();
}

// beginAlphaToCoverage - Enables alpha-to-coverage when rendering alpha tested polys
void VendorSpecificRendering::beginAlphaToCoverage(IDirect3DDevice9* device) {
    if (~Configuration.MGEFlags & TRANSPARENCY_AA) {
        return;
    }

    switch (alphaToCoverageMode) {
    case ATOC_ADAPTIVETESS:
        device->SetRenderState(D3DRS_ADAPTIVETESS_Y, D3DFMT_ATOC);
        break;
    case ATOC_POINTSIZE:
        device->SetRenderState(D3DRS_POINTSIZE, D3DFMT_A2M1);
        break;
    }
}

// endAlphaToCoverage -  Disables alpha-to-coverage
void VendorSpecificRendering::endAlphaToCoverage(IDirect3DDevice9* device) {
    if (~Configuration.MGEFlags & TRANSPARENCY_AA) {
        return;
    }

    switch (alphaToCoverageMode) {
    case ATOC_ADAPTIVETESS:
        device->SetRenderState(D3DRS_ADAPTIVETESS_Y, D3DFMT_UNKNOWN);
        break;
    case ATOC_POINTSIZE:
        device->SetRenderState(D3DRS_POINTSIZE, D3DFMT_A2M0);
        break;
    }
}

