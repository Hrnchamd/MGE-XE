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
#include "../../include/obj/NiParticleGrowFade.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiParticleGrowFade::TYPE("NiParticleGrowFade", &NiParticleModifier::TYPE );

NiParticleGrowFade::NiParticleGrowFade() : grow(0.0f), fade(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiParticleGrowFade::~NiParticleGrowFade() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiParticleGrowFade::GetType() const {
	return TYPE;
}

NiObject * NiParticleGrowFade::Create() {
	return new NiParticleGrowFade;
}

void NiParticleGrowFade::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::Read( in, link_stack, info );
	NifStream( grow, in, info );
	NifStream( fade, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiParticleGrowFade::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( grow, out, info );
	NifStream( fade, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiParticleGrowFade::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiParticleModifier::asString();
	out << "  Grow:  " << grow << endl;
	out << "  Fade:  " << fade << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiParticleGrowFade::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiParticleGrowFade::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiParticleModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiParticleGrowFade::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiParticleModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
