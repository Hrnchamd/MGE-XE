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
#include "../../include/obj/BSMultiBoundOBB.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSMultiBoundOBB::TYPE("BSMultiBoundOBB", &BSMultiBoundData::TYPE );

BSMultiBoundOBB::BSMultiBoundOBB() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSMultiBoundOBB::~BSMultiBoundOBB() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSMultiBoundOBB::GetType() const {
	return TYPE;
}

NiObject * BSMultiBoundOBB::Create() {
	return new BSMultiBoundOBB;
}

void BSMultiBoundOBB::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSMultiBoundData::Read( in, link_stack, info );
	NifStream( center, in, info );
	NifStream( size, in, info );
	NifStream( rotation, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSMultiBoundOBB::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSMultiBoundData::Write( out, link_map, missing_link_stack, info );
	NifStream( center, out, info );
	NifStream( size, out, info );
	NifStream( rotation, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSMultiBoundOBB::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << BSMultiBoundData::asString();
	out << "  Center:  " << center << endl;
	out << "  Size:  " << size << endl;
	out << "  Rotation:  " << rotation << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSMultiBoundOBB::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSMultiBoundData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSMultiBoundOBB::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = BSMultiBoundData::GetRefs();
	return refs;
}

std::list<NiObject *> BSMultiBoundOBB::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = BSMultiBoundData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
