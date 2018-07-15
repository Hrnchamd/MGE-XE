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
#include "../../include/obj/BSMultiBoundAABB.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSMultiBoundAABB::TYPE("BSMultiBoundAABB", &BSMultiBoundData::TYPE );

BSMultiBoundAABB::BSMultiBoundAABB() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSMultiBoundAABB::~BSMultiBoundAABB() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSMultiBoundAABB::GetType() const {
	return TYPE;
}

NiObject * BSMultiBoundAABB::Create() {
	return new BSMultiBoundAABB;
}

void BSMultiBoundAABB::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSMultiBoundData::Read( in, link_stack, info );
	NifStream( position, in, info );
	NifStream( extent, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSMultiBoundAABB::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSMultiBoundData::Write( out, link_map, missing_link_stack, info );
	NifStream( position, out, info );
	NifStream( extent, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSMultiBoundAABB::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << BSMultiBoundData::asString();
	out << "  Position:  " << position << endl;
	out << "  Extent:  " << extent << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSMultiBoundAABB::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSMultiBoundData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSMultiBoundAABB::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = BSMultiBoundData::GetRefs();
	return refs;
}

std::list<NiObject *> BSMultiBoundAABB::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = BSMultiBoundData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
