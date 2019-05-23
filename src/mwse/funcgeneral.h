#pragma once

#include "mwseinstruction.h"



struct mwseWipeAll : public mwseInstruction {
    mwseWipeAll(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseOutputDebugString : public mwseInstruction {
    mwseOutputDebugString(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseOutputVersionString : public mwseInstruction {
    mwseOutputVersionString(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseGetVersion : public mwseInstruction {
    mwseGetVersion(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseGetScreenWidth : public mwseInstruction {
    mwseGetScreenWidth(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseGetScreenHeight : public mwseInstruction {
    mwseGetScreenHeight(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseGetEyeVec : public mwseInstruction {
    mwseGetEyeVec(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};
