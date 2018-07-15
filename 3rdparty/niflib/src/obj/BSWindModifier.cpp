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
#include "../../include/obj/BSWindModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSWindModifier::TYPE("BSWindModifier", &NiPSysModifier::TYPE );

BSWindModifier::BSWindModifier() : strength(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

BSWindModifier::~BSWindModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & BSWindModifier::GetType() const {
	return TYPE;
}

NiObject * BSWindModifier::Create() {
	return new BSWindModifier;
}

void BSWindModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::Read( in, link_stack, info );
	NifStream( strength, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void BSWindModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( strength, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string BSWindModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifier::asString();
	out << "  Strength:  " << strength << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void BSWindModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSWindModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifier::GetRefs();
	return refs;
}

std::list<NiObject *> BSWindModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
