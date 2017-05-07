
#include "mwseinstruction.h"

struct mwseGetBaseHealth : public mwseInstruction
{
    mwseGetBaseHealth(TES3MACHINE& mach) : mwseInstruction(mach) { vptr = &vtable; }
    static __thiscall bool execute(mwseInstruction *_this);

private:
    static vtable_t vtable;
};

struct mwseGetBaseMagicka : public mwseInstruction
{
    mwseGetBaseMagicka(TES3MACHINE& mach) : mwseInstruction(mach) { vptr = &vtable; }
    static __thiscall bool execute(mwseInstruction *_this);

private:
    static vtable_t vtable;
};

struct mwseGetBaseFatigue : public mwseInstruction
{
    mwseGetBaseFatigue(TES3MACHINE& mach) : mwseInstruction(mach) { vptr = &vtable; }
    static __thiscall bool execute(mwseInstruction *_this);

private:
    static vtable_t vtable;
};

struct mwseGetDeleted : public mwseInstruction
{
    mwseGetDeleted(TES3MACHINE& mach) : mwseInstruction(mach) { vptr = &vtable; }
    static __thiscall bool execute(mwseInstruction *_this);

private:
    static vtable_t vtable;
};
