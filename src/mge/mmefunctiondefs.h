#pragma once

const size_t MGEINPUT_MAXMACROS = 256 + 10;
const size_t MGEINPUT_MAXTRIGGERS = 4;

class MacroFunctions {
public:
    static void TakeScreenshot();
    static void ToggleStatusText();
    static void ToggleFpsCounter();
    static void ShowLastMessage();
    static void ToggleBlending();
    static void ToggleShaders();
    static void ToggleDistantLand();
    static void ToggleShadows();
    static void ToggleGrass();
    static void ToggleLightingMode();
    static void ToggleTransparencyAA();
    static void IncreaseViewRange();
    static void DecreaseViewRange();
    static void ToggleZoom();
    static void ResetEnableZoom();
    static void IncreaseZoom();
    static void DecreaseZoom();
    static void ToggleCrosshair();
    static void NextTrack();
    static void DisableMusic();
    static void IncreaseFOV();
    static void DecreaseFOV();
    static void HaggleMore1();
    static void HaggleMore10();
    static void HaggleMore100();
    static void HaggleMore1000();
    static void HaggleMore10000();
    static void HaggleLess1();
    static void HaggleLess10();
    static void HaggleLess100();
    static void HaggleLess1000();
    static void HaggleLess10000();
    static void MoveForward3PCam();
    static void MoveBack3PCam();
    static void MoveLeft3PCam();
    static void MoveRight3PCam();
    static void MoveDown3PCam();
    static void MoveUp3PCam();
};



enum MacroType {
    MT_Unused = 0,                 // This key isn't assigned to anything
    //FD_Console
    MT_Console1 = 1,               // Enter console command, exit console
    MT_Console2 = 2,               // Don't open or close console
    //FD_Press
    MT_Hammer1 = 3,                // Hammer a key while pressed
    MT_Hammer2 = 4,                // Start hammering a key
    MT_Unhammer = 5,               // Stop hammering a key
    MT_AHammer1 = 6,               // Does the same as hammer, but hits it in alternate frames
    MT_AHammer2 = 7,
    MT_AUnhammer = 8,
    MT_Press1 = 9,                 // Other keys pressed while this is pressed
    MT_Press2 = 10,                // Press keys when this is pressed, but dont depress
    MT_Unpress = 11,               // Depress any pressed keys
    //FD_Timer
    MT_BeginTimer = 12,            // Start a timer trigger
    MT_EndTimer = 13,              // End a timer trigger
    //FD_Graphics
    MT_Graphics = 14               // Perform a graphics function
};

const struct MacroTypeLabel {
    const char* label;
    MacroType type;
} macroTypeLabels[] = {
    "Console1", MT_Console1,
    "Console2", MT_Console2,
    "Hammer1", MT_Hammer1,
    "Hammer2", MT_Hammer2,
    "Unhammer", MT_Unhammer,
    "AHammer1", MT_AHammer1,
    "AHammer2", MT_AHammer2,
    "AUnhammer", MT_AUnhammer,
    "Press1", MT_Press1,
    "Press2", MT_Press2,
    "Unpress", MT_Unpress,
    "BeginTimer", MT_BeginTimer,
    "EndTimer", MT_EndTimer,
    "Graphics", MT_Graphics,
    0, MT_Unused                    // Sentinel value
};

enum GraphicsFuncs {
    GF_Screenshot = 0,              // Take a screenshot
    GF_ToggleTrAA = 5,              // Toggles transparency AA
    GF_ToggleZoom = 7,              // Toggles zoom on and off
    GF_IncreaseZoom = 8,            // Increases zoom
    GF_DecreaseZoom = 9,            // Decreases zoom
    GF_ResetEnableZoom = 10,        // Resets zoom level and enables zoom
    GF_ToggleText = 11,             // Toggles status text and fps counter on/off
    GF_ShowLastText = 12,           // Shows the last status text again
    GF_Shader = 13,                 // Toggles post-process shaders
    GF_ToggleFps = 14,              // Toggles the fps counter
    GF_IncreaseView = 21,           // Increase the view distance
    GF_DecreaseView = 22,           // Decrease the view distance
    GF_ToggleCrosshair = 27,        // Toggles the crosshair
    GF_NextTrack = 28,              // Starts the next music track playing
    GF_DisableMusic = 29,           // Sets the music really quiet (due to bug at zero volume)
    GF_HaggleMore1 = 30,            // Increases barter amount by 1
    GF_HaggleMore100 = 31,          // Increases barter amount by 100
    GF_HaggleMore10000 = 32,        // Increases barter amount by 10000
    GF_HaggleLess1 = 33,            // Decreases barter amount by 1
    GF_HaggleLess100 = 34,          // Decreases barter amount by 100
    GF_HaggleLess10000 = 35,        // Decreases barter amount by 10000
    GF_ToggleDL = 36,               // Toggles distant land
    GF_ToggleShadows = 37,          // Toggles dynamic shadows
    GF_ToggleGrass = 38,            // Toggles grass
    GF_ToggleMwMgeBlending = 39,    // Toggles MW/MGE blending
    GF_ToggleLightingMode = 40,     // Toggles enhanced lighting shader
    GF_IncreaseFOV = 41,            // Increases FOV
    GF_DecreaseFOV = 42,            // Decreases FOV
    GF_HaggleMore10 = 43,           // Increases barter amount by 10
    GF_HaggleMore1000 = 44,         // Increases barter amount by 1000
    GF_HaggleLess10 = 45,           // Decreases barter amount by 10
    GF_HaggleLess1000 = 46,         // Decreases barter amount by 1000
    GF_MoveForward3PC = 48,         // Third person camera movement
    GF_MoveBack3PC = 49,
    GF_MoveLeft3PC = 50,
    GF_MoveRight3PC = 51,
    GF_MoveDown3PC = 52,
    GF_MoveUp3PC = 53,
    MGEINPUT_GRAPHICSFUNCS          // Handy way of getting the number of elements in an enum
};

struct FD_Console {
    BYTE Length;                        // The size of the string
    BYTE KeyCodes[MGEINPUT_MAXMACROS];  // A list of keycodes (This can be a byte because there's never more than 256)
    BYTE KeyStates[MGEINPUT_MAXMACROS]; // A list of keystates
};
struct FD_Press {
    BYTE KeyStates[MGEINPUT_MAXMACROS]; // Includes mouse buttons
};
struct FD_Timer {
    BYTE TimerID;                       // The timer to activate/deactivate
};
struct FD_Graphics {
    BYTE function;                      // The GraphicsFunc to call
};

struct sFakeKey {
    BYTE type;
    union {
        FD_Console Console;
        FD_Press Press;
        FD_Timer Timer;
        FD_Graphics Graphics;
    };
};

struct sFakeTrigger {
    DWORD TimeInterval;
    BYTE Active;
    FD_Press Data;
};
