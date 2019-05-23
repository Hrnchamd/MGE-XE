
#include "quadtree.h"

#include <algorithm>



using std::deque;

static const size_t QUADTREE_MAX_DEPTH = 8;
static const size_t QUADTREE_TARGET_LEAF_SIZE = 6;
static const float QUADTREE_MIN_DIST = 20.0f;

//-----------------------------------------------------------------------------
// QuadTreeMesh class
//-----------------------------------------------------------------------------

QuadTreeMesh::QuadTreeMesh(
    BoundingSphere sphere,
    BoundingBox box,
    D3DXMATRIX transform,
    IDirect3DTexture9* tex,
    int verts,
    IDirect3DVertexBuffer9* vBuffer,
    int faces,
    IDirect3DIndexBuffer9* iBuffer
) {
    this->sphere = sphere;
    this->box = box;
    this->transform = transform;
    this->tex = tex;
    this->verts = verts;
    this->vBuffer = vBuffer;
    this->faces = faces;
    this->iBuffer = iBuffer;

    D3DSURFACE_DESC texdesc;
    tex->GetLevelDesc(0, &texdesc);
    this->hasalpha = (texdesc.Format == D3DFMT_A8R8G8B8 || texdesc.Format == D3DFMT_DXT3 || texdesc.Format == D3DFMT_DXT5);
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
    tex = rh.tex;
    verts = rh.verts;
    vBuffer = rh.vBuffer;
    faces = rh.faces;
    iBuffer = rh.iBuffer;
    hasalpha = rh.hasalpha;

    return *this;
}

//-----------------------------------------------------------------------------

QuadTreeMesh::QuadTreeMesh(const QuadTreeMesh& rh) {
    *this = rh;
}

//-----------------------------------------------------------------------------

bool QuadTreeMesh::CompareByState(const QuadTreeMesh* lh, const QuadTreeMesh* rh) {
    if (lh->tex < rh->tex) {
        return true;
    }

    if (lh->tex == rh->tex && lh->vBuffer < rh->vBuffer) {
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------

bool QuadTreeMesh::CompareByTexture(const QuadTreeMesh* lh, const QuadTreeMesh* rh) {
    return (lh->tex < rh->tex);
}

//-----------------------------------------------------------------------------

bool QuadTreeMesh::operator==(const QuadTreeMesh& rh) {
    return (tex == rh.tex && vBuffer == rh.vBuffer);
}

//-----------------------------------------------------------------------------
// VisibleSet class
//-----------------------------------------------------------------------------

void VisibleSet::RemoveAll() {
    visible_set.clear();
}

//-----------------------------------------------------------------------------

void VisibleSet::Render(
    IDirect3DDevice9* device,
    ID3DXEffect* effect,
    ID3DXEffect* effectPool,
    D3DXHANDLE* texture_handle,
    D3DXHANDLE* hasalpha_handle,
    D3DXHANDLE* world_matrix_handle,
    unsigned int vertex_size) {
    // Iterate through each group of textures in the map
    IDirect3DTexture9* last_texture = 0;
    IDirect3DVertexBuffer9* last_buffer = 0;

    const auto& visible_set_const = visible_set;
    for (const auto mesh : visible_set_const) {
        bool effect_changed = false;

        // Set texture if it has changed
        if (effect && texture_handle && last_texture != mesh->tex) {
            effectPool->SetTexture(*texture_handle, mesh->tex);
            if (hasalpha_handle) {
                // Control if texture access is required
                effectPool->SetBool(*hasalpha_handle, mesh->hasalpha);
            } else {
                // Alpha test is compatible with transparency supersampling, while clip() isn't
                device->SetRenderState(D3DRS_ALPHATESTENABLE, mesh->hasalpha);
            }
            effect_changed = true;
            last_texture = mesh->tex;
        }

        // Set buffer if it has changed
        if (last_buffer != mesh->vBuffer) {
            device->SetIndices(mesh->iBuffer);
            device->SetStreamSource(0, mesh->vBuffer, 0, vertex_size);
            last_buffer = mesh->vBuffer;
        }

        // Set transform matrix
        if (effect && world_matrix_handle) {
            effectPool->SetMatrix(*world_matrix_handle, &mesh->transform);
            effect_changed = true;
        }

        // Commit any changes that were made to the effect
        if (effect_changed) {
            effect->CommitChanges();
        }

        device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh->verts, 0, mesh->faces);
    }
}

//-----------------------------------------------------------------------------

void VisibleSet::SortByState() {
    if (visible_set.size() > 0) {
        std::sort(visible_set.begin(), visible_set.end(), QuadTreeMesh::CompareByState);
    }
}

//-----------------------------------------------------------------------------

void VisibleSet::SortByTexture() {
    if (visible_set.size() > 0) {
        std::sort(visible_set.begin(), visible_set.end(), QuadTreeMesh::CompareByTexture);
    }
}

//-----------------------------------------------------------------------------
// QuadTreeNode class
//-----------------------------------------------------------------------------

void QuadTreeNode::GetVisibleMeshes(const ViewFrustum& frustum, const D3DXVECTOR4& viewsphere, VisibleSet& visible_set, bool inside) {
    // Check if this node is fully outside the frustum.
    // If inside = true then that means it has already been determined that this entire branch is visible
    if (inside == false) {
        ViewFrustum::Containment result = frustum.ContainsSphere(sphere);

        if (result == ViewFrustum::OUTSIDE) {
            return;
        }

        if (result == ViewFrustum::INSIDE) {
            inside = true;
        }
    }

    // If this node has children, check them
    if (GetChildCount() > 0) {
        if (children[0]) {
            children[0]->GetVisibleMeshes(frustum, viewsphere, visible_set, inside);
        }

        if (children[1]) {
            children[1]->GetVisibleMeshes(frustum, viewsphere, visible_set, inside);
        }

        if (children[2]) {
            children[2]->GetVisibleMeshes(frustum, viewsphere, visible_set, inside);
        }

        if (children[3]) {
            children[3]->GetVisibleMeshes(frustum, viewsphere, visible_set, inside);
        }

        return;
    }

    // If this node has any meshes, check each of their visibility and add them to the list if they're not completely outside the frustum
    for (size_t i = 0, size = meshes.size(); i < size; ++i) {
        const QuadTreeMesh* mesh = meshes[i];

        if (inside == false) {
            ViewFrustum::Containment res = frustum.ContainsSphere(mesh->sphere);
            if (res == ViewFrustum::OUTSIDE) {
                continue;
            }

            if (res == ViewFrustum::INTERSECTS) {
                // The sphere intersects one of the edges of the screen, so try the box test
                res = frustum.ContainsBox(mesh->box);
                if (res == ViewFrustum::OUTSIDE) {
                    continue;
                }
            }
        }

        // Avoid camera rotation dependent clipping by using a spherical far clip plane
        // Test mesh against view sphere (eyepos.xyz, radius)
        D3DXVECTOR3 eyepos(viewsphere.x, viewsphere.y, viewsphere.z);
        D3DXVECTOR3 d = mesh->sphere.center - eyepos;
        float rangesquared = d.x*d.x + d.y*d.y + d.z*d.z;
        float viewlimit = viewsphere.w + mesh->sphere.radius;

        if (rangesquared <= viewlimit*viewlimit) {
            visible_set.visible_set.push_back(mesh);
        }
    }
}

void QuadTreeNode::GetVisibleMeshesCoarse(const ViewFrustum& frustum, VisibleSet& visible_set, bool inside) {
    // Check if this node is fully outside the frustum.
    // If inside = true then that means it has already been determined that this entire branch is visible
    if (inside == false) {
        ViewFrustum::Containment result = frustum.ContainsSphere(sphere);

        if (result == ViewFrustum::OUTSIDE) {
            return;
        }

        if (result == ViewFrustum::INSIDE) {
            inside = true;
        }
    }

    // If this node has children, check them
    if (GetChildCount() > 0) {
        if (children[0]) {
            children[0]->GetVisibleMeshesCoarse(frustum, visible_set, inside);
        }

        if (children[1]) {
            children[1]->GetVisibleMeshesCoarse(frustum, visible_set, inside);
        }

        if (children[2]) {
            children[2]->GetVisibleMeshesCoarse(frustum, visible_set, inside);
        }

        if (children[3]) {
            children[3]->GetVisibleMeshesCoarse(frustum, visible_set, inside);
        }

        return;
    }

    // If this node has any meshes, check each of their visibility and add them to the list if they're not completely outside the frustum
    for (size_t i = 0, size = meshes.size(); i < size; ++i) {
        const QuadTreeMesh* mesh = meshes[i];

        // Only test bounding sphere
        if (inside == false && frustum.ContainsSphere(mesh->sphere) == ViewFrustum::OUTSIDE) {
            continue;
        }

        visible_set.visible_set.push_back(mesh);
    }
}

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

void QuadTree::AddMesh(
    BoundingSphere sphere,
    BoundingBox box,
    D3DXMATRIX transform,
    IDirect3DTexture9* tex,
    int verts,
    IDirect3DVertexBuffer9* vBuffer,
    int faces,
    IDirect3DIndexBuffer9* iBuffer
) {
    QuadTreeMesh* new_mesh = CreateMesh(
                                 sphere,
                                 box,
                                 transform,
                                 tex,
                                 verts,
                                 vBuffer,
                                 faces,
                                 iBuffer);

    m_root_node->AddMesh(new_mesh, QUADTREE_MAX_DEPTH);
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

void QuadTree::GetVisibleMeshes(const ViewFrustum& frustum, const D3DXVECTOR4& sphere, VisibleSet& visible_set) {
    m_root_node->GetVisibleMeshes(frustum, sphere, visible_set);
}

void QuadTree::GetVisibleMeshesCoarse(const ViewFrustum& frustum, VisibleSet& visible_set) {
    m_root_node->GetVisibleMeshesCoarse(frustum, visible_set);
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
    BoundingSphere sphere,
    BoundingBox box,
    D3DXMATRIX transform,
    IDirect3DTexture9* tex,
    int verts,
    IDirect3DVertexBuffer9* vBuffer,
    int faces,
    IDirect3DIndexBuffer9* iBuffer
) {

    QuadTreeMesh* new_obj = (QuadTreeMesh*)m_mesh_pool.Alloc();
    // Use placement new to construct the object
    ::new(new_obj) QuadTreeMesh(
        sphere,
        box,
        transform,
        tex,
        verts,
        vBuffer,
        faces,
        iBuffer);
    return new_obj;
}

//-----------------------------------------------------------------------------
