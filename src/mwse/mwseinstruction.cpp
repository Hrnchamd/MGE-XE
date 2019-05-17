
#include "mwseinstruction.h"

// vmPopString() - Pops a string pointer from the top of the stack
//                 and returns a null-terminated copy of the string
const char* mwseInstruction::vmPopString() {
    VMREGTYPE Arg;
    if (!vmPop(&Arg)) { return nullptr; }
    return vmGetString((void*)Arg);
}
