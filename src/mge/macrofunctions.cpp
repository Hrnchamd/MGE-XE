
#include <stdio.h>
#include <sys/stat.h>
#include "proxydx/d3d8header.h"
#include "support/strsec.h"

#include "configuration.h"
#include "mwbridge.h"
#include "statusoverlay.h"
#include "distantland.h"
#include "mmefunctiondefs.h"



void MacroFunctions::TakeScreenshot()
{
    const char * strImageExtensions[] = { ".bmp", ".jpg", ".dds", ".png", ".tga" };
    const D3DXIMAGE_FILEFORMAT formats[] = { D3DXIFF_BMP, D3DXIFF_JPG, D3DXIFF_DDS, D3DXIFF_PNG, D3DXIFF_TGA };
    char filename[256], path[256];
    bool usedir = false;
    struct _stat unusedstat;

    // Requires distant land to be loaded
    if(!DistantLand::ready) return;

    // Grab copy of surface
    IDirect3DSurface9 *surface = DistantLand::captureScreen();
    if(!surface) { StatusOverlay::setStatus("Screenshot failed - Surface error"); return; }

    // Set up path
	if(strlen(Configuration.SSDir) > 0)
    {
        usedir = true;

        if(_stat(Configuration.SSDir, &unusedstat) == -1 && !CreateDirectory(Configuration.SSDir, NULL))
            usedir = false;
    }

    if(usedir)
        sprintf(filename, "%s\\%s", Configuration.SSDir, Configuration.SSName);
    else
        sprintf(filename, "%s", Configuration.SSName);

    // Find first unused screenshot number
    for(unsigned long n = 1; n <= 99999; ++n)
    {
        sprintf(path, "%s%0*d%s", filename, Configuration.SSMinNumChars, n, strImageExtensions[Configuration.SSFormat]);
        if (_stat(path, &unusedstat) == -1)
        {
            HRESULT hr = D3DXSaveSurfaceToFile(path, formats[Configuration.SSFormat], surface, NULL, NULL);
            if(SUCCEEDED(hr))
            {
                sprintf(filename, "%s%0*d", Configuration.SSName, Configuration.SSMinNumChars, n);
                StatusOverlay::setStatus(filename);
            }
            else
            {
                sprintf(filename, "Screenshot failed - D3DX Error %x", hr);
                StatusOverlay::setStatus(filename);
            }
            break;
        }
    }

    surface->Release();
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

void MacroFunctions::ToggleZoom() {
    Configuration.MGEFlags ^= ZOOM_ASPECT;
    displayFlag(ZOOM_ASPECT, "Zoom enabled", "Zoom disabled");
}

void MacroFunctions::IncreaseZoom() {
    if(Configuration.MGEFlags & ZOOM_ASPECT)
        Configuration.Zoom.zoom = std::min(Configuration.Zoom.zoom + 0.0625, 8.0);
}

void MacroFunctions::DecreaseZoom() {
    if(Configuration.MGEFlags & ZOOM_ASPECT)
        Configuration.Zoom.zoom = std::max(1.0, Configuration.Zoom.zoom - 0.0625);
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

void MacroFunctions::MoveForward3PCam() {
    DECLARE_MWBRIDGE
    if(mwBridge->is3rdPerson() && !mwBridge->IsMenu())
        Configuration.Offset3rdPerson.y = std::min(-25.0, Configuration.Offset3rdPerson.y * 0.96);
}

void MacroFunctions::MoveBack3PCam() {
    DECLARE_MWBRIDGE
    if(mwBridge->is3rdPerson() && !mwBridge->IsMenu())
        Configuration.Offset3rdPerson.y = std::max(-2500.0, Configuration.Offset3rdPerson.y * 1.04);
}

void MacroFunctions::MoveLeft3PCam() {
    DECLARE_MWBRIDGE
    if(mwBridge->is3rdPerson() && !mwBridge->IsMenu())
        Configuration.Offset3rdPerson.x = std::max(-125.0, Configuration.Offset3rdPerson.x - 1.0);
}

void MacroFunctions::MoveRight3PCam() {
    DECLARE_MWBRIDGE
    if(mwBridge->is3rdPerson() && !mwBridge->IsMenu())
        Configuration.Offset3rdPerson.x = std::min(125.0, Configuration.Offset3rdPerson.x + 1.0);
}

void MacroFunctions::MoveDown3PCam() {
    DECLARE_MWBRIDGE
    if(mwBridge->is3rdPerson() && !mwBridge->IsMenu())
        Configuration.Offset3rdPerson.z = std::max(-125.0, Configuration.Offset3rdPerson.z - 1.0);
}

void MacroFunctions::MoveUp3PCam() {
    DECLARE_MWBRIDGE
    if(mwBridge->is3rdPerson() && !mwBridge->IsMenu())
        Configuration.Offset3rdPerson.z = std::min(125.0, Configuration.Offset3rdPerson.z + 1.0);
}
