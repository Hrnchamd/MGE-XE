/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include "../../include/niflib.h"
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiObject::TYPE("NiObject", &RefObject::TYPE );

NiObject::NiObject() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiObject::~NiObject() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiObject::GetType() const {
	return TYPE;
}

NiObject * NiObject::Create() {
	return new NiObject;
}

void NiObject::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//


	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiObject::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//


	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiObject::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiObject::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//


	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiObject::GetRefs() const {
	list<Ref<NiObject> > refs;
	return refs;
}

std::list<NiObject *> NiObject::GetPtrs() const {
	list<NiObject *> ptrs;
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

NiObjectRef NiObject::Clone( unsigned int version, unsigned int user_version ) {
	//Create a string stream to temporarily hold the state-save of this object
	stringstream tmp;

	//Create a new object of the same type
	NiObjectRef clone = ObjectRegistry::CreateObject( this->GetType().GetTypeName() );

	//Dummy map
	map<NiObjectRef,unsigned int> link_map;

	//Write this object's data to the stream
	NifInfo info( version, user_version );
	list<NiObject *> missing_link_stack;
	this->Write( tmp, link_map, missing_link_stack, info );

	//Dummy stack
	list<unsigned int> link_stack;

	//Read the data back from the stream into the clone
	clone->Read( tmp, link_stack, info );

	//We don't fix the links, causing the clone to be a copy of all
	//data but have none of the linkage of the original.

	//return new object
	return clone;
};

//--END CUSTOM CODE--//
