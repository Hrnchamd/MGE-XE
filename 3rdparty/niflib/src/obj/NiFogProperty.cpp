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
#include "../../include/obj/NiFogProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiFogProperty::TYPE("NiFogProperty", &NiProperty::TYPE );

NiFogProperty::NiFogProperty() : flags((unsigned short)0), fogDepth(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiFogProperty::~NiFogProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiFogProperty::GetType() const {
	return TYPE;
}

NiObject * NiFogProperty::Create() {
	return new NiFogProperty;
}

void NiFogProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Read( in, link_stack, info );
	NifStream( flags, in, info );
	NifStream( fogDepth, in, info );
	NifStream( fogColor, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiFogProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Write( out, link_map, missing_link_stack, info );
	NifStream( flags, out, info );
	NifStream( fogDepth, out, info );
	NifStream( fogColor, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiFogProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiProperty::asString();
	out << "  Flags:  " << flags << endl;
	out << "  Fog Depth:  " << fogDepth << endl;
	out << "  Fog Color:  " << fogColor << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiFogProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiFogProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiProperty::GetRefs();
	return refs;
}

std::list<NiObject *> NiFogProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiProperty::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

unsigned short NiFogProperty::GetFlags() const {
   return flags;
}

void NiFogProperty::SetFlags( unsigned short n ) {
   flags = n;
}

float NiFogProperty::GetFogDepth() const {
   return fogDepth;
}

void NiFogProperty::SetFogDepth(float value) {
   fogDepth = value;
}

Color3 NiFogProperty::GetFogColor() const {
   return fogColor;
}

void NiFogProperty::SetFogColor(Color3 value) {
   fogColor = value;
}

//--END CUSTOM CODE--//
