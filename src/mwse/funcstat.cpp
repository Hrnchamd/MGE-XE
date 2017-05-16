
#include "mge/mwbridge.h"
#include "funcstat.h"


static MWRecord * findEntity(const char *id)
{
    typedef MWRecord * (__thiscall *findMWEntity_t)(void *, const char *);
    const findMWEntity_t findMWEntity = reinterpret_cast<findMWEntity_t>(0x4b8b60);

    DWORD *dataHandler = *reinterpret_cast<DWORD**>(0x7c67e0);
    return findMWEntity(*reinterpret_cast<void**>(dataHandler), id);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetBaseHealth)

// [ref] GetBaseHealth -> returns <float>
bool mwseGetBaseHealth::execute(mwseInstruction *_this)
{
    VMFLOAT ret = 0;
    const BYTE *actor = reinterpret_cast<const BYTE*>(vmGetTargetActor());

    if(actor)
        ret = *reinterpret_cast<const float *>(actor + 0x2b8);

    return _this->vmPush(ret);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetBaseMagicka)

// [ref] GetBaseMagicka -> returns <float>
bool mwseGetBaseMagicka::execute(mwseInstruction *_this)
{
    VMFLOAT ret = 0;
    const BYTE *actor = reinterpret_cast<const BYTE*>(vmGetTargetActor());

    if(actor)
        ret = *reinterpret_cast<const float *>(actor + 0x2c4);

    return _this->vmPush(ret);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetBaseFatigue)

// [ref] GetBaseFatigue -> returns <float>
bool mwseGetBaseFatigue::execute(mwseInstruction *_this)
{
    VMFLOAT ret = 0;
    const BYTE *actor = reinterpret_cast<const BYTE*>(vmGetTargetActor());

    if(actor)
        ret = *reinterpret_cast<const float *>(actor + 0x2dc);

    return _this->vmPush(ret);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseLastActorHit)

// [ref] LastActorHit -> returns <ref>
bool mwseLastActorHit::execute(mwseInstruction *_this)
{
    VMREGTYPE ret = 0;
    const BYTE *actor = reinterpret_cast<const BYTE*>(vmGetTargetActor());

    if(actor)
    {
        const BYTE *targetActor = *reinterpret_cast<const BYTE *const *>(actor + 0xf0);
        if(targetActor)
            ret = *reinterpret_cast<const VMREGTYPE *>(targetActor + 0x14);
    }

    return _this->vmPush(ret);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetDeleted)

// [ref] GetDeleted -> returns <long>
bool mwseGetDeleted::execute(mwseInstruction *_this)
{
    const MWReference *refr = vmGetTargetRef();
    VMREGTYPE ret = (refr->flags & 0x20) != 0;
    return _this->vmPush(ret);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseIsScripted)

// [ref] IsScripted -> returns <long>
bool mwseIsScripted::execute(mwseInstruction *_this)
{
    const MWReference *refr = vmGetTargetRef();
    const MWRecord *entity = refr->baseEntity;

    // Call <vtbl + 0x4c> const char * Entity::getScript
    typedef const char * (__thiscall *getScript_t)(const MWRecord *);
    getScript_t getScript = reinterpret_cast<getScript_t>(entity->vtbl[0x13]);
    VMREGTYPE ret = getScript(entity) != 0;

    return _this->vmPush(ret);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetEntityName)

// Replacement for buggy MWSE function
// [ref] SetEntityName <string name>
bool mwseSetEntityName::execute(mwseInstruction *_this)
{
    MWReference *refr = vmGetTargetRef();
    MWRecord *entity = refr->baseEntity;
    const char *name = _this->vmPopString();
    if(!name) return false;

    // Check if entity is an actor clone, as only the base entity can set the name
    typedef char (__thiscall *isClone_t)(const MWRecord *);
    isClone_t isClone = reinterpret_cast<isClone_t>(0x4f0ff0);
    if(isClone(entity))
    {
        // Get base entity
        entity = *reinterpret_cast<MWRecord**>(reinterpret_cast<BYTE*>(entity) + 0x6c);
    }

    // Call <vtbl + 0x10c> Entity::setName(const char *)
    typedef void (__thiscall *setName_t)(MWRecord *, const char *);
    setName_t setName = reinterpret_cast<setName_t>(entity->vtbl[0x43]);
    setName(entity, name);

    // Set entity modified flag so that the name is saved
    // Has a side effect of locking in the entity data from the current load order
    entity->flags |= 2;

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetOwner)

// Replacement for missing MWSE function
// [ref] SetOwner <string id> -> <long success>
bool mwseSetOwner::execute(mwseInstruction *_this)
{
    VMREGTYPE ret = 0;
    MWReference *refr = vmGetTargetRef();
    const char *id = _this->vmPopString();
    if(!id) return false;

    typedef DWORD * (__thiscall *getConditionData_t)(MWReference *);
    const getConditionData_t getConditionData = reinterpret_cast<getConditionData_t>(0x4e5460);
    DWORD *cond = getConditionData(refr);

    if(cond)
    {
        // Check if owner is a base NPC
        const MWRecord *owner = findEntity(id);
        if(owner && owner->vtbl == reinterpret_cast<void**>(0x749de8))
        {
            // Write owner into item condition struct
            cond[1] = reinterpret_cast<DWORD>(owner);
            // Set reference modified flag
            refr->flags |= 2;
            ret = 1;
        }
    }

    return _this->vmPush(ret);
}
