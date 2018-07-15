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
#include "../../include/obj/NiPSEmitterRotSpeedVarCtlr.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSEmitterRotSpeedVarCtlr::TYPE("NiPSEmitterRotSpeedVarCtlr", &NiPSEmitterRotSpeedCtlr::TYPE );

NiPSEmitterRotSpeedVarCtlr::NiPSEmitterRotSpeedVarCtlr() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSEmitterRotSpeedVarCtlr::~NiPSEmitterRotSpeedVarCtlr() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSEmitterRotSpeedVarCtlr::GetType() const {
	return TYPE;
}

NiObject * NiPSEmitterRotSpeedVarCtlr::Create() {
	return new NiPSEmitterRotSpeedVarCtlr;
}

void NiPSEmitterRotSpeedVarCtlr::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSEmitterRotSpeedCtlr::Read( in, link_stack, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSEmitterRotSpeedVarCtlr::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSEmitterRotSpeedCtlr::Write( out, link_map, missing_link_stack, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSEmitterRotSpeedVarCtlr::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSEmitterRotSpeedCtlr::asString();
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSEmitterRotSpeedVarCtlr::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSEmitterRotSpeedCtlr::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSEmitterRotSpeedVarCtlr::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSEmitterRotSpeedCtlr::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSEmitterRotSpeedVarCtlr::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSEmitterRotSpeedCtlr::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
