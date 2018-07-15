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
#include "../../include/obj/bhkNiTriStripsShape.h"
#include "../../include/gen/OblivionColFilter.h"
#include "../../include/obj/NiTriStripsData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkNiTriStripsShape::TYPE("bhkNiTriStripsShape", &bhkShapeCollection::TYPE );

bhkNiTriStripsShape::bhkNiTriStripsShape() : material((HavokMaterial)0), skyrimMaterial((SkyrimHavokMaterial)0), unknownFloat1(0.1f), unknownInt1((unsigned int)0x004ABE60), unknownInt2((unsigned int)1), scale(1.0, 1.0, 1.0), unknownInt3((unsigned int)0), numStripsData((unsigned int)0), numDataLayers((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkNiTriStripsShape::~bhkNiTriStripsShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkNiTriStripsShape::GetType() const {
	return TYPE;
}

NiObject * bhkNiTriStripsShape::Create() {
	return new bhkNiTriStripsShape;
}

void bhkNiTriStripsShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	bhkShapeCollection::Read( in, link_stack, info );
	if ( (info.userVersion < 12) ) {
		NifStream( material, in, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( skyrimMaterial, in, info );
	};
	NifStream( unknownFloat1, in, info );
	NifStream( unknownInt1, in, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknownInts1[i1], in, info );
	};
	NifStream( unknownInt2, in, info );
	NifStream( scale, in, info );
	NifStream( unknownInt3, in, info );
	NifStream( numStripsData, in, info );
	stripsData.resize(numStripsData);
	for (unsigned int i1 = 0; i1 < stripsData.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( numDataLayers, in, info );
	dataLayers.resize(numDataLayers);
	for (unsigned int i1 = 0; i1 < dataLayers.size(); i1++) {
		NifStream( dataLayers[i1].layer, in, info );
		NifStream( dataLayers[i1].colFilter, in, info );
		NifStream( dataLayers[i1].unknownShort, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkNiTriStripsShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShapeCollection::Write( out, link_map, missing_link_stack, info );
	numDataLayers = (unsigned int)(dataLayers.size());
	numStripsData = (unsigned int)(stripsData.size());
	if ( (info.userVersion < 12) ) {
		NifStream( material, out, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( skyrimMaterial, out, info );
	};
	NifStream( unknownFloat1, out, info );
	NifStream( unknownInt1, out, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknownInts1[i1], out, info );
	};
	NifStream( unknownInt2, out, info );
	NifStream( scale, out, info );
	NifStream( unknownInt3, out, info );
	NifStream( numStripsData, out, info );
	for (unsigned int i1 = 0; i1 < stripsData.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*stripsData[i1]), out );
		} else {
			if ( stripsData[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(stripsData[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( stripsData[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( numDataLayers, out, info );
	for (unsigned int i1 = 0; i1 < dataLayers.size(); i1++) {
		NifStream( dataLayers[i1].layer, out, info );
		NifStream( dataLayers[i1].colFilter, out, info );
		NifStream( dataLayers[i1].unknownShort, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkNiTriStripsShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkShapeCollection::asString();
	numDataLayers = (unsigned int)(dataLayers.size());
	numStripsData = (unsigned int)(stripsData.size());
	out << "  Material:  " << material << endl;
	out << "  Skyrim Material:  " << skyrimMaterial << endl;
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Ints 1[" << i1 << "]:  " << unknownInts1[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Scale:  " << scale << endl;
	out << "  Unknown Int 3:  " << unknownInt3 << endl;
	out << "  Num Strips Data:  " << numStripsData << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < stripsData.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Strips Data[" << i1 << "]:  " << stripsData[i1] << endl;
		array_output_count++;
	};
	out << "  Num Data Layers:  " << numDataLayers << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < dataLayers.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Layer:  " << dataLayers[i1].layer << endl;
		out << "    Col Filter:  " << dataLayers[i1].colFilter << endl;
		out << "    Unknown Short:  " << dataLayers[i1].unknownShort << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkNiTriStripsShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShapeCollection::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < stripsData.size(); i1++) {
		stripsData[i1] = FixLink<NiTriStripsData>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkNiTriStripsShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkShapeCollection::GetRefs();
	for (unsigned int i1 = 0; i1 < stripsData.size(); i1++) {
		if ( stripsData[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(stripsData[i1]));
	};
	return refs;
}

std::list<NiObject *> bhkNiTriStripsShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkShapeCollection::GetPtrs();
	for (unsigned int i1 = 0; i1 < stripsData.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

int bhkNiTriStripsShape::GetNumStripsData( )
{
	return numStripsData;
}

void bhkNiTriStripsShape::SetNumStripsData(int n)
{
	numStripsData = n;
	stripsData.resize(n);
}

Ref<NiTriStripsData> bhkNiTriStripsShape::GetStripsData( int index )
{
	return Ref<NiTriStripsData>(stripsData[index]);
}

void bhkNiTriStripsShape::SetStripsData( int index, NiTriStripsData * strips )
{
	stripsData[index] = strips;
}



Vector3 bhkNiTriStripsShape::GetScale() const {
	return scale;
}

void bhkNiTriStripsShape::SetScale( const Vector3 & n ) {
	scale = n;	
}

HavokMaterial bhkNiTriStripsShape::GetMaterial() const {
	return material;
}

void bhkNiTriStripsShape::SetMaterial( HavokMaterial value ) {
	material = value;
}

unsigned int bhkNiTriStripsShape::GetNumDataLayers() const {
	return numDataLayers;
}

void bhkNiTriStripsShape::SetNumDataLayers( unsigned int i ) {
	numDataLayers = i;
	dataLayers.resize(i);
}

OblivionLayer bhkNiTriStripsShape::GetOblivionLayer( unsigned int index ) const {
	return dataLayers[index].layer;
}

void bhkNiTriStripsShape::SetOblivionLayer( unsigned int index, OblivionLayer layer ){
	dataLayers[index].layer = layer;
}

unsigned char bhkNiTriStripsShape::GetOblivionFilter( unsigned int index ) const {
	return dataLayers[index].colFilter;
}

void bhkNiTriStripsShape::SetOblivionFilter( unsigned int index, unsigned char filter ) {
	dataLayers[index].colFilter = filter;
}

void bhkNiTriStripsShape::CalcMassProperties(float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia)
{
	center = Vector3(0,0,0);
	mass = 0.0f, volume = 0.0f;
	inertia = InertiaMatrix::IDENTITY;

	vector<Vector3> verts;
	vector<Triangle> tris;
	for ( vector<NiTriStripsDataRef>::iterator itr = stripsData.begin(); itr != stripsData.end(); ++itr )
	{
		size_t nv = verts.size(), nt = tris.size();
		vector<Vector3> v = (*itr)->GetVertices();
		vector<Triangle> t = (*itr)->GetTriangles();
		for (size_t i=0; i<nv; ++i)
			verts.push_back( v[i] );
		for (size_t i=0; i<nt; ++i)
			tris.push_back( Triangle(t[i][0] + nt, t[i][1] + nt, t[i][2] + nt) );
	}
	Inertia::CalcMassPropertiesPolyhedron(verts, tris, density, solid, mass, volume, center, inertia);
}
//--END CUSTOM CODE--//
