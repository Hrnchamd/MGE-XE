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
#include "../../include/obj/NiPSEmitterDeclinationVarCtlr.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSEmitterDeclinationVarCtlr::TYPE("NiPSEmitterDeclinationVarCtlr", &NiPSEmitterDeclinationCtlr::TYPE );

NiPSEmitterDeclinationVarCtlr::NiPSEmitterDeclinationVarCtlr() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSEmitterDeclinationVarCtlr::~NiPSEmitterDeclinationVarCtlr() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSEmitterDeclinationVarCtlr::GetType() const {
	return TYPE;
}

NiObject * NiPSEmitterDeclinationVarCtlr::Create() {
	return new NiPSEmitterDeclinationVarCtlr;
}

void NiPSEmitterDeclinationVarCtlr::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSEmitterDeclinationCtlr::Read( in, link_stack, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSEmitterDeclinationVarCtlr::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSEmitterDeclinationCtlr::Write( out, link_map, missing_link_stack, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSEmitterDeclinationVarCtlr::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSEmitterDeclinationCtlr::asString();
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSEmitterDeclinationVarCtlr::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSEmitterDeclinationCtlr::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSEmitterDeclinationVarCtlr::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSEmitterDeclinationCtlr::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSEmitterDeclinationVarCtlr::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSEmitterDeclinationCtlr::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
