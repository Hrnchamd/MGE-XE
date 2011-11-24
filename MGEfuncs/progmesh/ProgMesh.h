/* ****************************************** *
 * --- Progressive Mesh Polygon Reduction --- *
 *                                            *
 *     Originally by Stan Melax, published    *
 *     at http://www.melax.com/polychop/      *
 *                                            *
 *     Reworked by wz for use with the        *
 *     Niflib library.                        *
 * ****************************************** */

#ifndef PROGMESH_H
#define PROGMESH_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <Assert.h>
#include <algorithm>
#include <vector>
#include <iostream>

#include <nif_math.h>

#include "../DXVertex.h"
#include "CollapseVertex.h"
#include "CollapseTriangle.h"

#define WEIGHT_BORDER 100

namespace Niflib {

    class ProgMesh;
    class CollapseVertex;
    class CollapseTriangle;

    struct PMarg {
    public:
        bool useedgelength;
        bool usecurvature;
        bool protecttexture;
        bool protectvc;
        bool lockborder;
        bool keepborder;
        bool removeduplicate;
    };

    class ProgMesh
    {
    public:
        ProgMesh(DWORD vertCount, DWORD faceCount, DXVertex* verts, WORD* faces);
        ~ProgMesh(void);

        // Compute the collapse information
        void ComputeProgressiveMesh(void);

        // Apply the collapsed mesh
        int DoProgressiveMesh(float, DWORD*, DWORD*, DXVertex**, WORD**);

        int GetVertexCount(void);
        int GetTriangleCount(void);

        // Control vertices
        bool HasVertex(CollapseVertex *);
        bool HasVertex(CollapseVertex *,
            std::vector<CollapseVertex *>::iterator &);
        void RemoveVertex(CollapseVertex *);

        // Control triangles
        bool HasTriangle(CollapseTriangle *);
        bool HasTriangle(CollapseTriangle *,
            std::vector<CollapseTriangle *>::iterator &);
        void RemoveTriangle(CollapseTriangle *);

        // Expose the collapse arguments
        PMarg Arguments;

        // Get some mesh data
        Triangle    GetFace(unsigned int);
        DXVertex    GetVert(unsigned int);

    private:
        // The containers that hold the meshes data
        std::vector<CollapseVertex *> vertices;
        std::vector<CollapseTriangle *> triangles;

        // The actual collapsing information
        std::vector<int> CollapseOrder;
        std::vector<int> CollapseMap;

        // Cache contents of the mesh
        int VertexCount;
        int TriangleCount;
        std::vector<Triangle> Faces;
        std::vector<DXVertex> Verts;

        // check for duplicate vertices
        bool CheckDuplicate(CollapseVertex * &);

        // collapsing methods
        void ComputeEdgeCostAtVertex(CollapseVertex *);
        void ComputeAllEdgeCollapseCosts(void);
        void Collapse(CollapseVertex *, CollapseVertex*, bool);
    };

}; //namespace Niflib

#endif
