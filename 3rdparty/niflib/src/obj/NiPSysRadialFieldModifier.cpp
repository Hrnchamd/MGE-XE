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
#include "../../include/obj/NiPSysRadialFieldModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysRadialFieldModifier::TYPE("NiPSysRadialFieldModifier", &NiPSysFieldModifier::TYPE );

NiPSysRadialFieldModifier::NiPSysRadialFieldModifier() : radialType((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSysRadialFieldModifier::~NiPSysRadialFieldModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSysRadialFieldModifier::GetType() const {
	return TYPE;
}

NiObject * NiPSysRadialFieldModifier::Create() {
	return new NiPSysRadialFieldModifier;
}

void NiPSysRadialFieldModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::Read( in, link_stack, info );
	NifStream( radialType, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysRadialFieldModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( radialType, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSysRadialFieldModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysFieldModifier::asString();
	out << "  Radial Type:  " << radialType << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysRadialFieldModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysRadialFieldModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysFieldModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysRadialFieldModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysFieldModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
