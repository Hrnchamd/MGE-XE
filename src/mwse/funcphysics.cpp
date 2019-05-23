
#include "funcphysics.h"
#include "proxydx/d3d8header.h"
#include "support/log.h"



struct MWEntity : MWRecord {
    char other[0x18];
    const float* bounds;
    const char* name;
};

struct Node {
    const void** vtbl;
    char stuff[0x10];
    unsigned short flags;
    unsigned short pad;
    Node* parent;
    float boundOrigin[3];
    float boundRadius;
    float* pLocalRotate;
    float localTranslate[3];
    float localScale;
    float worldRotate[9];
    float worldTranslate[3];
    float worldScale;
    char various[0x28];
    void* skinInstance;
};

struct Pick {
    struct Record {
        Node* spObject;
        Node* spProxyParent;
        float intersect[3];
        float distance;
        unsigned short usTriangleIndex;
        unsigned short usVertexIndex[3];
        float texture[2];
        float normal[3];
        unsigned char color[4];
    };
    struct Results {
        void** vtbl;
        Record** data;
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
    void* spRoot;
    Results pickResults;
    Record* pLastAddedRecord;
    bool bReturnTexture;
    bool bReturnNormal;
    bool bReturnSmoothNormal;
    bool bReturnColor;
};

static void** pWorldController = reinterpret_cast<void**>(0x7c6cdc);
static Pick* pick = reinterpret_cast<Pick*>(0x7d12e8);
static Pick::Record lastHit;
const void* vtbl_TriShape = reinterpret_cast<void*>(0x7508b0);

typedef bool (__thiscall* pickObjects_t)(Pick*, const float*, const float*, bool, float);
typedef void (__thiscall* pickClearResults_t)(Pick*);
typedef MWReference* (__cdecl* findNodeReference_t)(Node*);
const pickObjects_t pickObjects = (pickObjects_t)0x6f3050;
const pickClearResults_t pickClearResults = (pickClearResults_t)0x6f2f80;
const findNodeReference_t findNodeReference = (findNodeReference_t)0x4c3c40;



static bool invokeRayTest(mwseInstruction* _this, const D3DXVECTOR3* pos, const D3DXVECTOR3* dir) {
    VMFLOAT hit_t = FLT_MAX;
    VMREGTYPE hit = 0;

    MWReference* refr = mwseInstruction::vmGetTargetRef();
    if (refr) {
        Node* node = reinterpret_cast<Node*>(refr->visual);
        // Hide reference's NiNode to avoid self-collision
        if (node && (node->flags & 1) == 0) {
            node->flags ^= 1;
        } else {
            node = 0;
        }

        // Root of scene to test
        void* spWorldRoot = *reinterpret_cast<void**>(reinterpret_cast<BYTE*>(*pWorldController) + 0x9c);
        pick->spRoot = spWorldRoot;

        float inv_length = 1.0f / D3DXVec3Length(dir);
        D3DXVECTOR3 dir_norm;
        D3DXVec3Scale(&dir_norm, dir, inv_length);
        if (pickObjects(pick, *pos, dir_norm, false, 0.0f)) {
            // Copy hit data to return later
            lastHit = *pick->pickResults.data[0];
            hit_t = lastHit.distance * inv_length;
            hit = 1;
            /*LOG::logline("      -> from=%.0f,%.0f,%.0f to=%.0f,%.0f,%.0f normal=%.3f,%.3f,%.3f t=%.3f dist=%.1f",
                         pos[0], pos[1], pos[2],
                         lastHit.intersect[0], lastHit.intersect[1], lastHit.intersect[2],
                         lastHit.normal[0], lastHit.normal[1], lastHit.normal[2],
                         hit_t, lastHit.distance);*/

            // Fix hit data for skinned meshes
            if (lastHit.spObject->vtbl == vtbl_TriShape && lastHit.spObject->skinInstance) {
                // Use reference origin if possible, as actors consist of several skinned meshes
                MWReference* refrHit = findNodeReference(lastHit.spObject);
                float* origin = refrHit ? refrHit->position : lastHit.spObject->boundOrigin;

                lastHit.intersect[0] = pos->x + hit_t * dir->x;
                lastHit.intersect[1] = pos->y + hit_t * dir->y;
                lastHit.intersect[2] = pos->z + hit_t * dir->z;

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
        if (node) {
            node->flags ^= 1;
        }
    }

    _this->vmPush(hit_t);
    _this->vmPush(hit);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseRayTest)

// [ref] RayTest <float dir.x> <float dir.y> <float dir.z> -> <long hit> <float hit_t>
bool mwseRayTest::execute(mwseInstruction* _this) {
    D3DXVECTOR3 pos, dir;

    if (!_this->vmPop(&dir.x)) { return false; }
    if (!_this->vmPop(&dir.y)) { return false; }
    if (!_this->vmPop(&dir.z)) { return false; }

    MWReference* refr = mwseInstruction::vmGetTargetRef();
    if (refr) {
        pos = D3DXVECTOR3(refr->position);
        return invokeRayTest(_this, &pos, &dir);
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseRayTestFrom)

// [ref] RayTestFrom <float pos.x> <float pos.y> <float pos.z> <float dir.x> <float dir.y> <float dir.z> -> <long hit> <float hit_t>
bool mwseRayTestFrom::execute(mwseInstruction* _this) {
    D3DXVECTOR3 pos, dir;

    if (!_this->vmPop(&pos.x)) { return false; }
    if (!_this->vmPop(&pos.y)) { return false; }
    if (!_this->vmPop(&pos.z)) { return false; }
    if (!_this->vmPop(&dir.x)) { return false; }
    if (!_this->vmPop(&dir.y)) { return false; }
    if (!_this->vmPop(&dir.z)) { return false; }

    return invokeRayTest(_this, &pos, &dir);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseRayHitPosition)

// RayHitPosition -> <float x> <float y> <float z>
bool mwseRayHitPosition::execute(mwseInstruction* _this) {
    _this->vmPush(static_cast<VMFLOAT>(lastHit.intersect[2]));
    _this->vmPush(static_cast<VMFLOAT>(lastHit.intersect[1]));
    _this->vmPush(static_cast<VMFLOAT>(lastHit.intersect[0]));
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseRayHitNormal)

// RayHitNormal -> <float nx> <float ny> <float nz>
bool mwseRayHitNormal::execute(mwseInstruction* _this) {
    _this->vmPush(static_cast<VMFLOAT>(lastHit.normal[2]));
    _this->vmPush(static_cast<VMFLOAT>(lastHit.normal[1]));
    _this->vmPush(static_cast<VMFLOAT>(lastHit.normal[0]));
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseRayHitRef)

// RayHitRef -> <ref r>
bool mwseRayHitRef::execute(mwseInstruction* _this) {
    MWReference* refrHit = findNodeReference(lastHit.spObject);
    return _this->vmPush(reinterpret_cast<VMREGTYPE>(refrHit));
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseModelBounds)

// [ref] ModelBounds -> <float min.x> <float min.y> <float min.z> <float max.x> <float max.y> <float max.z>
bool mwseModelBounds::execute(mwseInstruction* _this) {
    MWReference* refr = vmGetTargetRef();
    MWEntity* entity = reinterpret_cast<MWEntity*>(refr->baseEntity);

    if (entity->bounds) {
        _this->vmPush(entity->bounds[5]);
        _this->vmPush(entity->bounds[4]);
        _this->vmPush(entity->bounds[3]);
        _this->vmPush(entity->bounds[2]);
        _this->vmPush(entity->bounds[1]);
        _this->vmPush(entity->bounds[0]);
    } else {
        for (size_t i = 0; i < 6; ++i) {
            _this->vmPush(VMFLOAT(0));
        }
    }
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseTransformVec)

// [ref] TransformVec <float v.x> <float v.y> <float v.z> -> <float v.x> <float v.y> <float v.z>
// Transform a vector by the reference's local transform
bool mwseTransformVec::execute(mwseInstruction* _this) {
    MWReference* refr = vmGetTargetRef();
    Node* node = reinterpret_cast<Node*>(refr->visual);
    D3DXVECTOR3 v, t;

    if (!_this->vmPop(&v.x)) { return false; }
    if (!_this->vmPop(&v.y)) { return false; }
    if (!_this->vmPop(&v.z)) { return false; }

    const float* m = node->pLocalRotate;
    D3DXVec3Scale(&v, &v, node->localScale);
    t.x = m[0]*v.x + m[1]*v.y + m[2]*v.z + node->localTranslate[0];
    t.y = m[3]*v.x + m[4]*v.y + m[5]*v.z + node->localTranslate[1];
    t.z = m[6]*v.x + m[7]*v.y + m[8]*v.z + node->localTranslate[2];

    _this->vmPush(t.z);
    _this->vmPush(t.y);
    _this->vmPush(t.x);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseIsAirborne)

// [ref] IsAirborne -> <long>
bool mwseIsAirborne::execute(mwseInstruction* _this) {
    void* actor = vmGetTargetActor();
    VMREGTYPE ret = 0;

    if (actor) {
        ret = (reinterpret_cast<BYTE*>(actor)[0x10] & 0x10) != 0;
    }

    return _this->vmPush(ret);
}

MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetAirVelocity)

// [ref] SetAirVelocity <float v.x> <float v.y> <float v.z>
bool mwseSetAirVelocity::execute(mwseInstruction* _this) {
    void* actor = vmGetTargetActor();
    D3DXVECTOR3 v;

    if (!_this->vmPop(&v.x)) { return false; }
    if (!_this->vmPop(&v.y)) { return false; }
    if (!_this->vmPop(&v.z)) { return false; }

    if (actor) {
        *reinterpret_cast<D3DXVECTOR3*>(reinterpret_cast<BYTE*>(actor) + 0x3c) = v;
    }

    return true;
}
