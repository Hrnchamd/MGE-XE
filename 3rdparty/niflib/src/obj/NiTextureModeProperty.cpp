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
#include "../../include/obj/NiTextureModeProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiTextureModeProperty::TYPE("NiTextureModeProperty", &NiProperty::TYPE );

NiTextureModeProperty::NiTextureModeProperty() : unknownShort((short)0), ps2L((short)0), ps2K((short)-75) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiTextureModeProperty::~NiTextureModeProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiTextureModeProperty::GetType() const {
	return TYPE;
}

NiObject * NiTextureModeProperty::Create() {
	return new NiTextureModeProperty;
}

void NiTextureModeProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Read( in, link_stack, info );
	if ( info.version <= 0x02030000 ) {
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			NifStream( unknownInts[i2], in, info );
		};
	};
	if ( info.version >= 0x03000000 ) {
		NifStream( unknownShort, in, info );
	};
	if ( ( info.version >= 0x03010000 ) && ( info.version <= 0x0A020000 ) ) {
		NifStream( ps2L, in, info );
		NifStream( ps2K, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTextureModeProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Write( out, link_map, missing_link_stack, info );
	if ( info.version <= 0x02030000 ) {
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			NifStream( unknownInts[i2], out, info );
		};
	};
	if ( info.version >= 0x03000000 ) {
		NifStream( unknownShort, out, info );
	};
	if ( ( info.version >= 0x03010000 ) && ( info.version <= 0x0A020000 ) ) {
		NifStream( ps2L, out, info );
		NifStream( ps2K, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiTextureModeProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiProperty::asString();
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 3; i1++) {
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
	out << "  Unknown Short:  " << unknownShort << endl;
	out << "  PS2 L:  " << ps2L << endl;
	out << "  PS2 K:  " << ps2K << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTextureModeProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiTextureModeProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiProperty::GetRefs();
	return refs;
}

std::list<NiObject *> NiTextureModeProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiProperty::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
