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
#include "../../include/obj/NiPSysSphereEmitter.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysSphereEmitter::TYPE("NiPSysSphereEmitter", &NiPSysVolumeEmitter::TYPE );

NiPSysSphereEmitter::NiPSysSphereEmitter() : radius(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysSphereEmitter::~NiPSysSphereEmitter() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysSphereEmitter::GetType() const {
	return TYPE;
}

NiObject * NiPSysSphereEmitter::Create() {
	return new NiPSysSphereEmitter;
}

void NiPSysSphereEmitter::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysVolumeEmitter::Read( in, link_stack, info );
	NifStream( radius, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysSphereEmitter::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysVolumeEmitter::Write( out, link_map, missing_link_stack, info );
	NifStream( radius, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPSysSphereEmitter::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysVolumeEmitter::asString();
	out << "  Radius:  " << radius << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysSphereEmitter::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysVolumeEmitter::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysSphereEmitter::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysVolumeEmitter::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysSphereEmitter::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysVolumeEmitter::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
