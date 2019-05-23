#pragma once

#include "proxydx/directin8.h"



class MGEProxyDirectInput : public ProxyDirectInput {
public:
    enum KeyBehavior { TAP, PUSH, HAMMER, AHAMMER, DISALLOW };
    static bool mouseClick;

    static void changeKeyBehavior(DWORD key, KeyBehavior kb, bool on);

public:
    MGEProxyDirectInput(IDirectInput8* real) : ProxyDirectInput(real) {}

    IDirectInputDevice8* factoryProxyInput(IDirectInputDevice8* device, REFGUID g);
};
