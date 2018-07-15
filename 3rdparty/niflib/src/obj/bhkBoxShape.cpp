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
#include "../../include/obj/bhkBoxShape.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkBoxShape::TYPE("bhkBoxShape", &bhkConvexShape::TYPE );

bhkBoxShape::bhkBoxShape() : minimumSize(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkBoxShape::~bhkBoxShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkBoxShape::GetType() const {
	return TYPE;
}

NiObject * bhkBoxShape::Create() {
	return new bhkBoxShape;
}

void bhkBoxShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkConvexShape::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( unknown8Bytes[i1], in, info );
	};
	NifStream( dimensions, in, info );
	NifStream( minimumSize, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkBoxShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkConvexShape::Write( out, link_map, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( unknown8Bytes[i1], out, info );
	};
	NifStream( dimensions, out, info );
	NifStream( minimumSize, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkBoxShape::asString( bool verbose ) const {
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
	out << "  Dimensions:  " << dimensions << endl;
	out << "  Minimum Size:  " << minimumSize << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkBoxShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkConvexShape::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkBoxShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkConvexShape::GetRefs();
	return refs;
}

std::list<NiObject *> bhkBoxShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkConvexShape::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Vector3 bhkBoxShape::GetDimensions() const {
	return dimensions;
}

void bhkBoxShape::SetDimensions(const Vector3 &value) {
	dimensions = value;
	minimumSize = min( min(value.x, value.y), value.z );
}

void bhkBoxShape::CalcMassProperties( float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia )
{
	Inertia::CalcMassPropertiesBox( dimensions, density, solid, mass, volume, center, inertia ); 
}
//--END CUSTOM CODE--//
