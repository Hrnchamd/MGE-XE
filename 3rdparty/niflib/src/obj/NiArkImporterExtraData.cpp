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
#include "../../include/obj/NiArkImporterExtraData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiArkImporterExtraData::TYPE("NiArkImporterExtraData", &NiExtraData::TYPE );

NiArkImporterExtraData::NiArkImporterExtraData() : unknownInt1((int)0), unknownInt2((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiArkImporterExtraData::~NiArkImporterExtraData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiArkImporterExtraData::GetType() const {
	return TYPE;
}

NiObject * NiArkImporterExtraData::Create() {
	return new NiArkImporterExtraData;
}

void NiArkImporterExtraData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::Read( in, link_stack, info );
	NifStream( unknownInt1, in, info );
	if ( info.version <= 0x0401000C ) {
		NifStream( unknownInt2, in, info );
	};
	NifStream( importerName, in, info );
	for (unsigned int i1 = 0; i1 < 13; i1++) {
		NifStream( unknownBytes[i1], in, info );
	};
	for (unsigned int i1 = 0; i1 < 7; i1++) {
		NifStream( unknownFloats[i1], in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiArkImporterExtraData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::Write( out, link_map, missing_link_stack, info );
	NifStream( unknownInt1, out, info );
	if ( info.version <= 0x0401000C ) {
		NifStream( unknownInt2, out, info );
	};
	NifStream( importerName, out, info );
	for (unsigned int i1 = 0; i1 < 13; i1++) {
		NifStream( unknownBytes[i1], out, info );
	};
	for (unsigned int i1 = 0; i1 < 7; i1++) {
		NifStream( unknownFloats[i1], out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiArkImporterExtraData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiExtraData::asString();
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Importer Name:  " << importerName << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 13; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Bytes[" << i1 << "]:  " << unknownBytes[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 7; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Floats[" << i1 << "]:  " << unknownFloats[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiArkImporterExtraData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiArkImporterExtraData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiExtraData::GetRefs();
	return refs;
}

std::list<NiObject *> NiArkImporterExtraData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiExtraData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
