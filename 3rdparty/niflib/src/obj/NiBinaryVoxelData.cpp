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
#include "../../include/obj/NiBinaryVoxelData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiBinaryVoxelData::TYPE("NiBinaryVoxelData", &NiObject::TYPE );

NiBinaryVoxelData::NiBinaryVoxelData() : unknownShort1((unsigned short)0), unknownShort2((unsigned short)0), unknownShort3((unsigned short)0), numUnknownVectors((unsigned int)0), numUnknownBytes2((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiBinaryVoxelData::~NiBinaryVoxelData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiBinaryVoxelData::GetType() const {
	return TYPE;
}

NiObject * NiBinaryVoxelData::Create() {
	return new NiBinaryVoxelData;
}

void NiBinaryVoxelData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( unknownShort1, in, info );
	NifStream( unknownShort2, in, info );
	NifStream( unknownShort3, in, info );
	for (unsigned int i1 = 0; i1 < 7; i1++) {
		NifStream( unknown7Floats[i1], in, info );
	};
	for (unsigned int i1 = 0; i1 < 7; i1++) {
		for (unsigned int i2 = 0; i2 < 12; i2++) {
			NifStream( unknownBytes1[i1][i2], in, info );
		};
	};
	NifStream( numUnknownVectors, in, info );
	unknownVectors.resize(numUnknownVectors);
	for (unsigned int i1 = 0; i1 < unknownVectors.size(); i1++) {
		NifStream( unknownVectors[i1], in, info );
	};
	NifStream( numUnknownBytes2, in, info );
	unknownBytes2.resize(numUnknownBytes2);
	for (unsigned int i1 = 0; i1 < unknownBytes2.size(); i1++) {
		NifStream( unknownBytes2[i1], in, info );
	};
	for (unsigned int i1 = 0; i1 < 5; i1++) {
		NifStream( unknown5Ints[i1], in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBinaryVoxelData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	numUnknownBytes2 = (unsigned int)(unknownBytes2.size());
	numUnknownVectors = (unsigned int)(unknownVectors.size());
	NifStream( unknownShort1, out, info );
	NifStream( unknownShort2, out, info );
	NifStream( unknownShort3, out, info );
	for (unsigned int i1 = 0; i1 < 7; i1++) {
		NifStream( unknown7Floats[i1], out, info );
	};
	for (unsigned int i1 = 0; i1 < 7; i1++) {
		for (unsigned int i2 = 0; i2 < 12; i2++) {
			NifStream( unknownBytes1[i1][i2], out, info );
		};
	};
	NifStream( numUnknownVectors, out, info );
	for (unsigned int i1 = 0; i1 < unknownVectors.size(); i1++) {
		NifStream( unknownVectors[i1], out, info );
	};
	NifStream( numUnknownBytes2, out, info );
	for (unsigned int i1 = 0; i1 < unknownBytes2.size(); i1++) {
		NifStream( unknownBytes2[i1], out, info );
	};
	for (unsigned int i1 = 0; i1 < 5; i1++) {
		NifStream( unknown5Ints[i1], out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiBinaryVoxelData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numUnknownBytes2 = (unsigned int)(unknownBytes2.size());
	numUnknownVectors = (unsigned int)(unknownVectors.size());
	out << "  Unknown Short 1:  " << unknownShort1 << endl;
	out << "  Unknown Short 2:  " << unknownShort2 << endl;
	out << "  Unknown Short 3:  " << unknownShort3 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 7; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 7 Floats[" << i1 << "]:  " << unknown7Floats[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 7; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		for (unsigned int i2 = 0; i2 < 12; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown Bytes 1[" << i2 << "]:  " << unknownBytes1[i1][i2] << endl;
			array_output_count++;
		};
	};
	out << "  Num Unknown Vectors:  " << numUnknownVectors << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknownVectors.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Vectors[" << i1 << "]:  " << unknownVectors[i1] << endl;
		array_output_count++;
	};
	out << "  Num Unknown Bytes 2:  " << numUnknownBytes2 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknownBytes2.size(); i1++) {
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
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 5; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 5 Ints[" << i1 << "]:  " << unknown5Ints[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBinaryVoxelData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBinaryVoxelData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiBinaryVoxelData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
