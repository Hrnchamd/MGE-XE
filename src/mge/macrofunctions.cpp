
#include <cstdio>
#include <sys/stat.h>
#include "proxydx/d3d8header.h"

#include "configuration.h"
#include "mwbridge.h"
#include "statusoverlay.h"
#include "distantland.h"
#include "postshaders.h"
#include "mmefunctiondefs.h"



static void SaveScreenshot(IDirect3DSurface9 *surface);


void MacroFunctions::TakeScreenshot()
{
    DECLARE_MWBRIDGE

    // Requires distant land to be loaded
    if(!DistantLand::ready) return;

    if(mwBridge->IsMenu())
    {
        // Save screen including UI
        IDirect3DSurface9 *surface = DistantLand::captureScreen();
        SaveScreenshot(surface);
        if(surface) surface->Release();
    }
    else
    {
        // Request distant land to save screen without UI
        DistantLand::requestCaptureNoUI(&SaveScreenshot);
    }
}

static void SaveScreenshot(IDirect3DSurface9 *surface)
{
    const char * strImageExtensions[] = { ".bmp", ".jpg", ".dds", ".png", ".tga" };
    const D3DXIMAGE_FILEFORMAT formats[] = { D3DXIFF_BMP, D3DXIFF_JPG, D3DXIFF_DDS, D3DXIFF_PNG, D3DXIFF_TGA };

    char filename[MAX_PATH], path[MAX_PATH];
    int str_sz;
    bool usedir = false;
    struct _stat unusedstat;
    SYSTEMTIME t;

    if(!surface) { StatusOverlay::setStatus("Screenshot failed - Surface error"); return; }

    // Set up path
    GetLocalTime(&t);
    std::snprintf(filename, sizeof(filename), "%s %04d-%02d-%02d %02d.%02d.%02d.%03d",
                  Configuration.SSName, t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    if(strlen(Configuration.SSDir) > 0)
    {
        usedir = true;

        if(_stat(Configuration.SSDir, &unusedstat) == -1 && !CreateDirectory(Configuration.SSDir, NULL))
            usedir = false;
    }

    if(usedir)
        str_sz = std::snprintf(path, sizeof(path), "%s\\%s%s", Configuration.SSDir, filename, strImageExtensions[Configuration.SSFormat]);
    else
        str_sz = std::snprintf(path, sizeof(path), "%s%s", filename, strImageExtensions[Configuration.SSFormat]);

    if(str_sz >= sizeof(filename))
    {
        StatusOverlay::setStatus("Screenshot failed - Path too long");
        return;
    }

    // Save screenshot to desired format
    HRESULT hr = D3DXSaveSurfaceToFile(path, formats[Configuration.SSFormat], surface, NULL, NULL);
    if(SUCCEEDED(hr))
    {
        StatusOverlay::setStatus(filename);
    }
    else
    {
        std::snprintf(filename, sizeof(filename), "Screenshot failed - D3DX Error %lx", hr);
        StatusOverlay::setStatus(filename);
    }
}

static void displayFlag(DWORD flag, const char *en, const char *ds)
{
    if(Configuration.MGEFlags & flag)
        StatusOverlay::setStatus(en);
    else
        StatusOverlay::setStatus(ds);
}

void MacroFunctions::ToggleStatusText() {
    Configuration.MGEFlags ^= DISPLAY_MESSAGES;

    if(Configuration.MGEFlags & DISPLAY_MESSAGES)
        StatusOverlay::setStatus("Displaying status messages");
}

void MacroFunctions::ToggleFpsCounter() {
    Configuration.MGEFlags ^= FPS_COUNTER;
}

void MacroFunctions::ShowLastMessage() {
    StatusOverlay::showLastStatus();
}

void MacroFunctions::ToggleBlending() {
    Configuration.MGEFlags ^= NO_MW_MGE_BLEND;
    displayFlag(NO_MW_MGE_BLEND, "MW/MGE blend disabled", "MW/MGE blend enabled");
}

void MacroFunctions::ToggleShaders() {
    PostShaders::updateShaderChain();
    Configuration.MGEFlags ^= USE_HW_SHADER;
    displayFlag(USE_HW_SHADER, "Shaders enabled", "Shaders disabled");
}

void MacroFunctions::ToggleDistantLand() {
    Configuration.MGEFlags ^= USE_DISTANT_LAND;
    displayFlag(USE_DISTANT_LAND, "Distant land enabled", "Distant land disabled");
}

void MacroFunctions::ToggleShadows() {
    Configuration.MGEFlags ^= USE_SHADOWS;
    displayFlag(USE_SHADOWS, "Shadows enabled", "Shadows disabled");
}

void MacroFunctions::ToggleGrass() {
    Configuration.MGEFlags ^= USE_GRASS;
    displayFlag(USE_GRASS, "Grass enabled", "Grass disabled");
}

void MacroFunctions::ToggleLightingMode() {
    Configuration.MGEFlags ^= USE_FFESHADER;
    displayFlag(USE_FFESHADER, "New dynamic lighting", "Standard dynamic lighting");
}

void MacroFunctions::ToggleTransparencyAA() {
    Configuration.MGEFlags ^= TRANSPARENCY_AA;
    displayFlag(TRANSPARENCY_AA, "Transparency AA enabled", "Transparency AA disabled");
}

void MacroFunctions::IncreaseViewRange() {
    DECLARE_MWBRIDGE
    float r = mwBridge->GetViewDistance();
    mwBridge->SetViewDistance(std::min(7168.0, r + 512.0));
}

void MacroFunctions::DecreaseViewRange() {
    DECLARE_MWBRIDGE
    float r = mwBridge->GetViewDistance();
    mwBridge->SetViewDistance(std::max(2500.0, r - 512.0));
}

void MacroFunctions::ToggleZoom() {
    Configuration.MGEFlags ^= ZOOM_ASPECT;
    displayFlag(ZOOM_ASPECT, "Zoom enabled", "Zoom disabled");
}

void MacroFunctions::ResetEnableZoom() {
    Configuration.MGEFlags |= ZOOM_ASPECT;
    Configuration.Zoom.zoom = 1.0;
    StatusOverlay::setStatus("Zoom reset");
}

void MacroFunctions::IncreaseZoom() {
    Configuration.MGEFlags |= ZOOM_ASPECT;
    Configuration.Zoom.zoom = std::min(Configuration.Zoom.zoom * 1.0078125, 40.0);
}

void MacroFunctions::DecreaseZoom() {
    Configuration.MGEFlags |= ZOOM_ASPECT;
    Configuration.Zoom.zoom = std::max(1.0, Configuration.Zoom.zoom / 1.0078125);
}

void MacroFunctions::ToggleCrosshair() {
    DECLARE_MWBRIDGE
    mwBridge->ToggleCrosshair();
}

void MacroFunctions::NextTrack() {
    DECLARE_MWBRIDGE
    mwBridge->SkipToNextTrack();
}

void MacroFunctions::DisableMusic() {
    DECLARE_MWBRIDGE
    mwBridge->DisableMusic();
}

void MacroFunctions::IncreaseFOV() {
    Configuration.ScreenFOV = std::min(Configuration.ScreenFOV + 1.0, 150.0);
}

void MacroFunctions::DecreaseFOV() {
    Configuration.ScreenFOV = std::max(60.0, Configuration.ScreenFOV - 1.0);
}

void MacroFunctions::HaggleMore1() { DECLARE_MWBRIDGE  mwBridge->HaggleMore(1); }
void MacroFunctions::HaggleMore10() { DECLARE_MWBRIDGE  mwBridge->HaggleMore(10); }
void MacroFunctions::HaggleMore100() { DECLARE_MWBRIDGE  mwBridge->HaggleMore(100); }
void MacroFunctions::HaggleMore1000() { DECLARE_MWBRIDGE  mwBridge->HaggleMore(1000); }
void MacroFunctions::HaggleMore10000() { DECLARE_MWBRIDGE  mwBridge->HaggleMore(10000); }

void MacroFunctions::HaggleLess1() { DECLARE_MWBRIDGE  mwBridge->HaggleLess(1); }
void MacroFunctions::HaggleLess10() { DECLARE_MWBRIDGE  mwBridge->HaggleLess(10); }
void MacroFunctions::HaggleLess100() { DECLARE_MWBRIDGE  mwBridge->HaggleLess(100); }
void MacroFunctions::HaggleLess1000() { DECLARE_MWBRIDGE  mwBridge->HaggleLess(1000); }
void MacroFunctions::HaggleLess10000() { DECLARE_MWBRIDGE  mwBridge->HaggleLess(10000); }

static void displayCamPosition()
{
    char str[256];
    std::snprintf(str, sizeof(str), "Camera offset at (%.0f, %.0f, %.0f)",
                  Configuration.Offset3rdPerson.x, Configuration.Offset3rdPerson.y, Configuration.Offset3rdPerson.z);
    StatusOverlay::setStatus(str);
}

void MacroFunctions::MoveForward3PCam() {
    DECLARE_MWBRIDGE
    if(mwBridge->is3rdPerson() && !mwBridge->IsMenu())
    {
        Configuration.Offset3rdPerson.y = std::min(-25.0, Configuration.Offset3rdPerson.y * 0.96);
        displayCamPosition();
    }
}

void MacroFunctions::MoveBack3PCam() {
    DECLARE_MWBRIDGE
    if(mwBridge->is3rdPerson() && !mwBridge->IsMenu())
    {
        Configuration.Offset3rdPerson.y = std::max(-2500.0, Configuration.Offset3rdPerson.y * 1.04);
        displayCamPosition();
    }
}

void MacroFunctions::MoveLeft3PCam() {
    DECLARE_MWBRIDGE
    if(mwBridge->is3rdPerson() && !mwBridge->IsMenu())
    {
        Configuration.Offset3rdPerson.x = std::max(-125.0, Configuration.Offset3rdPerson.x - 1.0);
        displayCamPosition();
    }
}

void MacroFunctions::MoveRight3PCam() {
    DECLARE_MWBRIDGE
    if(mwBridge->is3rdPerson() && !mwBridge->IsMenu())
    {
        Configuration.Offset3rdPerson.x = std::min(125.0, Configuration.Offset3rdPerson.x + 1.0);
        displayCamPosition();
    }
}

void MacroFunctions::MoveDown3PCam() {
    DECLARE_MWBRIDGE
    if(mwBridge->is3rdPerson() && !mwBridge->IsMenu())
    {
        Configuration.Offset3rdPerson.z = std::max(-125.0, Configuration.Offset3rdPerson.z - 1.0);
        displayCamPosition();
    }
}

void MacroFunctions::MoveUp3PCam() {
    DECLARE_MWBRIDGE
    if(mwBridge->is3rdPerson() && !mwBridge->IsMenu())
    {
        Configuration.Offset3rdPerson.z = std::min(125.0, Configuration.Offset3rdPerson.z + 1.0);
        displayCamPosition();
    }
}
