
#include "funcphysics.h"
#include "proxydx/d3d8header.h"
#include "support/log.h"


struct MWEntity
{
    const void *vtbl;
    char tag[4];
    char other[0x20];
    const float *bounds;
    const char *name;
};

struct Node
{
    const void *vtbl;
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

static void **pWorldController = reinterpret_cast<void**>(0x7c6cdc);
static Pick *pick = reinterpret_cast<Pick*>(0x7d12e8);
static Pick::Record lastHit;
const void *vtbl_TriShape = reinterpret_cast<void*>(0x7508b0);

typedef bool (__thiscall *pickObjects_t)(Pick *, float *, float *, bool, float);
typedef void (__thiscall *pickClearResults_t)(Pick *);
typedef MWReference * (__cdecl *findNodeReference_t)(Node *);
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

    MWReference *refr = vmGetTargetRef();
    if(refr)
    {
        Node *node = reinterpret_cast<Node *>(refr->visual);
        // Hide reference's NiNode to avoid self-collision
        if(node)
            node->flags ^= 1;

        // Root of scene to test
        void *spWorldRoot = *reinterpret_cast<void**>(reinterpret_cast<BYTE*>(*pWorldController) + 0x9c);
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
            if(lastHit.spObject->vtbl == vtbl_TriShape && lastHit.spObject->skinInstance)
            {
                // Use reference origin if possible, as actors consist of several skinned meshes
                MWReference *refrHit = findNodeReference(lastHit.spObject);
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
    MWReference *refrHit = findNodeReference(lastHit.spObject);
    return _this->vmPush(reinterpret_cast<VMREGTYPE>(refrHit));
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseModelBounds)

// [ref] ModelBounds -> <float min.x> <float min.y> <float min.z> <float max.x> <float max.y> <float max.z>
bool mwseModelBounds::execute(mwseInstruction *_this)
{
    MWReference *refr = vmGetTargetRef();
    MWEntity *entity = reinterpret_cast<MWEntity*>(refr->baseEntity);

    if(entity->bounds)
    {
        _this->vmPush(entity->bounds[5]);
        _this->vmPush(entity->bounds[4]);
        _this->vmPush(entity->bounds[3]);
        _this->vmPush(entity->bounds[2]);
        _this->vmPush(entity->bounds[1]);
        _this->vmPush(entity->bounds[0]);
    }
    else
    {
        for(size_t i = 0; i < 6; ++i)
            _this->vmPush(VMFLOAT(0));
    }
    return true;
}
