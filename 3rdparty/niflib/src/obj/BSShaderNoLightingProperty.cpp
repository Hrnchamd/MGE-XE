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
#include "../../include/obj/BSShaderNoLightingProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSShaderNoLightingProperty::TYPE("BSShaderNoLightingProperty", &BSShaderLightingProperty::TYPE );

BSShaderNoLightingProperty::BSShaderNoLightingProperty() : unknownFloat2(1.0f), unknownFloat3(0.0f), unknownFloat4(1.0f), unknownFloat5(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSShaderNoLightingProperty::~BSShaderNoLightingProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSShaderNoLightingProperty::GetType() const {
	return TYPE;
}

NiObject * BSShaderNoLightingProperty::Create() {
	return new BSShaderNoLightingProperty;
}

void BSShaderNoLightingProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSShaderLightingProperty::Read( in, link_stack, info );
	NifStream( fileName, in, info );
	if ( ((info.userVersion >= 11) && (info.userVersion2 > 26)) ) {
		NifStream( unknownFloat2, in, info );
		NifStream( unknownFloat3, in, info );
		NifStream( unknownFloat4, in, info );
		NifStream( unknownFloat5, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSShaderNoLightingProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSShaderLightingProperty::Write( out, link_map, missing_link_stack, info );
	NifStream( fileName, out, info );
	if ( ((info.userVersion >= 11) && (info.userVersion2 > 26)) ) {
		NifStream( unknownFloat2, out, info );
		NifStream( unknownFloat3, out, info );
		NifStream( unknownFloat4, out, info );
		NifStream( unknownFloat5, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSShaderNoLightingProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << BSShaderLightingProperty::asString();
	out << "  File Name:  " << fileName << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Unknown Float 3:  " << unknownFloat3 << endl;
	out << "  Unknown Float 4:  " << unknownFloat4 << endl;
	out << "  Unknown Float 5:  " << unknownFloat5 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSShaderNoLightingProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	BSShaderLightingProperty::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSShaderNoLightingProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = BSShaderLightingProperty::GetRefs();
	return refs;
}

std::list<NiObject *> BSShaderNoLightingProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = BSShaderLightingProperty::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

string BSShaderNoLightingProperty::GetFileName() const {
	return fileName;
}

void BSShaderNoLightingProperty::SetFileName( const string & value ) {
	fileName = value;
}

//--END CUSTOM CODE--//
