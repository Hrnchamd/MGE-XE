#pragma once

#include <wtypes.h>



typedef BYTE* VPVOID;       // so I can do arithmetic
typedef DWORD VMSIZE;       // to hold max address
typedef WORD OPCODE;        // any consistent size
typedef long VMREGTYPE;     // as large as the largest type
typedef short VMINTERRUPT;  // how many interrupts do you need?
typedef float VMFLOAT;      // make sure this is the same size as STDSTACKTYPE, 32 bits
typedef char VMBYTE;        // any consistent size, pref 8 bits
typedef short VMSHORT;      // any consistent size
typedef long VMLONG;        // any consistent size > VMSHORT
typedef DWORD VMFLAGSTYPE;  // how many flags do you need?

enum MWRecordTag {
    MWTag_Activator = 0x49544341,
    MWTag_Apparatus = 0x41505041,
    MWTag_Armor = 0x4f4d5241,
    MWTag_BodyPart = 0x59444f42,
    MWTag_Book = 0x4b4f4f42,
    MWTag_Clothing = 0x544f4c43,
    MWTag_Container = 0x544e4f43,
    MWTag_Door = 0x524f4f44,
    MWTag_Ingredient = 0x52474e49,
    MWTag_Light = 0x4847494c,
    MWTag_Lockpick = 0x4b434f4c,
    MWTag_MiscItem = 0x4353494d,
    MWTag_Probe = 0x424f5250,
    MWTag_RepairItem = 0x41504552,
    MWTag_Static = 0x54415453,
    MWTag_Weapon = 0x50414557,
    MWTag_NPC = 0x5f43504e,
    MWTag_Creature = 0x41455243,
    MWTag_LevelledCreature = 0x4356454c,
    MWTag_Spell = 0x4c455053,
    MWTag_Enchantment = 0x48434e45,
    MWTag_Potion = 0x48434c41,
    MWTag_LevelledItem = 0x4956454c,
    MWTag_Ammo = 0x4f4d4d41
};

struct MWRecord {
    const void** vtbl;
    union {
        char tag[4];
        unsigned int tagCode;
    };
    unsigned int flags;
    void* sourceMod;
};

struct MWReference : MWRecord {
    void* visual;
    void* cellList;
    MWReference* lastCloneRefr;
    MWReference* nextListRefr;
    MWReference* prevListRefr;
    void* unknown;
    MWRecord* baseEntity;
    float orientation[3];
    float position[3];
    void* extraData;
    unsigned int sourceID, targetID;
};
