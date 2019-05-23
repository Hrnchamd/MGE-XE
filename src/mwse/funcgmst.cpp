
#include "mge/mwbridge.h"
#include "funcgmst.h"



MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetGS)

// GetGS <long gmst_id> -> returns <long/float value>
bool mwseGetGS::execute(mwseInstruction* _this) {
    VMLONG Arg1;
    VMREGTYPE ret;

    if (!_this->vmPop(&Arg1)) { return false; }

    ret = *(VMREGTYPE*)MWBridge::get()->getGMSTPointer(Arg1);

    return _this->vmPush(ret);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetGS)

// SetGS <long gmst_id> <long/float value>
bool mwseSetGS::execute(mwseInstruction* _this) {
    VMLONG Arg1;
    VMLONG Arg2;

    if (!_this->vmPop(&Arg1)) { return false; }
    if (!_this->vmPop(&Arg2)) { return false; }

    void* gmst = MWBridge::get()->getGMSTPointer(Arg1);
    *(VMLONG*)gmst = Arg2;

    return true;
}
