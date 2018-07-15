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
#include "../../include/obj/bhkTransformShape.h"
#include "../../include/obj/bhkShape.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkTransformShape::TYPE("bhkTransformShape", &bhkShape::TYPE );

bhkTransformShape::bhkTransformShape() : shape(NULL), material((HavokMaterial)0), skyrimMaterial((SkyrimHavokMaterial)0), unknownFloat1(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkTransformShape::~bhkTransformShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkTransformShape::GetType() const {
	return TYPE;
}

NiObject * bhkTransformShape::Create() {
	return new bhkTransformShape;
}

void bhkTransformShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	bhkShape::Read( in, link_stack, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	if ( (info.userVersion < 12) ) {
		NifStream( material, in, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( skyrimMaterial, in, info );
	};
	NifStream( unknownFloat1, in, info );
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( unknown8Bytes[i1], in, info );
	};
	NifStream( transform, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkTransformShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShape::Write( out, link_map, missing_link_stack, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*shape), out );
	} else {
		if ( shape != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(shape) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( shape );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( (info.userVersion < 12) ) {
		NifStream( material, out, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( skyrimMaterial, out, info );
	};
	NifStream( unknownFloat1, out, info );
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( unknown8Bytes[i1], out, info );
	};
	NifStream( transform, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkTransformShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkShape::asString();
	out << "  Shape:  " << shape << endl;
	out << "  Material:  " << material << endl;
	out << "  Skyrim Material:  " << skyrimMaterial << endl;
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
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
	out << "  Transform:  " << transform << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkTransformShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShape::FixLinks( objects, link_stack, missing_link_stack, info );
	shape = FixLink<bhkShape>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkTransformShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkShape::GetRefs();
	if ( shape != NULL )
		refs.push_back(StaticCast<NiObject>(shape));
	return refs;
}

std::list<NiObject *> bhkTransformShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkShape::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Ref<bhkShape > bhkTransformShape::GetShape() const {
	return shape;
}

void bhkTransformShape::SetShape( bhkShape * value ) {
	shape = value;
}

HavokMaterial bhkTransformShape::GetMaterial() const {
	return material;
}

void bhkTransformShape::SetMaterial( HavokMaterial value ) {
	material = value;
}

Matrix44 bhkTransformShape::GetTransform() const {
	return transform;
}

void bhkTransformShape::SetTransform(const Matrix44 & value ) {
	transform = value;
}

void bhkTransformShape::CalcMassProperties(float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia)
{
	center = transform.GetTranslation();
	mass = 0.0f, volume = 0.0f;
	inertia = InertiaMatrix::IDENTITY;
	if (shape != NULL)
	{
		Matrix44 transform_transposed = transform.Transpose();
		shape->CalcMassProperties(density, solid, mass, volume, center, inertia);
		center = transform * center;

		Matrix44 tm(inertia.Submatrix(0, 0));
		Matrix44 im = transform_transposed * tm * transform;
		inertia = InertiaMatrix(im.GetRotation());
	}
}
//--END CUSTOM CODE--//
