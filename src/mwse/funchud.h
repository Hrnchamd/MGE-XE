#pragma once

#include "mwseinstruction.h"



void resetMWSEHud();

struct mwseWipeHUDElements : public mwseInstruction {
    mwseWipeHUDElements(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseWithHUD : public mwseInstruction {
    mwseWithHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseCancelWithHUD : public mwseInstruction {
    mwseCancelWithHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseLoadHUD : public mwseInstruction {
    mwseLoadHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwsePositionHUD : public mwseInstruction {
    mwsePositionHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseScaleHUD : public mwseInstruction {
    mwseScaleHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseFullscreenHUD : public mwseInstruction {
    mwseFullscreenHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseEnableHUD : public mwseInstruction {
    mwseEnableHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseDisableHUD : public mwseInstruction {
    mwseDisableHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseChangeHUDTexture : public mwseInstruction {
    mwseChangeHUDTexture(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseChangeHUDEffect : public mwseInstruction {
    mwseChangeHUDEffect(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseFreeHUD : public mwseInstruction {
    mwseFreeHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseNIDLoadHUD : public mwseInstruction {
    mwseNIDLoadHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseNIDPositionHUD : public mwseInstruction {
    mwseNIDPositionHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseNIDScaleHUD : public mwseInstruction {
    mwseNIDScaleHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseNIDFullscreenHUD : public mwseInstruction {
    mwseNIDFullscreenHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseNIDEnableHUD : public mwseInstruction {
    mwseNIDEnableHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseNIDDisableHUD : public mwseInstruction {
    mwseNIDDisableHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseNIDChangeHUDTexture : public mwseInstruction {
    mwseNIDChangeHUDTexture(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseNIDChangeHUDEffect : public mwseInstruction {
    mwseNIDChangeHUDEffect(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseNIDFreeHUD : public mwseInstruction {
    mwseNIDFreeHUD(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseNIDSetHUDEffectLong : public mwseInstruction {
    mwseNIDSetHUDEffectLong(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseNIDSetHUDEffectFloat : public mwseInstruction {
    mwseNIDSetHUDEffectFloat(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};

struct mwseNIDSetHUDEffectVec : public mwseInstruction {
    mwseNIDSetHUDEffectVec(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);
private:
    static vtable_t vtable;
};
