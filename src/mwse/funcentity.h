#pragma once

#include "mwseinstruction.h"



struct mwseGetBaseHealth : public mwseInstruction {
    mwseGetBaseHealth(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseGetBaseMagicka : public mwseInstruction {
    mwseGetBaseMagicka(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseGetBaseFatigue : public mwseInstruction {
    mwseGetBaseFatigue(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseLastActorHit : public mwseInstruction {
    mwseLastActorHit(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseGetDeleted : public mwseInstruction {
    mwseGetDeleted(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseIsScripted : public mwseInstruction {
    mwseIsScripted(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetEntityName : public mwseInstruction {
    mwseSetEntityName(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetOwner : public mwseInstruction {
    mwseSetOwner(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseModelSwitchNode : public mwseInstruction {
    mwseModelSwitchNode(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};
