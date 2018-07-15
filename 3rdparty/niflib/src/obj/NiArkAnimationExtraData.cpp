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
#include "../../include/obj/NiArkAnimationExtraData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiArkAnimationExtraData::TYPE("NiArkAnimationExtraData", &NiExtraData::TYPE );

NiArkAnimationExtraData::NiArkAnimationExtraData() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiArkAnimationExtraData::~NiArkAnimationExtraData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiArkAnimationExtraData::GetType() const {
	return TYPE;
}

NiObject * NiArkAnimationExtraData::Create() {
	return new NiArkAnimationExtraData;
}

void NiArkAnimationExtraData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknownInts[i1], in, info );
	};
	if ( info.version <= 0x0401000C ) {
		for (unsigned int i2 = 0; i2 < 37; i2++) {
			NifStream( unknownBytes[i2], in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiArkAnimationExtraData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::Write( out, link_map, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknownInts[i1], out, info );
	};
	if ( info.version <= 0x0401000C ) {
		for (unsigned int i2 = 0; i2 < 37; i2++) {
			NifStream( unknownBytes[i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiArkAnimationExtraData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiExtraData::asString();
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Ints[" << i1 << "]:  " << unknownInts[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 37; i1++) {
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
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiArkAnimationExtraData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiArkAnimationExtraData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiExtraData::GetRefs();
	return refs;
}

std::list<NiObject *> NiArkAnimationExtraData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiExtraData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
