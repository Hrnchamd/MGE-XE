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
#include "../../include/obj/NiPSysEmitterPlanarAngleVarCtlr.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysEmitterPlanarAngleVarCtlr::TYPE("NiPSysEmitterPlanarAngleVarCtlr", &NiPSysModifierFloatCtlr::TYPE );

NiPSysEmitterPlanarAngleVarCtlr::NiPSysEmitterPlanarAngleVarCtlr() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSysEmitterPlanarAngleVarCtlr::~NiPSysEmitterPlanarAngleVarCtlr() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSysEmitterPlanarAngleVarCtlr::GetType() const {
	return TYPE;
}

NiObject * NiPSysEmitterPlanarAngleVarCtlr::Create() {
	return new NiPSysEmitterPlanarAngleVarCtlr;
}

void NiPSysEmitterPlanarAngleVarCtlr::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifierFloatCtlr::Read( in, link_stack, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysEmitterPlanarAngleVarCtlr::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifierFloatCtlr::Write( out, link_map, missing_link_stack, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSysEmitterPlanarAngleVarCtlr::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifierFloatCtlr::asString();
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysEmitterPlanarAngleVarCtlr::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifierFloatCtlr::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysEmitterPlanarAngleVarCtlr::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifierFloatCtlr::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysEmitterPlanarAngleVarCtlr::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifierFloatCtlr::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
