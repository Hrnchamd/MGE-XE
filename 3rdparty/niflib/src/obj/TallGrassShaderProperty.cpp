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
#include "../../include/obj/TallGrassShaderProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type TallGrassShaderProperty::TYPE("TallGrassShaderProperty", &BSShaderProperty::TYPE );

TallGrassShaderProperty::TallGrassShaderProperty() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

TallGrassShaderProperty::~TallGrassShaderProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & TallGrassShaderProperty::GetType() const {
	return TYPE;
}

NiObject * TallGrassShaderProperty::Create() {
	return new TallGrassShaderProperty;
}

void TallGrassShaderProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSShaderProperty::Read( in, link_stack, info );
	NifStream( fileName, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void TallGrassShaderProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSShaderProperty::Write( out, link_map, missing_link_stack, info );
	NifStream( fileName, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string TallGrassShaderProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << BSShaderProperty::asString();
	out << "  File Name:  " << fileName << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void TallGrassShaderProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSShaderProperty::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> TallGrassShaderProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = BSShaderProperty::GetRefs();
	return refs;
}

std::list<NiObject *> TallGrassShaderProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = BSShaderProperty::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

string TallGrassShaderProperty::GetFileName() const {
	return fileName;
}

void TallGrassShaderProperty::SetFileName( const string & value ) {
	fileName = value;
}

//--END CUSTOM CODE--//
