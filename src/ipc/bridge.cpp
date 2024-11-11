#include "ipc/bridge.h"
#include "support/log.h"

#include <cmath>

IPC::MapViewOfFileNuma2_t IPC::MapViewOfFileNuma2 = nullptr;
IPC::MapViewOfFile3_t IPC::MapViewOfFile3 = nullptr;
IPC::UnmapViewOfFile2_t IPC::UnmapViewOfFile2 = nullptr;
IPC::UnmapViewOfFileEx_t IPC::UnmapViewOfFileEx = nullptr;
IPC::VirtualAlloc2_t IPC::VirtualAlloc2 = nullptr;

bool IPC::initImports() {
    auto kernel32 = LoadLibraryA("Kernel32.dll");
    auto kernelbase = LoadLibraryA("Kernelbase.dll");

    if (kernel32 == NULL) {
        return false;
    }

    if (kernelbase == NULL) {
        FreeLibrary(kernel32);
        return false;
    }

    // the docs claim MapViewOfFile3 and VirtualAlloc2 are in kernel32, but they're actually in kernelbase
    IPC::MapViewOfFileNuma2 = reinterpret_cast<IPC::MapViewOfFileNuma2_t>(GetProcAddress(kernelbase, "MapViewOfFileNuma2"));
    IPC::MapViewOfFile3 = reinterpret_cast<IPC::MapViewOfFile3_t>(GetProcAddress(kernelbase, "MapViewOfFile3"));
    IPC::UnmapViewOfFile2 = reinterpret_cast<IPC::UnmapViewOfFile2_t>(GetProcAddress(kernelbase, "UnmapViewOfFile2"));
    IPC::UnmapViewOfFileEx = reinterpret_cast<IPC::UnmapViewOfFileEx_t>(GetProcAddress(kernel32, "UnmapViewOfFileEx"));
    IPC::VirtualAlloc2 = reinterpret_cast<IPC::VirtualAlloc2_t>(GetProcAddress(kernelbase, "VirtualAlloc2"));

    auto success = IPC::MapViewOfFileNuma2 != nullptr && IPC::MapViewOfFile3 != nullptr && IPC::UnmapViewOfFile2 != nullptr && IPC::UnmapViewOfFileEx != nullptr && IPC::VirtualAlloc2 != nullptr;
    if (!success) {
        FreeLibrary(kernel32);
        FreeLibrary(kernelbase);
        IPC::MapViewOfFileNuma2 = nullptr;
        IPC::MapViewOfFile3 = nullptr;
        IPC::UnmapViewOfFile2 = nullptr;
        IPC::UnmapViewOfFileEx = nullptr;
        IPC::VirtualAlloc2 = nullptr;
    }

    return success;
}

//-----------------------------------------------------------------------------
// ViewFrustum class
//-----------------------------------------------------------------------------

ViewFrustum::ViewFrustum(const D3DXMATRIX* viewProj) {
    // Near plane
    frustum[0].a = viewProj->_13;
    frustum[0].b = viewProj->_23;
    frustum[0].c = viewProj->_33;
    frustum[0].d = viewProj->_43;

    // Far plane
    frustum[1].a = viewProj->_14 - viewProj->_13;
    frustum[1].b = viewProj->_24 - viewProj->_23;
    frustum[1].c = viewProj->_34 - viewProj->_33;
    frustum[1].d = viewProj->_44 - viewProj->_43;

    // Left plane
    frustum[2].a = viewProj->_14 + viewProj->_11;
    frustum[2].b = viewProj->_24 + viewProj->_21;
    frustum[2].c = viewProj->_34 + viewProj->_31;
    frustum[2].d = viewProj->_44 + viewProj->_41;

    // Right plane
    frustum[3].a = viewProj->_14 - viewProj->_11;
    frustum[3].b = viewProj->_24 - viewProj->_21;
    frustum[3].c = viewProj->_34 - viewProj->_31;
    frustum[3].d = viewProj->_44 - viewProj->_41;

    // Top plane
    frustum[4].a = viewProj->_14 - viewProj->_12;
    frustum[4].b = viewProj->_24 - viewProj->_22;
    frustum[4].c = viewProj->_34 - viewProj->_32;
    frustum[4].d = viewProj->_44 - viewProj->_42;

    // Bottom plane
    frustum[5].a = viewProj->_14 + viewProj->_12;
    frustum[5].b = viewProj->_24 + viewProj->_22;
    frustum[5].c = viewProj->_34 + viewProj->_32;
    frustum[5].d = viewProj->_44 + viewProj->_42;

    // Normalize planes
    for (size_t f = 0; f < 6; ++f) {
        D3DXPLANE temp(frustum[f]);
        D3DXPlaneNormalize(&frustum[f], &temp);
    }
}

//-----------------------------------------------------------------------------

ViewFrustum::Containment ViewFrustum::ContainsSphere(const BoundingSphere& sphere) const {
    float dist[6];
    size_t f;

    for (f = 0; f < 6; ++f) {
        dist[f] = D3DXPlaneDotCoord(&frustum[f], &sphere.center);
        if (dist[f] + sphere.radius < 0) {
            return OUTSIDE;
        }
    }

    for (f = 0; f < 6; ++f) {
        if (std::fabs(dist[f]) < sphere.radius) {
            return INTERSECTS;
        }
    }

    return INSIDE;
}

//-----------------------------------------------------------------------------

ViewFrustum::Containment ViewFrustum::ContainsBox(const BoundingBox& box) const {
    // Do OBB-plane test for each frustum plane
    for (size_t f = 0; f < 6; ++f) {
        D3DXVECTOR4 extent;

        extent.x = std::fabs(D3DXPlaneDotNormal(&frustum[f], &box.vx));
        extent.y = std::fabs(D3DXPlaneDotNormal(&frustum[f], &box.vy));
        extent.z = std::fabs(D3DXPlaneDotNormal(&frustum[f], &box.vz));
        extent.w = D3DXPlaneDotCoord(&frustum[f], &box.center);

        // Fail if centre + projected extents is outside the halfspace
        if (extent.w + extent.x + extent.y + extent.z < 0) {
            return OUTSIDE;
        }
    }

    // Neglect to test frustum multi-plane corner cases to save time; this still culls conservatively

    return INSIDE;
}

//-----------------------------------------------------------------------------
