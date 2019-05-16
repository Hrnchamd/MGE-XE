
#include "directin8.h"



ProxyDirectInput::ProxyDirectInput(IDirectInput8* real) : realInput(real) {}

HRESULT _stdcall ProxyDirectInput::QueryInterface (REFIID riid, LPVOID* ppvObj) {
    return realInput->QueryInterface(riid,ppvObj);
}
ULONG _stdcall ProxyDirectInput::AddRef(void) {
    return realInput->AddRef();
}
ULONG _stdcall ProxyDirectInput::Release(void) {
    return realInput->Release();
}

HRESULT _stdcall ProxyDirectInput::CreateDevice(REFGUID r, IDirectInputDevice8A** device, IUnknown* unk) {
    IDirectInputDevice8A* realDevice;
    HRESULT hr = realInput->CreateDevice(r, &realDevice, unk);

    if (hr == DI_OK) {
        *device = factoryProxyInput(realDevice, r);
    }

    return hr;
}

HRESULT _stdcall ProxyDirectInput::EnumDevices(DWORD a,LPDIENUMDEVICESCALLBACKA b,void* c,DWORD d) {
    return realInput->EnumDevices(a,b,c,d);
}
HRESULT _stdcall ProxyDirectInput::GetDeviceStatus(REFGUID r) {
    return realInput->GetDeviceStatus(r);
}
HRESULT _stdcall ProxyDirectInput::RunControlPanel(HWND a,DWORD b) {
    return realInput->RunControlPanel(a,b);
}
HRESULT _stdcall ProxyDirectInput::Initialize(HINSTANCE a,DWORD b) {
    return realInput->Initialize(a,b);
}
HRESULT _stdcall ProxyDirectInput::FindDevice(REFGUID a,LPCSTR b,LPGUID c) {
    return realInput->FindDevice(a,b,c);
}
HRESULT _stdcall ProxyDirectInput::EnumDevicesBySemantics(LPCSTR a,LPDIACTIONFORMATA b,LPDIENUMDEVICESBYSEMANTICSCBA c,void* d,DWORD e) {
    return realInput->EnumDevicesBySemantics(a,b,c,d,e);
}
HRESULT _stdcall ProxyDirectInput::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK a,LPDICONFIGUREDEVICESPARAMSA b,DWORD c,void* d) {
    return realInput->ConfigureDevices(a,b,c,d);
}

IDirectInputDevice8* ProxyDirectInput::factoryProxyInput(IDirectInputDevice8* device, REFGUID g) {
    return device;
}



ProxyInputDevice::ProxyInputDevice(IDirectInputDevice8* device) : realDevice(device) { }

HRESULT _stdcall ProxyInputDevice::QueryInterface(REFIID riid,void** ppvObj) {
    return realDevice->QueryInterface(riid,ppvObj);
}
ULONG _stdcall ProxyInputDevice::AddRef() {
    return realDevice->AddRef();
}
ULONG _stdcall ProxyInputDevice::Release() {
    return realDevice->Release();
}

HRESULT _stdcall ProxyInputDevice::GetCapabilities(LPDIDEVCAPS a) {
    return realDevice->GetCapabilities(a);
}
HRESULT _stdcall ProxyInputDevice::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA a,void* b,DWORD c) {
    return realDevice->EnumObjects(a,b,c);
}
HRESULT _stdcall ProxyInputDevice::GetProperty(REFGUID a,DIPROPHEADER* b) {
    return realDevice->GetProperty(a,b);
}
HRESULT _stdcall ProxyInputDevice::SetProperty(REFGUID a,const DIPROPHEADER* b) {
    return realDevice->SetProperty(a,b);
}
HRESULT _stdcall ProxyInputDevice::Acquire() {
    return realDevice->Acquire();
}
HRESULT _stdcall ProxyInputDevice::Unacquire() {
    return realDevice->Unacquire();
}
HRESULT _stdcall ProxyInputDevice::GetDeviceState(DWORD a,void* b) {
    return realDevice->GetDeviceState(a,b);
}
HRESULT _stdcall ProxyInputDevice::GetDeviceData(DWORD a,DIDEVICEOBJECTDATA* b,DWORD* c,DWORD d) {
    return realDevice->GetDeviceData(a,b,c,d);
}
HRESULT _stdcall ProxyInputDevice::SetDataFormat(const DIDATAFORMAT* a) {
    return realDevice->SetDataFormat(a);
}
HRESULT _stdcall ProxyInputDevice::SetEventNotification(HANDLE a) {
    return realDevice->SetEventNotification(a);
}
HRESULT _stdcall ProxyInputDevice::SetCooperativeLevel(HWND a,DWORD b) {
    return realDevice->SetCooperativeLevel(a,b);
}
HRESULT _stdcall ProxyInputDevice::GetObjectInfo(DIDEVICEOBJECTINSTANCE* a,DWORD b,DWORD c) {
    return realDevice->GetObjectInfo(a,b,c);
}
HRESULT _stdcall ProxyInputDevice::GetDeviceInfo(DIDEVICEINSTANCE* a) {
    return realDevice->GetDeviceInfo(a);
}
HRESULT _stdcall ProxyInputDevice::RunControlPanel(HWND a,DWORD b) {
    return realDevice->RunControlPanel(a,b);
}
HRESULT _stdcall ProxyInputDevice::Initialize(HINSTANCE a,DWORD b,REFGUID c) {
    return realDevice->Initialize(a,b,c);
}
HRESULT _stdcall ProxyInputDevice::CreateEffect(REFGUID a,const DIEFFECT* b,LPDIRECTINPUTEFFECT* c,IUnknown* d) {
    return realDevice->CreateEffect(a,b,c,d);
}
HRESULT _stdcall ProxyInputDevice::EnumEffects(LPDIENUMEFFECTSCALLBACK a,void* b,DWORD c) {
    return realDevice->EnumEffects(a,b,c);
}
HRESULT _stdcall ProxyInputDevice::GetEffectInfo(DIEFFECTINFO* a,REFGUID b) {
    return realDevice->GetEffectInfo(a,b);
}
HRESULT _stdcall ProxyInputDevice::GetForceFeedbackState(DWORD* a) {
    return realDevice->GetForceFeedbackState(a);
}
HRESULT _stdcall ProxyInputDevice::SendForceFeedbackCommand(DWORD a) {
    return realDevice->SendForceFeedbackCommand(a);
}
HRESULT _stdcall ProxyInputDevice::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK a,void* b,DWORD c) {
    return realDevice->EnumCreatedEffectObjects(a,b,c);
}
HRESULT _stdcall ProxyInputDevice::Escape(DIEFFESCAPE* a) {
    return realDevice->Escape(a);
}
HRESULT _stdcall ProxyInputDevice::Poll() {
    return realDevice->Poll();
}
HRESULT _stdcall ProxyInputDevice::SendDeviceData(DWORD a,const DIDEVICEOBJECTDATA* b,DWORD* c,DWORD d) {
    return realDevice->SendDeviceData(a,b,c,d);
}
HRESULT _stdcall ProxyInputDevice::EnumEffectsInFile(const char* a,LPDIENUMEFFECTSINFILECALLBACK b,void* c,DWORD d) {
    return realDevice->EnumEffectsInFile(a,b,c,d);
}
HRESULT _stdcall ProxyInputDevice::WriteEffectToFile(const char* a,DWORD b,DIFILEEFFECT* c,DWORD d) {
    return realDevice->WriteEffectToFile(a,b,c,d);
}
HRESULT _stdcall ProxyInputDevice::BuildActionMap(DIACTIONFORMAT* a,const char* b,DWORD c) {
    return realDevice->BuildActionMap(a,b,c);
}
HRESULT _stdcall ProxyInputDevice::SetActionMap(DIACTIONFORMAT* a,const char* b,DWORD c) {
    return realDevice->SetActionMap(a,b,c);
}
HRESULT _stdcall ProxyInputDevice::GetImageInfo(DIDEVICEIMAGEINFOHEADER* a) {
    return realDevice->GetImageInfo(a);
}
