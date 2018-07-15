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
#include "../../include/obj/bhkCapsuleShape.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkCapsuleShape::TYPE("bhkCapsuleShape", &bhkConvexShape::TYPE );

bhkCapsuleShape::bhkCapsuleShape() : radius1(0.0f), radius2(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkCapsuleShape::~bhkCapsuleShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkCapsuleShape::GetType() const {
	return TYPE;
}

NiObject * bhkCapsuleShape::Create() {
	return new bhkCapsuleShape;
}

void bhkCapsuleShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkConvexShape::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( unknown8Bytes[i1], in, info );
	};
	NifStream( firstPoint, in, info );
	NifStream( radius1, in, info );
	NifStream( secondPoint, in, info );
	NifStream( radius2, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkCapsuleShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkConvexShape::Write( out, link_map, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( unknown8Bytes[i1], out, info );
	};
	NifStream( firstPoint, out, info );
	NifStream( radius1, out, info );
	NifStream( secondPoint, out, info );
	NifStream( radius2, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkCapsuleShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkConvexShape::asString();
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 8 Bytes[" << i1 << "]:  " << unknown8Bytes[i1] << endl;
		array_output_count++;
	};
	out << "  First Point:  " << firstPoint << endl;
	out << "  Radius 1:  " << radius1 << endl;
	out << "  Second Point:  " << secondPoint << endl;
	out << "  Radius 2:  " << radius2 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkCapsuleShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkConvexShape::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkCapsuleShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkConvexShape::GetRefs();
	return refs;
}

std::list<NiObject *> bhkCapsuleShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkConvexShape::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

float bhkCapsuleShape::GetRadius() const {
	return radius;
}

void bhkCapsuleShape::SetRadius( float value ) {
	radius = value;
}

Vector3 bhkCapsuleShape::GetFirstPoint() const {
	return firstPoint;
}

void bhkCapsuleShape::SetFirstPoint( const Vector3 & value ) {
	firstPoint = value;
}

float bhkCapsuleShape::GetRadius1() const {
	return radius1;
}

void bhkCapsuleShape::SetRadius1( float value ) {
	radius1 = value;
}

Vector3 bhkCapsuleShape::GetSecondPoint() const {
	return secondPoint;
}

void bhkCapsuleShape::SetSecondPoint( const Vector3 & value ) {
	secondPoint = value;
}

float bhkCapsuleShape::GetRadius2() const {
	return radius2;
}

void bhkCapsuleShape::SetRadius2( float value ) {
	radius2 = value;
}

/*! Helper routine for calculating mass properties.
*  \param[in]  density Uniform density of object
*  \param[in]  solid Determines whether the object is assumed to be solid or not
*  \param[out] mass Calculated mass of the object
*  \param[out] center Center of mass
*  \param[out] inertia Mass Inertia Tensor
*  \return Return mass, center, and inertia tensor.
*/
void bhkCapsuleShape::CalcMassProperties(float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia)
{
	Inertia::CalcMassPropertiesCapsule(firstPoint, secondPoint, radius, density, solid, mass, volume, center, inertia);
}

//--END CUSTOM CODE--//
