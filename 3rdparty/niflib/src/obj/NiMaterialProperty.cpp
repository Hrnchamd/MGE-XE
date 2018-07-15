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
#include "../../include/obj/NiMaterialProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiMaterialProperty::TYPE("NiMaterialProperty", &NiProperty::TYPE );

NiMaterialProperty::NiMaterialProperty() : flags((unsigned short)0), glossiness(0.0f), alpha(0.0f), emitMulti(1.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiMaterialProperty::~NiMaterialProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiMaterialProperty::GetType() const {
	return TYPE;
}

NiObject * NiMaterialProperty::Create() {
	return new NiMaterialProperty;
}

void NiMaterialProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Read( in, link_stack, info );
	if ( ( info.version >= 0x03000000 ) && ( info.version <= 0x0A000102 ) ) {
		NifStream( flags, in, info );
	};
	if ( (!((info.version == 0x14020007) && ((info.userVersion >= 11) && (info.userVersion2 > 21)))) ) {
		NifStream( ambientColor, in, info );
		NifStream( diffuseColor, in, info );
	};
	NifStream( specularColor, in, info );
	NifStream( emissiveColor, in, info );
	NifStream( glossiness, in, info );
	NifStream( alpha, in, info );
	if ( ((info.version == 0x14020007) && ((info.userVersion >= 11) && (info.userVersion2 > 21))) ) {
		NifStream( emitMulti, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiMaterialProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Write( out, link_map, missing_link_stack, info );
	if ( ( info.version >= 0x03000000 ) && ( info.version <= 0x0A000102 ) ) {
		NifStream( flags, out, info );
	};
	if ( (!((info.version == 0x14020007) && ((info.userVersion >= 11) && (info.userVersion2 > 21)))) ) {
		NifStream( ambientColor, out, info );
		NifStream( diffuseColor, out, info );
	};
	NifStream( specularColor, out, info );
	NifStream( emissiveColor, out, info );
	NifStream( glossiness, out, info );
	NifStream( alpha, out, info );
	if ( ((info.version == 0x14020007) && ((info.userVersion >= 11) && (info.userVersion2 > 21))) ) {
		NifStream( emitMulti, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiMaterialProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiProperty::asString();
	out << "  Flags:  " << flags << endl;
	out << "  Ambient Color:  " << ambientColor << endl;
	out << "  Diffuse Color:  " << diffuseColor << endl;
	out << "  Specular Color:  " << specularColor << endl;
	out << "  Emissive Color:  " << emissiveColor << endl;
	out << "  Glossiness:  " << glossiness << endl;
	out << "  Alpha:  " << alpha << endl;
	out << "  Emit Multi:  " << emitMulti << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiMaterialProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiMaterialProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiProperty::GetRefs();
	return refs;
}

std::list<NiObject *> NiMaterialProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiProperty::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

unsigned short NiMaterialProperty::GetFlags() const {
	return flags;
}

void NiMaterialProperty::SetFlags( unsigned short n ) {
	flags = n;
}

float NiMaterialProperty::GetTransparency() const {
	return alpha;
}

void NiMaterialProperty::SetTransparency( float n ) {
	alpha = n;
}

float NiMaterialProperty::GetGlossiness() const {
	return glossiness;
}

void NiMaterialProperty::SetGlossiness( float n ) {
	glossiness = n;
}

Color3 NiMaterialProperty::GetAmbientColor() const {
	return ambientColor;
}

void NiMaterialProperty::SetAmbientColor( const Color3 & n ) {
	ambientColor = n;
}

Color3 NiMaterialProperty::GetDiffuseColor() const {
	return diffuseColor;
}

void NiMaterialProperty::SetDiffuseColor( const Color3 & n ) {
	diffuseColor = n;
}

Color3 NiMaterialProperty::GetEmissiveColor() const {
	return emissiveColor;
}

void NiMaterialProperty::SetEmissiveColor( const Color3 & n ) {
	emissiveColor = n;
}

Color3 NiMaterialProperty::GetSpecularColor() const {
	return specularColor;
}

void NiMaterialProperty::SetSpecularColor( const Color3 & n ) {
	specularColor = n;
}

//--END CUSTOM CODE--//
