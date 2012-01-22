
#pragma once

#include "VMTYPES.h"

#define MWSEINSTRUCTION_DECLARE_VTABLE(classname) \
mwseInstruction::vtable_t classname::vtable = { &classname::destructor, &classname::getOperands, &classname::execute };

struct TES3MACHINE;

struct mwseInstruction
{
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
        void (__fastcall *d)(mwseInstruction*);
        int (__stdcall *g)(/* ignore this pointer */ OPCODE, VPVOID);
        bool (__fastcall *e)(mwseInstruction*);
    } vtable_t;

    mwseInstruction(TES3MACHINE& mach) : vm(mach) {}

	static __fastcall void destructor(mwseInstruction *_this) {}
	static __stdcall int getOperands(OPCODE opcode, VPVOID operanddata) { return 0; }
	static __fastcall bool execute(mwseInstruction *_this) { return false; }

    inline bool vmPush(VMREGTYPE val);
    inline bool vmPush(VMFLOAT val);
    inline bool vmPop(void *val);
    inline const char * vmGetString(void *str);
    const char * vmPopString();

	vtable_t *vptr;
	TES3MACHINE& vm;
};

inline bool mwseInstruction::vmPush(VMREGTYPE val)
{
    // Call <vtbl + 0x34> bool TES3MACHINE::push(VMREGTYPE)
    // uses properties of fastcall to put vm in ecx
    typedef bool (__fastcall *vmpush_t)(TES3MACHINE*, int, VMREGTYPE);
    vmpush_t f = *reinterpret_cast<vmpush_t*>(*(BYTE**)(&vm) + 0x34);

    return f(&vm, 0, val);
}

inline bool mwseInstruction::vmPush(VMFLOAT val)
{
    // Call <vtbl + 0x38> bool TES3MACHINE::push(VMFLOAT)
    // uses properties of fastcall to put vm in ecx
    typedef bool (__fastcall *vmpush_t)(TES3MACHINE*, int, VMFLOAT);
    vmpush_t f = *reinterpret_cast<vmpush_t*>(*(BYTE**)(&vm) + 0x38);

    return f(&vm, 0, val);
}

inline bool mwseInstruction::vmPop(void *val)
{
    // Call <vtbl + 0x3c> bool TES3MACHINE::pop(VMREGTYPE&)
    // uses properties of fastcall to put vm in ecx
    typedef bool (__fastcall *vmpop_t)(TES3MACHINE*, int, void *);
    vmpop_t f = *reinterpret_cast<vmpop_t*>(*(BYTE**)(&vm) + 0x3c);

    return f(&vm, 0, val);
}

inline const char * mwseInstruction::vmGetString(void *str)
{
    // Call <vtbl + 0x6c> const char * TES3MACHINE::GetString(VPVOID)
    // uses properties of fastcall to put vm in ecx
    typedef const char * (__fastcall *vmgetstring_t)(TES3MACHINE*, int, void *);
    vmgetstring_t f = *reinterpret_cast<vmgetstring_t*>(*(BYTE**)(&vm) + 0x6c);

    return f(&vm, 0, str);
}
