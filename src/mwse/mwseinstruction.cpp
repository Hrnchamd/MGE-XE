
#include "mwseinstruction.h"

const char * mwseInstruction::vmPopString()
{
	VMREGTYPE Arg;
	if(!vmPop(&Arg)) return 0;
	return vmGetString((void *)Arg);
}
