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
#include "../../include/obj/NiFloatExtraDataController.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiFloatExtraDataController::TYPE("NiFloatExtraDataController", &NiExtraDataController::TYPE );

NiFloatExtraDataController::NiFloatExtraDataController() : numExtraBytes((byte)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiFloatExtraDataController::~NiFloatExtraDataController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiFloatExtraDataController::GetType() const {
	return TYPE;
}

NiObject * NiFloatExtraDataController::Create() {
	return new NiFloatExtraDataController;
}

void NiFloatExtraDataController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraDataController::Read( in, link_stack, info );
	if ( info.version >= 0x0A020000 ) {
		NifStream( controllerData, in, info );
	};
	if ( info.version <= 0x0A010000 ) {
		NifStream( numExtraBytes, in, info );
		for (unsigned int i2 = 0; i2 < 7; i2++) {
			NifStream( unknownBytes[i2], in, info );
		};
		unknownExtraBytes.resize(numExtraBytes);
		for (unsigned int i2 = 0; i2 < unknownExtraBytes.size(); i2++) {
			NifStream( unknownExtraBytes[i2], in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiFloatExtraDataController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraDataController::Write( out, link_map, missing_link_stack, info );
	numExtraBytes = (byte)(unknownExtraBytes.size());
	if ( info.version >= 0x0A020000 ) {
		NifStream( controllerData, out, info );
	};
	if ( info.version <= 0x0A010000 ) {
		NifStream( numExtraBytes, out, info );
		for (unsigned int i2 = 0; i2 < 7; i2++) {
			NifStream( unknownBytes[i2], out, info );
		};
		for (unsigned int i2 = 0; i2 < unknownExtraBytes.size(); i2++) {
			NifStream( unknownExtraBytes[i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiFloatExtraDataController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiExtraDataController::asString();
	numExtraBytes = (byte)(unknownExtraBytes.size());
	out << "  Controller Data:  " << controllerData << endl;
	out << "  Num Extra Bytes:  " << numExtraBytes << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 7; i1++) {
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
	for (unsigned int i1 = 0; i1 < unknownExtraBytes.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Extra Bytes[" << i1 << "]:  " << unknownExtraBytes[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiFloatExtraDataController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraDataController::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiFloatExtraDataController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiExtraDataController::GetRefs();
	return refs;
}

std::list<NiObject *> NiFloatExtraDataController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiExtraDataController::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
