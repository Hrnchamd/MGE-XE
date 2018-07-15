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
#include "../../include/obj/NiVertexColorProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiVertexColorProperty::TYPE("NiVertexColorProperty", &NiProperty::TYPE );

NiVertexColorProperty::NiVertexColorProperty() : flags((unsigned short)0), vertexMode((VertMode)0), lightingMode((LightMode)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiVertexColorProperty::~NiVertexColorProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiVertexColorProperty::GetType() const {
	return TYPE;
}

NiObject * NiVertexColorProperty::Create() {
	return new NiVertexColorProperty;
}

void NiVertexColorProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Read( in, link_stack, info );
	NifStream( flags, in, info );
	if ( info.version <= 0x14000005 ) {
		NifStream( vertexMode, in, info );
		NifStream( lightingMode, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	if ( info.version > 0x14000005 ) {
		lightingMode = (LightMode)UnpackField( flags, 3, 1);
		vertexMode = (VertMode)UnpackField( flags, 4, 2);
	}
	//--END CUSTOM CODE--//
}

void NiVertexColorProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Write( out, link_map, missing_link_stack, info );
	NifStream( flags, out, info );
	if ( info.version <= 0x14000005 ) {
		NifStream( vertexMode, out, info );
		NifStream( lightingMode, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiVertexColorProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiProperty::asString();
	out << "  Flags:  " << flags << endl;
	out << "  Vertex Mode:  " << vertexMode << endl;
	out << "  Lighting Mode:  " << lightingMode << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiVertexColorProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiVertexColorProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiProperty::GetRefs();
	return refs;
}

std::list<NiObject *> NiVertexColorProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiProperty::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

unsigned short NiVertexColorProperty::GetFlags() const {
   return flags;
}

void NiVertexColorProperty::SetFlags(unsigned short value) {
   flags = value;
}

VertMode NiVertexColorProperty::GetVertexMode() const {
   return vertexMode;
}

void NiVertexColorProperty::SetVertexMode(VertMode value) {
   vertexMode = value;
}

LightMode NiVertexColorProperty::GetLightingMode() const {
   return lightingMode;
}

void NiVertexColorProperty::SetLightingMode(LightMode value) {
   lightingMode = value;
}

//--END CUSTOM CODE--//
