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
#include "../../include/obj/NiScreenLODData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiScreenLODData::TYPE("NiScreenLODData", &NiLODData::TYPE );

NiScreenLODData::NiScreenLODData() : boundRadius(0.0f), worldRadius(0.0f), proportionCount((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiScreenLODData::~NiScreenLODData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiScreenLODData::GetType() const {
	return TYPE;
}

NiObject * NiScreenLODData::Create() {
	return new NiScreenLODData;
}

void NiScreenLODData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiLODData::Read( in, link_stack, info );
	NifStream( boundCenter, in, info );
	NifStream( boundRadius, in, info );
	NifStream( worldCenter, in, info );
	NifStream( worldRadius, in, info );
	NifStream( proportionCount, in, info );
	proportionLevels.resize(proportionCount);
	for (unsigned int i1 = 0; i1 < proportionLevels.size(); i1++) {
		NifStream( proportionLevels[i1], in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiScreenLODData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiLODData::Write( out, link_map, missing_link_stack, info );
	proportionCount = (unsigned int)(proportionLevels.size());
	NifStream( boundCenter, out, info );
	NifStream( boundRadius, out, info );
	NifStream( worldCenter, out, info );
	NifStream( worldRadius, out, info );
	NifStream( proportionCount, out, info );
	for (unsigned int i1 = 0; i1 < proportionLevels.size(); i1++) {
		NifStream( proportionLevels[i1], out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiScreenLODData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiLODData::asString();
	proportionCount = (unsigned int)(proportionLevels.size());
	out << "  Bound Center:  " << boundCenter << endl;
	out << "  Bound Radius:  " << boundRadius << endl;
	out << "  World Center:  " << worldCenter << endl;
	out << "  World Radius:  " << worldRadius << endl;
	out << "  Proportion Count:  " << proportionCount << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < proportionLevels.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Proportion Levels[" << i1 << "]:  " << proportionLevels[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiScreenLODData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiLODData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiScreenLODData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiLODData::GetRefs();
	return refs;
}

std::list<NiObject *> NiScreenLODData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiLODData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Vector3 NiScreenLODData::GetBoundCenter() const {
	return boundCenter;
}

void NiScreenLODData::SetBoundCenter( const Vector3 & value ) {
	boundCenter = value;
}

float NiScreenLODData::GetBoundRadius() const {
	return boundRadius;
}

void NiScreenLODData::SetBoundRadius( float value ) {
	boundRadius = value;
}

Vector3 NiScreenLODData::GetWorldCenter() const {
	return worldCenter;
}

void NiScreenLODData::SetWorldCenter( const Vector3 & value ) {
	worldCenter = value;
}

float NiScreenLODData::GetWorldRadius() const {
	return worldRadius;
}

void NiScreenLODData::SetWorldRadius( float value ) {
	worldRadius = value;
}

vector<float > NiScreenLODData::GetProportionLevels() const {
	return proportionLevels;
}

void NiScreenLODData::SetProportionLevels( const vector<float >& value ) {
	proportionLevels = value;
}

//--END CUSTOM CODE--//
