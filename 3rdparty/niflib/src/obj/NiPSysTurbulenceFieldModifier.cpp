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
#include "../../include/obj/NiPSysTurbulenceFieldModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysTurbulenceFieldModifier::TYPE("NiPSysTurbulenceFieldModifier", &NiPSysFieldModifier::TYPE );

NiPSysTurbulenceFieldModifier::NiPSysTurbulenceFieldModifier() : frequency(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSysTurbulenceFieldModifier::~NiPSysTurbulenceFieldModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSysTurbulenceFieldModifier::GetType() const {
	return TYPE;
}

NiObject * NiPSysTurbulenceFieldModifier::Create() {
	return new NiPSysTurbulenceFieldModifier;
}

void NiPSysTurbulenceFieldModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::Read( in, link_stack, info );
	NifStream( frequency, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysTurbulenceFieldModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( frequency, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSysTurbulenceFieldModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysFieldModifier::asString();
	out << "  Frequency:  " << frequency << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysTurbulenceFieldModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysTurbulenceFieldModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysFieldModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysTurbulenceFieldModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysFieldModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
