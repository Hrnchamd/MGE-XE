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
#include "../../include/obj/NiBooleanExtraData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiBooleanExtraData::TYPE("NiBooleanExtraData", &NiExtraData::TYPE );

NiBooleanExtraData::NiBooleanExtraData() : booleanData((byte)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiBooleanExtraData::~NiBooleanExtraData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiBooleanExtraData::GetType() const {
	return TYPE;
}

NiObject * NiBooleanExtraData::Create() {
	return new NiBooleanExtraData;
}

void NiBooleanExtraData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::Read( in, link_stack, info );
	NifStream( booleanData, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBooleanExtraData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::Write( out, link_map, missing_link_stack, info );
	NifStream( booleanData, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiBooleanExtraData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiExtraData::asString();
	out << "  Boolean Data:  " << booleanData << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBooleanExtraData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBooleanExtraData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiExtraData::GetRefs();
	return refs;
}

std::list<NiObject *> NiBooleanExtraData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiExtraData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

bool NiBooleanExtraData::GetData() const {
	return (booleanData != 0);
}

void NiBooleanExtraData::SetData( bool n ) {
	booleanData = n;
}

//--END CUSTOM CODE--//
