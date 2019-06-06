#pragma once

#include "mwseinstruction.h"



struct mwseSetSkyColour : public mwseInstruction {
    mwseSetSkyColour(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetFogColour : public mwseInstruction {
    mwseSetFogColour(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetAmbientColour : public mwseInstruction {
    mwseSetAmbientColour(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetSunColour : public mwseInstruction {
    mwseSetSunColour(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetSunriseSunset : public mwseInstruction {
    mwseSetSunriseSunset(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseGetScattering : public mwseInstruction {
    mwseGetScattering(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetScattering : public mwseInstruction {
    mwseSetScattering(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetWeatherGlare : public mwseInstruction {
    mwseSetWeatherGlare(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetWeatherCloudSpeed : public mwseInstruction {
    mwseSetWeatherCloudSpeed(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetWeatherWindSpeed : public mwseInstruction {
    mwseSetWeatherWindSpeed(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseGetWeatherDLFog : public mwseInstruction {
    mwseGetWeatherDLFog(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetWeatherDLFog : public mwseInstruction {
    mwseSetWeatherDLFog(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseGetWeatherPPLLight : public mwseInstruction {
    mwseGetWeatherPPLLight(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};

struct mwseSetWeatherPPLLight : public mwseInstruction {
    mwseSetWeatherPPLLight(TES3MACHINE& mach) : mwseInstruction(mach) {
        vptr = &vtable;
    }
    static bool __thiscall execute(mwseInstruction* _this);

private:
    static vtable_t vtable;
};
