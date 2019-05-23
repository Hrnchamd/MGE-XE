#pragma once

#include "mwseinstruction.h"



struct mwseEnableZoom : public mwseInstruction {
    mwseEnableZoom(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseDisableZoom : public mwseInstruction {
    mwseDisableZoom(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseToggleZoom : public mwseInstruction {
    mwseToggleZoom(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseZoomIn : public mwseInstruction {
    mwseZoomIn(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseZoomOut : public mwseInstruction {
    mwseZoomOut(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseZoomInBy : public mwseInstruction {
    mwseZoomInBy(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseZoomOutBy : public mwseInstruction {
    mwseZoomOutBy(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetZoom : public mwseInstruction {
    mwseSetZoom(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseZoom : public mwseInstruction {
    mwseZoom(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseStopZoom : public mwseInstruction {
    mwseStopZoom(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseGetZoom : public mwseInstruction {
    mwseGetZoom(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseEnableCameraShake : public mwseInstruction {
    mwseEnableCameraShake(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseDisableCameraShake : public mwseInstruction {
    mwseDisableCameraShake(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetCameraShakeMagnitude : public mwseInstruction {
    mwseSetCameraShakeMagnitude(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseCameraShakeAccel : public mwseInstruction {
    mwseCameraShakeAccel(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseStopCameraShakeAccel : public mwseInstruction {
    mwseStopCameraShakeAccel(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseRotateScreenBy : public mwseInstruction {
    mwseRotateScreenBy(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetScreenRotation : public mwseInstruction {
    mwseSetScreenRotation(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseScreenSpin : public mwseInstruction {
    mwseScreenSpin(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseStopScreenSpin : public mwseInstruction {
    mwseStopScreenSpin(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseGetScreenRotation : public mwseInstruction {
    mwseGetScreenRotation(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};
