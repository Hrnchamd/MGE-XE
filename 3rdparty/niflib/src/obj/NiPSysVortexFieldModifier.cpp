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
#include "../../include/obj/NiPSysVortexFieldModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysVortexFieldModifier::TYPE("NiPSysVortexFieldModifier", &NiPSysFieldModifier::TYPE );

NiPSysVortexFieldModifier::NiPSysVortexFieldModifier() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSysVortexFieldModifier::~NiPSysVortexFieldModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSysVortexFieldModifier::GetType() const {
	return TYPE;
}

NiObject * NiPSysVortexFieldModifier::Create() {
	return new NiPSysVortexFieldModifier;
}

void NiPSysVortexFieldModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::Read( in, link_stack, info );
	NifStream( direction, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysVortexFieldModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( direction, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSysVortexFieldModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysFieldModifier::asString();
	out << "  Direction:  " << direction << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysVortexFieldModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysVortexFieldModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysFieldModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysVortexFieldModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysFieldModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
