
#include "mwseinstruction.h"

struct mwseRayTest : public mwseInstruction
{
    mwseRayTest(TES3MACHINE& mach) : mwseInstruction(mach) { vptr = &vtable; }
    static __thiscall bool execute(mwseInstruction *_this);
private:
    static vtable_t vtable;
};

struct mwseRayHitPosition : public mwseInstruction
{
    mwseRayHitPosition(TES3MACHINE& mach) : mwseInstruction(mach) { vptr = &vtable; }
    static __thiscall bool execute(mwseInstruction *_this);
private:
    static vtable_t vtable;
};

struct mwseRayHitNormal : public mwseInstruction
{
    mwseRayHitNormal(TES3MACHINE& mach) : mwseInstruction(mach) { vptr = &vtable; }
    static __thiscall bool execute(mwseInstruction *_this);
private:
    static vtable_t vtable;
};

struct mwseRayHitRef : public mwseInstruction
{
    mwseRayHitRef(TES3MACHINE& mach) : mwseInstruction(mach) { vptr = &vtable; }
    static __thiscall bool execute(mwseInstruction *_this);
private:
    static vtable_t vtable;
};

struct mwseModelBounds : public mwseInstruction
{
    mwseModelBounds(TES3MACHINE& mach) : mwseInstruction(mach) { vptr = &vtable; }
    static __thiscall bool execute(mwseInstruction *_this);
private:
    static vtable_t vtable;
};

struct mwseTransformVec : public mwseInstruction
{
    mwseTransformVec(TES3MACHINE& mach) : mwseInstruction(mach) { vptr = &vtable; }
    static __thiscall bool execute(mwseInstruction *_this);
private:
    static vtable_t vtable;
};
