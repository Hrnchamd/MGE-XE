#include "ProgMesh.h"

namespace Niflib {

    ProgMesh::ProgMesh(DWORD vertCount, DWORD faceCount, DXVertex* verts, WORD* faces) {
        this->VertexCount = vertCount;
        this->TriangleCount = faceCount;

        Verts.clear();
        Verts.reserve(vertCount);
        for (DWORD i = 0; i < vertCount; i++) {
            Verts.push_back(verts[i]);
        }

        Faces.clear();
        Faces.reserve(faceCount);
        for (DWORD i = 0; i < faceCount; i++) {
            Faces.push_back(*(Triangle*)&faces[i*3]);
        }
    }

    ProgMesh::~ProgMesh(void) {
    }

    bool ProgMesh::HasVertex(CollapseVertex* v) {
        std::vector<CollapseVertex*>::iterator vertex = std::find(this->vertices.begin(), this->vertices.end(), v);
        return (vertex != this->vertices.end());
    }

    bool ProgMesh::HasVertex(CollapseVertex* v, std::vector<CollapseVertex*>::iterator& vertex) {
        vertex = std::find(this->vertices.begin(), this->vertices.end(), v);
        return (vertex != this->vertices.end());
    }

    void ProgMesh::RemoveVertex(CollapseVertex* v) {
        std::vector<CollapseVertex*>::iterator vertex;
        if (this->HasVertex(v, vertex)) {
            delete v;
            this->vertices.erase(vertex);
        }
    }

    bool ProgMesh::HasTriangle(CollapseTriangle* t) {
        std::vector<CollapseTriangle*>::iterator triangle = std::find(this->triangles.begin(), this->triangles.end(), t);
        return (triangle != this->triangles.end());
    }

    bool ProgMesh::HasTriangle(CollapseTriangle* t, std::vector<CollapseTriangle*>::iterator& triangle) {
        triangle = std::find(this->triangles.begin(), this->triangles.end(), t);
        return (triangle != this->triangles.end());
    }

    void ProgMesh::RemoveTriangle(CollapseTriangle* t) {
        std::vector<CollapseTriangle*>::iterator triangle;
        if (this->HasTriangle(t, triangle)) {
            delete t;
            this->triangles.erase(triangle);
        }
    }

    Triangle ProgMesh::GetFace(unsigned int n) {
        return this->Faces[n];
    }

    DXVertex ProgMesh::GetVert(unsigned int n) {
        return this->Verts[n];
    }

    int ProgMesh::GetVertexCount(void) {
        return this->VertexCount;
    }

    int ProgMesh::GetTriangleCount(void) {
        return this->TriangleCount;
    }

    bool ProgMesh::CheckDuplicate(CollapseVertex*& v) {
        for (int i = 0; i < (int)this->vertices.size(); i++) {
            CollapseVertex* u = this->vertices[i];

            if (u->Vert.Position == v->Vert.Position) {
                if (u->Vert.Normal != v->Vert.Normal) {
                    continue;
                }

                if (this->Arguments.protecttexture && !(u->IsSameUV(v))) {
                    continue;
                }

                if (this->Arguments.protectvc && !(*(DWORD*)u->Vert.Diffuse == *(DWORD*)v->Vert.Diffuse)) {
                    continue;
                }

                // delete the duplicate
                delete v;

                // copy the pointer to the original vertex
                v = this->vertices[i];
                v->Duplicate++;

                return true;
            }
        }

        return false;
    }

    void ProgMesh::ComputeEdgeCostAtVertex(CollapseVertex* v) {
        // compute the edge collapse cost for all edges that start
        // from vertex v.  Since we are only interested in reducing
        // the object by selecting the min cost edge at each step, we
        // only cache the cost of the least cost edge at this vertex
        // (in member variable collapse) as well as the value of the
        // cost (in member variable objdist).
        if (v->Neighbors.empty()) {
            // v doesn't have neighbors so it costs nothing to collapse
            v->Candidate = NULL;
            v->Cost = -0.01f;
            return;
        }

        // search all neighboring edges for "least cost" edge
        for (int i = 0; i < (int)v->Neighbors.size(); i++) {
            float cost = v->ComputeCost(v->Neighbors[i]);
            v->AddCost(cost, v->Neighbors[i]);
        }
    }

    void ProgMesh::ComputeAllEdgeCollapseCosts(void) {
        // For all the edges, compute the difference it would make
        // to the model if it was collapsed.  The least of these
        // per vertex is cached in each vertex object.
        for (int i = 0; i < (int)this->vertices.size(); i++) {
            this->ComputeEdgeCostAtVertex(this->vertices[i]);
        }

        // sort the vertices by "cost"
        std::sort(this->vertices.begin(),
                  this->vertices.end(),
                  CollapseVertex::SortByCost);
    }

    void ProgMesh::Collapse(CollapseVertex* u,
                            CollapseVertex* v,
                            bool recompute = true) {
        // Collapse the edge uv by moving vertex u onto v
        // Actually remove tris on uv, then update tris that
        // have u to have v, and then remove u.
        if (!v) {
            // u is a vertex all by itself so just delete it
            this->RemoveVertex(u);
            return;
        }

        // store the sides that contain both u and v
        std::vector<CollapseTriangle*> sides;
        for (int i = 0; i < (int)u->Faces.size(); i++) {
            if (u->Faces[i]->HasVertex(v)) {
                sides.push_back(u->Faces[i]);
            }
        }

        // delete triangles on edge uv:
        for (int i = 0; i < (int)sides.size(); i++) {
            this->RemoveTriangle(sides[i]);
        }

        // update remaining triangles to have v instead of u
        for (int i = (int)u->Faces.size(); i > 0; i--) {
            u->Faces.back()->ReplaceVertex(u, v);
        }

        this->RemoveVertex(u);

        std::sort(this->vertices.begin(),
                  this->vertices.end(), CollapseVertex::SortByCost);
    }

    void ProgMesh::ComputeProgressiveMesh(void) {
        this->vertices.clear();
        this->vertices.reserve(this->VertexCount);

        for (int i = 0; i < this->VertexCount; i++) {
            CollapseVertex* v = new CollapseVertex(this, i);

            if (this->Arguments.removeduplicate) {
                this->CheckDuplicate(v);
            }

            this->vertices.push_back(v);
        }

        this->triangles.clear();
        this->triangles.reserve(this->TriangleCount);

        for (int i = 0; i < this->TriangleCount; i++) {
            CollapseTriangle* t = new CollapseTriangle(
                this->vertices[this->Faces[i].v1],
                this->vertices[this->Faces[i].v2],
                this->vertices[this->Faces[i].v3]);
            this->triangles.push_back(t);
        }

        for (int i = 0; i < (int)this->vertices.size(); i++) {
            // reindex to compensate removed dups
            this->vertices[i]->ID = i;

            // now see if vertex is border in the original mesh
            this->vertices[i]->LockBorder();

            // from now, automatically calculate costs
            this->vertices[i]->use_cost = true;

            // remove this if it is a dup
            if (this->vertices[i]->Duplicate) {
                this->vertices[i]->Duplicate--;
                this->vertices.erase(this->vertices.begin() + i);
                i--;
            }
        }

        this->ComputeAllEdgeCollapseCosts();

        this->CollapseOrder.clear();
        this->CollapseOrder.resize(this->VertexCount);
        this->CollapseMap.clear();
        this->CollapseMap.resize(this->VertexCount);

        while (!this->vertices.empty()) {
            // get the next vertex to collapse
            CollapseVertex* mn = this->vertices.back();
            CollapseVertex* cv = mn->Candidate;

            // store the collapse order
            this->CollapseOrder[vertices.size() - 1] = mn->ID;
            this->CollapseMap[mn->ID] = (cv ? cv->ID : -1);

            // Collapse() this vertex
            this->Collapse(mn, cv);
        }

        assert(this->triangles.size() == 0);
        assert(this->vertices.size() == 0);
    }


    int ProgMesh::DoProgressiveMesh(float ratio, DWORD* newVertCount, DWORD* newFaceCount, DXVertex** newVerts, WORD** newFaces) {
        assert(this->CollapseOrder.size() == this->VertexCount);

        // how many vertices are left after reduction
        unsigned int target = (unsigned int)(ratio * this->VertexCount);

        // clear the vertex and triangle lists
        this->vertices.clear();
        this->triangles.clear();

        // container for the vertices after reduction
        std::vector<CollapseVertex*> CollapseList;

        // containers for the reduced mesh
        std::vector<Triangle> new_Faces;
        std::vector<DXVertex> new_Verts;

        for (int i = 0; i < this->VertexCount; i++) {
            CollapseVertex* v = new CollapseVertex(this, i);

            if (this->Arguments.removeduplicate) {
                this->CheckDuplicate(v);
            }

            this->vertices.push_back(v);
        }

        for (int i = 0; i < this->TriangleCount; i++) {
            Triangle t_ = this->Faces[i];
            CollapseTriangle* t = new CollapseTriangle(
                this->vertices[t_.v1],
                this->vertices[t_.v2],
                this->vertices[t_.v3]);
            this->triangles.push_back(t);
        }

        for (int i = 0; i < (int)this->vertices.size(); i++) {
            this->vertices[i]->ID = i;
            this->vertices[i]->LockBorder();

            if (this->vertices[i]->Duplicate) {
                this->vertices[i]->Duplicate--;
                this->vertices.erase(this->vertices.begin() + i);
                i--;
            }
        }

        for (int i = 0; i < (int)this->vertices.size(); i++) {
            CollapseVertex* mn = this->vertices[i];
            CollapseVertex* cv =
                (this->CollapseMap[mn->ID] == -1) ?
                NULL : this->vertices[this->CollapseMap[mn->ID]];

            mn->Candidate = cv;

            CollapseList.push_back(this->vertices[CollapseOrder[i]]);
        }

        while ((DWORD)CollapseList.size() > target) {
            // get the next vertex to collapse
            CollapseVertex* mn = CollapseList.back();

            // abort if we start to collapse borders
            if (/*this->Arguments.keepborder &&
                this->Arguments.lockborder &&*/
                mn->IsBorder()) {
                /*std::cerr << "Target is "
                    << target
                    << ", but node is a border already."
                    << "\nAborting..." << endl;*/
                break;
            }

            // abort if we reach the impossible collapses
            if (mn->Cost > 999999.0f) {
                /*std::cerr << "Target is "
                    << target
                    << ", but this is an impossible collapse already."
                    << "\nAborting..." << endl;*/
                break;
            }

            // Collapse this edge
            Collapse(mn, mn->Candidate, false);

            // remove this entry from the list
            CollapseList.pop_back();
        }

        for (int i = 0; i < (int)this->vertices.size(); i++) {
            // reassign the ID of the vertex
            this->vertices[i]->ID = i;

            // recompute the vertex' normal
            this->vertices[i]->ComputeNormal();

            new_Verts.push_back(this->vertices[i]->Vert);
        }

        for (unsigned int i = 0; i < this->triangles.size(); i++) {
            Triangle face;
            face.v1 = this->triangles[i]->vertex[0]->ID;
            face.v2 = this->triangles[i]->vertex[1]->ID;
            face.v3 = this->triangles[i]->vertex[2]->ID;

            new_Faces.push_back(face);
        }

        // Free vertices and faces
        for (size_t i = 0; i < this->triangles.size(); i++) {
            delete this->triangles[i];
        }
        for (size_t i = 0; i < this->vertices.size(); i++) {
            delete this->vertices[i];
        }
        this->triangles.clear();
        this->vertices.clear();

        // store the return value, the number of vertices left
        int result = (int)new_Verts.size();
        if (result == 0 || new_Faces.size() == 0 || new_Verts.size() == VertexCount) {
            return 0;
        }

        // set the new mesh data
        *newFaceCount = new_Faces.size();
        *newVertCount = new_Verts.size();

        *newFaces = new WORD[new_Faces.size()*3];
        *newVerts = new DXVertex[new_Verts.size()];

        for (DWORD i = 0; i < new_Faces.size(); i++) {
            *(Triangle*)(&(*newFaces)[i*3]) = new_Faces[i];
        }
        memcpy(*newVerts, &new_Verts[0], sizeof(DXVertex) * new_Verts.size());

        return result;
    }

}; //namespace Niflib
