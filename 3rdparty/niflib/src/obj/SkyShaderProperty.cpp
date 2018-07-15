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
#include "../../include/obj/SkyShaderProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type SkyShaderProperty::TYPE("SkyShaderProperty", &BSShaderProperty::TYPE );

SkyShaderProperty::SkyShaderProperty() : unknownInt4((int)0), unknownInt5((int)3) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

SkyShaderProperty::~SkyShaderProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & SkyShaderProperty::GetType() const {
	return TYPE;
}

NiObject * SkyShaderProperty::Create() {
	return new SkyShaderProperty;
}

void SkyShaderProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSShaderProperty::Read( in, link_stack, info );
	NifStream( unknownInt4, in, info );
	NifStream( fileName, in, info );
	NifStream( unknownInt5, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void SkyShaderProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSShaderProperty::Write( out, link_map, missing_link_stack, info );
	NifStream( unknownInt4, out, info );
	NifStream( fileName, out, info );
	NifStream( unknownInt5, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string SkyShaderProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << BSShaderProperty::asString();
	out << "  Unknown Int 4:  " << unknownInt4 << endl;
	out << "  File Name:  " << fileName << endl;
	out << "  Unknown Int 5:  " << unknownInt5 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void SkyShaderProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSShaderProperty::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> SkyShaderProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = BSShaderProperty::GetRefs();
	return refs;
}

std::list<NiObject *> SkyShaderProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = BSShaderProperty::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

string SkyShaderProperty::GetFileName() const {
	return fileName;
}

void SkyShaderProperty::SetFileName( const string & value ) {
	fileName = value;
}

//--END CUSTOM CODE--//
