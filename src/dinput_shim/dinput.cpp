#define STRICT
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINDOWS 0x0410
#define WINVER 0x0410
#include <windows.h>
#include <objbase.h>

typedef HRESULT (__stdcall *MYPROC)(HINSTANCE,DWORD,REFIID,void**,void*);

extern "C" HRESULT __stdcall FakeDirectInputCreate(HINSTANCE a, DWORD b, REFIID c, void **d, void *e)
{
    HMODULE FakeD3Ddll = LoadLibrary("d3d8.dll");
    MYPROC func = (MYPROC)GetProcAddress(FakeD3Ddll, "DirectInput8Create");
    return (func)(a,b,c,d,e);
}
