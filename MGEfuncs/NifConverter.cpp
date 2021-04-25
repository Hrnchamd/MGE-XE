#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../3rdparty/niflib/include/niflib.h"
#include "../3rdparty/niflib/include/obj/NiObject.h"
#include "../3rdparty/niflib/include/obj/NiAVObject.h"
#include "../3rdparty/niflib/include/obj/NiNode.h"
#include "../3rdparty/niflib/include/obj/NiSwitchNode.h"
#include "../3rdparty/niflib/include/obj/NiProperty.h"
#include "../3rdparty/niflib/include/obj/NiMaterialProperty.h"
#include "../3rdparty/niflib/include/obj/NiTexturingProperty.h"
#include "../3rdparty/niflib/include/obj/NiSourceTexture.h"
#include "../3rdparty/niflib/include/obj/NiTriBasedGeom.h"
#include "../3rdparty/niflib/include/obj/NiTriBasedGeomData.h"
#include "../3rdparty/niflib/include/obj/NiBinaryExtraData.h"
#include "../3rdparty/niflib/include/obj/NiTriStripsData.h"
#include "../3rdparty/niflib/include/obj/RootCollisionNode.h"

#include <assert.h>
#include <fstream>
#include <strstream>
#include <vector>
#include <float.h>
#include <map>
#include <memory>

#include <d3d9.h>
#include <d3dx9.h>
#include "DXVertex.h"

#include "progmesh/ProgMesh.h"

// Vertex Cache Optimizer
#include "../3rdparty/tootle/src/TootleLib/include/tootlelib.h"

using namespace Niflib;
using std::vector;


static IDirect3DDevice9* device;
static HANDLE staticFile;

// Functions from OpenEXR to convert a float to a half float
static inline unsigned short FloatToHalfI(unsigned int i) {
    register int s =  (i >> 16) & 0x00008000;
    register int e = ((i >> 23) & 0x000000ff) - (127 - 15);
    register int m =   i        & 0x007fffff;

    if (e <= 0) {
        if (e < -10) {
            return 0;
        }
        m = (m | 0x00800000) >> (1 - e);

        return s | (m >> 13);
    } else if (e == 0xff - (127 - 15)) {
        if (m == 0) { // Inf
            return s | 0x7c00;
        } else { // NAN
            m >>= 13;
            return s | 0x7c00 | m | (m == 0);
        }
    } else {
        if (e > 30) { // Overflow
            return s | 0x7c00;
        }

        return s | (e << 10) | (m >> 13);
    }
}

static inline unsigned short FloatToHalf(float i) {
    union {
        float f;
        unsigned int i;
    } v;
    v.f = i;
    return FloatToHalfI(v.i);
}

struct DXMatrix {
    float data[4*4];
};

struct ExportedNode {
    Vector3 center;
    float radius;
    Vector3 max;
    Vector3 min;
    int verts;
    int faces;
    std::unique_ptr<DXVertex[]> vBuffer;
    std::unique_ptr<unsigned short[]> iBuffer;
    string tex;
    float emissive;

    ExportedNode() {
        center.Set(0.0f, 0.0f, 0.0f);
        radius = 0;
        verts = 0;
        faces = 0;
        emissive = 0.0f;
    }

    ExportedNode(const ExportedNode& src) {
        center.Set(0.0f, 0.0f, 0.0f);
        radius = 0;
        verts = 0;
        faces = 0;
        emissive = 0.0f;

        *this = src;
    }

    ExportedNode& operator=(const ExportedNode& src) {
        vBuffer.reset();
        iBuffer.reset();

        verts = src.verts;
        faces = src.faces;
        tex = src.tex;
        emissive = src.emissive;

        if (verts) {
            vBuffer = std::make_unique<DXVertex[]>(verts);
            memcpy(vBuffer.get(), src.vBuffer.get(), verts * sizeof(DXVertex));
        }

        if (faces) {
            iBuffer = std::make_unique<unsigned short[]>(faces * 3);
            memcpy(iBuffer.get(), src.iBuffer.get(), faces * 3 * sizeof(unsigned short));
        }

        return *this;
    }

    void CalcBounds() {
        // If the node has no vertices, give it default bounds
        if (verts == 0) {
            center.x = 0.0f;
            center.y = 0.0f;
            center.z = 0.0f;
            radius = 0.0f;
            return;
        }

        max = Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        min = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

        for (int v = 0; v < verts; ++v) {
            float x = vBuffer[v].Position.x;
            float y = vBuffer[v].Position.y;
            float z = vBuffer[v].Position.z;

            if (x > max.x) { max.x = x; }
            if (y > max.y) { max.y = y; }
            if (z > max.z) { max.z = z; }

            if (x < min.x) { min.x = x; }
            if (y < min.y) { min.y = y; }
            if (z < min.z) { min.z = z; }
        }

        // Store center of this node
        center = (min + max) / 2;

        // Find the furthest point from the center to get the radius
        float radius_squared = 0.0f;
        for (int v = 0; v < verts; ++v) {
            float x = vBuffer[v].Position.x;
            float y = vBuffer[v].Position.y;
            float z = vBuffer[v].Position.z;

            float dist_squared = (x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) + (z-center.z)*(z-center.z);

            if (dist_squared > radius_squared) {
                radius_squared = dist_squared;
            }

        }

        // Store local radius of this node
        radius = sqrt(radius_squared);
    }

    void Optimize(unsigned int cache_size, float simplify, bool old) {
        const unsigned int stride = 36;

        // Reduce vertex count by scaling factor simplify
        if (simplify < 1 && faces > 8) {
            ProgMesh pmesh(verts, faces, vBuffer.get(), iBuffer.get());
            pmesh.ComputeProgressiveMesh();

            DXVertex* newVerts;
            WORD* newFaces;

            if (pmesh.DoProgressiveMesh(simplify, (DWORD*)&verts, (DWORD*)&faces, &newVerts, &newFaces) > 0) {
                vBuffer.reset(newVerts);
                iBuffer.reset(newFaces);

                /*char buf[260];
                sprintf(buf, "Mesh simplified from %d to %d", debugVerts, verts);
                OutputDebugStringA(buf);*/
            }
        }

        // Create temporary 32-bit index buffer
        size_t iBufferSize = faces * 3;
        vector<unsigned int> iBuffer32(iBufferSize);
        for (size_t j = 0; j < iBufferSize; ++j) {
            iBuffer32[j] = iBuffer[j];
        }

        TootleResult result = TootleOptimizeVCache(&*iBuffer32.begin(), faces, verts, cache_size, &*iBuffer32.begin(), NULL, TOOTLE_VCACHE_AUTO);

        if (result != TOOTLE_OK) {
            // log_file << "TootleOptimizeVCache returned an error" << endl;
            return;
        }

        result = TootleOptimizeVertexMemory(vBuffer.get(), &*iBuffer32.begin(), verts, faces, stride, vBuffer.get(), &*iBuffer32.begin(), NULL);

        if (result != TOOTLE_OK) {
            // log_file << "TootleOptimizeVertexMemory returned an error" << endl;
            return;
        }

        // Copy 32-bit index buffer back into 16-bit indices
        for (size_t j = 0; j < iBufferSize; ++j) {
            iBuffer[j] = (unsigned short)iBuffer32[j];
        }
    }


    void Save(HANDLE& file) {
        DWORD unused;
        short slen = (short)tex.size() + 1;

        // Write radius and center
        WriteFile(file, &radius, 4, &unused, 0);

        WriteFile(file, &center.x, 4, &unused, 0);
        WriteFile(file, &center.y, 4, &unused, 0);
        WriteFile(file, &center.z, 4, &unused, 0);

        // Write min and max (bounding box)
        WriteFile(file, &min.x, 4, &unused, 0);
        WriteFile(file, &min.y, 4, &unused, 0);
        WriteFile(file, &min.z, 4, &unused, 0);

        WriteFile(file, &max.x, 4, &unused, 0);
        WriteFile(file, &max.y, 4, &unused, 0);
        WriteFile(file, &max.z, 4, &unused, 0);

        // Write vert and face counts
        WriteFile(file, &verts, 4, &unused, 0);
        WriteFile(file, &faces, 4, &unused, 0);

        // Compress vertex buffer
        vector<DXCompressedVertex> compVBuf(verts);

        for (int i = 0; i < verts; ++i) {
            DXCompressedVertex& cv = compVBuf[i];
            DXVertex& v = vBuffer[i];

            // Copy uncompressed values
            cv.Diffuse[0] = v.Diffuse[0];
            cv.Diffuse[1] = v.Diffuse[1];
            cv.Diffuse[2] = v.Diffuse[2];
            cv.Diffuse[3] = v.Diffuse[3];

            // Compress position
            cv.Position[0] = FloatToHalf(v.Position.x);
            cv.Position[1] = FloatToHalf(v.Position.y);
            cv.Position[2] = FloatToHalf(v.Position.z);
            cv.Position[3] = FloatToHalf(1.0f);

            // Compress Texcoords
            cv.texCoord[0] = FloatToHalf(v.texCoord.u);
            cv.texCoord[1] = FloatToHalf(v.texCoord.v);

            // Compress normals
            cv.Normal[0] = (unsigned char)(255.0f * (v.Normal.x * 0.5 + 0.5));
            cv.Normal[1] = (unsigned char)(255.0f * (v.Normal.y * 0.5 + 0.5));
            cv.Normal[2] = (unsigned char)(255.0f * (v.Normal.z * 0.5 + 0.5));
            cv.Normal[3] = (unsigned char)(255.0f * emissive);
        }

        // Write vertex and index buffers
        WriteFile(file, &*compVBuf.begin(), verts * sizeof(DXCompressedVertex), &unused, 0);
        WriteFile(file, iBuffer.get(), faces * 3 * sizeof(unsigned short), &unused, 0);

        // Write texture name
        WriteFile(file, &slen, 2, &unused, 0);
        WriteFile(file, tex.c_str(), slen, &unused, 0);
    }
};

enum StaticType {
    STATIC_AUTO = 0,
    STATIC_NEAR = 1,
    STATIC_FAR = 2,
    STATIC_VERY_FAR = 3,
    STATIC_GRASS = 4,
    STATIC_TREE = 5,
    STATIC_BUILDING = 6
};

class ExportedNif {
public:
    Vector3 center;
    float radius;
    unsigned char static_type;
    vector<ExportedNode> nodes;

    void CalcBounds() {
        // Calculate the total bounds of all nodes
        Vector3 max = Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        Vector3 min = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

        // Find minimum and maximum x, y, and z positions
        for (size_t n = 0; n < nodes.size(); ++n) {
            // If the node has no vertices, give it default bounds
            if (nodes[n].verts == 0) {
                nodes[n].center.x = 0.0f;
                nodes[n].center.y = 0.0f;
                nodes[n].center.z = 0.0f;
                nodes[n].radius = 0.0f;
                continue;
            }

            for (int v = 0; v < nodes[n].verts; ++v) {
                float x, y, z;
                x = nodes[n].vBuffer[v].Position.x;
                y = nodes[n].vBuffer[v].Position.y;
                z = nodes[n].vBuffer[v].Position.z;

                if (x > max.x) { max.x = x; }
                if (y > max.y) { max.y = y; }
                if (z > max.z) { max.z = z; }

                if (x < min.x) { min.x = x; }
                if (y < min.y) { min.y = y; }
                if (z < min.z) { min.z = z; }
            }
        }

        // Average min/max positions to get center
        center = (min + max) / 2;

        // Find the furthest point from the center to get the radius
        float radius_squared = 0.0f;
        for (size_t n = 0; n < nodes.size(); ++n) {
            for (int v = 0; v < nodes[n].verts; ++v) {
                float x = nodes[n].vBuffer[v].Position.x;
                float y = nodes[n].vBuffer[v].Position.y;
                float z = nodes[n].vBuffer[v].Position.z;

                float dist_squared = (x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) + (z-center.z)*(z-center.z);

                if (dist_squared > radius_squared) {
                    radius_squared = dist_squared;
                }
            }
        }

        radius = sqrt(radius_squared);
    }

    void CalcNodeBounds() {
        for (size_t i = 0; i < nodes.size(); ++i) {
            nodes[i].CalcBounds();
        }
    }

private:

    bool MergeShape(ExportedNode* dst, ExportedNode* src) {
        // Sum vert and face counts
        int verts = src->verts + dst->verts;
        int faces = src->faces + dst->faces;

        // Create new buffers large enough to hold all vertices from original ones
        auto v_buf = std::make_unique<DXVertex[]>(verts);
        auto i_buf = std::make_unique<unsigned short[]>(faces*3);

        // Copy data from previous buffers into new ones
        memcpy(v_buf.get(), dst->vBuffer.get(), dst->verts * sizeof(DXVertex));
        memcpy(v_buf.get() + dst->verts, src->vBuffer.get(), src->verts * sizeof(DXVertex));

        memcpy(i_buf.get(), dst->iBuffer.get(), dst->faces * 3 * sizeof(unsigned short));
        memcpy(i_buf.get() + dst->faces * 3, src->iBuffer.get(), src->faces * 3 * sizeof(unsigned short));

        // Account for the offset in the indices copied from src
        for (int i = dst->faces * 3; i < faces * 3; ++i) {
            i_buf[i] += dst->verts;
        }

        // Set new values in dst
        dst->vBuffer.swap(v_buf);
        dst->iBuffer.swap(i_buf);
        dst->verts = verts;
        dst->faces = faces;

        return true;
    }

    void SearchShapes(NiAVObjectRef rootObj, vector<NiTriBasedGeomRef>* SubsetNodes) {
        // Check if this object is derived from NiTriBasedGeom
        NiTriBasedGeomRef niGeom = DynamicCast<NiTriBasedGeom>(rootObj);
        if (niGeom) {
            SubsetNodes->push_back(niGeom);
        } else {
            // Check if this object derives from NiNode and, thus, may have children
            // Follow switch index for NiSwitchNodes, ignore RootCollisionNodes
            NiNodeRef niNode = DynamicCast<NiNode>(rootObj);
            NiSwitchNodeRef niSwitch = DynamicCast<NiSwitchNode>(rootObj);
            RootCollisionNodeRef collision = DynamicCast<RootCollisionNode>(rootObj);
            if (niSwitch) {
                // Search just the selected child
                SearchShapes(niSwitch->GetActiveChild(), SubsetNodes);
            } else if (niNode && !collision) {
                // Call this function for any children
                vector<NiAVObjectRef> children = niNode->GetChildren();
                for (size_t i = 0; i < children.size(); i++) {
                    SearchShapes(children[i], SubsetNodes);
                }
            }
        }
    }

    bool ExportShape(NiTriBasedGeomRef niGeom, ExportedNode* node) {
        // Check that an external texture exists
        NiTexturingPropertyRef niTexProp = DynamicCast<NiTexturingProperty>(niGeom->GetPropertyByType(NiTexturingProperty::TYPE));
        if (!niTexProp || niTexProp->GetTextureCount() == 0) {
            // log_file << "External texture does not exist" << endl;
            return false;
        }
        TexDesc texDesc = niTexProp->GetTexture(0);
        NiSourceTextureRef niSrcTex = texDesc.source;
        if (!niSrcTex || !niSrcTex->IsTextureExternal()) {
            // log_file << "Texture was not external" << endl;
            return false;
        }

        // Get data object (NiTriBasedGeomData) from geometry node (NiTriBasedGeom)
        NiTriBasedGeomDataRef niGeomData = DynamicCast<NiTriBasedGeomData>(niGeom->GetData());
        if (!niGeomData) {
            // log_file << "There is no Geometry data on this mesh." << endl;
            return false;
        }

        // Get material object (NiMaterialProperty) from geometry node (NiTriBasedGeom)
        NiMaterialPropertyRef niMatProp = DynamicCast<NiMaterialProperty>(niGeom->GetPropertyByType(NiMaterialProperty::TYPE));

        // Get Diffuse color (will be baked into vertices
        Color3 diffuse(1.0f, 1.0f, 1.0f);
        if (niMatProp) {
            diffuse = niMatProp->GetDiffuseColor();
        }
        // Get the emissive color (will be averaged and stored in alpha chanel of vertices)
        Color3 emissive(0.0f, 0.0f, 0.0f);
        if (niMatProp) {
            emissive = niMatProp->GetEmissiveColor();
        }
        node->emissive = (emissive.r + emissive.b + emissive.g) / 3.0f;

        // Get the alpha of the material
        float Alpha = 1.0f;
        if (niMatProp) {
            Alpha = niMatProp->GetTransparency();
        }

        // Check that there is at least one set of texture coords available
        if (niGeomData->GetUVSetCount() == 0) {
            // log_file << "There are no texture coordinates on this mesh." << endl;
            return false;
        }

        // ProgMesh simplify = ProgMesh(niGeomData);
        // simplify.ComputeProgressiveMesh();
        // simplify.DoProgressiveMesh(0.1);

        // Indicies
        vector<Triangle> tris = niGeomData->GetTriangles();
        node->faces = tris.size();
        if (node->faces == 0) {
            // log_file << "This mesh has no triangles." << endl;
            return false;
        }

        // Now that we're sure this mesh is valid, start the conversion

        // Get transformation of mesh as 4x4 matrix
        Matrix44 transform = niGeom->GetWorldTransform();

        // Get a matrix that only contains the world rotation matrix
        // This will be used to transform normals
        Matrix44 rotation(transform.GetRotation());

        node->iBuffer = std::make_unique<unsigned short[]>(node->faces*3);
        for (int i = 0; i < node->faces; i++) {
            node->iBuffer[i*3+0] = tris[i].v1;
            node->iBuffer[i*3+1] = tris[i].v2;
            node->iBuffer[i*3+2] = tris[i].v3;
        }

        // Vertex data
        vector<Vector3> positions;
        vector<Vector3> normals;
        if (niGeom->IsSkin()) {
            niGeom->GetSkinDeformation(positions, normals);
        } else {
            positions = niGeomData->GetVertices();
            normals = niGeomData->GetNormals();
        }
        vector<Color4> colors = niGeomData->GetColors();
        vector<TexCoord> texCoords = niGeomData->GetUVSet(0);

        // Vertices
        node->verts = niGeomData->GetVertexCount();

        node->vBuffer = std::make_unique<DXVertex[]>(node->verts);
        for (int i = 0; i < node->verts; i++) {
            // Push the world transform into the verticies
            positions[i] = transform * positions[i];

            // Apply the world transform's rotation to the normals
            normals[i] = rotation * normals[i];

            node->vBuffer[i].Position = positions[i];
            if (normals.size()>0) {
                node->vBuffer[i].Normal = normals[i];
            } else {
                node->vBuffer[i].Normal.x = 0;
                node->vBuffer[i].Normal.y = 0;
                node->vBuffer[i].Normal.z = 1;
            }
            if (colors.size()>0) {
                node->vBuffer[i].Diffuse[0] = (unsigned char)(255.0f * colors[i].b * diffuse.b);
                node->vBuffer[i].Diffuse[1] = (unsigned char)(255.0f * colors[i].g * diffuse.g);
                node->vBuffer[i].Diffuse[2] = (unsigned char)(255.0f * colors[i].r * diffuse.r);
                node->vBuffer[i].Diffuse[3] = (unsigned char)(255.0f * colors[i].a * Alpha);
            } else {
                node->vBuffer[i].Diffuse[0] = (unsigned char)(255.0f * diffuse.b);
                node->vBuffer[i].Diffuse[1] = (unsigned char)(255.0f * diffuse.g);
                node->vBuffer[i].Diffuse[2] = (unsigned char)(255.0f * diffuse.r);
                node->vBuffer[i].Diffuse[3] = (unsigned char)(255.0f * Alpha);
            }

            node->vBuffer[i].texCoord = texCoords[i];
        }

        // Get texture file path
        string s = niSrcTex->GetTextureFileName();

        // Make texture path all lowercase
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] >= 65 && s[i] <= 90) {
                s[i] += 32;
            }
        }

        // If the path starts with "textures" or "\textures" remove it
        size_t pos = s.find("textures");
        if (pos <= 1) {
            s = s.substr(pos + 8, string::npos);
        }

        // Remove any leading forward slashes that remain
        if (s[0] == '\\') {
            s = s.substr(1, string::npos );
        }

        node->tex = s;

        return true;
    }


public:

    void Optimize(unsigned int cache_size, float simplify, bool old) {
        // Try to combine nodes that have the same texture path
        map<string, ExportedNode*> node_tex;

        for (size_t i = 0; i < nodes.size(); ++i) {
            // Check if this node has already been found
            map<string, ExportedNode*>::iterator it = node_tex.find(nodes[i].tex);

            if (it == node_tex.end()) {
                // Nothing with this texture has been found yet.  Store the node's pointer in the map
                node_tex[ nodes[i].tex ] = &nodes[i];
            } else {
                // A shape with this texture has been found already.  Merge this one into it.
                MergeShape(it->second, &nodes[i]);
            }
        }

        size_t count = 0;
        if (node_tex.size() < nodes.size() && node_tex.size() != 0) {
            // We reduced the number of nodes, so create a new list to save
            vector<ExportedNode> merged_nodes(node_tex.size());

            for (map<string, ExportedNode*>::iterator it = node_tex.begin(); it != node_tex.end(); ++it) {
                merged_nodes[count] = *(it->second);
                ++count;
            }

            nodes = merged_nodes;
        }


        // Now optimize each node
        for (size_t i = 0; i < nodes.size(); ++i) {
            nodes[i].Optimize(cache_size, simplify, old);
        }
    }

    bool LoadNifFromStream(const char* data, int size) {
        istrstream s(data, size);
        NiAVObjectRef rootObj;

        try {
            rootObj = DynamicCast<NiAVObject>(ReadNifTree(s, 0));
        } catch (std::runtime_error& e) {
            std::fstream error_log("mge3\\distant-land-niflib-error.log", std::ios_base::out | std::ios_base::app);
            error_log << e.what() << std::endl;
            return false;
        }

        if (!rootObj) {
            // log_file << "Root object was null." << endl;
            return false;
        }

        // Object root transform should not affect results
        rootObj->SetLocalTransform(Matrix44::IDENTITY);

        vector<NiTriBasedGeomRef> SubsetNodes;
        SearchShapes(rootObj, &SubsetNodes);

        if (SubsetNodes.size() == 0) {
            // log_file << "SubsetNodes size is zero." << endl;
            return false;
        }

        for (size_t i = 0; i < SubsetNodes.size(); ++i) {
            ExportedNode tmp_node;
            if (ExportShape(SubsetNodes[i], &tmp_node)) {
                nodes.push_back(tmp_node);
            }
        }

        if (nodes.size() == 0) {
            // log_file << "nodes size is zero." << endl;
            return false;
        }

        // Success
        return true;
    }

    bool Save() {
        // HANDLE h = CreateFileA(outpath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
        HANDLE h = staticFile;

        DWORD unused;
        if (h == INVALID_HANDLE_VALUE) {
            // log_file << "File handle is invalid." << endl;
            return false;
        }
        int nodeCount = (int)nodes.size();
        SetFilePointer(h, 0, NULL, FILE_END);

        WriteFile(h, &nodeCount, 4, &unused, 0);
        WriteFile(h, &radius, 4, &unused, 0);
        WriteFile(h, &center.x, 4, &unused, 0 );
        WriteFile(h, &center.y, 4, &unused, 0 );
        WriteFile(h, &center.z, 4, &unused, 0 );
        WriteFile(h, &static_type, 1, &unused, 0);

        for (size_t i = 0; i < nodes.size(); i++) {
            nodes[i].Save(h);
        }

        return true;
    }
};



extern "C" int __stdcall GetVertSize() {
    return (int)sizeof(DXVertex);
}

extern "C" int __stdcall GetCompressedVertSize() {
    return (int)sizeof(DXCompressedVertex);
}

extern "C" int __stdcall GetLandVertSize() {
    return (int)sizeof(DXCompressedLandVertex);
}

extern "C" float __stdcall ProcessNif(char* data, int datasize, float simplify, float cutoff, BYTE static_type, BYTE old) {

    // Load the NIF data into our DirectX-friendly format
    ExportedNif nif;
    if (! nif.LoadNifFromStream(data, datasize)) {
        // log_file << "LoadNifFromStream failed." << endl;
        return -1;
    }

    // Calculate the bounds of the NIF to determine whether it exceeds our cutoff value
    nif.CalcBounds();

    if (static_type == STATIC_AUTO && nif.radius < cutoff) {
        // log_file << "Radius was below cutoff value." << endl;
        return -2;
    }

    // Buildings are treated as if they are twice their actual size.
    if (static_type == STATIC_BUILDING && nif.radius * 2.0f < cutoff) {
        // log_file << "Radius was below cutoff value." << endl;
        return -2;
    }

    if (!staticFile) {
        return nif.radius;
    }

    // Optimize NIF and calculate node bounds

    nif.Optimize(16, simplify, old != 0);
    nif.CalcNodeBounds();

    // Determine whether this will be a near or far distant static based on size
    nif.static_type = static_type;

    // Save NIF to new format
    if (!nif.Save()) {
        // log_file << "NIF Save failed." << endl;
        return -3;
    }

    return nif.radius;
}

extern "C" void __stdcall BeginStaticCreation(IDirect3DDevice9* _device, char* outpath) {
    device = _device;
    if (outpath) {
        staticFile = CreateFileA(outpath, FILE_GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
    } else {
        staticFile = 0;
    }
}

extern "C" void __stdcall EndStaticCreation() {
    CloseHandle(staticFile);
}
