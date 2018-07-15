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
#include "../../include/obj/BSFurnitureMarker.h"
#include "../../include/gen/FurniturePosition.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSFurnitureMarker::TYPE("BSFurnitureMarker", &NiExtraData::TYPE );

BSFurnitureMarker::BSFurnitureMarker() : numPositions((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

BSFurnitureMarker::~BSFurnitureMarker() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & BSFurnitureMarker::GetType() const {
	return TYPE;
}

NiObject * BSFurnitureMarker::Create() {
	return new BSFurnitureMarker;
}

void BSFurnitureMarker::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::Read( in, link_stack, info );
	NifStream( numPositions, in, info );
	positions.resize(numPositions);
	for (unsigned int i1 = 0; i1 < positions.size(); i1++) {
		NifStream( positions[i1].offset, in, info );
		if ( (info.userVersion <= 11) ) {
			NifStream( positions[i1].orientation, in, info );
			NifStream( positions[i1].positionRef1, in, info );
			NifStream( positions[i1].positionRef2, in, info );
		};
		if ( ((info.version >= 0x14020007) && (info.userVersion >= 12)) ) {
			NifStream( positions[i1].heading, in, info );
			NifStream( positions[i1].animationType, in, info );
			NifStream( positions[i1].entryProperties, in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void BSFurnitureMarker::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::Write( out, link_map, missing_link_stack, info );
	numPositions = (unsigned int)(positions.size());
	NifStream( numPositions, out, info );
	for (unsigned int i1 = 0; i1 < positions.size(); i1++) {
		NifStream( positions[i1].offset, out, info );
		if ( (info.userVersion <= 11) ) {
			NifStream( positions[i1].orientation, out, info );
			NifStream( positions[i1].positionRef1, out, info );
			NifStream( positions[i1].positionRef2, out, info );
		};
		if ( ((info.version >= 0x14020007) && (info.userVersion >= 12)) ) {
			NifStream( positions[i1].heading, out, info );
			NifStream( positions[i1].animationType, out, info );
			NifStream( positions[i1].entryProperties, out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string BSFurnitureMarker::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiExtraData::asString();
	numPositions = (unsigned int)(positions.size());
	out << "  Num Positions:  " << numPositions << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < positions.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Offset:  " << positions[i1].offset << endl;
		out << "    Orientation:  " << positions[i1].orientation << endl;
		out << "    Position Ref 1:  " << positions[i1].positionRef1 << endl;
		out << "    Position Ref 2:  " << positions[i1].positionRef2 << endl;
		out << "    Heading:  " << positions[i1].heading << endl;
		out << "    Animation Type:  " << positions[i1].animationType << endl;
		out << "    Entry Properties:  " << positions[i1].entryProperties << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void BSFurnitureMarker::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiExtraData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSFurnitureMarker::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiExtraData::GetRefs();
	return refs;
}

std::list<NiObject *> BSFurnitureMarker::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiExtraData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

vector<FurniturePosition> BSFurnitureMarker::GetFurniturePositions() const {
	return positions;
}
	
void BSFurnitureMarker::SetFurniturePositions( const vector<FurniturePosition> & n ) {
	numPositions = (unsigned int)(n.size());
	positions = n;
}

//--END CUSTOM CODE--//
