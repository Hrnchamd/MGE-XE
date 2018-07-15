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
#include "../../include/obj/BSMultiBoundSphere.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSMultiBoundSphere::TYPE("BSMultiBoundSphere", &BSMultiBoundData::TYPE );

BSMultiBoundSphere::BSMultiBoundSphere() : unknownInt1((int)0), unknownInt2((int)0), unknownInt3((int)0), radius(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSMultiBoundSphere::~BSMultiBoundSphere() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSMultiBoundSphere::GetType() const {
	return TYPE;
}

NiObject * BSMultiBoundSphere::Create() {
	return new BSMultiBoundSphere;
}

void BSMultiBoundSphere::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSMultiBoundData::Read( in, link_stack, info );
	NifStream( unknownInt1, in, info );
	NifStream( unknownInt2, in, info );
	NifStream( unknownInt3, in, info );
	NifStream( radius, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSMultiBoundSphere::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSMultiBoundData::Write( out, link_map, missing_link_stack, info );
	NifStream( unknownInt1, out, info );
	NifStream( unknownInt2, out, info );
	NifStream( unknownInt3, out, info );
	NifStream( radius, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSMultiBoundSphere::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << BSMultiBoundData::asString();
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Unknown Int 3:  " << unknownInt3 << endl;
	out << "  Radius:  " << radius << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSMultiBoundSphere::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSMultiBoundData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSMultiBoundSphere::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = BSMultiBoundData::GetRefs();
	return refs;
}

std::list<NiObject *> BSMultiBoundSphere::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = BSMultiBoundData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
