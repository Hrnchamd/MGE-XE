/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include "../../include/Inertia.h"
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/bhkSphereRepShape.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkSphereRepShape::TYPE("bhkSphereRepShape", &bhkShape::TYPE );

bhkSphereRepShape::bhkSphereRepShape() : material((HavokMaterial)0), skyrimMaterial((SkyrimHavokMaterial)0), radius(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkSphereRepShape::~bhkSphereRepShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkSphereRepShape::GetType() const {
	return TYPE;
}

NiObject * bhkSphereRepShape::Create() {
	return new bhkSphereRepShape;
}

void bhkSphereRepShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShape::Read( in, link_stack, info );
	if ( (info.userVersion < 12) ) {
		NifStream( material, in, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( skyrimMaterial, in, info );
	};
	NifStream( radius, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkSphereRepShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShape::Write( out, link_map, missing_link_stack, info );
	if ( (info.userVersion < 12) ) {
		NifStream( material, out, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( skyrimMaterial, out, info );
	};
	NifStream( radius, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkSphereRepShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << bhkShape::asString();
	out << "  Material:  " << material << endl;
	out << "  Skyrim Material:  " << skyrimMaterial << endl;
	out << "  Radius:  " << radius << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkSphereRepShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShape::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkSphereRepShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkShape::GetRefs();
	return refs;
}

std::list<NiObject *> bhkSphereRepShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkShape::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

HavokMaterial bhkSphereRepShape::GetMaterial() const {
	return material;
}

void bhkSphereRepShape::SetMaterial( HavokMaterial value ) {
	material = value;
}

SkyrimHavokMaterial bhkSphereRepShape::GetSkyrimMaterial() const {
	return skyrimMaterial;
}

void bhkSphereRepShape::SetSkyrimMaterial( SkyrimHavokMaterial value ) {
	skyrimMaterial = value;
}

float bhkSphereRepShape::GetRadius() const {
	return radius;
}

void bhkSphereRepShape::SetRadius( float value ) {
	radius = value;
}

void bhkSphereRepShape::CalcMassProperties(float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia)
{
	center = Vector3(0,0,0);
	mass = 0.0f, volume = 0.0f;
	inertia = InertiaMatrix::IDENTITY;
	Inertia::CalcMassPropertiesSphere(radius, density, solid, mass, volume, center, inertia);

}
//--END CUSTOM CODE--//
