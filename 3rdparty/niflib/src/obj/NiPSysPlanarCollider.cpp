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
#include "../../include/obj/NiPSysPlanarCollider.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysPlanarCollider::TYPE("NiPSysPlanarCollider", &NiPSysCollider::TYPE );

NiPSysPlanarCollider::NiPSysPlanarCollider() : width(0.0f), height(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysPlanarCollider::~NiPSysPlanarCollider() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysPlanarCollider::GetType() const {
	return TYPE;
}

NiObject * NiPSysPlanarCollider::Create() {
	return new NiPSysPlanarCollider;
}

void NiPSysPlanarCollider::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysCollider::Read( in, link_stack, info );
	NifStream( width, in, info );
	NifStream( height, in, info );
	NifStream( xAxis, in, info );
	NifStream( yAxis, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysPlanarCollider::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysCollider::Write( out, link_map, missing_link_stack, info );
	NifStream( width, out, info );
	NifStream( height, out, info );
	NifStream( xAxis, out, info );
	NifStream( yAxis, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPSysPlanarCollider::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysCollider::asString();
	out << "  Width:  " << width << endl;
	out << "  Height:  " << height << endl;
	out << "  X Axis:  " << xAxis << endl;
	out << "  Y Axis:  " << yAxis << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysPlanarCollider::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysCollider::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysPlanarCollider::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysCollider::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysPlanarCollider::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysCollider::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
