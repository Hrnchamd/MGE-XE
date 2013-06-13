
#include "mge/mwbridge.h"
#include "funcweather.h"


struct MWWeather
{
    struct RGBfloat { float r, g, b; };

    int unk0[5];
    RGBfloat ambientCol[4];
    RGBfloat fogCol[4];
    RGBfloat skyCol[4];
    RGBfloat sunCol[4];
};


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetSkyColour)

// SetWeatherSky <byte weatherID> <byte time_enum> <long red> <long green> <long blue>
// time_enum -> Sunrise = 0, Day = 1, Sunset = 2, Night = 3
bool mwseSetSkyColour::execute(mwseInstruction *_this)
{
	VMREGTYPE weather_id, time_enum, r, g, b;

	if(!_this->vmPop(&weather_id)) return false;
	if(!_this->vmPop(&time_enum)) return false;
	if(!_this->vmPop(&r)) return false;
	if(!_this->vmPop(&g)) return false;
	if(!_this->vmPop(&b)) return false;

    DECLARE_MWBRIDGE
    MWWeather *w = (MWWeather *)mwBridge->GetWthrStruct(weather_id);
    MWWeather::RGBfloat col = { r / 255.0f , g / 255.0f , b / 255.0f };
    w->skyCol[time_enum] = col;

	return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetFogColour)

// SetWeatherFog <byte weatherID> <byte time_enum> <long red> <long green> <long blue>
// time_enum -> Sunrise = 0, Day = 1, Sunset = 2, Night = 3
bool mwseSetFogColour::execute(mwseInstruction *_this)
{
	VMREGTYPE weather_id, time_enum, r, g, b;

	if(!_this->vmPop(&weather_id)) return false;
	if(!_this->vmPop(&time_enum)) return false;
	if(!_this->vmPop(&r)) return false;
	if(!_this->vmPop(&g)) return false;
	if(!_this->vmPop(&b)) return false;

    DECLARE_MWBRIDGE
    MWWeather *w = (MWWeather *)mwBridge->GetWthrStruct(weather_id);
    MWWeather::RGBfloat col = { r / 255.0f , g / 255.0f , b / 255.0f };
    w->fogCol[time_enum] = col;

	return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetAmbientColour)

// SetWeatherAmbient <byte weatherID> <byte time_enum> <long red> <long green> <long blue>
// time_enum -> Sunrise = 0, Day = 1, Sunset = 2, Night = 3
bool mwseSetAmbientColour::execute(mwseInstruction *_this)
{
	VMREGTYPE weather_id, time_enum, r, g, b;

	if(!_this->vmPop(&weather_id)) return false;
	if(!_this->vmPop(&time_enum)) return false;
	if(!_this->vmPop(&r)) return false;
	if(!_this->vmPop(&g)) return false;
	if(!_this->vmPop(&b)) return false;

    DECLARE_MWBRIDGE
    MWWeather *w = (MWWeather *)mwBridge->GetWthrStruct(weather_id);
    MWWeather::RGBfloat col = { r / 255.0f , g / 255.0f , b / 255.0f };
    w->ambientCol[time_enum] = col;

	return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetSunColour)

// SetWeatherSun <byte weatherID> <byte time_enum> <long red> <long green> <long blue>
// time_enum -> Sunrise = 0, Day = 1, Sunset = 2, Night = 3
bool mwseSetSunColour::execute(mwseInstruction *_this)
{
	VMREGTYPE weather_id, time_enum, r, g, b;

	if(!_this->vmPop(&weather_id)) return false;
	if(!_this->vmPop(&time_enum)) return false;
	if(!_this->vmPop(&r)) return false;
	if(!_this->vmPop(&g)) return false;
	if(!_this->vmPop(&b)) return false;

    DECLARE_MWBRIDGE
    MWWeather *w = (MWWeather *)mwBridge->GetWthrStruct(weather_id);
    MWWeather::RGBfloat col = { r / 255.0f , g / 255.0f , b / 255.0f };
    w->sunCol[time_enum] = col;

	return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetSunrise)

// SetSunrise <float time> <float duration>
bool mwseSetSunrise::execute(mwseInstruction *_this)
{
    VMFLOAT t, duration;

	if(!_this->vmPop(&t)) return false;
	if(!_this->vmPop(&duration)) return false;

    DECLARE_MWBRIDGE
    mwBridge->setSunriseTimes(t, duration);
	return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetSunset)

// SetSunset <float time> <float duration>
bool mwseSetSunset::execute(mwseInstruction *_this)
{
    VMFLOAT t, duration;

	if(!_this->vmPop(&t)) return false;
	if(!_this->vmPop(&duration)) return false;

    DECLARE_MWBRIDGE
    mwBridge->setSunsetTimes(t, duration);
	return true;
}
