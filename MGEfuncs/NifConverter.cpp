#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "niflib.h"
#include "obj/NiObject.h"
#include "obj/NiAVObject.h"
#include "obj/NiNode.h"
#include "obj/NiProperty.h"
#include "obj/NiMaterialProperty.h"
#include "obj/NiTexturingProperty.h"
#include "obj/NiSourceTexture.h"
#include "obj/NiTriBasedGeom.h"
#include "obj/NiTriBasedGeomData.h"
#include "obj/NiBinaryExtraData.h"
#include "obj/NiTriStripsData.h"

#include <assert.h>
#include <fstream>
#include <strstream>
#include <vector>
#include <float.h>
#include <map>

#include <d3d9.h>
#include <d3dx9.h>
#include "DXVertex.h"

#include "progmesh/ProgMesh.h"

//Vertex Cache Optimizer
#include <tootlelib.h>

//ofstream log_file( "C:\\mge_convert_log.txt" );

using namespace Niflib;

#define SAFERELEASEP(a) { if(a) { delete[] a; } a=0; }

static IDirect3DDevice9* device;
static HANDLE staticFile;

//Functions from OpenEXR to convert a float to a half float
static inline unsigned short FloatToHalfI(unsigned int i)
{
    register int s =  (i >> 16) & 0x00008000;
    register int e = ((i >> 23) & 0x000000ff) - (127 - 15);
    register int m =   i        & 0x007fffff;

    if (e <= 0)
    {
        if (e < -10)
        {
            return 0;
        }
        m = (m | 0x00800000) >> (1 - e);

        return s | (m >> 13);
    }
    else if (e == 0xff - (127 - 15))
    {
        if (m == 0) // Inf
        {
            return s | 0x7c00;
        }
        else    // NAN
        {
            m >>= 13;
            return s | 0x7c00 | m | (m == 0);
        }
    }
    else
    {
        if (e > 30) // Overflow
        {
            return s | 0x7c00;
        }

        return s | (e << 10) | (m >> 13);
    }
}

static inline unsigned short FloatToHalf(float i)
{
    union { float f; unsigned int i; } v;
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
    DXVertex* vBuffer;
    unsigned short* iBuffer;
    string tex;
    float emissive;

    ExportedNode() {
        center.Set(0.0f, 0.0f, 0.0f);
        radius = 0;
        verts = 0;
        faces = 0;
        vBuffer = 0;
        iBuffer = 0;
        emissive = 0.0f;
    }

    ExportedNode( const ExportedNode & src ) {
        center.Set(0.0f, 0.0f, 0.0f);
        radius = 0;
        verts = 0;
        faces = 0;
        vBuffer = 0;
        iBuffer = 0;
        emissive = 0.0f;

        *this = src;
    }

    ExportedNode & operator=(const ExportedNode & src) {
        SAFERELEASEP(vBuffer);
        SAFERELEASEP(iBuffer);

        verts = src.verts;
        faces = src.faces;
        tex = src.tex;
        emissive = src.emissive;

        if ( verts ) {
            vBuffer = new DXVertex[verts];
            memcpy( vBuffer, src.vBuffer, verts * sizeof(DXVertex) );
        }

        if ( faces ) {
            iBuffer = new unsigned short[faces * 3];
            memcpy( iBuffer, src.iBuffer, faces * 6 );
        }

        return *this;
    }

    void CalcBounds() {
        //If the node has no vertices, give it default bounds
        if ( verts == 0 ) {
            center.x = 0.0f;
            center.y = 0.0f;
            center.z = 0.0f;
            radius = 0.0f;
            return;
        }

        max = Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        min = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

        for ( int v = 0; v < verts; ++v ) {
            float x = vBuffer[v].Position.x;
            float y = vBuffer[v].Position.y;
            float z = vBuffer[v].Position.z;

            if ( x > max.x ) { max.x = x; }
            if ( y > max.y ) { max.y = y; }
            if ( z > max.z ) { max.z = z; }

            if ( x < min.x ) { min.x = x; }
            if ( y < min.y ) { min.y = y; }
            if ( z < min.z ) { min.z = z; }
        }

        //Store center of this node
        center = (min + max) / 2;

        //Find the furthest point from the center to get the radius
        float radius_squared = 0.0f;
        for ( int v = 0; v < verts; ++v ) {
            float x = vBuffer[v].Position.x;
            float y = vBuffer[v].Position.y;
            float z = vBuffer[v].Position.z;

            float dist_squared = (x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) + (z-center.z)*(z-center.z);

            if ( dist_squared > radius_squared ) {
                radius_squared = dist_squared;
            }

        }

        //Store local radius of this node
        radius = sqrt(radius_squared);
    }

    /*int CanRemoveTriangle(WORD i, WORD a, WORD b, int* adj, Vector3* norm) {
        int j=-1;
        if(adj[a*3+0]!=i&&adj[a*3+0]!=-1&&(adj[a*3+0]==adj[b*3+0]||adj[a*3+0]==adj[b*3+1]||adj[a*3+0]==adj[b*3+2])) j = adj[a*3+0];
        if(adj[a*3+1]!=i&&adj[a*3+1]!=-1&&(adj[a*3+1]==adj[b*3+0]||adj[a*3+1]==adj[b*3+1]||adj[a*3+1]==adj[b*3+2])) j = adj[a*3+1];
        if(adj[a*3+2]!=i&&adj[a*3+2]!=-1&&(adj[a*3+2]==adj[b*3+0]||adj[a*3+2]==adj[b*3+1]||adj[a*3+2]==adj[b*3+2])) j = adj[a*3+2];
        if(j==-1) return -1;
        if(norm[i].DotProduct(norm[a])>0.1f||norm[i].DotProduct(norm[b])>0.1f||norm[i].DotProduct(norm[j])>0.1f) return -1;
        return j;
    }
    bool MergeTriangles(WORD a, WORD b, int vert) {

    }
    bool ContaintsVert(WORD face, int vert) {
        return iBuffer[face*3+0]==vert || iBuffer[face*3+1]==vert || iBuffer[face*3+2]==vert;
    }
    bool RemoveTriangle(WORD a, WORD b, WORD c, WORD d) {
        int removedVertex=-1, sharedVertex=-1;
        for(int i=0;i<3;i++) {
            if(ContaintsVert(b, iBuffer[a*3+i])&&ContaintsVert(b, iBuffer[a*3+i])&&ContaintsVert(b, iBuffer[a*3+i])) {
                removedVertex=iBuffer[a*3+i];
                break;
            }
        }
        if(removedVertex==-1) return false;
        return MergeTriangles(a,b,removedVertex) || MergeTriangles(c,d,removedVertex);
        return true;
    }
    void ShrinkMesh() {
        ID3DXMesh *mesh;
            int *adj=new int[faces*3];
            Vector3 *norm=new Vector3[faces];
            void* data;

            D3DXCreateMeshFVF(faces, verts, D3DXMESH_SYSTEMMEM, D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1, device, &mesh);
            mesh->LockVertexBuffer(0,&data);
            memcpy(data, vBuffer, verts*stride);
            mesh->UnlockVertexBuffer();
            mesh->LockIndexBuffer(0,&data);
            memcpy(data, iBuffer, faces*6);
            mesh->UnlockIndexBuffer();

            mesh->GenerateAdjacency(0.0f, (DWORD*)adj);
            Triangle* tris=(Triangle*)iBuffer;

            bool removed;
            int removedCount=0;
            //Repeat until no more triangles can be removed
            do {
                removed=false;
                //Generate normals
                for(int i=0;i<faces;i++) {
                    Vector3 v0 = vBuffer[tris[i][0]].Position;
                    Vector3 v1 = vBuffer[tris[i][1]].Position;
                    Vector3 v2 = vBuffer[tris[i][2]].Position;

                    Vector3 a = v1 - v0;
                    Vector3 b = v2 - v0;

                    norm[i]=a.CrossProduct(b).Normalized();
                }
                //Loop through and remove faces
                for(int i=0;i<faces;i++) {
                    int j;
                    if(adj[i*3+0]!=-1&&adj[i+3+1]!=-1&&((j=CanRemoveTriangle(i, adj[i*3+0], adj[i+3+1], adj, norm))!=-1)) {
                        RemoveTriangle(i, adj[i*3+0], j, adj[i*3+1], adj, norm);
                        removed=true;
                        removedCount++;
                    } else if(adj[i*3+0]!=-1&&adj[i+3+2]!=-1&&((j=CanRemoveTriangle(i, adj[i*3+0], adj[i+3+2], adj, norm))!=-1))) {
                        RemoveTriangle(i, adj[i*3+0], j, adj[i*3+2], adj, norm);
                        removed=true;
                        removedCount++;
                    } else if(adj[i*3+1]!=-1&&adj[i+3+2]!=-1&&((j=CanRemoveTriangle(i, adj[i*3+1], adj[i+3+2], adj, norm))!=-1))) {
                        RemoveTriangle(i, adj[i*3+1], j, adj[i*3+2], adj, norm);
                        removed=true;
                        removedCount++;
                    }
                }
            } while(removed);

            //Now remove any unreferences verticies
    }*/
    void Optimize( unsigned int cache_size, float simplify, bool old ) {
        const unsigned int stride = 36;

        if(simplify<1&&faces>8) {

            //ShrinkMesh();

            if(!old) {

                ProgMesh pmesh(verts, faces, vBuffer, iBuffer);
                pmesh.ComputeProgressiveMesh();

                DXVertex* newVerts;
                WORD* newFaces;

                if(stride!=sizeof(DXVertex)) {
                    int iii=sizeof(DXVertex);
                }

                int debugVerts=verts;
                if(pmesh.DoProgressiveMesh(simplify, (DWORD*)&verts, (DWORD*)&faces, &newVerts, &newFaces)>0) {
                    delete[] iBuffer;
                    delete[] vBuffer;
                    iBuffer=newFaces;
                    vBuffer=newVerts;

                    /*char buf[260];
                    sprintf(buf, "Mesh simplified from %d to %d", debugVerts, verts);
                    OutputDebugStringA(buf);*/
                }

            } else {

                ID3DXMesh *mesh, *nmesh;
                DWORD *adjacency1=new DWORD[faces*3];
                DWORD *adjacency2=new DWORD[faces*3];
                void* data;

                D3DXATTRIBUTEWEIGHTS weights;
                memset(&weights, 0, sizeof(weights));
                weights.Boundary=2;
                weights.Position=1;
                weights.Normal=1;

                //TODO: Check HRESULT
                D3DXCreateMeshFVF(faces, verts, D3DXMESH_SYSTEMMEM, D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1, device, &mesh);
                mesh->LockVertexBuffer(0,&data);
                memcpy(data, vBuffer, verts*stride);
                mesh->UnlockVertexBuffer();
                mesh->LockIndexBuffer(0,&data);
                memcpy(data, iBuffer, faces*6);
                mesh->UnlockIndexBuffer();

                mesh->GenerateAdjacency(0.0f, adjacency1);

                D3DXCleanMesh(D3DXCLEAN_SIMPLIFICATION, mesh, adjacency1, &nmesh, adjacency2, 0);
                mesh->Release();
                D3DXSimplifyMesh(nmesh, adjacency2, &weights, 0, (int)(faces*simplify), D3DXMESHSIMP_FACE, &mesh);
                nmesh->Release();

                delete [] adjacency1;
                delete [] adjacency2;

                verts=mesh->GetNumVertices();
                faces=mesh->GetNumFaces();

                delete [] vBuffer;
                delete [] iBuffer;

                vBuffer = new DXVertex[verts];
                iBuffer = new unsigned short[faces*3];

                mesh->LockVertexBuffer(D3DLOCK_READONLY,&data);
                memcpy(vBuffer, data, verts*stride);
                mesh->UnlockVertexBuffer();
                mesh->LockIndexBuffer(D3DLOCK_READONLY,&data);
                memcpy(iBuffer, data, faces*6);
                mesh->UnlockIndexBuffer();

                mesh->Release();

            }

        }

        //Create temporary 32-bit index buffer
        unsigned int * iBuffer32 = new unsigned int[faces * 3];
        for ( int j = 0; j < faces * 3; ++j ) {
            iBuffer32[j] = iBuffer[j];
        }


        TootleResult result = TootleOptimizeVCache( iBuffer32, faces, verts, cache_size, iBuffer32, NULL, TOOTLE_VCACHE_AUTO);

        if( result != TOOTLE_OK ) {
            //log_file << "TootleOptimizeVCache returned an error" << endl;
            delete [] iBuffer32;
            return;
        }

        result = TootleOptimizeVertexMemory( vBuffer, iBuffer32, verts, faces, stride, vBuffer, iBuffer32, NULL );

        if( result != TOOTLE_OK ) {
            //log_file << "TootleOptimizeVertexMemory returned an error" << endl;
            delete [] iBuffer32;
            return;
        }

        //Copy 32-bit index buffer back into 16-bit indices
        for ( int j = 0; j < faces * 3; ++j ) {
            iBuffer[j] = (unsigned short)iBuffer32[j];
        }

        //free temporary buffer
        delete [] iBuffer32;
    }


    void Save(HANDLE & file) {
        DWORD unused;
        short slen = (short)tex.size() + 1;

        //Write radius and center
        WriteFile(file, &radius, 4, &unused, 0);

        WriteFile(file, &center.x, 4, &unused, 0);
        WriteFile(file, &center.y, 4, &unused, 0);
        WriteFile(file, &center.z, 4, &unused, 0);

        //Write min and max (bounding box)
        WriteFile(file, &min.x, 4, &unused, 0);
        WriteFile(file, &min.y, 4, &unused, 0);
        WriteFile(file, &min.z, 4, &unused, 0);

        WriteFile(file, &max.x, 4, &unused, 0);
        WriteFile(file, &max.y, 4, &unused, 0);
        WriteFile(file, &max.z, 4, &unused, 0);

        //Write vert and face counts
        WriteFile(file, &verts, 4, &unused, 0);
        WriteFile(file, &faces, 4, &unused, 0);

        //Compress vertex buffer
        DXCompressedVertex * compVBuf = new DXCompressedVertex[verts];
        for ( int i = 0; i < verts; ++i ) {
            DXCompressedVertex & cv = compVBuf[i];
            DXVertex & v = vBuffer[i];

            //Copy uncompressed values
            cv.Diffuse[0] = v.Diffuse[0];
            cv.Diffuse[1] = v.Diffuse[1];
            cv.Diffuse[2] = v.Diffuse[2];
            cv.Diffuse[3] = v.Diffuse[3];

            //Compress position
            cv.Position[0] = FloatToHalf(v.Position.x);
            cv.Position[1] = FloatToHalf(v.Position.y);
            cv.Position[2] = FloatToHalf(v.Position.z);
            cv.Position[3] = FloatToHalf(1.0f);

            //Compress Texcoords
            cv.texCoord[0] = FloatToHalf(v.texCoord.u);
            cv.texCoord[1] = FloatToHalf(v.texCoord.v);

            //Compress normals
            cv.Normal[0] = (unsigned char)( 255.0f * (v.Normal.x * 0.5 + 0.5) );
            cv.Normal[1] = (unsigned char)( 255.0f * (v.Normal.y * 0.5 + 0.5) );
            cv.Normal[2] = (unsigned char)( 255.0f * (v.Normal.z * 0.5 + 0.5) );
            cv.Normal[3] = (unsigned char)( 255.0f * emissive );
        }

        //Write vertex and index buffers
        WriteFile(file, compVBuf, verts*sizeof(DXCompressedVertex), &unused, 0);
        WriteFile(file, iBuffer, faces*6, &unused, 0);

        //Delete compressed vertices
        delete [] compVBuf;

        //Write texture name
        WriteFile(file, &slen, 2, &unused, 0);
        WriteFile(file, tex.c_str(), slen, &unused, 0);
    }

    void Load(HANDLE & file) {
        DWORD unused;

        //Read radius and center
        ReadFile(file, &radius, 4, &unused, 0);

        ReadFile(file, &center.x, 4, &unused, 0);
        ReadFile(file, &center.y, 4, &unused, 0);
        ReadFile(file, &center.z, 4, &unused, 0);

        //Read min and max (bounding box)
        ReadFile(file, &min.x, 4, &unused, 0);
        ReadFile(file, &min.y, 4, &unused, 0);
        ReadFile(file, &min.z, 4, &unused, 0);

        ReadFile(file, &max.x, 4, &unused, 0);
        ReadFile(file, &max.y, 4, &unused, 0);
        ReadFile(file, &max.z, 4, &unused, 0);

        //Read vert and face counts
        ReadFile(file, &verts, 4, &unused, 0);
        ReadFile(file, &faces, 4, &unused, 0);

        //Read vertex and index buffers
        ReadFile(file, vBuffer, verts*sizeof(DXCompressedVertex), &unused, 0);
        ReadFile(file, iBuffer, faces*6, &unused, 0);

        //Read texture name
        short slen;
        ReadFile(file, &slen, 2, &unused, 0);

        char * tmp = new char[slen];
        ReadFile(file, tmp, slen, &unused, 0);
        tex = tmp;
        delete [] tmp;
    }

    ~ExportedNode() {
        SAFERELEASEP(vBuffer);
        SAFERELEASEP(iBuffer);
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
        //Calculate the total bounds of all nodes
        Vector3 max = Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        Vector3 min = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

        //Find minimum and maximum x, y, and z positions
        for ( size_t n = 0; n < nodes.size(); ++n ) {
            //If the node has no vertices, give it default bounds
            if ( nodes[n].verts == 0 ) {
                nodes[n].center.x = 0.0f;
                nodes[n].center.y = 0.0f;
                nodes[n].center.z = 0.0f;
                nodes[n].radius = 0.0f;
                continue;
            }

            for ( int v = 0; v < nodes[n].verts; ++v ) {
                float x, y, z;
                x = nodes[n].vBuffer[v].Position.x;
                y = nodes[n].vBuffer[v].Position.y;
                z = nodes[n].vBuffer[v].Position.z;

                if ( x > max.x ) { max.x = x; }
                if ( y > max.y ) { max.y = y; }
                if ( z > max.z ) { max.z = z; }

                if ( x < min.x ) { min.x = x; }
                if ( y < min.y ) { min.y = y; }
                if ( z < min.z ) { min.z = z; }
            }
        }

        //Average min/max positions to get center
        Vector3 center = (min + max) / 2;

        //Find the furthest point from the center to get the radius
        float radius_squared = 0.0f;
        for ( size_t n = 0; n < nodes.size(); ++n ) {
            for ( int v = 0; v < nodes[n].verts; ++v ) {
                float x = nodes[n].vBuffer[v].Position.x;
                float y = nodes[n].vBuffer[v].Position.y;
                float z = nodes[n].vBuffer[v].Position.z;

                float dist_squared = (x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) + (z-center.z)*(z-center.z);

                if ( dist_squared > radius_squared ) {
                    radius_squared = dist_squared;
                }
            }
        }

        radius = sqrt( radius_squared );
    }

    void CalcNodeBounds() {
        for (size_t i = 0; i < nodes.size(); ++i ) {
            nodes[i].CalcBounds();
        }
    }

private:

    bool MergeShape( ExportedNode* dst, ExportedNode* src ) {
        //Sum vert and face counts
        int verts = src->verts + dst->verts;
        int faces = src->faces + dst->faces;

        //Create new buffers large enough to hold all vertices from original ones
        DXVertex * v_buf = new DXVertex[verts];
        unsigned short * i_buf = new unsigned short[faces*3];

        //Copy data from previous buffers into new ones
        memcpy( v_buf, dst->vBuffer, dst->verts * sizeof(DXVertex) );
        memcpy( v_buf + dst->verts, src->vBuffer, src->verts * sizeof(DXVertex) );

        memcpy( i_buf, dst->iBuffer, dst->faces * 6 );
        memcpy( i_buf + dst->faces * 3, src->iBuffer, src->faces * 6 );

        //Account for the offset in the indices copied from src
        for ( int i = dst->faces * 3; i < faces * 3; ++i ) {
            i_buf[i] += dst->verts;
        }

        //Delete old dst buffers
        delete [] dst->vBuffer;
        delete [] dst->iBuffer;

        //Set new values in dst
        dst->vBuffer = v_buf;
        dst->verts = verts;
        dst->iBuffer = i_buf;
        dst->faces = faces;

        return true;
    }

    void SearchShapes( NiAVObjectRef rootObj, vector<NiTriBasedGeomRef>* SubsetNodes ) {
        //Check if this object is derived from NiTriBasedGeom
        NiTriBasedGeomRef niGeom = DynamicCast<NiTriBasedGeom>( rootObj );
        if(niGeom) {
            SubsetNodes->push_back(niGeom);
        } else {
            //Check if this object derives from NiNode and, thus, may have children
            NiNodeRef niNode = DynamicCast<NiNode>( rootObj );
            if(niNode) {
                //Call this function for any children
                vector<NiAVObjectRef> children = niNode->GetChildren();
                for(unsigned int i = 0; i < children.size(); i++) {
                    SearchShapes( children[i], SubsetNodes );
                }
            }
        }
    }

    bool ExportShape( NiTriBasedGeomRef niGeom, ExportedNode* node ) {
        //Check that an external texture exists
        NiTexturingPropertyRef niTexProp = DynamicCast<NiTexturingProperty>(niGeom->GetPropertyByType( NiTexturingProperty::TYPE ));
        if(!niTexProp||niTexProp->GetTextureCount()==0) {
            //log_file << "External texture does not exist" << endl;
            return false;
        }
        TexDesc texDesc=niTexProp->GetTexture(0);
        NiSourceTextureRef niSrcTex = texDesc.source;
        if(!niSrcTex || !niSrcTex->IsTextureExternal() ) {
            //log_file << "Texture was not external" << endl;
            return false;
        }

        //Get data object (NiTriBasedGeomData) from geometry node (NiTriBasedGeom)
        NiTriBasedGeomDataRef niGeomData = DynamicCast<NiTriBasedGeomData>(niGeom->GetData());
        if(!niGeomData) {
            //log_file << "There is no Geometry data on this mesh." << endl;
            return false;
        }

        //Get material object (NiMaterialProperty) from geometry node (NiTriBasedGeom)
        NiMaterialPropertyRef niMatProp = DynamicCast<NiMaterialProperty>(niGeom->GetPropertyByType( NiMaterialProperty::TYPE ));

        //Get Diffuse color (will be baked into vertices
        Color3 diffuse( 1.0f, 1.0f, 1.0f );
        if ( niMatProp ) {
            diffuse = niMatProp->GetDiffuseColor();
        }
        //Get the emissive color (will be averaged and stored in alpha chanel of vertices)
        Color3 emissive( 0.0f, 0.0f, 0.0f );
        if ( niMatProp ) {
            emissive = niMatProp->GetEmissiveColor();
        }
        node->emissive = (emissive.r + emissive.b + emissive.g) / 3.0f;

        //Get the alpha of the material
        float Alpha = 1.0f;
        if ( niMatProp ) {
            Alpha = niMatProp->GetTransparency();
        }

        //Check that there is at least one set of texture coords available
        if(niGeomData->GetUVSetCount()==0) {
            //log_file << "There are no texture coordinates on this mesh." << endl;
            return false;
        }

        //ProgMesh simplify=ProgMesh(niGeomData);
        //simplify.ComputeProgressiveMesh();
        //simplify.DoProgressiveMesh(0.1);

        //Indicies
        vector<Triangle> tris = niGeomData->GetTriangles();
        node->faces=tris.size();
        if(node->faces==0) {
            //log_file << "This mesh has no triangles." << endl;
            return false;
        }

        //Now that we're sure this mesh is valid, start the conversion

        //Get transformation of mesh as 4x4 matrix
        Matrix44 transform = niGeom->GetWorldTransform();

        //Get a matrix that only contains the world rotation matrix
        //This will be used to transform normals
        Matrix44 rotation(transform.GetRotation());

        node->iBuffer=new unsigned short[node->faces*3];
        for(int i=0;i<node->faces;i++) {
            node->iBuffer[i*3+0]=tris[i].v1;
            node->iBuffer[i*3+1]=tris[i].v2;
            node->iBuffer[i*3+2]=tris[i].v3;
        }

        //Vertex data
        vector<Vector3> positions;
        vector<Vector3> normals;
        if ( niGeom->IsSkin() ) {
            niGeom->GetSkinDeformation( positions, normals );
        } else {
            positions = niGeomData->GetVertices();
            normals = niGeomData->GetNormals();
        }
        vector<Color4> colors = niGeomData->GetColors();
        vector<TexCoord> texCoords = niGeomData->GetUVSet(0);

        //Verticies
        node->verts=niGeomData->GetVertexCount();

        node->vBuffer=new DXVertex[node->verts];
        for(int i=0;i<node->verts;i++) {
            //Push the world transform into the verticies
            positions[i] = transform * positions[i];

            normals[i] = rotation * normals[i];

            //Apply the world transform's rotation to the normals

            node->vBuffer[i].Position=positions[i];
            if(normals.size()>0) {
                node->vBuffer[i].Normal=normals[i];
            } else {
                node->vBuffer[i].Normal.x=0;
                node->vBuffer[i].Normal.y=0;
                node->vBuffer[i].Normal.z=1;
            }
            if(colors.size()>0) {
                node->vBuffer[i].Diffuse[0]=(unsigned char)(255.0f*colors[i].b * diffuse.b);
                node->vBuffer[i].Diffuse[1]=(unsigned char)(255.0f*colors[i].g * diffuse.g);
                node->vBuffer[i].Diffuse[2]=(unsigned char)(255.0f*colors[i].r * diffuse.r);
                node->vBuffer[i].Diffuse[3]=(unsigned char)(255.0f * colors[i].a * Alpha);
            } else {
                node->vBuffer[i].Diffuse[0] = (unsigned char)(255.0f * diffuse.b);
                node->vBuffer[i].Diffuse[1] = (unsigned char)(255.0f * diffuse.g);
                node->vBuffer[i].Diffuse[2] = (unsigned char)(255.0f * diffuse.r);
                node->vBuffer[i].Diffuse[3] = (unsigned char)(255.0f * Alpha);
            }

            node->vBuffer[i].texCoord=texCoords[i];
        }

        //Get texture file path
        string s = niSrcTex->GetTextureFileName();

        //Make texture path all lowercase
        for ( size_t i = 0; i < s.size(); ++i ) {
            if ( s[i] >= 65 && s[i] <= 90 ) {
                s[i] += 32;
            }
        }

        //If the path starts with "textures" or "\textures" remove it
        size_t pos = s.find( "textures" );
        if ( pos <= 1 ) {
            s = s.substr( pos + 8, string::npos );
        }

        //Remove any leading forward slashes that remain
        if ( s[0] == '\\' ) {
            s = s.substr(1, string::npos );
        }

        node->tex = s;

        return true;
    }


public:

    void Optimize( unsigned int cache_size, float simplify, bool old ) {
        //Try to combine nodes that have the same texture path
        map<string, ExportedNode*> node_tex;

        for ( size_t i = 0; i < nodes.size(); ++i ) {
            //Check if this node has already been found
            map<string, ExportedNode*>::iterator it = node_tex.find( nodes[i].tex );

            if ( it == node_tex.end() ) {
                //Nothing with this texture has been found yet.  Store the node's pointer in the map
                node_tex[ nodes[i].tex ] = &nodes[i];
            } else {
                //A shape with this texture has been found already.  Merge this one into it.
                MergeShape( it->second, &nodes[i] );
            }
        }

        size_t count = 0;
        if ( node_tex.size() < nodes.size() && node_tex.size() != 0 ) {
            //We reduced the number of nodes, so create a new list to save
            vector<ExportedNode> merged_nodes( node_tex.size() );

            for ( map<string, ExportedNode*>::iterator it = node_tex.begin(); it != node_tex.end(); ++it ) {
                merged_nodes[count] = *(it->second);

                ++count;
            }

            nodes = merged_nodes;
        }


        //Now optimize each node
        for ( size_t i = 0; i < nodes.size(); ++i ) {
            nodes[i].Optimize(cache_size, simplify, old);
        }
    }

    bool LoadNifFromStream( const char* data, int size ) {

        istrstream s(data, size);
        NiAVObjectRef rootObj = DynamicCast<NiAVObject>( ReadNifTree(s, 0) );

        //Object root transform should not affect results
        rootObj->SetLocalTransform( Matrix44::IDENTITY );

        vector<NiTriBasedGeomRef> SubsetNodes;

        if(!rootObj) {
            //log_file << "Root object was null." << endl;
            return false;
        }

        SearchShapes( rootObj, &SubsetNodes );

        if( SubsetNodes.size() == 0 ) {
            //log_file << "SubsetNodes size is zero." << endl;
            return false;
        }

        for( size_t i = 0; i < SubsetNodes.size(); ++i ) {
            ExportedNode tmp_node;
            if( ExportShape(SubsetNodes[i], &tmp_node) ) {
                nodes.push_back( tmp_node );
            }
        }

        if( nodes.size() == 0 ) {
            //log_file << "nodes size is zero." << endl;
            return false;
        }

        //Success
        return true;
    }

    bool Save() {
        //HANDLE h=CreateFileA(outpath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
        HANDLE h = staticFile;

        DWORD unused;
        if(h==INVALID_HANDLE_VALUE) {
            //log_file << "File handle is invalid." << endl;
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

        for( size_t i = 0; i < nodes.size(); i++ ) {
            nodes[i].Save(h);
        }

        return true;
    }
};

int _stdcall GetVertSize() {
    return (int)sizeof(DXVertex);
}

int _stdcall GetCompressedVertSize() {
    return (int)sizeof(DXCompressedVertex);
}

int _stdcall GetLandVertSize() {
    return (int)sizeof(DXCompressedLandVertex);
}

float _stdcall ProcessNif(char* data, int datasize, float simplify, float cutoff, BYTE static_type, BYTE old) {

    //Load the NIF data into our DirectX-friendly format
    ExportedNif nif;
    if (! nif.LoadNifFromStream(data, datasize) ) {
        //log_file << "LoadNifFromStream failed." << endl;
        return -1;
    }

    //Calculate the bounds of the NIF to determine whether it exceeds our cutoff value
    nif.CalcBounds();

    if( static_type == STATIC_AUTO && nif.radius < cutoff ) {
        //log_file << "Radius was below cutoff value." << endl;
        return -2;
    }

    //Buildings are treated as if they are twice their actual size.
    if( static_type == STATIC_BUILDING && nif.radius * 2.0f < cutoff ) {
        //log_file << "Radius was below cutoff value." << endl;
        return -2;
    }

    if(!staticFile) {
        return nif.radius;
    }

    //Optimize NIF and calculate node bounds

    nif.Optimize(16, simplify, old!=0);
    nif.CalcNodeBounds();

    //Determine whether this will be a near or far distant static based on size
    nif.static_type = static_type;

    //Save NIF to new format
    if (!nif.Save() ) {
        //log_file << "NIF Save failed." << endl;
        return -3;
    }

    return nif.radius;
}

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

    unsigned int & operator[](int n) {
        switch (n) {
            case 0: return v1; break;
            case 1: return v2; break;
            case 2: return v3; break;
            default: throw std::out_of_range("Index out of range for Triangle");
        };
    }
    unsigned int operator[](int n) const {
        switch (n) {
            case 0: return v1; break;
            case 1: return v2; break;
            case 2: return v3; break;
            default: throw std::out_of_range("Index out of range for Triangle");
        };
    }
};

bool LoadLandMesh( char* file_path, vector<Vector3> & vertices, vector<TexCoord> & uvs, vector<LargeTriangle> & triangles ) {
    HANDLE file=CreateFile(file_path,GENERIC_READ,0,0,OPEN_EXISTING,0,0);
    if(file==INVALID_HANDLE_VALUE) { return false; }
    DWORD verts, faces, unused;
    bool large;
    ReadFile(file,&verts,4,&unused,0);
    ReadFile(file,&faces,4,&unused,0);

    if( verts>0xFFFF || faces>0xFFFF ) {
        large = true;
    } else {
        large = false;
    }

    vertices.resize(verts);
    //normals.resize(verts);
    uvs.resize(verts);
    triangles.resize(faces);

    for ( size_t i = 0; i < verts; ++i ) {
        ReadFile(file,&vertices[i], 12, &unused, 0);
        //ReadFile(file,&normals[i], 12, &unused, 0);
        ReadFile(file,&uvs[i], 8, &unused, 0);
    }

    for ( size_t i = 0; i < faces; ++i ) {
        if ( large == true ) {
            unsigned int tmp[3];
            ReadFile(file,tmp,4*3,&unused,0);
            triangles[i].v1 = tmp[0];
            triangles[i].v2 = tmp[1];
            triangles[i].v3 = tmp[2];
        } else {
            unsigned short tmp[3];
            ReadFile(file,tmp,2*3,&unused,0);
            triangles[i].v1 = tmp[0];
            triangles[i].v2 = tmp[1];
            triangles[i].v3 = tmp[2];
        }
    }

    CloseHandle(file);

    return true;
}

class LandMesh {
public:
    vector<Vector3> vertices;
    vector<LargeTriangle> triangles;
    vector<TexCoord> uvs;
    float radius;
    Vector3 center;
    Vector3 min;
    Vector3 max;

    void CalcBounds( const Vector3 & new_min, const Vector3 & new_max ) {

        min = new_min;
        max = new_max;

        //Average min/max positions to get center
        center = (min + max) / 2.0f;

        //Find the furthest point from the center to get the radius
        float radius_sqared = 0.0f;

        for ( size_t i = 0; i < vertices.size(); ++i ) {
            float x, y, z;
            x = vertices[i].x;
            y = vertices[i].y;
            z = vertices[i].z;

            float dist = (x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) + (z-center.z)*(z-center.z);

            if ( dist > radius_sqared ) {
                radius_sqared = dist;
            }
        }

        radius = sqrt( radius_sqared );
    }

    static bool SaveMeshes( LPCSTR file_path, vector<LandMesh> & meshes ) {
        DWORD mesh_count, unused;
        HANDLE file=CreateFile(file_path,GENERIC_WRITE,0,0,CREATE_ALWAYS,0,0);
        if(file==INVALID_HANDLE_VALUE) { return false; }
        mesh_count = meshes.size();
        WriteFile(file, &mesh_count, 4, &unused, 0 );

        for ( size_t i = 0; i < meshes.size(); ++i ) {
            if ( !meshes[i].Save(file) ) { return false; }
        }

        CloseHandle(file);

        return true;
    }

    bool Save( HANDLE & file ) {
        DWORD verts, faces, unused;
        bool large;
        verts = vertices.size();
        faces = triangles.size();

        WriteFile(file,&radius,4,&unused,0);
        WriteFile(file,&center, 12, &unused, 0);

        WriteFile(file,&min, 12, &unused, 0);
        WriteFile(file,&max, 12, &unused, 0);

        WriteFile(file,&verts,4,&unused,0);
        WriteFile(file,&faces,4,&unused,0);

        if( verts>0xFFFF || faces>0xFFFF ) {
            large = true;
        } else {
            large = false;
        }

        DXCompressedLandVertex * compVerts = new DXCompressedLandVertex[verts];

        for ( size_t i = 0; i < verts; ++i ) {
            compVerts[i].Position = vertices[i];

            //WriteFile(file,&vertices[i], 12, &unused, 0);
            //WriteFile(file,&uvs[i], 8, &unused, 0);

            //Compress UVs to a normalized 16-bit unsigned short
            //short compUVs[2];
            compVerts[i].texCoord[0] = (short)(uvs[i].u * 32768.0f);
            compVerts[i].texCoord[1] = (short)(uvs[i].v * 32768.0f);
            //WriteFile(file, compUVs, 4, &unused, 0);
        }

        WriteFile(file, compVerts, sizeof(DXCompressedLandVertex) * verts, &unused, 0);

        delete [] compVerts;

        for ( size_t i = 0; i < faces; ++i ) {
            if ( large == true ) {
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
    HeightFieldSampler( float * d, size_t dh, size_t dw, float t, float l, float b, float r ) :
        data(d), data_height(dh), data_width(dw), top(t), left(l), bottom(b), right(r) {}
    ~HeightFieldSampler() {}

    TexCoord SampleTexCoord( float x, float y ) {
        float tx = (0.0f - left + x) / (right - left);
        float ty = 1.0f - ((0.0f - bottom + y) / (top - bottom));
        return TexCoord( tx, ty );
    }

    float SampleHeight( float x, float y ) {
        //Figure which height values to sample.
        size_t low_x, high_x, low_y, high_y;

        float data_x = (0.0f - left + x) / (right - left) * (float)data_width;
        float data_y = (0.0f - bottom + y) / (top - bottom) * (float)data_height;

        low_x = (size_t)floor(data_x);
        high_x = (size_t)ceil(data_x);
        low_y = (size_t)floor(data_y);
        high_y = (size_t)ceil(data_y);

        //Linear Interpolation
        float x_interp = 1.0f;
        if ( high_x - low_x == 1 ) {
            x_interp = data_x - (float)low_x;
        }

        float y_interp = 1.0f;
        if ( high_y - low_y == 1 ) {
            float y_interp = data_y - (float)low_y;
        }

        //horizontal
        float bottom_val = GetHeightValue(low_x, low_y) * (1.0f - x_interp) + GetHeightValue( high_x, low_y ) * x_interp;
        float top_val = GetHeightValue(low_x, high_y) * (1.0f - x_interp) + GetHeightValue( high_x, high_y ) * x_interp;

        //vertical
        float result = top_val * (1.0f - y_interp) + bottom_val * y_interp;
        return result;
    }

    float GetHeightValue( size_t x, size_t y ) {
        if ( x < 0 ) { x = 0; }
        if ( x > data_width - 1 ) { x = data_width - 1; }
        if ( y < 0 ) { y = 0; }
        if ( y > data_height - 1 ) { y = data_height -1; }

        return data[ y * data_width + x ];
    }

    float top, left, bottom, right;
    float * data;
    size_t data_height;
    size_t data_width;
};

class SplitTriangle {
public:
    Vector3 left, right, top;
    SplitTriangle( const Vector3 & left, const Vector3 & right, const Vector3 & top ) {
        this->left = left;
        this->right = right;
        this->top = top;
    }
    ~SplitTriangle() {}

    Vector3 GetHypoCenter() {
        return (right + left) / 2.0f;
    }

    SplitTriangle LeftSplit( const Vector3 & new_vert ) {
        return SplitTriangle( right, top, new_vert );
    }

    SplitTriangle RightSplit( const Vector3 & new_vert ) {
        return SplitTriangle( top, left, new_vert );
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
        //Make sure pool can hold this object
        if( last_used_index + 1 >= pool.size() ) {
            //No more room RoamVarianceNode objects to hand out.  return NULL
            return 0;
        }

        //increment the last used index and return the object at that position
        ++last_used_index;
        //Clear out any data in the object so it's as if it's a new object
        pool[last_used_index].ClearChildren();

        return &pool[last_used_index];
    }

    //This shouldn't be called directly, used Create instead to allocate with the pool
    RoamVarianceNode() : variance(0.0f), left_child(0), right_child(0) {}

    static void ResetPool() {
        //Move the index of the next node to be handed out back to the begining.
        //There should be no outstanding RoamVarianceNode pointers when this is called.
        last_used_index = 0;
    }

    void ClearChildren() {
        left_child = 0;
        right_child = 0;
    }

    ~RoamVarianceNode() {}

    void CalculateVariance( HeightFieldSampler * sampler, SplitTriangle & tri, size_t depth ) {
        //On the downward pass, calculate the variance as the difference in height between the
        //average of left and right, and the the real height value as given by the sampler
        Vector3 avg = tri.GetHypoCenter();
        float samp_height = sampler->SampleHeight( avg.x, avg.y );

        variance = abs( avg.z - samp_height );

        //Give extra weight to the split if it causes the vertex to switch from being above the water to being below the water or vice versa
        //Water level is zero
        if ( (avg.z > 0.0f && samp_height < 0.0f) || samp_height > 0.0f && avg.z < 0.0f ) {
            variance *= 4.0f;
        }

        //Give extra weight to the split if it the average vertex would be above the real height
        if ( avg.z > samp_height ) {
            variance *= 4.0f;
        }

        //If we have reached the maximum depth, free any children and start unwiding traversal
        if ( depth == 0 ) {
            ClearChildren();
            return;
        }

        //If we have not reached the maximum depth, create children and call this function on them
        avg.z = samp_height;

        if (!right_child) {
            right_child = Create();
        }
        right_child->CalculateVariance( sampler, tri.RightSplit(avg), depth - 1 );


        if (!left_child) {
            left_child = Create();
        }
        left_child->CalculateVariance( sampler, tri.LeftSplit(avg), depth - 1 );

        //We want the variance of this node to represent the maximum variance of all children nodes, so choose the highest of
        //the variances as the new variance
        if ( right_child->variance > variance ) {
            variance = right_child->variance;
        }
        if ( left_child->variance > variance ) {
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
    RoamTriangleNode * rt;

    RenderTriangle( const SplitTriangle & s_tri, RoamTriangleNode * r_tri ) : st(s_tri), rt(r_tri) {
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
        //Check whether this node has already been split
        if (left_child || right_child ) {
            //This node has already been split
            return;
        }

        //Check if the hypotonuse of this triangle is on an edge (has no base neighbor)
        if (!base_neighbor) {
            //This is on an edge, so split this triangle only
            EdgeSplit();
            return;
        }

        //Check if this triangle and its base neighbor form a diamond (they are eachother's base neighbor)
        if (base_neighbor->base_neighbor == this) {
            //split this triangle and its neighbor
            DiamondSplit();
            return;
        }

        //These triangles don't form a diamond, so call split on the base neighbor before splitting this triangle
        base_neighbor->Split();

        //Split the triangle and its neighbor
        DiamondSplit();
    }

private:
    void EdgeSplit() {
        assert(left_child == 0 && right_child == 0);

        //Create children
        left_child = new RoamTriangleNode();
        right_child = new RoamTriangleNode();

        //Set neighbor linkage
        left_child->base_neighbor = left_neighbor;
        left_child->left_neighbor = right_child;
        left_child->right_neighbor = 0;

        RelinkNeighbor( left_child->left_neighbor, this, left_child );
        RelinkNeighbor( left_child->base_neighbor, this, left_child );

        right_child->base_neighbor = right_neighbor;
        right_child->left_neighbor = 0;
        right_child->right_neighbor = left_child;

        RelinkNeighbor( right_child->left_neighbor, this, right_child );
        RelinkNeighbor( right_child->base_neighbor, this, right_child );

        //Clear neighbors of this object since it now just represents a node, not a real triangle
        //Don't clear base_neighbor since it should either already be null or cleared by the DiamondSplit function
        right_neighbor = 0;
        left_neighbor = 0;
    }

    void RelinkNeighbor( RoamTriangleNode* neighbor, RoamTriangleNode* old_link, RoamTriangleNode* new_link ) {
        if (neighbor) {
            if ( neighbor->base_neighbor == old_link ) {
                neighbor->base_neighbor = new_link;
            } else if ( neighbor->left_neighbor == old_link ) {
                neighbor->left_neighbor = new_link;
            } else if ( neighbor->right_neighbor == old_link ) {
                neighbor->right_neighbor = new_link;
            }
        }
    }

    void DiamondSplit() {
        assert( base_neighbor != 0 && base_neighbor->base_neighbor == this );

        //Start with an edge split for both triangles
        EdgeSplit();
        base_neighbor->EdgeSplit();

        //Now set left and right neighbor links which are set to zero by the basic edge split
        right_child->left_neighbor = base_neighbor->left_child;
        left_child->right_neighbor = base_neighbor->right_child;

        base_neighbor->right_child->left_neighbor = left_child;
        base_neighbor->left_child->right_neighbor = right_child;

        //Clear base_neighbors of these objects since they now just represents a node, not a real triangle
        base_neighbor->base_neighbor = 0;
        base_neighbor = 0;

    }
public:
    void Tesselate( RoamVarianceNode* v_tri, float max_variance ) {
        //Determine if the variance of this triangle is enough that we want to split it
        if ( v_tri->variance < max_variance ) {
            //The variance is within tolerable levels, so end the recursion of this branch
            return;
        }

        //The variance is too high, so we need to split this triangle
        Split();

        //If the variance triangle has children, continue on down the tree recursivly
        if ( !v_tri->left_child || !v_tri->right_child ) {
            //The variance triangle has no children, so we're done
            return;
        }

        //The variance triangle has children so call this function on the newly created children of this roam triangle node
        left_child->Tesselate( v_tri->left_child, max_variance );
        right_child->Tesselate( v_tri->right_child, max_variance );
    }

    void GatherTriangles( HeightFieldSampler * sampler, SplitTriangle & s_tri, vector<RenderTriangle> & triangles  ) {

        Vector3 hc = s_tri.GetHypoCenter();
        hc.z = sampler->SampleHeight( hc.x, hc.y );

        if ( !left_child || !right_child ) {
            //This node has no children, so add the triangle to the list and return
            triangles.push_back( RenderTriangle(s_tri, this) );
            return;
        }

        //This node has children, so call this function on them
        left_child->GatherTriangles( sampler, s_tri.LeftSplit(hc), triangles );
        right_child->GatherTriangles( sampler, s_tri.RightSplit(hc), triangles );
    }

    //void DebugPrint( size_t depth = 0 ) {
    //    for ( size_t i = 0; i < depth; ++i ) {
    //        log_file << "  ";
    //    }

    //    log_file << depth << " - rn: " << right_neighbor << " ln: " << left_neighbor << " bn: " << base_neighbor << " lc:" << left_child << " rc: " << right_child << endl;

    //    if ( left_child ) {
    //        left_child->DebugPrint( depth + 1 );
    //    }
    //    if ( right_child ) {
    //        right_child->DebugPrint( depth + 1 );
    //    }
    //}
};

class CmpVec3 : public Vector3 {
public:
    CmpVec3(const Vector3 & v ) {
        x = v.x;
        y = v.y;
        z = v.z;
    }

    CmpVec3 & operator=( const Vector3 & rh ) {
        x = rh.x;
        y = rh.y;
        z = rh.z;
    }

    Vector3 AsVec3() {
        return Vector3(x,y,z);
    }

    static bool FltEq( float lh, float rh ) {
        return abs(lh - rh) < 0.0001f;
    }

    static bool FltLt( float lh, float rh ) {
        return lh - 0.0001f < rh;
    }

    bool operator==( const CmpVec3 & rh ) const {
        return FltEq(x, rh.x) && FltEq(y, rh.y) && FltEq(z, rh.z);
    }

    friend bool operator<( const CmpVec3 & lh, const CmpVec3 & rh ) {
        if ( lh == rh ) {
            return false;
        }

        if ( FltEq(lh.x, rh.x) ) {
            if ( FltEq(lh.y, rh.y) ) {
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
    RoamLandPatch( float t, float l, float b, float r, HeightFieldSampler* s ) : top(t), left(l), bottom(b), right(r), sampler(s) {
        t1.base_neighbor = &t2;
        t2.base_neighbor = &t1;
    }

    RoamLandPatch( const RoamLandPatch & patch ) {
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
        return Vector3( left, top, sampler->SampleHeight(left,top) );
    }
    Vector3 GetBottomLeft() {
        return Vector3( left, bottom, sampler->SampleHeight(left,bottom) );
    }
    Vector3 GetTopRight() {
        return Vector3( right, top, sampler->SampleHeight(right,top) );
    }
    Vector3 GetBottomRight() {
        return Vector3( right, bottom, sampler->SampleHeight(right,bottom) );
    }

    void ConnectRightNeighbor( RoamLandPatch & neighbor ) {
        t2.right_neighbor = &neighbor.t1;
        neighbor.t1.right_neighbor = &t2;
    }

    void ConnectLeftNeighbor( RoamLandPatch & neighbor ) {
        t1.right_neighbor = &neighbor.t2;
        neighbor.t2.right_neighbor = &t1;
    }

    void ConnectTopNeighbor( RoamLandPatch & neighbor ) {
        t2.left_neighbor = &neighbor.t1;
        neighbor.t1.left_neighbor = &t2;
    }

    void ConnectBottomNeighbor( RoamLandPatch & neighbor ) {
        t1.left_neighbor = &neighbor.t2;
        neighbor.t2.left_neighbor = &t1;
    }

    void Tesselate( float max_variance, size_t tree_depth ) {
        Vector3 top_left = GetTopLeft();
        Vector3 bottom_left = GetBottomLeft();
        Vector3 top_right = GetTopRight();
        Vector3 bottom_right = GetBottomRight();

        RoamVarianceNode* variance_root = RoamVarianceNode::Create();
        variance_root->CalculateVariance( sampler, SplitTriangle(bottom_right, top_left, bottom_left), tree_depth );
        t1.Tesselate( variance_root, max_variance );
        variance_root = 0;
        RoamVarianceNode::ResetPool();

        variance_root = RoamVarianceNode::Create();
        variance_root->CalculateVariance( sampler, SplitTriangle(top_left, bottom_right, top_right), tree_depth );
        t2.Tesselate( variance_root, max_variance );
        variance_root = 0;

        RoamVarianceNode::ResetPool();
    }

    LandMesh GenerateMesh( unsigned int cache_size ) {
        LandMesh mesh;
        Vector3 top_left = GetTopLeft();
        Vector3 bottom_left = GetBottomLeft();
        Vector3 top_right = GetTopRight();
        Vector3 bottom_right = GetBottomRight();

        vector<RenderTriangle> render_triangles;

        t1.GatherTriangles( sampler, SplitTriangle(bottom_right, top_left, bottom_left), render_triangles );
        t2.GatherTriangles( sampler, SplitTriangle(top_left, bottom_right, top_right), render_triangles );

        //Walk through the triangles that were gathered, adding their vertices and indices to a map
        Vector3 max = Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        Vector3 min = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

        map<CmpVec3, size_t> vert_map;
        size_t render_triangles_size = render_triangles.size();
        for ( size_t i = 0; i < render_triangles_size; ++i ) {
            size_t right_index, left_index, top_index;
            map<CmpVec3, size_t>::iterator it;

            it = vert_map.find( render_triangles[i].st.left );
            if ( it == vert_map.end() ) {
                //Add new index
                left_index = mesh.vertices.size();
                Vector3 &v = render_triangles[i].st.left;
                vert_map[v] = left_index;
                mesh.vertices.push_back(v);

                if ( v.x > max.x ) { max.x = v.x; }
                if ( v.y > max.y ) { max.y = v.y; }
                if ( v.z > max.z ) { max.z = v.z; }

                if ( v.x < min.x ) { min.x = v.x; }
                if ( v.y < min.y ) { min.y = v.y; }
                if ( v.z < min.z ) { min.z = v.z; }
            } else {
                //Get index from existing vertex
                left_index = it->second;
            }

            it = vert_map.find( render_triangles[i].st.right );
            if ( it == vert_map.end() ) {
                //Add new index
                right_index = mesh.vertices.size();
                Vector3 &v = render_triangles[i].st.right;
                vert_map[v] = right_index;
                mesh.vertices.push_back(v);

                if ( v.x > max.x ) { max.x = v.x; }
                if ( v.y > max.y ) { max.y = v.y; }
                if ( v.z > max.z ) { max.z = v.z; }

                if ( v.x < min.x ) { min.x = v.x; }
                if ( v.y < min.y ) { min.y = v.y; }
                if ( v.z < min.z ) { min.z = v.z; }
            } else {
                //Get index from existing vertex
                right_index = it->second;
            }

            it = vert_map.find( render_triangles[i].st.top );
            if ( it == vert_map.end() ) {
                //Add new index
                top_index = mesh.vertices.size();
                Vector3 &v = render_triangles[i].st.top;
                vert_map[v] = top_index;
                mesh.vertices.push_back(v);

                if ( v.x > max.x ) { max.x = v.x; }
                if ( v.y > max.y ) { max.y = v.y; }
                if ( v.z > max.z ) { max.z = v.z; }

                if ( v.x < min.x ) { min.x = v.x; }
                if ( v.y < min.y ) { min.y = v.y; }
                if ( v.z < min.z ) { min.z = v.z; }
            } else {
                //Get index from existing vertex
                top_index = it->second;
            }

            mesh.triangles.push_back( LargeTriangle(right_index, top_index, left_index) );
        }

        if ( abs(min.z + 2048.0f) <= 0.001f && abs(max.z + 2048.0f) <= 0.001f ) {
            //This mesh is perfectly flat at the bottom of the world.  Return an empty mesh.
            return LandMesh();
        }

        //Calculate mesh bounds
        mesh.CalcBounds( min, max );

        //Cache optimize triangle and vertex order
        unsigned int* iBuffer = (unsigned int*)&mesh.triangles[0];
        void* vBuffer = (void*)&mesh.vertices[0];
        unsigned int verts = (unsigned int)mesh.vertices.size();
        unsigned int faces = (unsigned int)mesh.triangles.size();
        unsigned int stride = 3 * sizeof(float);

        TootleResult result = TootleOptimizeVCache( iBuffer, faces, verts, cache_size, iBuffer, NULL, TOOTLE_VCACHE_AUTO);

        if( result != TOOTLE_OK ) {
            //log_file << "TootleOptimizeVCache returned an error" << endl;
            return LandMesh();
        }

        result = TootleOptimizeVertexMemory( vBuffer, iBuffer, verts, faces, stride, vBuffer, iBuffer, NULL );

        if( result != TOOTLE_OK ) {
            //log_file << "TootleOptimizeVertexMemory returned an error" << endl;
            return LandMesh();
        }

        //Now that all the vertices have been found, figure out the UVs for them
        for ( size_t i = 0; i < mesh.vertices.size(); ++i ) {
            mesh.uvs.push_back( sampler->SampleTexCoord( mesh.vertices[i].x, mesh.vertices[i].y ) );
        }

        return mesh;
    }

    //void DebugPrint() {
    //    t1.DebugPrint();
    //    t2.DebugPrint();
    //}
};

void TessellateLandscape( char* file_path, float* height_data, unsigned int data_height, unsigned int data_width, float top, float left, float bottom, float right, float error_tolerance ) {

    //Create sampler
    HeightFieldSampler sampler( height_data, data_height, data_width, top, left, bottom, right );

    //Create patches
    size_t patches_across = (size_t)floor( ((float)data_width) / 256.0f + 0.5f );
    size_t patches_down = (size_t)floor( ((float)data_height) / 256.0f + 0.5f );

    float patch_width = (right - left) / (float)patches_across;
    float patch_height = (top - bottom) / (float)patches_down;

    vector<RoamLandPatch> patches;

    Vector3 corner(left, bottom, 0.0f);

    //Fill in patch data
    patches.resize( patches_across * patches_down );

    for ( size_t y = 0; y < patches_down; ++y ) {
        for ( size_t x = 0; x < patches_across; ++x ) {
            size_t i = y * patches_across + x;

            patches[i].sampler = &sampler;
            patches[i].left = corner.x;
            patches[i].right = corner.x + patch_width;
            patches[i].bottom = corner.y;
            patches[i].top = corner.y + patch_height;

            //Move the corner right for the next patch
            corner.x += patch_width;
        }
        //Move the corner up and back to the left edge for the next patch
        corner.y += patch_height;
        corner.x = left;
    }

    //Connect neighboring patches
    for ( size_t y = 0; y < patches_down; ++y ) {
        for ( size_t x = 0; x < patches_across; ++x ) {
            size_t index = y * patches_across + x;
            size_t rn_index = y * patches_across + x + 1;
            size_t tn_index = (y+1) * patches_across + x;

            if ( x != patches_across - 1 ) {
                patches[index].t2.left_neighbor = &patches[rn_index].t1;
                patches[rn_index].t1.left_neighbor = &patches[index].t2;
            }

            if ( y != patches_down - 1 ) {
                patches[index].t2.right_neighbor = &patches[tn_index].t1;
                patches[tn_index].t1.right_neighbor = &patches[index].t2;
            }
        }
    }

    //Tesselate patches
    for ( size_t i = 0; i < patches.size(); ++i ) {
        patches[i].Tesselate( error_tolerance, 14 );
    }

    //patch.DebugPrint();

    //Generate Meshes
    vector<LandMesh> meshes;

    for ( size_t i = 0; i < patches.size(); ++i ) {
        LandMesh mesh = patches[i].GenerateMesh(16);

        if ( mesh.vertices.size() > 0 ) {
            meshes.push_back( mesh );
        }
    }

    //Count verts and tris
    size_t verts = 0;
    size_t tris = 0;
    for ( size_t i = 0; i < meshes.size(); ++i ) {
        verts += meshes[i].vertices.size();
        tris += meshes[i].triangles.size();
    }

    //Save the Meshes
    LandMesh::SaveMeshes( file_path, meshes );
}


void _stdcall BeginStaticCreation(IDirect3DDevice9* _device, char* outpath) {
    device=_device;
    if(outpath) staticFile=CreateFileA(outpath, FILE_GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
    else staticFile=0;
}
void _stdcall EndStaticCreation() {
    CloseHandle(staticFile);
}
