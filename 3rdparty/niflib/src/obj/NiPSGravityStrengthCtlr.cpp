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
#include "../../include/obj/NiPSGravityStrengthCtlr.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSGravityStrengthCtlr::TYPE("NiPSGravityStrengthCtlr", &NiTimeController::TYPE );

NiPSGravityStrengthCtlr::NiPSGravityStrengthCtlr() : unknown2((int)0), unknown3((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSGravityStrengthCtlr::~NiPSGravityStrengthCtlr() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSGravityStrengthCtlr::GetType() const {
	return TYPE;
}

NiObject * NiPSGravityStrengthCtlr::Create() {
	return new NiPSGravityStrengthCtlr;
}

void NiPSGravityStrengthCtlr::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiTimeController::Read( in, link_stack, info );
	NifStream( unknown2, in, info );
	NifStream( unknown3, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSGravityStrengthCtlr::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiTimeController::Write( out, link_map, missing_link_stack, info );
	NifStream( unknown2, out, info );
	NifStream( unknown3, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSGravityStrengthCtlr::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiTimeController::asString();
	out << "  Unknown 2:  " << unknown2 << endl;
	out << "  Unknown 3:  " << unknown3 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSGravityStrengthCtlr::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiTimeController::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSGravityStrengthCtlr::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiTimeController::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSGravityStrengthCtlr::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiTimeController::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
