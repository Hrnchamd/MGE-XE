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
#include "../../include/obj/BSSegmentedTriShape.h"
#include "../../include/gen/BSSegment.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSSegmentedTriShape::TYPE("BSSegmentedTriShape", &NiTriShape::TYPE );

BSSegmentedTriShape::BSSegmentedTriShape() : numSegments((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSSegmentedTriShape::~BSSegmentedTriShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSSegmentedTriShape::GetType() const {
	return TYPE;
}

NiObject * BSSegmentedTriShape::Create() {
	return new BSSegmentedTriShape;
}

void BSSegmentedTriShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiTriShape::Read( in, link_stack, info );
	NifStream( numSegments, in, info );
	segment.resize(numSegments);
	for (unsigned int i1 = 0; i1 < segment.size(); i1++) {
		NifStream( segment[i1].internalIndex, in, info );
		NifStream( segment[i1].flags, in, info );
		NifStream( segment[i1].unknownByte1, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSSegmentedTriShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiTriShape::Write( out, link_map, missing_link_stack, info );
	numSegments = (int)(segment.size());
	NifStream( numSegments, out, info );
	for (unsigned int i1 = 0; i1 < segment.size(); i1++) {
		NifStream( segment[i1].internalIndex, out, info );
		NifStream( segment[i1].flags, out, info );
		NifStream( segment[i1].unknownByte1, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSSegmentedTriShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiTriShape::asString();
	numSegments = (int)(segment.size());
	out << "  Num Segments:  " << numSegments << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < segment.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Internal index:  " << segment[i1].internalIndex << endl;
		out << "    Flags:  " << segment[i1].flags << endl;
		out << "    Unknown Byte 1:  " << segment[i1].unknownByte1 << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSSegmentedTriShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiTriShape::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSSegmentedTriShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiTriShape::GetRefs();
	return refs;
}

std::list<NiObject *> BSSegmentedTriShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiTriShape::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
