
#include "dlmath.h"

#include <cmath>

//-----------------------------------------------------------------------------
// BoundingSphere class
//-----------------------------------------------------------------------------

BoundingSphere::BoundingSphere() : center(0.0f, 0.0f, 0.0f), radius(0.0f) {
}

//-----------------------------------------------------------------------------

BoundingSphere::BoundingSphere(const BoundingSphere& sphere) {
    *this = sphere;
}

//-----------------------------------------------------------------------------

BoundingSphere& BoundingSphere::operator=(const BoundingSphere& sphere) {
    center.x = sphere.center.x;
    center.y = sphere.center.y;
    center.z = sphere.center.z;
    radius = sphere.radius;

    return *this;
}

//-----------------------------------------------------------------------------

BoundingSphere& BoundingSphere::operator+=(const BoundingSphere& rh) {
    // This code is based from the math described on this page:
    // http://xengine.sourceforge.net/docs/classXEngine_1_1Math_1_1Sphere.html
    // However, the formula for "coef" appears to have had the subtraction reversed.

    // This will be defined as returning the minimum bounding sphere which contains the two spheres being added together

    BoundingSphere result;
    D3DXVECTOR3 vect = rh.center - center;
    float dist = D3DXVec3Length(&vect);

    // Check if the sphere centers are almost the same, or if either radius is zero
    if (dist <= 0.001f || radius == 0.0f || rh.radius == 0.0f) {
        // Return the larger of the two radii
        if (rh.radius > radius) {
            radius = rh.radius;
            center = rh.center;
        }
        return *this;
    }

    // Interval for first sphere is [-r0, r0]; interval for second sphere is [d - r1, d + r1]
    if (-radius < dist - rh.radius && radius > dist + rh.radius) {
        // Right hand sphere is contained in this one
        result.center = center;
        result.radius = radius;
    } else if (dist - rh.radius < -radius && dist + rh.radius > radius) {
        // This sphere is contained in right hand one
        result.center = rh.center;
        result.radius = rh.radius;
    } else {
        // One sphere is not contained in the other

        // radius is (dist + r0 + r1) / 2
        // center is on the line c0 + coef * norm_vec
        // where coef = (dist + r1 - r0) / 2

        D3DXVECTOR3 norm_vect;
        result.radius = 0.5f * (dist + radius + rh.radius);
        D3DXVec3Normalize(&norm_vect, &vect);

        float coef = 0.5f * (dist + rh.radius - radius);
        result.center = center + coef * norm_vect;
    }

    center = result.center;
    radius = result.radius;

    return *this;
}

//-----------------------------------------------------------------------------

BoundingSphere BoundingSphere::operator+(const BoundingSphere& rh) {
    return BoundingSphere(*this) += rh;
}

//-----------------------------------------------------------------------------
// BoundingBox class
//-----------------------------------------------------------------------------

BoundingBox::BoundingBox() {
    center = D3DXVECTOR3(0.0, 0.0, 0.0);
    vx = vy = vz = center;
}

//-----------------------------------------------------------------------------

BoundingBox::BoundingBox(const BoundingBox& rh) {
    *this = rh;
}

//-----------------------------------------------------------------------------

BoundingBox& BoundingBox::operator=(const BoundingBox& rh) {
    center = rh.center;
    vx = rh.vx;
    vy = rh.vy;
    vz = rh.vz;

    return *this;
}

//-----------------------------------------------------------------------------

BoundingBox::BoundingBox(const D3DXVECTOR3& min, const D3DXVECTOR3& max) {
    Set(min, max);
}

//-----------------------------------------------------------------------------

void BoundingBox::Set(const D3DXVECTOR3& min, const D3DXVECTOR3& max) {
    center = 0.5f * (min + max);
    vx = D3DXVECTOR3(0.5f * (max.x - min.x), 0, 0);
    vy = D3DXVECTOR3(0, 0.5f * (max.y - min.y), 0);
    vz = D3DXVECTOR3(0, 0, 0.5f * (max.z - min.z));
}

//-----------------------------------------------------------------------------

void BoundingBox::Transform(const D3DXMATRIX& m) {
    D3DXVec3TransformCoord(&center, &center, &m);
    D3DXVec3TransformNormal(&vx, &vx, &m);
    D3DXVec3TransformNormal(&vy, &vy, &m);
    D3DXVec3TransformNormal(&vz, &vz, &m);
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
