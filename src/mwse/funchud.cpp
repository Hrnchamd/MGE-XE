
#include <string>
#include "funchud.h"
#include "mge/userhud.h"


std::string currentHUDName;
MGEhud::hud_id currentHUD;



void resetMWSEHud()
{
    MGEhud::reset();
    currentHUD = MGEhud::invalid_hud_id;
}


mwseInstruction::vtable_t mwseWipeHUDElements::vtable = { &mwseWipeHUDElements::destructor, &mwseWipeHUDElements::getOperands, &mwseWipeHUDElements::execute };

// WipeHUDElements
bool mwseWipeHUDElements::execute(mwseInstruction *_this)
{
    resetMWSEHud();
    return true;
}


mwseInstruction::vtable_t mwseWithHUD::vtable = { &mwseWithHUD::destructor, &mwseWithHUD::getOperands, &mwseWithHUD::execute };

// WithHUD <string hud>
bool mwseWithHUD::execute(mwseInstruction *_this)
{
    const char *hud = _this->vmPopString();
    if(!hud) return false;

    currentHUDName = hud;
    currentHUD = MGEhud::resolveName(hud);
    return true;
}


mwseInstruction::vtable_t mwseCancelWithHUD::vtable = { &mwseCancelWithHUD::destructor, &mwseCancelWithHUD::getOperands, &mwseCancelWithHUD::execute };

// CancelWithHUD
bool mwseCancelWithHUD::execute(mwseInstruction *_this)
{
    currentHUDName.clear();
    currentHUD = MGEhud::invalid_hud_id;
     return true;
}


mwseInstruction::vtable_t mwseLoadHUD::vtable = { &mwseLoadHUD::destructor, &mwseLoadHUD::getOperands, &mwseLoadHUD::execute };

// LoadHUD <string hud> <string texture>
bool mwseLoadHUD::execute(mwseInstruction *_this)
{
    const char *hud = _this->vmPopString();
    if(!hud) return false;

    const char *tex = _this->vmPopString();
    if(!tex) return false;

    MGEhud::load(hud, tex);

    return true;
}


mwseInstruction::vtable_t mwsePositionHUD::vtable = { &mwsePositionHUD::destructor, &mwsePositionHUD::getOperands, &mwsePositionHUD::execute };

// PositionHUD <string hud> <float x> <float y>
bool mwsePositionHUD::execute(mwseInstruction *_this)
{
    VMFLOAT x, y;

    const char *hud = _this->vmPopString();
    if(!hud) return false;

    if(!_this->vmPop(&x)) return false;
    if(!_this->vmPop(&y)) return false;

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if(id != MGEhud::invalid_hud_id)
        MGEhud::setPosition(id, x, y);

    return true;
}


mwseInstruction::vtable_t mwseScaleHUD::vtable = { &mwseScaleHUD::destructor, &mwseScaleHUD::getOperands, &mwseScaleHUD::execute };

// ScaleHUD <string hud> <float xscale> <float yscale>
bool mwseScaleHUD::execute(mwseInstruction *_this)
{
    VMFLOAT xscale, yscale;

    const char *hud = _this->vmPopString();
    if(!hud) return false;

    if(!_this->vmPop(&xscale)) return false;
    if(!_this->vmPop(&yscale)) return false;

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if(id != MGEhud::invalid_hud_id)
        MGEhud::setScale(id, xscale, yscale);

    return true;
}


mwseInstruction::vtable_t mwseFullscreenHUD::vtable = { &mwseFullscreenHUD::destructor, &mwseFullscreenHUD::getOperands, &mwseFullscreenHUD::execute };

// FullscreenHUD <string hud>
bool mwseFullscreenHUD::execute(mwseInstruction *_this)
{
    const char *hud = _this->vmPopString();
    if(!hud) return false;

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if(id != MGEhud::invalid_hud_id)
        MGEhud::setFullscreen(id);

    return true;
}


mwseInstruction::vtable_t mwseEnableHUD::vtable = { &mwseEnableHUD::destructor, &mwseEnableHUD::getOperands, &mwseEnableHUD::execute };

// EnableHUD <string hud>
bool mwseEnableHUD::execute(mwseInstruction *_this)
{
    const char *hud = _this->vmPopString();
    if(!hud) return false;

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if(id != MGEhud::invalid_hud_id)
        MGEhud::enable(id);

    return true;
}


mwseInstruction::vtable_t mwseDisableHUD::vtable = { &mwseDisableHUD::destructor, &mwseDisableHUD::getOperands, &mwseDisableHUD::execute };

// DisableHUD <string hud>
bool mwseDisableHUD::execute(mwseInstruction *_this)
{
    const char *hud = _this->vmPopString();
    if(!hud) return false;

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if(id != MGEhud::invalid_hud_id)
        MGEhud::disable(id);

    return true;
}


mwseInstruction::vtable_t mwseChangeHUDTexture::vtable = { &mwseChangeHUDTexture::destructor, &mwseChangeHUDTexture::getOperands, &mwseChangeHUDTexture::execute };

// ChangeHUDTexture <string hud> <string texture>
bool mwseChangeHUDTexture::execute(mwseInstruction *_this)
{
    const char *hud = _this->vmPopString();
    if(!hud) return false;

    const char *tex = _this->vmPopString();
    if(!tex) return false;

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if(id != MGEhud::invalid_hud_id)
        MGEhud::setTexture(id, tex);

    return true;
}


mwseInstruction::vtable_t mwseChangeHUDEffect::vtable = { &mwseChangeHUDEffect::destructor, &mwseChangeHUDEffect::getOperands, &mwseChangeHUDEffect::execute };

// ChangeHUDEffect <string hud> <string effect>
bool mwseChangeHUDEffect::execute(mwseInstruction *_this)
{
    const char *hud = _this->vmPopString();
    if(!hud) return false;

    const char *fx = _this->vmPopString();
    if(!fx) return false;

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if(id != MGEhud::invalid_hud_id)
        MGEhud::setEffect(id, fx);

    return true;
}


mwseInstruction::vtable_t mwseFreeHUD::vtable = { &mwseFreeHUD::destructor, &mwseFreeHUD::getOperands, &mwseFreeHUD::execute };

// FreeHUD <string hud>
bool mwseFreeHUD::execute(mwseInstruction *_this)
{
    const char *hud = _this->vmPopString();
    if(!hud) return false;

    MGEhud::hud_id id = MGEhud::resolveName(hud);
    if(id != MGEhud::invalid_hud_id)
        MGEhud::free(id);

    return true;
}


mwseInstruction::vtable_t mwseNIDLoadHUD::vtable = { &mwseNIDLoadHUD::destructor, &mwseNIDLoadHUD::getOperands, &mwseNIDLoadHUD::execute };

// NIDLoadHUD <string texture>
bool mwseNIDLoadHUD::execute(mwseInstruction *_this)
{
    const char *tex = _this->vmPopString();
    if(!tex) return false;

    currentHUD = MGEhud::load(currentHUDName.c_str(), tex);
    return true;
}


mwseInstruction::vtable_t mwseNIDPositionHUD::vtable = { &mwseNIDPositionHUD::destructor, &mwseNIDPositionHUD::getOperands, &mwseNIDPositionHUD::execute };

// NIDPositionHUD <float x> <float y>
bool mwseNIDPositionHUD::execute(mwseInstruction *_this)
{
    VMFLOAT x, y;

    if(!_this->vmPop(&x)) return false;
    if(!_this->vmPop(&y)) return false;

    if(currentHUD != MGEhud::invalid_hud_id)
        MGEhud::setPosition(currentHUD, x, y);
    return true;
}


mwseInstruction::vtable_t mwseNIDScaleHUD::vtable = { &mwseNIDScaleHUD::destructor, &mwseNIDScaleHUD::getOperands, &mwseNIDScaleHUD::execute };

// NIDScaleHUD <float xscale> <float yscale>
bool mwseNIDScaleHUD::execute(mwseInstruction *_this)
{
    VMFLOAT xscale, yscale;

    if(!_this->vmPop(&xscale)) return false;
    if(!_this->vmPop(&yscale)) return false;

    if(currentHUD != MGEhud::invalid_hud_id)
        MGEhud::setScale(currentHUD, xscale, yscale);
    return true;
}


mwseInstruction::vtable_t mwseNIDFullscreenHUD::vtable = { &mwseNIDFullscreenHUD::destructor, &mwseNIDFullscreenHUD::getOperands, &mwseNIDFullscreenHUD::execute };

// NIDFullscreenHUD
bool mwseNIDFullscreenHUD::execute(mwseInstruction *_this)
{
    if(currentHUD != MGEhud::invalid_hud_id)
        MGEhud::setFullscreen(currentHUD);
    return true;
}


mwseInstruction::vtable_t mwseNIDEnableHUD::vtable = { &mwseNIDEnableHUD::destructor, &mwseNIDEnableHUD::getOperands, &mwseNIDEnableHUD::execute };

// NIDEnableHUD
bool mwseNIDEnableHUD::execute(mwseInstruction *_this)
{
    if(currentHUD != MGEhud::invalid_hud_id)
        MGEhud::enable(currentHUD);
    return true;
}


mwseInstruction::vtable_t mwseNIDDisableHUD::vtable = { &mwseNIDDisableHUD::destructor, &mwseNIDDisableHUD::getOperands, &mwseNIDDisableHUD::execute };

// NIDDisableHUD
bool mwseNIDDisableHUD::execute(mwseInstruction *_this)
{
    if(currentHUD != MGEhud::invalid_hud_id)
        MGEhud::disable(currentHUD);
    return true;
}


mwseInstruction::vtable_t mwseNIDChangeHUDTexture::vtable = { &mwseNIDChangeHUDTexture::destructor, &mwseNIDChangeHUDTexture::getOperands, &mwseNIDChangeHUDTexture::execute };

// NIDChangeHUDTexture <string texture>
bool mwseNIDChangeHUDTexture::execute(mwseInstruction *_this)
{
    const char *tex = _this->vmPopString();
    if(!tex) return false;

    if(currentHUD != MGEhud::invalid_hud_id)
        MGEhud::setTexture(currentHUD, tex);
    return true;
}


mwseInstruction::vtable_t mwseNIDChangeHUDEffect::vtable = { &mwseNIDChangeHUDEffect::destructor, &mwseNIDChangeHUDEffect::getOperands, &mwseNIDChangeHUDEffect::execute };

// NIDChangeHUDEffect <string effect>
bool mwseNIDChangeHUDEffect::execute(mwseInstruction *_this)
{
    const char *fx = _this->vmPopString();
    if(!fx) return false;

    if(currentHUD != MGEhud::invalid_hud_id)
        MGEhud::setEffect(currentHUD, fx);
    return true;
}


mwseInstruction::vtable_t mwseNIDFreeHUD::vtable = { &mwseNIDFreeHUD::destructor, &mwseNIDFreeHUD::getOperands, &mwseNIDFreeHUD::execute };

// NIDFreeHUD
bool mwseNIDFreeHUD::execute(mwseInstruction *_this)
{
    if(currentHUD != MGEhud::invalid_hud_id)
    {
        MGEhud::free(currentHUD);
        currentHUD = MGEhud::invalid_hud_id;
        // keep currentHUDName active for subsequent loads
    }

    return true;
}
