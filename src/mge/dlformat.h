#pragma once

#include "ipc/bridge.h"
#include "dlmath.h"
#include <vector>

enum StaticType {
    STATIC_AUTO = 0,
    STATIC_NEAR = 1,
    STATIC_FAR = 2,
    STATIC_VERY_FAR = 3,
    STATIC_GRASS = 4,
    STATIC_TREE = 5,
    STATIC_BUILDING = 6
};

struct LandMesh {
    BoundingSphere sphere;
    BoundingBox box;
    DWORD verts;
    DWORD faces;
    ptr32<IDirect3DVertexBuffer9> vbuffer;
    ptr32<IDirect3DIndexBuffer9> ibuffer;
};

#pragma pack(push, 4)
struct DistantSubset {
    DWORD parentStaticIndex;
    BoundingSphere sphere;
    D3DXVECTOR3 aabbMin, aabbMax;       // corners of the axis-aligned bounding box
    ptr32<IDirect3DTexture9> tex;
    bool hasAlpha, hasUVController;
    ptr32<IDirect3DVertexBuffer9> vbuffer;
    ptr32<IDirect3DIndexBuffer9> ibuffer;
    int verts;
    int faces;
};

struct DistantStatic {
    unsigned char type;
    BoundingSphere sphere;
    D3DXVECTOR3 aabbMin, aabbMax;       // corners of the axis-aligned bounding box
    DWORD firstSubsetIndex;
    size_t numSubsets;
};

struct UsedDistantStatic {
    DWORD staticRef;
    uint16_t visIndex;
    D3DXVECTOR3 pos;
    float scale;
    D3DXMATRIX transform;
    BoundingSphere sphere;      // post-transform
    BoundingBox box;            // post-transform

    BoundingSphere GetBoundingSphere(const BoundingSphere& base) const {
        BoundingSphere sphere;
        D3DXVec3TransformCoord(&sphere.center, &base.center, &transform);
        sphere.radius = base.radius * scale;

        return sphere;
    }

    BoundingBox GetBoundingBox(const D3DXVECTOR3& aabbMin, const D3DXVECTOR3& aabbMax) const {
        BoundingBox box;
        box.Set(aabbMin, aabbMax);
        box.Transform(transform);

        return box;
    }
};
#pragma pack(pop)