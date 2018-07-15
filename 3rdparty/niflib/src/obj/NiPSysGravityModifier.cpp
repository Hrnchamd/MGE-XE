/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiPSysGravityModifier.h"
#include "../../include/obj/NiNode.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysGravityModifier::TYPE("NiPSysGravityModifier", &NiPSysModifier::TYPE );

NiPSysGravityModifier::NiPSysGravityModifier() : gravityObject(NULL), decay(0.0f), strength(0.0f), forceType((ForceType)0), turbulence(0.0f), turbulenceScale(1.0f), unknownByte((byte)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysGravityModifier::~NiPSysGravityModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysGravityModifier::GetType() const {
	return TYPE;
}

NiObject * NiPSysGravityModifier::Create() {
	return new NiPSysGravityModifier;
}

void NiPSysGravityModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiPSysModifier::Read( in, link_stack, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( gravityAxis, in, info );
	NifStream( decay, in, info );
	NifStream( strength, in, info );
	NifStream( forceType, in, info );
	NifStream( turbulence, in, info );
	NifStream( turbulenceScale, in, info );
	if ( ( info.version >= 0x14020007 ) && ( (info.userVersion >= 11) ) ) {
		NifStream( unknownByte, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysGravityModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::Write( out, link_map, missing_link_stack, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*gravityObject), out );
	} else {
		if ( gravityObject != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(gravityObject) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( gravityObject );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	NifStream( gravityAxis, out, info );
	NifStream( decay, out, info );
	NifStream( strength, out, info );
	NifStream( forceType, out, info );
	NifStream( turbulence, out, info );
	NifStream( turbulenceScale, out, info );
	if ( ( info.version >= 0x14020007 ) && ( (info.userVersion >= 11) ) ) {
		NifStream( unknownByte, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPSysGravityModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifier::asString();
	out << "  Gravity Object:  " << gravityObject << endl;
	out << "  Gravity Axis:  " << gravityAxis << endl;
	out << "  Decay:  " << decay << endl;
	out << "  Strength:  " << strength << endl;
	out << "  Force Type:  " << forceType << endl;
	out << "  Turbulence:  " << turbulence << endl;
	out << "  Turbulence Scale:  " << turbulenceScale << endl;
	out << "  Unknown Byte:  " << unknownByte << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysGravityModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::FixLinks( objects, link_stack, missing_link_stack, info );
	gravityObject = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysGravityModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysGravityModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifier::GetPtrs();
	if ( gravityObject != NULL )
		ptrs.push_back((NiObject *)(gravityObject));
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
