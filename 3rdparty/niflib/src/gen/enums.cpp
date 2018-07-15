/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include <string>
#include <iostream>
#include "../../include/NIF_IO.h"
#include "../../include/gen/enums.h"
#include "../../include/gen/enums_intl.h"

using namespace std;

namespace Niflib {



//--ForceType--//

void NifStream( ForceType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = ForceType(temp);
}

void NifStream( ForceType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, ForceType const & val ) {
	switch ( val ) {
		case FORCE_PLANAR: return out << "FORCE_PLANAR";
		case FORCE_SPHERICAL: return out << "FORCE_SPHERICAL";
		case FORCE_UNKNOWN: return out << "FORCE_UNKNOWN";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--CollisionMode--//

void NifStream( CollisionMode & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = CollisionMode(temp);
}

void NifStream( CollisionMode const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, CollisionMode const & val ) {
	switch ( val ) {
		case CM_USE_OBB: return out << "CM_USE_OBB";
		case CM_USE_TRI: return out << "CM_USE_TRI";
		case CM_USE_ABV: return out << "CM_USE_ABV";
		case CM_NOTEST: return out << "CM_NOTEST";
		case CM_USE_NIBOUND: return out << "CM_USE_NIBOUND";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--DeactivatorType--//

void NifStream( DeactivatorType & val, istream& in, const NifInfo & info ) {
	byte temp;
	NifStream( temp, in, info );
	val = DeactivatorType(temp);
}

void NifStream( DeactivatorType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (byte)(val), out, info );
}

ostream & operator<<( ostream & out, DeactivatorType const & val ) {
	switch ( val ) {
		case DEACTIVATOR_INVALID: return out << "DEACTIVATOR_INVALID";
		case DEACTIVATOR_NEVER: return out << "DEACTIVATOR_NEVER";
		case DEACTIVATOR_SPATIAL: return out << "DEACTIVATOR_SPATIAL";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--hkResponseType--//

void NifStream( hkResponseType & val, istream& in, const NifInfo & info ) {
	byte temp;
	NifStream( temp, in, info );
	val = hkResponseType(temp);
}

void NifStream( hkResponseType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (byte)(val), out, info );
}

ostream & operator<<( ostream & out, hkResponseType const & val ) {
	switch ( val ) {
		case RESPONSE_INVALID: return out << "RESPONSE_INVALID";
		case RESPONSE_SIMPLE_CONTACT: return out << "RESPONSE_SIMPLE_CONTACT";
		case RESPONSE_REPORTING: return out << "RESPONSE_REPORTING";
		case RESPONSE_NONE: return out << "RESPONSE_NONE";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--TexTransform--//

void NifStream( TexTransform & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = TexTransform(temp);
}

void NifStream( TexTransform const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, TexTransform const & val ) {
	switch ( val ) {
		case TT_TRANSLATE_U: return out << "TT_TRANSLATE_U";
		case TT_TRANSLATE_V: return out << "TT_TRANSLATE_V";
		case TT_ROTATE: return out << "TT_ROTATE";
		case TT_SCALE_U: return out << "TT_SCALE_U";
		case TT_SCALE_V: return out << "TT_SCALE_V";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--HavokMaterial--//

void NifStream( HavokMaterial & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = HavokMaterial(temp);
}

void NifStream( HavokMaterial const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, HavokMaterial const & val ) {
	switch ( val ) {
		case HAV_MAT_STONE: return out << "HAV_MAT_STONE";
		case HAV_MAT_CLOTH: return out << "HAV_MAT_CLOTH";
		case HAV_MAT_DIRT: return out << "HAV_MAT_DIRT";
		case HAV_MAT_GLASS: return out << "HAV_MAT_GLASS";
		case HAV_MAT_GRASS: return out << "HAV_MAT_GRASS";
		case HAV_MAT_METAL: return out << "HAV_MAT_METAL";
		case HAV_MAT_ORGANIC: return out << "HAV_MAT_ORGANIC";
		case HAV_MAT_SKIN: return out << "HAV_MAT_SKIN";
		case HAV_MAT_WATER: return out << "HAV_MAT_WATER";
		case HAV_MAT_WOOD: return out << "HAV_MAT_WOOD";
		case HAV_MAT_HEAVY_STONE: return out << "HAV_MAT_HEAVY_STONE";
		case HAV_MAT_HEAVY_METAL: return out << "HAV_MAT_HEAVY_METAL";
		case HAV_MAT_HEAVY_WOOD: return out << "HAV_MAT_HEAVY_WOOD";
		case HAV_MAT_CHAIN: return out << "HAV_MAT_CHAIN";
		case HAV_MAT_SNOW: return out << "HAV_MAT_SNOW";
		case HAV_MAT_STONE_STAIRS: return out << "HAV_MAT_STONE_STAIRS";
		case HAV_MAT_CLOTH_STAIRS: return out << "HAV_MAT_CLOTH_STAIRS";
		case HAV_MAT_DIRT_STAIRS: return out << "HAV_MAT_DIRT_STAIRS";
		case HAV_MAT_GLASS_STAIRS: return out << "HAV_MAT_GLASS_STAIRS";
		case HAV_MAT_GRASS_STAIRS: return out << "HAV_MAT_GRASS_STAIRS";
		case HAV_MAT_METAL_STAIRS: return out << "HAV_MAT_METAL_STAIRS";
		case HAV_MAT_ORGANIC_STAIRS: return out << "HAV_MAT_ORGANIC_STAIRS";
		case HAV_MAT_SKIN_STAIRS: return out << "HAV_MAT_SKIN_STAIRS";
		case HAV_MAT_WATER_STAIRS: return out << "HAV_MAT_WATER_STAIRS";
		case HAV_MAT_WOOD_STAIRS: return out << "HAV_MAT_WOOD_STAIRS";
		case HAV_MAT_HEAVY_STONE_STAIRS: return out << "HAV_MAT_HEAVY_STONE_STAIRS";
		case HAV_MAT_HEAVY_METAL_STAIRS: return out << "HAV_MAT_HEAVY_METAL_STAIRS";
		case HAV_MAT_HEAVY_WOOD_STAIRS: return out << "HAV_MAT_HEAVY_WOOD_STAIRS";
		case HAV_MAT_CHAIN_STAIRS: return out << "HAV_MAT_CHAIN_STAIRS";
		case HAV_MAT_SNOW_STAIRS: return out << "HAV_MAT_SNOW_STAIRS";
		case HAV_MAT_ELEVATOR: return out << "HAV_MAT_ELEVATOR";
		case HAV_MAT_RUBBER: return out << "HAV_MAT_RUBBER";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--EndianType--//

void NifStream( EndianType & val, istream& in, const NifInfo & info ) {
	byte temp;
	NifStream( temp, in, info );
	val = EndianType(temp);
}

void NifStream( EndianType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (byte)(val), out, info );
}

ostream & operator<<( ostream & out, EndianType const & val ) {
	switch ( val ) {
		case ENDIAN_BIG: return out << "ENDIAN_BIG";
		case ENDIAN_LITTLE: return out << "ENDIAN_LITTLE";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--VelocityType--//

void NifStream( VelocityType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = VelocityType(temp);
}

void NifStream( VelocityType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, VelocityType const & val ) {
	switch ( val ) {
		case VELOCITY_USE_NORMALS: return out << "VELOCITY_USE_NORMALS";
		case VELOCITY_USE_RANDOM: return out << "VELOCITY_USE_RANDOM";
		case VELOCITY_USE_DIRECTION: return out << "VELOCITY_USE_DIRECTION";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--AnimationType--//

void NifStream( AnimationType & val, istream& in, const NifInfo & info ) {
	unsigned short temp;
	NifStream( temp, in, info );
	val = AnimationType(temp);
}

void NifStream( AnimationType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned short)(val), out, info );
}

ostream & operator<<( ostream & out, AnimationType const & val ) {
	switch ( val ) {
		case SIT: return out << "Sit";
		case SLEEP: return out << "Sleep";
		case LEAN: return out << "Lean";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--DataStreamUsage--//

void NifStream( DataStreamUsage & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = DataStreamUsage(temp);
}

void NifStream( DataStreamUsage const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, DataStreamUsage const & val ) {
	switch ( val ) {
		case USAGE_VERTEX_INDEX: return out << "USAGE_VERTEX_INDEX";
		case USAGE_VERTEX: return out << "USAGE_VERTEX";
		case USAGE_SHADER_CONSTANT: return out << "USAGE_SHADER_CONSTANT";
		case USAGE_USER: return out << "USAGE_USER";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--StencilCompareMode--//

void NifStream( StencilCompareMode & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = StencilCompareMode(temp);
}

void NifStream( StencilCompareMode const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, StencilCompareMode const & val ) {
	switch ( val ) {
		case TEST_NEVER: return out << "TEST_NEVER";
		case TEST_LESS: return out << "TEST_LESS";
		case TEST_EQUAL: return out << "TEST_EQUAL";
		case TEST_LESS_EQUAL: return out << "TEST_LESS_EQUAL";
		case TEST_GREATER: return out << "TEST_GREATER";
		case TEST_NOT_EQUAL: return out << "TEST_NOT_EQUAL";
		case TEST_GREATER_EQUAL: return out << "TEST_GREATER_EQUAL";
		case TEST_ALWAYS: return out << "TEST_ALWAYS";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--TexFilterMode--//

void NifStream( TexFilterMode & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = TexFilterMode(temp);
}

void NifStream( TexFilterMode const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, TexFilterMode const & val ) {
	switch ( val ) {
		case FILTER_NEAREST: return out << "FILTER_NEAREST";
		case FILTER_BILERP: return out << "FILTER_BILERP";
		case FILTER_TRILERP: return out << "FILTER_TRILERP";
		case FILTER_NEAREST_MIPNEAREST: return out << "FILTER_NEAREST_MIPNEAREST";
		case FILTER_NEAREST_MIPLERP: return out << "FILTER_NEAREST_MIPLERP";
		case FILTER_BILERP_MIPNEAREST: return out << "FILTER_BILERP_MIPNEAREST";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--SymmetryType--//

void NifStream( SymmetryType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = SymmetryType(temp);
}

void NifStream( SymmetryType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, SymmetryType const & val ) {
	switch ( val ) {
		case SPHERICAL_SYMMETRY: return out << "SPHERICAL_SYMMETRY";
		case CYLINDRICAL_SYMMETRY: return out << "CYLINDRICAL_SYMMETRY";
		case PLANAR_SYMMETRY: return out << "PLANAR_SYMMETRY";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--LightMode--//

void NifStream( LightMode & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = LightMode(temp);
}

void NifStream( LightMode const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, LightMode const & val ) {
	switch ( val ) {
		case LIGHT_MODE_EMISSIVE: return out << "LIGHT_MODE_EMISSIVE";
		case LIGHT_MODE_EMI_AMB_DIF: return out << "LIGHT_MODE_EMI_AMB_DIF";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--MipMapFormat--//

void NifStream( MipMapFormat & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = MipMapFormat(temp);
}

void NifStream( MipMapFormat const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, MipMapFormat const & val ) {
	switch ( val ) {
		case MIP_FMT_NO: return out << "MIP_FMT_NO";
		case MIP_FMT_YES: return out << "MIP_FMT_YES";
		case MIP_FMT_DEFAULT: return out << "MIP_FMT_DEFAULT";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--StencilAction--//

void NifStream( StencilAction & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = StencilAction(temp);
}

void NifStream( StencilAction const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, StencilAction const & val ) {
	switch ( val ) {
		case ACTION_KEEP: return out << "ACTION_KEEP";
		case ACTION_ZERO: return out << "ACTION_ZERO";
		case ACTION_REPLACE: return out << "ACTION_REPLACE";
		case ACTION_INCREMENT: return out << "ACTION_INCREMENT";
		case ACTION_DECREMENT: return out << "ACTION_DECREMENT";
		case ACTION_INVERT: return out << "ACTION_INVERT";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--SyncPoint--//

void NifStream( SyncPoint & val, istream& in, const NifInfo & info ) {
	unsigned short temp;
	NifStream( temp, in, info );
	val = SyncPoint(temp);
}

void NifStream( SyncPoint const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned short)(val), out, info );
}

ostream & operator<<( ostream & out, SyncPoint const & val ) {
	switch ( val ) {
		case SYNC_ANY: return out << "SYNC_ANY";
		case SYNC_UPDATE: return out << "SYNC_UPDATE";
		case SYNC_POST_UPDATE: return out << "SYNC_POST_UPDATE";
		case SYNC_VISIBLE: return out << "SYNC_VISIBLE";
		case SYNC_RENDER: return out << "SYNC_RENDER";
		case SYNC_PHYSICS_SIMULATE: return out << "SYNC_PHYSICS_SIMULATE";
		case SYNC_PHYSICS_COMPLETED: return out << "SYNC_PHYSICS_COMPLETED";
		case SYNC_REFLECTIONS: return out << "SYNC_REFLECTIONS";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--TexType--//

void NifStream( TexType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = TexType(temp);
}

void NifStream( TexType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, TexType const & val ) {
	switch ( val ) {
		case BASE_MAP: return out << "BASE_MAP";
		case DARK_MAP: return out << "DARK_MAP";
		case DETAIL_MAP: return out << "DETAIL_MAP";
		case GLOSS_MAP: return out << "GLOSS_MAP";
		case GLOW_MAP: return out << "GLOW_MAP";
		case BUMP_MAP: return out << "BUMP_MAP";
		case NORMAL_MAP: return out << "NORMAL_MAP";
		case UNKNOWN2_MAP: return out << "UNKNOWN2_MAP";
		case DECAL_0_MAP: return out << "DECAL_0_MAP";
		case DECAL_1_MAP: return out << "DECAL_1_MAP";
		case DECAL_2_MAP: return out << "DECAL_2_MAP";
		case DECAL_3_MAP: return out << "DECAL_3_MAP";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--BSDismemberBodyPartType--//

void NifStream( BSDismemberBodyPartType & val, istream& in, const NifInfo & info ) {
	unsigned short temp;
	NifStream( temp, in, info );
	val = BSDismemberBodyPartType(temp);
}

void NifStream( BSDismemberBodyPartType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned short)(val), out, info );
}

ostream & operator<<( ostream & out, BSDismemberBodyPartType const & val ) {
	switch ( val ) {
		case BP_TORSO: return out << "BP_TORSO";
		case BP_HEAD: return out << "BP_HEAD";
		case BP_HEAD2: return out << "BP_HEAD2";
		case BP_LEFTARM: return out << "BP_LEFTARM";
		case BP_LEFTARM2: return out << "BP_LEFTARM2";
		case BP_RIGHTARM: return out << "BP_RIGHTARM";
		case BP_RIGHTARM2: return out << "BP_RIGHTARM2";
		case BP_LEFTLEG: return out << "BP_LEFTLEG";
		case BP_LEFTLEG2: return out << "BP_LEFTLEG2";
		case BP_LEFTLEG3: return out << "BP_LEFTLEG3";
		case BP_RIGHTLEG: return out << "BP_RIGHTLEG";
		case BP_RIGHTLEG2: return out << "BP_RIGHTLEG2";
		case BP_RIGHTLEG3: return out << "BP_RIGHTLEG3";
		case BP_BRAIN: return out << "BP_BRAIN";
		case SBP_30_HEAD: return out << "SBP_30_HEAD";
		case SBP_31_HAIR: return out << "SBP_31_HAIR";
		case SBP_32_BODY: return out << "SBP_32_BODY";
		case SBP_33_HANDS: return out << "SBP_33_HANDS";
		case SBP_34_FOREARMS: return out << "SBP_34_FOREARMS";
		case SBP_35_AMULET: return out << "SBP_35_AMULET";
		case SBP_36_RING: return out << "SBP_36_RING";
		case SBP_37_FEET: return out << "SBP_37_FEET";
		case SBP_38_CALVES: return out << "SBP_38_CALVES";
		case SBP_39_SHIELD: return out << "SBP_39_SHIELD";
		case SBP_40_TAIL: return out << "SBP_40_TAIL";
		case SBP_41_LONGHAIR: return out << "SBP_41_LONGHAIR";
		case SBP_42_CIRCLET: return out << "SBP_42_CIRCLET";
		case SBP_43_EARS: return out << "SBP_43_EARS";
		case SBP_44_DRAGON_BLOODHEAD_OR_MOD_MOUTH: return out << "SBP_44_DRAGON_BLOODHEAD_OR_MOD_MOUTH";
		case SBP_45_DRAGON_BLOODWINGL_OR_MOD_NECK: return out << "SBP_45_DRAGON_BLOODWINGL_OR_MOD_NECK";
		case SBP_46_DRAGON_BLOODWINGR_OR_MOD_CHEST_PRIMARY: return out << "SBP_46_DRAGON_BLOODWINGR_OR_MOD_CHEST_PRIMARY";
		case SBP_47_DRAGON_BLOODTAIL_OR_MOD_BACK: return out << "SBP_47_DRAGON_BLOODTAIL_OR_MOD_BACK";
		case SBP_48_MOD_MISC1: return out << "SBP_48_MOD_MISC1";
		case SBP_49_MOD_PELVIS_PRIMARY: return out << "SBP_49_MOD_PELVIS_PRIMARY";
		case SBP_50_DECAPITATEDHEAD: return out << "SBP_50_DECAPITATEDHEAD";
		case SBP_51_DECAPITATE: return out << "SBP_51_DECAPITATE";
		case SBP_52_MOD_PELVIS_SECONDARY: return out << "SBP_52_MOD_PELVIS_SECONDARY";
		case SBP_53_MOD_LEG_RIGHT: return out << "SBP_53_MOD_LEG_RIGHT";
		case SBP_54_MOD_LEG_LEFT: return out << "SBP_54_MOD_LEG_LEFT";
		case SBP_55_MOD_FACE_JEWELRY: return out << "SBP_55_MOD_FACE_JEWELRY";
		case SBP_56_MOD_CHEST_SECONDARY: return out << "SBP_56_MOD_CHEST_SECONDARY";
		case SBP_57_MOD_SHOULDER: return out << "SBP_57_MOD_SHOULDER";
		case SBP_58_MOD_ARM_LEFT: return out << "SBP_58_MOD_ARM_LEFT";
		case SBP_59_MOD_ARM_RIGHT: return out << "SBP_59_MOD_ARM_RIGHT";
		case SBP_60_MOD_MISC2: return out << "SBP_60_MOD_MISC2";
		case SBP_61_FX01: return out << "SBP_61_FX01";
		case BP_SECTIONCAP_HEAD: return out << "BP_SECTIONCAP_HEAD";
		case BP_SECTIONCAP_HEAD2: return out << "BP_SECTIONCAP_HEAD2";
		case BP_SECTIONCAP_LEFTARM: return out << "BP_SECTIONCAP_LEFTARM";
		case BP_SECTIONCAP_LEFTARM2: return out << "BP_SECTIONCAP_LEFTARM2";
		case BP_SECTIONCAP_RIGHTARM: return out << "BP_SECTIONCAP_RIGHTARM";
		case BP_SECTIONCAP_RIGHTARM2: return out << "BP_SECTIONCAP_RIGHTARM2";
		case BP_SECTIONCAP_LEFTLEG: return out << "BP_SECTIONCAP_LEFTLEG";
		case BP_SECTIONCAP_LEFTLEG2: return out << "BP_SECTIONCAP_LEFTLEG2";
		case BP_SECTIONCAP_LEFTLEG3: return out << "BP_SECTIONCAP_LEFTLEG3";
		case BP_SECTIONCAP_RIGHTLEG: return out << "BP_SECTIONCAP_RIGHTLEG";
		case BP_SECTIONCAP_RIGHTLEG2: return out << "BP_SECTIONCAP_RIGHTLEG2";
		case BP_SECTIONCAP_RIGHTLEG3: return out << "BP_SECTIONCAP_RIGHTLEG3";
		case BP_SECTIONCAP_BRAIN: return out << "BP_SECTIONCAP_BRAIN";
		case SBP_130_HEAD: return out << "SBP_130_HEAD";
		case SBP_131_HAIR: return out << "SBP_131_HAIR";
		case SBP_141_LONGHAIR: return out << "SBP_141_LONGHAIR";
		case SBP_142_CIRCLET: return out << "SBP_142_CIRCLET";
		case SBP_143_EARS: return out << "SBP_143_EARS";
		case SBP_150_DECAPITATEDHEAD: return out << "SBP_150_DECAPITATEDHEAD";
		case BP_TORSOCAP_HEAD: return out << "BP_TORSOCAP_HEAD";
		case BP_TORSOCAP_HEAD2: return out << "BP_TORSOCAP_HEAD2";
		case BP_TORSOCAP_LEFTARM: return out << "BP_TORSOCAP_LEFTARM";
		case BP_TORSOCAP_LEFTARM2: return out << "BP_TORSOCAP_LEFTARM2";
		case BP_TORSOCAP_RIGHTARM: return out << "BP_TORSOCAP_RIGHTARM";
		case BP_TORSOCAP_RIGHTARM2: return out << "BP_TORSOCAP_RIGHTARM2";
		case BP_TORSOCAP_LEFTLEG: return out << "BP_TORSOCAP_LEFTLEG";
		case BP_TORSOCAP_LEFTLEG2: return out << "BP_TORSOCAP_LEFTLEG2";
		case BP_TORSOCAP_LEFTLEG3: return out << "BP_TORSOCAP_LEFTLEG3";
		case BP_TORSOCAP_RIGHTLEG: return out << "BP_TORSOCAP_RIGHTLEG";
		case BP_TORSOCAP_RIGHTLEG2: return out << "BP_TORSOCAP_RIGHTLEG2";
		case BP_TORSOCAP_RIGHTLEG3: return out << "BP_TORSOCAP_RIGHTLEG3";
		case BP_TORSOCAP_BRAIN: return out << "BP_TORSOCAP_BRAIN";
		case SBP_230_HEAD: return out << "SBP_230_HEAD";
		case BP_TORSOSECTION_HEAD: return out << "BP_TORSOSECTION_HEAD";
		case BP_TORSOSECTION_HEAD2: return out << "BP_TORSOSECTION_HEAD2";
		case BP_TORSOSECTION_LEFTARM: return out << "BP_TORSOSECTION_LEFTARM";
		case BP_TORSOSECTION_LEFTARM2: return out << "BP_TORSOSECTION_LEFTARM2";
		case BP_TORSOSECTION_RIGHTARM: return out << "BP_TORSOSECTION_RIGHTARM";
		case BP_TORSOSECTION_RIGHTARM2: return out << "BP_TORSOSECTION_RIGHTARM2";
		case BP_TORSOSECTION_LEFTLEG: return out << "BP_TORSOSECTION_LEFTLEG";
		case BP_TORSOSECTION_LEFTLEG2: return out << "BP_TORSOSECTION_LEFTLEG2";
		case BP_TORSOSECTION_LEFTLEG3: return out << "BP_TORSOSECTION_LEFTLEG3";
		case BP_TORSOSECTION_RIGHTLEG: return out << "BP_TORSOSECTION_RIGHTLEG";
		case BP_TORSOSECTION_RIGHTLEG2: return out << "BP_TORSOSECTION_RIGHTLEG2";
		case BP_TORSOSECTION_RIGHTLEG3: return out << "BP_TORSOSECTION_RIGHTLEG3";
		case BP_TORSOSECTION_BRAIN: return out << "BP_TORSOSECTION_BRAIN";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--ChannelType--//

void NifStream( ChannelType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = ChannelType(temp);
}

void NifStream( ChannelType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, ChannelType const & val ) {
	switch ( val ) {
		case CHNL_RED: return out << "CHNL_RED";
		case CHNL_GREEN: return out << "CHNL_GREEN";
		case CHNL_BLUE: return out << "CHNL_BLUE";
		case CHNL_ALPHA: return out << "CHNL_ALPHA";
		case CHNL_COMPRESSED: return out << "CHNL_COMPRESSED";
		case CHNL_INDEX: return out << "CHNL_INDEX";
		case CHNL_EMPTY: return out << "CHNL_EMPTY";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--SkyObjectType--//

void NifStream( SkyObjectType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = SkyObjectType(temp);
}

void NifStream( SkyObjectType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, SkyObjectType const & val ) {
	switch ( val ) {
		case BSSM_SKY_TEXTURE: return out << "BSSM_SKY_TEXTURE";
		case BSSM_SKY_SUNGLARE: return out << "BSSM_SKY_SUNGLARE";
		case BSSM_SKY: return out << "BSSM_SKY";
		case BSSM_SKY_CLOUDS: return out << "BSSM_SKY_CLOUDS";
		case BSSM_SKY_STARS: return out << "BSSM_SKY_STARS";
		case BSSM_SKY_MOON_STARS_MASK: return out << "BSSM_SKY_MOON_STARS_MASK";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--OblivionLayer--//

void NifStream( OblivionLayer & val, istream& in, const NifInfo & info ) {
	byte temp;
	NifStream( temp, in, info );
	val = OblivionLayer(temp);
}

void NifStream( OblivionLayer const & val, ostream& out, const NifInfo & info ) {
	NifStream( (byte)(val), out, info );
}

ostream & operator<<( ostream & out, OblivionLayer const & val ) {
	switch ( val ) {
		case OL_UNIDENTIFIED: return out << "OL_UNIDENTIFIED";
		case OL_STATIC: return out << "OL_STATIC";
		case OL_ANIM_STATIC: return out << "OL_ANIM_STATIC";
		case OL_TRANSPARENT: return out << "OL_TRANSPARENT";
		case OL_CLUTTER: return out << "OL_CLUTTER";
		case OL_WEAPON: return out << "OL_WEAPON";
		case OL_PROJECTILE: return out << "OL_PROJECTILE";
		case OL_SPELL: return out << "OL_SPELL";
		case OL_BIPED: return out << "OL_BIPED";
		case OL_TREES: return out << "OL_TREES";
		case OL_PROPS: return out << "OL_PROPS";
		case OL_WATER: return out << "OL_WATER";
		case OL_TRIGGER: return out << "OL_TRIGGER";
		case OL_TERRAIN: return out << "OL_TERRAIN";
		case OL_TRAP: return out << "OL_TRAP";
		case OL_NONCOLLIDABLE: return out << "OL_NONCOLLIDABLE";
		case OL_CLOUD_TRAP: return out << "OL_CLOUD_TRAP";
		case OL_GROUND: return out << "OL_GROUND";
		case OL_PORTAL: return out << "OL_PORTAL";
		case OL_STAIRS: return out << "OL_STAIRS";
		case OL_CHAR_CONTROLLER: return out << "OL_CHAR_CONTROLLER";
		case OL_AVOID_BOX: return out << "OL_AVOID_BOX";
		case OL_UNKNOWN1: return out << "OL_UNKNOWN1";
		case OL_UNKNOWN2: return out << "OL_UNKNOWN2";
		case OL_CAMERA_PICK: return out << "OL_CAMERA_PICK";
		case OL_ITEM_PICK: return out << "OL_ITEM_PICK";
		case OL_LINE_OF_SIGHT: return out << "OL_LINE_OF_SIGHT";
		case OL_PATH_PICK: return out << "OL_PATH_PICK";
		case OL_CUSTOM_PICK_1: return out << "OL_CUSTOM_PICK_1";
		case OL_CUSTOM_PICK_2: return out << "OL_CUSTOM_PICK_2";
		case OL_SPELL_EXPLOSION: return out << "OL_SPELL_EXPLOSION";
		case OL_DROPPING_PICK: return out << "OL_DROPPING_PICK";
		case OL_OTHER: return out << "OL_OTHER";
		case OL_HEAD: return out << "OL_HEAD";
		case OL_BODY: return out << "OL_BODY";
		case OL_SPINE1: return out << "OL_SPINE1";
		case OL_SPINE2: return out << "OL_SPINE2";
		case OL_L_UPPER_ARM: return out << "OL_L_UPPER_ARM";
		case OL_L_FOREARM: return out << "OL_L_FOREARM";
		case OL_L_HAND: return out << "OL_L_HAND";
		case OL_L_THIGH: return out << "OL_L_THIGH";
		case OL_L_CALF: return out << "OL_L_CALF";
		case OL_L_FOOT: return out << "OL_L_FOOT";
		case OL_R_UPPER_ARM: return out << "OL_R_UPPER_ARM";
		case OL_R_FOREARM: return out << "OL_R_FOREARM";
		case OL_R_HAND: return out << "OL_R_HAND";
		case OL_R_THIGH: return out << "OL_R_THIGH";
		case OL_R_CALF: return out << "OL_R_CALF";
		case OL_R_FOOT: return out << "OL_R_FOOT";
		case OL_TAIL: return out << "OL_TAIL";
		case OL_SIDE_WEAPON: return out << "OL_SIDE_WEAPON";
		case OL_SHIELD: return out << "OL_SHIELD";
		case OL_QUIVER: return out << "OL_QUIVER";
		case OL_BACK_WEAPON: return out << "OL_BACK_WEAPON";
		case OL_BACK_WEAPON2: return out << "OL_BACK_WEAPON2";
		case OL_PONYTAIL: return out << "OL_PONYTAIL";
		case OL_WING: return out << "OL_WING";
		case OL_NULL: return out << "OL_NULL";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--SkyrimLayer--//

void NifStream( SkyrimLayer & val, istream& in, const NifInfo & info ) {
	byte temp;
	NifStream( temp, in, info );
	val = SkyrimLayer(temp);
}

void NifStream( SkyrimLayer const & val, ostream& out, const NifInfo & info ) {
	NifStream( (byte)(val), out, info );
}

ostream & operator<<( ostream & out, SkyrimLayer const & val ) {
	switch ( val ) {
		case SKYL_UNIDENTIFIED: return out << "SKYL_UNIDENTIFIED";
		case SKYL_STATIC: return out << "SKYL_STATIC";
		case SKYL_ANIMSTATIC: return out << "SKYL_ANIMSTATIC";
		case SKYL_TRANSPARENT: return out << "SKYL_TRANSPARENT";
		case SKYL_CLUTTER: return out << "SKYL_CLUTTER";
		case SKYL_WEAPON: return out << "SKYL_WEAPON";
		case SKYL_PROJECTILE: return out << "SKYL_PROJECTILE";
		case SKYL_SPELL: return out << "SKYL_SPELL";
		case SKYL_BIPED: return out << "SKYL_BIPED";
		case SKYL_TREES: return out << "SKYL_TREES";
		case SKYL_PROPS: return out << "SKYL_PROPS";
		case SKYL_WATER: return out << "SKYL_WATER";
		case SKYL_TRIGGER: return out << "SKYL_TRIGGER";
		case SKYL_TERRAIN: return out << "SKYL_TERRAIN";
		case SKYL_TRAP: return out << "SKYL_TRAP";
		case SKYL_NONCOLLIDABLE: return out << "SKYL_NONCOLLIDABLE";
		case SKYL_CLOUD_TRAP: return out << "SKYL_CLOUD_TRAP";
		case SKYL_GROUND: return out << "SKYL_GROUND";
		case SKYL_PORTAL: return out << "SKYL_PORTAL";
		case SKYL_DEBRIS_SMALL: return out << "SKYL_DEBRIS_SMALL";
		case SKYL_DEBRIS_LARGE: return out << "SKYL_DEBRIS_LARGE";
		case SKYL_ACOUSTIC_SPACE: return out << "SKYL_ACOUSTIC_SPACE";
		case SKYL_ACTORZONE: return out << "SKYL_ACTORZONE";
		case SKYL_PROJECTILEZONE: return out << "SKYL_PROJECTILEZONE";
		case SKYL_GASTRAP: return out << "SKYL_GASTRAP";
		case SKYL_SHELLCASING: return out << "SKYL_SHELLCASING";
		case SKYL_TRANSPARENT_SMALL: return out << "SKYL_TRANSPARENT_SMALL";
		case SKYL_INVISIBLE_WALL: return out << "SKYL_INVISIBLE_WALL";
		case SKYL_TRANSPARENT_SMALL_ANIM: return out << "SKYL_TRANSPARENT_SMALL_ANIM";
		case SKYL_WARD: return out << "SKYL_WARD";
		case SKYL_CHARCONTROLLER: return out << "SKYL_CHARCONTROLLER";
		case SKYL_STAIRHELPER: return out << "SKYL_STAIRHELPER";
		case SKYL_DEADBIP: return out << "SKYL_DEADBIP";
		case SKYL_BIPED_NO_CC: return out << "SKYL_BIPED_NO_CC";
		case SKYL_AVOIDBOX: return out << "SKYL_AVOIDBOX";
		case SKYL_COLLISIONBOX: return out << "SKYL_COLLISIONBOX";
		case SKYL_CAMERASHPERE: return out << "SKYL_CAMERASHPERE";
		case SKYL_DOORDETECTION: return out << "SKYL_DOORDETECTION";
		case SKYL_CONEPROJECTILE: return out << "SKYL_CONEPROJECTILE";
		case SKYL_CAMERAPICK: return out << "SKYL_CAMERAPICK";
		case SKYL_ITEMPICK: return out << "SKYL_ITEMPICK";
		case SKYL_LINEOFSIGHT: return out << "SKYL_LINEOFSIGHT";
		case SKYL_PATHPICK: return out << "SKYL_PATHPICK";
		case SKYL_CUSTOMPICK1: return out << "SKYL_CUSTOMPICK1";
		case SKYL_CUSTOMPICK2: return out << "SKYL_CUSTOMPICK2";
		case SKYL_SPELLEXPLOSION: return out << "SKYL_SPELLEXPLOSION";
		case SKYL_DROPPINGPICK: return out << "SKYL_DROPPINGPICK";
		case SKYL_NULL: return out << "SKYL_NULL";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--PSLoopBehavior--//

void NifStream( PSLoopBehavior & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = PSLoopBehavior(temp);
}

void NifStream( PSLoopBehavior const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, PSLoopBehavior const & val ) {
	switch ( val ) {
		case PS_LOOP_CLAMP_BIRTH: return out << "PS_LOOP_CLAMP_BIRTH";
		case PS_LOOP_CLAMP_DEATH: return out << "PS_LOOP_CLAMP_DEATH";
		case PS_LOOP_AGESCALE: return out << "PS_LOOP_AGESCALE";
		case PS_LOOP_LOOP: return out << "PS_LOOP_LOOP";
		case PS_LOOP_REFLECT: return out << "PS_LOOP_REFLECT";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--SolverDeactivation--//

void NifStream( SolverDeactivation & val, istream& in, const NifInfo & info ) {
	byte temp;
	NifStream( temp, in, info );
	val = SolverDeactivation(temp);
}

void NifStream( SolverDeactivation const & val, ostream& out, const NifInfo & info ) {
	NifStream( (byte)(val), out, info );
}

ostream & operator<<( ostream & out, SolverDeactivation const & val ) {
	switch ( val ) {
		case SOLVER_DEACTIVATION_INVALID: return out << "SOLVER_DEACTIVATION_INVALID";
		case SOLVER_DEACTIVATION_OFF: return out << "SOLVER_DEACTIVATION_OFF";
		case SOLVER_DEACTIVATION_LOW: return out << "SOLVER_DEACTIVATION_LOW";
		case SOLVER_DEACTIVATION_MEDIUM: return out << "SOLVER_DEACTIVATION_MEDIUM";
		case SOLVER_DEACTIVATION_HIGH: return out << "SOLVER_DEACTIVATION_HIGH";
		case SOLVER_DEACTIVATION_MAX: return out << "SOLVER_DEACTIVATION_MAX";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--MeshPrimitiveType--//

void NifStream( MeshPrimitiveType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = MeshPrimitiveType(temp);
}

void NifStream( MeshPrimitiveType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, MeshPrimitiveType const & val ) {
	switch ( val ) {
		case MESH_PRIMITIVE_TRIANGLES: return out << "MESH_PRIMITIVE_TRIANGLES";
		case MESH_PRIMITIVE_TRISTRIPS: return out << "MESH_PRIMITIVE_TRISTRIPS";
		case MESH_PRIMITIVE_LINESTRIPS: return out << "MESH_PRIMITIVE_LINESTRIPS";
		case MESH_PRIMITIVE_QUADS: return out << "MESH_PRIMITIVE_QUADS";
		case MESH_PRIMITIVE_POINTS: return out << "MESH_PRIMITIVE_POINTS";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--FaceDrawMode--//

void NifStream( FaceDrawMode & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = FaceDrawMode(temp);
}

void NifStream( FaceDrawMode const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, FaceDrawMode const & val ) {
	switch ( val ) {
		case DRAW_CCW_OR_BOTH: return out << "DRAW_CCW_OR_BOTH";
		case DRAW_CCW: return out << "DRAW_CCW";
		case DRAW_CW: return out << "DRAW_CW";
		case DRAW_BOTH: return out << "DRAW_BOTH";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--AlphaFormat--//

void NifStream( AlphaFormat & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = AlphaFormat(temp);
}

void NifStream( AlphaFormat const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, AlphaFormat const & val ) {
	switch ( val ) {
		case ALPHA_NONE: return out << "ALPHA_NONE";
		case ALPHA_BINARY: return out << "ALPHA_BINARY";
		case ALPHA_SMOOTH: return out << "ALPHA_SMOOTH";
		case ALPHA_DEFAULT: return out << "ALPHA_DEFAULT";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--BoundVolumeType--//

void NifStream( BoundVolumeType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = BoundVolumeType(temp);
}

void NifStream( BoundVolumeType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, BoundVolumeType const & val ) {
	switch ( val ) {
		case BASE_BV: return out << "BASE_BV";
		case SPHERE_BV: return out << "SPHERE_BV";
		case BOX_BV: return out << "BOX_BV";
		case CAPSULE_BV: return out << "CAPSULE_BV";
		case UNION_BV: return out << "UNION_BV";
		case HALFSPACE_BV: return out << "HALFSPACE_BV";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--EffectType--//

void NifStream( EffectType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = EffectType(temp);
}

void NifStream( EffectType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, EffectType const & val ) {
	switch ( val ) {
		case EFFECT_PROJECTED_LIGHT: return out << "EFFECT_PROJECTED_LIGHT";
		case EFFECT_PROJECTED_SHADOW: return out << "EFFECT_PROJECTED_SHADOW";
		case EFFECT_ENVIRONMENT_MAP: return out << "EFFECT_ENVIRONMENT_MAP";
		case EFFECT_FOG_MAP: return out << "EFFECT_FOG_MAP";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--KeyType--//

void NifStream( KeyType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = KeyType(temp);
}

void NifStream( KeyType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, KeyType const & val ) {
	switch ( val ) {
		case LINEAR_KEY: return out << "LINEAR_KEY";
		case QUADRATIC_KEY: return out << "QUADRATIC_KEY";
		case TBC_KEY: return out << "TBC_KEY";
		case XYZ_ROTATION_KEY: return out << "XYZ_ROTATION_KEY";
		case CONST_KEY: return out << "CONST_KEY";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--VertMode--//

void NifStream( VertMode & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = VertMode(temp);
}

void NifStream( VertMode const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, VertMode const & val ) {
	switch ( val ) {
		case VERT_MODE_SRC_IGNORE: return out << "VERT_MODE_SRC_IGNORE";
		case VERT_MODE_SRC_EMISSIVE: return out << "VERT_MODE_SRC_EMISSIVE";
		case VERT_MODE_SRC_AMB_DIF: return out << "VERT_MODE_SRC_AMB_DIF";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--SortingMode--//

void NifStream( SortingMode & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = SortingMode(temp);
}

void NifStream( SortingMode const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, SortingMode const & val ) {
	switch ( val ) {
		case SORTING_INHERIT: return out << "SORTING_INHERIT";
		case SORTING_OFF: return out << "SORTING_OFF";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--CoordGenType--//

void NifStream( CoordGenType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = CoordGenType(temp);
}

void NifStream( CoordGenType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, CoordGenType const & val ) {
	switch ( val ) {
		case CG_WORLD_PARALLEL: return out << "CG_WORLD_PARALLEL";
		case CG_WORLD_PERSPECTIVE: return out << "CG_WORLD_PERSPECTIVE";
		case CG_SPHERE_MAP: return out << "CG_SPHERE_MAP";
		case CG_SPECULAR_CUBE_MAP: return out << "CG_SPECULAR_CUBE_MAP";
		case CG_DIFFUSE_CUBE_MAP: return out << "CG_DIFFUSE_CUBE_MAP";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--BSShaderType--//

void NifStream( BSShaderType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = BSShaderType(temp);
}

void NifStream( BSShaderType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, BSShaderType const & val ) {
	switch ( val ) {
		case SHADER_TALL_GRASS: return out << "SHADER_TALL_GRASS";
		case SHADER_DEFAULT: return out << "SHADER_DEFAULT";
		case SHADER_SKY: return out << "SHADER_SKY";
		case SHADER_SKIN: return out << "SHADER_SKIN";
		case SHADER_WATER: return out << "SHADER_WATER";
		case SHADER_LIGHTING30: return out << "SHADER_LIGHTING30";
		case SHADER_TILE: return out << "SHADER_TILE";
		case SHADER_NOLIGHTING: return out << "SHADER_NOLIGHTING";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--ApplyMode--//

void NifStream( ApplyMode & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = ApplyMode(temp);
}

void NifStream( ApplyMode const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, ApplyMode const & val ) {
	switch ( val ) {
		case APPLY_REPLACE: return out << "APPLY_REPLACE";
		case APPLY_DECAL: return out << "APPLY_DECAL";
		case APPLY_MODULATE: return out << "APPLY_MODULATE";
		case APPLY_HILIGHT: return out << "APPLY_HILIGHT";
		case APPLY_HILIGHT2: return out << "APPLY_HILIGHT2";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--MotionSystem--//

void NifStream( MotionSystem & val, istream& in, const NifInfo & info ) {
	byte temp;
	NifStream( temp, in, info );
	val = MotionSystem(temp);
}

void NifStream( MotionSystem const & val, ostream& out, const NifInfo & info ) {
	NifStream( (byte)(val), out, info );
}

ostream & operator<<( ostream & out, MotionSystem const & val ) {
	switch ( val ) {
		case MO_SYS_INVALID: return out << "MO_SYS_INVALID";
		case MO_SYS_DYNAMIC: return out << "MO_SYS_DYNAMIC";
		case MO_SYS_SPHERE: return out << "MO_SYS_SPHERE";
		case MO_SYS_SPHERE_INERTIA: return out << "MO_SYS_SPHERE_INERTIA";
		case MO_SYS_BOX: return out << "MO_SYS_BOX";
		case MO_SYS_BOX_STABILIZED: return out << "MO_SYS_BOX_STABILIZED";
		case MO_SYS_KEYFRAMED: return out << "MO_SYS_KEYFRAMED";
		case MO_SYS_FIXED: return out << "MO_SYS_FIXED";
		case MO_SYS_THIN_BOX: return out << "MO_SYS_THIN_BOX";
		case MO_SYS_CHARACTER: return out << "MO_SYS_CHARACTER";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--BillboardMode--//

void NifStream( BillboardMode & val, istream& in, const NifInfo & info ) {
	unsigned short temp;
	NifStream( temp, in, info );
	val = BillboardMode(temp);
}

void NifStream( BillboardMode const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned short)(val), out, info );
}

ostream & operator<<( ostream & out, BillboardMode const & val ) {
	switch ( val ) {
		case ALWAYS_FACE_CAMERA: return out << "ALWAYS_FACE_CAMERA";
		case ROTATE_ABOUT_UP: return out << "ROTATE_ABOUT_UP";
		case RIGID_FACE_CAMERA: return out << "RIGID_FACE_CAMERA";
		case ALWAYS_FACE_CENTER: return out << "ALWAYS_FACE_CENTER";
		case RIGID_FACE_CENTER: return out << "RIGID_FACE_CENTER";
		case ROTATE_ABOUT_UP2: return out << "ROTATE_ABOUT_UP2";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--ZCompareMode--//

void NifStream( ZCompareMode & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = ZCompareMode(temp);
}

void NifStream( ZCompareMode const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, ZCompareMode const & val ) {
	switch ( val ) {
		case ZCOMP_ALWAYS: return out << "ZCOMP_ALWAYS";
		case ZCOMP_LESS: return out << "ZCOMP_LESS";
		case ZCOMP_EQUAL: return out << "ZCOMP_EQUAL";
		case ZCOMP_LESS_EQUAL: return out << "ZCOMP_LESS_EQUAL";
		case ZCOMP_GREATER: return out << "ZCOMP_GREATER";
		case ZCOMP_NOT_EQUAL: return out << "ZCOMP_NOT_EQUAL";
		case ZCOMP_GREATER_EQUAL: return out << "ZCOMP_GREATER_EQUAL";
		case ZCOMP_NEVER: return out << "ZCOMP_NEVER";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--TargetColor--//

void NifStream( TargetColor & val, istream& in, const NifInfo & info ) {
	unsigned short temp;
	NifStream( temp, in, info );
	val = TargetColor(temp);
}

void NifStream( TargetColor const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned short)(val), out, info );
}

ostream & operator<<( ostream & out, TargetColor const & val ) {
	switch ( val ) {
		case TC_AMBIENT: return out << "TC_AMBIENT";
		case TC_DIFFUSE: return out << "TC_DIFFUSE";
		case TC_SPECULAR: return out << "TC_SPECULAR";
		case TC_SELF_ILLUM: return out << "TC_SELF_ILLUM";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--SkyrimHavokMaterial--//

void NifStream( SkyrimHavokMaterial & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = SkyrimHavokMaterial(temp);
}

void NifStream( SkyrimHavokMaterial const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, SkyrimHavokMaterial const & val ) {
	switch ( val ) {
		case SKY_HAV_MAT_LIGHT_WOOD: return out << "SKY_HAV_MAT_LIGHT_WOOD";
		case SKY_HAV_MAT_BROKEN_STONE: return out << "SKY_HAV_MAT_BROKEN_STONE";
		case SKY_HAV_MAT_SNOW: return out << "SKY_HAV_MAT_SNOW";
		case SKY_HAV_MAT_GRAVEL: return out << "SKY_HAV_MAT_GRAVEL";
		case SKY_HAV_MAT_MATERIAL_CHAIN_METAL: return out << "SKY_HAV_MAT_MATERIAL_CHAIN_METAL";
		case SKY_HAV_MAT_WOOD: return out << "SKY_HAV_MAT_WOOD";
		case SKY_HAV_MAT_SKIN: return out << "SKY_HAV_MAT_SKIN";
		case SKY_HAV_MAT_BARREL: return out << "SKY_HAV_MAT_BARREL";
		case SKY_HAV_MAT_MATERIAL_CERAMIC_MEDIUM: return out << "SKY_HAV_MAT_MATERIAL_CERAMIC_MEDIUM";
		case SKY_HAV_MAT_MATERIAL_BASKET: return out << "SKY_HAV_MAT_MATERIAL_BASKET";
		case SKY_HAV_MAT_ICE: return out << "SKY_HAV_MAT_ICE";
		case SKY_HAV_MAT_STAIRS_STONE: return out << "SKY_HAV_MAT_STAIRS_STONE";
		case SKY_HAV_MAT_MATERIAL_BLADE_1HAND: return out << "SKY_HAV_MAT_MATERIAL_BLADE_1HAND";
		case SKY_HAV_MAT_WATER: return out << "SKY_HAV_MAT_WATER";
		case SKY_HAV_MAT_UNKNOWN_1028101969: return out << "SKY_HAV_MAT_UNKNOWN_1028101969";
		case SKY_HAV_MAT_MATERIAL_BOOK: return out << "SKY_HAV_MAT_MATERIAL_BOOK";
		case SKY_HAV_MAT_SOLID_METAL: return out << "SKY_HAV_MAT_SOLID_METAL";
		case SKY_HAV_MAT_MATERIAL_AXE_1HAND: return out << "SKY_HAV_MAT_MATERIAL_AXE_1HAND";
		case SKY_HAV_MAT_UNKNOWN_1440721808: return out << "SKY_HAV_MAT_UNKNOWN_1440721808";
		case SKY_HAV_MAT_STAIRS_WOOD: return out << "SKY_HAV_MAT_STAIRS_WOOD";
		case SKY_HAV_MAT_MUD: return out << "SKY_HAV_MAT_MUD";
		case SKY_HAV_MAT_STAIRS_SNOW: return out << "SKY_HAV_MAT_STAIRS_SNOW";
		case SKY_HAV_MAT_UNKNOWN_1574477864: return out << "SKY_HAV_MAT_UNKNOWN_1574477864";
		case SKY_HAV_MAT_UNKNOWN_1591009235: return out << "SKY_HAV_MAT_UNKNOWN_1591009235";
		case SKY_HAV_MAT_MATERIAL_BOWS_STAVES: return out << "SKY_HAV_MAT_MATERIAL_BOWS_STAVES";
		case SKY_HAV_MAT_MATERIAL_WOOD_AS_STAIRS: return out << "SKY_HAV_MAT_MATERIAL_WOOD_AS_STAIRS";
		case SKY_HAV_MAT_GRASS: return out << "SKY_HAV_MAT_GRASS";
		case SKY_HAV_MAT_MATERIAL_BOULDER_LARGE: return out << "SKY_HAV_MAT_MATERIAL_BOULDER_LARGE";
		case SKY_HAV_MAT_MATERIAL_STONE_AS_STAIRS: return out << "SKY_HAV_MAT_MATERIAL_STONE_AS_STAIRS";
		case SKY_HAV_MAT_MATERIAL_BLADE_2HAND: return out << "SKY_HAV_MAT_MATERIAL_BLADE_2HAND";
		case SKY_HAV_MAT_MATERIAL_BOTTLE_SMALL: return out << "SKY_HAV_MAT_MATERIAL_BOTTLE_SMALL";
		case SKY_HAV_MAT_SAND: return out << "SKY_HAV_MAT_SAND";
		case SKY_HAV_MAT_HEAVY_METAL: return out << "SKY_HAV_MAT_HEAVY_METAL";
		case SKY_HAV_MAT_DRAGON: return out << "SKY_HAV_MAT_DRAGON";
		case SKY_HAV_MAT_MATERIAL_BLADE_1HAND_SMALL: return out << "SKY_HAV_MAT_MATERIAL_BLADE_1HAND_SMALL";
		case SKY_HAV_MAT_MATERIAL_SKIN_SMALL: return out << "SKY_HAV_MAT_MATERIAL_SKIN_SMALL";
		case SKY_HAV_MAT_STAIRS_BROKEN_STONE: return out << "SKY_HAV_MAT_STAIRS_BROKEN_STONE";
		case SKY_HAV_MAT_MATERIAL_SKIN_LARGE: return out << "SKY_HAV_MAT_MATERIAL_SKIN_LARGE";
		case SKY_HAV_MAT_ORGANIC: return out << "SKY_HAV_MAT_ORGANIC";
		case SKY_HAV_MAT_MATERIAL_BONE: return out << "SKY_HAV_MAT_MATERIAL_BONE";
		case SKY_HAV_MAT_HEAVY_WOOD: return out << "SKY_HAV_MAT_HEAVY_WOOD";
		case SKY_HAV_MAT_MATERIAL_CHAIN: return out << "SKY_HAV_MAT_MATERIAL_CHAIN";
		case SKY_HAV_MAT_DIRT: return out << "SKY_HAV_MAT_DIRT";
		case SKY_HAV_MAT_MATERIAL_ARMOR_LIGHT: return out << "SKY_HAV_MAT_MATERIAL_ARMOR_LIGHT";
		case SKY_HAV_MAT_MATERIAL_SHIELD_LIGHT: return out << "SKY_HAV_MAT_MATERIAL_SHIELD_LIGHT";
		case SKY_HAV_MAT_MATERIAL_COIN: return out << "SKY_HAV_MAT_MATERIAL_COIN";
		case SKY_HAV_MAT_MATERIAL_SHIELD_HEAVY: return out << "SKY_HAV_MAT_MATERIAL_SHIELD_HEAVY";
		case SKY_HAV_MAT_MATERIAL_ARMOR_HEAVY: return out << "SKY_HAV_MAT_MATERIAL_ARMOR_HEAVY";
		case SKY_HAV_MAT_MATERIAL_ARROW: return out << "SKY_HAV_MAT_MATERIAL_ARROW";
		case SKY_HAV_MAT_GLASS: return out << "SKY_HAV_MAT_GLASS";
		case SKY_HAV_MAT_STONE: return out << "SKY_HAV_MAT_STONE";
		case SKY_HAV_MAT_CLOTH: return out << "SKY_HAV_MAT_CLOTH";
		case SKY_HAV_MAT_MATERIAL_BLUNT_2HAND: return out << "SKY_HAV_MAT_MATERIAL_BLUNT_2HAND";
		case SKY_HAV_MAT_MATERIAL_BOULDER_MEDIUM: return out << "SKY_HAV_MAT_MATERIAL_BOULDER_MEDIUM";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--ChannelConvention--//

void NifStream( ChannelConvention & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = ChannelConvention(temp);
}

void NifStream( ChannelConvention const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, ChannelConvention const & val ) {
	switch ( val ) {
		case CC_FIXED: return out << "CC_FIXED";
		case CC_INDEX: return out << "CC_INDEX";
		case CC_COMPRESSED: return out << "CC_COMPRESSED";
		case CC_EMPTY: return out << "CC_EMPTY";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--ImageType--//

void NifStream( ImageType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = ImageType(temp);
}

void NifStream( ImageType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, ImageType const & val ) {
	switch ( val ) {
		case RGB: return out << "RGB";
		case RGBA: return out << "RGBA";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--PixelLayout--//

void NifStream( PixelLayout & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = PixelLayout(temp);
}

void NifStream( PixelLayout const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, PixelLayout const & val ) {
	switch ( val ) {
		case PIX_LAY_PALETTISED: return out << "PIX_LAY_PALETTISED";
		case PIX_LAY_HIGH_COLOR_16: return out << "PIX_LAY_HIGH_COLOR_16";
		case PIX_LAY_TRUE_COLOR_32: return out << "PIX_LAY_TRUE_COLOR_32";
		case PIX_LAY_COMPRESSED: return out << "PIX_LAY_COMPRESSED";
		case PIX_LAY_BUMPMAP: return out << "PIX_LAY_BUMPMAP";
		case PIX_LAY_PALETTISED_4: return out << "PIX_LAY_PALETTISED_4";
		case PIX_LAY_DEFAULT: return out << "PIX_LAY_DEFAULT";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--ConsistencyType--//

void NifStream( ConsistencyType & val, istream& in, const NifInfo & info ) {
	unsigned short temp;
	NifStream( temp, in, info );
	val = ConsistencyType(temp);
}

void NifStream( ConsistencyType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned short)(val), out, info );
}

ostream & operator<<( ostream & out, ConsistencyType const & val ) {
	switch ( val ) {
		case CT_MUTABLE: return out << "CT_MUTABLE";
		case CT_STATIC: return out << "CT_STATIC";
		case CT_VOLATILE: return out << "CT_VOLATILE";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--TexClampMode--//

void NifStream( TexClampMode & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = TexClampMode(temp);
}

void NifStream( TexClampMode const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, TexClampMode const & val ) {
	switch ( val ) {
		case CLAMP_S_CLAMP_T: return out << "CLAMP_S_CLAMP_T";
		case CLAMP_S_WRAP_T: return out << "CLAMP_S_WRAP_T";
		case WRAP_S_CLAMP_T: return out << "WRAP_S_CLAMP_T";
		case WRAP_S_WRAP_T: return out << "WRAP_S_WRAP_T";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--ComponentFormat--//

void NifStream( ComponentFormat & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = ComponentFormat(temp);
}

void NifStream( ComponentFormat const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, ComponentFormat const & val ) {
	switch ( val ) {
		case F_UNKNOWN: return out << "F_UNKNOWN";
		case F_INT8_1: return out << "F_INT8_1";
		case F_INT8_2: return out << "F_INT8_2";
		case F_INT8_3: return out << "F_INT8_3";
		case F_INT8_4: return out << "F_INT8_4";
		case F_UINT8_1: return out << "F_UINT8_1";
		case F_UINT8_2: return out << "F_UINT8_2";
		case F_UINT8_3: return out << "F_UINT8_3";
		case F_UINT8_4: return out << "F_UINT8_4";
		case F_NORMINT8_1: return out << "F_NORMINT8_1";
		case F_NORMINT8_2: return out << "F_NORMINT8_2";
		case F_NORMINT8_3: return out << "F_NORMINT8_3";
		case F_NORMINT8_4: return out << "F_NORMINT8_4";
		case F_NORMUINT8_1: return out << "F_NORMUINT8_1";
		case F_NORMUINT8_2: return out << "F_NORMUINT8_2";
		case F_NORMUINT8_3: return out << "F_NORMUINT8_3";
		case F_NORMUINT8_4: return out << "F_NORMUINT8_4";
		case F_INT16_1: return out << "F_INT16_1";
		case F_INT16_2: return out << "F_INT16_2";
		case F_INT16_3: return out << "F_INT16_3";
		case F_INT16_4: return out << "F_INT16_4";
		case F_UINT16_1: return out << "F_UINT16_1";
		case F_UINT16_2: return out << "F_UINT16_2";
		case F_UINT16_3: return out << "F_UINT16_3";
		case F_UINT16_4: return out << "F_UINT16_4";
		case F_NORMINT16_1: return out << "F_NORMINT16_1";
		case F_NORMINT16_2: return out << "F_NORMINT16_2";
		case F_NORMINT16_3: return out << "F_NORMINT16_3";
		case F_NORMINT16_4: return out << "F_NORMINT16_4";
		case F_NORMUINT16_1: return out << "F_NORMUINT16_1";
		case F_NORMUINT16_2: return out << "F_NORMUINT16_2";
		case F_NORMUINT16_3: return out << "F_NORMUINT16_3";
		case F_NORMUINT16_4: return out << "F_NORMUINT16_4";
		case F_INT32_1: return out << "F_INT32_1";
		case F_INT32_2: return out << "F_INT32_2";
		case F_INT32_3: return out << "F_INT32_3";
		case F_INT32_4: return out << "F_INT32_4";
		case F_UINT32_1: return out << "F_UINT32_1";
		case F_UINT32_2: return out << "F_UINT32_2";
		case F_UINT32_3: return out << "F_UINT32_3";
		case F_UINT32_4: return out << "F_UINT32_4";
		case F_NORMINT32_1: return out << "F_NORMINT32_1";
		case F_NORMINT32_2: return out << "F_NORMINT32_2";
		case F_NORMINT32_3: return out << "F_NORMINT32_3";
		case F_NORMINT32_4: return out << "F_NORMINT32_4";
		case F_NORMUINT32_1: return out << "F_NORMUINT32_1";
		case F_NORMUINT32_2: return out << "F_NORMUINT32_2";
		case F_NORMUINT32_3: return out << "F_NORMUINT32_3";
		case F_NORMUINT32_4: return out << "F_NORMUINT32_4";
		case F_FLOAT16_1: return out << "F_FLOAT16_1";
		case F_FLOAT16_2: return out << "F_FLOAT16_2";
		case F_FLOAT16_3: return out << "F_FLOAT16_3";
		case F_FLOAT16_4: return out << "F_FLOAT16_4";
		case F_FLOAT32_1: return out << "F_FLOAT32_1";
		case F_FLOAT32_2: return out << "F_FLOAT32_2";
		case F_FLOAT32_3: return out << "F_FLOAT32_3";
		case F_FLOAT32_4: return out << "F_FLOAT32_4";
		case F_UINT_10_10_10_L1: return out << "F_UINT_10_10_10_L1";
		case F_NORMINT_10_10_10_L1: return out << "F_NORMINT_10_10_10_L1";
		case F_NORMINT_11_11_10: return out << "F_NORMINT_11_11_10";
		case F_NORMUINT8_4_BGRA: return out << "F_NORMUINT8_4_BGRA";
		case F_NORMINT_10_10_10_2: return out << "F_NORMINT_10_10_10_2";
		case F_UINT_10_10_10_2: return out << "F_UINT_10_10_10_2";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--MotionQuality--//

void NifStream( MotionQuality & val, istream& in, const NifInfo & info ) {
	byte temp;
	NifStream( temp, in, info );
	val = MotionQuality(temp);
}

void NifStream( MotionQuality const & val, ostream& out, const NifInfo & info ) {
	NifStream( (byte)(val), out, info );
}

ostream & operator<<( ostream & out, MotionQuality const & val ) {
	switch ( val ) {
		case MO_QUAL_INVALID: return out << "MO_QUAL_INVALID";
		case MO_QUAL_FIXED: return out << "MO_QUAL_FIXED";
		case MO_QUAL_KEYFRAMED: return out << "MO_QUAL_KEYFRAMED";
		case MO_QUAL_DEBRIS: return out << "MO_QUAL_DEBRIS";
		case MO_QUAL_MOVING: return out << "MO_QUAL_MOVING";
		case MO_QUAL_CRITICAL: return out << "MO_QUAL_CRITICAL";
		case MO_QUAL_BULLET: return out << "MO_QUAL_BULLET";
		case MO_QUAL_USER: return out << "MO_QUAL_USER";
		case MO_QUAL_CHARACTER: return out << "MO_QUAL_CHARACTER";
		case MO_QUAL_KEYFRAMED_REPORT: return out << "MO_QUAL_KEYFRAMED_REPORT";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--CloningBehavior--//

void NifStream( CloningBehavior & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = CloningBehavior(temp);
}

void NifStream( CloningBehavior const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, CloningBehavior const & val ) {
	switch ( val ) {
		case CLONING_SHARE: return out << "CLONING_SHARE";
		case CLONING_COPY: return out << "CLONING_COPY";
		case CLONING_BLANK_COPY: return out << "CLONING_BLANK_COPY";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--PropagationMode--//

void NifStream( PropagationMode & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = PropagationMode(temp);
}

void NifStream( PropagationMode const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, PropagationMode const & val ) {
	switch ( val ) {
		case PROPAGATE_ON_SUCCESS: return out << "PROPAGATE_ON_SUCCESS";
		case PROPAGATE_ON_FAILURE: return out << "PROPAGATE_ON_FAILURE";
		case PROPAGATE_ALWAYS: return out << "PROPAGATE_ALWAYS";
		case PROPAGATE_NEVER: return out << "PROPAGATE_NEVER";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--PixelFormat--//

void NifStream( PixelFormat & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = PixelFormat(temp);
}

void NifStream( PixelFormat const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, PixelFormat const & val ) {
	switch ( val ) {
		case PX_FMT_RGB8: return out << "PX_FMT_RGB8";
		case PX_FMT_RGBA8: return out << "PX_FMT_RGBA8";
		case PX_FMT_PAL8: return out << "PX_FMT_PAL8";
		case PX_FMT_DXT1: return out << "PX_FMT_DXT1";
		case PX_FMT_DXT5: return out << "PX_FMT_DXT5";
		case PX_FMT_DXT5_ALT: return out << "PX_FMT_DXT5_ALT";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--CycleType--//

void NifStream( CycleType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = CycleType(temp);
}

void NifStream( CycleType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, CycleType const & val ) {
	switch ( val ) {
		case CYCLE_LOOP: return out << "CYCLE_LOOP";
		case CYCLE_REVERSE: return out << "CYCLE_REVERSE";
		case CYCLE_CLAMP: return out << "CYCLE_CLAMP";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--FieldType--//

void NifStream( FieldType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = FieldType(temp);
}

void NifStream( FieldType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, FieldType const & val ) {
	switch ( val ) {
		case FIELD_WIND: return out << "FIELD_WIND";
		case FIELD_POINT: return out << "FIELD_POINT";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--BSLightingShaderPropertyShaderType--//

void NifStream( BSLightingShaderPropertyShaderType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = BSLightingShaderPropertyShaderType(temp);
}

void NifStream( BSLightingShaderPropertyShaderType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, BSLightingShaderPropertyShaderType const & val ) {
	switch ( val ) {
		case DEFAULT: return out << "Default";
		case ENVIRONMENT_MAP: return out << "Environment Map";
		case GLOW_SHADER: return out << "Glow Shader";
		case HEIGHTMAP: return out << "Heightmap";
		case FACE_TINT: return out << "Face Tint";
		case SKIN_TINT: return out << "Skin Tint";
		case HAIR_TINT: return out << "Hair Tint";
		case PARALLAX_OCC_MATERIAL: return out << "Parallax Occ Material";
		case WORLD_MULTITEXTURE: return out << "World Multitexture";
		case WORLDMAP1: return out << "WorldMap1";
		case UNKNOWN_10: return out << "Unknown 10";
		case MULTILAYER_PARALLAX: return out << "MultiLayer Parallax";
		case UNKNOWN_12: return out << "Unknown 12";
		case WORLDMAP2: return out << "WorldMap2";
		case SPARKLE_SNOW: return out << "Sparkle Snow";
		case WORLDMAP3: return out << "WorldMap3";
		case EYE_ENVMAP: return out << "Eye Envmap";
		case UNKNOWN_17: return out << "Unknown 17";
		case WORLDMAP4: return out << "WorldMap4";
		case WORLD_LOD_MULTITEXTURE: return out << "World LOD Multitexture";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--DecayType--//

void NifStream( DecayType & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = DecayType(temp);
}

void NifStream( DecayType const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, DecayType const & val ) {
	switch ( val ) {
		case DECAY_NONE: return out << "DECAY_NONE";
		case DECAY_LINEAR: return out << "DECAY_LINEAR";
		case DECAY_EXPONENTIAL: return out << "DECAY_EXPONENTIAL";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--EmitFrom--//

void NifStream( EmitFrom & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = EmitFrom(temp);
}

void NifStream( EmitFrom const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, EmitFrom const & val ) {
	switch ( val ) {
		case EMIT_FROM_VERTICES: return out << "EMIT_FROM_VERTICES";
		case EMIT_FROM_FACE_CENTER: return out << "EMIT_FROM_FACE_CENTER";
		case EMIT_FROM_EDGE_CENTER: return out << "EMIT_FROM_EDGE_CENTER";
		case EMIT_FROM_FACE_SURFACE: return out << "EMIT_FROM_FACE_SURFACE";
		case EMIT_FROM_EDGE_SURFACE: return out << "EMIT_FROM_EDGE_SURFACE";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--SkyrimWaterShaderFlags--//

void NifStream( SkyrimWaterShaderFlags & val, istream& in, const NifInfo & info ) {
	byte temp;
	NifStream( temp, in, info );
	val = SkyrimWaterShaderFlags(temp);
}

void NifStream( SkyrimWaterShaderFlags const & val, ostream& out, const NifInfo & info ) {
	NifStream( (byte)(val), out, info );
}

ostream & operator<<( ostream & out, SkyrimWaterShaderFlags const & val ) {
	switch ( val ) {
		case SWSF1_UNKNOWN0: return out << "SWSF1_UNKNOWN0";
		case SWSF1_BYPASS_REFRACTION_MAP: return out << "SWSF1_Bypass_Refraction_Map";
		case SWSF1_WATER_TOGGLE: return out << "SWSF1_Water_Toggle";
		case SWSF1_UNKNOWN3: return out << "SWSF1_UNKNOWN3";
		case SWSF1_UNKNOWN4: return out << "SWSF1_UNKNOWN4";
		case SWSF1_UNKNOWN5: return out << "SWSF1_UNKNOWN5";
		case SWSF1_HIGHLIGHT_LAYER_TOGGLE: return out << "SWSF1_Highlight_Layer_Toggle";
		case SWSF1_ENABLED: return out << "SWSF1_Enabled";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--SkyrimShaderPropertyFlags1--//

void NifStream( SkyrimShaderPropertyFlags1 & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = SkyrimShaderPropertyFlags1(temp);
}

void NifStream( SkyrimShaderPropertyFlags1 const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, SkyrimShaderPropertyFlags1 const & val ) {
	switch ( val ) {
		case SLSF1_SPECULAR: return out << "SLSF1_Specular";
		case SLSF1_SKINNED: return out << "SLSF1_Skinned";
		case SLSF1_TEMP_REFRACTION: return out << "SLSF1_Temp_Refraction";
		case SLSF1_VERTEX_ALPHA: return out << "SLSF1_Vertex_Alpha";
		case SLSF1_GREYSCALE_TO_PALETTECOLOR: return out << "SLSF1_Greyscale_To_PaletteColor";
		case SLSF1_GREYSCALE_TO_PALETTEALPHA: return out << "SLSF1_Greyscale_To_PaletteAlpha";
		case SLSF1_USE_FALLOFF: return out << "SLSF1_Use_Falloff";
		case SLSF1_ENVIRONMENT_MAPPING: return out << "SLSF1_Environment_Mapping";
		case SLSF1_RECIEVE_SHADOWS: return out << "SLSF1_Recieve_Shadows";
		case SLSF1_CAST_SHADOWS: return out << "SLSF1_Cast_Shadows";
		case SLSF1_FACEGEN_DETAIL_MAP: return out << "SLSF1_Facegen_Detail_Map";
		case SLSF1_PARALLAX: return out << "SLSF1_Parallax";
		case SLSF1_MODEL_SPACE_NORMALS: return out << "SLSF1_Model_Space_Normals";
		case SLSF1_NON_PROJECTIVE_SHADOWS: return out << "SLSF1_Non_Projective_Shadows";
		case SLSF1_LANDSCAPE: return out << "SLSF1_Landscape";
		case SLSF1_REFRACTION: return out << "SLSF1_Refraction";
		case SLSF1_FIRE_REFRACTION: return out << "SLSF1_Fire_Refraction";
		case SLSF1_EYE_ENVIRONMENT_MAPPING: return out << "SLSF1_Eye_Environment_Mapping";
		case SLSF1_HAIR_SOFT_LIGHTING: return out << "SLSF1_Hair_Soft_Lighting";
		case SLSF1_SCREENDOOR_ALPHA_FADE: return out << "SLSF1_Screendoor_Alpha_Fade";
		case SLSF1_LOCALMAP_HIDE_SECRET: return out << "SLSF1_Localmap_Hide_Secret";
		case SLSF1_FACEGEN_RGB_TINT: return out << "SLSF1_FaceGen_RGB_Tint";
		case SLSF1_OWN_EMIT: return out << "SLSF1_Own_Emit";
		case SLSF1_PROJECTED_UV: return out << "SLSF1_Projected_UV";
		case SLSF1_MULTIPLE_TEXTURES: return out << "SLSF1_Multiple_Textures";
		case SLSF1_REMAPPABLE_TEXTURES: return out << "SLSF1_Remappable_Textures";
		case SLSF1_DECAL: return out << "SLSF1_Decal";
		case SLSF1_DYNAMIC_DECAL: return out << "SLSF1_Dynamic_Decal";
		case SLSF1_PARALLAX_OCCLUSION: return out << "SLSF1_Parallax_Occlusion";
		case SLSF1_EXTERNAL_EMITTANCE: return out << "SLSF1_External_Emittance";
		case SLSF1_SOFT_EFFECT: return out << "SLSF1_Soft_Effect";
		case SLSF1_ZBUFFER_TEST: return out << "SLSF1_ZBuffer_Test";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--BSShaderFlags--//

void NifStream( BSShaderFlags & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = BSShaderFlags(temp);
}

void NifStream( BSShaderFlags const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, BSShaderFlags const & val ) {
	switch ( val ) {
		case SF_SPECULAR: return out << "SF_Specular";
		case SF_SKINNED: return out << "SF_Skinned";
		case SF_LOWDETAIL: return out << "SF_LowDetail";
		case SF_VERTEX_ALPHA: return out << "SF_Vertex_Alpha";
		case SF_UNKNOWN_1: return out << "SF_Unknown_1";
		case SF_SINGLE_PASS: return out << "SF_Single_Pass";
		case SF_EMPTY: return out << "SF_Empty";
		case SF_ENVIRONMENT_MAPPING: return out << "SF_Environment_Mapping";
		case SF_ALPHA_TEXTURE: return out << "SF_Alpha_Texture";
		case SF_UNKNOWN_2: return out << "SF_Unknown_2";
		case SF_FACEGEN: return out << "SF_FaceGen";
		case SF_PARALLAX_SHADER_INDEX_15: return out << "SF_Parallax_Shader_Index_15";
		case SF_UNKNOWN_3: return out << "SF_Unknown_3";
		case SF_NON_PROJECTIVE_SHADOWS: return out << "SF_Non_Projective_Shadows";
		case SF_UNKNOWN_4: return out << "SF_Unknown_4";
		case SF_REFRACTION: return out << "SF_Refraction";
		case SF_FIRE_REFRACTION: return out << "SF_Fire_Refraction";
		case SF_EYE_ENVIRONMENT_MAPPING: return out << "SF_Eye_Environment_Mapping";
		case SF_HAIR: return out << "SF_Hair";
		case SF_DYNAMIC_ALPHA: return out << "SF_Dynamic_Alpha";
		case SF_LOCALMAP_HIDE_SECRET: return out << "SF_Localmap_Hide_Secret";
		case SF_WINDOW_ENVIRONMENT_MAPPING: return out << "SF_Window_Environment_Mapping";
		case SF_TREE_BILLBOARD: return out << "SF_Tree_Billboard";
		case SF_SHADOW_FRUSTUM: return out << "SF_Shadow_Frustum";
		case SF_MULTIPLE_TEXTURES: return out << "SF_Multiple_Textures";
		case SF_REMAPPABLE_TEXTURES: return out << "SF_Remappable_Textures";
		case SF_DECAL_SINGLE_PASS: return out << "SF_Decal_Single_Pass";
		case SF_DYNAMIC_DECAL_SINGLE_PASS: return out << "SF_Dynamic_Decal_Single_Pass";
		case SF_PARALLAX_OCCULSION: return out << "SF_Parallax_Occulsion";
		case SF_EXTERNAL_EMITTANCE: return out << "SF_External_Emittance";
		case SF_SHADOW_MAP: return out << "SF_Shadow_Map";
		case SF_ZBUFFER_TEST: return out << "SF_ZBuffer_Test";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--FurnitureEntryPoints--//

void NifStream( FurnitureEntryPoints & val, istream& in, const NifInfo & info ) {
	unsigned short temp;
	NifStream( temp, in, info );
	val = FurnitureEntryPoints(temp);
}

void NifStream( FurnitureEntryPoints const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned short)(val), out, info );
}

ostream & operator<<( ostream & out, FurnitureEntryPoints const & val ) {
	switch ( val ) {
		case FRONT: return out << "Front";
		case BEHIND: return out << "Behind";
		case RIGHT: return out << "Right";
		case LEFT: return out << "Left";
		case UP: return out << "Up";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--BSPartFlag--//

void NifStream( BSPartFlag & val, istream& in, const NifInfo & info ) {
	unsigned short temp;
	NifStream( temp, in, info );
	val = BSPartFlag(temp);
}

void NifStream( BSPartFlag const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned short)(val), out, info );
}

ostream & operator<<( ostream & out, BSPartFlag const & val ) {
	switch ( val ) {
		case PF_EDITOR_VISIBLE: return out << "PF_EDITOR_VISIBLE";
		case PF_START_NET_BONESET: return out << "PF_START_NET_BONESET";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--DataStreamAccess--//

void NifStream( DataStreamAccess & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = DataStreamAccess(temp);
}

void NifStream( DataStreamAccess const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, DataStreamAccess const & val ) {
	switch ( val ) {
		case CPU_READ: return out << "CPU Read";
		case CPU_WRITE_STATIC: return out << "CPU Write Static";
		case CPU_WRITE_MUTABLE: return out << "CPU Write Mutable";
		case CPU_WRITE_VOLATILE: return out << "CPU Write Volatile";
		case GPU_READ: return out << "GPU Read";
		case GPU_WRITE: return out << "GPU Write";
		case CPU_WRITE_STATIC_INITITIALIZED: return out << "CPU Write Static Inititialized";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--SkyrimShaderPropertyFlags2--//

void NifStream( SkyrimShaderPropertyFlags2 & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = SkyrimShaderPropertyFlags2(temp);
}

void NifStream( SkyrimShaderPropertyFlags2 const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, SkyrimShaderPropertyFlags2 const & val ) {
	switch ( val ) {
		case SLSF2_ZBUFFER_WRITE: return out << "SLSF2_ZBuffer_Write";
		case SLSF2_LOD_LANDSCAPE: return out << "SLSF2_LOD_Landscape";
		case SLSF2_LOD_OBJECTS: return out << "SLSF2_LOD_Objects";
		case SLSF2_NO_FADE: return out << "SLSF2_No_Fade";
		case SLSF2_DOUBLE_SIDED: return out << "SLSF2_Double_Sided";
		case SLSF2_VERTEX_COLORS: return out << "SLSF2_Vertex_Colors";
		case SLSF2_GLOW_MAP: return out << "SLSF2_Glow_Map";
		case SLSF2_ASSUME_SHADOWMASK: return out << "SLSF2_Assume_Shadowmask";
		case SLSF2_PACKED_TANGENT: return out << "SLSF2_Packed_Tangent";
		case SLSF2_MULTI_INDEX_SNOW: return out << "SLSF2_Multi_Index_Snow";
		case SLSF2_VERTEX_LIGHTING: return out << "SLSF2_Vertex_Lighting";
		case SLSF2_UNIFORM_SCALE: return out << "SLSF2_Uniform_Scale";
		case SLSF2_FIT_SLOPE: return out << "SLSF2_Fit_Slope";
		case SLSF2_BILLBOARD: return out << "SLSF2_Billboard";
		case SLSF2_NO_LOD_LAND_BLEND: return out << "SLSF2_No_LOD_Land_Blend";
		case SLSF2_ENVMAP_LIGHT_FADE: return out << "SLSF2_EnvMap_Light_Fade";
		case SLSF2_WIREFRAME: return out << "SLSF2_Wireframe";
		case SLSF2_WEAPON_BLOOD: return out << "SLSF2_Weapon_Blood";
		case SLSF2_HIDE_ON_LOCAL_MAP: return out << "SLSF2_Hide_On_Local_Map";
		case SLSF2_PREMULT_ALPHA: return out << "SLSF2_Premult_Alpha";
		case SLSF2_CLOUD_LOD: return out << "SLSF2_Cloud_LOD";
		case SLSF2_ANISOTROPIC_LIGHTING: return out << "SLSF2_Anisotropic_Lighting";
		case SLSF2_NO_TRANSPARENCY_MULTISAMPLING: return out << "SLSF2_No_Transparency_Multisampling";
		case SLSF2_UNUSED01: return out << "SLSF2_Unused01";
		case SLSF2_MULTI_LAYER_PARALLAX: return out << "SLSF2_Multi_Layer_Parallax";
		case SLSF2_SOFT_LIGHTING: return out << "SLSF2_Soft_Lighting";
		case SLSF2_RIM_LIGHTING: return out << "SLSF2_Rim_Lighting";
		case SLSF2_BACK_LIGHTING: return out << "SLSF2_Back_Lighting";
		case SLSF2_UNUSED02: return out << "SLSF2_Unused02";
		case SLSF2_TREE_ANIM: return out << "SLSF2_Tree_Anim";
		case SLSF2_EFFECT_LIGHTING: return out << "SLSF2_Effect_Lighting";
		case SLSF2_HD_LOD_OBJECTS: return out << "SLSF2_HD_LOD_Objects";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}


//--BSSegmentFlags--//

void NifStream( BSSegmentFlags & val, istream& in, const NifInfo & info ) {
	unsigned int temp;
	NifStream( temp, in, info );
	val = BSSegmentFlags(temp);
}

void NifStream( BSSegmentFlags const & val, ostream& out, const NifInfo & info ) {
	NifStream( (unsigned int)(val), out, info );
}

ostream & operator<<( ostream & out, BSSegmentFlags const & val ) {
	switch ( val ) {
		case BSSEG_WATER: return out << "BSSEG_WATER";
		default: return out << "Invalid Value! - " << (unsigned int)(val);
	}
}

}
