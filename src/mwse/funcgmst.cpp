
#include "mge/mwbridge.h"
#include "funcgmst.h"


mwseInstruction::vtable_t mwseGetGS::vtable = { &mwseGetGS::destructor, &mwseGetGS::getOperands, &mwseGetGS::execute };

// GetGS <long gmst_id> -> returns <long/float value>
bool mwseGetGS::execute(mwseInstruction *_this)
{
	VMLONG Arg1;
	VMREGTYPE ret;

	if(!_this->vmPop(&Arg1)) return false;

    DECLARE_MWBRIDGE
    ret = *(VMREGTYPE *)mwBridge->getGMSTPointer(Arg1);

	return _this->vmPush(ret);
}


mwseInstruction::vtable_t mwseSetGS::vtable = { &mwseSetGS::destructor, &mwseSetGS::getOperands, &mwseSetGS::execute };

// SetGS <long gmst_id> <long/float value>
bool mwseSetGS::execute(mwseInstruction *_this)
{
	VMLONG Arg1;
	VMLONG Arg2;

	if(!_this->vmPop(&Arg1)) return false;
	if(!_this->vmPop(&Arg2)) return false;

    DECLARE_MWBRIDGE
    void *gmst = mwBridge->getGMSTPointer(Arg1);
    *(VMLONG *)gmst = Arg2;

	return true;
}
