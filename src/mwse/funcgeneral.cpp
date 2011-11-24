
#include <string>
#include "funcgeneral.h"
#include "funchud.h"
#include "support/log.h"
#include "mge/mgeversion.h"
#include "mge/userhud.h"


mwseInstruction::vtable_t mwseWipeAll::vtable = { &mwseWipeAll::destructor, &mwseWipeAll::getOperands, &mwseWipeAll::execute };

// WipeAll
bool mwseWipeAll::execute(mwseInstruction *_this)
{
    resetMWSEHud();
	return true;
}


mwseInstruction::vtable_t mwseOutputDebugString::vtable = { &mwseOutputDebugString::destructor, &mwseOutputDebugString::getOperands, &mwseOutputDebugString::execute };

// OutputDebugString
bool mwseOutputDebugString::execute(mwseInstruction *_this)
{
	const char *str = _this->vmPopString();
	if(!str) return false;

    LOG::logline("%s", str);
    return true;
}


mwseInstruction::vtable_t mwseOutputVersionString::vtable = { &mwseOutputVersionString::destructor, &mwseOutputVersionString::getOperands, &mwseOutputVersionString::execute };

// OutputVersionString
bool mwseOutputVersionString::execute(mwseInstruction *_this)
{
    LOG::logline("%s", XE_VERSION_STRING);
    return true;
}


mwseInstruction::vtable_t mwseGetVersion::vtable = { &mwseGetVersion::destructor, &mwseGetVersion::getOperands, &mwseGetVersion::execute };

// GetVersion -> returns <long version>
bool mwseGetVersion::execute(mwseInstruction *_this)
{
	VMREGTYPE ret = MGE_MWSE_VERSION;
	return _this->vmPush(ret);
}


mwseInstruction::vtable_t mwseGetScreenWidth::vtable = { &mwseGetScreenWidth::destructor, &mwseGetScreenWidth::getOperands, &mwseGetScreenWidth::execute };

// GetScreenWidth -> returns <short width>
bool mwseGetScreenWidth::execute(mwseInstruction *_this)
{
	VMREGTYPE ret = MGEhud::getScreenWidth();
	return _this->vmPush(ret);
}


mwseInstruction::vtable_t mwseGetScreenHeight::vtable = { &mwseGetScreenHeight::destructor, &mwseGetScreenHeight::getOperands, &mwseGetScreenHeight::execute };

// GetScreenHeight -> returns <short height>
bool mwseGetScreenHeight::execute(mwseInstruction *_this)
{
	VMREGTYPE ret = MGEhud::getScreenHeight();
	return _this->vmPush(ret);
}
