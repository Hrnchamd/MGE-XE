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
#include "../../include/obj/NiBlendFloatInterpolator.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiBlendFloatInterpolator::TYPE("NiBlendFloatInterpolator", &NiBlendInterpolator::TYPE );

NiBlendFloatInterpolator::NiBlendFloatInterpolator() : floatValue(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiBlendFloatInterpolator::~NiBlendFloatInterpolator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiBlendFloatInterpolator::GetType() const {
	return TYPE;
}

NiObject * NiBlendFloatInterpolator::Create() {
	return new NiBlendFloatInterpolator;
}

void NiBlendFloatInterpolator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBlendInterpolator::Read( in, link_stack, info );
	NifStream( floatValue, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBlendFloatInterpolator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBlendInterpolator::Write( out, link_map, missing_link_stack, info );
	NifStream( floatValue, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiBlendFloatInterpolator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiBlendInterpolator::asString();
	out << "  Float Value:  " << floatValue << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBlendFloatInterpolator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBlendInterpolator::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBlendFloatInterpolator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiBlendInterpolator::GetRefs();
	return refs;
}

std::list<NiObject *> NiBlendFloatInterpolator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiBlendInterpolator::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

float NiBlendFloatInterpolator::GetFloatValue() const {
	return floatValue;
}

void NiBlendFloatInterpolator::SetFloatValue( float value ) {
	floatValue = value;
}

//--END CUSTOM CODE--//
