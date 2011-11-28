// This file contains code from fps optimizer
// Memory layout originally worked out by Alexander Stasenko

#include "MWBridge.h"
#include "assert.h"

static MWBridge m_instance;

typedef void (_stdcall *mmHaggleProc)();

//-----------------------------------------------------------------------------

MWBridge::MWBridge()
{
    memset(this, 0, sizeof(*this));
    m_loaded = false;
    m_version = 0;
    InitStaticMemory();
}

//-----------------------------------------------------------------------------

MWBridge::~MWBridge()
{
}

//-----------------------------------------------------------------------------

MWBridge* MWBridge::Inst()
{
    return &m_instance;
}

//-----------------------------------------------------------------------------

void MWBridge::InitStaticMemory ()
{
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

void MWBridge::Load()
{
    // Standard Morrowind
    DWORD dwTruRenderWidthOff = 0x48;
    DWORD dwHRotScaleOff = 0x50;

    eMaster1 = read_dword(eMaster); //0x007C67DC
    eMaster2 = read_dword(eMaster + 0x500);  //0x007C6CDC

    eFPS = eMaster1 + 0x14;  //0x14
    eTimer = eFPS + 0xC;       //0x20
    eD3D = eTimer + 0x10;    //0x30
    ePCRef = eD3D + 0x2C;            //0x5C
    eTruRenderWidth = eD3D + dwTruRenderWidthOff;   //0x78
    eShadowSlider = eTruRenderWidth + 0xC;        //0x84
    eCrosshair1 = eShadowSlider + 0x10;         //0x94
    eAI = eCrosshair1 + 0x4;            //0x98
    eView0 = eAI + dwHRotScaleOff + 0x5C;  //0xF4
    eRenderWidth = eView0 + 0x4;                 //0xF8
    eView1 = eRenderWidth + 0x188;         //0x280
    eCombat = eView1 + 0x80;                //0x300

    eGamma = eMaster2 + 0x3C;  //0x3C  //00D1E090
    eView4 = eGamma+ + 0x10;   //0x4C  //00D1E0A0
    eLookMenu = eView4 + 0x9C;    //0xE8  //00D1E090

    eX = read_dword(eView0 - 0x10) + 0x1C;
    eCos = eX + 0xD4;
    eWorldFOV = eCos + 0x10;
    eView2 = eWorldFOV + 0x14;

    eSkyFOV = read_dword(eRenderWidth + 0x18) + 0x100;
    eMenuFOV = read_dword(eRenderWidth + 0x44) + 0x100;

    eView3 = read_dword(eView1 - 0x10) + 0x114;
    eExt = read_dword(eView1 + 0x10) + 0x10;
    eMenu = read_dword(read_dword(eView1 + 0x14) + 0x10) + 0x58;
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

    GetShadowFovAddr();

    m_loaded = true;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::read_dword(const DWORD dwAddress)
{
    return *reinterpret_cast<DWORD*>(dwAddress);
}

//-----------------------------------------------------------------------------

WORD MWBridge::read_word(const DWORD dwAddress)
{
    return *reinterpret_cast<WORD*>(dwAddress);
}

//-----------------------------------------------------------------------------

BYTE MWBridge::read_byte(const DWORD dwAddress)
{
    return *reinterpret_cast<BYTE*>(dwAddress);
}

//-----------------------------------------------------------------------------

float MWBridge::read_float(const DWORD dwAddress)
{
    return *reinterpret_cast<float*>(dwAddress);
}

//-----------------------------------------------------------------------------

void MWBridge::write_dword(const DWORD dwAddress, DWORD dword)
{
    *reinterpret_cast<DWORD*>(dwAddress) = dword;
}

//-----------------------------------------------------------------------------

void MWBridge::write_word(const DWORD dwAddress, WORD word)
{
    *reinterpret_cast<WORD*>(dwAddress) = word;
}

//-----------------------------------------------------------------------------

void MWBridge::write_byte(const DWORD dwAddress, BYTE byte)
{
    *reinterpret_cast<BYTE*>(dwAddress) = byte;
}

//-----------------------------------------------------------------------------

void MWBridge::write_float(const DWORD dwAddress, float f)
{
    *reinterpret_cast<float*>(dwAddress) = f;
}

//-----------------------------------------------------------------------------

bool MWBridge::CanLoad()
{
    // reads static address, so game doesn't need to be loaded
    return read_dword(eEnviro) != 0;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetAlwaysRun()
{
    assert(m_loaded);
    return read_dword(read_dword(read_dword(eD3D + 0x2C) + 0x24)) + dwAlwaysRunOffset;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetAutoRun()
{
    assert(m_loaded);
    return GetAlwaysRun() + 4;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetShadowToggleAddr()
{
    assert(m_loaded);
    DWORD addr = read_dword(eView1 + 0xC);
    return addr ?  (addr + 0xC) : 0;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetShadowRealAddr()
{
    assert(m_loaded);
    DWORD addr = read_dword(eView1 + 0xC);
    return addr ?  (addr + 0x14) : 0;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetShadowFovAddr()
{
    assert(m_loaded);

    eShadowFOV = read_dword (eView1 + 0xC);
    if (eShadowFOV)
    {
        eShadowFOV = read_dword (eShadowFOV + 0x8);
        if (eShadowFOV) eShadowFOV += 0x100;
    }
    return eShadowFOV;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetCrosshair2()
{
    assert(m_loaded);
    return read_dword(eView0 - 0x50) + 0x14;
}

//-----------------------------------------------------------------------------

void MWBridge::SetCrosshairEnabled(bool enabled)
{
    assert(m_loaded);
    if (enabled)
    {
        eCrosshair2 = GetCrosshair2();
        write_byte(eCrosshair2, read_byte(eCrosshair2) & 0xfe);
        write_byte(eCrosshair1, read_byte(eCrosshair1) & 0xfe);
    }
    else
    {
        eCrosshair2 = GetCrosshair2();
        write_byte(eCrosshair2, read_byte(eCrosshair2) | 0x01);
        write_byte(eCrosshair1, read_byte(eCrosshair1) | 0x01);
    }
}

//-----------------------------------------------------------------------------

void MWBridge::ToggleCrosshair()
{
    assert(m_loaded);
    eCrosshair2 = GetCrosshair2();
    BYTE b = read_byte(eCrosshair2);
    BYTE b2 = read_byte(eCrosshair1);
    write_byte(eCrosshair2, b ^ 0x01);
    write_byte(eCrosshair1, b2 ^ 0x01);
}

//-----------------------------------------------------------------------------

bool MWBridge::IsExterior()
{
    assert(m_loaded);
    DWORD addr = read_dword(eEnviro);
    if ( addr !=0 )
        return read_dword(addr + 0xAC) == 0;
    else
        return 0;
}

//-----------------------------------------------------------------------------

bool MWBridge::IsMenu()
{
    assert(m_loaded);
    return (read_dword(eMenu) & 0x10000) != 0;
}

//-----------------------------------------------------------------------------

bool MWBridge::IsLoadScreen()
{
    return (read_byte(eLoad) != 0);
}

//-----------------------------------------------------------------------------

bool MWBridge::IsCombat()
{
    assert(m_loaded);
    return (read_dword(eCombat) & 1) != 0;
}

//-----------------------------------------------------------------------------

bool MWBridge::IsCrosshair()
{
    assert(m_loaded);
    return (read_dword(eCrosshair1) & 1) == 0;
}

//-----------------------------------------------------------------------------

bool MWBridge::IsAlwaysRun()
{
    assert(m_loaded);
    return  read_byte(GetAlwaysRun()+3) != 0;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetNextTrack()
{
    assert(m_loaded);
    return read_dword(eD3D + 0x4) + 0x8;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetMusicVol()
{
    assert(m_loaded);
    return GetNextTrack() + 0x28C;
}

//-----------------------------------------------------------------------------

void MWBridge::SkipToNextTrack()
{
    assert(m_loaded);
    BYTE *flags = (BYTE *)GetNextTrack();
    *flags &= ~2;
}

//-----------------------------------------------------------------------------

void MWBridge::DisableMusic()
{
    assert(m_loaded);
    eMusicVol = GetMusicVol();
    write_float(eMusicVol, 0.01f);
    write_float(eMusicVol - 0x08, 0.01f);

    // uses properties of fastcall to put vm in ecx
    typedef void (__fastcall *mmVolumeProc)(DWORD, int, float);
    mmVolumeProc mvp = (mmVolumeProc)eMusicVolFunc;

    mvp(eMusicVol - 0x294, 0, 0.01f);
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetCurrentWeather()
{
    assert(m_loaded);
    DWORD weather = read_dword(eCurWthrStruct);
    if (weather == 0) return 0;
    return read_byte(weather + 4);
}

//-----------------------------------------------------------------------------

DWORD MWBridge::GetNextWeather()
{
    assert(m_loaded);
    DWORD weather = read_dword(eNextWthrStruct);
    if (weather == 0) return GetCurrentWeather();
    return read_byte(weather + 4);
}

//-----------------------------------------------------------------------------

float MWBridge::GetWeatherRatio()
{
    assert(m_loaded);
    return read_float(eWeatherRatio);
}

//-----------------------------------------------------------------------------

RGBVECTOR* MWBridge::CurSkyColVector()
{
    assert(m_loaded);
    return (RGBVECTOR*)eCurSkyCol;
}

//-----------------------------------------------------------------------------

RGBVECTOR* MWBridge::CurFogColVector()
{
    assert(m_loaded);
    return (RGBVECTOR*)eCurFogCol;
}

//-----------------------------------------------------------------------------

void MWBridge::setSceneFogCol(DWORD c)
{
    DWORD addr = read_dword(eEnviro) + 0x9c;
    addr = read_dword(addr) + 0x1c;
    write_dword(addr, c);
}

//-----------------------------------------------------------------------------

bool MWBridge::CellHasWeather()
{
    assert(m_loaded);
    DWORD addr = read_dword(eEnviro);
    if (addr == 0) return true;
    addr = read_dword(addr + 0xAC);
    if (addr != 0) return ((read_byte(addr + 0x18) & 0xF3) == 0x93);
    return true;
}

//-----------------------------------------------------------------------------

float * MWBridge::GetWindVector()
{
    assert(m_loaded);
    return (float*)eWindVector;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::WthrStruc(int wthr)
{
    assert(m_loaded);
    if (wthr >= 0 && wthr <= 9)
    {
        DWORD addr = read_dword(eWthrArray + (wthr << 2));
        if (addr != 0) return addr;
    }
    return 0;
}

//-----------------------------------------------------------------------------

int MWBridge::GetWthrString(int wthr, int offset, char str[])
{
    assert(m_loaded);
    int i = 0;
    DWORD addr = WthrStruc(wthr);
    if (addr != 0)
    {
        addr += offset;
        while ((str[i] = read_byte(addr)) != 0)
        {
            ++addr;
            ++i;
        }
    }
    str[i++] = 0;
    return i;
}

//-----------------------------------------------------------------------------

void MWBridge::SetWthrString(int wthr, int offset, char str[])
{
    assert(m_loaded);
    int i = 0;
    DWORD addr = WthrStruc(wthr);
    if (addr != 0)
    {
        addr += offset;
        char c;
        do
        {
            write_byte(addr++, c = str[i++]);
        }
        while (c != 0);
    }
}

//-----------------------------------------------------------------------------

bool MWBridge::CellHasWater()
{
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) return ((read_byte(addr + 0x18) & 0x73) == 0x13);
    return true;
}

//-----------------------------------------------------------------------------

bool MWBridge::IsUnderwater(float eyeZ)
{
    assert(m_loaded);
    return (CellHasWater() && (eyeZ < WaterLevel() - 1.0f));
}

//-----------------------------------------------------------------------------

bool MWBridge::WaterReflects(float eyeZ)
{
    assert(m_loaded);
    return (CellHasWater() && (eyeZ > WaterLevel() - 1.0f));
}

//-----------------------------------------------------------------------------

float MWBridge::simulationTime()
{
    assert(m_loaded);
    return read_float(0x7c6708);
}

//-----------------------------------------------------------------------------

float MWBridge::frameTime()
{
    assert(m_loaded);
    return read_float(eMaster1 + 0x2c);
}

//-----------------------------------------------------------------------------

float MWBridge::GetViewDistance()
{
    assert(m_loaded);
    return read_float(eView0);
}

//-----------------------------------------------------------------------------

void MWBridge::SetViewDistance(float dist)
{
    assert(m_loaded);
    write_float(eView0, dist);
    write_float(eView1, dist);
    write_float(eView2, dist);
    write_float(eView3, dist);
    write_float(eView4, dist);
}

//-----------------------------------------------------------------------------

float MWBridge::GetAIDistance()
{
    assert(m_loaded);
    return read_float(eAI);
}

//-----------------------------------------------------------------------------

void MWBridge::SetAIDistance(float dist)
{
    assert(m_loaded);
    write_float(eAI, dist);
}

//-----------------------------------------------------------------------------

void MWBridge::SetFOV(float screenFOV)
{
    assert(m_loaded);

    //Recalculate FOV values
    float fovtan = tanf(screenFOV*D3DX_PI/360.0f);

    if ( fabs(read_float(eWorldFOV)+fovtan) > 0.001f )
    {
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

        if (!eShadowFOV)
            GetShadowFovAddr();
        if (eShadowFOV)
        {
            write_float(eShadowFOV ,-fovtan);
            write_float(eShadowFOV+1*sizeof(float),fovtan);
            write_float(eShadowFOV+2*sizeof(float),fovtanaspect);
            write_float(eShadowFOV+3*sizeof(float),-fovtanaspect);
        }
    }

}

//-----------------------------------------------------------------------------

void MWBridge::GetSunDir(float& x, float& y, float& z)
{
    // Note: Previous method caused significant jitter with moving view
    // This now returns the exact offset which was in the same scenegraph node
    assert(m_loaded);
    x = read_float(eSunDir);
    y = read_float(eSunDir + 0x4);
    z = read_float(eSunDir + 0x8);
}

//-----------------------------------------------------------------------------

BYTE MWBridge::GetSunVis()
{
    assert(m_loaded);
    return read_byte(eSunVis);
}

//-----------------------------------------------------------------------------

float MWBridge::GetSunriseHour()
{
    assert(m_loaded);
    return read_float(eSunriseHour);
}

//-----------------------------------------------------------------------------

void MWBridge::SetSunriseHour(float hour)
{
    assert(m_loaded);
    write_float(eSunriseHour, hour);
}

//-----------------------------------------------------------------------------

float MWBridge::GetSunriseDuration()
{
    assert(m_loaded);
    return read_float(eSunriseDuration);
}

//-----------------------------------------------------------------------------

void MWBridge::SetSunriseDuration(float duration)
{
    assert(m_loaded);
    write_float(eSunriseDuration, duration);
}

//-----------------------------------------------------------------------------

float MWBridge::GetSunsetHour()
{
    assert(m_loaded);
    return read_float(eSunsetHour);
}

//-----------------------------------------------------------------------------

void MWBridge::SetSunsetHour(float hour)
{
    assert(m_loaded);
    write_float(eSunsetHour, hour);
}

//-----------------------------------------------------------------------------

float MWBridge::GetSunsetDuration()
{
    assert(m_loaded);
    return read_float(eSunsetDuration);
}

//-----------------------------------------------------------------------------

void MWBridge::SetSunsetDuration(float duration)
{
    assert(m_loaded);
    write_float(eSunsetDuration, duration);
}

//-----------------------------------------------------------------------------

DWORD MWBridge::IntCurCellAddr()
{
    assert(m_loaded);

    DWORD addr = read_dword(eEnviro);
    if (addr != 0) return read_dword(addr + 0xAC);
    return 0;
}

//-----------------------------------------------------------------------------

const char * MWBridge::getInteriorName()
{
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();

    if(addr)
        return (const char *)read_dword(addr + 0x10);
    else
        return 0;
}

//-----------------------------------------------------------------------------

bool MWBridge::IntLikeExterior()
{
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) return ((read_byte(addr + 0x18) & 0xF3) == 0x93);
    return false;
}

//-----------------------------------------------------------------------------

bool MWBridge::IntIllegSleep()
{
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) return ((read_byte(addr + 0x18) & 0x75) == 0x15);
    return false;
}

//-----------------------------------------------------------------------------

bool MWBridge::IntHasWater()
{
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) return ((read_byte(addr + 0x18) & 0xF3) == 0x13);
    return false;
}

//-----------------------------------------------------------------------------

float MWBridge::WaterLevel()
{
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0 && ((read_byte(addr + 0x18) & 0xF3) == 0x13)) return read_float(addr + 0x90);
    return 0.0f;
}

//-----------------------------------------------------------------------------

void MWBridge::HaggleMore(DWORD num)
{
    assert(m_loaded);
 typedef void (_stdcall *mmVolumeProc)(float);
typedef void (_stdcall *mmHaggleProc)();
   mmHaggleProc proc = (mmHaggleProc)eHaggleMore;
    num -= 1;
    if (num != 0)
    {
        long d = (long)read_dword(0x7D287C);
        if (d <= 0)
            d -= num;
        else
            d += num;

        write_dword(0x7D287C, d);
    }
    proc();
}

//-----------------------------------------------------------------------------

void MWBridge::HaggleLess(DWORD num)
{
    assert(m_loaded);
    mmHaggleProc proc = (mmHaggleProc)eHaggleLess;
    long d =( long)read_dword(0x7D287C);
    num -=1;
    if (num != 0)
    {
        if (d <= 0)
            d += num;
        else
            d -= num;

        write_dword(0x7D287C, d);
    }
    proc();
}

//-----------------------------------------------------------------------------

const BYTE * MWBridge::getInteriorAmb()
{
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) return (BYTE*)(addr + 0x1C);
    return 0;
}

//-----------------------------------------------------------------------------

const BYTE * MWBridge::getInteriorSun()
{
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) return (BYTE*)(addr + 0x20);
    return 0;
}

//-----------------------------------------------------------------------------

const BYTE * MWBridge::getInteriorFog()
{
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) return (BYTE*)(addr + 0x24);
    return 0;
}

//-----------------------------------------------------------------------------

float MWBridge::getInteriorFogDens()
{
    assert(m_loaded);
    DWORD addr = IntCurCellAddr();
    if (addr != 0) return read_float(addr + 0x28);
    return 0;
}

//-----------------------------------------------------------------------------

DWORD MWBridge::PlayerPositionPointer()
{
    DWORD addr = eMaster1;
    if (addr != 0)
    {
        addr = read_dword(addr + 0x34);
        if (addr != 0) return addr + 0x2AC;
    }
    return 0;
}

//-----------------------------------------------------------------------------

float MWBridge::PlayerPositionX()
{
    DWORD addr = PlayerPositionPointer();
    if (addr != 0) return read_float(addr + 0);
    return 0;
}

//-----------------------------------------------------------------------------

float MWBridge::PlayerPositionY()
{
    DWORD addr = PlayerPositionPointer();
    if (addr != 0) return read_float(addr + 4);
    return 0;
}

//-----------------------------------------------------------------------------

float MWBridge::PlayerPositionZ()
{
    DWORD addr = PlayerPositionPointer();
    if (addr != 0) return read_float(addr + 8);
    return 0;
}

//-----------------------------------------------------------------------------

float MWBridge::PlayerHeight()   //player eyes height, in CS
{
    float height = read_float(0x7D39F0); //like "Master", only read, in game PlayerHeight*125.0f
    return (height == 0 ? 1.0f : height);
}

//-----------------------------------------------------------------------------

bool MWBridge::IsPlayerWaiting()   //wait\sleep menu
{
    DWORD addr = eMaster1;
    if (addr != 0)
    {
        addr=read_dword(addr + 0x354);
        if (addr != 0) return (read_byte(addr) == 0x01);
    }
    return false;
}

//-----------------------------------------------------------------------------

D3DXVECTOR3 * MWBridge::PCam3Offset()
{
    // Pointer resolve will fail during load screens
    if(IsLoadScreen()) return 0;

    // Player structure
    DWORD blah0 = read_dword(eMaster1 + 0x5c);
    DWORD blah1 = read_dword(blah0 + 0x24);
    DWORD macp = read_dword(blah1);
    if(macp == 0) return 0;

    // Camera control structure
    DWORD node = read_dword(macp + 0x244);
    return (D3DXVECTOR3*)(node + 0xd8);
}

//-----------------------------------------------------------------------------

bool MWBridge::Is3rdPerson()
{
    if(IsLoadScreen()) return 0;

    // Player structure
    DWORD blah0 = read_dword(eMaster1 + 0x5c);
    DWORD blah1 = read_dword(blah0 + 0x24);
    DWORD macp = read_dword(blah1);
    if(macp == 0) return 0;

    // Camera control structure
    DWORD node = read_dword(macp + 0x244);
    return read_byte(node + 0xe8);
}

//-----------------------------------------------------------------------------

DWORD MWBridge::PlayerTarget()
{
    return read_dword(eLookMenu);
}

//-----------------------------------------------------------------------------

bool MWBridge::IsPlayerCasting()
{
    // Player structure
    DWORD blah0 = read_dword(eMaster1 + 0x5c);
    DWORD blah1 = read_dword(blah0 + 0x24);
    DWORD macp = read_dword(blah1);
    if(macp == 0) return false;

    // Check animation state machine
    BYTE anim = read_byte(macp + 0xdd);
    return anim == 0x0a;
}

//-----------------------------------------------------------------------------

bool MWBridge::IsPlayerAimingWeapon()
{
    // Player structure
    DWORD blah0 = read_dword(eMaster1 + 0x5c);
    DWORD blah1 = read_dword(blah0 + 0x24);
    DWORD macp = read_dword(blah1);
    if(macp == 0) return false;

    // Check animation state machine
    BYTE anim = read_byte(macp + 0xdd);
    if(anim != 2) return false;

    // Check weapon type (bow, crossbow, thrown)
    DWORD weapon = read_dword(macp + 0x388);
    if(weapon == 0) return false;

    weapon = read_dword(weapon);
    return read_byte(weapon + 0x5c) >= 9;
}

//-----------------------------------------------------------------------------

void MWBridge::toggleRipples(BOOL enabled)
{
    DWORD addr = eRipplesSwitch;
    DWORD code = read_dword(addr);
    if (enabled && code == 0x33504D8B || !enabled && code == 0x3390C931) return;
    code = enabled ? 0x33504D8B : 0x3390C931;
    DWORD oldProtect;
    VirtualProtect((LPVOID) addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
    write_dword(addr, code);
    VirtualProtect((LPVOID) addr, 4, oldProtect, &oldProtect);
}

//-----------------------------------------------------------------------------

void MWBridge::markWaterNode(float k)
{
    // Get water node
    DWORD addr = read_dword(eEnviro);
    addr = read_dword(addr + 0xb4ec);
    addr = read_dword(addr + 0xb4);

    // Look for NiMaterialProperty in property list
    DWORD linknode;
    for(linknode = read_dword(addr + 0x8c); linknode; linknode = read_dword(linknode + 4))
    {
        if(read_dword(read_dword(linknode)) == 0x75036c)
            break;
    }

    // Write to specular power member
    if(linknode)
        write_float(read_dword(linknode) + 0x4c, k);
}

//-----------------------------------------------------------------------------

void MWBridge::disableScreenshotFunc()
{
    DWORD addr = 0x41b08a;

    // Replace jz short with jmp (74 -> eb)
    DWORD oldProtect;
    VirtualProtect((LPVOID)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
    write_byte(addr, 0xeb);
    VirtualProtect((LPVOID)addr, 4, oldProtect, &oldProtect);
}

//-----------------------------------------------------------------------------

void MWBridge::disableSunglare()
{
    DWORD addr = 0x4404fb;

    // Replace jz short with nop (74 xx -> 90 90)
    DWORD oldProtect;
    VirtualProtect((LPVOID)addr, 8, PAGE_EXECUTE_READWRITE, &oldProtect);
    write_byte(addr, 0x90);
    write_byte(addr+1, 0x90);
    VirtualProtect((LPVOID)addr, 8, oldProtect, &oldProtect);
}

//-----------------------------------------------------------------------------

void * MWBridge::getGMSTPointer(int id)
{
    DWORD addr = read_dword(eEnviro);
    addr = read_dword(addr);
    addr = read_dword(addr + 0x18);
    addr = read_dword(addr + 4 * id);
    return (void *)(addr + 0x10);
}
