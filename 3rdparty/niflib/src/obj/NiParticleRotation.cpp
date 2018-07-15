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
#include "../../include/obj/NiParticleRotation.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiParticleRotation::TYPE("NiParticleRotation", &NiParticleModifier::TYPE );

NiParticleRotation::NiParticleRotation() : randomInitialAxis_((byte)0), rotationSpeed_(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiParticleRotation::~NiParticleRotation() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiParticleRotation::GetType() const {
	return TYPE;
}

NiObject * NiParticleRotation::Create() {
	return new NiParticleRotation;
}

void NiParticleRotation::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::Read( in, link_stack, info );
	NifStream( randomInitialAxis_, in, info );
	NifStream( initialAxis_, in, info );
	NifStream( rotationSpeed_, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiParticleRotation::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( randomInitialAxis_, out, info );
	NifStream( initialAxis_, out, info );
	NifStream( rotationSpeed_, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiParticleRotation::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiParticleModifier::asString();
	out << "  Random Initial Axis?:  " << randomInitialAxis_ << endl;
	out << "  Initial Axis?:  " << initialAxis_ << endl;
	out << "  Rotation Speed?:  " << rotationSpeed_ << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiParticleRotation::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiParticleRotation::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiParticleModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiParticleRotation::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiParticleModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
