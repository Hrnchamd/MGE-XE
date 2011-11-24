
#include "support/log.h"
#include "mgedinput.h"
#include "configuration.h"
#include "mgeversion.h"
#include "mmefunctiondefs.h"
#include "mwbridge.h"

#define ZeroStruct(a) { ZeroMemory(&a,sizeof(a)); }
#define KEYDOWN(name, key) (name[key] & 0x80)


bool MGEProxyDirectInput::mouseClick = false;



typedef void (*FakeFunc)();

FakeFunc FakeFuncs[GRAPHICSFUNCS];      //See GraphicsFuncs enum
sFakeKey FakeKeys[MAXMACROS];     //Last 8 reserved for mouse
sFakeTrigger Triggers[MAXTRIGGERS];   //Up to 4 time lagged triggers
BYTE RemappedKeys[256];

//Fake input device variables
BYTE LastBytes[MAXMACROS];     //Stores which keys were pressed last GetData call
BYTE FakeStates[MAXMACROS];    //Stores which keys are currently permenently down
BYTE HammerStates[MAXMACROS];  //Stores which keys are currently being hammered
BYTE AHammerStates[MAXMACROS]; //Stores the keys that are currently being ahammered
BYTE TapStates[MAXMACROS];     //Stores the keys that need to be tapped next frame
BYTE DisallowStates[MAXMACROS];//Stores which keys are disallowed
DIDEVICEOBJECTDATA FakeBuffer[256]; //Stores the list of fake keypresses to send to console
DWORD FakeBufferStart;      //The index of the next character to write from FakeBuffer[]
DWORD FakeBufferEnd;        //The index of the last character contained in FakeBuffer[]
DWORD TriggerFireTimes[MAXTRIGGERS];
bool FinishedFake;    //true to shut down the console
bool CloseConsole;    //true to shut the console after performing a command
BYTE MouseIn[10];      //Used to transfer keypresses to the mouse
BYTE MouseOut[10];     //Used to transfer keypresses back from the mouse

static bool SkipIntro;
static bool GlobalHammer;
static bool UseAltCombatWrapper;

enum AttackState { State_NONE = 0, State_SLASH, State_PIERCE, State_HACK, State_NONE2  };

bool MadeAttack=false;         // True when the player makes an attack (Because the keyboard must be used before the mouse)
bool MadeAttackLast=false;   // Used in power attacks
int AttackType=0;                    // Used to store the state of the mouse between frames
int LastAttack=0;                     // You cant use the same attack twice in a row
const int altSensitivity = 18;   // How many pixels the mouse must move to register an attack
const int maxGap = 15;          // If the difference between x and y movement is greater than this then dont use a hacking attack



static void stub() {}

void* CreateInputWrapper(void* real)
{
    IDirectInput8A* Real = (IDirectInput8A*)real;

    LOG::logline(">> CreateInputWrapper");

    //Now load all of the fake keys
    DWORD unused;
    HANDLE keyfile=CreateFileA("MGE3\\DInput.data",GENERIC_READ,0,0,OPEN_EXISTING,0,0);

    if (keyfile!=INVALID_HANDLE_VALUE)
    {
        BYTE version;
        ReadFile(keyfile,&version,1,&unused,NULL);

        if(version == MGE_SAVE_VERSION)
        {
            bool DisableConsole;

            ReadFile(keyfile,&SkipIntro,1,&unused,NULL);
            ReadFile(keyfile,&DisableConsole,1,&unused,NULL);
            ReadFile(keyfile,&UseAltCombatWrapper,1,&unused,NULL);
            ReadFile(keyfile,&FakeKeys,sizeof(FakeKeys),&unused,NULL);
            ReadFile(keyfile,&Triggers,sizeof(Triggers),&unused,NULL);
        }
        else
        {
            LOG::logline("MGE\\dinput.data appears to be out of date.\n"
                     "You need to run MGEgui.exe at least once to update the save files.");
        }
        CloseHandle(keyfile);
    }
    else
    {
        LOG::logline("Could not open MGE\\dinput.data for reading.\n"
                 "You need to run MGEgui.exe at least once to create the save files.");
    }

    // Initial state
    GlobalHammer=true;       //Used to hammer keys

    FakeBufferStart=0;
    FakeBufferEnd=0;
    FinishedFake=false;      //true to shut down the console
    CloseConsole=false;      //true to shut the console after performing a command

    ZeroStruct(RemappedKeys);
    ZeroStruct(LastBytes);
    ZeroStruct(FakeStates);
    ZeroStruct(FakeBuffer);
    ZeroStruct(TapStates);

    for(WORD w=0;w<MAXMACROS;w++)
        DisallowStates[w]=0x80;

    for(int i=0;i<MAXTRIGGERS;i++)
        TriggerFireTimes[i]=::GetTickCount()+Triggers[i].TimeInterval;

    // Initialize the array of function pointers
    for(int i = 0; i != GRAPHICSFUNCS; ++i)
        FakeFuncs[i] = stub;

    FakeFuncs[GF_Screenshot] = MacroFunctions::TakeScreenshot;
    FakeFuncs[GF_ToggleZoom] = MacroFunctions::ToggleZoom;
    FakeFuncs[GF_IncreaseZoom] = MacroFunctions::IncreaseZoom;
    FakeFuncs[GF_DecreaseZoom] = MacroFunctions::DecreaseZoom;
    FakeFuncs[GF_ToggleText] = MacroFunctions::ToggleStatusText;
    FakeFuncs[GF_ShowLastText] = MacroFunctions::ShowLastMessage;
    FakeFuncs[GF_ToggleFps] = MacroFunctions::ToggleFpsCounter;
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

    FakeFuncs[GF_HWShader] = MacroFunctions::ToggleShaders;
    FakeFuncs[GF_ToggleDL] = MacroFunctions::ToggleDistantLand;
    FakeFuncs[GF_ToggleDS] = MacroFunctions::ToggleDistantStatics;
    FakeFuncs[GF_ToggleGrass] = MacroFunctions::ToggleGrass;
    FakeFuncs[GF_ToggleMwMgeBlending] = MacroFunctions::ToggleBlending;

    FakeFuncs[GF_MoveForward3PC] = MacroFunctions::MoveForward3PCam;
    FakeFuncs[GF_MoveBack3PC] = MacroFunctions::MoveBack3PCam;
    FakeFuncs[GF_MoveLeft3PC] = MacroFunctions::MoveLeft3PCam;
    FakeFuncs[GF_MoveRight3PC] = MacroFunctions::MoveRight3PCam;
    FakeFuncs[GF_MoveDown3PC] = MacroFunctions::MoveDown3PCam;
    FakeFuncs[GF_MoveUp3PC] = MacroFunctions::MoveUp3PCam;

    // Force screenshots from PrintScreen
    FakeKeys[0xb7].type = FKT_Graphics;
    FakeKeys[0xb7].Graphics.function = GF_Screenshot;

    LOG::logline("<< CreateInputWrapper");
    return new MGEProxyDirectInput(Real);
}


void FakeKeyPress(BYTE key,BYTE data) {
    FakeBuffer[FakeBufferEnd].dwOfs=key;
    FakeBuffer[FakeBufferEnd++].dwData=data;
}

void FakeString(BYTE chars[],BYTE data[],BYTE length) {
    for(int i=0;i<length;i++) {
        FakeKeyPress(chars[i],data[i]);
    }
}


class RemapWrapper : public ProxyInputDevice
{
public:
    RemapWrapper(IDirectInputDevice8 *device) : ProxyInputDevice(device) {}

    HRESULT _stdcall GetDeviceState(DWORD a, void *b)
    {
        BYTE bytes[256];
        HRESULT hr = realDevice->GetDeviceState(256, bytes);
        if(hr != DI_OK) return hr;

        BYTE *b2 = (BYTE*)b;
        ZeroMemory(b, 256);
        for (int i = 0; i < 256; i++)
        {
            if(RemappedKeys[i])
                b2[RemappedKeys[i]] |= bytes[i];
            else
                b2[i] = bytes[i];
        }
        return DI_OK;
    }

    HRESULT _stdcall GetDeviceData(DWORD a, DIDEVICEOBJECTDATA *b ,DWORD *c, DWORD d)
    {
        if (*c != 1 || b == NULL) return realDevice->GetDeviceData(a, b, c, d);

        HRESULT hr = realDevice->GetDeviceData(a, b, c, d);
        if (*c != 1 || hr != DI_OK) return hr;

        if(RemappedKeys[b->dwOfs])
            b->dwOfs = RemappedKeys[b->dwOfs];

        return hr;
    }
};

class MGEProxyKeyboard : public ProxyInputDevice
{
public:
    MGEProxyKeyboard(IDirectInputDevice8* device) : ProxyInputDevice(device) {}

    HRESULT _stdcall GetDeviceState(DWORD a,LPVOID b)
    {
        //This is a keyboard, so get a list of bytes (Dont forget the mouse too)
        BYTE bytes[MAXMACROS];
        HRESULT hr=realDevice->GetDeviceState(256,bytes);
        if (hr!=DI_OK) return hr;
        CopyMemory(&bytes[256],&MouseOut,10);

        //Get any extra key presses
        if (GlobalHammer=!GlobalHammer)
        {
            for (DWORD byte=0;byte<256;byte++)
            {
                bytes[byte]|=FakeStates[byte];
                bytes[byte]|=HammerStates[byte];
                bytes[byte]&=DisallowStates[byte];
                if (TapStates[byte])
                {
                    bytes[byte]=0x80;
                    TapStates[byte]=0;
                }
            }
            for (DWORD byte=256;byte<MAXMACROS-2;byte++)
            {
                bytes[byte]|=FakeStates[byte];
                bytes[byte]|=HammerStates[byte];
            }
        }
        else
        {
            for (DWORD byte=0;byte<256;byte++)
            {
                bytes[byte]|=FakeStates[byte];
                bytes[byte]|=AHammerStates[byte];
                bytes[byte]&=DisallowStates[byte];
                if (TapStates[byte])
                {
                    bytes[byte]=0x80;
                    TapStates[byte]=0;
                }
            }
            for (DWORD byte=256;byte<MAXMACROS-2;byte++)
            {
                bytes[byte]|=FakeStates[byte];
                bytes[byte]|=AHammerStates[byte];
            }
        }
        if (SkipIntro)
        {
        //push escape to skip the intro
            if (GlobalHammer) bytes[0x01]=0x80;
        }
        else if (FinishedFake)
        {
        //Close the console after faking a command (If using console 1 style)
            FinishedFake=false;
            bytes[0x29]=0x80;
        }
        else
        {
        //Process triggers
            DWORD time=::GetTickCount();
            for (DWORD trigger=0;trigger<MAXTRIGGERS;trigger++)
            {
                if (Triggers[trigger].Active&&Triggers[trigger].TimeInterval>0&&TriggerFireTimes[trigger]<time)
                {
                    for (int i=0;i<MAXMACROS;i++)
                    {
                        bytes[i]|=Triggers[trigger].Data.KeyStates[i];
                    }
                    TriggerFireTimes[trigger]=time+Triggers[trigger].TimeInterval;
                }
            }
            //Process each key for keypresses
            for (DWORD key=0;key<MAXMACROS;key++)
            {
                if (FakeKeys[key].type!=FKT_Unused&&KEYDOWN(bytes,key))
                {
                    switch (FakeKeys[key].type)
                    {
                    case FKT_Console1:
                        if (!KEYDOWN(LastBytes,key))
                        {
                            bytes[0x29]=0x80;
                            FakeString(FakeKeys[key].Console.KeyCodes,FakeKeys[key].Console.KeyStates,FakeKeys[key].Console.Length);
                            CloseConsole=true;
                        }
                        break;
                    case FKT_Console2:
                        if (!KEYDOWN(LastBytes,key))
                        {
                            FakeString(FakeKeys[key].Console.KeyCodes,FakeKeys[key].Console.KeyStates,FakeKeys[key].Console.Length);
                            CloseConsole=false;
                        }
                        break;
                    case FKT_Hammer1:
                        for (DWORD byte=0;byte<MAXMACROS;byte++)
                        {
                            if (FakeKeys[key].Press.KeyStates[byte]&&GlobalHammer)
                                bytes[byte]=0x80;
                        }
                        break;
                    case FKT_Hammer2:
                        for (DWORD byte=0;byte<MAXMACROS;byte++)
                        {
                            if (FakeKeys[key].Press.KeyStates[byte])
                                HammerStates[byte]=0x80;
                        }
                        break;
                    case FKT_Unhammer:
                        for (DWORD byte=0;byte<MAXMACROS;byte++)
                        {
                            if (FakeKeys[key].Press.KeyStates[byte])
                                HammerStates[byte]=0x00;
                        }
                        break;
                    case FKT_AHammer1:
                        for (DWORD byte=0;byte<MAXMACROS;byte++)
                        {
                            if (FakeKeys[key].Press.KeyStates[byte]&&!GlobalHammer)
                                bytes[byte]=0x80;
                        }
                        break;
                    case FKT_AHammer2:
                        for (DWORD byte=0;byte<MAXMACROS;byte++)
                        {
                            if (FakeKeys[key].Press.KeyStates[byte])
                                AHammerStates[byte]=0x80;
                        }
                        break;
                    case FKT_AUnhammer:
                        for (DWORD byte=0;byte<MAXMACROS;byte++)
                        {
                            if (FakeKeys[key].Press.KeyStates[byte])
                                AHammerStates[byte]=0x00;
                        }
                        break;
                    case FKT_Press1:
                        for (DWORD byte=0;byte<MAXMACROS;byte++)
                        {
                            if (FakeKeys[key].Press.KeyStates[byte])
                                bytes[byte]=0x80;
                        }
                        break;
                    case FKT_Press2:
                        for (DWORD byte=0;byte<MAXMACROS;byte++)
                        {
                            if (FakeKeys[key].Press.KeyStates[byte])
                                FakeStates[byte]=0x80;
                        }
                        break;
                    case FKT_Unpress:
                        for (DWORD byte=0;byte<MAXMACROS;byte++)
                        {
                            if (FakeKeys[key].Press.KeyStates[byte])
                                FakeStates[byte]=0x00;
                        }
                        break;
                    case FKT_BeginTimer:
                        if (!KEYDOWN(LastBytes,key))
                            Triggers[FakeKeys[key].Timer.TimerID].Active=true;
                        break;
                    case FKT_EndTimer:
                        if (!KEYDOWN(LastBytes,key))
                            Triggers[FakeKeys[key].Timer.TimerID].Active=false;

                        break;
                    case FKT_Graphics:
                        //Want increase/decrease zoom to work at all times
                        if ((!KEYDOWN(LastBytes,key))||(FakeKeys[key].Graphics.function==GF_IncreaseZoom||
                                                        FakeKeys[key].Graphics.function==GF_DecreaseZoom||
                                                        FakeKeys[key].Graphics.function==GF_IncreaseView||
                                                        FakeKeys[key].Graphics.function==GF_DecreaseView||
                                                        FakeKeys[key].Graphics.function==GF_IncreaseAI||
                                                        FakeKeys[key].Graphics.function==GF_DecreaseAI||
                                                        FakeKeys[key].Graphics.function==GF_IncreaseFOV||
                                                        FakeKeys[key].Graphics.function==GF_DecreaseFOV))
                        {
                            (FakeFuncs[FakeKeys[key].Graphics.function])();
                        }
                        break;
                    }
                }
            }
        }
        ::CopyMemory(b,bytes,a);
        ::CopyMemory(LastBytes,bytes,MAXMACROS);
        ::CopyMemory(MouseIn,&bytes[256],10);
        return DI_OK;
    }

    HRESULT _stdcall GetDeviceData(DWORD a,DIDEVICEOBJECTDATA* b,DWORD* c,DWORD d)
    {
        //This only gets called for keyboards
        if (*c==1&&SkipIntro)
        {
        //Skip the second intro (Beats me why it wants buffered data)
            SkipIntro=false;
            FakeBuffer[0].dwOfs=0x01;
            FakeBuffer[0].dwData=0x80;
            *b=FakeBuffer[0];
            return DI_OK;
        }
        else if (*c==1&&FakeBufferEnd>FakeBufferStart)
        {
            //Inject a fake keypress
            *b=FakeBuffer[FakeBufferStart++];
            if (FakeBufferStart==FakeBufferEnd)
            {
                if (CloseConsole)
                {
                    FinishedFake=true;
                    CloseConsole=false;
                }
                FakeBufferStart=0;
                FakeBufferEnd=0;
            }
            return DI_OK;
        }
        else
        {
            //Read a real keypress
            if (*c>1&&!CloseConsole)
            {
                FakeBufferStart=0;
                FakeBufferEnd=0;
            }
            return realDevice->GetDeviceData(a,b,c,d);
        }
    }
};

class MGEProxyMouse : public ProxyInputDevice
{
public:
    DWORD deviceType;

    MGEProxyMouse(IDirectInputDevice8* device) : ProxyInputDevice(device) {}

    HRESULT _stdcall GetDeviceState(DWORD a,LPVOID b)
    {
        DIMOUSESTATE2* MouseState=(DIMOUSESTATE2*)b;
        HRESULT hr=realDevice->GetDeviceState(sizeof(DIMOUSESTATE2),MouseState);
        if (hr!=DI_OK) return hr;

        MGEProxyDirectInput::mouseClick = MouseOut[0] & ~MouseState->rgbButtons[0];

        if (MouseState->lZ>0)
        {
            MouseOut[8]=0x80;
            MouseOut[9]=0;
        }
        else if (MouseState->lZ<0)
        {
            MouseOut[8]=0;
            MouseOut[9]=0x80;
        }
        else
        {
            MouseOut[8]=0;
            MouseOut[9]=0;
        }

        for (DWORD i=0;i<8;i++)
        {
            MouseOut[i]=MouseState->rgbButtons[i];
            MouseState->rgbButtons[i]|=MouseIn[i];
            MouseState->rgbButtons[i]&=DisallowStates[i+256];
            if (TapStates[i+256])
            {
                MouseState->rgbButtons[i]=0x80;
                TapStates[i+256]=0x00;
            }
        }

        return DI_OK;
    }
};

class MGEProxyKeyboardAltCombat : public MGEProxyKeyboard
{
public:
    MGEProxyKeyboardAltCombat(IDirectInputDevice8* device) : MGEProxyKeyboard(device) {}

    HRESULT _stdcall GetDeviceState(DWORD a, void* b)
    {
        HRESULT hr = MGEProxyKeyboard::GetDeviceState(a, b);
        if(hr != DI_OK) return hr;

        DECLARE_MWBRIDGE
        if(mwBridge->IsLoaded() && mwBridge->IsMenu())
            return DI_OK;

        // We only want to modify keyboard input when the player has the mouse held down
        if(AttackType && AttackType != State_NONE2)
        {
            BYTE *bytes = (BYTE*)b;
            bytes[0x1e]=bytes[0x1f]=bytes[0x20]=bytes[0x11]=0;  // Set all movement keys to 0

            // Then set appropriate keys to 0x80 depending on what type of attack is being made
            if(GlobalHammer) {
                if(AttackType==State_SLASH) bytes[0x1e]=0x80;
                if(AttackType==State_PIERCE) bytes[0x11]=0x80;
            } else {
                if(AttackType==State_SLASH) bytes[0x20]=0x80;
                if(AttackType==State_PIERCE) bytes[0x1f]=0x80;
            }

            MadeAttack=true;    //Tell the mouse that an attack has been made, so to press the mouse button
        }
        return DI_OK;
    }
};

class MGEProxyMouseAltCombat : public MGEProxyMouse
{
public:
    MGEProxyMouseAltCombat(IDirectInputDevice8* device) : MGEProxyMouse(device) {}

    HRESULT _stdcall GetDeviceState(DWORD a, void* b)
    {
        HRESULT hr = MGEProxyMouse::GetDeviceState(a, b);
        if(hr != DI_OK) return hr;

        DECLARE_MWBRIDGE
        if(mwBridge->IsLoaded() && mwBridge->IsMenu())
            return DI_OK;

        DIMOUSESTATE2 *MouseState=(DIMOUSESTATE2*)b;

        if(MouseState->rgbButtons[0])
        {
            if(abs(MouseState->lX) > abs(MouseState->lY)+maxGap) MouseState->lY=0;
            if(abs(MouseState->lY) > abs(MouseState->lX)+maxGap) MouseState->lX=0;
            bool slash = abs(MouseState->lX) > altSensitivity;
            bool pierce = abs(MouseState->lY) > altSensitivity;

            DWORD Attack=0x0000;   //Which direction has the mouse moved
            if(MouseState->lX > altSensitivity)  Attack|=0x0001;
            if(MouseState->lX < -altSensitivity) Attack|=0x0010;
            if(MouseState->lY > altSensitivity)  Attack|=0x0100;
            if(MouseState->lY < -altSensitivity) Attack|=0x1000;

            if(MadeAttackLast&&(Attack==LastAttack&&Attack!=0)) {
                MadeAttack=true;
            }
            if(Attack==LastAttack||Attack==0) {
                AttackType=State_NONE2; //Cant attack by moving the mouse in the same direction twice
            } else {
                //Set attacktype appropriately depending on mouse movement
                if(slash&&pierce) {
                    AttackType=State_HACK;
                } else if(slash) {
                    AttackType=State_SLASH;
                } else if(pierce) {
                    AttackType=State_PIERCE;
                } else {
                    //This differentiates between not having the mouse button down, and having the mouse down but not moving it
                    AttackType=State_NONE2;
                }
                LastAttack=Attack;
            }

            MouseState->lX=0;   //Set mouse movement and left button to 0
            MouseState->lY=0;
            MouseState->rgbButtons[0]=0;

            if(MadeAttack) {
                MouseState->rgbButtons[0]=0x80; //If an attack has been made then press the left mouse button
                MadeAttack=false;
            }
            MadeAttackLast=MadeAttack;
        } else {
            // Mouse button isn't down
            AttackType=State_NONE;
            LastAttack=0;
        }
        return DI_OK;
    }
};

IDirectInputDevice8* MGEProxyDirectInput::factoryProxyInput(IDirectInputDevice8* device, REFGUID g)
{
    if(g == GUID_SysKeyboard)
    {
        if(UseAltCombatWrapper)
            device = new MGEProxyKeyboardAltCombat(device);
        else
            device = new MGEProxyKeyboard(device);
        LOG::logline("-- Proxy Keyboard OK");

        HANDLE RemapperFile=CreateFileA("MGE3\\Remap.data",GENERIC_READ,0,0,OPEN_EXISTING,0,0);
        if (RemapperFile != INVALID_HANDLE_VALUE)
        {
            DWORD read;
            ReadFile(RemapperFile, &RemappedKeys, 256, &read, NULL);
            CloseHandle(RemapperFile);

            device = new RemapWrapper(device);
            LOG::logline("-- Re-proxy remapped keyboard");
        }
    }
    else if(g == GUID_SysMouse)
    {
        if(UseAltCombatWrapper)
            device = new MGEProxyMouseAltCombat(device);
        else
            device = new MGEProxyMouse(device);
        LOG::logline("-- Proxy Mouse OK");
    }

    return device;
}
