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
#include "../../include/obj/bhkMultiSphereShape.h"
#include "../../include/gen/SphereBV.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkMultiSphereShape::TYPE("bhkMultiSphereShape", &bhkSphereRepShape::TYPE );

bhkMultiSphereShape::bhkMultiSphereShape() : unknownFloat1(0.0f), unknownFloat2(0.0f), numSpheres((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkMultiSphereShape::~bhkMultiSphereShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkMultiSphereShape::GetType() const {
	return TYPE;
}

NiObject * bhkMultiSphereShape::Create() {
	return new bhkMultiSphereShape;
}

void bhkMultiSphereShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkSphereRepShape::Read( in, link_stack, info );
	NifStream( unknownFloat1, in, info );
	NifStream( unknownFloat2, in, info );
	NifStream( numSpheres, in, info );
	spheres.resize(numSpheres);
	for (unsigned int i1 = 0; i1 < spheres.size(); i1++) {
		NifStream( spheres[i1].center, in, info );
		NifStream( spheres[i1].radius, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkMultiSphereShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkSphereRepShape::Write( out, link_map, missing_link_stack, info );
	numSpheres = (unsigned int)(spheres.size());
	NifStream( unknownFloat1, out, info );
	NifStream( unknownFloat2, out, info );
	NifStream( numSpheres, out, info );
	for (unsigned int i1 = 0; i1 < spheres.size(); i1++) {
		NifStream( spheres[i1].center, out, info );
		NifStream( spheres[i1].radius, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkMultiSphereShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkSphereRepShape::asString();
	numSpheres = (unsigned int)(spheres.size());
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Num Spheres:  " << numSpheres << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < spheres.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Center:  " << spheres[i1].center << endl;
		out << "    Radius:  " << spheres[i1].radius << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkMultiSphereShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkSphereRepShape::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkMultiSphereShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkSphereRepShape::GetRefs();
	return refs;
}

std::list<NiObject *> bhkMultiSphereShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkSphereRepShape::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

vector<SphereBV > bhkMultiSphereShape::GetSpheres() const {
	return spheres;
}

void bhkMultiSphereShape::SetSpheres( const vector<SphereBV >& value ) {
	spheres = value;
}

void bhkMultiSphereShape::CalcMassProperties(float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia)
{
	// TODO: Calculate this properly
	center = Vector3(0,0,0);
	mass = 0.0f, volume = 0.0f;
	inertia = InertiaMatrix::IDENTITY;
}
//--END CUSTOM CODE--//
