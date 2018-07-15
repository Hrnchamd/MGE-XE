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
#include "../../include/obj/NiPSCylinderEmitter.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSCylinderEmitter::TYPE("NiPSCylinderEmitter", &NiPSSphereEmitter::TYPE );

NiPSCylinderEmitter::NiPSCylinderEmitter() : unknown23(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSCylinderEmitter::~NiPSCylinderEmitter() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSCylinderEmitter::GetType() const {
	return TYPE;
}

NiObject * NiPSCylinderEmitter::Create() {
	return new NiPSCylinderEmitter;
}

void NiPSCylinderEmitter::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSSphereEmitter::Read( in, link_stack, info );
	NifStream( unknown23, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSCylinderEmitter::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSSphereEmitter::Write( out, link_map, missing_link_stack, info );
	NifStream( unknown23, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSCylinderEmitter::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSSphereEmitter::asString();
	out << "  Unknown 23:  " << unknown23 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSCylinderEmitter::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSSphereEmitter::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSCylinderEmitter::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSSphereEmitter::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSCylinderEmitter::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSSphereEmitter::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
