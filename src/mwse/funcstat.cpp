
#include "mge/mwbridge.h"
#include "funcstat.h"


static const BYTE * getRefrActor()
{
    void *refr = *reinterpret_cast<void**>(0x7cebec);
    if(!refr)
        return 0;

    typedef const BYTE * (__thiscall *resolveActor_t)(void *);
    resolveActor_t resolveActor = (resolveActor_t)0x4e5750;
    return resolveActor(refr);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetBaseHealth)

// GetBaseHealth -> returns <float>
bool mwseGetBaseHealth::execute(mwseInstruction *_this)
{
    VMFLOAT ret = 0;
    const BYTE *actor = getRefrActor();

    if(actor)
        ret = *reinterpret_cast<const float *>(actor + 0x2b8);

    return _this->vmPush(ret);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetBaseMagicka)

// GetBaseMagicka -> returns <float>
bool mwseGetBaseMagicka::execute(mwseInstruction *_this)
{
    VMFLOAT ret = 0;
    const BYTE *actor = getRefrActor();

    if(actor)
        ret = *reinterpret_cast<const float *>(actor + 0x2c4);

    return _this->vmPush(ret);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetBaseFatigue)

// GetBaseFatigue -> returns <float>
bool mwseGetBaseFatigue::execute(mwseInstruction *_this)
{
    VMFLOAT ret = 0;
    const BYTE *actor = getRefrActor();

    if(actor)
        ret = *reinterpret_cast<const float *>(actor + 0x2dc);

    return _this->vmPush(ret);
}
