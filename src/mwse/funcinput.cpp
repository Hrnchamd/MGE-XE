
#include "funcinput.h"
#include "mge/mgedinput.h"



MWSEINSTRUCTION_DECLARE_VTABLE(mwseTapKey)

// TapKey
bool mwseTapKey::execute(mwseInstruction* _this) {
    VMREGTYPE key;
    if (!_this->vmPop(&key)) { return false; }

    MGEProxyDirectInput::changeKeyBehavior(key, MGEProxyDirectInput::TAP, true);
    return true;
}

MWSEINSTRUCTION_DECLARE_VTABLE(mwsePushKey)

// PushKey
bool mwsePushKey::execute(mwseInstruction* _this) {
    VMREGTYPE key;
    if (!_this->vmPop(&key)) { return false; }

    MGEProxyDirectInput::changeKeyBehavior(key, MGEProxyDirectInput::PUSH, true);
    return true;
}

MWSEINSTRUCTION_DECLARE_VTABLE(mwseReleaseKey)

// ReleaseKey
bool mwseReleaseKey::execute(mwseInstruction* _this) {
    VMREGTYPE key;
    if (!_this->vmPop(&key)) { return false; }

    MGEProxyDirectInput::changeKeyBehavior(key, MGEProxyDirectInput::PUSH, false);
    return true;
}

MWSEINSTRUCTION_DECLARE_VTABLE(mwseHammerKey)

// HammerKey
bool mwseHammerKey::execute(mwseInstruction* _this) {
    VMREGTYPE key;
    if (!_this->vmPop(&key)) { return false; }

    MGEProxyDirectInput::changeKeyBehavior(key, MGEProxyDirectInput::HAMMER, true);
    return true;
}

MWSEINSTRUCTION_DECLARE_VTABLE(mwseUnhammerKey)

// UnhammerKey
bool mwseUnhammerKey::execute(mwseInstruction* _this) {
    VMREGTYPE key;
    if (!_this->vmPop(&key)) { return false; }

    MGEProxyDirectInput::changeKeyBehavior(key, MGEProxyDirectInput::HAMMER, false);
    return true;
}

MWSEINSTRUCTION_DECLARE_VTABLE(mwseAHammerKey)

// AHammerKey
bool mwseAHammerKey::execute(mwseInstruction* _this) {
    VMREGTYPE key;
    if (!_this->vmPop(&key)) { return false; }

    MGEProxyDirectInput::changeKeyBehavior(key, MGEProxyDirectInput::AHAMMER, true);
    return true;
}

MWSEINSTRUCTION_DECLARE_VTABLE(mwseAUnhammerKey)

// AUnhammerKey
bool mwseAUnhammerKey::execute(mwseInstruction* _this) {
    VMREGTYPE key;
    if (!_this->vmPop(&key)) { return false; }

    MGEProxyDirectInput::changeKeyBehavior(key, MGEProxyDirectInput::AHAMMER, false);
    return true;
}

MWSEINSTRUCTION_DECLARE_VTABLE(mwseDisallowKey)

// DisallowKey
bool mwseDisallowKey::execute(mwseInstruction* _this) {
    VMREGTYPE key;
    if (!_this->vmPop(&key)) { return false; }

    MGEProxyDirectInput::changeKeyBehavior(key, MGEProxyDirectInput::DISALLOW, true);
    return true;
}

MWSEINSTRUCTION_DECLARE_VTABLE(mwseAllowKey)

// AllowKey
bool mwseAllowKey::execute(mwseInstruction* _this) {
    VMREGTYPE key;
    if (!_this->vmPop(&key)) { return false; }

    MGEProxyDirectInput::changeKeyBehavior(key, MGEProxyDirectInput::DISALLOW, false);
    return true;
}
