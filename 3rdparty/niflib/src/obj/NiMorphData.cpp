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
#include "../../include/obj/NiMorphData.h"
#include "../../include/gen/Morph.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiMorphData::TYPE("NiMorphData", &NiObject::TYPE );

NiMorphData::NiMorphData() : numMorphs((unsigned int)0), numVertices((unsigned int)0), relativeTargets((byte)1) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiMorphData::~NiMorphData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiMorphData::GetType() const {
	return TYPE;
}

NiObject * NiMorphData::Create() {
	return new NiMorphData;
}

void NiMorphData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( numMorphs, in, info );
	NifStream( numVertices, in, info );
	NifStream( relativeTargets, in, info );
	morphs.resize(numMorphs);
	for (unsigned int i1 = 0; i1 < morphs.size(); i1++) {
		if ( info.version >= 0x0A01006A ) {
			NifStream( morphs[i1].frameName, in, info );
		};
		if ( info.version <= 0x0A010000 ) {
			NifStream( morphs[i1].numKeys, in, info );
			NifStream( morphs[i1].interpolation, in, info );
			morphs[i1].keys.resize(morphs[i1].numKeys);
			for (unsigned int i3 = 0; i3 < morphs[i1].keys.size(); i3++) {
				NifStream( morphs[i1].keys[i3], in, info, morphs[i1].interpolation );
			};
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A020000 ) ) {
			NifStream( morphs[i1].unknownInt, in, info );
		};
		if ( ( info.version >= 0x14000004 ) && ( info.version <= 0x14000005 ) && ( info.userVersion == 0 ) ) {
			NifStream( morphs[i1].unknownInt, in, info );
		};
		morphs[i1].vectors.resize(numVertices);
		for (unsigned int i2 = 0; i2 < morphs[i1].vectors.size(); i2++) {
			NifStream( morphs[i1].vectors[i2], in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiMorphData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	numMorphs = (unsigned int)(morphs.size());
	NifStream( numMorphs, out, info );
	NifStream( numVertices, out, info );
	NifStream( relativeTargets, out, info );
	for (unsigned int i1 = 0; i1 < morphs.size(); i1++) {
		morphs[i1].numKeys = (unsigned int)(morphs[i1].keys.size());
		if ( info.version >= 0x0A01006A ) {
			NifStream( morphs[i1].frameName, out, info );
		};
		if ( info.version <= 0x0A010000 ) {
			NifStream( morphs[i1].numKeys, out, info );
			NifStream( morphs[i1].interpolation, out, info );
			for (unsigned int i3 = 0; i3 < morphs[i1].keys.size(); i3++) {
				NifStream( morphs[i1].keys[i3], out, info, morphs[i1].interpolation );
			};
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A020000 ) ) {
			NifStream( morphs[i1].unknownInt, out, info );
		};
		if ( ( info.version >= 0x14000004 ) && ( info.version <= 0x14000005 ) && ( info.userVersion == 0 ) ) {
			NifStream( morphs[i1].unknownInt, out, info );
		};
		for (unsigned int i2 = 0; i2 < morphs[i1].vectors.size(); i2++) {
			NifStream( morphs[i1].vectors[i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiMorphData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numMorphs = (unsigned int)(morphs.size());
	out << "  Num Morphs:  " << numMorphs << endl;
	out << "  Num Vertices:  " << numVertices << endl;
	out << "  Relative Targets:  " << relativeTargets << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < morphs.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		morphs[i1].numKeys = (unsigned int)(morphs[i1].keys.size());
		out << "    Frame Name:  " << morphs[i1].frameName << endl;
		out << "    Num Keys:  " << morphs[i1].numKeys << endl;
		out << "    Interpolation:  " << morphs[i1].interpolation << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < morphs[i1].keys.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Keys[" << i2 << "]:  " << morphs[i1].keys[i2] << endl;
			array_output_count++;
		};
		out << "    Unknown Int:  " << morphs[i1].unknownInt << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < morphs[i1].vectors.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Vectors[" << i2 << "]:  " << morphs[i1].vectors[i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiMorphData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiMorphData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiMorphData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

void NiMorphData::NormalizeKeys( float phase, float frequency ) {
	for ( size_t i = 0; i < morphs.size(); ++i ) {
		NormalizeKeyVector( morphs[i].keys, phase, frequency );
	}
}

int NiMorphData::GetVertexCount() const {
	
	return numVertices;
}

void NiMorphData::SetVertexCount( int n ) {
	numVertices = n;
	for ( unsigned int i = 0; i < morphs.size(); ++i ) {
		morphs[i].vectors.resize( n );
	}
}

int NiMorphData::GetMorphCount() const {
	return int(morphs.size());
}

void NiMorphData::SetMorphCount( int n ) {
	unsigned int old_size = (unsigned int)(morphs.size());
	morphs.resize( n );

	//Make sure any new vertex groups are the right size
	for (unsigned int i = old_size; i < morphs.size(); ++i ) {
		morphs[i].vectors.resize( numVertices );
	}
}

KeyType NiMorphData::GetMorphKeyType( int n ) const {
	return morphs[n].interpolation;
}

void NiMorphData::SetMorphKeyType( int n, KeyType t ) {
	morphs[n].interpolation = t;
}

vector< Key<float> > NiMorphData::GetMorphKeys( int n ) const {
	return morphs[n].keys;
}

void NiMorphData::SetMorphKeys( int n, vector< Key<float> > const & keys ) {
	morphs[n].keys = keys;
}

vector<Vector3> NiMorphData::GetMorphVerts( int n) const {
	return morphs[n].vectors;
}

void NiMorphData::SetMorphVerts( int n, const vector<Vector3> & in ) {
	// Make sure the size of the incoming vector equal vertCount
	if ( in.size() != numVertices )
		throw runtime_error("Input array size must equal Vertex Count.  Call SetVertexCount() to resize.");

	//It's the right size, so go ahead and set it
	morphs[n].vectors = in;
}

string NiMorphData::GetFrameName( int n ) const
{
	return morphs[n].frameName;
}

void NiMorphData::SetFrameName( int n, string const & key ) {
	morphs[n].frameName = key;
}

//--END CUSTOM CODE--//
