#pragma once

#include "VMTYPES.h"

#define MWSEINSTRUCTION_DECLARE_VTABLE(classname) \
mwseInstruction::vtable_t classname::vtable = { &classname::deleting_destructor, &classname::getOperands, &classname::execute };

struct TES3MACHINE;

struct mwseInstruction {
    typedef struct {
        /*
        equivalent to MSVC definition:
        class MWSEInstruction
        {
            virtual thiscall ~INSTRUCTION(void);
            virtual thiscall int GetOperands(OPCODE opcode, VPVOID operanddata);
            virtual thiscall bool execute(void);
        }
        */
        void (__thiscall* d)(mwseInstruction*, int);
        int (__stdcall* g)(/* ignore this pointer */ OPCODE, VPVOID);
        bool (__thiscall* e)(mwseInstruction*);
    } vtable_t;

    mwseInstruction(TES3MACHINE& mach) : vm(mach) {}

    static void __thiscall deleting_destructor(mwseInstruction* _this, int delete_flags) {}
    static int __stdcall getOperands(OPCODE opcode, VPVOID operanddata) {
        return 0;
    }
    static bool __thiscall execute(mwseInstruction* _this) {
        return false;
    }

    inline bool vmPush(VMREGTYPE val);
    inline bool vmPush(VMFLOAT val);
    inline bool vmPop(VMREGTYPE* val);
    inline bool vmPop(VMFLOAT* val);
    inline const char* vmGetString(void* str);
    const char* vmPopString();

    inline static MWReference* vmGetTargetRef();
    inline static void* vmGetTargetActor();

    vtable_t* vptr;
    TES3MACHINE& vm;
};

// vmPush(VMREGTYPE) - Pushes an integer (of any type) onto the stack
inline bool mwseInstruction::vmPush(VMREGTYPE val) {
    // Call <vtbl + 0x34> bool TES3MACHINE::push(VMREGTYPE)
    typedef bool (__thiscall *vmpush_t)(TES3MACHINE*, VMREGTYPE);
    const vmpush_t f = *reinterpret_cast<vmpush_t*>(*(BYTE**)(&vm) + 0x34);

    return f(&vm, val);
}

// vmPush(VMREGTYPE) - Pushes a float onto the stack
inline bool mwseInstruction::vmPush(VMFLOAT val) {
    // Call <vtbl + 0x38> bool TES3MACHINE::push(VMFLOAT)
    typedef bool (__thiscall *vmpush_t)(TES3MACHINE*, VMFLOAT);
    const vmpush_t f = *reinterpret_cast<vmpush_t*>(*(BYTE**)(&vm) + 0x38);

    return f(&vm, val);
}

// vmPop(VMREGTYPE*) - Pops an integer (of any type) off the stack
inline bool mwseInstruction::vmPop(VMREGTYPE* val) {
    // Call <vtbl + 0x3c> bool TES3MACHINE::pop(VMREGTYPE&)
    typedef bool (__thiscall *vmpop_t)(TES3MACHINE*, void*);
    vmpop_t f = *reinterpret_cast<vmpop_t*>(*(BYTE**)(&vm) + 0x3C);

    return f(&vm, val);
}

// vmPop(VMFLOAT*) - Pops a float off the stack
inline bool mwseInstruction::vmPop(VMFLOAT* val) {
    // Call <vtbl + 0x3c> bool TES3MACHINE::pop(VMREGTYPE&)
    typedef bool (__thiscall *vmpop_t)(TES3MACHINE*, void*);
    const vmpop_t f = *reinterpret_cast<vmpop_t*>(*(BYTE**)(&vm) + 0x3C);

    return f(&vm, val);
}

// vmGetString(void*) - Returns a null-terminated string copied from the stack, given a stack pointer
inline const char* mwseInstruction::vmGetString(void* str) {
    // Call <vtbl + 0x6c> const char * TES3MACHINE::GetString(VPVOID)
    typedef const char* (__thiscall *vmgetstring_t)(TES3MACHINE*, void*);
    const vmgetstring_t f = *reinterpret_cast<vmgetstring_t*>(*(BYTE**)(&vm) + 0x6C);

    return f(&vm, str);
}

// vmGetTargetRef - Returns the reference that the script is targetted to
inline MWReference* mwseInstruction::vmGetTargetRef() {
    return *reinterpret_cast<MWReference**>(0x7CEBEC);
}

// vmGetTargetActor - Returns the actor linked to the target reference
inline void* mwseInstruction::vmGetTargetActor() {
    MWReference* refr = vmGetTargetRef();
    if (refr) {
        typedef void* (__thiscall *resolveActor_t)(void*);
        const resolveActor_t resolveActor = reinterpret_cast<resolveActor_t>(0x4E5750);
        return resolveActor(refr);
    }
    return nullptr;
}
