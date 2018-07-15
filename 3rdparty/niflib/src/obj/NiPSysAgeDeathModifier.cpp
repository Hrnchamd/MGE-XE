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
#include "../../include/obj/NiPSysAgeDeathModifier.h"
#include "../../include/obj/NiPSysSpawnModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysAgeDeathModifier::TYPE("NiPSysAgeDeathModifier", &NiPSysModifier::TYPE );

NiPSysAgeDeathModifier::NiPSysAgeDeathModifier() : spawnOnDeath(false), spawnModifier(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysAgeDeathModifier::~NiPSysAgeDeathModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysAgeDeathModifier::GetType() const {
	return TYPE;
}

NiObject * NiPSysAgeDeathModifier::Create() {
	return new NiPSysAgeDeathModifier;
}

void NiPSysAgeDeathModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiPSysModifier::Read( in, link_stack, info );
	NifStream( spawnOnDeath, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysAgeDeathModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( spawnOnDeath, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*spawnModifier), out );
	} else {
		if ( spawnModifier != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(spawnModifier) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( spawnModifier );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPSysAgeDeathModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifier::asString();
	out << "  Spawn on Death:  " << spawnOnDeath << endl;
	out << "  Spawn Modifier:  " << spawnModifier << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysAgeDeathModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::FixLinks( objects, link_stack, missing_link_stack, info );
	spawnModifier = FixLink<NiPSysSpawnModifier>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysAgeDeathModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifier::GetRefs();
	if ( spawnModifier != NULL )
		refs.push_back(StaticCast<NiObject>(spawnModifier));
	return refs;
}

std::list<NiObject *> NiPSysAgeDeathModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
