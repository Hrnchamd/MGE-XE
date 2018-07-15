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
#include "../../include/obj/NiUVData.h"
#include "../../include/gen/KeyGroup.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiUVData::TYPE("NiUVData", &NiObject::TYPE );

NiUVData::NiUVData() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiUVData::~NiUVData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiUVData::GetType() const {
	return TYPE;
}

NiObject * NiUVData::Create() {
	return new NiUVData;
}

void NiUVData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( uvGroups[i1].numKeys, in, info );
		if ( (uvGroups[i1].numKeys != 0) ) {
			NifStream( uvGroups[i1].interpolation, in, info );
		};
		uvGroups[i1].keys.resize(uvGroups[i1].numKeys);
		for (unsigned int i2 = 0; i2 < uvGroups[i1].keys.size(); i2++) {
			NifStream( uvGroups[i1].keys[i2], in, info, uvGroups[i1].interpolation );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiUVData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		uvGroups[i1].numKeys = (unsigned int)(uvGroups[i1].keys.size());
		NifStream( uvGroups[i1].numKeys, out, info );
		if ( (uvGroups[i1].numKeys != 0) ) {
			NifStream( uvGroups[i1].interpolation, out, info );
		};
		for (unsigned int i2 = 0; i2 < uvGroups[i1].keys.size(); i2++) {
			NifStream( uvGroups[i1].keys[i2], out, info, uvGroups[i1].interpolation );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiUVData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		uvGroups[i1].numKeys = (unsigned int)(uvGroups[i1].keys.size());
		out << "    Num Keys:  " << uvGroups[i1].numKeys << endl;
		if ( (uvGroups[i1].numKeys != 0) ) {
			out << "      Interpolation:  " << uvGroups[i1].interpolation << endl;
		};
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < uvGroups[i1].keys.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Keys[" << i2 << "]:  " << uvGroups[i1].keys[i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiUVData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiUVData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiUVData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
