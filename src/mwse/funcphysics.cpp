
#include "funcphysics.h"
#include "proxydx/d3d8header.h"
#include "support/log.h"


struct Node
{
    void *vtbl;
    char stuff[0x10];
    unsigned short flags;
    unsigned short pad;
    Node *parent;
    float boundOrigin[3];
    float boundRadius;
    float *pLocalRotate;
    float localTranslate[3];
    float localScale;
    char various[0x5c];
    void *skinInstance;
};

struct Reference
{
    void *vtbl;
    char something[0xc];
    Node *visual;
    char things[0x14];
    void *baseEntity;
    float orientation[3];
    float position[3];
};

struct Pick
{
    struct Record
    {
        Node *spObject;
        Node *spProxyParent;
        float intersect[3];
        float distance;
        unsigned short usTriangleIndex;
        unsigned short usVertexIndex[3];
        float texture[2];
        float normal[3];
        unsigned char color[4];
    };
    struct Results
    {
        void *vtbl;
        Record **data;
        size_t storageCount;
        size_t endIndex;
        size_t filledCount;
        size_t growByCount;
    };

    int ePickType;
    int eSortType;
    int eIntersectType;
    int eCoordinateType;
    bool bFrontOnly;
    bool bObserveAppCullFlag;
    void *spRoot;
    Results pickResults;
    Record *pLastAddedRecord;
    bool bReturnTexture;
    bool bReturnNormal;
    bool bReturnSmoothNormal;
    bool bReturnColor;
};

static Pick *pick = (Pick *)0x7d12e8;
static Pick::Record lastHit;

typedef bool (__thiscall *pickObjects_t)(Pick *, float *, float *, bool, float);
typedef void (__thiscall *pickClearResults_t)(Pick *);
typedef Reference * (__cdecl *findNodeReference_t)(Node *);
const pickObjects_t pickObjects = (pickObjects_t)0x6f3050;
const pickClearResults_t pickClearResults = (pickClearResults_t)0x6f2f80;
const findNodeReference_t findNodeReference = (findNodeReference_t)0x4c3c40;



MWSEINSTRUCTION_DECLARE_VTABLE(mwseRayTest)

// [ref] RayTest <float dir.x> <float dir.y> <float dir.z> -> <float hit_t>
bool mwseRayTest::execute(mwseInstruction *_this)
{
    D3DXVECTOR3 dir;
    VMFLOAT hit_t = -1.0f;

    if(!_this->vmPop(&dir[0])) return false;
    if(!_this->vmPop(&dir[1])) return false;
    if(!_this->vmPop(&dir[2])) return false;

    Reference *refr = *reinterpret_cast<Reference**>(0x7cebec);
    if(refr)
    {
        Node *node = refr->visual;
        // Hide reference's NiNode to avoid self-collision
        if(node)
            node->flags ^= 1;

        // Root of scene to test
        void *spWorldRoot = *reinterpret_cast<void**>(*reinterpret_cast<BYTE**>(0x7c6cdc) + 0x9c);
        pick->spRoot = spWorldRoot;

        float *pos = refr->position;
        float inv_length = 1.0 / D3DXVec3Length(&dir);
        D3DXVECTOR3 dir_norm;
        D3DXVec3Scale(&dir_norm, &dir, inv_length);
        if(pickObjects(pick, pos, dir_norm, false, 0.0f))
        {
            // Copy hit data to return later
            lastHit = *pick->pickResults.data[0];
            hit_t = lastHit.distance * inv_length;
            /*LOG::logline("      -> from=%.0f,%.0f,%.0f to=%.0f,%.0f,%.0f normal=%.3f,%.3f,%.3f t=%.3f dist=%.1f",
                         pos[0], pos[1], pos[2],
                         lastHit.intersect[0], lastHit.intersect[1], lastHit.intersect[2],
                         lastHit.normal[0], lastHit.normal[1], lastHit.normal[2],
                         hit_t, lastHit.distance);*/

            // Fix hit data for skinned meshes
            if(lastHit.spObject->vtbl == (void*)0x7508b0 && lastHit.spObject->skinInstance)
            {
                // Use reference origin if possible, as actors consist of several skinned meshes
                Reference *refrHit = findNodeReference(lastHit.spObject);
                float *origin = refrHit ? refrHit->position : lastHit.spObject->boundOrigin;

                lastHit.intersect[0] = pos[0] + hit_t * dir[0];
                lastHit.intersect[1] = pos[1] + hit_t * dir[1];
                lastHit.intersect[2] = pos[2] + hit_t * dir[2];

                // Use cylindrical bounds to calculate normal
                D3DXVECTOR3 radial;
                radial[0] = lastHit.intersect[0] - origin[0];
                radial[1] = lastHit.intersect[1] - origin[1];
                radial[2] = 1e-5;
                D3DXVec3Normalize(reinterpret_cast<D3DXVECTOR3*>(lastHit.normal), &radial);
                /*LOG::logline("      => to=%.0f,%.0f,%.0f normal=%.3f,%.3f,%.3f",
                             lastHit.intersect[0], lastHit.intersect[1], lastHit.intersect[2],
                             lastHit.normal[0], lastHit.normal[1], lastHit.normal[2]);*/
            }
        }

        // Required cleanup
        pickClearResults(pick);
        pick->spRoot = 0;

        // Restore visibility of reference's NiNode
        if(node)
            node->flags ^= 1;
    }

    _this->vmPush(hit_t);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseRayHitPosition)

// RayHitPosition -> <float x> <float y> <float z>
bool mwseRayHitPosition::execute(mwseInstruction *_this)
{
    _this->vmPush(static_cast<VMFLOAT>(lastHit.intersect[2]));
    _this->vmPush(static_cast<VMFLOAT>(lastHit.intersect[1]));
    _this->vmPush(static_cast<VMFLOAT>(lastHit.intersect[0]));
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseRayHitNormal)

// RayHitNormal -> <float nx> <float ny> <float nz>
bool mwseRayHitNormal::execute(mwseInstruction *_this)
{
    _this->vmPush(static_cast<VMFLOAT>(lastHit.normal[2]));
    _this->vmPush(static_cast<VMFLOAT>(lastHit.normal[1]));
    _this->vmPush(static_cast<VMFLOAT>(lastHit.normal[0]));
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseRayHitRef)

// RayHitRef -> <ref r>
bool mwseRayHitRef::execute(mwseInstruction *_this)
{
    Reference *refrHit = findNodeReference(lastHit.spObject);
    return _this->vmPush(reinterpret_cast<VMREGTYPE>(refrHit));
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseModelBounds)

// [ref] ModelBounds -> <float min.x> <float min.y> <float min.z> <float max.x> <float max.y> <float max.z>
bool mwseModelBounds::execute(mwseInstruction *_this)
{
    Reference *refr = *reinterpret_cast<Reference**>(0x7cebec);
    BYTE *entity = reinterpret_cast<BYTE*>(refr->baseEntity);
    VMFLOAT *bounds = *reinterpret_cast<VMFLOAT**>(entity + 0x28);
    if(bounds)
    {
        _this->vmPush(bounds[5]);
        _this->vmPush(bounds[4]);
        _this->vmPush(bounds[3]);
        _this->vmPush(bounds[2]);
        _this->vmPush(bounds[1]);
        _this->vmPush(bounds[0]);
    }
    else
    {
        for(size_t i = 0; i < 6; ++i)
            _this->vmPush(VMFLOAT(0));
    }
    return true;
}
