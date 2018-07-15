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
#include "../../include/obj/NiVertWeightsExtraData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiVertWeightsExtraData::TYPE("NiVertWeightsExtraData", &NiExtraData::TYPE );

NiVertWeightsExtraData::NiVertWeightsExtraData() : numBytes((unsigned int)0), numVertices((unsigned short)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiVertWeightsExtraData::~NiVertWeightsExtraData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiVertWeightsExtraData::GetType() const {
	return TYPE;
}

NiObject * NiVertWeightsExtraData::Create() {
	return new NiVertWeightsExtraData;
}

void NiVertWeightsExtraData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::Read( in, link_stack, info );
	NifStream( numBytes, in, info );
	NifStream( numVertices, in, info );
	weight.resize(numVertices);
	for (unsigned int i1 = 0; i1 < weight.size(); i1++) {
		NifStream( weight[i1], in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiVertWeightsExtraData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::Write( out, link_map, missing_link_stack, info );
	numVertices = (unsigned short)(weight.size());
	NifStream( numBytes, out, info );
	NifStream( numVertices, out, info );
	for (unsigned int i1 = 0; i1 < weight.size(); i1++) {
		NifStream( weight[i1], out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiVertWeightsExtraData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiExtraData::asString();
	numVertices = (unsigned short)(weight.size());
	out << "  Num Bytes:  " << numBytes << endl;
	out << "  Num Vertices:  " << numVertices << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < weight.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Weight[" << i1 << "]:  " << weight[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiVertWeightsExtraData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiVertWeightsExtraData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiExtraData::GetRefs();
	return refs;
}

std::list<NiObject *> NiVertWeightsExtraData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiExtraData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

vector<float> NiVertWeightsExtraData::GetData() const {
	return weight;
}
	
void NiVertWeightsExtraData::SetData( const vector<float> & n ) {
	numVertices = (unsigned int)(n.size());
	numBytes = numVertices + 2;
	weight = n;
}

//--END CUSTOM CODE--//
