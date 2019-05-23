
#include "funchud.h"
#include "mge/userhud.h"

#include <string>



std::string currentHUDName;
MGEhud::hud_id currentHUD;


// Shared functions

void resetMWSEHud() {
    MGEhud::reset();
    currentHUD = MGEhud::invalid_hud_id;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseWipeHUDElements)

// WipeHUDElements
bool mwseWipeHUDElements::execute(mwseInstruction* _this) {
    resetMWSEHud();
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseWithHUD)

// WithHUD <string hud>
bool mwseWithHUD::execute(mwseInstruction* _this) {
    const char* hud = _this->vmPopString();
    if (!hud) { return false; }

    currentHUDName = hud;
    currentHUD = MGEhud::resolveName(hud);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseCancelWithHUD)

// CancelWithHUD
bool mwseCancelWithHUD::execute(mwseInstruction* _this) {
    currentHUDName.clear();
    currentHUD = MGEhud::invalid_hud_id;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseLoadHUD)

// LoadHUD <string hud> <string texture>
bool mwseLoadHUD::execute(mwseInstruction* _this) {
    const char* hud = _this->vmPopString();
    if (!hud) { return false; }

    const char* tex = _this->vmPopString();
    if (!tex) { return false; }

    MGEhud::load(hud, tex);

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwsePositionHUD)

// PositionHUD <string hud> <float x> <float y>
bool mwsePositionHUD::execute(mwseInstruction* _this) {
    VMFLOAT x, y;

    const char* hud = _this->vmPopString();
    if (!hud) { return false; }

    if (!_this->vmPop(&x)) { return false; }
    if (!_this->vmPop(&y)) { return false; }

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if (id != MGEhud::invalid_hud_id) {
        MGEhud::setPosition(id, x, y);
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseScaleHUD)

// ScaleHUD <string hud> <float xscale> <float yscale>
bool mwseScaleHUD::execute(mwseInstruction* _this) {
    VMFLOAT xscale, yscale;

    const char* hud = _this->vmPopString();
    if (!hud) { return false; }

    if (!_this->vmPop(&xscale)) { return false; }
    if (!_this->vmPop(&yscale)) { return false; }

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if (id != MGEhud::invalid_hud_id) {
        MGEhud::setScale(id, xscale, yscale);
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseFullscreenHUD)

// FullscreenHUD <string hud>
bool mwseFullscreenHUD::execute(mwseInstruction* _this) {
    const char* hud = _this->vmPopString();
    if (!hud) { return false; }

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if (id != MGEhud::invalid_hud_id) {
        MGEhud::setFullscreen(id);
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseEnableHUD)

// EnableHUD <string hud>
bool mwseEnableHUD::execute(mwseInstruction* _this) {
    const char* hud = _this->vmPopString();
    if (!hud) { return false; }

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if (id != MGEhud::invalid_hud_id) {
        MGEhud::enable(id);
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseDisableHUD)

// DisableHUD <string hud>
bool mwseDisableHUD::execute(mwseInstruction* _this) {
    const char* hud = _this->vmPopString();
    if (!hud) { return false; }

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if (id != MGEhud::invalid_hud_id) {
        MGEhud::disable(id);
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseChangeHUDTexture)

// ChangeHUDTexture <string hud> <string texture>
bool mwseChangeHUDTexture::execute(mwseInstruction* _this) {
    const char* hud = _this->vmPopString();
    if (!hud) { return false; }

    const char* tex = _this->vmPopString();
    if (!tex) { return false; }

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if (id != MGEhud::invalid_hud_id) {
        MGEhud::setTexture(id, tex);
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseChangeHUDEffect)

// ChangeHUDEffect <string hud> <string effect>
bool mwseChangeHUDEffect::execute(mwseInstruction* _this) {
    const char* hud = _this->vmPopString();
    if (!hud) { return false; }

    const char* fx = _this->vmPopString();
    if (!fx) { return false; }

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if (id != MGEhud::invalid_hud_id) {
        MGEhud::setEffect(id, fx);
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseFreeHUD)

// FreeHUD <string hud>
bool mwseFreeHUD::execute(mwseInstruction* _this) {
    const char* hud = _this->vmPopString();
    if (!hud) { return false; }

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if (id != MGEhud::invalid_hud_id) {
        MGEhud::free(id);
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseNIDLoadHUD)

// NIDLoadHUD <string texture>
bool mwseNIDLoadHUD::execute(mwseInstruction* _this) {
    const char* tex = _this->vmPopString();
    if (!tex) { return false; }

    currentHUD = MGEhud::load(currentHUDName.c_str(), tex);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseNIDPositionHUD)

// NIDPositionHUD <float x> <float y>
bool mwseNIDPositionHUD::execute(mwseInstruction* _this) {
    VMFLOAT x, y;

    if (!_this->vmPop(&x)) { return false; }
    if (!_this->vmPop(&y)) { return false; }

    if (currentHUD != MGEhud::invalid_hud_id) {
        MGEhud::setPosition(currentHUD, x, y);
    }
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseNIDScaleHUD)

// NIDScaleHUD <float xscale> <float yscale>
bool mwseNIDScaleHUD::execute(mwseInstruction* _this) {
    VMFLOAT xscale, yscale;

    if (!_this->vmPop(&xscale)) { return false; }
    if (!_this->vmPop(&yscale)) { return false; }

    if (currentHUD != MGEhud::invalid_hud_id) {
        MGEhud::setScale(currentHUD, xscale, yscale);
    }
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseNIDFullscreenHUD)

// NIDFullscreenHUD
bool mwseNIDFullscreenHUD::execute(mwseInstruction* _this) {
    if (currentHUD != MGEhud::invalid_hud_id) {
        MGEhud::setFullscreen(currentHUD);
    }
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseNIDEnableHUD)

// NIDEnableHUD
bool mwseNIDEnableHUD::execute(mwseInstruction* _this) {
    if (currentHUD != MGEhud::invalid_hud_id) {
        MGEhud::enable(currentHUD);
    }
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseNIDDisableHUD)

// NIDDisableHUD
bool mwseNIDDisableHUD::execute(mwseInstruction* _this) {
    if (currentHUD != MGEhud::invalid_hud_id) {
        MGEhud::disable(currentHUD);
    }
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseNIDChangeHUDTexture)

// NIDChangeHUDTexture <string texture>
bool mwseNIDChangeHUDTexture::execute(mwseInstruction* _this) {
    const char* tex = _this->vmPopString();
    if (!tex) { return false; }

    if (currentHUD != MGEhud::invalid_hud_id) {
        MGEhud::setTexture(currentHUD, tex);
    }
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseNIDChangeHUDEffect)

// NIDChangeHUDEffect <string effect>
bool mwseNIDChangeHUDEffect::execute(mwseInstruction* _this) {
    const char* fx = _this->vmPopString();
    if (!fx) { return false; }

    if (currentHUD != MGEhud::invalid_hud_id) {
        MGEhud::setEffect(currentHUD, fx);
    }
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseNIDFreeHUD)

// NIDFreeHUD
bool mwseNIDFreeHUD::execute(mwseInstruction* _this) {
    if (currentHUD != MGEhud::invalid_hud_id) {
        MGEhud::free(currentHUD);
        currentHUD = MGEhud::invalid_hud_id;
        // keep currentHUDName active for subsequent loads
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseNIDSetHUDEffectLong)

bool mwseNIDSetHUDEffectLong::execute(mwseInstruction* _this) {
    const char* varName;
    VMLONG x;

    varName = _this->vmPopString();
    if (!varName) { return false; }
    if (!_this->vmPop(&x)) { return false; }

    if (currentHUD != MGEhud::invalid_hud_id) {
        MGEhud::setEffectInt(currentHUD, varName, x);
    }
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseNIDSetHUDEffectFloat)

bool mwseNIDSetHUDEffectFloat::execute(mwseInstruction* _this) {
    const char* varName;
    VMFLOAT x;

    varName = _this->vmPopString();
    if (!varName) { return false; }
    if (!_this->vmPop(&x)) { return false; }

    if (currentHUD != MGEhud::invalid_hud_id) {
        MGEhud::setEffectFloat(currentHUD, varName, x);
    }
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseNIDSetHUDEffectVec)

bool mwseNIDSetHUDEffectVec::execute(mwseInstruction* _this) {
    const char* varName;
    VMFLOAT v[4];

    varName = _this->vmPopString();
    if (!varName) { return false; }
    if (!_this->vmPop(&v[0])) { return false; }
    if (!_this->vmPop(&v[1])) { return false; }
    if (!_this->vmPop(&v[2])) { return false; }
    if (!_this->vmPop(&v[3])) { return false; }

    if (currentHUD != MGEhud::invalid_hud_id) {
        MGEhud::setEffectVec4(currentHUD, varName, v);
    }
    return true;
}
