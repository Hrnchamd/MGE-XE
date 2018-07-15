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
#include "../../include/obj/NiPSEmitterPlanarAngleVarCtlr.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSEmitterPlanarAngleVarCtlr::TYPE("NiPSEmitterPlanarAngleVarCtlr", &NiPSEmitterPlanarAngleCtlr::TYPE );

NiPSEmitterPlanarAngleVarCtlr::NiPSEmitterPlanarAngleVarCtlr() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSEmitterPlanarAngleVarCtlr::~NiPSEmitterPlanarAngleVarCtlr() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSEmitterPlanarAngleVarCtlr::GetType() const {
	return TYPE;
}

NiObject * NiPSEmitterPlanarAngleVarCtlr::Create() {
	return new NiPSEmitterPlanarAngleVarCtlr;
}

void NiPSEmitterPlanarAngleVarCtlr::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSEmitterPlanarAngleCtlr::Read( in, link_stack, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSEmitterPlanarAngleVarCtlr::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSEmitterPlanarAngleCtlr::Write( out, link_map, missing_link_stack, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSEmitterPlanarAngleVarCtlr::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSEmitterPlanarAngleCtlr::asString();
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSEmitterPlanarAngleVarCtlr::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSEmitterPlanarAngleCtlr::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSEmitterPlanarAngleVarCtlr::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSEmitterPlanarAngleCtlr::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSEmitterPlanarAngleVarCtlr::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSEmitterPlanarAngleCtlr::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
