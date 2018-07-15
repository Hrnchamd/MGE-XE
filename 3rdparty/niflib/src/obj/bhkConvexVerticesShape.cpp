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
#include "../../include/obj/bhkConvexVerticesShape.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkConvexVerticesShape::TYPE("bhkConvexVerticesShape", &bhkConvexShape::TYPE );

bhkConvexVerticesShape::bhkConvexVerticesShape() : numVertices((unsigned int)0), numNormals((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkConvexVerticesShape::~bhkConvexVerticesShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkConvexVerticesShape::GetType() const {
	return TYPE;
}

NiObject * bhkConvexVerticesShape::Create() {
	return new bhkConvexVerticesShape;
}

void bhkConvexVerticesShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkConvexShape::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 6; i1++) {
		NifStream( unknown6Floats[i1], in, info );
	};
	NifStream( numVertices, in, info );
	vertices.resize(numVertices);
	for (unsigned int i1 = 0; i1 < vertices.size(); i1++) {
		NifStream( vertices[i1], in, info );
	};
	NifStream( numNormals, in, info );
	normals.resize(numNormals);
	for (unsigned int i1 = 0; i1 < normals.size(); i1++) {
		NifStream( normals[i1], in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkConvexVerticesShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkConvexShape::Write( out, link_map, missing_link_stack, info );
	numNormals = (unsigned int)(normals.size());
	numVertices = (unsigned int)(vertices.size());
	for (unsigned int i1 = 0; i1 < 6; i1++) {
		NifStream( unknown6Floats[i1], out, info );
	};
	NifStream( numVertices, out, info );
	for (unsigned int i1 = 0; i1 < vertices.size(); i1++) {
		NifStream( vertices[i1], out, info );
	};
	NifStream( numNormals, out, info );
	for (unsigned int i1 = 0; i1 < normals.size(); i1++) {
		NifStream( normals[i1], out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkConvexVerticesShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkConvexShape::asString();
	numNormals = (unsigned int)(normals.size());
	numVertices = (unsigned int)(vertices.size());
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 6; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 6 Floats[" << i1 << "]:  " << unknown6Floats[i1] << endl;
		array_output_count++;
	};
	out << "  Num Vertices:  " << numVertices << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < vertices.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Vertices[" << i1 << "]:  " << vertices[i1] << endl;
		array_output_count++;
	};
	out << "  Num Normals:  " << numNormals << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < normals.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Normals[" << i1 << "]:  " << normals[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkConvexVerticesShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkConvexShape::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkConvexVerticesShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkConvexShape::GetRefs();
	return refs;
}

std::list<NiObject *> bhkConvexVerticesShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkConvexShape::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
vector<Vector3> bhkConvexVerticesShape::GetNormals() const {
	//Remove any bad triangles
	vector<Vector3> good_normals;
	for ( unsigned i = 0; i < normals.size(); ++i ) {
		const Vector4 & t = normals[i];
		Vector3 v(t[0], t[1], t[2]);
		good_normals.push_back(v);
	}
	return good_normals;
}

int bhkConvexVerticesShape::GetVertexCount() const {
	return vertices.size();
}

vector<Vector3> bhkConvexVerticesShape::GetVertices() const {
	//Remove any bad triangles
	vector<Vector3> good_vertices;
	for ( unsigned i = 0; i < vertices.size(); ++i ) {
		const Vector4 & t = vertices[i];
		Vector3 v(t[0], t[1], t[2]); 
		good_vertices.push_back(v);
	}
	return good_vertices;
}

vector<float> bhkConvexVerticesShape::GetDistToCenter() const 
{
	//Remove any bad triangles
	vector<float> good_dist;
	for ( unsigned i = 0; i < normals.size(); ++i ) {
		good_dist.push_back(normals[i][3]);
	}
	return good_dist;
}

void bhkConvexVerticesShape::SetVertices( const vector<Vector3> & in )
{
	size_t size = in.size();
	vertices.resize(size);
	for (size_t i=0; i<size; ++i)
	{
		Vector4 &f = vertices[i];
		const Vector3 &v = in[i];

		f[0] = v.x;
		f[1] = v.y;
		f[2] = v.z;
		f[3] = 0.0f;
	}
}

void bhkConvexVerticesShape::SetNormals( const vector<Vector3> & in )
{
	size_t size = in.size();
	normals.resize(size);
	for (size_t i=0; i<size; ++i)
	{
		Vector4 &f = normals[i];
		const Vector3 &v = in[i];

		f[0] = v.x;
		f[1] = v.y;
		f[2] = v.z;
		f[3] = 0.0f;
	}
}

void bhkConvexVerticesShape::SetDistToCenter( const vector<float> & in )
{
	if ( in.size() != normals.size() ) {
		throw runtime_error("Distance vector size does not match normal size.");
	}

	size_t size = in.size();
	normals.resize(size);
	for (size_t i=0; i<size; ++i)
	{
		Vector4 &f = normals[i];

		f[3] = in[i];
	}
}

vector<Vector4> bhkConvexVerticesShape::GetNormalsAndDist() const
{
	return normals;
}

void bhkConvexVerticesShape::SetNormalsAndDist(const vector<Vector4>& value) 
{
	normals = value;
}

void bhkConvexVerticesShape::CalcMassProperties(float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia)
{
	center = Vector3(0,0,0);
	mass = 0.0f, volume = 0.0f;
	inertia = InertiaMatrix::IDENTITY;
	vector<Vector3> verts = GetVertices();
	vector<Triangle> tris; // no tris mean convex
	Inertia::CalcMassPropertiesPolyhedron(verts, tris, density, solid, mass, volume, center, inertia);
}
//--END CUSTOM CODE--//
