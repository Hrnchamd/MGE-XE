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
#include "../../include/obj/bhkBvTreeShape.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkBvTreeShape::TYPE("bhkBvTreeShape", &bhkShape::TYPE );

bhkBvTreeShape::bhkBvTreeShape() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkBvTreeShape::~bhkBvTreeShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkBvTreeShape::GetType() const {
	return TYPE;
}

NiObject * bhkBvTreeShape::Create() {
	return new bhkBvTreeShape;
}

void bhkBvTreeShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShape::Read( in, link_stack, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkBvTreeShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShape::Write( out, link_map, missing_link_stack, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkBvTreeShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << bhkShape::asString();
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkBvTreeShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShape::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkBvTreeShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkShape::GetRefs();
	return refs;
}

std::list<NiObject *> bhkBvTreeShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkShape::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
void bhkBvTreeShape::CalcMassProperties( float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia )
{
	center = Vector3(0,0,0);
	mass = 0.0f, volume = 0.0f;
	inertia = InertiaMatrix::IDENTITY;
}

//--END CUSTOM CODE--//
