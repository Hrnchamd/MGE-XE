#pragma once

#include "mwseinstruction.h"



struct mwseTapKey : public mwseInstruction {
    mwseTapKey(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwsePushKey : public mwseInstruction {
    mwsePushKey(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseReleaseKey : public mwseInstruction {
    mwseReleaseKey(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseHammerKey : public mwseInstruction {
    mwseHammerKey(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseUnhammerKey : public mwseInstruction {
    mwseUnhammerKey(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseAHammerKey : public mwseInstruction {
    mwseAHammerKey(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseAUnhammerKey : public mwseInstruction {
    mwseAUnhammerKey(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseDisallowKey : public mwseInstruction {
    mwseDisallowKey(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseAllowKey : public mwseInstruction {
    mwseAllowKey(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};
