
#include <cstdlib>
#include <cstring>
#include "support/log.h"
#include "mgedinput.h"
#include "configuration.h"
#include "mgeversion.h"
#include "mmefunctiondefs.h"
#include "mwbridge.h"


bool MGEProxyDirectInput::mouseClick = false;


typedef void (*FakeFunc)();

static FakeFunc FakeFuncs[MGEINPUT_GRAPHICSFUNCS];  // See GraphicsFuncs enum
static sFakeKey FakeKeys[MGEINPUT_MAXMACROS];       // Last 10 reserved for mouse
static sFakeTrigger Triggers[MGEINPUT_MAXTRIGGERS]; // Up to 4 time delayed triggers
static BYTE RemappedKeys[256];

// Input device macro variables
static BYTE LastBytes[MGEINPUT_MAXMACROS];          // Which keys were pressed last GetData call
static BYTE FakeStates[MGEINPUT_MAXMACROS];         // Which keys are currently permanently down
static BYTE HammerStates[MGEINPUT_MAXMACROS];       // Which keys are currently being hammered
static BYTE AHammerStates[MGEINPUT_MAXMACROS];      // Which keys are currently being ahammered
static BYTE TapStates[MGEINPUT_MAXMACROS];          // Which keys need to be tapped next frame
static BYTE DisallowMask[MGEINPUT_MAXMACROS];       // Mask of which keys are disallowed
static DIDEVICEOBJECTDATA FakeBuffer[256];          // Stores the list of fake keypresses to send to console
static DWORD FakeBufferStart;                       // The index of the next character to write from FakeBuffer[]
static DWORD FakeBufferEnd;                         // The index of the last character contained in FakeBuffer[]
static DWORD TriggerFireTimes[MGEINPUT_MAXTRIGGERS];
static bool FinishedFake;                           // true to shut down the console
static bool CloseConsole;                           // true to shut the console after performing a command
static BYTE MouseIn[10];                            // Used to transfer keypresses to the mouse
static BYTE MouseOut[10];                           // Used to transfer keypresses back from the mouse

enum AttackState { State_NONE = 0, State_SLASH, State_PIERCE, State_CHOP, State_NOMOTION  };

static struct {
    bool directionPressed;          // True when the player makes an attack (Because the keyboard must be used before the mouse)
    bool directionPressedLast;
    int attackType;                 // Used to store the state of the mouse between frames
    int lastAttack;                 // You cant use the same attack direction twice in a row
} AltCombat = {
    false, false, 0, 0
};

const int altSensitivity = 18;      // How many pixels the mouse must move to register an attack
const int maxGap = 15;              // If the difference between x and y movement is greater than this, don't use a hacking attack

static bool GlobalHammer;



static void loadInputSettings();
static void stub() {}

void* CreateInputWrapper(void* real) {
    LOG::logline(">> CreateInputWrapper");

    // Read macros and triggers
    loadInputSettings();

    // Initial state
    GlobalHammer = true;       // Used to hammer keys (alternates between up/down)

    FakeBufferStart = 0;
    FakeBufferEnd = 0;
    FinishedFake = false;      // true to shut down the console
    CloseConsole = false;      // true to shut the console after performing a command

    ZeroMemory(&LastBytes, sizeof(LastBytes));
    memset(DisallowMask, 0xff, sizeof(DisallowMask));

    for (int i = 0; i != MGEINPUT_MAXTRIGGERS; ++i) {
        TriggerFireTimes[i] = GetTickCount() + Triggers[i].TimeInterval;
    }

    // Initialize the array of macro function pointers
    for (int i = 0; i != MGEINPUT_GRAPHICSFUNCS; ++i) {
        FakeFuncs[i] = stub;
    }

    FakeFuncs[GF_Screenshot] = MacroFunctions::TakeScreenshot;
    FakeFuncs[GF_ToggleZoom] = MacroFunctions::ToggleZoom;
    FakeFuncs[GF_IncreaseZoom] = MacroFunctions::IncreaseZoom;
    FakeFuncs[GF_DecreaseZoom] = MacroFunctions::DecreaseZoom;
    FakeFuncs[GF_ResetEnableZoom] = MacroFunctions::ResetEnableZoom;
    FakeFuncs[GF_ToggleText] = MacroFunctions::ToggleStatusText;
    FakeFuncs[GF_ShowLastText] = MacroFunctions::ShowLastMessage;
    FakeFuncs[GF_ToggleFps] = MacroFunctions::ToggleFpsCounter;
    FakeFuncs[GF_IncreaseView] = MacroFunctions::IncreaseViewRange;
    FakeFuncs[GF_DecreaseView] = MacroFunctions::DecreaseViewRange;
    FakeFuncs[GF_ToggleCrosshair] = MacroFunctions::ToggleCrosshair;
    FakeFuncs[GF_NextTrack] = MacroFunctions::NextTrack;
    FakeFuncs[GF_DisableMusic] = MacroFunctions::DisableMusic;
    FakeFuncs[GF_IncreaseFOV] = MacroFunctions::IncreaseFOV;
    FakeFuncs[GF_DecreaseFOV] = MacroFunctions::DecreaseFOV;

    FakeFuncs[GF_HaggleMore1] = MacroFunctions::HaggleMore1;
    FakeFuncs[GF_HaggleMore10] = MacroFunctions::HaggleMore10;
    FakeFuncs[GF_HaggleMore100] = MacroFunctions::HaggleMore100;
    FakeFuncs[GF_HaggleMore1000] = MacroFunctions::HaggleMore1000;
    FakeFuncs[GF_HaggleMore10000] = MacroFunctions::HaggleMore10000;
    FakeFuncs[GF_HaggleLess1] = MacroFunctions::HaggleLess1;
    FakeFuncs[GF_HaggleLess10] = MacroFunctions::HaggleLess10;
    FakeFuncs[GF_HaggleLess100] = MacroFunctions::HaggleLess100;
    FakeFuncs[GF_HaggleLess1000] = MacroFunctions::HaggleLess1000;
    FakeFuncs[GF_HaggleLess10000] = MacroFunctions::HaggleLess10000;

    FakeFuncs[GF_Shader] = MacroFunctions::ToggleShaders;
    FakeFuncs[GF_ToggleDL] = MacroFunctions::ToggleDistantLand;
    FakeFuncs[GF_ToggleShadows] = MacroFunctions::ToggleShadows;
    FakeFuncs[GF_ToggleGrass] = MacroFunctions::ToggleGrass;
    FakeFuncs[GF_ToggleMwMgeBlending] = MacroFunctions::ToggleBlending;
    FakeFuncs[GF_ToggleLightingMode] = MacroFunctions::ToggleLightingMode;
    FakeFuncs[GF_ToggleTrAA] = MacroFunctions::ToggleTransparencyAA;

    FakeFuncs[GF_MoveForward3PC] = MacroFunctions::MoveForward3PCam;
    FakeFuncs[GF_MoveBack3PC] = MacroFunctions::MoveBack3PCam;
    FakeFuncs[GF_MoveLeft3PC] = MacroFunctions::MoveLeft3PCam;
    FakeFuncs[GF_MoveRight3PC] = MacroFunctions::MoveRight3PCam;
    FakeFuncs[GF_MoveDown3PC] = MacroFunctions::MoveDown3PCam;
    FakeFuncs[GF_MoveUp3PC] = MacroFunctions::MoveUp3PCam;

    // Force screenshots from PrintScreen
    FakeKeys[0xb7].type = MT_Graphics;
    FakeKeys[0xb7].Graphics.function = GF_Screenshot;

    LOG::logline("<< CreateInputWrapper");
    return new MGEProxyDirectInput((IDirectInput8A*)real);
}

void MGEProxyDirectInput::changeKeyBehavior(DWORD key, MGEProxyDirectInput::KeyBehavior kb, bool on) {
    if (key >= MGEINPUT_MAXMACROS) {
        return;
    }

    switch (kb) {
    case MGEProxyDirectInput::TAP:
        TapStates[key] = on ? 0x80 : 0;
        break;
    case MGEProxyDirectInput::PUSH:
        FakeStates[key] = on ? 0x80 : 0;
        break;
    case MGEProxyDirectInput::HAMMER:
        HammerStates[key] = on ? 0x80 : 0;
        break;
    case MGEProxyDirectInput::AHAMMER:
        AHammerStates[key] = on ? 0x80 : 0;
        break;
    case MGEProxyDirectInput::DISALLOW:
        DisallowMask[key] = on ? 0 : 0xff;
        break;
    }
}

static void FakeString(BYTE chars[], BYTE data[], BYTE length) {
    for (int i = 0; i != length; ++i) {
        FakeBuffer[FakeBufferEnd].dwOfs = chars[i];
        FakeBuffer[FakeBufferEnd].dwData = data[i];
        ++FakeBufferEnd;
    }
}


// RemapWrapper: Keyboard remapper
class RemapWrapper : public ProxyInputDevice {
public:
    RemapWrapper(IDirectInputDevice8* device) : ProxyInputDevice(device) {}

    HRESULT _stdcall GetDeviceState(DWORD a, void* b) {
        BYTE bytes[256];
        HRESULT hr = realDevice->GetDeviceState(256, bytes);
        if (hr != DI_OK) {
            return hr;
        }

        BYTE* b2 = (BYTE*)b;
        ZeroMemory(b, 256);
        for (int i = 0; i < 256; i++) {
            if (RemappedKeys[i]) {
                b2[RemappedKeys[i]] |= bytes[i];
            } else {
                b2[i] = bytes[i];
            }
        }
        return DI_OK;
    }

    HRESULT _stdcall GetDeviceData(DWORD a, DIDEVICEOBJECTDATA* b ,DWORD* c, DWORD d) {
        if (*c != 1 || b == NULL) {
            return realDevice->GetDeviceData(a, b, c, d);
        }

        HRESULT hr = realDevice->GetDeviceData(a, b, c, d);
        if (*c != 1 || hr != DI_OK) {
            return hr;
        }

        if (RemappedKeys[b->dwOfs]) {
            b->dwOfs = RemappedKeys[b->dwOfs];
        }

        return hr;
    }
};


// MGEProxyKeyboard: Handles keyboard macros and triggers
class MGEProxyKeyboard : public ProxyInputDevice {
public:
    MGEProxyKeyboard(IDirectInputDevice8* device) : ProxyInputDevice(device) {}

    HRESULT _stdcall GetDeviceState(DWORD a, LPVOID b) {
        // This is a keyboard, so get a list of bytes
        BYTE bytes[MGEINPUT_MAXMACROS];
        HRESULT hr = realDevice->GetDeviceState(256, bytes);
        if (hr != DI_OK) {
            return hr;
        }

        // Copy mouse state to act as an extra 10 keys
        CopyMemory(&bytes[256], &MouseOut, 10);

        // Get any extra key presses
        GlobalHammer = !GlobalHammer;
        const BYTE* hammer = GlobalHammer ? HammerStates : AHammerStates;

        for (DWORD byte = 0; byte < 256; byte++) {
            bytes[byte] |= FakeStates[byte];
            bytes[byte] |= hammer[byte];
            bytes[byte] &= DisallowMask[byte];
            bytes[byte] |= TapStates[byte];
            TapStates[byte] = 0;
        }
        for (DWORD byte = 256; byte < MGEINPUT_MAXMACROS; byte++) {
            bytes[byte] |= FakeStates[byte];
            bytes[byte] |= hammer[byte];
        }

        if (FinishedFake) {
            // Close the console after faking a command (If using console 1 style)
            FinishedFake = false;
            bytes[0x29] = 0x80;
        } else {
            // Process triggers
            DWORD time = GetTickCount();
            for (DWORD trigger = 0; trigger < MGEINPUT_MAXTRIGGERS; trigger++) {
                if (Triggers[trigger].Active && Triggers[trigger].TimeInterval > 0 && TriggerFireTimes[trigger] < time) {
                    for (int i = 0; i < MGEINPUT_MAXMACROS; i++) {
                        bytes[i] |= Triggers[trigger].Data.KeyStates[i];
                    }

                    TriggerFireTimes[trigger] = time + Triggers[trigger].TimeInterval;
                }
            }
            // Process each key for keypresses
            for (DWORD key = 0; key < MGEINPUT_MAXMACROS; key++) {
                if (FakeKeys[key].type != MT_Unused && (bytes[key] & 0x80)) {
                    BYTE last = LastBytes[key] & 0x80;
                    switch (FakeKeys[key].type) {
                    case MT_Console1:
                        if (!last) {
                            bytes[0x29] = 0x80;
                            FakeString(FakeKeys[key].Console.KeyCodes, FakeKeys[key].Console.KeyStates, FakeKeys[key].Console.Length);
                            CloseConsole = true;
                        }
                        break;
                    case MT_Console2:
                        if (!last) {
                            FakeString(FakeKeys[key].Console.KeyCodes, FakeKeys[key].Console.KeyStates, FakeKeys[key].Console.Length);
                            CloseConsole = false;
                        }
                        break;
                    case MT_Hammer1:
                        for (DWORD byte = 0; byte < MGEINPUT_MAXMACROS; byte++) {
                            if (FakeKeys[key].Press.KeyStates[byte] && GlobalHammer) {
                                bytes[byte] = 0x80;
                            }
                        }
                        break;
                    case MT_Hammer2:
                        for (DWORD byte = 0; byte < MGEINPUT_MAXMACROS; byte++) {
                            if (FakeKeys[key].Press.KeyStates[byte]) {
                                HammerStates[byte] = 0x80;
                            }
                        }
                        break;
                    case MT_Unhammer:
                        for (DWORD byte = 0; byte < MGEINPUT_MAXMACROS; byte++) {
                            if (FakeKeys[key].Press.KeyStates[byte]) {
                                HammerStates[byte] = 0x00;
                            }
                        }
                        break;
                    case MT_AHammer1:
                        for (DWORD byte = 0; byte < MGEINPUT_MAXMACROS; byte++) {
                            if (FakeKeys[key].Press.KeyStates[byte] && !GlobalHammer) {
                                bytes[byte] = 0x80;
                            }
                        }
                        break;
                    case MT_AHammer2:
                        for (DWORD byte = 0; byte < MGEINPUT_MAXMACROS; byte++) {
                            if (FakeKeys[key].Press.KeyStates[byte]) {
                                AHammerStates[byte] = 0x80;
                            }
                        }
                        break;
                    case MT_AUnhammer:
                        for (DWORD byte = 0; byte < MGEINPUT_MAXMACROS; byte++) {
                            if (FakeKeys[key].Press.KeyStates[byte]) {
                                AHammerStates[byte] = 0x00;
                            }
                        }
                        break;
                    case MT_Press1:
                        for (DWORD byte = 0; byte < MGEINPUT_MAXMACROS; byte++) {
                            if (FakeKeys[key].Press.KeyStates[byte]) {
                                bytes[byte] = 0x80;
                            }
                        }
                        break;
                    case MT_Press2:
                        for (DWORD byte = 0; byte < MGEINPUT_MAXMACROS; byte++) {
                            if (FakeKeys[key].Press.KeyStates[byte]) {
                                FakeStates[byte] = 0x80;
                            }
                        }
                        break;
                    case MT_Unpress:
                        for (DWORD byte = 0; byte < MGEINPUT_MAXMACROS; byte++) {
                            if (FakeKeys[key].Press.KeyStates[byte]) {
                                FakeStates[byte] = 0x00;
                            }
                        }
                        break;
                    case MT_BeginTimer:
                        if (!last) {
                            Triggers[FakeKeys[key].Timer.TimerID].Active = true;
                        }
                        break;
                    case MT_EndTimer:
                        if (!last) {
                            Triggers[FakeKeys[key].Timer.TimerID].Active = false;
                        }
                        break;
                    case MT_Graphics:
                        // Activate on keydown only, except for certain functions which should repeat
                        if ((!last)||(FakeKeys[key].Graphics.function == GF_IncreaseZoom ||
                                      FakeKeys[key].Graphics.function == GF_DecreaseZoom ||
                                      FakeKeys[key].Graphics.function == GF_IncreaseFOV ||
                                      FakeKeys[key].Graphics.function == GF_DecreaseFOV)) {
                            (FakeFuncs[FakeKeys[key].Graphics.function])();
                        }
                        break;
                    }
                }
            }
        }
        CopyMemory(b, bytes, a);
        CopyMemory(LastBytes, bytes, MGEINPUT_MAXMACROS);
        CopyMemory(MouseIn, &bytes[256], 10);
        return DI_OK;
    }

    HRESULT _stdcall GetDeviceData(DWORD a, DIDEVICEOBJECTDATA* b, DWORD* c, DWORD d) {
        // This only gets called for keyboards
        if (*c == 1 && FakeBufferEnd > FakeBufferStart) {
            // Inject a fake keypress
            *b = FakeBuffer[FakeBufferStart++];
            if (FakeBufferStart == FakeBufferEnd) {
                if (CloseConsole) {
                    FinishedFake = true;
                    CloseConsole = false;
                }
                FakeBufferStart = 0;
                FakeBufferEnd = 0;
            }
            return DI_OK;
        } else {
            // Read a real keypress
            if (*c > 1 && !CloseConsole) {
                FakeBufferStart = 0;
                FakeBufferEnd = 0;
            }
            return realDevice->GetDeviceData(a, b, c, d);
        }
    }
};


// MGEProxyMouse: Maps mouse buttons to macro trigger inputs
class MGEProxyMouse : public ProxyInputDevice {
public:
    DWORD deviceType;

    MGEProxyMouse(IDirectInputDevice8* device) : ProxyInputDevice(device) {}

    HRESULT _stdcall GetDeviceState(DWORD a, LPVOID b) {
        DIMOUSESTATE2* mouseState = (DIMOUSESTATE2*)b;
        HRESULT hr = realDevice->GetDeviceState(sizeof(DIMOUSESTATE2), mouseState);
        if (hr != DI_OK) {
            return hr;
        }

        // Notify application of clicks
        MGEProxyDirectInput::mouseClick = MouseOut[0] & ~mouseState->rgbButtons[0];

        // Map mousewheel to macro triggers 8/9
        if (mouseState->lZ>0) {
            MouseOut[8] = 0x80;
            MouseOut[9] = 0;
        } else if (mouseState->lZ<0) {
            MouseOut[8] = 0;
            MouseOut[9] = 0x80;
        } else {
            MouseOut[8] = 0;
            MouseOut[9] = 0;
        }

        for (DWORD i = 0; i < 8; i++) {
            MouseOut[i] = mouseState->rgbButtons[i];
            mouseState->rgbButtons[i] |= MouseIn[i];
            mouseState->rgbButtons[i] &= DisallowMask[i+256];
            mouseState->rgbButtons[i] |= TapStates[i+256];
            TapStates[i+256] = 0;
        }

        return DI_OK;
    }
};


// MGEProxyKeyboardAltCombat: Keyboard component of Daggerfall-like combat input
class MGEProxyKeyboardAltCombat : public MGEProxyKeyboard {
public:
    MGEProxyKeyboardAltCombat(IDirectInputDevice8* device) : MGEProxyKeyboard(device) {}

    HRESULT _stdcall GetDeviceState(DWORD a, void* b) {
        HRESULT hr = MGEProxyKeyboard::GetDeviceState(a, b);
        if (hr != DI_OK) {
            return hr;
        }

        // Don't run combat input mode when a menu is up
        auto mwBridge = MWBridge::get();
        if (!mwBridge->IsLoaded() || mwBridge->IsMenu()) {
            return DI_OK;
        }

        // We only want to modify keyboard input when the player has the mouse held down
        if (AltCombat.attackType && AltCombat.attackType != State_NOMOTION) {
            BYTE* keyState = (BYTE*)b;

            // Read scancodes for movement keybinds (which can change during play)
            int forward = mwBridge->getKeybindCode(0);
            int back = mwBridge->getKeybindCode(1);
            int left = mwBridge->getKeybindCode(2);
            int right = mwBridge->getKeybindCode(3);

            // Set all movement keys to up state
            keyState[forward] = keyState[back] = keyState[left] = keyState[right] = 0;

            // Then set appropriate keys to pressed depending on what type of attack is being made
            if (GlobalHammer) {
                // AltCombat.attackType == State_CHOP -> no key required
                if (AltCombat.attackType == State_SLASH) {
                    keyState[left] = 0x80;
                }
                if (AltCombat.attackType == State_PIERCE) {
                    keyState[forward] = 0x80;
                }
            } else {
                // AltCombat.attackType == State_CHOP -> no key required
                if (AltCombat.attackType == State_SLASH) {
                    keyState[right] = 0x80;
                }
                if (AltCombat.attackType == State_PIERCE) {
                    keyState[back] = 0x80;
                }
            }

            // Tell the mouse proxy that a swing is ready, so to intiate attack
            AltCombat.directionPressed = true;
        }
        return DI_OK;
    }
};


// MGEProxyMouseAltCombat: Mouse component of Daggerfall-like combat input
class MGEProxyMouseAltCombat : public MGEProxyMouse {
public:
    MGEProxyMouseAltCombat(IDirectInputDevice8* device) : MGEProxyMouse(device) {}

    HRESULT _stdcall GetDeviceState(DWORD a, void* b) {
        HRESULT hr = MGEProxyMouse::GetDeviceState(a, b);
        if (hr != DI_OK) {
            return hr;
        }

        // Don't run combat input mode when a menu is up
        auto mwBridge = MWBridge::get();
        if (!mwBridge->IsLoaded() || mwBridge->IsMenu()) {
            return DI_OK;
        }

        // Capture mouse movement while mouse is pressed
        // Skip/cancel if a ranged weapon is equipped
        DIMOUSESTATE2* mouseState = (DIMOUSESTATE2*)b;
        bool ranged = mwBridge->getPlayerWeapon() >= 9;

        if (mouseState->rgbButtons[0] && !ranged) {
            // If the difference between x and y movement is greater than maxGap, prefer slash over chop
            if (abs(mouseState->lX) > abs(mouseState->lY)+maxGap) {
                mouseState->lY = 0;
            }

            bool slash = abs(mouseState->lX) > altSensitivity;
            bool pierce = abs(mouseState->lY) > altSensitivity;

            int attack = 0;   // Which direction has the mouse moved
            if (mouseState->lX > altSensitivity) {
                attack |= 0x0001;
            }
            if (mouseState->lX < -altSensitivity) {
                attack |= 0x0010;
            }
            if (mouseState->lY > altSensitivity) {
                attack |= 0x0100;
            }
            if (mouseState->lY < -altSensitivity) {
                attack |= 0x1000;
            }

            if (AltCombat.directionPressedLast && attack == AltCombat.lastAttack && attack != 0) {
                AltCombat.directionPressed = true;
            }

            if (attack == AltCombat.lastAttack || attack == 0) {
                AltCombat.attackType = State_NOMOTION;  // Can't attack by moving the mouse in the same direction twice
            } else {
                // Set attack type appropriately depending on mouse movement
                if (slash && pierce) {
                    AltCombat.attackType = State_CHOP;
                } else if (slash) {
                    AltCombat.attackType = State_SLASH;
                } else if (pierce) {
                    AltCombat.attackType = State_PIERCE;
                } else {
                    // This differentiates between not having the mouse button down, and having the mouse down but not moving it
                    AltCombat.attackType = State_NOMOTION;
                }
                AltCombat.lastAttack = attack;
            }

            // Don't pass mouse movement and left button state to Morrowind
            mouseState->lX = 0;
            mouseState->lY = 0;
            mouseState->rgbButtons[0] = 0;

            // If the correct movement key is down then press the left mouse button
            if (AltCombat.directionPressed) {
                mouseState->rgbButtons[0] = 0x80;
            }

            AltCombat.directionPressedLast = AltCombat.directionPressed;
        } else {
            // Mouseup state passes through to finish attacks

            // Reset alt combat on mouse up / ranged
            AltCombat.directionPressed = false;
            AltCombat.directionPressedLast = false;
            AltCombat.attackType = State_NONE;
            AltCombat.lastAttack = 0;
        }
        return DI_OK;
    }
};



IDirectInputDevice8* MGEProxyDirectInput::factoryProxyInput(IDirectInputDevice8* device, REFGUID g) {
    if (g == GUID_SysKeyboard) {
        if (Configuration.Input.AltCombat) {
            device = new MGEProxyKeyboardAltCombat(device);
        } else {
            device = new MGEProxyKeyboard(device);
        }
        LOG::logline("-- Proxy Keyboard OK");

        if (Configuration.Input.Remap[0] != 0) {
            device = new RemapWrapper(device);
            LOG::logline("-- Remapped keyboard");
        }
    } else if (g == GUID_SysMouse) {
        if (Configuration.Input.AltCombat) {
            device = new MGEProxyMouseAltCombat(device);
        } else {
            device = new MGEProxyMouse(device);
        }
        LOG::logline("-- Proxy Mouse OK");
    }

    return device;
}


// Input config parser

static bool entryParse(char* text, char prefix, size_t* key, const char** values, size_t* value_count) {
    // Split line into <key>=<values>
    char* sep = std::strchr(text, '=');
    if (sep == NULL || *text != prefix) {
        return false;
    }

    // In-place convert comma-separated list into null-terminated strings
    size_t c = 0;
    for (char* v = sep + 1; v; ++c) {
        v = std::strchr(v, ',');
        if (v) {
            *v++ = 0;
        }
    }

    *key = std::atoi(text + 1);
    *values = sep + 1;
    *value_count = c;
    return true;
}


static const char* entryNextValue(const char* s) {
    return s + strlen(s) + 1;
}

static void loadInputSettings() {
    size_t seek;
    for (char* line = Configuration.Input.Macros; *line; line += seek) {
        size_t key, value_count;
        const char* values;
        seek = strlen(line) + 1;

        if (!entryParse(line, 'M', &key, &values, &value_count)) {
            continue;
        }
        if (value_count < 2 || key >= MGEINPUT_MAXMACROS) {
            continue;
        }

        sFakeKey* macro = &FakeKeys[key];
        for (const MacroTypeLabel* x = macroTypeLabels; x->label; ++x) {
            if (std::strcmp(values, x->label) == 0) {
                macro->type = x->type;
                break;
            }
        }

        switch (macro->type) {
        case MT_Console1:
        case MT_Console2:
            macro->Console.Length = 0;
            for (size_t i = 2; i < value_count; i += 2, ++macro->Console.Length) {
                values = entryNextValue(values);
                macro->Console.KeyCodes[macro->Console.Length] = std::atoi(values);
                values = entryNextValue(values);
                macro->Console.KeyStates[macro->Console.Length] = (std::strcmp(values, "True") == 0) ? 0x80 : 0;
            }
            break;
        case MT_Press1:
        case MT_Press2:
        case MT_Unpress:
        case MT_Hammer1:
        case MT_Hammer2:
        case MT_Unhammer:
        case MT_AHammer1:
        case MT_AHammer2:
        case MT_AUnhammer:
            for (size_t i = 1; i < value_count; ++i) {
                values = entryNextValue(values);
                macro->Press.KeyStates[std::atoi(values)] = 0x80;
            }
            break;
        case MT_BeginTimer:
        case MT_EndTimer:
            macro->Timer.TimerID = std::atoi(entryNextValue(values));
            break;
        case MT_Graphics:
            macro->Graphics.function = std::atoi(entryNextValue(values));
            break;
        }
    }

    for (char* line = Configuration.Input.Triggers; *line; line += seek) {
        size_t key, value_count;
        const char* values;
        seek = strlen(line) + 1;

        if (!entryParse(line, 'T', &key, &values, &value_count)) {
            continue;
        }
        if (value_count < 2 || key >= MGEINPUT_MAXTRIGGERS) {
            continue;
        }

        sFakeTrigger* trigger = &Triggers[key];

        trigger->Active = (std::strcmp(values, "True") == 0);
        values = entryNextValue(values);
        trigger->TimeInterval = 1000 * std::atoi(values);

        for (size_t i = 2; i < value_count; ++i) {
            values = entryNextValue(values);
            trigger->Data.KeyStates[std::atoi(values)] = 0x80;
        }
    }

    for (char* line = Configuration.Input.Remap; *line; line += seek) {
        size_t key, value_count;
        const char* values;
        seek = strlen(line) + 1;

        if (!entryParse(line, 'R', &key, &values, &value_count)) {
            continue;
        }
        if (value_count != 1 || key >= 256) {
            continue;
        }

        RemappedKeys[key] = std::atoi(values);
    }
}
