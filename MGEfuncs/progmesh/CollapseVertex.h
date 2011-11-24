#ifndef COLLAPSEVERTEX_H
#define COLLAPSEVERTEX_H

#include <algorithm>
#include <map>
#include <vector>

#include <nif_math.h>

#include "../DXVertex.h"
#include "ProgMesh.h"
#include "CollapseTriangle.h"

namespace Niflib {

    class ProgMesh;
    class CollapseTriangle;
    class CollapseVertex;

    class CollapseVertex
    {
    public:
        CollapseVertex(ProgMesh *, unsigned int, bool = false);
        ~CollapseVertex(void);

        std::vector<CollapseVertex *> Neighbors;
        bool IsNeighbor(CollapseVertex *);
        bool IsNeighbor(CollapseVertex *,
            std::vector<CollapseVertex *>::iterator &);
        bool AddNeighbor(CollapseVertex *);
        bool RemoveNeighbor(CollapseVertex *);
        bool RemoveIfNotNeighbor(CollapseVertex *);

        std::vector<CollapseTriangle *> Faces;
        bool IsFace(CollapseTriangle *);
        bool IsFace(CollapseTriangle *,
            std::vector<CollapseTriangle *>::iterator &);
        bool IsInFaces(CollapseVertex *);
        bool IsInFaces(CollapseVertex *, CollapseTriangle * &);
        void AddFace(CollapseTriangle *);
        void RemoveFace(CollapseTriangle *);

        bool IsBorder(void);
        void LockBorder(void);

        void AddCost(float, CollapseVertex *);
        void RemoveCost(CollapseVertex *);
        float GetCost(CollapseVertex *);
        float ComputeCost(CollapseVertex *);

        void ComputeNormal(void);

        DXVertex Vert;
        unsigned int                    ID;
        float                            Cost;
        CollapseVertex *                Candidate;
        unsigned int                    Duplicate;

        bool IsSameUV(CollapseVertex *);

        bool use_cost;

        bool operator==(CollapseVertex *);
        bool operator< (CollapseVertex *);

        static bool SortByCost(CollapseVertex *, CollapseVertex *);

    private:
        ProgMesh * parent;
        std::multimap<float, CollapseVertex *> n_costs;
        bool border;
    };

} // namespace Niflib

#endif
