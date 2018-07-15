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
#include "../../include/obj/NiTriShapeData.h"
#include "../../include/gen/MatchGroup.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiTriShapeData::TYPE("NiTriShapeData", &NiTriBasedGeomData::TYPE );

NiTriShapeData::NiTriShapeData() : numTrianglePoints((unsigned int)0), hasTriangles(false), numMatchGroups((unsigned short)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiTriShapeData::~NiTriShapeData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiTriShapeData::GetType() const {
	return TYPE;
}

NiObject * NiTriShapeData::Create() {
	return new NiTriShapeData;
}

void NiTriShapeData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTriBasedGeomData::Read( in, link_stack, info );
	NifStream( numTrianglePoints, in, info );
	if ( info.version >= 0x0A010000 ) {
		NifStream( hasTriangles, in, info );
	};
	if ( info.version <= 0x0A000102 ) {
		triangles.resize(numTriangles);
		hasTriangles = (triangles.size() > 0);
		for (unsigned int i2 = 0; i2 < triangles.size(); i2++) {
			NifStream( triangles[i2], in, info );
		};
	};
	if ( info.version >= 0x0A000103 ) {
		if ( hasTriangles ) {
			triangles.resize(numTriangles);
			for (unsigned int i3 = 0; i3 < triangles.size(); i3++) {
				NifStream( triangles[i3], in, info );
			};
		};
	};
	if ( info.version >= 0x03010000 ) {
		NifStream( numMatchGroups, in, info );
		matchGroups.resize(numMatchGroups);
		for (unsigned int i2 = 0; i2 < matchGroups.size(); i2++) {
			NifStream( matchGroups[i2].numVertices, in, info );
			matchGroups[i2].vertexIndices.resize(matchGroups[i2].numVertices);
			for (unsigned int i3 = 0; i3 < matchGroups[i2].vertexIndices.size(); i3++) {
				NifStream( matchGroups[i2].vertexIndices[i3], in, info );
			};
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTriShapeData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTriBasedGeomData::Write( out, link_map, missing_link_stack, info );
	numMatchGroups = (unsigned short)(matchGroups.size());
	hasTriangles = hasTrianglesCalc(info);
	NifStream( numTrianglePoints, out, info );
	if ( info.version >= 0x0A010000 ) {
		NifStream( hasTriangles, out, info );
	};
	if ( info.version <= 0x0A000102 ) {
		for (unsigned int i2 = 0; i2 < triangles.size(); i2++) {
			NifStream( triangles[i2], out, info );
		};
	};
	if ( info.version >= 0x0A000103 ) {
		if ( hasTriangles ) {
			for (unsigned int i3 = 0; i3 < triangles.size(); i3++) {
				NifStream( triangles[i3], out, info );
			};
		};
	};
	if ( info.version >= 0x03010000 ) {
		NifStream( numMatchGroups, out, info );
		for (unsigned int i2 = 0; i2 < matchGroups.size(); i2++) {
			matchGroups[i2].numVertices = (unsigned short)(matchGroups[i2].vertexIndices.size());
			NifStream( matchGroups[i2].numVertices, out, info );
			for (unsigned int i3 = 0; i3 < matchGroups[i2].vertexIndices.size(); i3++) {
				NifStream( matchGroups[i2].vertexIndices[i3], out, info );
			};
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiTriShapeData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiTriBasedGeomData::asString();
	numMatchGroups = (unsigned short)(matchGroups.size());
	out << "  Num Triangle Points:  " << numTrianglePoints << endl;
	out << "  Has Triangles:  " << hasTriangles << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < triangles.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Triangles[" << i1 << "]:  " << triangles[i1] << endl;
		array_output_count++;
	};
	out << "  Num Match Groups:  " << numMatchGroups << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < matchGroups.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		matchGroups[i1].numVertices = (unsigned short)(matchGroups[i1].vertexIndices.size());
		out << "    Num Vertices:  " << matchGroups[i1].numVertices << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < matchGroups[i1].vertexIndices.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Vertex Indices[" << i2 << "]:  " << matchGroups[i1].vertexIndices[i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTriShapeData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTriBasedGeomData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiTriShapeData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiTriBasedGeomData::GetRefs();
	return refs;
}

std::list<NiObject *> NiTriShapeData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiTriBasedGeomData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

NiTriShapeData::NiTriShapeData(const vector<Triangle> &tris) {
   SetTriangles(tris);
}

void NiTriShapeData::SetVertices( const vector<Vector3> & in ) {
	//Take normal action
	NiTriBasedGeomData::SetVertices( in );

	//Also, clear match detection data
	RemoveMatchData();
}

void NiTriShapeData::DoMatchDetection() {
	/* minimum number of groups of shared normals */
	matchGroups.resize( 0 );
	/* counting sharing */
	vector<bool> is_shared( vertices.size(), false );

	for ( unsigned short i = 0; i < vertices.size() - 1; ++i ) {
		/* this index belongs to a group already */
		if ( is_shared[i] )
			continue;

		/* we may find a valid group for this vertex */
		MatchGroup group;
		/* this vertex belongs to the group as well */
		group.vertexIndices.push_back(i);

		// Find all vertices that match this one.
		for ( unsigned short j = i + 1; j < vertices.size(); ++j ) {
			/* this index belongs to another group already */
			/* so its vert/norm cannot match this group! */
			if ( is_shared[j] )
				continue;
			/* for automatic regeneration we just consider
			 * identical positions, though the format would
			 * allow distinct positions to share a normal
			 */
			if ( vertices[j] != vertices[i] )
				continue;
			if ( normals [j] != normals [i] )
				continue;
			/* remember this vertex' index */
			group.vertexIndices.push_back(j);
		}

		/* the currently observed vertex shares a normal with others */
		if ( ( group.numVertices = group.vertexIndices.size() ) > 1 ) {
			/* mark all of the participating vertices to belong to a group */
			for ( unsigned short n = 0; n < group.numVertices; n++ )
				is_shared[group.vertexIndices[n]] = true;

			/* register the group */
			matchGroups.push_back(group);
		}
	}
}

void NiTriShapeData::RemoveMatchData() { 
	matchGroups.clear();
}

bool NiTriShapeData::HasMatchData() {
	return ( matchGroups.size() > 0 );
}

vector<Triangle> NiTriShapeData::GetTriangles() const {
	//Remove any bad triangles
	vector<Triangle> good_triangles;
	for ( unsigned i = 0; i < triangles.size(); ++i ) {
		const Triangle & t = triangles[i];
		if ( t.v1 != t.v2 && t.v2 != t.v3 && t.v1 != t.v3 ) {
			good_triangles.push_back(t);
		}
	}
	return good_triangles;
}

void NiTriShapeData::SetTriangles( const vector<Triangle> & in ) {
	if ( in.size() > 65535 || in.size() < 0 ) {
		throw runtime_error("Invalid Triangle Count: must be between 0 and 65535.");
	}

	triangles = in;

	hasTriangles = ( triangles.size() != 0 );

	//Set nuber of triangles
	numTriangles = (unsigned int)(triangles.size());

	//Set number of trianble points to the number of triangles times 3
	numTrianglePoints = numTriangles * 3;
}

//--END CUSTOM CODE--//
