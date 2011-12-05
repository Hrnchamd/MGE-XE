
#define MAXMACROS 266
#define MAXTRIGGERS 4

class MacroFunctions
{
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
    static void ToggleZoom();
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



enum FakeKeyType {
    FKT_Unused=0,       //This key isn't assigned to anything
    //FD_Console
    FKT_Console1=1,     //Enter console command, exit console
    FKT_Console2=2,     //Dont open or close console
    //FD_Press
    FKT_Hammer1=3,      //Hammer a key while pressed
    FKT_Hammer2=4,      //Start hammering a key
    FKT_Unhammer=5,     //Stop hammering a key
    FKT_AHammer1=6,     //Does the same as hammer, but hits it in alternate frames
    FKT_AHammer2=7,
    FKT_AUnhammer=8,
    FKT_Press1=9,       //Other keys pressed while this is pressed
    FKT_Press2=10,      //Press keys when this is pressed, but dont depress
    FKT_Unpress=11,     //Depress any pressed keys
    //FD_Timer
    FKT_BeginTimer=12,  //Start a timer trigger
    FKT_EndTimer=13,    //End a timer trigger
    //FD_Graphics
    FKT_Graphics=14     //Perform a graphics function
};

enum GraphicsFuncs {
    GF_Screenshot=0,    //Take a screenshot
    GF_Fog=1,           //Toggle fogging
    GF_ScaleFilter=2,   //Cycle the scale filter
    GF_MipFilter=3,     //Cycle the mip filter
    GF_FogMode=4,       //Cycle the fog mode
    GF_AA=5,            //Toggle antialiasing
    GF_CycleAniso=6,    //Cycles anisotropic filtering level
    GF_ToggleZoom=7,   //Toggles zoom on and off
    GF_IncreaseZoom=8, //Increases zoom
    GF_DecreaseZoom=9, //Deceases zoom
    GF_RotateScreen=10, //Rotates the screen
    GF_ToggleText=11,   //toggles status text and fps counter on/off
    GF_ShowLastText=12, //Shows the last bit of text again
    GF_HWShader=13,     //Toggles hardware shaders
    GF_ToggleFps=14,    //Toggle the fps counter
    GF_IncreaseFog=15,  //Increase fogging
    GF_DecreaseFog=16,  //Decrease fogging
    MF_ToggleAltCombat=17,//toggles alternate combat controls
    MF_DelQuickSave=18,   //deletes the quicksave file
    MF_DelAutoSave=19,    //deletes the autosave file
    GF_ToggleAAFix=20,  //Toggle the AA colour fix
    GF_IncreaseView=21, //increase the view distance
    GF_DecreaseView=22, //Decrease the view distance
    GF_IncreaseAI=23,   //Increase the ai distance
    GF_DecreaseAI=24,   //Decrease the ai distance
    GF_IncreaseLOD=25,  //Decreases (yes, I know. lower bias increase LOD) the mipmap bias
    GF_DecreaseLOD=26,  //Increases the mipmap bias
    GF_ToggleCrosshair=27,  //Toggles the crosshair
    GF_NextTrack=28,        //Starts the next music track playing
    GF_DisableMusic=29,     //Sets the music really quiet
    GF_HaggleMore1=30,      //Increases barter amout by 1
    GF_HaggleMore100=31,    //Increases barter amout by 100
    GF_HaggleMore10000=32,  //Increases barter amout by 10000
    GF_HaggleLess1=33,      //Decreases barter amout by 1
    GF_HaggleLess100=34,    //Decreases barter amout by 100
    GF_HaggleLess10000=35,  //Decreases barter amout by 10000
	GF_ToggleDL=36,
    GF_ToggleDS=37,	//Toggle distant statics
    GF_ToggleGrass=38,	//Toggle grass
    GF_ToggleMwMgeBlending=39,//Toggle MW/MGE blending
    GF_CycleWater=40,//Toggle MW/MGE blending
    GF_IncreaseFOV=41,
    GF_DecreaseFOV=42,
    GF_HaggleMore10=43,    //Increases barter amout by 10
    GF_HaggleMore1000=44,    //Increases barter amout by 1000
    GF_HaggleLess10=45,    //Decreases barter amout by 10
    GF_HaggleLess1000=46,    //Decreases barter amout by 1000
    GF_ToggleSkyReflection=47,    //toggle sky reflection in water
    GF_MoveForward3PC = 48,
    GF_MoveBack3PC = 49,
    GF_MoveLeft3PC = 50,
    GF_MoveRight3PC = 51,
    GF_MoveDown3PC = 52,
    GF_MoveUp3PC = 53,
    GRAPHICSFUNCS       //Handy way of getting the number of elements in an enum
};

struct FD_Console {
    BYTE Length;               //The size of the string
    BYTE KeyCodes[MAXMACROS];  //A list of keycodes (This can be a byte because there's never more than 256)
    BYTE KeyStates[MAXMACROS]; //A list of keystates
};
struct FD_Press {
    BYTE KeyStates[MAXMACROS];    //Last 10 for mouse
};
struct FD_Timer {
    BYTE TimerID;           //The timer to activate/deactivate
};
struct FD_Graphics {
    BYTE function; //The GraphicsFuncs to call in the fake d3d dll
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
    BYTE Unused;        //Need this extra byte to avoid packing issues
};
