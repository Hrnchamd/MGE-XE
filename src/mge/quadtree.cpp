
#include "quadtree.h"

#include <algorithm>



static const size_t QUADTREE_MAX_DEPTH = 10;
static const size_t QUADTREE_TARGET_LEAF_SIZE = 15;
static const float QUADTREE_MIN_DIST = 20.0f;

//-----------------------------------------------------------------------------
// QuadTreeMesh class
//-----------------------------------------------------------------------------

QuadTreeMesh::QuadTreeMesh(
    const BoundingSphere& sphere,
    const BoundingBox& box,
    const D3DXMATRIX& transform,
    bool hasAlpha,
    bool animateUV,
    ptr32<IDirect3DTexture9> tex,
    int verts,
    ptr32<IDirect3DVertexBuffer9> vBuffer,
    int faces,
    ptr32<IDirect3DIndexBuffer9> iBuffer
) {
    this->sphere = sphere;
    this->box = box;
    this->enabled = true;
    this->hasAlpha = hasAlpha;
    this->animateUV = animateUV;
    this->transform = transform;
    this->tex = tex;
    this->verts = verts;
    this->vBuffer = vBuffer;
    this->faces = faces;
    this->iBuffer = iBuffer;
}

//-----------------------------------------------------------------------------

QuadTreeMesh::~QuadTreeMesh() {
    // Don't free anything, mesh resources are shared
}

//-----------------------------------------------------------------------------

QuadTreeMesh& QuadTreeMesh::operator=(const QuadTreeMesh& rh) {
    sphere.center = rh.sphere.center;
    sphere.radius = rh.sphere.radius;
    box = rh.box;
    transform = rh.transform;
    hasAlpha = rh.hasAlpha;
    animateUV = rh.animateUV;
    tex = rh.tex;
    verts = rh.verts;
    vBuffer = rh.vBuffer;
    faces = rh.faces;
    iBuffer = rh.iBuffer;

    return *this;
}

//-----------------------------------------------------------------------------

QuadTreeMesh::QuadTreeMesh(const QuadTreeMesh& rh) {
    *this = rh;
}

//-----------------------------------------------------------------------------

bool QuadTreeMesh::CompareByState(const RenderMesh& lh, const RenderMesh& rh) {
    if (lh.tex < rh.tex) {
        return true;
    }

    if (lh.tex == rh.tex && lh.vBuffer < rh.vBuffer) {
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------

bool QuadTreeMesh::CompareByTexture(const RenderMesh& lh, const RenderMesh& rh) {
    return (lh.tex < rh.tex);
}

//-----------------------------------------------------------------------------

bool QuadTreeMesh::operator==(const QuadTreeMesh& rh) {
    return (tex == rh.tex && vBuffer == rh.vBuffer);
}

//-----------------------------------------------------------------------------
// QuadTreeNode class
//-----------------------------------------------------------------------------

void QuadTreeNode::AddMesh(QuadTreeMesh* new_mesh, int depth) {
    size_t meshes_size = meshes.size();

    // If we have reached the last level of the quad tree, add the mesh and return
    if (depth == 0) {
        meshes.push_back(new_mesh);
        return;
    }

    // If this node has no meshes or children, go ahead and add the mesh to it
    if (GetChildCount() == 0 && meshes_size < QUADTREE_TARGET_LEAF_SIZE) {
        meshes.push_back(new_mesh);
        return;
    }

    // If there are already meshes at this node, add it anyway if it's close enough to the first one
    if (meshes_size > 0) {
        D3DXVECTOR3 diff = new_mesh->sphere.center - meshes[0]->sphere.center;
        if (D3DXVec3Length(&diff) <= QUADTREE_MIN_DIST) {
            meshes.push_back(new_mesh);
            return;
        }
    }

    // Push down the new mesh and the existing ones
    PushDown(new_mesh, depth);

    for (size_t i = 0; i != meshes_size; ++i) {
        PushDown(meshes[i], depth);
    }

    // Clear mesh list
    meshes.clear();
}

//-----------------------------------------------------------------------------

void QuadTreeNode::PushDown(QuadTreeMesh* new_mesh, int depth) {
    if (new_mesh->sphere.center.y > box_center.y) {
        if (new_mesh->sphere.center.x > box_center.x) {
            // Quadrant I (+x +y)
            if (!children[0]) {
                // Create child
                children[0] = m_owner->CreateNode();
                children[0]->box_size = box_size / 2;
                children[0]->box_center.x = box_center.x + box_size / 4;
                children[0]->box_center.y = box_center.y + box_size / 4;
            }

            children[0]->AddMesh(new_mesh, depth - 1);
        } else {
            // Quadrant II (-x +y)
            if (!children[1]) {
                // Create child
                children[1] = m_owner->CreateNode();
                children[1]->box_size = box_size / 2;
                children[1]->box_center.x = box_center.x - box_size / 4;
                children[1]->box_center.y = box_center.y + box_size / 4;
            }

            children[1]->AddMesh(new_mesh, depth - 1);
        }
    } else {
        if (new_mesh->sphere.center.x < box_center.x) {
            // Quadrant III (-x -y)
            if (!children[2]) {
                // Create child
                children[2] = m_owner->CreateNode();
                children[2]->box_size = box_size / 2;
                children[2]->box_center.x = box_center.x - box_size / 4;
                children[2]->box_center.y = box_center.y - box_size / 4;
            }

            children[2]->AddMesh(new_mesh, depth - 1);
        } else {
            // Quadrant IV (+x -y)
            if (!children[3]) {
                // Create child
                children[3] = m_owner->CreateNode();
                children[3]->box_size = box_size / 2;
                children[3]->box_center.x = box_center.x + box_size / 4;
                children[3]->box_center.y = box_center.y - box_size / 4;
            }

            children[3]->AddMesh(new_mesh, depth - 1);
        }
    }
}

//-----------------------------------------------------------------------------

bool QuadTreeNode::Optimize() {
    // Call this function on each child
    for (size_t i = 0; i < 4; ++i) {
        QuadTreeNode* old_child = children[i];
        if (old_child && old_child->Optimize()) {
            // This child has only one child of its own so it should be removed
            // First get the child
            QuadTreeNode* new_child = 0;
            for (size_t j = 0; j < 4; ++j) {
                new_child = old_child->children[j];
                if (new_child) {
                    old_child->children[j] = 0;
                    break;
                }
            }

            // Replace this child with its child
            children[i] = new_child;
            // old_child dealloc handled when MemoryPool is flushed
        }
    }

    // Report number of children remaining in this node to calling function after optimization is complete
    if (GetChildCount() == 1) {
        // This node should be removed
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------

BoundingSphere QuadTreeNode::CalcVolume() {
    // Traverse down until we reach the leaf nodes, then percolate the bounding spheres back up
    sphere = BoundingSphere();

    if (children[0]) {
        sphere += children[0]->CalcVolume();
    }

    if (children[1]) {
        sphere += children[1]->CalcVolume();
    }

    if (children[2]) {
        sphere += children[2]->CalcVolume();
    }

    if (children[3]) {
        sphere += children[3]->CalcVolume();
    }

    if (sphere.empty()) {
        // This node doesn't have any children, so sum the bounds of its meshes
        for (size_t i = 0; i < meshes.size(); ++i) {
            sphere += meshes[i]->sphere;
        }
    }

    return sphere;
}

//-----------------------------------------------------------------------------

int QuadTreeNode::GetChildCount() const {
    int count = 0;

    if (children[0]) {
        ++count;
    }

    if (children[1]) {
        ++count;
    }

    if (children[2]) {
        ++count;
    }

    if (children[3]) {
        ++count;
    }

    return count;
}

//-----------------------------------------------------------------------------

QuadTreeNode::QuadTreeNode(QuadTree* owner) {
    children[0] = 0;
    children[1] = 0;
    children[2] = 0;
    children[3] = 0;

    box_size = 0.0f;
    box_center.x = 0.0f;
    box_center.y = 0.0f;

    m_owner = owner;
}

//-----------------------------------------------------------------------------

QuadTreeNode::~QuadTreeNode() {
    // Don't delete meshes or children because the tree doesn't own them
}

//-----------------------------------------------------------------------------
// QuadTree class
//-----------------------------------------------------------------------------

QuadTree::QuadTree() :
    m_node_pool(sizeof(QuadTreeNode), 500),
    m_mesh_pool(sizeof(QuadTreeMesh), 500) {

    // Create the root node
    m_root_node = CreateNode();
}

//-----------------------------------------------------------------------------

QuadTree::~QuadTree() {
    // Blow away the memory pools
    m_node_pool.Flush();
    m_mesh_pool.Flush();

    m_root_node = 0;
}

//-----------------------------------------------------------------------------

QuadTreeMesh* QuadTree::AddMesh(
    const BoundingSphere& sphere,
    const BoundingBox& box,
    const D3DXMATRIX& transform,
    bool hasAlpha,
    bool animateUV,
    ptr32<IDirect3DTexture9> tex,
    int verts,
    ptr32<IDirect3DVertexBuffer9> vBuffer,
    int faces,
    ptr32<IDirect3DIndexBuffer9> iBuffer
) {
    QuadTreeMesh* new_mesh = CreateMesh(
                                 sphere,
                                 box,
                                 transform,
                                 hasAlpha,
                                 animateUV,
                                 tex,
                                 verts,
                                 vBuffer,
                                 faces,
                                 iBuffer);

    m_root_node->AddMesh(new_mesh, QUADTREE_MAX_DEPTH);
    return new_mesh;
}

//-----------------------------------------------------------------------------

bool QuadTree::Optimize() {
    return m_root_node->Optimize();
}

//-----------------------------------------------------------------------------

void QuadTree::Clear() {
    // Blow away the memory pools
    m_node_pool.Flush();
    m_mesh_pool.Flush();

    // Create a new root node
    m_root_node = CreateNode();
}

//-----------------------------------------------------------------------------

void QuadTree::SetBox(float size, const D3DXVECTOR2& center) {
    m_root_node->box_size = size;
    m_root_node->box_center = center;
}

//-----------------------------------------------------------------------------

void QuadTree::CalcVolume() {
    m_root_node->CalcVolume();
}

//-----------------------------------------------------------------------------

QuadTreeNode* QuadTree::CreateNode() {
    QuadTreeNode* new_obj = (QuadTreeNode*)m_node_pool.Alloc();

    // Use placement new to construct the object
    ::new(new_obj) QuadTreeNode(this);
    return new_obj;
}

//-----------------------------------------------------------------------------

QuadTreeMesh* QuadTree::CreateMesh(
    const BoundingSphere& sphere,
    const BoundingBox& box,
    const D3DXMATRIX& transform,
    bool hasAlpha,
    bool animateUV,
    ptr32<IDirect3DTexture9> tex,
    int verts,
    ptr32<IDirect3DVertexBuffer9> vBuffer,
    int faces,
    ptr32<IDirect3DIndexBuffer9> iBuffer
) {

    QuadTreeMesh* new_obj = (QuadTreeMesh*)m_mesh_pool.Alloc();
    // Use placement new to construct the object
    ::new(new_obj) QuadTreeMesh(
        sphere,
        box,
        transform,
        hasAlpha,
        animateUV,
        tex,
        verts,
        vBuffer,
        faces,
        iBuffer);
    return new_obj;
}

//-----------------------------------------------------------------------------
