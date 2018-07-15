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
#include "../../include/obj/NiRangeLODData.h"
#include "../../include/gen/LODRange.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiRangeLODData::TYPE("NiRangeLODData", &NiLODData::TYPE );

NiRangeLODData::NiRangeLODData() : numLodLevels((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiRangeLODData::~NiRangeLODData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiRangeLODData::GetType() const {
	return TYPE;
}

NiObject * NiRangeLODData::Create() {
	return new NiRangeLODData;
}

void NiRangeLODData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiLODData::Read( in, link_stack, info );
	NifStream( lodCenter, in, info );
	NifStream( numLodLevels, in, info );
	lodLevels.resize(numLodLevels);
	for (unsigned int i1 = 0; i1 < lodLevels.size(); i1++) {
		NifStream( lodLevels[i1].nearExtent, in, info );
		NifStream( lodLevels[i1].farExtent, in, info );
		if ( info.version <= 0x03010000 ) {
			for (unsigned int i3 = 0; i3 < 3; i3++) {
				NifStream( lodLevels[i1].unknownInts[i3], in, info );
			};
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiRangeLODData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiLODData::Write( out, link_map, missing_link_stack, info );
	numLodLevels = (unsigned int)(lodLevels.size());
	NifStream( lodCenter, out, info );
	NifStream( numLodLevels, out, info );
	for (unsigned int i1 = 0; i1 < lodLevels.size(); i1++) {
		NifStream( lodLevels[i1].nearExtent, out, info );
		NifStream( lodLevels[i1].farExtent, out, info );
		if ( info.version <= 0x03010000 ) {
			for (unsigned int i3 = 0; i3 < 3; i3++) {
				NifStream( lodLevels[i1].unknownInts[i3], out, info );
			};
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiRangeLODData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiLODData::asString();
	numLodLevels = (unsigned int)(lodLevels.size());
	out << "  LOD Center:  " << lodCenter << endl;
	out << "  Num LOD Levels:  " << numLodLevels << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < lodLevels.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Near Extent:  " << lodLevels[i1].nearExtent << endl;
		out << "    Far Extent:  " << lodLevels[i1].farExtent << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown Ints[" << i2 << "]:  " << lodLevels[i1].unknownInts[i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiRangeLODData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiLODData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiRangeLODData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiLODData::GetRefs();
	return refs;
}

std::list<NiObject *> NiRangeLODData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiLODData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Vector3 NiRangeLODData::GetLODCenter() const {
	return lodCenter;
}

void NiRangeLODData::SetLODCenter( const Vector3 & value ) {
	lodCenter = value;
}

vector<LODRange > NiRangeLODData::GetLODLevels() const {
	return lodLevels;
}

void NiRangeLODData::SetLODLevels( const vector<LODRange >& value ) {
	lodLevels = value;
}

//--END CUSTOM CODE--//
