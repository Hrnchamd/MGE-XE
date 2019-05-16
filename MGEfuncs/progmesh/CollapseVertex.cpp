#include "CollapseVertex.h"

namespace Niflib {

    CollapseVertex::CollapseVertex(ProgMesh* _parent,
                                   unsigned int _ID,
                                   bool _use_cost) {
        this->parent = _parent;
        this->ID = _ID;
        this->use_cost = _use_cost;

        this->Vert = _parent->GetVert(this->ID);

        this->Cost = -1.0f;
        this->Candidate = NULL;
        this->Duplicate = false;

        this->border = false;
    }

    CollapseVertex::~CollapseVertex(void) {
        assert(this->Faces.empty());

        while (!this->Neighbors.empty()) {
            this->Neighbors.back()->RemoveNeighbor(this);
            this->Neighbors.pop_back();
        }
    }

    bool CollapseVertex::IsNeighbor(CollapseVertex* v) {
        std::vector<CollapseVertex*>::iterator neighbor =
            std::find(this->Neighbors.begin(),
                      this->Neighbors.end(),
                      v);

        return (neighbor != this->Neighbors.end());
    }

    bool CollapseVertex::IsNeighbor(CollapseVertex* v,
                                    std::vector<CollapseVertex*>::iterator& neighbor) {
        neighbor =
            std::find(this->Neighbors.begin(),
                      this->Neighbors.end(),
                      v);

        return (neighbor != this->Neighbors.end());
    }

    bool CollapseVertex::AddNeighbor(CollapseVertex* v) {
        if (!this->IsNeighbor(v) && v != this) {
            this->Neighbors.push_back(v);

            if (this->use_cost) {
                float c = this->ComputeCost(v);
                this->AddCost(c, v);
            }

            return true;
        }

        return false;
    }

    bool CollapseVertex::RemoveNeighbor(CollapseVertex* v) {
        std::vector<CollapseVertex*>::iterator neighbor;
        if (this->IsNeighbor(v, neighbor)) {
            this->Neighbors.erase(neighbor);

            if (this->use_cost) {
                this->RemoveCost(v);
            }

            return true;
        }

        return false;
    }

    bool CollapseVertex::RemoveIfNotNeighbor(CollapseVertex* v) {
        // removes n from neighbor list if n isn't a neighbor.
        if (!this->IsInFaces(v)) {
            return this->RemoveNeighbor(v);
        }

        return false;
    }

    bool CollapseVertex::IsFace(CollapseTriangle* t) {
        std::vector<CollapseTriangle*>::iterator face =
            std::find(this->Faces.begin(),
                      this->Faces.end(),
                      t);

        return (face != this->Faces.end());
    }

    bool CollapseVertex::IsFace(CollapseTriangle* t,
                                std::vector<CollapseTriangle*>::iterator& face) {
        face =
            std::find(this->Faces.begin(),
                      this->Faces.end(),
                      t);

        return (face != this->Faces.end());
    }

    bool CollapseVertex::IsInFaces(CollapseVertex* v) {
        for (int i = 0; i < (int)this->Faces.size(); i++) {
            if (this->Faces[i]->HasVertex(v)) {
                return true;
            }
        }
        return false;
    }

    bool CollapseVertex::IsInFaces(CollapseVertex* v,
                                   CollapseTriangle*& triangle) {
        for (int i = 0; i < (int)this->Faces.size(); i++) {
            if (this->Faces[i]->HasVertex(v)) {
                triangle = this->Faces[i];
                return true;
            }
        }
        return false;
    }

    void CollapseVertex::AddFace(CollapseTriangle* f) {
        assert(f->HasVertex(this));

        if (!this->IsFace(f)) {
            this->Faces.push_back(f);

            for (int i = 0; i < 3; i++) {
                if (f->vertex[i] == this) {
                    continue;
                }

                this->AddNeighbor(f->vertex[i]);
            }
        }
    }

    void CollapseVertex::RemoveFace(CollapseTriangle* f) {
        assert(f->HasVertex(this));

        std::vector<CollapseTriangle*>::iterator face;
        if (this->IsFace(f, face)) {
            this->Faces.erase(face);

            for (int i = 0; i < 3; i++) {
                if (f->vertex[i] == this) {
                    continue;
                }

                this->RemoveIfNotNeighbor(f->vertex[i]);
            }
        }
    }

    bool CollapseVertex::IsBorder(void) {
        return this->border;
    }

    void CollapseVertex::LockBorder(void) {
        this->border = (this->Faces.size() < this->Neighbors.size());
    }

    void CollapseVertex::AddCost(float c, CollapseVertex* v) {
        std::pair<float, CollapseVertex*> n_pair(c, v);
        this->n_costs.insert(n_pair);

        if (c < this->Cost || !this->Candidate) {
            this->Cost = c;
            this->Candidate = v;
        }
    }

    void CollapseVertex::RemoveCost(CollapseVertex* v) {
        std::multimap<float, CollapseVertex*>::iterator c;
        for (c = this->n_costs.begin();
                c != this->n_costs.end();
                c++) {
            if (c->second == v) {
                this->n_costs.erase(c);
                break;
            }
        }

        if (this->Candidate == v) {
            if (this->n_costs.empty()) {
                this->Cost = -1.0f;
                this->Candidate = NULL;
            } else {
                this->Cost = this->n_costs.begin()->first;
                this->Candidate = this->n_costs.begin()->second;
            }
        }
    }

    float CollapseVertex::GetCost(CollapseVertex* v) {
        if (!this->use_cost) {
            return -1.0f;
        }

        std::multimap<float, CollapseVertex*>::iterator c;
        for (c = this->n_costs.begin();
                c != this->n_costs.end();
                c++) {
            if (c->second == v) {
                return c->first;
            }
        }

        return -1.0f;
    }

    bool CollapseVertex::IsSameUV(CollapseVertex* v) {
        return this->Vert.texCoord == v->Vert.texCoord;
    }

    bool CollapseVertex::operator==(CollapseVertex* v) {
        return (this->ID == v->ID && this->parent == v->parent);
    }

    bool CollapseVertex::operator<(CollapseVertex* v) {
        return (this->Cost > v->Cost);
    }

    bool CollapseVertex::SortByCost(CollapseVertex* u,
                                    CollapseVertex* v) {
        return (u->Cost > v->Cost);
    }

    float CollapseVertex::ComputeCost(CollapseVertex* v) {
        // if we collapse edge uv by moving u to v then how
        // much different will the model change, i.e. how much "error".
        // Texture, vertex normal, and border vertex code was removed
        // to keep this demo as simple as possible.
        // The method of determining cost was designed in order
        // to exploit small and coplanar regions for
        // effective polygon reduction.
        // Is is possible to add some checks here to see if "folds"
        // would be generated.  i.e. normal of a remaining face gets
        // flipped.  I never seemed to run into this problem and
        // therefore never added code to detect this case.

        assert(this->IsNeighbor(v));

        float edgelength = 1.0f;
        if (this->parent->Arguments.useedgelength) {
            Vector3 len = (v->Vert.Position - this->Vert.Position);
            edgelength = len.Magnitude();
        }

        // prevent impossible movements
        if (this->Neighbors.size() == v->Neighbors.size()) {
            int i;
            for (i = 0; i < (int)this->Neighbors.size(); i++) {
                if (this->Neighbors[i] == v) {
                    continue;
                }
                if (!v->IsNeighbor(this->Neighbors[i])) {
                    break;
                }
            }

            // they share the same neighbors, alert!
            if (i == (int)this->Neighbors.size()) {
                return 999999.9f;
            }
        }

        float curvature = 0.001f;

        // find the "sides" triangles that are on the edge uv
        std::vector<CollapseTriangle*> sides;

        for (int i = 0; i < (int)this->Faces.size(); i++) {
            if (v->IsFace(this->Faces[i])) {
                sides.push_back(this->Faces[i]);
            }
        }

        if (this->parent->Arguments.usecurvature) {
            // use the triangle facing most away from the sides
            // to determine our curvature term
            for (int i = 0; i < (int)this->Faces.size(); i++) {
                float mincurv = 1; // curve for face i and closer side to it

                for (int j = 0; j < (int)sides.size(); j++) {
                    // use dot product of face normals. '^' defined in vector
                    float dotprod =
                        this->Faces[i]->normal.DotProduct(
                            sides[j]->normal);
                    mincurv = min(mincurv, (1.002f - dotprod) / 2.0f);
                }
                curvature = max(curvature, mincurv);
            }
        }

        // check for border to interior collapses
        if (this->IsBorder()) {
            curvature *= WEIGHT_BORDER;
        }

        // LockDown border edges (i.e. try not to touch them at all)
        // this is done by locking any border vertex.
        // i.e. even if uv isn't a border edge we dont want
        // to collapse u to any vertex
        // if u is on a border
        if (this->parent->Arguments.protecttexture) {
            // check for texture seam ripping
            if (!this->IsSameUV(v)) {
                curvature = 1;
            }
        }

        if (this->parent->Arguments.protectvc) {
            // adding support for 2nd pass or vert color here:
            // check for vert color (or uvw2) seam ripping
            if (!(*(DWORD*)this->Vert.Diffuse == *(DWORD*)v->Vert.Diffuse)) {
                curvature = 1;
            }
        }

        if (this->parent->Arguments.lockborder && this->IsBorder()) {
            curvature = 9999.9f;
        }

        return edgelength * curvature;
    }

    void CollapseVertex::ComputeNormal(void) {
        if (this->Faces.empty()) {
            return;
        }

        Vector3 Face_Normal;

        for (int i = 0; i < (int)this->Faces.size(); i++) {
            Face_Normal += this->Faces[i]->normal;
        }

        this->Vert.Normal = Face_Normal.Normalized();
    }

} // namespace Niflib
