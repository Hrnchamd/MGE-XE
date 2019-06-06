// This file contains code from fps optimizer
// Memory layout originally worked out by Alexander Stasenko

#include "mwbridge.h"
#include "assert.h"

#include <cmath>



static MWBridge m_instance;


class VirtualMemWriteAccessor {
    void* address;
    size_t length;
    DWORD oldProtect;

public:
    VirtualMemWriteAccessor(void* addr, size_t len) : address(addr), length(len) {
        VirtualProtect(address, length, PAGE_EXECUTE_READWRITE, &oldProtect);
    }
    ~VirtualMemWriteAccessor() {
        VirtualProtect(address, length, oldProtect, &oldProtect);
    }
};

//-----------------------------------------------------------------------------

MWBridge::MWBridge() {
    memset(this, 0, sizeof(*this));
    m_loaded = false;
    m_version = 0;
    InitStaticMemory();
}

//-----------------------------------------------------------------------------

MWBridge::~MWBridge() {
}

//-----------------------------------------------------------------------------

MWBridge* MWBridge::get() {
    return &m_instance;
}

//-----------------------------------------------------------------------------

void MWBridge::InitStaticMemory() {
    // Bloodmoon v. 1080
    eNoMusicBreak = 0x00403659;
    eMusicVolFunc = 0x00403a10;
    eHaggleMore = 0x005A73D0;
    eTruform = 0x006e4ffc;
    eGetMouseState = 0x00406721;
    eNoWorldFOV = 0x004049fe;
    eXRotSpeed = 0x005692b1;
    eYRotSpeed = eXRotSpeed + 0x11C;
    eScrollScale = 0x006139b6;
    eBookScale = 0x005ac47b;
    eRipplesSwitch = 0x0051C2D4;

    eXMenuHudIn = 0x005f43c4;
    eXMenuNoMouse = 0x00408740;
    eXMenuNoFOV = 0x00404b38;
    eXMenuWnds = 0x00583072;
    eXMenuPopups = 0x005961AC;
    eXMenuLoWnds = 0x00586985;
    eXMenuSubtitles = 0x005f980f;
    eXMenuFPS = 0x0041bc5e;

    dwAlwaysRunOffset = 0x5B4;

    eMaster = 0x007C67DC;
    eEnviro = eMaster + 0x4;
    eLoad = eMaster + 0x1DDC;

    eHaggleLess  = eHaggleMore + 0xF0;
    eXMenuHudOut = eXMenuHudIn + 0x448;
    eMenuMouseMove = eXMenuNoMouse + 0xE0;
    eJournalScale = eBookScale + 0xF5;
}

//-----------------------------------------------------------------------------

void MWBridge::Load() {
    // Standard Morrowind
    DWORD dwTruRenderWidthOff = 0x48;
    DWORD dwHRotScaleOff = 0x50;

    eMaster1 = read_dword(eMaster);
    eMaster2 = read_dword(eMaster + 0x500);

    eFPS = eMaster1 + 0x14;
    eTimer = eFPS + 0xC;
    eD3D = eTimer + 0x10;
    ePCRef = eD3D + 0x2C;
    eTruRenderWidth = eD3D + dwTruRenderWidthOff;
    eShadowSlider = eTruRenderWidth + 0xC;
    eCrosshair1 = eShadowSlider + 0x10;
    eAI = eCrosshair1 + 0x4;
    eMenu = eMaster1 + 0xD6;
    eView0 = eAI + dwHRotScaleOff + 0x5C;
    eRenderWidth = eView0 + 0x4;
    eView1 = eRenderWidth + 0x188;
    eCombat = eView1 + 0x80;

    eGamma = eMaster2 + 0x3C;
    eView4 = eGamma + 0x10;
    eLookMenu = eView4 + 0x9C;

    eX = read_dword(eView0 - 0x10) + 0x1C;
    eCos = eX + 0xD4;
    eWorldFOV = eCos + 0x10;
    eView2 = eWorldFOV + 0x14;

    eSkyFOV = read_dword(eRenderWidth + 0x18) + 0x100;
    eMenuFOV = read_dword(eRenderWidth + 0x44) + 0x100;

    eView3 = read_dword(eView1 - 0x10) + 0x114;
    eExt = read_dword(eView1 + 0x10) + 0x10;
    eMouseLim = read_dword(eD3D + 0x20) + 0x24;

    eGammaFunc = read_dword(read_dword(eMaster2) + 0x50);

    eWthrArray = read_dword(eMaster1 + 0x58) + 0x14;
    eCurWthrStruct = eWthrArray + 0x28;  // 0x3c
    eNextWthrStruct = eCurWthrStruct + 0x04;  // 0x40
    eCurSkyCol = eNextWthrStruct + 0x50;  // 0x90
    eCurFogCol = eNextWthrStruct + 0x5c;  // 0x9c
    eWindVector = eNextWthrStruct + 0x78;  // 0xb8
    eSunriseHour = eNextWthrStruct + 0x9c;  // 0xdc
    eSunsetHour = eNextWthrStruct + 0xa0;  // 0xe0
    eSunriseDuration = eNextWthrStruct + 0xa4;  // 0xe4
    eSunsetDuration = eNextWthrStruct + 0xa8;  // 0xe8
    eWeatherRatio = eNextWthrStruct + 0x130;  // 0x170

    eSunDir = read_dword(eWthrArray - 0x14) + 0x30;
    eSunVis = read_dword(read_dword(read_dword(eWthrArray + 0x74)+0x98)+0x24)+0x3;

    m_loaded = true;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::read_dword(const DWORD dwAddress) {
    return *reinterpret_cast<DWORD*>(dwAddress);
}

//-----------------------------------------------------------------------------

WORD MWBridge::read_word(const DWORD dwAddress) {
    return *reinterpret_cast<WORD*>(dwAddress);
}

//-----------------------------------------------------------------------------

BYTE MWBridge::read_byte(const DWORD dwAddress) {
    return *reinterpret_cast<BYTE*>(dwAddress);
}

//-----------------------------------------------------------------------------

float MWBridge::read_float(const DWORD dwAddress) {
    return *reinterpret_cast<float*>(dwAddress);
}

//-----------------------------------------------------------------------------

void MWBridge::write_dword(const DWORD dwAddress, DWORD dword) {
    *reinterpret_cast<DWORD*>(dwAddress) = dword;
}

//-----------------------------------------------------------------------------

void MWBridge::write_word(const DWORD dwAddress, WORD word) {
    *reinterpret_cast<WORD*>(dwAddress) = word;
}

//-----------------------------------------------------------------------------

void MWBridge::write_byte(const DWORD dwAddress, BYTE byte) {
    *reinterpret_cast<BYTE*>(dwAddress) = byte;
}

//-----------------------------------------------------------------------------

void MWBridge::write_float(const DWORD dwAddress, float f) {
    *reinterpret_cast<float*>(dwAddress) = f;
}

//-----------------------------------------------------------------------------

void MWBridge::write_ptr(const DWORD dwAddress, void* ptr) {
    *reinterpret_cast<void**>(dwAddress) = ptr;
}

//-----------------------------------------------------------------------------

bool MWBridge::CanLoad() {
    // reads static address, so game doesn't need to be loaded
    return read_dword(eEnviro) != 0;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetAlwaysRun() {
    assert(m_loaded);
    return read_dword(read_dword(read_dword(eD3D + 0x2C) + 0x24)) + dwAlwaysRunOffset;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetAutoRun() {
    assert(m_loaded);
    return GetAlwaysRun() + 4;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetShadowToggleAddr() {
    assert(m_loaded);
    DWORD addr = read_dword(eView1 + 0xC);
    return addr ?  (addr + 0xC) : 0;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetShadowRealAddr() {
    assert(m_loaded);
    DWORD addr = read_dword(eView1 + 0xC);
    return addr ?  (addr + 0x14) : 0;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetShadowFovAddr() {
    assert(m_loaded);

    eShadowFOV = read_dword (eView1 + 0xC);
    if (eShadowFOV) {
        eShadowFOV = read_dword (eShadowFOV + 0x8);
        if (eShadowFOV) {
            eShadowFOV += 0x100;
        }
    }
    return eShadowFOV;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetCrosshair2() {
    assert(m_loaded);
    return read_dword(eView0 - 0x50) + 0x14;
}

//-----------------------------------------------------------------------------

void MWBridge::SetCrosshairEnabled(bool enabled) {
    assert(m_loaded);
    if (enabled) {
        eCrosshair2 = GetCrosshair2();
        write_byte(eCrosshair2, read_byte(eCrosshair2) & 0xfe);
        write_byte(eCrosshair1, read_byte(eCrosshair1) & 0xfe);
    } else {
        eCrosshair2 = GetCrosshair2();
        write_byte(eCrosshair2, read_byte(eCrosshair2) | 0x01);
        write_byte(eCrosshair1, read_byte(eCrosshair1) | 0x01);
    }
}

//-----------------------------------------------------------------------------

void MWBridge::ToggleCrosshair() {
    assert(m_loaded);
    eCrosshair2 = GetCrosshair2();
    BYTE b = read_byte(eCrosshair2);
    BYTE b2 = read_byte(eCrosshair1);
    write_byte(eCrosshair2, b ^ 0x01);
    write_byte(eCrosshair1, b2 ^ 0x01);
}

//-----------------------------------------------------------------------------

bool MWBridge::IsExterior() {
    assert(m_loaded);
    DWORD addr = read_dword(eEnviro);
    if ( addr != 0 ) {
        return read_dword(addr + 0xAC) == 0;
    } else {
        return false;
    }
}

//-----------------------------------------------------------------------------

bool MWBridge::IsMenu() {
    assert(m_loaded);
    return read_byte(eMenu);
}

//-----------------------------------------------------------------------------

bool MWBridge::IsLoadScreen() {
    return (read_byte(eLoad) != 0);
}

//-----------------------------------------------------------------------------

bool MWBridge::IsCombat() {
    assert(m_loaded);
    return (read_dword(eCombat) & 1) != 0;
}

//-----------------------------------------------------------------------------

bool MWBridge::IsCrosshair() {
    assert(m_loaded);
    return (read_dword(eCrosshair1) & 1) == 0;
}

//-----------------------------------------------------------------------------

bool MWBridge::IsAlwaysRun() {
    assert(m_loaded);
    return  read_byte(GetAlwaysRun()+3) != 0;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetNextTrack() {
    assert(m_loaded);
    return read_dword(eD3D + 0x4) + 0x8;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetMusicVol() {
    assert(m_loaded);
    return GetNextTrack() + 0x28C;
}

//-----------------------------------------------------------------------------

void MWBridge::SkipToNextTrack() {
    assert(m_loaded);
    BYTE* flags = (BYTE*)GetNextTrack();
    *flags &= ~2;
}

//-----------------------------------------------------------------------------

void MWBridge::DisableMusic() {
    assert(m_loaded);
    eMusicVol = GetMusicVol();
    write_float(eMusicVol, 0.01f);
    write_float(eMusicVol - 0x08, 0.01f);

    typedef void (__thiscall *mmVolumeProc)(DWORD, float);
    const mmVolumeProc mvp = (mmVolumeProc)eMusicVolFunc;

    mvp(eMusicVol - 0x294, 0.01f);
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetCurrentWeather() {
    assert(m_loaded);
    DWORD weather = read_dword(eCurWthrStruct);
    if (weather == 0) {
        return 0;
    }
    return read_byte(weather + 4);
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetNextWeather() {
    assert(m_loaded);
    DWORD weather = read_dword(eNextWthrStruct);
    if (weather == 0) {
        return GetCurrentWeather();
    }
    return read_byte(weather + 4);
}

//-----------------------------------------------------------------------------

float MWBridge::GetWeatherRatio() {
    assert(m_loaded);
    return read_float(eWeatherRatio);
}

//-----------------------------------------------------------------------------

const RGBVECTOR* MWBridge::getCurrentWeatherSkyCol() {
    assert(m_loaded);
    return (RGBVECTOR*)eCurSkyCol;
}

//-----------------------------------------------------------------------------

const RGBVECTOR* MWBridge::getCurrentWeatherFogCol() {
    assert(m_loaded);
    return (RGBVECTOR*)eCurFogCol;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::getScenegraphFogCol() {
    DWORD addr = read_dword(eEnviro) + 0x9c;
    addr = read_dword(addr) + 0x1c;
    return read_dword(addr);
}

//-----------------------------------------------------------------------------

void MWBridge::setScenegraphFogCol(DWORD c) {
    DWORD addr = read_dword(eEnviro) + 0x9c;
    addr = read_dword(addr) + 0x1c;
    write_dword(addr, c);
}

//-----------------------------------------------------------------------------

float MWBridge::getScenegraphFogDensity() {
    DWORD addr = read_dword(eEnviro) + 0x9c;
    addr = read_dword(addr) + 0x18;
    return read_float(addr);
}

//-----------------------------------------------------------------------------

bool MWBridge::CellHasWeather() {
    assert(m_loaded);
    DWORD addr = read_dword(eEnviro);
    if (addr == 0) {
        return true;
    }
    addr = read_dword(addr + 0xAC);
    if (addr != 0) {
        return ((read_byte(addr + 0x18) & 0xF3) == 0x93);
    }
    return true;
}

//-----------------------------------------------------------------------------

float* MWBridge::GetWindVector() {
    assert(m_loaded);
    return (float*)eWindVector;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetWthrStruct(int wthr) {
    assert(m_loaded);
    if (wthr >= 0 && wthr <= 9) {
        return read_dword(eWthrArray + 4*wthr);
    }
    return 0;
}

//-----------------------------------------------------------------------------

int MWBridge::GetWthrString(int wthr, int offset, char str[]) {
    assert(m_loaded);
    DWORD addr = GetWthrStruct(wthr);
    int i = 0;

    if (addr != 0) {
        addr += offset;
        while ((str[i] = read_byte(addr)) != 0) {
            ++addr;
            ++i;
        }
    }
    str[i++] = 0;
    return i;
}

//-----------------------------------------------------------------------------

void MWBridge::SetWthrString(int wthr, int offset, char str[]) {
    assert(m_loaded);
    DWORD addr = GetWthrStruct(wthr);
    int i = 0;

    if (addr != 0) {
        char c;
        addr += offset;
        do {
            c = str[i++];
            write_byte(addr++, c);
        } while (c != 0);
    }
}

//-----------------------------------------------------------------------------

bool MWBridge::CellHasWater() {
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) {
        return ((read_byte(addr + 0x18) & 0x73) == 0x13);
    }
    return true;
}

//-----------------------------------------------------------------------------

bool MWBridge::IsUnderwater(float eyeZ) {
    assert(m_loaded);
    return (CellHasWater() && (eyeZ < WaterLevel() - 1.0f));
}

//-----------------------------------------------------------------------------

bool MWBridge::WaterReflects(float eyeZ) {
    assert(m_loaded);
    return (CellHasWater() && (eyeZ > WaterLevel() - 1.0f));
}

//-----------------------------------------------------------------------------

// simulationTime - Total real time elapsed this session, does not advance in menus
float MWBridge::simulationTime() {
    assert(m_loaded);
    return read_float(0x7c6708);
}

//-----------------------------------------------------------------------------

// frameTime - Duration of last frame in seconds
float MWBridge::frameTime() {
    assert(m_loaded);
    return read_float(eMaster1 + 0x2c);
}

//-----------------------------------------------------------------------------

// getMouseSensitivityYX() - Returns address of mouse sensitivity struct
// data is float[2], Y sensitivity component is first
float* MWBridge::getMouseSensitivityYX() {
    return reinterpret_cast<float*>(eMaster1 + 0xe8);
}

//-----------------------------------------------------------------------------

float MWBridge::GetViewDistance() {
    assert(m_loaded);
    return read_float(eView0);
}

//-----------------------------------------------------------------------------

void MWBridge::SetViewDistance(float dist) {
    assert(m_loaded);
    write_float(eView0, dist);
    write_float(eView1, dist);
    write_float(eView2, dist);
    write_float(eView3, dist);
    write_float(eView4, dist);
}

//-----------------------------------------------------------------------------

float MWBridge::GetAIDistance() {
    assert(m_loaded);
    return read_float(eAI);
}

//-----------------------------------------------------------------------------

void MWBridge::SetAIDistance(float dist) {
    assert(m_loaded);
    write_float(eAI, dist);
}

//-----------------------------------------------------------------------------

void MWBridge::SetFOV(float screenFOV) {
    assert(m_loaded);

    // Recalculate FOV values
    float fovtan = std::tan(screenFOV*D3DX_PI/360.0f);

    if ( std::fabs(read_float(eWorldFOV)+fovtan) > 0.001f ) {
        float aspect = read_float(eWorldFOV+1*sizeof(float)) / read_float(eWorldFOV+2*sizeof(float));
        float fovtanaspect = fovtan / aspect;

        write_float(eWorldFOV,-fovtan);
        write_float(eWorldFOV+1*sizeof(float),fovtan);
        write_float(eWorldFOV+2*sizeof(float),fovtanaspect);
        write_float(eWorldFOV+3*sizeof(float),-fovtanaspect);

        write_float(eSkyFOV ,-fovtan);
        write_float(eSkyFOV+1*sizeof(float),fovtan);
        write_float(eSkyFOV+2*sizeof(float),fovtanaspect);
        write_float(eSkyFOV+3*sizeof(float),-fovtanaspect);

        if (!eShadowFOV) {
            GetShadowFovAddr();
        }
        if (eShadowFOV) {
            write_float(eShadowFOV ,-fovtan);
            write_float(eShadowFOV+1*sizeof(float),fovtan);
            write_float(eShadowFOV+2*sizeof(float),fovtanaspect);
            write_float(eShadowFOV+3*sizeof(float),-fovtanaspect);
        }
    }

}

//-----------------------------------------------------------------------------

void MWBridge::GetSunDir(float& x, float& y, float& z) {
    // Note: Previous method caused significant jitter with moving view
    // This now returns the exact offset which was in the same scenegraph node
    assert(m_loaded);
    x = read_float(eSunDir);
    y = read_float(eSunDir + 0x4);
    z = read_float(eSunDir + 0x8);
}

//-----------------------------------------------------------------------------

BYTE MWBridge::GetSunVis() {
    assert(m_loaded);
    return read_byte(eSunVis);
}

//-----------------------------------------------------------------------------

// setSunriseSunset - Sets sunrise and sunset time and duration
void MWBridge::setSunriseSunset(float rise_time, float rise_dur, float set_time, float set_dur) {
    write_float(eSunriseHour, rise_time);
    write_float(eSunriseDuration, rise_dur);
    write_float(eSunsetHour, set_time);
    write_float(eSunsetDuration, set_dur);
}

//-----------------------------------------------------------------------------

DWORD MWBridge::IntCurCellAddr() {
    assert(m_loaded);

    DWORD addr = read_dword(eEnviro);
    if (addr != 0) {
        return read_dword(addr + 0xAC);
    }
    return 0;
}

//-----------------------------------------------------------------------------

const char* MWBridge::getInteriorName() {
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();

    if (addr) {
        return (const char*)read_dword(addr + 0x10);
    } else {
        return nullptr;
    }
}

//-----------------------------------------------------------------------------

bool MWBridge::IntLikeExterior() {
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) {
        return ((read_byte(addr + 0x18) & 0xF3) == 0x93);
    }
    return false;
}

//-----------------------------------------------------------------------------

bool MWBridge::IntIllegSleep() {
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) {
        return ((read_byte(addr + 0x18) & 0x75) == 0x15);
    }
    return false;
}

//-----------------------------------------------------------------------------

bool MWBridge::IntHasWater() {
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) {
        return ((read_byte(addr + 0x18) & 0xF3) == 0x13);
    }
    return false;
}

//-----------------------------------------------------------------------------

float MWBridge::WaterLevel() {
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0 && ((read_byte(addr + 0x18) & 0xF3) == 0x13)) {
        return read_float(addr + 0x90);
    }
    return 0.0f;
}

//-----------------------------------------------------------------------------

void MWBridge::HaggleMore(DWORD num) {
    assert(m_loaded);
    typedef void (_stdcall *mmHaggleProc)();
    mmHaggleProc proc = (mmHaggleProc)eHaggleMore;
    num -= 1;
    if (num != 0) {
        int d = (int)read_dword(0x7D287C);
        if (d <= 0) {
            d -= num;
        } else {
            d += num;
        }

        write_dword(0x7D287C, d);
    }
    proc();
}

//-----------------------------------------------------------------------------

void MWBridge::HaggleLess(DWORD num) {
    assert(m_loaded);
    typedef void (_stdcall *mmHaggleProc)();
    mmHaggleProc proc = (mmHaggleProc)eHaggleLess;
    num -= 1;
    if (num != 0) {
        int d = (int)read_dword(0x7D287C);
        if (d <= 0) {
            d += num;
        } else {
            d -= num;
        }

        write_dword(0x7D287C, d);
    }
    proc();
}

//-----------------------------------------------------------------------------

const BYTE* MWBridge::getInteriorAmb() {
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) {
        return (BYTE*)(addr + 0x1C);
    }
    return 0;
}

//-----------------------------------------------------------------------------

const BYTE* MWBridge::getInteriorSun() {
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) {
        return (BYTE*)(addr + 0x20);
    }
    return 0;
}

//-----------------------------------------------------------------------------

const BYTE* MWBridge::getInteriorFog() {
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) {
        return (BYTE*)(addr + 0x24);
    }
    return nullptr;
}

//-----------------------------------------------------------------------------

float MWBridge::getInteriorFogDens() {
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) {
        return read_float(addr + 0x28);
    }
    return 0;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::PlayerPositionPointer() {
    DWORD addr = eMaster1;
    if (addr != 0) {
        addr = read_dword(addr + 0x34);
        if (addr != 0) {
            return addr + 0x2AC;
        }
    }
    return 0;
}

//-----------------------------------------------------------------------------

float MWBridge::PlayerPositionX() {
    DWORD addr = PlayerPositionPointer();
    if (addr != 0) {
        return read_float(addr + 0);
    }
    return 0;
}

//-----------------------------------------------------------------------------

float MWBridge::PlayerPositionY() {
    DWORD addr = PlayerPositionPointer();
    if (addr != 0) {
        return read_float(addr + 4);
    }
    return 0;
}

//-----------------------------------------------------------------------------

float MWBridge::PlayerPositionZ() {
    DWORD addr = PlayerPositionPointer();
    if (addr != 0) {
        return read_float(addr + 8);
    }
    return 0;
}

//-----------------------------------------------------------------------------

float MWBridge::PlayerHeight() { // player eyes height, in CS
    float height = read_float(0x7D39F0); // like "Master", only read, in game PlayerHeight*125.0f
    return (height == 0 ? 1.0f : height);
}

//-----------------------------------------------------------------------------

bool MWBridge::IsPlayerWaiting() { // wait/sleep menu
    DWORD addr = eMaster1;
    if (addr != 0) {
        addr = read_dword(addr + 0x354);
        if (addr != 0) {
            return (read_byte(addr) == 0x01);
        }
    }
    return false;
}

//-----------------------------------------------------------------------------

// getPlayerMACP - Gets main game object holding the player state
DWORD MWBridge::getPlayerMACP() {
    DWORD addr = read_dword(eMaster1 + 0x5c);
    addr = read_dword(addr + 0x24);
    return read_dword(addr);
}

//-----------------------------------------------------------------------------

D3DXVECTOR3* MWBridge::PCam3Offset() {
    // Pointer resolve will fail during load screens
    if (IsLoadScreen()) {
        return nullptr;
    }

    DWORD macp = getPlayerMACP();
    if (macp == 0) {
        return nullptr;
    }

    // Camera control structure
    DWORD node = read_dword(macp + 0x244);
    return (D3DXVECTOR3*)(node + 0xd8);
}

//-----------------------------------------------------------------------------

bool MWBridge::is3rdPerson() {
    // Pointer resolve will fail during load screens
    if (IsLoadScreen()) {
        return false;
    }

    DWORD macp = getPlayerMACP();
    if (macp == 0) {
        return false;
    }

    // Camera control structure
    DWORD node = read_dword(macp + 0x244);
    return read_byte(node + 0xe8);
}

//-----------------------------------------------------------------------------

DWORD MWBridge::getPlayerTarget() {
    return read_dword(eLookMenu);
}

//-----------------------------------------------------------------------------

// getPlayerWeapon - Gets player weapon type
int MWBridge::getPlayerWeapon() {
    DWORD macp = getPlayerMACP();
    if (macp == 0) {
        return 0;
    }

    // Check active weapon
    DWORD weapon = read_dword(macp + 0x388);
    if (weapon == 0) {
        return -1;
    }

    weapon = read_dword(weapon);
    return read_byte(weapon + 0x5c);
}

//-----------------------------------------------------------------------------

// isPlayerCasting - Tests is the player is currently casting
bool MWBridge::isPlayerCasting() {
    DWORD macp = getPlayerMACP();
    if (macp == 0) {
        return false;
    }

    // Check animation state machine for casting
    BYTE anim = read_byte(macp + 0xdd);
    return anim == 0x0a;
}

//-----------------------------------------------------------------------------

// isPlayerAimingWeapon - Tests if the player is in the drawing stage of attacking with a ranged weapon
bool MWBridge::isPlayerAimingWeapon() {
    DWORD macp = getPlayerMACP();
    if (macp == 0) {
        return 0;
    }

    // Check animation state machine for weapon pullback
    BYTE anim = read_byte(macp + 0xdd);
    if (anim != 2) {
        return false;
    }

    // Check weapon type (bow, crossbow, thrown)
    DWORD weapon = read_dword(macp + 0x388);
    if (weapon == 0) {
        return false;
    }

    weapon = read_dword(weapon);
    return read_byte(weapon + 0x5c) >= 9;
}

//-----------------------------------------------------------------------------

// toggleRipples - Turns off ripple generation from all sources
void MWBridge::toggleRipples(BOOL enabled) {
    DWORD addr = eRipplesSwitch;
    DWORD code = read_dword(addr);
    if (enabled && code == 0x33504D8B || !enabled && code == 0x3390C931) {
        return;
    }
    code = enabled ? 0x33504D8B : 0x3390C931;

    VirtualMemWriteAccessor vw((void*)addr, 4);
    write_dword(addr, code);
}

//-----------------------------------------------------------------------------

// markWaterNode
// Edits the water material to set (normally unused) specular power to a recognizable value
void MWBridge::markWaterNode(float k) {
    // Get water node
    DWORD addr = read_dword(eEnviro);
    addr = read_dword(addr + 0xb4ec);
    addr = read_dword(addr + 0xb4);

    // Look for NiMaterialProperty in property list (skipping first property)
    DWORD linknode;
    for (linknode = read_dword(addr + 0x8c); linknode; linknode = read_dword(linknode + 4)) {
        if (read_dword(read_dword(linknode)) == 0x75036c) {
            break;
        }
    }

    // Write to specular power member
    if (linknode) {
        write_float(read_dword(linknode) + 0x4c, k);
    }
}

//-----------------------------------------------------------------------------

// markMoonNodes
// Edits the material for both moons to set (normally unused) specular power to a recognizable value
void MWBridge::markMoonNodes(float k) {
    DWORD addr = read_dword(eMaster);
    addr = read_dword(addr + 0x58);

    // Get masser node
    DWORD moon = read_dword(addr + 0x48);
    moon = read_dword(moon + 0x10);

    // Look for NiMaterialProperty in first property slot
    DWORD node = read_dword(moon + 0x88);

    // Write to specular power member
    if (node && read_dword(node) == 0x75036c) {
        write_float(node + 0x4c, k);
    }

    // Get secunda node
    moon = read_dword(addr + 0x44);
    moon = read_dword(moon + 0x10);

    // Look for NiMaterialProperty in first property slot
    node = read_dword(moon + 0x88);

    // Write to specular power member
    if (node && read_dword(node) == 0x75036c) {
        write_float(node + 0x4c, k);
    }
}

//-----------------------------------------------------------------------------

// disableScreenshotFunc
// Stops Morrowind from taking its own screenshots, or displaying an error message, when PrtScr is pressed
void MWBridge::disableScreenshotFunc() {
    DWORD addr = 0x41b08a;

    // Replace jz short with jmp (74 -> eb)
    VirtualMemWriteAccessor vw((void*)addr, 4);
    write_byte(addr, 0xeb);
}

//-----------------------------------------------------------------------------

// disableSunglare - Turns off the sunglare billboard and fullscreen glare that appears when looking at the sun
void MWBridge::disableSunglare() {
    DWORD addr = 0x4404fb;

    // Replace jz short with nop (74 xx -> 90 90)
    VirtualMemWriteAccessor vw((void*)addr, 4);
    write_byte(addr, 0x90);
    write_byte(addr+1, 0x90);
}

//-----------------------------------------------------------------------------

// disableIntroMovies - Skips playing both intro movies
void MWBridge::disableIntroMovies() {
    DWORD addr = 0x418ef0;
    BYTE patch[] = { 0xeb, 0x16 };

    VirtualMemWriteAccessor vw0((void*)addr, 2);
    memcpy((void*)addr, patch, sizeof(patch));

    addr = 0x5fc8f7;
    VirtualMemWriteAccessor vw1((void*)addr, 2);
    memcpy((void*)addr, patch, sizeof(patch));
}

//-----------------------------------------------------------------------------

// isIntroDone - Tests if both intro movies are finished, and main menu is about to display
bool MWBridge::isIntroDone() {
    return read_byte(0x7d5005) != 0;
}

//-----------------------------------------------------------------------------

// isLoadingSplash - Tests if a splash screen is shown (as a proxy for post-main menu loading)
bool MWBridge::isLoadingSplash() {
    return read_byte(0x7d4294) != 0;
}

//-----------------------------------------------------------------------------

// redirectMenuBackground - Redirects splash screen scenegraph draw call to another function
void MWBridge::redirectMenuBackground(void (_stdcall* func)(int)) {
    DWORD addr = 0x04589fb;

    // Reset to original if null is passed
    DWORD calladdr = func ? (DWORD)func : 0x6cc7b0;

    // Replace jump address
    VirtualMemWriteAccessor vw((void*)addr, 4);
    write_dword(addr, calladdr - (addr+4));
}

//-----------------------------------------------------------------------------

// setUIScale - Configures the scaling of Morrowind's UI system, must be called early before main menu
//              MWBridge is not required to be loaded for this function.
void MWBridge::setUIScale(float scale) {
    DWORD addr = read_dword(eMaster);
    int w, h;

    // Read UI viewport width and height
    w = read_dword(addr + 0x78);
    h = read_dword(addr + 0x7c);
    // Calculate a smaller viewport that will be scaled up by Morrowind
    w = (int)(w / scale);
    h = (int)(h / scale);
    // Write new viewport size
    write_dword(addr + 0x78, w);
    write_dword(addr + 0x7c, h);

    // Call UI configuration method to update scaling
    typedef void (__thiscall *uiproc1)(DWORD, DWORD);
    const uiproc1 ui_configureUIScale = (uiproc1)0x40f2a0;

    ui_configureUIScale(addr, w);

    // Call UI configuration method to update mouse bounds
    typedef void (__thiscall *uiproc2)(DWORD, int, int, int, int);
    const uiproc2 ui_configureUIMouseArea = (uiproc2)0x408740;

    int w_half = (w+1) / 2, h_half = (h+1) / 2;
    ui_configureUIMouseArea(read_dword(addr + 0x50), -w_half, -h_half, w_half, h_half);

    // Patch raycast system to use UI viewport size instead of D3D viewport size
    addr = 0x6f5157;
    const BYTE patch[] = {
        0xa1, 0xdc, 0x67, 0x7c, 0x00,       // mov eax, eMaster
        0x8b, 0x78, 0x78,                   // mov edi, [eax+0x78]
        0x8b, 0x40, 0x7c,                   // mov eax, [eax+0x7c]
        0x90, 0x90, 0x90                    // nops
    };

    VirtualMemWriteAccessor vw((void*)addr, sizeof(patch));
    memcpy((void*)addr, patch, sizeof(patch));
}

//-----------------------------------------------------------------------------

// patchUIConfigure - Patches the normal call to ui_configureUIScale to redirect to a new function.
//                    MWBridge is not required to be loaded for this function.
void MWBridge::patchUIConfigure(void (_stdcall* newfunc)()) {
    DWORD addr = 0x40e554;
    BYTE patch[] = {
        0xb8, 0xff, 0xff, 0xff, 0xff,       // mov eax, newfunc
        0xff, 0xd0,                         // call eax
        0xeb, 0x06                          // jmp past rest of block
    };

    VirtualMemWriteAccessor vw((void*)addr, sizeof(patch));
    memcpy((void*)addr, patch, sizeof(patch));
    write_ptr(addr + 1, reinterpret_cast<void*>(newfunc));
}

//-----------------------------------------------------------------------------

static int (__cdecl* patchFrameTimerTarget)();

// patchFrameTimer - Patches certain calls to timeGetTime to redirect to a new function.
void MWBridge::patchFrameTimer(int (__cdecl* newfunc)()) {
    DWORD addrs[] = { 0x403b52, 0x4535fd, 0x453615, 0x453638 };

    patchFrameTimerTarget = newfunc;

    for (int i = 0; i != sizeof(addrs)/sizeof(addrs[0]); ++i) {
        VirtualMemWriteAccessor vw((void*)addrs[i], sizeof(&patchFrameTimerTarget));
        write_dword(addrs[i], reinterpret_cast<DWORD>(&patchFrameTimerTarget));
    }
}

//-----------------------------------------------------------------------------

// getGMSTPointer - Gets a pointer directly to the data of a GMST (of any type)
void* MWBridge::getGMSTPointer(DWORD id) {
    DWORD addr = read_dword(eEnviro);
    addr = read_dword(addr);
    addr = read_dword(addr + 0x18);
    addr = read_dword(addr + 4 * id);
    return (void*)(addr + 0x10);
}

//-----------------------------------------------------------------------------

// getKeybindCode - Gets the scancode that an action is bound to
// action -> the keybind order in the Morrowind controls menu
DWORD MWBridge::getKeybindCode(DWORD action) {
    DWORD addr = read_dword(eMaster1 + 0x4c) + 0x1b3c;
    return read_dword(addr + 16*action);
}

//-----------------------------------------------------------------------------

// getPlayerName - Returns the player's name, or null if not loaded
const char* MWBridge::getPlayerName() {
    DWORD macp = getPlayerMACP();
    if (macp == 0) {
        return nullptr;
    }

    // Get name from base NPC
    DWORD npcClone = read_dword(macp + 0x560);
    DWORD npcBase = read_dword(npcClone + 0x6c);
    return reinterpret_cast<const char*>(read_dword(npcBase + 0x70));
}

//-----------------------------------------------------------------------------

// getGameHour - Returns the value of the script global GameHour
float MWBridge::getGameHour() {
    DWORD gvar = read_dword(eMaster1 + 0xa8);
    return read_float(gvar + 0x34);
}

//-----------------------------------------------------------------------------

// getDaysPassed - Returns the value of the script global DaysPassed
int MWBridge::getDaysPassed() {
    DWORD gvar = read_dword(eMaster1 + 0xb8);
    return int(read_float(gvar + 0x34));
}

//-----------------------------------------------------------------------------

// getFrameBeginMillis - Returns timer millis measured at start of frame
int MWBridge::getFrameBeginMillis() {
    return read_dword(eMaster1 + 0x20);
}
