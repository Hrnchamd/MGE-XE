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
#include "../../include/obj/NiPhysXMeshDesc.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPhysXMeshDesc::TYPE("NiPhysXMeshDesc", &NiObject::TYPE );

NiPhysXMeshDesc::NiPhysXMeshDesc() : unknownShort1((short)0), unknownFloat1(0.0f), unknownShort2((short)0), unknownByte1((byte)0), unknownFloat2(0.0f), unknownInt1((int)0), unknownInt2((int)0), numVertices((int)0), unknownInt4((int)0), unknownByte2((byte)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPhysXMeshDesc::~NiPhysXMeshDesc() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPhysXMeshDesc::GetType() const {
	return TYPE;
}

NiObject * NiPhysXMeshDesc::Create() {
	return new NiPhysXMeshDesc;
}

void NiPhysXMeshDesc::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( unknownShort1, in, info );
	NifStream( unknownFloat1, in, info );
	NifStream( unknownShort2, in, info );
	for (unsigned int i1 = 0; i1 < 3; i1++) {
		NifStream( unknownBytes0[i1], in, info );
	};
	NifStream( unknownByte1, in, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknownBytes1[i1], in, info );
	};
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( unknownBytes2[i1], in, info );
	};
	NifStream( unknownFloat2, in, info );
	NifStream( unknownInt1, in, info );
	NifStream( unknownInt2, in, info );
	NifStream( numVertices, in, info );
	NifStream( unknownInt4, in, info );
	vertices.resize(numVertices);
	for (unsigned int i1 = 0; i1 < vertices.size(); i1++) {
		NifStream( vertices[i1], in, info );
	};
	for (unsigned int i1 = 0; i1 < 982; i1++) {
		NifStream( unknownBytes3[i1], in, info );
	};
	for (unsigned int i1 = 0; i1 < 368; i1++) {
		NifStream( unknownShorts1[i1], in, info );
	};
	for (unsigned int i1 = 0; i1 < 3328; i1++) {
		NifStream( unknownInts1[i1], in, info );
	};
	NifStream( unknownByte2, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPhysXMeshDesc::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	numVertices = (int)(vertices.size());
	NifStream( unknownShort1, out, info );
	NifStream( unknownFloat1, out, info );
	NifStream( unknownShort2, out, info );
	for (unsigned int i1 = 0; i1 < 3; i1++) {
		NifStream( unknownBytes0[i1], out, info );
	};
	NifStream( unknownByte1, out, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknownBytes1[i1], out, info );
	};
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( unknownBytes2[i1], out, info );
	};
	NifStream( unknownFloat2, out, info );
	NifStream( unknownInt1, out, info );
	NifStream( unknownInt2, out, info );
	NifStream( numVertices, out, info );
	NifStream( unknownInt4, out, info );
	for (unsigned int i1 = 0; i1 < vertices.size(); i1++) {
		NifStream( vertices[i1], out, info );
	};
	for (unsigned int i1 = 0; i1 < 982; i1++) {
		NifStream( unknownBytes3[i1], out, info );
	};
	for (unsigned int i1 = 0; i1 < 368; i1++) {
		NifStream( unknownShorts1[i1], out, info );
	};
	for (unsigned int i1 = 0; i1 < 3328; i1++) {
		NifStream( unknownInts1[i1], out, info );
	};
	NifStream( unknownByte2, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPhysXMeshDesc::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numVertices = (int)(vertices.size());
	out << "  Unknown Short 1:  " << unknownShort1 << endl;
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Unknown Short 2:  " << unknownShort2 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 3; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Bytes 0[" << i1 << "]:  " << unknownBytes0[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Byte 1:  " << unknownByte1 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Bytes 1[" << i1 << "]:  " << unknownBytes1[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Bytes 2[" << i1 << "]:  " << unknownBytes2[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Num Vertices:  " << numVertices << endl;
	out << "  Unknown Int 4:  " << unknownInt4 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < vertices.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Vertices[" << i1 << "]:  " << vertices[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 982; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Bytes 3[" << i1 << "]:  " << unknownBytes3[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 368; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Shorts 1[" << i1 << "]:  " << unknownShorts1[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 3328; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Ints 1[" << i1 << "]:  " << unknownInts1[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Byte 2:  " << unknownByte2 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPhysXMeshDesc::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPhysXMeshDesc::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiPhysXMeshDesc::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
