
#include "videobackground.h"
#include "mwbridge.h"
#include "support/log.h"



#define BINKSURFACE32       3
#define BINKCOPYALL         0x80000000

struct Bink {
    DWORD width, height;
    DWORD frames, frameNum, lastFrameNum;
    DWORD frameRate, frameRateDiv;

    // and a lot more junk
};

typedef Bink* (_stdcall* BinkOpen_t)(const char*, DWORD);
typedef void (_stdcall* BinkClose_t)(Bink*);
typedef int (_stdcall* BinkDoFrame_t)(Bink*);
typedef int (_stdcall* BinkCopyToBuffer_t)(Bink*, void*, int, DWORD, DWORD, DWORD, DWORD);
typedef int (_stdcall* BinkWait_t)(Bink*);
typedef void (_stdcall* BinkNextFrame_t)(Bink*);

BinkOpen_t BinkOpen;
BinkClose_t BinkClose;
BinkDoFrame_t BinkDoFrame;
BinkCopyToBuffer_t BinkCopyToBuffer;
BinkWait_t BinkWait;
BinkNextFrame_t BinkNextFrame;

IDirect3DDevice9* VideoPatch::d;
VideoBackground VideoPatch::v;
int VideoPatch::state;

const char* videoPath = "Data Files\\video\\menu_background.bik";



bool VideoBackground::init() {

    HMODULE hDLL = LoadLibrary("binkw32.dll");
    if (hDLL == NULL) {
        return false;
    }

    BinkOpen = (BinkOpen_t)GetProcAddress(hDLL, "_BinkOpen@8");
    BinkClose = (BinkClose_t)GetProcAddress(hDLL, "_BinkClose@4");
    BinkDoFrame = (BinkDoFrame_t)GetProcAddress(hDLL, "_BinkDoFrame@4");
    BinkCopyToBuffer = (BinkCopyToBuffer_t)GetProcAddress(hDLL, "_BinkCopyToBuffer@28");
    BinkWait = (BinkWait_t)GetProcAddress(hDLL, "_BinkWait@4");
    BinkNextFrame = (BinkNextFrame_t)GetProcAddress(hDLL, "_BinkNextFrame@4");

    // If there is no replacer installed, signal failure but not an error
    if (GetFileAttributes(videoPath) == INVALID_FILE_ATTRIBUTES) {
        return false;
    }

    return true;
}

bool VideoBackground::begin(IDirect3DDevice9* device) {
    video = BinkOpen(videoPath, 0);
    if (!video) {
        LOG::logline("!! Video renderer: Bink failed to open video file.");
        end();
        return false;
    }

    HRESULT hr = device->CreateOffscreenPlainSurface(video->width, video->height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surface, 0);
    if (hr != D3D_OK) {
        LOG::logline("!! Video renderer: Failed to create a surface for video output.");
        end();
        return false;
    }

    return true;
}

void VideoBackground::render(IDirect3DDevice9* device) {
    // Check if it's time to decode another frame
    if (!BinkWait(video)) {
        D3DLOCKED_RECT rect;

        // Decode audio/video
        BinkDoFrame(video);
        if (surface->LockRect(&rect, 0, D3DLOCK_DISCARD) == D3D_OK) {
            BinkCopyToBuffer(video, rect.pBits, rect.Pitch, video->height, 0, 0, BINKSURFACE32 | BINKCOPYALL);
            surface->UnlockRect();
        }

        // Advance frame; loops automatically
        BinkNextFrame(video);
    }

    // Blit over background
    IDirect3DSurface9* backbuffer;
    device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
    device->StretchRect(surface, 0, backbuffer, 0, D3DTEXF_LINEAR);
    backbuffer->Release();
}

void VideoBackground::end() {
    if (video) {
        BinkClose(video);
        video = 0;
    }

    if (surface) {
        surface->Release();
        surface = 0;
    }
}



struct VideoState {
    enum {
        PreMainScreen = 0,
        WaitForMain = 1,
        Playing = 2,
        Done = -1
    };
};

void VideoPatch::start(IDirect3DDevice9* device) {
    if (state == VideoState::PreMainScreen) {
        d = device;
        if (v.init()) {
            state = VideoState::WaitForMain;
            MWBridge::get()->redirectMenuBackground(VideoPatch::patch);
        }
        else {
            state = VideoState::Done;
        }
    }
}

void VideoPatch::monitor(IDirect3DDevice9* device) {
    auto mwBridge = MWBridge::get();

    if (state == VideoState::WaitForMain) {
        // Wait until pre-main menu loading screen is gone
        if (!mwBridge->isLoadingBar()) {
            if (v.begin(device)) {
                state = VideoState::Playing;
            }
            else {
                state = VideoState::Done;
            }
        }
    }
    else if (state == VideoState::Playing && mwBridge->isLoadingBar()) {
        // Release when first loading bar appears (includes new game cutscene)
        state = VideoState::Done;
        mwBridge->redirectMenuBackground(nullptr);
        v.end();
    }
}

void _stdcall VideoPatch::patch(int x) {
    if (state == VideoState::Playing) {
        v.render(d);
    }
}
