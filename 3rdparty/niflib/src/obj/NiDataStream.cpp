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
#include "../../include/obj/NiDataStream.h"
#include "../../include/gen/Region.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiDataStream::TYPE("NiDataStream", &NiObject::TYPE );

NiDataStream::NiDataStream() : usage((DataStreamUsage)0), access((DataStreamAccess)0), numBytes((unsigned int)0), cloningBehavior((CloningBehavior)CLONING_SHARE), numRegions((unsigned int)0), numComponents((unsigned int)0), streamable(1) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiDataStream::~NiDataStream() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiDataStream::GetType() const {
	return TYPE;
}

NiObject * NiDataStream::Create() {
	return new NiDataStream;
}

void NiDataStream::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( usage, in, info );
	NifStream( access, in, info );
	NifStream( numBytes, in, info );
	NifStream( cloningBehavior, in, info );
	NifStream( numRegions, in, info );
	regions.resize(numRegions);
	for (unsigned int i1 = 0; i1 < regions.size(); i1++) {
		NifStream( regions[i1].startIndex, in, info );
		NifStream( regions[i1].numIndices, in, info );
	};
	NifStream( numComponents, in, info );
	componentFormats.resize(numComponents);
	for (unsigned int i1 = 0; i1 < componentFormats.size(); i1++) {
		NifStream( componentFormats[i1], in, info );
	};
	data.resize(numBytes);
	for (unsigned int i1 = 0; i1 < data.size(); i1++) {
		NifStream( data[i1], in, info );
	};
	NifStream( streamable, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiDataStream::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	numComponents = (unsigned int)(componentFormats.size());
	numRegions = (unsigned int)(regions.size());
	numBytes = (unsigned int)(data.size());
	NifStream( usage, out, info );
	NifStream( access, out, info );
	NifStream( numBytes, out, info );
	NifStream( cloningBehavior, out, info );
	NifStream( numRegions, out, info );
	for (unsigned int i1 = 0; i1 < regions.size(); i1++) {
		NifStream( regions[i1].startIndex, out, info );
		NifStream( regions[i1].numIndices, out, info );
	};
	NifStream( numComponents, out, info );
	for (unsigned int i1 = 0; i1 < componentFormats.size(); i1++) {
		NifStream( componentFormats[i1], out, info );
	};
	for (unsigned int i1 = 0; i1 < data.size(); i1++) {
		NifStream( data[i1], out, info );
	};
	NifStream( streamable, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiDataStream::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numComponents = (unsigned int)(componentFormats.size());
	numRegions = (unsigned int)(regions.size());
	numBytes = (unsigned int)(data.size());
	out << "  Usage:  " << usage << endl;
	out << "  Access:  " << access << endl;
	out << "  Num Bytes:  " << numBytes << endl;
	out << "  Cloning Behavior:  " << cloningBehavior << endl;
	out << "  Num Regions:  " << numRegions << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < regions.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Start Index:  " << regions[i1].startIndex << endl;
		out << "    Num Indices:  " << regions[i1].numIndices << endl;
	};
	out << "  Num Components:  " << numComponents << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < componentFormats.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Component Formats[" << i1 << "]:  " << componentFormats[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < data.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Data[" << i1 << "]:  " << data[i1] << endl;
		array_output_count++;
	};
	out << "  Streamable:  " << streamable << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiDataStream::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiDataStream::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiDataStream::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
