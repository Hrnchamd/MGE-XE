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
#include "../../include/obj/NiParticleColorModifier.h"
#include "../../include/obj/NiColorData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiParticleColorModifier::TYPE("NiParticleColorModifier", &NiParticleModifier::TYPE );

NiParticleColorModifier::NiParticleColorModifier() : colorData(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiParticleColorModifier::~NiParticleColorModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiParticleColorModifier::GetType() const {
	return TYPE;
}

NiObject * NiParticleColorModifier::Create() {
	return new NiParticleColorModifier;
}

void NiParticleColorModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiParticleModifier::Read( in, link_stack, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiParticleColorModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::Write( out, link_map, missing_link_stack, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*colorData), out );
	} else {
		if ( colorData != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(colorData) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( colorData );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiParticleColorModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiParticleModifier::asString();
	out << "  Color Data:  " << colorData << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiParticleColorModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::FixLinks( objects, link_stack, missing_link_stack, info );
	colorData = FixLink<NiColorData>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiParticleColorModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiParticleModifier::GetRefs();
	if ( colorData != NULL )
		refs.push_back(StaticCast<NiObject>(colorData));
	return refs;
}

std::list<NiObject *> NiParticleColorModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiParticleModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
