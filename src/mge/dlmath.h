#pragma once

#define D3DXFX_LARGEADDRESS_HANDLE

#include "d3dx9math.h"



struct BoundingSphere {
    D3DXVECTOR3 center;
    float radius;

    BoundingSphere();
    BoundingSphere(const BoundingSphere& sphere);
    BoundingSphere& operator=(const BoundingSphere& sphere);
    bool empty() const {
        return radius == 0.0f;
    }

    BoundingSphere& operator+=(const BoundingSphere& rh);
    BoundingSphere operator+(const BoundingSphere& rh);
};


struct BoundingBox {
    D3DXVECTOR3 center, vx, vy, vz;

    BoundingBox();
    BoundingBox(const BoundingBox& rh);

    BoundingBox& operator=(const BoundingBox& rh);
    BoundingBox(const D3DXVECTOR3& min, const D3DXVECTOR3& max);
    void Set(const D3DXVECTOR3& min, const D3DXVECTOR3& max);
    void Transform(const D3DXMATRIX& m);
};
