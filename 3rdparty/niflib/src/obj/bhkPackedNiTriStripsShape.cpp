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
#include "../../include/obj/bhkPackedNiTriStripsShape.h"
#include "../../include/gen/OblivionSubShape.h"
#include "../../include/obj/hkPackedNiTriStripsData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkPackedNiTriStripsShape::TYPE("bhkPackedNiTriStripsShape", &bhkShapeCollection::TYPE );

bhkPackedNiTriStripsShape::bhkPackedNiTriStripsShape() : numSubShapes((unsigned short)0), unknownInt1((unsigned int)0), unknownInt2((unsigned int)0x014E9DD8), unknownFloat1(0.1f), unknownInt3((unsigned int)0), scaleCopy_(1.0, 1.0, 1.0), unknownFloat2(0.0f), unknownFloat3(0.1f), scale(1.0, 1.0, 1.0), unknownFloat4(0.0f), data(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkPackedNiTriStripsShape::~bhkPackedNiTriStripsShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkPackedNiTriStripsShape::GetType() const {
	return TYPE;
}

NiObject * bhkPackedNiTriStripsShape::Create() {
	return new bhkPackedNiTriStripsShape;
}

void bhkPackedNiTriStripsShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	bhkShapeCollection::Read( in, link_stack, info );
	if ( info.version <= 0x14000005 ) {
		NifStream( numSubShapes, in, info );
		subShapes.resize(numSubShapes);
		for (unsigned int i2 = 0; i2 < subShapes.size(); i2++) {
			NifStream( subShapes[i2].layer, in, info );
			NifStream( subShapes[i2].colFilter, in, info );
			NifStream( subShapes[i2].unknownShort, in, info );
			NifStream( subShapes[i2].numVertices, in, info );
			NifStream( subShapes[i2].material, in, info );
		};
	};
	NifStream( unknownInt1, in, info );
	NifStream( unknownInt2, in, info );
	NifStream( unknownFloat1, in, info );
	NifStream( unknownInt3, in, info );
	NifStream( scaleCopy_, in, info );
	NifStream( unknownFloat2, in, info );
	NifStream( unknownFloat3, in, info );
	NifStream( scale, in, info );
	NifStream( unknownFloat4, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkPackedNiTriStripsShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShapeCollection::Write( out, link_map, missing_link_stack, info );
	numSubShapes = (unsigned short)(subShapes.size());
	if ( info.version <= 0x14000005 ) {
		NifStream( numSubShapes, out, info );
		for (unsigned int i2 = 0; i2 < subShapes.size(); i2++) {
			NifStream( subShapes[i2].layer, out, info );
			NifStream( subShapes[i2].colFilter, out, info );
			NifStream( subShapes[i2].unknownShort, out, info );
			NifStream( subShapes[i2].numVertices, out, info );
			NifStream( subShapes[i2].material, out, info );
		};
	};
	NifStream( unknownInt1, out, info );
	NifStream( unknownInt2, out, info );
	NifStream( unknownFloat1, out, info );
	NifStream( unknownInt3, out, info );
	NifStream( scaleCopy_, out, info );
	NifStream( unknownFloat2, out, info );
	NifStream( unknownFloat3, out, info );
	NifStream( scale, out, info );
	NifStream( unknownFloat4, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*data), out );
	} else {
		if ( data != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(data) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( data );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkPackedNiTriStripsShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkShapeCollection::asString();
	numSubShapes = (unsigned short)(subShapes.size());
	out << "  Num Sub Shapes:  " << numSubShapes << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < subShapes.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Layer:  " << subShapes[i1].layer << endl;
		out << "    Col Filter:  " << subShapes[i1].colFilter << endl;
		out << "    Unknown Short:  " << subShapes[i1].unknownShort << endl;
		out << "    Num Vertices:  " << subShapes[i1].numVertices << endl;
		out << "    Material:  " << subShapes[i1].material << endl;
	};
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Unknown Int 3:  " << unknownInt3 << endl;
	out << "  Scale Copy?:  " << scaleCopy_ << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Unknown Float 3:  " << unknownFloat3 << endl;
	out << "  Scale:  " << scale << endl;
	out << "  Unknown Float 4:  " << unknownFloat4 << endl;
	out << "  Data:  " << data << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkPackedNiTriStripsShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShapeCollection::FixLinks( objects, link_stack, missing_link_stack, info );
	data = FixLink<hkPackedNiTriStripsData>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkPackedNiTriStripsShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkShapeCollection::GetRefs();
	if ( data != NULL )
		refs.push_back(StaticCast<NiObject>(data));
	return refs;
}

std::list<NiObject *> bhkPackedNiTriStripsShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkShapeCollection::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
Ref<hkPackedNiTriStripsData> bhkPackedNiTriStripsShape::GetData() const {
	return data;
}

void bhkPackedNiTriStripsShape::SetData( hkPackedNiTriStripsData * n ) {
	data = n;
}

vector<OblivionSubShape> bhkPackedNiTriStripsShape::GetSubShapes() const {
	return subShapes;
}

void bhkPackedNiTriStripsShape::SetSubShapes( vector<OblivionSubShape>& value ) {
	numSubShapes = value.size();
	subShapes = value;
}

Vector3 bhkPackedNiTriStripsShape::GetScale() const {
	return scale;
}

void bhkPackedNiTriStripsShape::SetScale( const Vector3 & n ) {
	scale = n;	
}

void bhkPackedNiTriStripsShape::CalcMassProperties(float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia)
{
	center = Vector3(0,0,0);
	mass = 0.0f, volume = 0.0f;
	inertia = InertiaMatrix::IDENTITY;

	if (data != NULL)
	{
		vector<Vector3> verts = data->GetVertices();
		vector<Triangle> tris = data->GetTriangles();
		Inertia::CalcMassPropertiesPolyhedron(verts, tris, density, solid, mass, volume, center, inertia);
	}
}
//--END CUSTOM CODE--//
