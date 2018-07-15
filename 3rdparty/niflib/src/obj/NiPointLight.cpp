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
#include "../../include/obj/NiPointLight.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPointLight::TYPE("NiPointLight", &NiLight::TYPE );

NiPointLight::NiPointLight() : constantAttenuation(0.0f), linearAttenuation(0.0f), quadraticAttenuation(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPointLight::~NiPointLight() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPointLight::GetType() const {
	return TYPE;
}

NiObject * NiPointLight::Create() {
	return new NiPointLight;
}

void NiPointLight::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiLight::Read( in, link_stack, info );
	NifStream( constantAttenuation, in, info );
	NifStream( linearAttenuation, in, info );
	NifStream( quadraticAttenuation, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPointLight::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiLight::Write( out, link_map, missing_link_stack, info );
	NifStream( constantAttenuation, out, info );
	NifStream( linearAttenuation, out, info );
	NifStream( quadraticAttenuation, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPointLight::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiLight::asString();
	out << "  Constant Attenuation:  " << constantAttenuation << endl;
	out << "  Linear Attenuation:  " << linearAttenuation << endl;
	out << "  Quadratic Attenuation:  " << quadraticAttenuation << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPointLight::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiLight::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPointLight::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiLight::GetRefs();
	return refs;
}

std::list<NiObject *> NiPointLight::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiLight::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

float NiPointLight::GetConstantAttenuation() const {
	return constantAttenuation;
}

void NiPointLight::SetConstantAttenuation( float value ) {
	constantAttenuation = value;
}

float NiPointLight::GetLinearAttenuation() const {
	return linearAttenuation;
}

void NiPointLight::SetLinearAttenuation( float value ) {
	linearAttenuation = value;
}

float NiPointLight::GetQuadraticAttenuation() const {
	return quadraticAttenuation;
}

void NiPointLight::SetQuadraticAttenuation( float value ) {
	quadraticAttenuation = value;
}

//--END CUSTOM CODE--//
