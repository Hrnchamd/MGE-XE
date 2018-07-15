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
#include "../../include/obj/NiPSysCylinderEmitter.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysCylinderEmitter::TYPE("NiPSysCylinderEmitter", &NiPSysVolumeEmitter::TYPE );

NiPSysCylinderEmitter::NiPSysCylinderEmitter() : radius(0.0f), height(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysCylinderEmitter::~NiPSysCylinderEmitter() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysCylinderEmitter::GetType() const {
	return TYPE;
}

NiObject * NiPSysCylinderEmitter::Create() {
	return new NiPSysCylinderEmitter;
}

void NiPSysCylinderEmitter::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysVolumeEmitter::Read( in, link_stack, info );
	NifStream( radius, in, info );
	NifStream( height, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysCylinderEmitter::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysVolumeEmitter::Write( out, link_map, missing_link_stack, info );
	NifStream( radius, out, info );
	NifStream( height, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPSysCylinderEmitter::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysVolumeEmitter::asString();
	out << "  Radius:  " << radius << endl;
	out << "  Height:  " << height << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysCylinderEmitter::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysVolumeEmitter::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysCylinderEmitter::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysVolumeEmitter::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysCylinderEmitter::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysVolumeEmitter::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
