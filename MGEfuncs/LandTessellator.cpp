#include <assert.h>
#include <fstream>
#include <vector>
#include <float.h>

#include "progmesh/ProgMesh.h"
#include "../3rdparty/tootle/src/TootleLib/include/tootlelib.h"

using namespace Niflib;
using std::vector;

struct LargeTriangle {
    unsigned int v1; /*!< The index of the first vertex. */
    unsigned int v2; /*!< The index of the second vertex. */
    unsigned int v3; /*!< The index of the third vertex. */

    LargeTriangle() {}

    LargeTriangle(unsigned int v1, unsigned int v2, unsigned int v3) {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }

    void Set(unsigned int v1, unsigned int v2, unsigned int v3) {
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }

    unsigned int& operator[](int n) {
        switch (n) {
        case 0:
            return v1;
            break;
        case 1:
            return v2;
            break;
        case 2:
            return v3;
            break;
        default:
            throw std::out_of_range("Index out of range for Triangle");
        };
    }
    unsigned int operator[](int n) const {
        switch (n) {
        case 0:
            return v1;
            break;
        case 1:
            return v2;
            break;
        case 2:
            return v3;
            break;
        default:
            throw std::out_of_range("Index out of range for Triangle");
        };
    }
};

class LandMesh {
public:
    vector<Vector3> vertices;
    vector<LargeTriangle> triangles;
    vector<TexCoord> uvs;
    float radius;
    Vector3 center;
    Vector3 min;
    Vector3 max;

    void CalcBounds(const Vector3& new_min, const Vector3& new_max) {

        min = new_min;
        max = new_max;

        // Average min/max positions to get center
        center = (min + max) / 2.0f;

        // Find the furthest point from the center to get the radius
        float radius_sqared = 0.0f;

        for (size_t i = 0; i < vertices.size(); ++i) {
            float x, y, z;
            x = vertices[i].x;
            y = vertices[i].y;
            z = vertices[i].z;

            float dist = (x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) + (z-center.z)*(z-center.z);

            if (dist > radius_sqared) {
                radius_sqared = dist;
            }
        }

        radius = sqrt(radius_sqared);
    }

    static bool SaveMeshes(LPCSTR file_path, vector<LandMesh>& meshes) {
        DWORD mesh_count, unused;
        HANDLE file = CreateFile(file_path,GENERIC_WRITE,0,0,CREATE_ALWAYS,0,0);
        if (file == INVALID_HANDLE_VALUE) {
            return false;
        }
        mesh_count = meshes.size();
        WriteFile(file, &mesh_count, 4, &unused, 0 );

        for (size_t i = 0; i < meshes.size(); ++i) {
            if (!meshes[i].Save(file)) {
                return false;
            }
        }

        CloseHandle(file);

        return true;
    }

    bool Save(HANDLE& file) {
        DWORD verts, faces, unused;
        bool large;
        verts = vertices.size();
        faces = triangles.size();

        WriteFile(file, &radius, 4, &unused, 0);
        WriteFile(file, &center, 12, &unused, 0);
        WriteFile(file, &min, 12, &unused, 0);
        WriteFile(file, &max, 12, &unused, 0);
        WriteFile(file, &verts, 4, &unused, 0);
        WriteFile(file, &faces, 4, &unused, 0);

        if (verts > 0xFFFF || faces > 0xFFFF) {
            large = true;
        } else {
            large = false;
        }

        std::vector<DXCompressedLandVertex> compVerts(verts);

        for (size_t i = 0; i < verts; ++i) {
            compVerts[i].Position = vertices[i];
            compVerts[i].texCoord[0] = (short)(uvs[i].u * 32768.0f);
            compVerts[i].texCoord[1] = (short)(uvs[i].v * 32768.0f);
        }

        WriteFile(file, &*compVerts.begin(), sizeof(DXCompressedLandVertex) * verts, &unused, 0);

        for (size_t i = 0; i < faces; ++i) {
            if (large) {
                unsigned int tmp[3];
                tmp[0] = triangles[i].v1;
                tmp[1] = triangles[i].v2;
                tmp[2] = triangles[i].v3;
                WriteFile(file,tmp,4*3,&unused,0);
            } else {
                unsigned short tmp[3];
                tmp[0] = triangles[i].v1;
                tmp[1] = triangles[i].v2;
                tmp[2] = triangles[i].v3;
                WriteFile(file,tmp,2*3,&unused,0);
            }
        }

        return true;
    }
};

class HeightFieldSampler {
public:
    struct AtlasRegion {
        float minX, maxX, minY, maxY;
        float offsetX, offsetY;
        float scaleX, scaleY;
    };

    float top, left, bottom, right;
    float* data;
    size_t data_height;
    size_t data_width;
    AtlasRegion* atlas_data;
    size_t atlas_count;

    HeightFieldSampler(float* d, size_t dh, size_t dw, float* adata, size_t ac, float t, float l, float b, float r) :
        top(t), left(l), bottom(b), right(r), data(d), data_height(dh), data_width(dw),
        atlas_data(reinterpret_cast<AtlasRegion*>(adata)), atlas_count(ac) {}
    ~HeightFieldSampler() {}

    TexCoord SampleTexCoord(float x, float y) {
        for (size_t n = 0; n < atlas_count; ++n) {
            AtlasRegion* r = &atlas_data[n];

            if (x >= r->minX && x <= r->maxX && y >= r->minY && y <= r->maxY) {
                float tx = (x - r->minX + r->offsetX) / r->scaleX;
                float ty = (y - r->minY + r->offsetY) / r->scaleY;
                return TexCoord(tx, 1.0f - ty);
            }
        }
        return TexCoord(0, 0);
    }

    float SampleHeight(float x, float y) {
        // Figure which height values to sample.
        size_t low_x, high_x, low_y, high_y;

        float data_x = (0.0f - left + x) / (right - left) * (float)data_width;
        float data_y = (0.0f - bottom + y) / (top - bottom) * (float)data_height;

        low_x = (size_t)floor(data_x);
        high_x = (size_t)ceil(data_x);
        low_y = (size_t)floor(data_y);
        high_y = (size_t)ceil(data_y);

        // Linear Interpolation
        float x_interp = 1.0f;
        if (high_x - low_x == 1) {
            x_interp = data_x - (float)low_x;
        }

        float y_interp = 1.0f;
        if (high_y - low_y == 1) {
            y_interp = data_y - (float)low_y;
        }

        // horizontal
        float bottom_val = GetHeightValue(low_x, low_y) * (1.0f - x_interp) + GetHeightValue(high_x, low_y) * x_interp;
        float top_val = GetHeightValue(low_x, high_y) * (1.0f - x_interp) + GetHeightValue(high_x, high_y) * x_interp;

        // vertical
        float result = top_val * (1.0f - y_interp) + bottom_val * y_interp;
        return result;
    }

    float GetHeightValue(size_t x, size_t y) {
        if (x < 0) {
            x = 0;
        }
        if (x > data_width - 1) {
            x = data_width - 1;
        }
        if (y < 0) {
            y = 0;
        }
        if (y > data_height - 1) {
            y = data_height -1;
        }

        return data[ y * data_width + x ];
    }
};

class SplitTriangle {
public:
    Vector3 left, right, top;
    SplitTriangle(const Vector3& left, const Vector3& right, const Vector3& top) {
        this->left = left;
        this->right = right;
        this->top = top;
    }
    ~SplitTriangle() {}

    Vector3 GetHypoCenter() const {
        return (right + left) / 2.0f;
    }

    SplitTriangle LeftSplit(const Vector3& new_vert) const {
        return SplitTriangle(right, top, new_vert);
    }

    SplitTriangle RightSplit(const Vector3& new_vert) const {
        return SplitTriangle(top, left, new_vert);
    }
};

class RoamVarianceNode {
public:
    float variance;
    RoamVarianceNode* left_child;
    RoamVarianceNode* right_child;

private:
    static size_t last_used_index;
    static vector<RoamVarianceNode> pool;


public:
    static RoamVarianceNode* Create() {
        // Make sure pool can hold this object
        if (last_used_index + 1 >= pool.size()) {
            // No more room RoamVarianceNode objects to hand out.
            return nullptr;
        }

        // increment the last used index and return the object at that position
        ++last_used_index;
        // Clear out any data in the object so it's as if it's a new object
        pool[last_used_index].ClearChildren();

        return &pool[last_used_index];
    }

    // This shouldn't be called directly, used Create instead to allocate with the pool
    RoamVarianceNode() : variance(0.0f), left_child(0), right_child(0) {}

    static void ResetPool() {
        // Move the index of the next node to be handed out back to the begining.
        // There should be no outstanding RoamVarianceNode pointers when this is called.
        last_used_index = 0;
    }

    void ClearChildren() {
        left_child = 0;
        right_child = 0;
    }

    ~RoamVarianceNode() {}

    void CalculateVariance(HeightFieldSampler* sampler, const SplitTriangle& tri, size_t depth) {
        // On the downward pass, calculate the variance as the difference in height between the
        // average of left and right, and the the real height value as given by the sampler
        Vector3 avg = tri.GetHypoCenter();
        float samp_height = sampler->SampleHeight(avg.x, avg.y);

        variance = abs(avg.z - samp_height);

        // Give extra weight to the split if it causes the vertex to switch from being above the water to being below the water or vice versa
        // Water level is zero
        if ((avg.z > 0.0f && samp_height < 0.0f) || (samp_height > 0.0f && avg.z < 0.0f)) {
            variance *= 4.0f;
        }

        // Give extra weight to the split if it the average vertex would be above the real height
        if (avg.z > samp_height) {
            variance *= 4.0f;
        }

        // If we have reached the maximum depth, free any children and start unwiding traversal
        if (depth == 0) {
            ClearChildren();
            return;
        }

        // If we have not reached the maximum depth, create children and call this function on them
        avg.z = samp_height;

        if (!right_child) {
            right_child = Create();
        }
        right_child->CalculateVariance(sampler, tri.RightSplit(avg), depth - 1);


        if (!left_child) {
            left_child = Create();
        }
        left_child->CalculateVariance(sampler, tri.LeftSplit(avg), depth - 1);

        // We want the variance of this node to represent the maximum variance of all children nodes, so choose the highest of
        // the variances as the new variance
        if (right_child->variance > variance) {
            variance = right_child->variance;
        }
        if (left_child->variance > variance) {
            variance = left_child->variance;
        }
    }
};

size_t RoamVarianceNode::last_used_index = 0;
vector<RoamVarianceNode> RoamVarianceNode::pool(32768);

class RoamTriangleNode;

class RenderTriangle {
public:
    SplitTriangle st;
    unsigned int left_index, right_index, top_index;
    RoamTriangleNode* rt;

    RenderTriangle(const SplitTriangle& s_tri, RoamTriangleNode* r_tri) : st(s_tri), rt(r_tri) {
        left_index = 0xFFFFFFFF;
        right_index = 0xFFFFFFFF;
        top_index = 0xFFFFFFFF;
    }
    ~RenderTriangle() {}
};

class RoamTriangleNode {
public:
    RoamTriangleNode* left_child;
    RoamTriangleNode* right_child;
    RoamTriangleNode* base_neighbor;
    RoamTriangleNode* left_neighbor;
    RoamTriangleNode* right_neighbor;

    RoamTriangleNode() : left_child(0), right_child(0), base_neighbor(0), left_neighbor(0), right_neighbor(0) {}
    ~RoamTriangleNode() {
        if (left_child) {
            delete left_child;
        }
        if (right_child) {
            delete right_child;
        }
    }

    void Split() {
        // Check whether this node has already been split
        if (left_child || right_child) {
            // This node has already been split
            return;
        }

        // Check if the hypotonuse of this triangle is on an edge (has no base neighbor)
        if (!base_neighbor) {
            // This is on an edge, so split this triangle only
            EdgeSplit();
            return;
        }

        // Check if this triangle and its base neighbor form a diamond (they are eachother's base neighbor)
        if (base_neighbor->base_neighbor == this) {
            // split this triangle and its neighbor
            DiamondSplit();
            return;
        }

        // These triangles don't form a diamond, so call split on the base neighbor before splitting this triangle
        base_neighbor->Split();

        // Split the triangle and its neighbor
        DiamondSplit();
    }

private:
    void EdgeSplit() {
        assert(left_child == 0 && right_child == 0);

        // Create children
        left_child = new RoamTriangleNode();
        right_child = new RoamTriangleNode();

        // Set neighbor linkage
        left_child->base_neighbor = left_neighbor;
        left_child->left_neighbor = right_child;
        left_child->right_neighbor = 0;

        RelinkNeighbor(left_child->left_neighbor, this, left_child);
        RelinkNeighbor(left_child->base_neighbor, this, left_child);

        right_child->base_neighbor = right_neighbor;
        right_child->left_neighbor = 0;
        right_child->right_neighbor = left_child;

        RelinkNeighbor(right_child->left_neighbor, this, right_child);
        RelinkNeighbor(right_child->base_neighbor, this, right_child);

        // Clear neighbors of this object since it now just represents a node, not a real triangle
        // Don't clear base_neighbor since it should either already be null or cleared by the DiamondSplit function
        right_neighbor = 0;
        left_neighbor = 0;
    }

    void RelinkNeighbor(RoamTriangleNode* neighbor, RoamTriangleNode* old_link, RoamTriangleNode* new_link) {
        if (neighbor) {
            if (neighbor->base_neighbor == old_link) {
                neighbor->base_neighbor = new_link;
            } else if (neighbor->left_neighbor == old_link) {
                neighbor->left_neighbor = new_link;
            } else if (neighbor->right_neighbor == old_link) {
                neighbor->right_neighbor = new_link;
            }
        }
    }

    void DiamondSplit() {
        assert(base_neighbor != 0 && base_neighbor->base_neighbor == this);

        // Start with an edge split for both triangles
        EdgeSplit();
        base_neighbor->EdgeSplit();

        // Now set left and right neighbor links which are set to zero by the basic edge split
        right_child->left_neighbor = base_neighbor->left_child;
        left_child->right_neighbor = base_neighbor->right_child;

        base_neighbor->right_child->left_neighbor = left_child;
        base_neighbor->left_child->right_neighbor = right_child;

        // Clear base_neighbors of these objects since they now just represents a node, not a real triangle
        base_neighbor->base_neighbor = 0;
        base_neighbor = 0;

    }
public:
    void Tessellate(RoamVarianceNode* v_tri, float max_variance) {
        // Determine if the variance of this triangle is enough that we want to split it
        if (v_tri->variance < max_variance) {
            // The variance is within tolerable levels, so end the recursion of this branch
            return;
        }

        // The variance is too high, so we need to split this triangle
        Split();

        // If the variance triangle has children, continue on down the tree recursivly
        if (!v_tri->left_child || !v_tri->right_child) {
            // The variance triangle has no children, so we're done
            return;
        }

        // The variance triangle has children so call this function on the newly created children of this roam triangle node
        left_child->Tessellate(v_tri->left_child, max_variance);
        right_child->Tessellate(v_tri->right_child, max_variance);
    }

    void GatherTriangles(HeightFieldSampler* sampler, const SplitTriangle& s_tri, vector<RenderTriangle>& triangles) {

        Vector3 hc = s_tri.GetHypoCenter();
        hc.z = sampler->SampleHeight(hc.x, hc.y);

        if (!left_child || !right_child) {
            // This node has no children, so add the triangle to the list and return
            triangles.push_back(RenderTriangle(s_tri, this));
            return;
        }

        // This node has children, so call this function on them
        left_child->GatherTriangles(sampler, s_tri.LeftSplit(hc), triangles);
        right_child->GatherTriangles(sampler, s_tri.RightSplit(hc), triangles);
    }
};

class CmpVec3 : public Vector3 {
public:
    CmpVec3(const Vector3& v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    CmpVec3& operator=(const Vector3& rh) {
        x = rh.x;
        y = rh.y;
        z = rh.z;
        return *this;
    }

    Vector3 AsVec3() {
        return Vector3(x,y,z);
    }

    static bool FltEq(float lh, float rh) {
        return abs(lh - rh) < 0.0001f;
    }

    static bool FltLt(float lh, float rh) {
        return lh - 0.0001f < rh;
    }

    bool operator==(const CmpVec3& rh) const {
        return FltEq(x, rh.x) && FltEq(y, rh.y) && FltEq(z, rh.z);
    }

    friend bool operator<(const CmpVec3& lh, const CmpVec3& rh) {
        if (lh == rh) {
            return false;
        }

        if (FltEq(lh.x, rh.x)) {
            if (FltEq(lh.y, rh.y)) {
                return lh.z < rh.z;
            } else {
                return lh.y < rh.y;
            }
        }

        return lh.x < rh.x;
    }
};

class RoamLandPatch {
public:
    float top, left, bottom, right;
    RoamTriangleNode t1, t2;
    HeightFieldSampler* sampler;

    RoamLandPatch() {
        t1.base_neighbor = &t2;
        t2.base_neighbor = &t1;
    }
    RoamLandPatch(float t, float l, float b, float r, HeightFieldSampler* s) : top(t), left(l), bottom(b), right(r), sampler(s) {
        t1.base_neighbor = &t2;
        t2.base_neighbor = &t1;
    }

    RoamLandPatch(const RoamLandPatch& patch) {
        sampler = patch.sampler;
        top = patch.top;
        left = patch.left;
        bottom = patch.bottom;
        right = patch.right;

        t1.base_neighbor = &t2;
        t2.base_neighbor = &t1;
    }

    ~RoamLandPatch() {}

    Vector3 GetTopLeft() {
        return Vector3(left, top, sampler->SampleHeight(left,top));
    }
    Vector3 GetBottomLeft() {
        return Vector3(left, bottom, sampler->SampleHeight(left,bottom));
    }
    Vector3 GetTopRight() {
        return Vector3(right, top, sampler->SampleHeight(right,top));
    }
    Vector3 GetBottomRight() {
        return Vector3(right, bottom, sampler->SampleHeight(right,bottom));
    }

    void ConnectRightNeighbor(RoamLandPatch& neighbor) {
        t2.right_neighbor = &neighbor.t1;
        neighbor.t1.right_neighbor = &t2;
    }

    void ConnectLeftNeighbor(RoamLandPatch& neighbor) {
        t1.right_neighbor = &neighbor.t2;
        neighbor.t2.right_neighbor = &t1;
    }

    void ConnectTopNeighbor(RoamLandPatch& neighbor) {
        t2.left_neighbor = &neighbor.t1;
        neighbor.t1.left_neighbor = &t2;
    }

    void ConnectBottomNeighbor(RoamLandPatch& neighbor) {
        t1.left_neighbor = &neighbor.t2;
        neighbor.t2.left_neighbor = &t1;
    }

    void Tessellate(float max_variance, size_t tree_depth) {
        Vector3 top_left = GetTopLeft();
        Vector3 bottom_left = GetBottomLeft();
        Vector3 top_right = GetTopRight();
        Vector3 bottom_right = GetBottomRight();

        RoamVarianceNode* variance_root = RoamVarianceNode::Create();
        variance_root->CalculateVariance(sampler, SplitTriangle(bottom_right, top_left, bottom_left), tree_depth);
        t1.Tessellate(variance_root, max_variance);
        variance_root = 0;
        RoamVarianceNode::ResetPool();

        variance_root = RoamVarianceNode::Create();
        variance_root->CalculateVariance(sampler, SplitTriangle(top_left, bottom_right, top_right), tree_depth);
        t2.Tessellate(variance_root, max_variance);
        variance_root = 0;

        RoamVarianceNode::ResetPool();
    }

    LandMesh GenerateMesh(unsigned int cache_size) {
        LandMesh mesh;
        Vector3 top_left = GetTopLeft();
        Vector3 bottom_left = GetBottomLeft();
        Vector3 top_right = GetTopRight();
        Vector3 bottom_right = GetBottomRight();

        vector<RenderTriangle> render_triangles;

        t1.GatherTriangles(sampler, SplitTriangle(bottom_right, top_left, bottom_left), render_triangles);
        t2.GatherTriangles(sampler, SplitTriangle(top_left, bottom_right, top_right), render_triangles);

        // Walk through the triangles that were gathered, adding their vertices and indices to a map
        Vector3 max = Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        Vector3 min = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

        map<CmpVec3, size_t> vert_map;
        size_t render_triangles_size = render_triangles.size();
        for (size_t i = 0; i < render_triangles_size; ++i) {
            size_t right_index, left_index, top_index;
            map<CmpVec3, size_t>::iterator it;

            it = vert_map.find(render_triangles[i].st.left);
            if (it == vert_map.end()) {
                // Add new index
                left_index = mesh.vertices.size();
                Vector3& v = render_triangles[i].st.left;
                vert_map[v] = left_index;
                mesh.vertices.push_back(v);

                if (v.x > max.x) { max.x = v.x; }
                if (v.y > max.y) { max.y = v.y; }
                if (v.z > max.z) { max.z = v.z; }

                if (v.x < min.x) { min.x = v.x; }
                if (v.y < min.y) { min.y = v.y; }
                if (v.z < min.z) { min.z = v.z; }
            } else {
                // Get index from existing vertex
                left_index = it->second;
            }

            it = vert_map.find(render_triangles[i].st.right);
            if (it == vert_map.end()) {
                // Add new index
                right_index = mesh.vertices.size();
                Vector3& v = render_triangles[i].st.right;
                vert_map[v] = right_index;
                mesh.vertices.push_back(v);

                if (v.x > max.x) { max.x = v.x; }
                if (v.y > max.y) { max.y = v.y; }
                if (v.z > max.z) { max.z = v.z; }

                if (v.x < min.x) { min.x = v.x; }
                if (v.y < min.y) { min.y = v.y; }
                if (v.z < min.z) { min.z = v.z; }
            } else {
                // Get index from existing vertex
                right_index = it->second;
            }

            it = vert_map.find(render_triangles[i].st.top);
            if (it == vert_map.end()) {
                // Add new index
                top_index = mesh.vertices.size();
                Vector3& v = render_triangles[i].st.top;
                vert_map[v] = top_index;
                mesh.vertices.push_back(v);

                if (v.x > max.x) { max.x = v.x; }
                if (v.y > max.y) { max.y = v.y; }
                if (v.z > max.z) { max.z = v.z; }

                if (v.x < min.x) { min.x = v.x; }
                if (v.y < min.y) { min.y = v.y; }
                if (v.z < min.z) { min.z = v.z; }
            } else {
                // Get index from existing vertex
                top_index = it->second;
            }

            mesh.triangles.push_back(LargeTriangle(right_index, top_index, left_index));
        }

        if (abs(min.z + 2048.0f) <= 0.001f && abs(max.z + 2048.0f) <= 0.001f) {
            // This mesh is perfectly flat at the bottom of the world.  Return an empty mesh.
            return LandMesh();
        }

        // Calculate mesh bounds
        mesh.CalcBounds(min, max);

        // Cache optimize triangle and vertex order
        unsigned int* iBuffer = (unsigned int*)&mesh.triangles[0];
        void* vBuffer = (void*)&mesh.vertices[0];
        unsigned int verts = (unsigned int)mesh.vertices.size();
        unsigned int faces = (unsigned int)mesh.triangles.size();
        unsigned int stride = 3 * sizeof(float);

        TootleResult result = TootleOptimizeVCache(iBuffer, faces, verts, cache_size, iBuffer, NULL, TOOTLE_VCACHE_AUTO);

        if (result != TOOTLE_OK) {
            return LandMesh();
        }

        result = TootleOptimizeVertexMemory(vBuffer, iBuffer, verts, faces, stride, vBuffer, iBuffer, NULL);

        if (result != TOOTLE_OK) {
            return LandMesh();
        }

        // Now that all the vertices have been found, figure out the UVs for them
        for (size_t i = 0; i < mesh.vertices.size(); ++i) {
            mesh.uvs.push_back(sampler->SampleTexCoord(mesh.vertices[i].x, mesh.vertices[i].y));
        }

        return mesh;
    }
};

extern "C" void TessellateLandscapeAtlased(char* file_path, float* height_data, unsigned int data_height, unsigned int data_width, float* atlas_data, unsigned int atlas_count, float top, float left, float bottom, float right, float error_tolerance) {

    // Create sampler
    HeightFieldSampler sampler(height_data, data_height, data_width, atlas_data, atlas_count, top, left, bottom, right);

    // Create patches
    size_t patches_across = (size_t)floor(((float)data_width) / 256.0f + 0.5f);
    size_t patches_down = (size_t)floor(((float)data_height) / 256.0f + 0.5f);

    float patch_width = (right - left) / (float)patches_across;
    float patch_height = (top - bottom) / (float)patches_down;

    vector<RoamLandPatch> patches;

    Vector3 corner(left, bottom, 0.0f);

    // Fill in patch data
    patches.resize(patches_across * patches_down);

    for (size_t y = 0; y < patches_down; ++y) {
        for (size_t x = 0; x < patches_across; ++x) {
            size_t i = y * patches_across + x;

            patches[i].sampler = &sampler;
            patches[i].left = corner.x;
            patches[i].right = corner.x + patch_width;
            patches[i].bottom = corner.y;
            patches[i].top = corner.y + patch_height;

            // Move the corner right for the next patch
            corner.x += patch_width;
        }
        // Move the corner up and back to the left edge for the next patch
        corner.y += patch_height;
        corner.x = left;
    }

    // Connect neighboring patches
    for (size_t y = 0; y < patches_down; ++y) {
        for (size_t x = 0; x < patches_across; ++x) {
            size_t index = y * patches_across + x;
            size_t rn_index = y * patches_across + x + 1;
            size_t tn_index = (y+1) * patches_across + x;

            if (x != patches_across - 1) {
                patches[index].t2.left_neighbor = &patches[rn_index].t1;
                patches[rn_index].t1.left_neighbor = &patches[index].t2;
            }

            if (y != patches_down - 1) {
                patches[index].t2.right_neighbor = &patches[tn_index].t1;
                patches[tn_index].t1.right_neighbor = &patches[index].t2;
            }
        }
    }

    // Tessellate patches
    for (size_t i = 0; i < patches.size(); ++i) {
        patches[i].Tessellate(error_tolerance, 14);
    }

    // Generate Meshes
    vector<LandMesh> meshes;

    for (size_t i = 0; i < patches.size(); ++i) {
        LandMesh mesh = patches[i].GenerateMesh(16);

        if (mesh.vertices.size() > 0) {
            meshes.push_back(mesh);
        }
    }

    // Count verts and tris
    size_t verts = 0;
    size_t tris = 0;
    for (size_t i = 0; i < meshes.size(); ++i) {
        verts += meshes[i].vertices.size();
        tris += meshes[i].triangles.size();
    }

    // Save the Meshes
    LandMesh::SaveMeshes(file_path, meshes);
}

