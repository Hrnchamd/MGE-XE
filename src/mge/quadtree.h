#pragma once

#include "dlmath.h"
#include "memorypool.h"
#include <vector>
#include <map>
#include <deque>



struct QuadTreeMesh {
    BoundingSphere sphere;
    BoundingBox box;

    IDirect3DTexture9* tex;
    D3DXMATRIX transform;
    int verts;
    IDirect3DVertexBuffer9* vBuffer;
    int faces;
    IDirect3DIndexBuffer9* iBuffer;
    bool hasalpha;

    QuadTreeMesh(
        BoundingSphere b_sphere,
        BoundingBox b_box,
        D3DXMATRIX transform,
        IDirect3DTexture9* tex,
        int verts,
        IDirect3DVertexBuffer9* vBuffer,
        int faces,
        IDirect3DIndexBuffer9* iBuffer
    );

    ~QuadTreeMesh();
    QuadTreeMesh& operator=(const QuadTreeMesh& rh);
    QuadTreeMesh(const QuadTreeMesh& rh);

    bool operator==(const QuadTreeMesh& rh);

    static bool CompareByState(const QuadTreeMesh* lh, const QuadTreeMesh* rh);
    static bool CompareByTexture(const QuadTreeMesh* lh, const QuadTreeMesh* rh);
};

//-----------------------------------------------------------------------------

class VisibleSet {
public:
    void RemoveAll();
    VisibleSet() {}
    ~VisibleSet() {}

    void Render(
        IDirect3DDevice9* device,
        ID3DXEffect* effect,
        ID3DXEffect* effectPool,
        D3DXHANDLE* texture_handle,
        D3DXHANDLE* hasalpha_handle,
        D3DXHANDLE* world_matrix_handle,
        unsigned int vertex_size );

    void SortByState();
    void SortByTexture();
    size_t size() const {
        return visible_set.size();
    }

    std::deque<const QuadTreeMesh*> visible_set;
};

//-----------------------------------------------------------------------------

class QuadTree;

struct QuadTreeNode {
    QuadTree* m_owner;
    QuadTreeNode* children[4];
    float box_size;
    D3DXVECTOR2 box_center;
    BoundingSphere sphere;
    std::vector<QuadTreeMesh*> meshes;

    QuadTreeNode(QuadTree* owner);
    ~QuadTreeNode();

    void GetVisibleMeshes(const ViewFrustum& frustum, const D3DXVECTOR4& viewsphere, VisibleSet& visible_set, bool inside = false);
    void GetVisibleMeshesCoarse(const ViewFrustum& frustum, VisibleSet& visible_set, bool inside = false);
    void AddMesh(QuadTreeMesh* new_mesh, int depth);

    void PushDown(QuadTreeMesh* new_mesh, int depth);
    bool Optimize();
    BoundingSphere CalcVolume();
    int GetChildCount() const;
    void ClearChildren();
};

//-----------------------------------------------------------------------------

class QuadTree {
public:

    QuadTree();
    ~QuadTree();
    void AddMesh(
        BoundingSphere sphere,
        BoundingBox box,
        D3DXMATRIX transform,
        IDirect3DTexture9* tex,
        int verts,
        IDirect3DVertexBuffer9* vBuffer,
        int faces,
        IDirect3DIndexBuffer9* iBuffer
    );
    bool Optimize();
    void Clear();
    void GetVisibleMeshes(const ViewFrustum& frustum, const D3DXVECTOR4& viewsphere, VisibleSet& visible_set);
    void GetVisibleMeshesCoarse(const ViewFrustum& frustum, VisibleSet& visible_set);
    void SetBox(float size, const D3DXVECTOR2& center);
    void CalcVolume();

    QuadTreeNode* m_root_node;
    MemoryPool m_node_pool;
    MemoryPool m_mesh_pool;

protected:
    friend struct QuadTreeNode;
    QuadTreeNode* CreateNode();
    QuadTreeMesh* CreateMesh(
        BoundingSphere sphere,
        BoundingBox box,
        D3DXMATRIX transform,
        IDirect3DTexture9* tex,
        int verts,
        IDirect3DVertexBuffer9* vBuffer,
        int faces,
        IDirect3DIndexBuffer9* iBuffer
    );
private:
    // Disallow copy and assignment
    QuadTree& operator=(QuadTree&);
    QuadTree(QuadTree&);
};
