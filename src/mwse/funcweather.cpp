
#include "funcweather.h"
#include "mge/mwbridge.h"
#include "mge/configuration.h"
#include "mge/distantland.h"



struct MWWeather {
    struct RGBfloat {
        float r, g, b;
    };

    void* vtbl;
    int id;
    float transitionDelta, glareView;
    int unk0;

    RGBfloat ambientCol[4];
    RGBfloat fogCol[4];
    RGBfloat skyCol[4];
    RGBfloat sunCol[4];
    RGBfloat sunsetDiscCol;

    int unk1[7];
    float cloudSpeed, windSpeed;
};


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetSkyColour)

// SetWeatherSky <byte weatherID> <byte time_enum> <long red> <long green> <long blue>
// time_enum -> Sunrise = 0, Day = 1, Sunset = 2, Night = 3
bool mwseSetSkyColour::execute(mwseInstruction* _this) {
    VMREGTYPE weather_id, time_enum, r, g, b;

    if (!_this->vmPop(&weather_id)) { return false; }
    if (!_this->vmPop(&time_enum)) { return false; }
    if (!_this->vmPop(&r)) { return false; }
    if (!_this->vmPop(&g)) { return false; }
    if (!_this->vmPop(&b)) { return false; }

    MWWeather* w = (MWWeather*)MWBridge::get()->GetWthrStruct(weather_id);
    if (w && time_enum >= 0 && time_enum <= 3) {
        MWWeather::RGBfloat col = { r / 255.0f , g / 255.0f , b / 255.0f };
        w->skyCol[time_enum] = col;
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetFogColour)

// SetWeatherFog <byte weatherID> <byte time_enum> <long red> <long green> <long blue>
// time_enum -> Sunrise = 0, Day = 1, Sunset = 2, Night = 3
bool mwseSetFogColour::execute(mwseInstruction* _this) {
    VMREGTYPE weather_id, time_enum, r, g, b;

    if (!_this->vmPop(&weather_id)) { return false; }
    if (!_this->vmPop(&time_enum)) { return false; }
    if (!_this->vmPop(&r)) { return false; }
    if (!_this->vmPop(&g)) { return false; }
    if (!_this->vmPop(&b)) { return false; }

    MWWeather* w = (MWWeather*)MWBridge::get()->GetWthrStruct(weather_id);
    if (w && time_enum >= 0 && time_enum <= 3) {
        MWWeather::RGBfloat col = { r / 255.0f , g / 255.0f , b / 255.0f };
        w->fogCol[time_enum] = col;
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetAmbientColour)

// SetWeatherAmbient <byte weatherID> <byte time_enum> <long red> <long green> <long blue>
// time_enum -> Sunrise = 0, Day = 1, Sunset = 2, Night = 3
bool mwseSetAmbientColour::execute(mwseInstruction* _this) {
    VMREGTYPE weather_id, time_enum, r, g, b;

    if (!_this->vmPop(&weather_id)) { return false; }
    if (!_this->vmPop(&time_enum)) { return false; }
    if (!_this->vmPop(&r)) { return false; }
    if (!_this->vmPop(&g)) { return false; }
    if (!_this->vmPop(&b)) { return false; }

    MWWeather* w = (MWWeather*)MWBridge::get()->GetWthrStruct(weather_id);
    if (w && time_enum >= 0 && time_enum <= 3) {
        MWWeather::RGBfloat col = { r / 255.0f , g / 255.0f , b / 255.0f };
        w->ambientCol[time_enum] = col;
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetSunColour)

// SetWeatherSun <byte weatherID> <byte time_enum> <long red> <long green> <long blue>
// time_enum -> Sunrise = 0, Day = 1, Sunset = 2, Night = 3
bool mwseSetSunColour::execute(mwseInstruction* _this) {
    VMREGTYPE weather_id, time_enum, r, g, b;

    if (!_this->vmPop(&weather_id)) { return false; }
    if (!_this->vmPop(&time_enum)) { return false; }
    if (!_this->vmPop(&r)) { return false; }
    if (!_this->vmPop(&g)) { return false; }
    if (!_this->vmPop(&b)) { return false; }

    MWWeather* w = (MWWeather*)MWBridge::get()->GetWthrStruct(weather_id);
    if (w && time_enum >= 0 && time_enum <= 3) {
        MWWeather::RGBfloat col = { r / 255.0f , g / 255.0f , b / 255.0f };
        w->sunCol[time_enum] = col;
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetSunriseSunset)

// SetSunriseSunset <float rise_time> <float rise_duration> <float set_time> <float set_duration>
bool mwseSetSunriseSunset::execute(mwseInstruction* _this) {
    VMFLOAT rise_time, rise_dur, set_time, set_dur;

    if (!_this->vmPop(&rise_time)) { return false; }
    if (!_this->vmPop(&rise_dur)) { return false; }
    if (!_this->vmPop(&set_time)) { return false; }
    if (!_this->vmPop(&set_dur)) { return false; }

    MWBridge::get()->setSunriseSunset(rise_time, rise_dur, set_time, set_dur);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetScattering)

// GetWeatherScattering -> <float outscatter_red> <float outscatter_green> <float outscatter_blue> <float inscatter_red> <float inscatter_geen> <float inscatter_blue>
bool mwseGetScattering::execute(mwseInstruction* _this) {
    _this->vmPush(DistantLand::atmOutscatter.r);
    _this->vmPush(DistantLand::atmOutscatter.g);
    _this->vmPush(DistantLand::atmOutscatter.b);
    _this->vmPush(DistantLand::atmInscatter.r);
    _this->vmPush(DistantLand::atmInscatter.g);
    _this->vmPush(DistantLand::atmInscatter.b);

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetScattering)

// SetWeatherScattering <float outscatter_red> <float outscatter_green> <float outscatter_blue> <float inscatter_red> <float inscatter_geen> <float inscatter_blue>
bool mwseSetScattering::execute(mwseInstruction* _this) {
    VMFLOAT outscatter_r, outscatter_g, outscatter_b;
    VMFLOAT inscatter_r, inscatter_g, inscatter_b;

    if (!_this->vmPop(&outscatter_r)) { return false; }
    if (!_this->vmPop(&outscatter_g)) { return false; }
    if (!_this->vmPop(&outscatter_b)) { return false; }
    if (!_this->vmPop(&inscatter_r)) { return false; }
    if (!_this->vmPop(&inscatter_g)) { return false; }
    if (!_this->vmPop(&inscatter_b)) { return false; }

    RGBVECTOR outscatter(outscatter_r, outscatter_g, outscatter_b), inscatter(inscatter_r, inscatter_g, inscatter_b);
    DistantLand::setScattering(outscatter, inscatter);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetWeatherGlare)

// SetWeatherGlare <byte weatherID> <float glare>
bool mwseSetWeatherGlare::execute(mwseInstruction* _this) {
    VMREGTYPE weather_id;
    VMFLOAT x;

    if (!_this->vmPop(&weather_id)) { return false; }
    if (!_this->vmPop(&x)) { return false; }

    MWWeather* w = (MWWeather*)MWBridge::get()->GetWthrStruct(weather_id);
    w->glareView = x;

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetWeatherCloudSpeed)

// SetWeatherCloudSpeed <byte weatherID> <float speed>
bool mwseSetWeatherCloudSpeed::execute(mwseInstruction* _this) {
    VMREGTYPE weather_id;
    VMFLOAT x;

    if (!_this->vmPop(&weather_id)) { return false; }
    if (!_this->vmPop(&x)) { return false; }

    MWWeather* w = (MWWeather*)MWBridge::get()->GetWthrStruct(weather_id);
    w->cloudSpeed = x;

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetWeatherWindSpeed)

// SetWeatherWindSpeed <byte weatherID> <float speed>
bool mwseSetWeatherWindSpeed::execute(mwseInstruction* _this) {
    VMREGTYPE weather_id;
    VMFLOAT x;

    if (!_this->vmPop(&weather_id)) { return false; }
    if (!_this->vmPop(&x)) { return false; }

    MWWeather* w = (MWWeather*)MWBridge::get()->GetWthrStruct(weather_id);
    w->windSpeed = x;

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetWeatherDLFog)

// GetWeatherDLFog <byte weatherID> -> <float fogDistMultiplier> <float fogOffsetPercent>
bool mwseGetWeatherDLFog::execute(mwseInstruction* _this) {
    VMREGTYPE weather_id;

    if (!_this->vmPop(&weather_id)) { return false; }

    if (weather_id >= 0 && weather_id <= 9) {
        _this->vmPush(Configuration.DL.FogD[weather_id]);
        _this->vmPush(Configuration.DL.FgOD[weather_id]);
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetWeatherDLFog)

// SetWeatherDLFog <byte weatherID> <float fogDistMultiplier> <float fogOffsetPercent>
bool mwseSetWeatherDLFog::execute(mwseInstruction* _this) {
    VMREGTYPE weather_id;
    VMFLOAT dist, offset;

    if (!_this->vmPop(&weather_id)) { return false; }
    if (!_this->vmPop(&dist)) { return false; }
    if (!_this->vmPop(&offset)) { return false; }

    if (weather_id >= 0 && weather_id <= 9) {
        Configuration.DL.FogD[weather_id] = dist;
        Configuration.DL.FgOD[weather_id] = offset;
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetWeatherPPLLight)

// GetWeatherPPLLight <byte weatherID> -> <float sunMultiplier> <float ambientMultiplier>
bool mwseGetWeatherPPLLight::execute(mwseInstruction* _this) {
    VMREGTYPE weather_id;
    VMFLOAT x;

    if (!_this->vmPop(&weather_id)) { return false; }

    if (weather_id >= 0 && weather_id <= 9) {
        _this->vmPush(Configuration.Lighting.SunMult[weather_id]);
        _this->vmPush(Configuration.Lighting.AmbMult[weather_id]);
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetWeatherPPLLight)

// SetWeatherPPLLight <byte weatherID> <float sunMultiplier> <float ambientMultiplier>
bool mwseSetWeatherPPLLight::execute(mwseInstruction* _this) {
    VMREGTYPE weather_id;
    VMFLOAT sun, amb;

    if (!_this->vmPop(&weather_id)) { return false; }
    if (!_this->vmPop(&sun)) { return false; }
    if (!_this->vmPop(&amb)) { return false; }

    if (weather_id >= 0 && weather_id <= 9) {
        Configuration.Lighting.SunMult[weather_id] = sun;
        Configuration.Lighting.AmbMult[weather_id] = amb;
    }

    return true;
}
