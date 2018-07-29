
enum StaticType {
    STATIC_AUTO = 0,
    STATIC_NEAR = 1,
    STATIC_FAR = 2,
    STATIC_VERY_FAR = 3,
    STATIC_GRASS = 4,
    STATIC_TREE = 5,
    STATIC_BUILDING = 6
};

struct LandMesh
{
    BoundingSphere sphere;
    BoundingBox box;
    DWORD verts;
    DWORD faces;
    IDirect3DVertexBuffer9 *vbuffer;
    IDirect3DIndexBuffer9 *ibuffer;
};

struct DistantSubset {
    BoundingSphere sphere;
    D3DXVECTOR3 min, max;               // corners of the axis-aligned bounding box
    IDirect3DTexture9 *tex;
    bool hasalpha;                      // texture has alpha transparency
    IDirect3DVertexBuffer9 *vbuffer;
    IDirect3DIndexBuffer9 *ibuffer;
    int verts;
    int faces;
};

struct DistantStatic {
    unsigned char type;
    BoundingSphere sphere;
    int numSubsets;
    DistantSubset *subsets;
};

struct UsedDistantStatic {
    DWORD staticRef;
    D3DXVECTOR3 pos;
    float scale;
    D3DXMATRIX transform;
    BoundingSphere sphere;      // post-transform

    BoundingSphere GetBoundingSphere(const DistantSubset& sub) const
    {
        BoundingSphere sphere;
        D3DXVec3TransformCoord(&sphere.center, &sub.sphere.center, &transform);
        sphere.radius = sub.sphere.radius * scale;

        return sphere;
    }

    BoundingBox GetBoundingBox(const DistantSubset& sub) const
    {
        BoundingBox box;
        box.Set(sub.min, sub.max);
        box.Transform(transform);

        return box;
    }
};
