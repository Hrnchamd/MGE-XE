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
#include "../../include/obj/NiPSysBoxEmitter.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysBoxEmitter::TYPE("NiPSysBoxEmitter", &NiPSysVolumeEmitter::TYPE );

NiPSysBoxEmitter::NiPSysBoxEmitter() : width(0.0f), height(0.0f), depth(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysBoxEmitter::~NiPSysBoxEmitter() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysBoxEmitter::GetType() const {
	return TYPE;
}

NiObject * NiPSysBoxEmitter::Create() {
	return new NiPSysBoxEmitter;
}

void NiPSysBoxEmitter::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysVolumeEmitter::Read( in, link_stack, info );
	NifStream( width, in, info );
	NifStream( height, in, info );
	NifStream( depth, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysBoxEmitter::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysVolumeEmitter::Write( out, link_map, missing_link_stack, info );
	NifStream( width, out, info );
	NifStream( height, out, info );
	NifStream( depth, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPSysBoxEmitter::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysVolumeEmitter::asString();
	out << "  Width:  " << width << endl;
	out << "  Height:  " << height << endl;
	out << "  Depth:  " << depth << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysBoxEmitter::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysVolumeEmitter::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysBoxEmitter::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysVolumeEmitter::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysBoxEmitter::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysVolumeEmitter::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
