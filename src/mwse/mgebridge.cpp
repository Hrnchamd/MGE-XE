
#include "funcgeneral.h"
#include "funcgmst.h"
#include "funchud.h"
#include "funccamera.h"
#include "funcweather.h"
#include "funcshader.h"
#include "funcinput.h"
#include "funcentity.h"
#include "funcmwui.h"
#include "funcphysics.h"
#include "mgebridge.h"
#include "mge/api.h"
#include "support/winheader.h"



struct TES3MACHINE;
typedef TES3MACHINE* (*MWSEGetVM_t)();
typedef bool (*MGEInterface_t)(api::MGEAPI*);
typedef bool (*MWSEAddInstruction_t)(OPCODE, mwseInstruction*);
typedef bool (__thiscall* addInstruction_t)(TES3MACHINE*, OPCODE, mwseInstruction*);

static TES3MACHINE* vm;
static addInstruction_t memberAddInstr;


// Perform MSVC thiscall vm->AddInstruction(op, instr) (MWSE 0.9.4a specific)
static bool MWSE94aAddInstruction(OPCODE op, mwseInstruction* instr) {
    return memberAddInstr(vm, op, instr);
}

// Bug: MWSE dynamically creates patch functions using memory allocated on the heap,
// where memory pages are not normally executable.
// Fix: Read MWSE structures and set executable flag on patch functions. (MWSE 0.9.4a specific)
static void fixMWSE94Problems(HMODULE dll) {
    // BreakpointData struct from MWSE source/Breakpoint.cpp
    // Dynamic allocated code is pointed to by overwritten
    struct BreakpointData {
        void* addr;
        DWORD len;
        void* overwritten, *func;
        bool active;
    };
    const int num_bps = 9;

    BreakpointData* bpData = reinterpret_cast<BreakpointData*>((char*)(dll) + 0x56900);
    for (int i = 0; i != num_bps; ++i, ++bpData) {
        void* patch = bpData->overwritten;
        DWORD trueLen = bpData->len + 7, oldProtect;

        VirtualProtect(patch, trueLen, PAGE_EXECUTE_READWRITE, &oldProtect);
    }
}

void MWSE_MGEPlugin::init(HMODULE dll) {
    // Test MWSE for extensibility
    MGEInterface_t MGEInterface = (MGEInterface_t)GetProcAddress(dll, "MGEInterface");
    MWSEGetVM_t MWSEGetVM = (MWSEGetVM_t)GetProcAddress(dll, "MWSEGetVM");
    MWSEAddInstruction_t MWSEAddInstruction = (MWSEAddInstruction_t)GetProcAddress(dll, "MWSEAddInstruction");

    if (MGEInterface) {
        // Create and pass API instance to MWSE 2.1+
        api::api = new api::MGEAPI_ExportVersion();
        MGEInterface(api::api);
    }

    if (MWSEGetVM && MWSEAddInstruction) {
        // Newer, extensible MWSE version
        vm = MWSEGetVM();
    } else {
        // Assume MWSE 0.9.4a, as packaged
        // Hackery; steal MWSE 0.9.4a VM global pointer and VM::AddInstruction member function
        vm = *reinterpret_cast<TES3MACHINE**>((char*)(dll) + 0x595cc);
        memberAddInstr = reinterpret_cast<addInstruction_t>((char*)(dll) + 0x38950);

        // Substitute static function for missing extension function
        MWSEAddInstruction = MWSE94aAddInstruction;

        // Fix access violations in MWSE
        fixMWSE94Problems(dll);
    }

    // New script functions
    MWSEAddInstruction(0x3a00, new mwseGetGS(*vm));
    MWSEAddInstruction(0x3a01, new mwseSetGS(*vm));
    MWSEAddInstruction(0x3a02, new mwseGetBaseHealth(*vm));
    MWSEAddInstruction(0x3a03, new mwseGetBaseMagicka(*vm));
    MWSEAddInstruction(0x3a04, new mwseGetBaseFatigue(*vm));
    MWSEAddInstruction(0x3a05, new mwseGetDeleted(*vm));
    MWSEAddInstruction(0x3a06, new mwseIsScripted(*vm));
    MWSEAddInstruction(0x3a07, new mwseLastActorHit(*vm));
    MWSEAddInstruction(0x3a08, new mwseSetEntityName(*vm));
    MWSEAddInstruction(0x3f11, new mwseSetOwner(*vm));
    MWSEAddInstruction(0x3a09, new mwseModelSwitchNode(*vm));

    MWSEAddInstruction(0x3a10, new mwseUIShow(*vm));
    MWSEAddInstruction(0x3a11, new mwseUIHide(*vm));

    MWSEAddInstruction(0x3a80, new mwseSetSkyColour(*vm));
    MWSEAddInstruction(0x3a81, new mwseSetFogColour(*vm));
    MWSEAddInstruction(0x3a82, new mwseSetAmbientColour(*vm));
    MWSEAddInstruction(0x3a83, new mwseSetSunColour(*vm));
    MWSEAddInstruction(0x3a84, new mwseSetSunriseSunset(*vm));
    MWSEAddInstruction(0x3a85, new mwseSetScattering(*vm));
    MWSEAddInstruction(0x3a86, new mwseSetWeatherGlare(*vm));
    MWSEAddInstruction(0x3a87, new mwseSetWeatherCloudSpeed(*vm));
    MWSEAddInstruction(0x3a88, new mwseSetWeatherWindSpeed(*vm));
    MWSEAddInstruction(0x3a89, new mwseGetScattering(*vm));
    MWSEAddInstruction(0x3a8a, new mwseGetWeatherDLFog(*vm));
    MWSEAddInstruction(0x3a8b, new mwseSetWeatherDLFog(*vm));
    MWSEAddInstruction(0x3a8c, new mwseGetWeatherPPLLight(*vm));
    MWSEAddInstruction(0x3a8d, new mwseSetWeatherPPLLight(*vm));

    MWSEAddInstruction(0x3700, new mwseWipeAll(*vm));
    MWSEAddInstruction(0x3701, new mwseOutputDebugString(*vm));
    MWSEAddInstruction(0x3702, new mwseOutputVersionString(*vm));
    MWSEAddInstruction(0x3703, new mwseGetVersion(*vm));
    MWSEAddInstruction(0x3704, new mwseGetScreenWidth(*vm));
    MWSEAddInstruction(0x3705, new mwseGetScreenHeight(*vm));
    MWSEAddInstruction(0x3707, new mwseGetEyeVec(*vm));

    MWSEAddInstruction(0x370a, new mwseWipeHUDElements(*vm));
    MWSEAddInstruction(0x370b, new mwseWithHUD(*vm));
    MWSEAddInstruction(0x370c, new mwseCancelWithHUD(*vm));
    MWSEAddInstruction(0x370d, new mwseLoadHUD(*vm));
    MWSEAddInstruction(0x370e, new mwsePositionHUD(*vm));
    MWSEAddInstruction(0x370f, new mwseScaleHUD(*vm));
    MWSEAddInstruction(0x3710, new mwseFullscreenHUD(*vm));
    MWSEAddInstruction(0x3711, new mwseEnableHUD(*vm));
    MWSEAddInstruction(0x3712, new mwseDisableHUD(*vm));
    MWSEAddInstruction(0x3713, new mwseChangeHUDTexture(*vm));
    MWSEAddInstruction(0x3714, new mwseChangeHUDEffect(*vm));
    MWSEAddInstruction(0x3715, new mwseFreeHUD(*vm));
    MWSEAddInstruction(0x3716, new mwseNIDLoadHUD(*vm));
    MWSEAddInstruction(0x3717, new mwseNIDPositionHUD(*vm));
    MWSEAddInstruction(0x3718, new mwseNIDScaleHUD(*vm));
    MWSEAddInstruction(0x3719, new mwseNIDFullscreenHUD(*vm));
    MWSEAddInstruction(0x371a, new mwseNIDEnableHUD(*vm));
    MWSEAddInstruction(0x371b, new mwseNIDDisableHUD(*vm));
    MWSEAddInstruction(0x371c, new mwseNIDChangeHUDTexture(*vm));
    MWSEAddInstruction(0x371d, new mwseNIDChangeHUDEffect(*vm));
    MWSEAddInstruction(0x371e, new mwseNIDFreeHUD(*vm));
    MWSEAddInstruction(0x3ac0, new mwseNIDSetHUDEffectLong(*vm));
    MWSEAddInstruction(0x3ac1, new mwseNIDSetHUDEffectFloat(*vm));
    MWSEAddInstruction(0x3ac2, new mwseNIDSetHUDEffectVec(*vm));

    MWSEAddInstruction(0x3733, new mwseTapKey(*vm));
    MWSEAddInstruction(0x3734, new mwsePushKey(*vm));
    MWSEAddInstruction(0x3735, new mwseReleaseKey(*vm));
    MWSEAddInstruction(0x3736, new mwseHammerKey(*vm));
    MWSEAddInstruction(0x3737, new mwseUnhammerKey(*vm));
    MWSEAddInstruction(0x3738, new mwseAHammerKey(*vm));
    MWSEAddInstruction(0x3739, new mwseAUnhammerKey(*vm));
    MWSEAddInstruction(0x373a, new mwseDisallowKey(*vm));
    MWSEAddInstruction(0x373b, new mwseAllowKey(*vm));

    MWSEAddInstruction(0x3756, new mwseEnableCameraShake(*vm));
    MWSEAddInstruction(0x3757, new mwseDisableCameraShake(*vm));
    MWSEAddInstruction(0x3758, new mwseSetCameraShakeMagnitude(*vm));
    MWSEAddInstruction(0x3759, new mwseCameraShakeAccel(*vm));
    MWSEAddInstruction(0x375a, new mwseStopCameraShakeAccel(*vm));
    MWSEAddInstruction(0x3768, new mwseRotateScreenBy(*vm));
    MWSEAddInstruction(0x3769, new mwseSetScreenRotation(*vm));
    MWSEAddInstruction(0x376a, new mwseScreenSpin(*vm));
    MWSEAddInstruction(0x376b, new mwseStopScreenSpin(*vm));
    MWSEAddInstruction(0x376c, new mwseGetScreenRotation(*vm));

    MWSEAddInstruction(0x376d, new mwseEnableZoom(*vm));
    MWSEAddInstruction(0x376e, new mwseDisableZoom(*vm));
    MWSEAddInstruction(0x376f, new mwseToggleZoom(*vm));
    MWSEAddInstruction(0x3770, new mwseZoomIn(*vm));
    MWSEAddInstruction(0x3771, new mwseZoomOut(*vm));
    MWSEAddInstruction(0x3772, new mwseZoomInBy(*vm));
    MWSEAddInstruction(0x3773, new mwseZoomOutBy(*vm));
    MWSEAddInstruction(0x3774, new mwseSetZoom(*vm));
    MWSEAddInstruction(0x3775, new mwseZoom(*vm));
    MWSEAddInstruction(0x3776, new mwseStopZoom(*vm));
    MWSEAddInstruction(0x3777, new mwseGetZoom(*vm));

    MWSEAddInstruction(0x3ab0, new mwseEnableShader(*vm));
    MWSEAddInstruction(0x3ab1, new mwseDisableShader(*vm));
    MWSEAddInstruction(0x3ab2, new mwseSetShaderFloat(*vm));
    MWSEAddInstruction(0x3ab3, new mwseSetShaderLong(*vm));
    MWSEAddInstruction(0x3ab4, new mwseSetShaderVector(*vm));

    MWSEAddInstruction(0x3ae0, new mwseRayTest(*vm));
    MWSEAddInstruction(0x3ae1, new mwseRayTestFrom(*vm));
    MWSEAddInstruction(0x3ae4, new mwseRayHitPosition(*vm));
    MWSEAddInstruction(0x3ae5, new mwseRayHitNormal(*vm));
    MWSEAddInstruction(0x3ae6, new mwseRayHitRef(*vm));
    MWSEAddInstruction(0x3ae8, new mwseModelBounds(*vm));
    MWSEAddInstruction(0x3ae9, new mwseTransformVec(*vm));
    MWSEAddInstruction(0x3aea, new mwseIsAirborne(*vm));
    MWSEAddInstruction(0x3aeb, new mwseSetAirVelocity(*vm));
}
