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
#include "../../include/obj/NiPSysEmitterLifeSpanCtlr.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysEmitterLifeSpanCtlr::TYPE("NiPSysEmitterLifeSpanCtlr", &NiPSysModifierFloatCtlr::TYPE );

NiPSysEmitterLifeSpanCtlr::NiPSysEmitterLifeSpanCtlr() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysEmitterLifeSpanCtlr::~NiPSysEmitterLifeSpanCtlr() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysEmitterLifeSpanCtlr::GetType() const {
	return TYPE;
}

NiObject * NiPSysEmitterLifeSpanCtlr::Create() {
	return new NiPSysEmitterLifeSpanCtlr;
}

void NiPSysEmitterLifeSpanCtlr::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifierFloatCtlr::Read( in, link_stack, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysEmitterLifeSpanCtlr::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifierFloatCtlr::Write( out, link_map, missing_link_stack, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPSysEmitterLifeSpanCtlr::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifierFloatCtlr::asString();
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysEmitterLifeSpanCtlr::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifierFloatCtlr::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysEmitterLifeSpanCtlr::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifierFloatCtlr::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysEmitterLifeSpanCtlr::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifierFloatCtlr::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
