#pragma once
#ifdef _CONF
#ifndef _INIDATA_H_
#define _INIDATA_H_

#include "configinternal.h"



const char* mgeini = "MGE3/MGE.ini";

const char* sections[] = {
    "Global Graphics",
    "Render State",
    "Input",
    "Misc",
    "Distant Land",
    "Distant Land Weather",
    "Shader Chain",
    "Per Pixel Lighting",
    "Macros",
    "MacrosDesc",
    "InputTriggers",
    "InputRemap"
};

const char* siniGlobGraph = sections[0];
const char* siniRendState = sections[1];
const char* siniInput = sections[2];
const char* siniMisc = sections[3];
const char* siniDL = sections[4];
const char* siniDLWeather = sections[5];
const char* siniShaders = sections[6];
const char* siniPPLighting = sections[7];
const char* siniMacros = sections[8];
const char* siniTriggers = sections[10];
const char* siniRemap = sections[11];

const tdictent dictentBool [] = {
    {False, 0},
    {True, 1},
    {"False", 0},
    {"True", 1},
    {"No", 0},
    {"Yes", 1},
    {"Off", 0},
    {"On", 1}
};
const tdictionary dictBool = {countof(dictentBool), dictentBool};

const tdictent dictentAA [] = {
    {"None", 0},
    {"2x", 2},
    {"4x", 4},
    {"8x", 8},
    {"16x", 16}
};
const tdictionary dictAA = {countof(dictentAA), dictentAA};

const tdictent dictentZBuf [] = {
    {"D24S8", 75},
    {"D24X8", 77},
    {"D32", 71},
    {"D16", 80},
    {"D16L", 70},
    {"D32FL", 82},
    {"INTZ", 1},
    {"RAWZ", 2},
    {"DF16", 3},
    {"DF24", 4}
};
const tdictionary dictZBuf = {countof(dictentZBuf), dictentZBuf};

const tdictent dictentVWait [] = {
    {"Immediate", 255},
    {"1", 1},
    {"2", 2},
    {"3", 4},
    {"4", 8},
};
const tdictionary dictVWait = {countof(dictentVWait), dictentVWait};

const tdictent dictentRefrRate [] = {
    {"Default", 0}
};
const tdictionary dictRefrRate = {countof(dictentRefrRate), dictentRefrRate};

const tdictent dictentAnisoLvl [] = {
    {"Off", 1},
    {"2x", 2},
    {"4x", 4},
    {"8x", 8},
    {"16x", 16}
};
const tdictionary dictAnisoLvl = {countof(dictentAnisoLvl), dictentAnisoLvl};

const tdictent dictentFogMode [] = {
    {"Depth pixel", 0},
    {"Depth vertex", 1},
    {"Range vertex", 2}
};
const tdictionary dictFogMode = {countof(dictentFogMode), dictentFogMode};

const tdictent dictentSSFormat [] = {
    {"BMP", 0},
    {"JPEG", 1},
    {"DDS", 2},
    {"PNG", 3},
    {"TGA", 4}
};
const tdictionary dictSSFormat = {countof(dictentSSFormat), dictentSSFormat};

const tdictent dictentSSSuffix [] = {
    {"Timestamp", 0},
    {"Ordinal", 1},
    {"Character Name, Ordinal", 2},
    {"Character Name, Game Time, Ordinal", 3}
};
const tdictionary dictSSSuffix = {countof(dictentSSSuffix), dictentSSSuffix};

const tdictent dictentPPLFlags [] = {
    {"Always", 0},
    {"Interiors only", 1}
};
const tdictionary dictPPLFlags = {countof(dictentPPLFlags), dictentPPLFlags};



const iniSetting iniSettings[] = {
    // Generic flags
    {&Configuration.MGEFlags, t_bit, MGE_DISABLED_BIT, siniMisc, "MGE Disabled", False, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, MWSE_DISABLED_BIT, siniMisc, "Internal MWSE Disabled", False, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, SKIP_INTRO_BIT, siniMisc, "Skip Intro Movies", True, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, FPS_COUNTER_BIT, siniRendState, "MGE FPS Counter", False, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, DISPLAY_MESSAGES_BIT, siniRendState, "MGE Messages", True, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, USE_MENU_CACHING_BIT, siniMisc, "Use Menu Background Caching", True, &dictBool, DICTONLY, 0, 0},

    // Distant Land flags
    {&Configuration.MGEFlags, t_bit, USE_DISTANT_LAND_BIT, siniDL, "Distant Land", True, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, USE_DISTANT_STATICS_BIT, siniDL, "Distant Statics", True, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, REFLECTIVE_WATER_BIT, siniDL, "Water Reflects Land", True, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, REFLECT_NEAR_BIT, siniDL, "Water Reflects Near Statics", True, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, REFLECT_INTERIOR_BIT, siniDL, "Water Reflects Interiors", False, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, REFLECT_SKY_BIT, siniDL, "Enable Sky Reflections", True, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, DYNAMIC_RIPPLES_BIT, siniDL, "Dynamic Ripples", False, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, BLUR_REFLECTIONS_BIT, siniDL, "Blur Water Reflections", False, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, EXP_FOG_BIT, siniDL, "Use Exponential Fog", False, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, USE_ATM_SCATTER_BIT, siniDL, "Use Atmosphere Scattering", False, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, USE_GRASS_BIT, siniDL, "Render Grass", True, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, USE_SHADOWS_BIT, siniDL, "Sun Shadows", True, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, USE_FFESHADER_BIT, siniDL, "Per Pixel Shader", False, &dictBool, DICTONLY, 0, 0},

    // Renderer options
    {&Configuration.AALevel, t_uint8, 1, siniGlobGraph, "Antialiasing Level", "None", &dictAA, DICTONLY, 0, 0},
    {&Configuration.ZBufFormat, t_uint8, 1, siniGlobGraph, "Z-Buffer Format", "D24S8", &dictZBuf, DICTONLY, 0, 0},
    {&Configuration.VWait, t_uint8, 1, siniGlobGraph, "VWait", "Immediate", &dictVWait, DICTONLY, 0, 0},
    {&Configuration.RefreshRate, t_uint8, 1, siniGlobGraph, "Refresh Rate", "Default", &dictRefrRate, MINMAX, 0, 240},
    {&Configuration.Borderless, t_bool, 1, siniGlobGraph, "Borderless Window", "True", &dictBool, DICTONLY, 0, 0},
    {&Configuration.AnisoLevel, t_uint8, 1, siniRendState, "Anisotropic Filtering Level", "Off", &dictAnisoLvl, DICTONLY, 0, 0},
    {&Configuration.LODBias, t_float, 1, siniRendState, "Mipmap LOD Bias", "0", NULL, MINMAX, -2, 2},
    {&Configuration.ScreenFOV, t_float, 1, siniRendState, "Horizontal Screen FOV", "75", NULL, MINMAX, 5, 150},
    {&Configuration.FogMode, t_uint8, 1, siniRendState, "Fog Mode", "Depth pixel", &dictFogMode, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, TRANSPARENCY_AA_BIT, siniRendState, "Transparency Antialiasing", True, &dictBool, DICTONLY, 0, 0},
    {&Configuration.MGEFlags, t_bit, USE_HW_SHADER_BIT, siniRendState, "Hardware Shader", False, &dictBool, DICTONLY, 0, 0},
    {&Configuration.HDRReactionSpeed, t_float, 1, siniRendState, "HDR Reaction Time", "2", NULL, MINMAX, 0.01, 30},
    {&Configuration.PerPixelLightFlags, t_uint32, 1, siniDL, "Per Pixel Shader Flags", "Always", &dictPPLFlags, DICTONLY, 0, 0},

    // Generic variables
    {&Configuration.SSFormat, t_uint8, 1, siniRendState, "Screenshot Format", "PNG", &dictSSFormat, DICTONLY, 0, 0},
    {&Configuration.SSDir, t_string, sizeof(Configuration.SSDir), siniRendState, "Screenshot Output Directory", "", NULL, 0, 0, 0},
    {&Configuration.SSName, t_string, sizeof(Configuration.SSName), siniRendState, "Screenshot Name Prefix", "Morrowind", NULL, 0, 0, 0},
    {&Configuration.SSSuffix, t_uint8, 1, siniRendState, "Screenshot Name Suffix", "Timestamp", &dictSSSuffix, DICTONLY, 0, 0},
    {&Configuration.StatusTimeout, t_int32, 1, siniRendState, "MGE Messages Timeout", "2000", NULL, MINMAX, 1000, 10000},
    {&Configuration.Force3rdPerson, t_bool, 1, siniMisc, "Customize 3rd Person Camera", "False", &dictBool, DICTONLY, 0, 0},
    {&Configuration.Offset3rdPerson.x, t_float, 1, siniMisc, "Initial 3rd Person Camera X", "0", NULL, MINMAX, -250.0, 250.0},
    {&Configuration.Offset3rdPerson.y, t_float, 1, siniMisc, "Initial 3rd Person Camera Y", "-160", NULL, MINMAX, -2500.0, 2500.0},
    {&Configuration.Offset3rdPerson.z, t_float, 1, siniMisc, "Initial 3rd Person Camera Z", "0", NULL, MINMAX, -250.0, 250.0},
    {&Configuration.CrosshairAutohide, t_bool, 1, siniMisc, "Crosshair Autohide", "False", &dictBool, DICTONLY, 0, 0},
    {&Configuration.UIScale, t_float, 1, siniRendState, "UI Scaling", "1", NULL, MINMAX, 0.5, 5.0},

    // Shaders, flat list
    {&Configuration.ShaderChain, t_set, sizeof(Configuration.ShaderChain), siniShaders, NULL, NULL, NULL, 0, 0, 0},

    // Distant Land, variables
    {&Configuration.DL.DrawDist, t_float, 1, siniDL, "Draw Distance", "5", NULL, MINMAX, 1, 300},
    {&Configuration.DL.NearStaticEnd, t_float, 1, siniDL, "Near Statics End", "2", NULL, MINMAX, 2, 299.8},
    {&Configuration.DL.FarStaticEnd, t_float, 1, siniDL, "Far Statics End", "4", NULL, MINMAX, 2.1, 299.9},
    {&Configuration.DL.VeryFarStaticEnd, t_float, 1, siniDL, "Very Far Statics End", "5", NULL, MINMAX, 2.2, 300},
    {&Configuration.DL.FarStaticMinSize, t_float, 1, siniDL, "Far Static Min Size", "600", NULL, MINMAX, 0, 9999},
    {&Configuration.DL.VeryFarStaticMinSize, t_float, 1, siniDL, "Very Far Static Min Size", "800", NULL, MINMAX, 0, 9999},
    {&Configuration.DL.AboveWaterFogStart, t_float, 1, siniDL, "Above Water Fog Start", "2", NULL, MINMAX, 0, 299.9},
    {&Configuration.DL.AboveWaterFogEnd, t_float, 1, siniDL, "Above Water Fog End", "5", NULL, MINMAX, 0.1, 300},
    {&Configuration.DL.BelowWaterFogStart, t_float, 1, siniDL, "Below Water Fog Start", "-0.5", NULL, MINMAX, -99.9, 299.9},
    {&Configuration.DL.BelowWaterFogEnd, t_float, 1, siniDL, "Below Water Fog End", "0.3", NULL, MINMAX, 0.1, 300},
    {&Configuration.DL.InteriorFogStart, t_float, 1, siniDL, "Interior Fog Start", "0", NULL, MINMAX, -0.9, 9.9},
    {&Configuration.DL.InteriorFogEnd, t_float, 1, siniDL, "Interior Fog End", "2.0", NULL, MINMAX, 0.1, 10},
    {&Configuration.DL.ExpFogDistMult, t_float, 1, siniDL, "Exponential Distance Multiplier", "4.0", NULL, MINMAX, 2.5, 5.0},
    {&Configuration.DL.WaterWaveHeight, t_uint8, 1, siniDL, "Water Wave Height", "0", NULL, MINMAX, 0, 250},
    {&Configuration.DL.WaterCaustics, t_uint8, 1, siniDL, "Water Caustics Intensity", "50", NULL, MINMAX, 0, 100},
    {&Configuration.DL.ShadowResolution, t_uint32, 1, siniDL, "Shadow Resolution", "1024", NULL, MINMAX, 512, 8192},

    // Distant Land, weather
    {&Configuration.DL.Wind[0], t_float, 1, siniDLWeather, "Clear Wind Ratio", "0.1", NULL, MINMAX, 0, 1},
    {&Configuration.DL.FogD[0], t_float, 1, siniDLWeather, "Clear Fog Ratio", "1", NULL, MINMAX, 0.001, 2},
    {&Configuration.DL.FgOD[0], t_float, 1, siniDLWeather, "Clear Fog Offset", "0", NULL, MINMAX, 0, 90},
    {&Configuration.DL.Wind[1], t_float, 1, siniDLWeather, "Cloudy Wind Ratio", "0.2", NULL, MINMAX, 0, 1},
    {&Configuration.DL.FogD[1], t_float, 1, siniDLWeather, "Cloudy Fog Ratio", "0.9", NULL, MINMAX, 0.001, 2},
    {&Configuration.DL.FgOD[1], t_float, 1, siniDLWeather, "Cloudy Fog Offset", "0", NULL, MINMAX, 0, 90},
    {&Configuration.DL.Wind[2], t_float, 1, siniDLWeather, "Foggy Wind Ratio", "0", NULL, MINMAX, 0, 1},
    {&Configuration.DL.FogD[2], t_float, 1, siniDLWeather, "Foggy Fog Ratio", "0.2", NULL, MINMAX, 0.001, 2},
    {&Configuration.DL.FgOD[2], t_float, 1, siniDLWeather, "Foggy Fog Offset", "30", NULL, MINMAX, 0, 90},
    {&Configuration.DL.Wind[3], t_float, 1, siniDLWeather, "Overcast Wind Ratio", "0.2", NULL, MINMAX, 0, 1},
    {&Configuration.DL.FogD[3], t_float, 1, siniDLWeather, "Overcast Fog Ratio", "0.7", NULL, MINMAX, 0.001, 2},
    {&Configuration.DL.FgOD[3], t_float, 1, siniDLWeather, "Overcast Fog Offset", "0", NULL, MINMAX, 0, 90},
    {&Configuration.DL.Wind[4], t_float, 1, siniDLWeather, "Rain Wind Ratio", "0.3", NULL, MINMAX, 0, 1},
    {&Configuration.DL.FogD[4], t_float, 1, siniDLWeather, "Rain Fog Ratio", "0.5", NULL, MINMAX, 0.001, 2},
    {&Configuration.DL.FgOD[4], t_float, 1, siniDLWeather, "Rain Fog Offset", "10", NULL, MINMAX, 0, 90},
    {&Configuration.DL.Wind[5], t_float, 1, siniDLWeather, "Thunderstorm Wind Ratio", "0.5", NULL, MINMAX, 0, 1},
    {&Configuration.DL.FogD[5], t_float, 1, siniDLWeather, "Thunderstorm Fog Ratio", "0.5", NULL, MINMAX, 0.001, 2},
    {&Configuration.DL.FgOD[5], t_float, 1, siniDLWeather, "Thunderstorm Fog Offset", "20", NULL, MINMAX, 0, 90},
    {&Configuration.DL.Wind[6], t_float, 1, siniDLWeather, "Ashstorm Wind Ratio", "0.8", NULL, MINMAX, 0, 1},
    {&Configuration.DL.FogD[6], t_float, 1, siniDLWeather, "Ashstorm Fog Ratio", "0.2", NULL, MINMAX, 0.001, 2},
    {&Configuration.DL.FgOD[6], t_float, 1, siniDLWeather, "Ashstorm Fog Offset", "50", NULL, MINMAX, 0, 90},
    {&Configuration.DL.Wind[7], t_float, 1, siniDLWeather, "Blight Wind Ratio", "0.9", NULL, MINMAX, 0, 1},
    {&Configuration.DL.FogD[7], t_float, 1, siniDLWeather, "Blight Fog Ratio", "0.2", NULL, MINMAX, 0.001, 2},
    {&Configuration.DL.FgOD[7], t_float, 1, siniDLWeather, "Blight Fog Offset", "60", NULL, MINMAX, 0, 90},
    {&Configuration.DL.Wind[8], t_float, 1, siniDLWeather, "Snow Wind Ratio", "0", NULL, MINMAX, 0, 1},
    {&Configuration.DL.FogD[8], t_float, 1, siniDLWeather, "Snow Fog Ratio", "0.5", NULL, MINMAX, 0.001, 2},
    {&Configuration.DL.FgOD[8], t_float, 1, siniDLWeather, "Snow Fog Offset", "40", NULL, MINMAX, 0, 90},
    {&Configuration.DL.Wind[9], t_float, 1, siniDLWeather, "Blizzard Wind Ratio", "0.9", NULL, MINMAX, 0, 1},
    {&Configuration.DL.FogD[9], t_float, 1, siniDLWeather, "Blizzard Fog Ratio", "0.16", NULL, MINMAX, 0.001, 2},
    {&Configuration.DL.FgOD[9], t_float, 1, siniDLWeather, "Blizzard Fog Offset", "70", NULL, MINMAX, 0, 90},

    // Per-pixel lighting
    {&Configuration.Lighting.SunMult[0], t_float, 1, siniPPLighting, "Clear Sun Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.AmbMult[0], t_float, 1, siniPPLighting, "Clear Ambient Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.SunMult[1], t_float, 1, siniPPLighting, "Cloudy Sun Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.AmbMult[1], t_float, 1, siniPPLighting, "Cloudy Ambient Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.SunMult[2], t_float, 1, siniPPLighting, "Foggy Sun Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.AmbMult[2], t_float, 1, siniPPLighting, "Foggy Ambient Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.SunMult[3], t_float, 1, siniPPLighting, "Overcast Sun Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.AmbMult[3], t_float, 1, siniPPLighting, "Overcast Ambient Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.SunMult[4], t_float, 1, siniPPLighting, "Rain Sun Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.AmbMult[4], t_float, 1, siniPPLighting, "Rain Ambient Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.SunMult[5], t_float, 1, siniPPLighting, "Thunderstorm Sun Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.AmbMult[5], t_float, 1, siniPPLighting, "Thunderstorm Ambient Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.SunMult[6], t_float, 1, siniPPLighting, "Ashstorm Sun Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.AmbMult[6], t_float, 1, siniPPLighting, "Ashstorm Ambient Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.SunMult[7], t_float, 1, siniPPLighting, "Blight Sun Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.AmbMult[7], t_float, 1, siniPPLighting, "Blight Ambient Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.SunMult[8], t_float, 1, siniPPLighting, "Snow Sun Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.AmbMult[8], t_float, 1, siniPPLighting, "Snow Ambient Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.SunMult[9], t_float, 1, siniPPLighting, "Blizzard Sun Brightness", "1", NULL, MINMAX, 0, 10},
    {&Configuration.Lighting.AmbMult[9], t_float, 1, siniPPLighting, "Blizzard Ambient Brightness", "1", NULL, MINMAX, 0, 10},

    // Input
    {&Configuration.Input.AltCombat, t_bool, 1, siniMisc, "Daggerfall Combat Controls", "False", &dictBool, DICTONLY, 0, 0},
    {&Configuration.Input.Macros, t_set, sizeof(Configuration.Input.Macros), siniMacros, NULL, NULL, NULL, 0, 0, 0},
    {&Configuration.Input.Triggers, t_set, sizeof(Configuration.Input.Triggers), siniTriggers, NULL, NULL, NULL, 0, 0, 0},
    {&Configuration.Input.Remap, t_set, sizeof(Configuration.Input.Remap), siniRemap, NULL, NULL, NULL, 0, 0, 0}
};

#endif /* _INIDATA_H_ */
#endif /* _CONF */
