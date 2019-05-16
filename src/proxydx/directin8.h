#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class ProxyDirectInput : public IDirectInput8 {
public:
    IDirectInput8* realInput;

    ProxyDirectInput(IDirectInput8* real);

    /*** IUnknown methods ***/
    HRESULT _stdcall QueryInterface (REFIID riid, LPVOID* ppvObj);
    ULONG _stdcall AddRef();
    ULONG _stdcall Release();

    /*** IDirectInput8W methods ***/
    HRESULT _stdcall CreateDevice(REFGUID r,IDirectInputDevice8A** device,IUnknown* unused);
    HRESULT _stdcall EnumDevices(DWORD a,LPDIENUMDEVICESCALLBACKA b,void* c,DWORD d);
    HRESULT _stdcall GetDeviceStatus(REFGUID r);
    HRESULT _stdcall RunControlPanel(HWND a,DWORD b);
    HRESULT _stdcall Initialize(HINSTANCE a,DWORD b);
    HRESULT _stdcall FindDevice(REFGUID a,LPCSTR b,LPGUID c);
    HRESULT _stdcall EnumDevicesBySemantics(LPCSTR a,LPDIACTIONFORMATA b,LPDIENUMDEVICESBYSEMANTICSCBA c,void* d,DWORD e);
    HRESULT _stdcall ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK a,LPDICONFIGUREDEVICESPARAMSA b,DWORD c,void* d);

    // Factory methods
    virtual IDirectInputDevice8* factoryProxyInput(IDirectInputDevice8* device, REFGUID g);
};

class ProxyInputDevice : public IDirectInputDevice8 {
public:
    IDirectInputDevice8* realDevice;

    ProxyInputDevice(IDirectInputDevice8* device);

    /*** IUnknown methods ***/
    HRESULT _stdcall QueryInterface(REFIID riid,void** ppvObj);
    ULONG _stdcall AddRef();
    ULONG _stdcall Release();

    /*** IDirectInputDevice8W methods ***/
    HRESULT _stdcall GetCapabilities(LPDIDEVCAPS a);
    HRESULT _stdcall EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA a,void* b,DWORD c);
    HRESULT _stdcall GetProperty(REFGUID a,DIPROPHEADER* b);
    HRESULT _stdcall SetProperty(REFGUID a,const DIPROPHEADER* b);
    HRESULT _stdcall Acquire();
    HRESULT _stdcall Unacquire();
    HRESULT _stdcall GetDeviceState(DWORD a,void* b);
    HRESULT _stdcall GetDeviceData(DWORD a,DIDEVICEOBJECTDATA* b,DWORD* c,DWORD d);
    HRESULT _stdcall SetDataFormat(const DIDATAFORMAT* a);
    HRESULT _stdcall SetEventNotification(HANDLE a);
    HRESULT _stdcall SetCooperativeLevel(HWND a,DWORD b);
    HRESULT _stdcall GetObjectInfo(DIDEVICEOBJECTINSTANCE* a,DWORD b,DWORD c);
    HRESULT _stdcall GetDeviceInfo(DIDEVICEINSTANCE* a);
    HRESULT _stdcall RunControlPanel(HWND a,DWORD b);
    HRESULT _stdcall Initialize(HINSTANCE a,DWORD b,REFGUID c);
    HRESULT _stdcall CreateEffect(REFGUID a,const DIEFFECT* b,LPDIRECTINPUTEFFECT* c,IUnknown* d);
    HRESULT _stdcall EnumEffects(LPDIENUMEFFECTSCALLBACK a,void* b,DWORD c);
    HRESULT _stdcall GetEffectInfo(DIEFFECTINFO* a,REFGUID b);
    HRESULT _stdcall GetForceFeedbackState(DWORD* a);
    HRESULT _stdcall SendForceFeedbackCommand(DWORD a);
    HRESULT _stdcall EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK a,void* b,DWORD c);
    HRESULT _stdcall Escape(DIEFFESCAPE* a);
    HRESULT _stdcall Poll();
    HRESULT _stdcall SendDeviceData(DWORD a,const DIDEVICEOBJECTDATA* b,DWORD* c,DWORD d);
    HRESULT _stdcall EnumEffectsInFile(const char* a,LPDIENUMEFFECTSINFILECALLBACK b,void* c,DWORD d);
    HRESULT _stdcall WriteEffectToFile(const char* a,DWORD b,DIFILEEFFECT* c,DWORD d);
    HRESULT _stdcall BuildActionMap(DIACTIONFORMAT* a,const char* b,DWORD c);
    HRESULT _stdcall SetActionMap(DIACTIONFORMAT* a,const char* b,DWORD c);
    HRESULT _stdcall GetImageInfo(DIDEVICEIMAGEINFOHEADER* a);
};
