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
#include "../../include/obj/NiTextKeyExtraData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiTextKeyExtraData::TYPE("NiTextKeyExtraData", &NiExtraData::TYPE );

NiTextKeyExtraData::NiTextKeyExtraData() : unknownInt1((unsigned int)0), numTextKeys((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiTextKeyExtraData::~NiTextKeyExtraData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiTextKeyExtraData::GetType() const {
	return TYPE;
}

NiObject * NiTextKeyExtraData::Create() {
	return new NiTextKeyExtraData;
}

void NiTextKeyExtraData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::Read( in, link_stack, info );
	if ( info.version <= 0x04020200 ) {
		NifStream( unknownInt1, in, info );
	};
	NifStream( numTextKeys, in, info );
	textKeys.resize(numTextKeys);
	for (unsigned int i1 = 0; i1 < textKeys.size(); i1++) {
		NifStream( textKeys[i1], in, info, 1 );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTextKeyExtraData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::Write( out, link_map, missing_link_stack, info );
	numTextKeys = (unsigned int)(textKeys.size());
	if ( info.version <= 0x04020200 ) {
		NifStream( unknownInt1, out, info );
	};
	NifStream( numTextKeys, out, info );
	for (unsigned int i1 = 0; i1 < textKeys.size(); i1++) {
		NifStream( textKeys[i1], out, info, 1 );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiTextKeyExtraData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiExtraData::asString();
	numTextKeys = (unsigned int)(textKeys.size());
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Num Text Keys:  " << numTextKeys << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < textKeys.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Text Keys[" << i1 << "]:  " << textKeys[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTextKeyExtraData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiTextKeyExtraData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiExtraData::GetRefs();
	return refs;
}

std::list<NiObject *> NiTextKeyExtraData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiExtraData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

vector< Key<string> > NiTextKeyExtraData::GetKeys() const {
	vector< Key<string> > value;
	for (vector< Key<IndexString> >::const_iterator itr = textKeys.begin(); itr != textKeys.end(); ++itr) {
		Key<string> key;
		key.time = (*itr).time;
		key.data = (*itr).data;
		key.tension = (*itr).tension;
		key.bias = (*itr).bias;
		key.continuity = (*itr).continuity;
		value.push_back(key);
	}
	return value;
}

void NiTextKeyExtraData::SetKeys( vector< Key<string> > const & keys ) {
	vector< Key<string> > value;
	textKeys.clear();
	for (vector< Key<string> >::const_iterator itr = keys.begin(); itr != keys.end(); ++itr) {
		Key<IndexString> key;
		key.time = (*itr).time;
		key.data = (*itr).data;
		key.tension = (*itr).tension;
		key.bias = (*itr).bias;
		key.continuity = (*itr).continuity;
		textKeys.push_back(key);
	}
}

//--END CUSTOM CODE--//
