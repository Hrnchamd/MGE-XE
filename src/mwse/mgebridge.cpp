
#include "mgebridge.h"
#include "funcgeneral.h"
#include "funcgmst.h"
#include "funchud.h"
#include "funczoom.h"
#include "funcweather.h"
#include "funcshader.h"


struct TES3MACHINE;
typedef bool (__fastcall *addInstruction_t)(TES3MACHINE*, int, OPCODE, mwseInstruction*);

static TES3MACHINE *vm;
static addInstruction_t funcAdd;

// perform MSVC thiscall vm->AddInstruction(op, instr)
static bool MWSEAddInstruction(OPCODE op, mwseInstruction *instr)
{
    // uses properties of fastcall to put vm in ecx
    funcAdd(vm, 0, op, instr);
}

void MWSE_MGEPlugin::init(DWORD vm_global, DWORD vm_addinstr)
{
    vm = reinterpret_cast<TES3MACHINE*>(vm_global);
    funcAdd = reinterpret_cast<addInstruction_t>(vm_addinstr);

    MWSEAddInstruction(0x3a00, new mwseGetGS(*vm));
    MWSEAddInstruction(0x3a01, new mwseSetGS(*vm));

    MWSEAddInstruction(0x3a80, new mwseSetSkyColour(*vm));
    MWSEAddInstruction(0x3a81, new mwseSetFogColour(*vm));
    MWSEAddInstruction(0x3a82, new mwseSetAmbientColour(*vm));
    MWSEAddInstruction(0x3a83, new mwseSetSunColour(*vm));
    MWSEAddInstruction(0x3a84, new mwseSetSunriseSunset(*vm));
    MWSEAddInstruction(0x3a85, new mwseSetScattering(*vm));

    MWSEAddInstruction(0x3700, new mwseWipeAll(*vm));
    MWSEAddInstruction(0x3701, new mwseOutputDebugString(*vm));
    MWSEAddInstruction(0x3702, new mwseOutputVersionString(*vm));
    MWSEAddInstruction(0x3703, new mwseGetVersion(*vm));
    MWSEAddInstruction(0x3704, new mwseGetScreenWidth(*vm));
    MWSEAddInstruction(0x3705, new mwseGetScreenHeight(*vm));

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
}
