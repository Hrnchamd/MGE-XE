#include "CollapseTriangle.h"

const double sqrt2 = 1.41421356;

namespace Niflib {

    CollapseTriangle::CollapseTriangle(CollapseVertex* v1,
                                       CollapseVertex* v2,
                                       CollapseVertex* v3) {
        assert(v1 != v2 && v2 != v3 && v3 != v1);

        this->vertex[0] = v1;
        this->vertex[1] = v2;
        this->vertex[2] = v3;

        for (int i = 0; i < 3; i++) {
            this->vertex[i]->AddFace(this);
        }

        this->ComputeNormal();
    }

    CollapseTriangle::~CollapseTriangle(void) {
        for (int i = 0; i < 3; i++) {
            if (!this->vertex[i]) {
                continue;
            }

            this->vertex[i]->RemoveFace(this);
        }
    }

    unsigned int CollapseTriangle::HasVertex(CollapseVertex* v) {
        for (int i = 0; i < 3; i++) {
            if (vertex[i] == v) {
                return (i+1);
            }
        }
        return false;
    }

    void CollapseTriangle::ReplaceVertex(CollapseVertex* u, CollapseVertex* v) {
        assert(u && v);
        assert(this->HasVertex(u));
        assert(!this->HasVertex(v));

        // remove this face from u
        u->RemoveFace(this);

        // change the u vertex to v
        this->vertex[this->HasVertex(u) - 1] = v;

        // add this face to v
        v->AddFace(this);

        // update old vertices to have v as neighbor, not u
        for (int i = 0; i < 3; i++) {
            // just update the old ones...
            if (this->vertex[i] == v) {
                continue;
            }

            // they were in a triangle, they have to be neighbors!
            assert(this->vertex[i]->IsNeighbor(u));
            this->vertex[i]->RemoveIfNotNeighbor(u);
            this->vertex[i]->AddNeighbor(v);
        }

        // recompute this face's normal vector
        this->ComputeNormal();
    }

    void CollapseTriangle::ComputeNormal(void) {
        Vector3 v[3];

        v[0] = this->vertex[0]->Vert.Position;
        v[1] = this->vertex[1]->Vert.Position;
        v[2] = this->vertex[2]->Vert.Position;

        Vector3 a = v[1] - v[0];
        Vector3 b = v[2] - v[0];

        Vector3 _normal = this->normal;

        this->normal = a.CrossProduct(b);

        if (this->normal.Magnitude() < 1e-3) {
            return;
        }

        this->normal = this->normal.Normalized();

        float len = _normal.Magnitude();
        if (len < 0.9f || len > 1.1f) {
            _normal = normal;
        }

        len = this->normal.DotProduct(_normal);

        if (len < 0) {
//            CollapseVertex * tmp = this->vertex[1];
//            this->vertex[1] = this->vertex[2];
//            this->vertex[2] = tmp;

            this->normal.x = -(this->normal.x);
            this->normal.y = -(this->normal.y);
            this->normal.z = -(this->normal.z);

            len = (this->normal + _normal).Magnitude();
            assert(len >= sqrt2);
        }
    }

} // namespace
