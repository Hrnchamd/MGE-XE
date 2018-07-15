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
#include "../../include/obj/NiBSplineCompPoint3Interpolator.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiBSplineCompPoint3Interpolator::TYPE("NiBSplineCompPoint3Interpolator", &NiBSplinePoint3Interpolator::TYPE );

NiBSplineCompPoint3Interpolator::NiBSplineCompPoint3Interpolator() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiBSplineCompPoint3Interpolator::~NiBSplineCompPoint3Interpolator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiBSplineCompPoint3Interpolator::GetType() const {
	return TYPE;
}

NiObject * NiBSplineCompPoint3Interpolator::Create() {
	return new NiBSplineCompPoint3Interpolator;
}

void NiBSplineCompPoint3Interpolator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBSplinePoint3Interpolator::Read( in, link_stack, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBSplineCompPoint3Interpolator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBSplinePoint3Interpolator::Write( out, link_map, missing_link_stack, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiBSplineCompPoint3Interpolator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiBSplinePoint3Interpolator::asString();
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBSplineCompPoint3Interpolator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBSplinePoint3Interpolator::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBSplineCompPoint3Interpolator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiBSplinePoint3Interpolator::GetRefs();
	return refs;
}

std::list<NiObject *> NiBSplineCompPoint3Interpolator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiBSplinePoint3Interpolator::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
