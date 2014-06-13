
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
    float radius;                       // radius of bounding sphere
    D3DXVECTOR3 center;                 // center of bounding sphere
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
    D3DXVECTOR3 center;                 // center of bounding sphere
    float radius;                       // radius of bounding sphere
    int numSubsets;
    DistantSubset *subsets;
};

struct UsedDistantStatic {
    DWORD staticRef;
    D3DXMATRIX transform;
    float radius;                       // radius * scale
    D3DXVECTOR3 center;                 // center + transform
    float scale;
    D3DXVECTOR3 pos;

    BoundingSphere GetBoundingSphere(const DistantSubset& sub) const
    {
        BoundingSphere sphere;
        D3DXVec3TransformCoord(&sphere.center, &sub.center, &transform);
        sphere.radius = sub.radius * scale;

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
