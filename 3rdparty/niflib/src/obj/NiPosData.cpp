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
#include "../../include/obj/NiPosData.h"
#include "../../include/gen/KeyGroup.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPosData::TYPE("NiPosData", &NiObject::TYPE );

NiPosData::NiPosData() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPosData::~NiPosData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPosData::GetType() const {
	return TYPE;
}

NiObject * NiPosData::Create() {
	return new NiPosData;
}

void NiPosData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( data.numKeys, in, info );
	if ( (data.numKeys != 0) ) {
		NifStream( data.interpolation, in, info );
	};
	data.keys.resize(data.numKeys);
	for (unsigned int i1 = 0; i1 < data.keys.size(); i1++) {
		NifStream( data.keys[i1], in, info, data.interpolation );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPosData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	data.numKeys = (unsigned int)(data.keys.size());
	NifStream( data.numKeys, out, info );
	if ( (data.numKeys != 0) ) {
		NifStream( data.interpolation, out, info );
	};
	for (unsigned int i1 = 0; i1 < data.keys.size(); i1++) {
		NifStream( data.keys[i1], out, info, data.interpolation );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPosData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	data.numKeys = (unsigned int)(data.keys.size());
	out << "  Num Keys:  " << data.numKeys << endl;
	if ( (data.numKeys != 0) ) {
		out << "    Interpolation:  " << data.interpolation << endl;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < data.keys.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Keys[" << i1 << "]:  " << data.keys[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPosData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPosData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiPosData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

KeyType NiPosData::GetKeyType() const {
	return data.interpolation;
}

void NiPosData::SetKeyType( KeyType t ) {
	data.interpolation = t;
}

vector< Key<Vector3> > NiPosData::GetKeys() const {
	return data.keys;
}

void NiPosData::SetKeys( vector< Key<Vector3> > const & keys ) {
	data.keys = keys;
}

void NiPosData::NormalizeKeys( float phase, float frequency ) {
	NormalizeKeyVector( this->data.keys, phase, frequency );
}

//--END CUSTOM CODE--//
