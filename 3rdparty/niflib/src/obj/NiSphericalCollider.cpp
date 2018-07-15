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
#include "../../include/obj/NiSphericalCollider.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiSphericalCollider::TYPE("NiSphericalCollider", &NiParticleModifier::TYPE );

NiSphericalCollider::NiSphericalCollider() : unknownFloat1(0.0f), unknownShort1((unsigned short)0), unknownFloat2(0.0f), unknownShort2((unsigned short)0), unknownFloat3(0.0f), unknownFloat4(0.0f), unknownFloat5(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiSphericalCollider::~NiSphericalCollider() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiSphericalCollider::GetType() const {
	return TYPE;
}

NiObject * NiSphericalCollider::Create() {
	return new NiSphericalCollider;
}

void NiSphericalCollider::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::Read( in, link_stack, info );
	NifStream( unknownFloat1, in, info );
	NifStream( unknownShort1, in, info );
	NifStream( unknownFloat2, in, info );
	if ( info.version <= 0x04020002 ) {
		NifStream( unknownShort2, in, info );
	};
	if ( info.version >= 0x04020100 ) {
		NifStream( unknownFloat3, in, info );
	};
	NifStream( unknownFloat4, in, info );
	NifStream( unknownFloat5, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiSphericalCollider::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( unknownFloat1, out, info );
	NifStream( unknownShort1, out, info );
	NifStream( unknownFloat2, out, info );
	if ( info.version <= 0x04020002 ) {
		NifStream( unknownShort2, out, info );
	};
	if ( info.version >= 0x04020100 ) {
		NifStream( unknownFloat3, out, info );
	};
	NifStream( unknownFloat4, out, info );
	NifStream( unknownFloat5, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiSphericalCollider::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiParticleModifier::asString();
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Unknown Short 1:  " << unknownShort1 << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Unknown Short 2:  " << unknownShort2 << endl;
	out << "  Unknown Float 3:  " << unknownFloat3 << endl;
	out << "  Unknown Float 4:  " << unknownFloat4 << endl;
	out << "  Unknown Float 5:  " << unknownFloat5 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiSphericalCollider::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiSphericalCollider::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiParticleModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiSphericalCollider::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiParticleModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
