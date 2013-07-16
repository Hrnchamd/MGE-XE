#ifndef _MW_BRIDGE_H_
#define _MW_BRIDGE_H_

#include "proxydx/d3d8header.h"

#define DECLARE_MWBRIDGE MWBridge* mwBridge = MWBridge::Inst();

//-----------------------------------------------------------------------------

class MWBridge {
public:
    ~MWBridge();

    // Singleton access
    static MWBridge* Inst();

    // Connect to Morrowind memory
    void Load();

    // Used to determine whether we have connected to Morrowind's dynamic memory yet
    inline bool IsLoaded();
    bool CanLoad();

    DWORD GetAlwaysRun();
    DWORD GetAutoRun();
    DWORD GetShadowToggleAddr();
    DWORD GetShadowRealAddr();
    DWORD GetShadowFovAddr();
    DWORD GetCrosshair2();
    void SetCrosshairEnabled(bool enabled);
    void ToggleCrosshair();
    bool IsExterior();
    bool IsMenu();
    bool IsLoadScreen();
    bool IsCombat();
    bool IsCrosshair();
    bool IsAlwaysRun();

    DWORD GetNextTrack();
    DWORD GetMusicVol();
    void SkipToNextTrack();
    void DisableMusic();

    DWORD GetCurrentWeather();
    DWORD GetNextWeather();
    float GetWeatherRatio();
    RGBVECTOR* CurSkyColVector();
    RGBVECTOR* CurFogColVector();
    void setSceneFogCol(DWORD c);
    bool CellHasWeather();
    float* GetWindVector();
    DWORD WthrStruc(int wthr);
    int GetWthrString(int wthr, int offset, char str[]);
    void SetWthrString(int wthr, int offset, char str[]);
    bool CellHasWater();
    bool IsUnderwater(float eyeZ);
    bool WaterReflects(float eyeZ);
    float simulationTime();
    float frameTime();

    float GetViewDistance();
    void SetViewDistance(float dist);
    float GetAIDistance();
    void SetAIDistance(float dist);

    void SetFOV(float screenFOV);

    void GetSunDir(float& x, float& y, float& z);
    BYTE GetSunVis();
    float GetSunriseHour();
    void SetSunriseHour(float hour);
    float GetSunriseDuration();
    void SetSunriseDuration(float duration);
    float GetSunsetHour();
    void SetSunsetHour(float hour);
    float GetSunsetDuration();
    void SetSunsetDuration(float duration);

    DWORD IntCurCellAddr();
    bool IntLikeExterior();
    bool IntIllegSleep();
    bool IntHasWater();
    float WaterLevel();

    const char * getInteriorName();
    const BYTE * getInteriorAmb();
    const BYTE * getInteriorSun();
    const BYTE * getInteriorFog();
    float getInteriorFogDens();

    DWORD PlayerPositionPointer();
    float PlayerPositionX();
    float PlayerPositionY();
    float PlayerPositionZ();
    float PlayerHeight();
    bool IsPlayerWaiting();
    D3DXVECTOR3 * PCam3Offset();
    DWORD getPlayerMACP();
    bool is3rdPerson();
    DWORD getPlayerTarget();
    int getPlayerWeapon();
    bool isPlayerCasting();
    bool isPlayerAimingWeapon();

    void HaggleMore(DWORD num);
    void HaggleLess(DWORD num);

    void toggleRipples(BOOL enabled);
    void markWaterNode(float k);
    void markMoonNodes(float k);
    void disableScreenshotFunc();
    void disableSunglare();
    bool isIntroDone();
    bool isLoadingSplash();
    void redirectMenuBackground(void (_stdcall *func)(int));

    void *getGMSTPointer(DWORD id);
    DWORD getKeybindCode(DWORD action);

    MWBridge();

protected:
    DWORD m_version;
    bool m_loaded;

    /// Sets pointers to static memory of Morrowind
    void InitStaticMemory();

    /// Functions for reading and writing data at locations in Morrowind's memory
    DWORD read_dword(const DWORD dwAddress);
    WORD read_word(const DWORD dwAddress);
    BYTE read_byte(const DWORD dwAddress);
    float read_float(const DWORD dwAddress);
    void write_dword(const DWORD dwAddress, DWORD dword);
    void write_word(const DWORD dwAddress, WORD word);
    void write_byte(const DWORD dwAddress, BYTE byte);
    void write_float(const DWORD dwAddress, float f);

    /// Pointers to Morrowind Memory
    DWORD
        eMaster, eEnviro, eMaster1, eMaster2,
        eFPS, eTimer, eD3D, eTruRenderWidth, eShadowSlider,
        eCrosshair1, eAI, eView0, eRenderWidth,
        eView1, eCombat, ePCRef,

        eGamma, eView4, eLookMenu,

        eX, eCos, eWorldFOV, eView2,

        eSkyFOV, eMenuFOV, eView3, eExt, eMenu, eMouseLim,

        eLoad,

        eWthrArray, eCurWthrStruct, eNextWthrStruct,
        eCurSkyCol, eCurFogCol,
        eWindVector,
        eSunriseHour, eSunsetHour, eSunriseDuration, eSunsetDuration,
        eSunDir, eSunVis, //real sun direction, sun(glare) alpha value
        eWeatherRatio;

    // floating point variables
    DWORD eNextTrack, eMusicVol,
        eAlwaysRun, eAutoRun,
        eShadowToggle, eShadowReal, eShadowFOV,
        eCrosshair2;

    // Pointers to Morrowind code
    DWORD eNoMusicBreak,
        eGammaFunc,
        eMusicVolFunc,
        eHaggleMore, eHaggleLess,
        eMenuMouseMove,
        eTruform, eGetMouseState,
        eXMenuHudIn, eXMenuHudOut, eXMenuNoMouse, eXMenuNoFOV,
        eXMenuWnds, eXMenuPopups, eXMenuLoWnds, eXMenuSubtitles, eXMenuFPS,
        eNoWorldFOV, eXRotSpeed, eYRotSpeed,
        eScrollScale, eBookScale, eJournalScale, eRipplesSwitch;

    // Other values
    DWORD dwAlwaysRunOffset;
};

//-----------------------------------------------------------------------------
// Inline Functions
//-----------------------------------------------------------------------------

inline bool MWBridge::IsLoaded() {
    return m_loaded;
}

//-----------------------------------------------------------------------------


#endif
