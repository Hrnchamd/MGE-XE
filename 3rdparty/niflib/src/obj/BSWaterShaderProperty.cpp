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
#include "../../include/obj/BSWaterShaderProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSWaterShaderProperty::TYPE("BSWaterShaderProperty", &NiProperty::TYPE );

BSWaterShaderProperty::BSWaterShaderProperty() : shaderFlags1((SkyrimShaderPropertyFlags1)0), shaderFlags2((SkyrimShaderPropertyFlags2)0), uvScale(1.0, 1.0), waterShaderFlags((SkyrimWaterShaderFlags)0), waterDirection((byte)3), unknownShort3((unsigned short)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSWaterShaderProperty::~BSWaterShaderProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSWaterShaderProperty::GetType() const {
	return TYPE;
}

NiObject * BSWaterShaderProperty::Create() {
	return new BSWaterShaderProperty;
}

void BSWaterShaderProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiProperty::Read( in, link_stack, info );
	NifStream( shaderFlags1, in, info );
	NifStream( shaderFlags2, in, info );
	NifStream( uvOffset, in, info );
	NifStream( uvScale, in, info );
	NifStream( waterShaderFlags, in, info );
	NifStream( waterDirection, in, info );
	NifStream( unknownShort3, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSWaterShaderProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiProperty::Write( out, link_map, missing_link_stack, info );
	NifStream( shaderFlags1, out, info );
	NifStream( shaderFlags2, out, info );
	NifStream( uvOffset, out, info );
	NifStream( uvScale, out, info );
	NifStream( waterShaderFlags, out, info );
	NifStream( waterDirection, out, info );
	NifStream( unknownShort3, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSWaterShaderProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiProperty::asString();
	out << "  Shader Flags 1:  " << shaderFlags1 << endl;
	out << "  Shader Flags 2:  " << shaderFlags2 << endl;
	out << "  UV Offset:  " << uvOffset << endl;
	out << "  UV Scale:  " << uvScale << endl;
	out << "  Water Shader Flags:  " << waterShaderFlags << endl;
	out << "  Water Direction:  " << waterDirection << endl;
	out << "  Unknown Short 3:  " << unknownShort3 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSWaterShaderProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiProperty::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSWaterShaderProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiProperty::GetRefs();
	return refs;
}

std::list<NiObject *> BSWaterShaderProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiProperty::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
