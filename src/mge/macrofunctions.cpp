
#include "proxydx/d3d8header.h"
#include "mmefunctiondefs.h"
#include "configuration.h"
#include "mwbridge.h"
#include "statusoverlay.h"
#include "distantland.h"
#include "postshaders.h"
#include "support/pngsave.h"

#include <cctype>
#include <cstdio>
#include <cstring>



enum SuffixFormatting {
    SuffixFormatting_Timestamp = 0,
    SuffixFormatting_Ordinal,
    SuffixFormatting_NameOrdinal,
    SuffixFormatting_NameGameTimeOrdinal
};

static void saveScreenshot(IDirect3DSurface9* surface);
static int nextScreenshotOrdinal(const char* path);


void MacroFunctions::TakeScreenshot() {
    // Requires distant land to be loaded
    if (!DistantLand::ready) {
        return;
    }

    if (MWBridge::get()->IsMenu()) {
        // Save screen including UI
        IDirect3DSurface9* surface = DistantLand::captureScreen();
        saveScreenshot(surface);
        if (surface) {
            surface->Release();
        }
    } else {
        // Request distant land to save screen without UI
        DistantLand::requestCaptureNoUI(&saveScreenshot);
    }
}

static void saveScreenshot(IDirect3DSurface9* surface) {
    const char* strImageExtensions[] = { ".bmp", ".jpg", ".dds", ".png", ".tga" };
    const D3DXIMAGE_FILEFORMAT formats[] = { D3DXIFF_BMP, D3DXIFF_JPG, D3DXIFF_DDS, D3DXIFF_PNG, D3DXIFF_TGA };

    char filename[MAX_PATH], path[MAX_PATH];
    const char* dir = "./screenshots";
    int str_sz;

    if (!surface) {
        StatusOverlay::setStatus("Screenshot failed - Surface error");
        return;
    }

    // Set up path
    if (strlen(Configuration.SSDir) > 0) {
        dir = Configuration.SSDir;
    }

    if (GetFileAttributes(dir) == INVALID_FILE_ATTRIBUTES) {
        if (!CreateDirectory(dir, NULL)) {
            std::snprintf(path, sizeof(path), "Screenshot failed - Cannot create directory %s", dir);
            StatusOverlay::setStatus(path);;
            return;
        }
    }

    // Append trailing space to name, if not blank
    str_sz = std::strlen(Configuration.SSName);
    if (str_sz > 0 && Configuration.SSName[str_sz - 1] != ' ' && (str_sz + 2) <= sizeof(Configuration.SSName)) {
        std::strcpy(Configuration.SSName + str_sz, " ");
    }

    // Construct name + suffix
    switch (Configuration.SSSuffix) {
    case SuffixFormatting_Timestamp:
    default: {
        SYSTEMTIME t;
        GetLocalTime(&t);
        std::snprintf(filename, sizeof(filename), "%s%04d-%02d-%02d %02d.%02d.%02d.%03d",
                      Configuration.SSName, t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    }
    break;
    case SuffixFormatting_Ordinal: {
        int nextOrdinal = nextScreenshotOrdinal(dir);
        std::snprintf(filename, sizeof(filename), "%s%04d", Configuration.SSName, nextOrdinal);
        ++nextOrdinal;
    }
    break;
    case SuffixFormatting_NameOrdinal: {
        int nextOrdinal = nextScreenshotOrdinal(dir);
        const char* name = MWBridge::get()->getPlayerName();
        if (!name) {
            name = "Menu";
        }

        std::snprintf(filename, sizeof(filename), "%s%s %04d", Configuration.SSName, name, nextOrdinal);
        ++nextOrdinal;
    }
    break;
    case SuffixFormatting_NameGameTimeOrdinal: {
        auto mwBridge = MWBridge::get();
        int nextOrdinal = nextScreenshotOrdinal(dir);
        const char* name = mwBridge->getPlayerName();
        const char* dayLocalized = *(const char**)mwBridge->getGMSTPointer(0x1e1);
        if (!name) {
            name = "Menu";
        }

        float gametime = mwBridge->getGameHour();
        int day = mwBridge->getDaysPassed();
        int hour = int(gametime), minute = int(60.0 * gametime) % 60;

        std::snprintf(filename, sizeof(filename), "%s%s, %s %d, %02d.%02d %04d",
                      Configuration.SSName, name, dayLocalized, day, hour, minute, nextOrdinal);
    }
    break;
    }

    str_sz = std::snprintf(path, sizeof(path), "%s\\%s%s", dir, filename, strImageExtensions[Configuration.SSFormat]);
    if (str_sz >= sizeof(path)) {
        StatusOverlay::setStatus("Screenshot failed - Path too long");
        return;
    }

    // Check for overwrite
    if (GetFileAttributes(path) != INVALID_FILE_ATTRIBUTES) {
        std::snprintf(path, sizeof(path), "Screenshot failed - %s already exists", filename);
        StatusOverlay::setStatus(path);
        return;
    }

    // Save screenshot to desired format
    if (Configuration.SSFormat == D3DXIFF_PNG) {
        // D3DX PNG support does full compression which takes >1 sec to save an image
        // Use a non-compressing PNG encoder for reasonable screenshot times
        bool success = false;
        D3DSURFACE_DESC desc;
        D3DLOCKED_RECT rect;
        surface->GetDesc(&desc);

        if (surface->LockRect(&rect, NULL, D3DLOCK_READONLY) == D3D_OK) {
            success = pngSaveBGRA(path, rect.pBits, desc.Width, desc.Height, rect.Pitch);
            surface->UnlockRect();
        }

        StatusOverlay::setStatus(success ? filename : "Screenshot failed");
    }
    else {
        HRESULT hr = D3DXSaveSurfaceToFile(path, formats[Configuration.SSFormat], surface, NULL, NULL);
        if (SUCCEEDED(hr)) {
            StatusOverlay::setStatus(filename);
        } else {
            std::snprintf(filename, sizeof(filename), "Screenshot failed - D3DX Error %lx", hr);
            StatusOverlay::setStatus(filename);
        }
    }
}

static int nextScreenshotOrdinal(const char* path) {
    static int nextOrdinal = -1;
    char findPattern[MAX_PATH];
    WIN32_FIND_DATA findData;

    if (nextOrdinal > 0) {
        return ++nextOrdinal;
    }

    nextOrdinal = 0;
    std::snprintf(findPattern, sizeof(findPattern), "%s\\*", path);

    HANDLE h = FindFirstFile(findPattern, &findData);
    if (h != INVALID_HANDLE_VALUE) {
        do {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                continue;
            }

            const char* lastSpace = std::strrchr(findData.cFileName, ' ');
            if (lastSpace && std::isdigit(lastSpace[1])) {
                nextOrdinal = std::max(nextOrdinal, std::atoi(lastSpace + 1));
            }
        } while (FindNextFile(h, &findData));

        FindClose(h);
    }

    return ++nextOrdinal;
}

static void displayFlag(DWORD flag, const char* en, const char* ds) {
    if (Configuration.MGEFlags & flag) {
        StatusOverlay::setStatus(en);
    } else {
        StatusOverlay::setStatus(ds);
    }
}

void MacroFunctions::ToggleStatusText() {
    Configuration.MGEFlags ^= DISPLAY_MESSAGES;

    if (Configuration.MGEFlags & DISPLAY_MESSAGES) {
        StatusOverlay::setStatus("Displaying status messages");
    }
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
    // Ignore if distant land is not loaded
    if (DistantLand::mapWorldSpaces.empty()) {
        return;
    }

    Configuration.MGEFlags ^= USE_DISTANT_LAND;
    displayFlag(USE_DISTANT_LAND, "Distant land enabled", "Distant land disabled");

    if (Configuration.MGEFlags & USE_DISTANT_LAND) {
        DistantLand::reloadShaders();
        StatusOverlay::setStatus("Distant land and FFE shaders reloaded");
    }
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
    if (Configuration.MGEFlags & USE_FFESHADER) {
        if (Configuration.PerPixelLightFlags == 0) {
            Configuration.PerPixelLightFlags = 1;
            StatusOverlay::setStatus("Per-pixel dynamic lighting - interiors only");
        } else {
            Configuration.MGEFlags ^= USE_FFESHADER;
            StatusOverlay::setStatus("Standard dynamic lighting");
        }
    } else {
        Configuration.MGEFlags ^= USE_FFESHADER;
        Configuration.PerPixelLightFlags = 0;
        StatusOverlay::setStatus("Per-pixel dynamic lighting");
    }
}

void MacroFunctions::ToggleTransparencyAA() {
    Configuration.MGEFlags ^= TRANSPARENCY_AA;
    displayFlag(TRANSPARENCY_AA, "Transparency AA enabled", "Transparency AA disabled");
}

void MacroFunctions::IncreaseViewRange() {
    auto mwBridge = MWBridge::get();
    float r = mwBridge->GetViewDistance();
    mwBridge->SetViewDistance(std::min(7168.0f, r + 512.0f));
}

void MacroFunctions::DecreaseViewRange() {
    auto mwBridge = MWBridge::get();
    float r = mwBridge->GetViewDistance();
    mwBridge->SetViewDistance(std::max(2500.0f, r - 512.0f));
}

void MacroFunctions::ToggleZoom() {
    Configuration.MGEFlags ^= ZOOM_ASPECT;
    displayFlag(ZOOM_ASPECT, "Zoom enabled", "Zoom disabled");
}

void MacroFunctions::ResetEnableZoom() {
    Configuration.MGEFlags |= ZOOM_ASPECT;
    Configuration.CameraEffects.zoom = 1.0;
    StatusOverlay::setStatus("Zoom reset");
}

void MacroFunctions::IncreaseZoom() {
    Configuration.MGEFlags |= ZOOM_ASPECT;
    Configuration.CameraEffects.zoom = std::min(Configuration.CameraEffects.zoom * 1.0078125f, 40.0f);
}

void MacroFunctions::DecreaseZoom() {
    Configuration.MGEFlags |= ZOOM_ASPECT;
    Configuration.CameraEffects.zoom = std::max(1.0f, Configuration.CameraEffects.zoom / 1.0078125f);
}

void MacroFunctions::ToggleCrosshair() {
    MWBridge::get()->ToggleCrosshair();
}

void MacroFunctions::NextTrack() {
    MWBridge::get()->SkipToNextTrack();
}

void MacroFunctions::DisableMusic() {
    MWBridge::get()->DisableMusic();
}

void MacroFunctions::IncreaseFOV() {
    Configuration.ScreenFOV = std::min(Configuration.ScreenFOV + 1.0f, 150.0f);
}

void MacroFunctions::DecreaseFOV() {
    Configuration.ScreenFOV = std::max(60.0f, Configuration.ScreenFOV - 1.0f);
}

void MacroFunctions::HaggleMore1() {
    MWBridge::get()->HaggleMore(1);
}
void MacroFunctions::HaggleMore10() {
    MWBridge::get()->HaggleMore(10);
}
void MacroFunctions::HaggleMore100() {
    MWBridge::get()->HaggleMore(100);
}
void MacroFunctions::HaggleMore1000() {
    MWBridge::get()->HaggleMore(1000);
}
void MacroFunctions::HaggleMore10000() {
    MWBridge::get()->HaggleMore(10000);
}

void MacroFunctions::HaggleLess1() {
    MWBridge::get()->HaggleLess(1);
}
void MacroFunctions::HaggleLess10() {
    MWBridge::get()->HaggleLess(10);
}
void MacroFunctions::HaggleLess100() {
    MWBridge::get()->HaggleLess(100);
}
void MacroFunctions::HaggleLess1000() {
    MWBridge::get()->HaggleLess(1000);
}
void MacroFunctions::HaggleLess10000() {
    MWBridge::get()->HaggleLess(10000);
}

static void displayCamPosition() {
    char str[256];
    std::snprintf(str, sizeof(str), "Camera offset at (%.0f, %.0f, %.0f)",
                  Configuration.Offset3rdPerson.x, Configuration.Offset3rdPerson.y, Configuration.Offset3rdPerson.z);
    StatusOverlay::setStatus(str);
}

void MacroFunctions::MoveForward3PCam() {
    auto mwBridge = MWBridge::get();
    if (mwBridge->is3rdPerson() && !mwBridge->IsMenu()) {
        Configuration.Offset3rdPerson.y = std::min(-25.0f, Configuration.Offset3rdPerson.y * 0.96f);
        displayCamPosition();
    }
}

void MacroFunctions::MoveBack3PCam() {
    auto mwBridge = MWBridge::get();
    if (mwBridge->is3rdPerson() && !mwBridge->IsMenu()) {
        Configuration.Offset3rdPerson.y = std::max(-2500.0f, Configuration.Offset3rdPerson.y * 1.04f);
        displayCamPosition();
    }
}

void MacroFunctions::MoveLeft3PCam() {
    auto mwBridge = MWBridge::get();
    if (mwBridge->is3rdPerson() && !mwBridge->IsMenu()) {
        Configuration.Offset3rdPerson.x = std::max(-125.0f, Configuration.Offset3rdPerson.x - 1.0f);
        displayCamPosition();
    }
}

void MacroFunctions::MoveRight3PCam() {
    auto mwBridge = MWBridge::get();
    if (mwBridge->is3rdPerson() && !mwBridge->IsMenu()) {
        Configuration.Offset3rdPerson.x = std::min(125.0f, Configuration.Offset3rdPerson.x + 1.0f);
        displayCamPosition();
    }
}

void MacroFunctions::MoveDown3PCam() {
    auto mwBridge = MWBridge::get();
    if (mwBridge->is3rdPerson() && !mwBridge->IsMenu()) {
        Configuration.Offset3rdPerson.z = std::max(-125.0f, Configuration.Offset3rdPerson.z - 1.0f);
        displayCamPosition();
    }
}

void MacroFunctions::MoveUp3PCam() {
    auto mwBridge = MWBridge::get();
    if (mwBridge->is3rdPerson() && !mwBridge->IsMenu()) {
        Configuration.Offset3rdPerson.z = std::min(125.0f, Configuration.Offset3rdPerson.z + 1.0f);
        displayCamPosition();
    }
}
