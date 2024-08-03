#pragma once

#include "dlmath.h"
#include "memorypool.h"
#include "ipc/bridge.h"

#include <algorithm>
#include <vector>



struct QuadTreeMesh: public RenderMesh {
    BoundingSphere sphere;
    BoundingBox box;

    QuadTreeMesh(
        const BoundingSphere& b_sphere,
        const BoundingBox& b_box,
        const D3DXMATRIX& transform,
        bool hasAlpha,
        bool animateUV,
        ptr32<IDirect3DTexture9> tex,
        int verts,
        ptr32<IDirect3DVertexBuffer9> vBuffer,
        int faces,
        ptr32<IDirect3DIndexBuffer9> iBuffer
    );

    ~QuadTreeMesh();
    QuadTreeMesh& operator=(const QuadTreeMesh& rh);
    QuadTreeMesh(const QuadTreeMesh& rh);

    bool operator==(const QuadTreeMesh& rh);

    static bool CompareByState(const RenderMesh& lh, const RenderMesh& rh);
    static bool CompareByTexture(const RenderMesh& lh, const RenderMesh& rh);
};

//-----------------------------------------------------------------------------
template<class T>
class VisibleSet {
public:
    VisibleSet() {}
    VisibleSet(T&& container): visible_set(container) {}
    ~VisibleSet() {}

    void Render(IDirect3DDevice9* device,
                unsigned int vertex_size,
                bool parallelRead = false) {
        IDirect3DVertexBuffer9* last_buffer = 0;

        if (parallelRead) {
            visible_set.start_read();
        }
        visible_set.restart();
        while (!visible_set.at_end()) {
            const RenderMesh& mesh = visible_set.next();
            // Set buffer if it has changed
            if (last_buffer != mesh.vBuffer) {
                device->SetIndices(mesh.iBuffer);
                device->SetStreamSource(0, mesh.vBuffer, 0, vertex_size);
                last_buffer = mesh.vBuffer;
            }

            device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh.verts, 0, mesh.faces);
        }

        if (parallelRead) {
            visible_set.end_read();
        }
    }

    void Render(IDirect3DDevice9* device,
                ID3DXEffect* effect,
                ID3DXEffect* effectPool,
                const D3DXHANDLE* texture_handle,
                const D3DXHANDLE* has_alpha_handle,
                const D3DXHANDLE* animate_uv_handle,
                const D3DXHANDLE* world_matrix_handle,
                unsigned int vertex_size,
                bool parallelRead = false) {
        IDirect3DTexture9* last_texture = nullptr;
        IDirect3DVertexBuffer9* last_buffer = nullptr;
        bool last_animateUV = false;

        // Reset UV animation variables
        if (animate_uv_handle) {
            effectPool->SetBool(*animate_uv_handle, false);
            effect->CommitChanges();
        }

        if (parallelRead) {
            visible_set.start_read();
        }
        visible_set.restart();
        while (!visible_set.at_end()) {
            const RenderMesh& mesh = visible_set.next();

            // Set texture and texture related variables if it has changed
            if (texture_handle && last_texture != mesh.tex) {
                effectPool->SetTexture(*texture_handle, mesh.tex);

                if (has_alpha_handle) {
                    // Depth-only rendering, control if texture alpha channel reads are required in shader
                    effectPool->SetBool(*has_alpha_handle, mesh.hasAlpha);
                }
                else {
                    // World rendering, alpha test state is compatible with transparency supersampling, while clip() isn't
                    device->SetRenderState(D3DRS_ALPHATESTENABLE, mesh.hasAlpha);
                }
                last_texture = mesh.tex;
            }

            // Set UV animation variables. Different objects may use the same texture, but animate differently
            if (animate_uv_handle && mesh.animateUV != last_animateUV) {
                effectPool->SetBool(*animate_uv_handle, mesh.animateUV);
                last_animateUV = mesh.animateUV;
            }

            // Set buffer if it has changed
            if (last_buffer != mesh.vBuffer) {
                device->SetIndices(mesh.iBuffer);
                device->SetStreamSource(0, mesh.vBuffer, 0, vertex_size);
                last_buffer = mesh.vBuffer;
            }

            // Set transform matrix
            effectPool->SetMatrix(*world_matrix_handle, &mesh.transform);

            effect->CommitChanges();
            device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh.verts, 0, mesh.faces);
        }

        if (parallelRead) {
            visible_set.end_read();
        }
    }

    void SortByState() {
        visible_set.sort_by_state();
    }

    void SortByTexture() {
        visible_set.sort_by_texture();
    }

    void RemoveAll() {
        visible_set.clear();
    }

    void SetVector(const T& vector) {
        visible_set = vector;
    }

    size_t Size() const {
        return visible_set.size();
    }

    bool Empty() const {
        return visible_set.size() == 0;
    }

    void Truncate(std::size_t count) {
        visible_set.truncate(count);
    }

    void StartWrite() {
        visible_set.start_write();
    }

    void EndWrite() {
        visible_set.end_write();
    }

    void Reset() {
        visible_set.restart();
    }

    const RenderMesh& First() {
        return visible_set.first();
    }

    const RenderMesh& Next() {
        return visible_set.next();
    }

    void PushBack(const RenderMesh& mesh) {
        visible_set.push_back(mesh);
    }

    bool AtEnd() {
        return visible_set.at_end();
    }

    T visible_set;
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

    template<class T>
    void GetVisibleMeshes(const ViewFrustum& frustum, const D3DXVECTOR4& viewsphere, VisibleSet<T>& visible_set, bool inside = false) {
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
        if (meshes.empty()) {
            return;
        }

        // If this node has any meshes, check each of their visibility and add them to the list if they're not completely outside the frustum
        D3DXVECTOR3 eyepos(viewsphere.x, viewsphere.y, viewsphere.z);

        for (const QuadTreeMesh* mesh : meshes) {
            if (!mesh->enabled) {
                continue;
            }

            if (inside == false) {
                ViewFrustum::Containment res = frustum.ContainsSphere(mesh->sphere);
                if (res == ViewFrustum::OUTSIDE) {
                    continue;
                }
                if (res == ViewFrustum::INTERSECTS) {
                    // The sphere intersects one of the edges of the screen, so try the box test
                    if (frustum.ContainsBox(mesh->box) == ViewFrustum::OUTSIDE) {
                        continue;
                    }
                }
            }

            // Avoid camera rotation dependent clipping by using a spherical far clip plane
            // Test mesh against view sphere (eyepos.xyz, radius)
            D3DXVECTOR3 d = mesh->sphere.center - eyepos;
            float range_squared = d.x * d.x + d.y * d.y + d.z * d.z;
            float view_limit = viewsphere.w + mesh->sphere.radius;

            if (range_squared <= view_limit * view_limit) {
                visible_set.PushBack(*mesh);
            }
        }
    }

    template<class T>
    void GetVisibleMeshesCoarse(const ViewFrustum& frustum, VisibleSet<T>& visible_set, bool inside = false) {
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
        if (meshes.empty()) {
            return;
        }

        // If this node has any meshes, check each of their visibility and add them to the list if they're not completely outside the frustum
        for (const QuadTreeMesh* mesh : meshes) {
            if (!mesh->enabled) {
                continue;
            }

            // Only test bounding sphere
            if (inside == false && frustum.ContainsSphere(mesh->sphere) == ViewFrustum::OUTSIDE) {
                continue;
            }

            visible_set.PushBack(*mesh);
        }
    }

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
    QuadTreeMesh* AddMesh(
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
    );

    bool Optimize();
    void Clear();
    template<class T>
    void GetVisibleMeshes(const ViewFrustum& frustum, const D3DXVECTOR4& viewsphere, VisibleSet<T>& visible_set) {
        m_root_node->GetVisibleMeshes(frustum, viewsphere, visible_set);
    }
    template<class T>
    void GetVisibleMeshesCoarse(const ViewFrustum& frustum, VisibleSet<T>& visible_set) {
        m_root_node->GetVisibleMeshesCoarse(frustum, visible_set);
    }
    void SetBox(float size, const D3DXVECTOR2& center);
    void CalcVolume();

    QuadTreeNode* m_root_node;
    MemoryPool m_node_pool;
    MemoryPool m_mesh_pool;

protected:
    friend struct QuadTreeNode;

    QuadTreeNode* CreateNode();
    QuadTreeMesh* CreateMesh(
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
    );
private:
    // Disallow copy and assignment
    QuadTree& operator=(QuadTree&);
    QuadTree(QuadTree&);
};
