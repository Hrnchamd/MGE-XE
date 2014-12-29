
#include "support/winheader.h"
#include "support/strsec.h"
#include "support/log.h"
#include "mge/configuration.h"
#include "mge/mgeversion.h"
#include "mwse/mgebridge.h"

extern void * CreateD3DWrapper(UINT);
extern void * CreateInputWrapper(void *);

static FARPROC getProc1(const char *lib, const char *funcname);
static void fixMWSEProblems(HMODULE dll);

static const char *welcomeMessage = XE_VERSION_STRING;
static bool isMW;



extern "C" BOOL _stdcall DllMain(HANDLE hModule, DWORD reason, void * unused)
{
    if(reason != DLL_PROCESS_ATTACH)
        return true;

    // Check if MW is in-process, avoid hooking the CS
    isMW = bool(GetModuleHandle("Morrowind.exe"));

    if(isMW)
    {
        LOG::open("mgeXE.log");
        LOG::logline(welcomeMessage);

        if(!Configuration.LoadSettings())
        {
            LOG::logline("Error: MGE is not configured. MGE will be disabled for this session.");
            isMW = false;
            return true;
        }

        if(Configuration.MGEFlags & MGE_DISABLED)
            isMW = false;

        if(~Configuration.MGEFlags & MWSE_DISABLED)
        {
            // Load MWSE dll, it injects by itself
            HMODULE dll = LoadLibraryA("MWSE.dll");
            if(dll)
            {
                if(~Configuration.MGEFlags & MGE_DISABLED)
                    MWSE_MGEPlugin::init(dll);

                LOG::logline("MWSE dll injected");
            }
            else
            {
                LOG::logline("MWSE dll failed to load");
            }
        }
    }

    return true;
}

extern "C" void * _stdcall FakeDirect3DCreate(UINT version)
{
    // Wrap Morrowind only, not TESCS
    if(isMW)
    {
        return CreateD3DWrapper(version);
    }
    else
    {
        typedef void * (_stdcall * D3DProc) (UINT);
        D3DProc func = (D3DProc)getProc1("\\d3d8.dll", "Direct3DCreate8");
        return (func)(version);
    }
}

extern "C" HRESULT _stdcall FakeDirectInputCreate(HINSTANCE a, DWORD b, REFIID c, void **d, void *e)
{
    typedef HRESULT (_stdcall * DInputProc) (HINSTANCE, DWORD, REFIID, void **, void *);
    DInputProc func = (DInputProc)getProc1("\\dinput8.dll", "DirectInput8Create");

    void *ret = 0;
    HRESULT hr = (func)(a, b, c, &ret, e);

    if(hr == S_OK)
    {
        if(isMW)
            *d = CreateInputWrapper(ret);
        else
            *d = ret;
    }

    return hr;
}


FARPROC getProc1(const char *lib, const char *funcname)
{
    // Get the address of a single function from a dll
    char path[MAX_PATH];
    GetSystemDirectoryA(path, MAX_PATH);
    strcat_s(path, MAX_PATH, lib);
    HMODULE dll = LoadLibraryA(path);
    return GetProcAddress(dll, funcname);
}
