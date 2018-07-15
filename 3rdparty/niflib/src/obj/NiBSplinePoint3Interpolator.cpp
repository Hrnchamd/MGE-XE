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
#include "../../include/obj/NiBSplinePoint3Interpolator.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiBSplinePoint3Interpolator::TYPE("NiBSplinePoint3Interpolator", &NiBSplineInterpolator::TYPE );

NiBSplinePoint3Interpolator::NiBSplinePoint3Interpolator() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiBSplinePoint3Interpolator::~NiBSplinePoint3Interpolator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiBSplinePoint3Interpolator::GetType() const {
	return TYPE;
}

NiObject * NiBSplinePoint3Interpolator::Create() {
	return new NiBSplinePoint3Interpolator;
}

void NiBSplinePoint3Interpolator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBSplineInterpolator::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 6; i1++) {
		NifStream( unknownFloats[i1], in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBSplinePoint3Interpolator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBSplineInterpolator::Write( out, link_map, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < 6; i1++) {
		NifStream( unknownFloats[i1], out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiBSplinePoint3Interpolator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiBSplineInterpolator::asString();
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 6; i1++) {
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

void NiBSplinePoint3Interpolator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBSplineInterpolator::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBSplinePoint3Interpolator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiBSplineInterpolator::GetRefs();
	return refs;
}

std::list<NiObject *> NiBSplinePoint3Interpolator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiBSplineInterpolator::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
