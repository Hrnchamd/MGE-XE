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
#include "../../include/obj/NiBlendPoint3Interpolator.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiBlendPoint3Interpolator::TYPE("NiBlendPoint3Interpolator", &NiBlendInterpolator::TYPE );

NiBlendPoint3Interpolator::NiBlendPoint3Interpolator() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiBlendPoint3Interpolator::~NiBlendPoint3Interpolator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiBlendPoint3Interpolator::GetType() const {
	return TYPE;
}

NiObject * NiBlendPoint3Interpolator::Create() {
	return new NiBlendPoint3Interpolator;
}

void NiBlendPoint3Interpolator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBlendInterpolator::Read( in, link_stack, info );
	NifStream( pointValue, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBlendPoint3Interpolator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBlendInterpolator::Write( out, link_map, missing_link_stack, info );
	NifStream( pointValue, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiBlendPoint3Interpolator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiBlendInterpolator::asString();
	out << "  Point Value:  " << pointValue << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBlendPoint3Interpolator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBlendInterpolator::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBlendPoint3Interpolator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiBlendInterpolator::GetRefs();
	return refs;
}

std::list<NiObject *> NiBlendPoint3Interpolator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiBlendInterpolator::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Vector3 NiBlendPoint3Interpolator::GetPointValue() const {
	return pointValue;
}

void NiBlendPoint3Interpolator::SetPointValue( Vector3 value ) {
	pointValue = value;
}

//--END CUSTOM CODE--//
