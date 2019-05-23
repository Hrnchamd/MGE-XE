#pragma once

#include "mwseinstruction.h"



struct mwseSetShaderLong : public mwseInstruction {
    mwseSetShaderLong(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseSetShaderFloat : public mwseInstruction {
    mwseSetShaderFloat(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseSetShaderVector : public mwseInstruction {
    mwseSetShaderVector(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseEnableShader : public mwseInstruction {
    mwseEnableShader(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseDisableShader : public mwseInstruction {
    mwseDisableShader(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};
