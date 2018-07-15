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
#include "../../include/obj/bhkConvexTransformShape.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkConvexTransformShape::TYPE("bhkConvexTransformShape", &bhkTransformShape::TYPE );

bhkConvexTransformShape::bhkConvexTransformShape() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkConvexTransformShape::~bhkConvexTransformShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkConvexTransformShape::GetType() const {
	return TYPE;
}

NiObject * bhkConvexTransformShape::Create() {
	return new bhkConvexTransformShape;
}

void bhkConvexTransformShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkTransformShape::Read( in, link_stack, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkConvexTransformShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkTransformShape::Write( out, link_map, missing_link_stack, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkConvexTransformShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << bhkTransformShape::asString();
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkConvexTransformShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkTransformShape::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkConvexTransformShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkTransformShape::GetRefs();
	return refs;
}

std::list<NiObject *> bhkConvexTransformShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkTransformShape::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
void bhkConvexTransformShape::CalcMassProperties(float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia)
{
	center = Vector3(0,0,0);
	mass = 0.0f, volume = 0.0f;
	inertia = InertiaMatrix::IDENTITY;
}


//--END CUSTOM CODE--//
