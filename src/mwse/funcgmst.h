
#include "mwseinstruction.h"

struct mwseGetGS : public mwseInstruction
{
    mwseGetGS(TES3MACHINE& mach) : mwseInstruction(mach) { vptr = &vtable; }
    static __thiscall bool execute(mwseInstruction *_this);

private:
    static vtable_t vtable;
};

struct mwseSetGS : public mwseInstruction
{
    mwseSetGS(TES3MACHINE& mach) : mwseInstruction(mach) { vptr = &vtable; }
    static __thiscall bool execute(mwseInstruction *_this);

private:
    static vtable_t vtable;
};
