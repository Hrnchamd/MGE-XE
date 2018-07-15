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
#include "../../include/obj/NiGeometryData.h"
#include "../../include/obj/AbstractAdditionalGeometryData.h"
#include "../../include/obj/NiPSysData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiGeometryData::TYPE("NiGeometryData", &NiObject::TYPE );

NiGeometryData::NiGeometryData() : unknownInt((int)0), numVertices((unsigned short)0), bsMaxVertices((unsigned short)0), keepFlags((byte)0), compressFlags((byte)0), hasVertices(1), numUvSets((unsigned short)0), bsNumUvSets((unsigned short)0), skyrimMaterial((SkyrimHavokMaterial)0), hasNormals(false), radius(0.0f), hasVertexColors(false), hasUv(false), consistencyFlags((ConsistencyType)CT_MUTABLE), additionalData(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiGeometryData::~NiGeometryData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiGeometryData::GetType() const {
	return TYPE;
}

NiObject * NiGeometryData::Create() {
	return new NiGeometryData;
}

void NiGeometryData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	if ( info.version >= 0x0A020000 ) {
		NifStream( unknownInt, in, info );
	};
	if ( (!IsDerivedType(NiPSysData::TYPE)) ) {
		NifStream( numVertices, in, info );
	};
	if ( ((info.version < 0x14020007) || (info.userVersion < 11)) ) {
		if ( IsDerivedType(NiPSysData::TYPE) ) {
			NifStream( numVertices, in, info );
		};
	};
	if ( ((info.version >= 0x14020007) && (info.userVersion >= 11)) ) {
		if ( IsDerivedType(NiPSysData::TYPE) ) {
			NifStream( bsMaxVertices, in, info );
		};
	};
	if ( info.version >= 0x0A010000 ) {
		NifStream( keepFlags, in, info );
		NifStream( compressFlags, in, info );
	};
	NifStream( hasVertices, in, info );
	if ( hasVertices ) {
		vertices.resize(numVertices);
		for (unsigned int i2 = 0; i2 < vertices.size(); i2++) {
			NifStream( vertices[i2], in, info );
		};
	};
	if ( ((info.version >= 0x0A000100) && (!((info.version >= 0x14020007) && (info.userVersion >= 11)))) ) {
		NifStream( numUvSets, in, info );
	};
	if ( ((info.version >= 0x14020007) && (info.userVersion >= 11)) ) {
		NifStream( bsNumUvSets, in, info );
	};
	if ( ( info.version >= 0x14020007 ) && ( info.userVersion == 12 ) ) {
		if ( (!IsDerivedType(NiPSysData::TYPE)) ) {
			NifStream( skyrimMaterial, in, info );
		};
	};
	NifStream( hasNormals, in, info );
	if ( hasNormals ) {
		normals.resize(numVertices);
		for (unsigned int i2 = 0; i2 < normals.size(); i2++) {
			NifStream( normals[i2], in, info );
		};
	};
	if ( info.version >= 0x0A010000 ) {
		if ( (hasNormals && ((numUvSets & 61440) || (bsNumUvSets & 61440))) ) {
			tangents.resize(numVertices);
			for (unsigned int i3 = 0; i3 < tangents.size(); i3++) {
				NifStream( tangents[i3], in, info );
			};
			bitangents.resize(numVertices);
			for (unsigned int i3 = 0; i3 < bitangents.size(); i3++) {
				NifStream( bitangents[i3], in, info );
			};
		};
	};
	NifStream( center, in, info );
	NifStream( radius, in, info );
	if ( ( info.version >= 0x14030009 ) && ( info.version <= 0x14030009 ) && ( info.userVersion == 131072 ) ) {
		for (unsigned int i2 = 0; i2 < 13; i2++) {
			NifStream( unknown13Shorts[i2], in, info );
		};
	};
	NifStream( hasVertexColors, in, info );
	if ( hasVertexColors ) {
		vertexColors.resize(numVertices);
		for (unsigned int i2 = 0; i2 < vertexColors.size(); i2++) {
			NifStream( vertexColors[i2], in, info );
		};
	};
	if ( info.version <= 0x04020200 ) {
		NifStream( numUvSets, in, info );
	};
	if ( info.version <= 0x04000002 ) {
		NifStream( hasUv, in, info );
	};
	uvSets.resize(((numUvSets & 63) | (bsNumUvSets & 1)));
	for (unsigned int i1 = 0; i1 < uvSets.size(); i1++) {
		uvSets[i1].resize(numVertices);
		for (unsigned int i2 = 0; i2 < uvSets[i1].size(); i2++) {
			NifStream( uvSets[i1][i2], in, info );
		};
	};
	if ( ( info.version >= 0x0A000100 ) && ( (info.userVersion < 12) ) ) {
		NifStream( consistencyFlags, in, info );
	};
	if ( ( info.version >= 0x0A000100 ) && ( (info.userVersion >= 12) ) ) {
		if ( (!IsDerivedType(NiPSysData::TYPE)) ) {
			NifStream( consistencyFlags, in, info );
		};
	};
	if ( ( info.version >= 0x14000004 ) && ( (info.userVersion < 12) ) ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	if ( ( info.version >= 0x14000004 ) && ( (info.userVersion >= 12) ) ) {
		if ( (!IsDerivedType(NiPSysData::TYPE)) ) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiGeometryData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	bsNumUvSets = bsNumUvSetsCalc(info);
	numUvSets = numUvSetsCalc(info);
	numVertices = (unsigned short)(vertices.size());
	if ( info.version >= 0x0A020000 ) {
		NifStream( unknownInt, out, info );
	};
	if ( (!IsDerivedType(NiPSysData::TYPE)) ) {
		NifStream( numVertices, out, info );
	};
	if ( ((info.version < 0x14020007) || (info.userVersion < 11)) ) {
		if ( IsDerivedType(NiPSysData::TYPE) ) {
			NifStream( numVertices, out, info );
		};
	};
	if ( ((info.version >= 0x14020007) && (info.userVersion >= 11)) ) {
		if ( IsDerivedType(NiPSysData::TYPE) ) {
			NifStream( bsMaxVertices, out, info );
		};
	};
	if ( info.version >= 0x0A010000 ) {
		NifStream( keepFlags, out, info );
		NifStream( compressFlags, out, info );
	};
	NifStream( hasVertices, out, info );
	if ( hasVertices ) {
		for (unsigned int i2 = 0; i2 < vertices.size(); i2++) {
			NifStream( vertices[i2], out, info );
		};
	};
	if ( ((info.version >= 0x0A000100) && (!((info.version >= 0x14020007) && (info.userVersion >= 11)))) ) {
		NifStream( numUvSets, out, info );
	};
	if ( ((info.version >= 0x14020007) && (info.userVersion >= 11)) ) {
		NifStream( bsNumUvSets, out, info );
	};
	if ( ( info.version >= 0x14020007 ) && ( info.userVersion == 12 ) ) {
		if ( (!IsDerivedType(NiPSysData::TYPE)) ) {
			NifStream( skyrimMaterial, out, info );
		};
	};
	NifStream( hasNormals, out, info );
	if ( hasNormals ) {
		for (unsigned int i2 = 0; i2 < normals.size(); i2++) {
			NifStream( normals[i2], out, info );
		};
	};
	if ( info.version >= 0x0A010000 ) {
		if ( (hasNormals && ((numUvSets & 61440) || (bsNumUvSets & 61440))) ) {
			for (unsigned int i3 = 0; i3 < tangents.size(); i3++) {
				NifStream( tangents[i3], out, info );
			};
			for (unsigned int i3 = 0; i3 < bitangents.size(); i3++) {
				NifStream( bitangents[i3], out, info );
			};
		};
	};
	NifStream( center, out, info );
	NifStream( radius, out, info );
	if ( ( info.version >= 0x14030009 ) && ( info.version <= 0x14030009 ) && ( info.userVersion == 131072 ) ) {
		for (unsigned int i2 = 0; i2 < 13; i2++) {
			NifStream( unknown13Shorts[i2], out, info );
		};
	};
	NifStream( hasVertexColors, out, info );
	if ( hasVertexColors ) {
		for (unsigned int i2 = 0; i2 < vertexColors.size(); i2++) {
			NifStream( vertexColors[i2], out, info );
		};
	};
	if ( info.version <= 0x04020200 ) {
		NifStream( numUvSets, out, info );
	};
	if ( info.version <= 0x04000002 ) {
		NifStream( hasUv, out, info );
	};
	for (unsigned int i1 = 0; i1 < uvSets.size(); i1++) {
		for (unsigned int i2 = 0; i2 < uvSets[i1].size(); i2++) {
			NifStream( uvSets[i1][i2], out, info );
		};
	};
	if ( ( info.version >= 0x0A000100 ) && ( (info.userVersion < 12) ) ) {
		NifStream( consistencyFlags, out, info );
	};
	if ( ( info.version >= 0x0A000100 ) && ( (info.userVersion >= 12) ) ) {
		if ( (!IsDerivedType(NiPSysData::TYPE)) ) {
			NifStream( consistencyFlags, out, info );
		};
	};
	if ( ( info.version >= 0x14000004 ) && ( (info.userVersion < 12) ) ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*additionalData), out );
		} else {
			if ( additionalData != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(additionalData) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( additionalData );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( ( info.version >= 0x14000004 ) && ( (info.userVersion >= 12) ) ) {
		if ( (!IsDerivedType(NiPSysData::TYPE)) ) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*additionalData), out );
			} else {
				if ( additionalData != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(additionalData) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( additionalData );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiGeometryData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numVertices = (unsigned short)(vertices.size());
	out << "  Unknown Int:  " << unknownInt << endl;
	if ( (!IsDerivedType(NiPSysData::TYPE)) ) {
		out << "    Num Vertices:  " << numVertices << endl;
	};
	if ( IsDerivedType(NiPSysData::TYPE) ) {
		out << "    BS Max Vertices:  " << bsMaxVertices << endl;
	};
	out << "  Keep Flags:  " << keepFlags << endl;
	out << "  Compress Flags:  " << compressFlags << endl;
	out << "  Has Vertices:  " << hasVertices << endl;
	if ( hasVertices ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < vertices.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Vertices[" << i2 << "]:  " << vertices[i2] << endl;
			array_output_count++;
		};
	};
	out << "  Num UV Sets:  " << numUvSets << endl;
	out << "  BS Num UV Sets:  " << bsNumUvSets << endl;
	if ( (!IsDerivedType(NiPSysData::TYPE)) ) {
		out << "    skyrimMaterial:  " << skyrimMaterial << endl;
	};
	out << "  Has Normals:  " << hasNormals << endl;
	if ( hasNormals ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < normals.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Normals[" << i2 << "]:  " << normals[i2] << endl;
			array_output_count++;
		};
	};
	if ( (hasNormals && ((numUvSets & 61440) || (bsNumUvSets & 61440))) ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < tangents.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Tangents[" << i2 << "]:  " << tangents[i2] << endl;
			array_output_count++;
		};
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < bitangents.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Bitangents[" << i2 << "]:  " << bitangents[i2] << endl;
			array_output_count++;
		};
	};
	out << "  Center:  " << center << endl;
	out << "  Radius:  " << radius << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 13; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 13 shorts[" << i1 << "]:  " << unknown13Shorts[i1] << endl;
		array_output_count++;
	};
	out << "  Has Vertex Colors:  " << hasVertexColors << endl;
	if ( hasVertexColors ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < vertexColors.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Vertex Colors[" << i2 << "]:  " << vertexColors[i2] << endl;
			array_output_count++;
		};
	};
	out << "  Has UV:  " << hasUv << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < uvSets.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		for (unsigned int i2 = 0; i2 < uvSets[i1].size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      UV Sets[" << i2 << "]:  " << uvSets[i1][i2] << endl;
			array_output_count++;
		};
	};
	out << "  Consistency Flags:  " << consistencyFlags << endl;
	out << "  Additional Data:  " << additionalData << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiGeometryData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( ( info.version >= 0x14000004 ) && ( (info.userVersion < 12) ) ) {
		additionalData = FixLink<AbstractAdditionalGeometryData>( objects, link_stack, missing_link_stack, info );
	};
	if ( ( info.version >= 0x14000004 ) && ( (info.userVersion >= 12) ) ) {
		if ( (!IsDerivedType(NiPSysData::TYPE)) ) {
			additionalData = FixLink<AbstractAdditionalGeometryData>( objects, link_stack, missing_link_stack, info );
		};
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiGeometryData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( additionalData != NULL )
		refs.push_back(StaticCast<NiObject>(additionalData));
	return refs;
}

std::list<NiObject *> NiGeometryData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

// Calculate bounding sphere using minimum-volume axis-align bounding box.  Its fast but not a very good fit.
static void CalcAxisAlignedBox(const vector<Vector3>& vertices, Vector3& center, float& radius)
{
	//--Calculate center & radius--//

	//Set lows and highs to first vertex
	Vector3 lows = vertices[ 0 ];
	Vector3 highs = vertices[ 0 ];

	//Iterate through the vertices, adjusting the stored values
	//if a vertex with lower or higher values is found
	for ( unsigned int i = 0; i < vertices.size(); ++i ) {
		const Vector3 & v = vertices[ i ];

		if ( v.x > highs.x ) highs.x = v.x;
		else if ( v.x < lows.x ) lows.x = v.x;

		if ( v.y > highs.y ) highs.y = v.y;
		else if ( v.y < lows.y ) lows.y = v.y;

		if ( v.z > highs.z ) highs.z = v.z;
		else if ( v.z < lows.z ) lows.z = v.z;
	}

	//Now we know the extent of the shape, so the center will be the average
	//of the lows and highs
	center = (highs + lows) / 2.0f;

	//The radius will be the largest distance from the center
	Vector3 diff;
	float dist2(0.0f), maxdist2(0.0f);
	for ( unsigned int i = 0; i < vertices.size(); ++i ) {
		const Vector3 & v = vertices[ i ];

		diff = center - v;
		dist2 = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
		if ( dist2 > maxdist2 ) maxdist2 = dist2;
	};
	radius = sqrt(maxdist2);
}

// Calculate bounding sphere using average position of the points.  Better fit but slower.
static void CalcCenteredSphere(const vector<Vector3>& vertices, Vector3& center, float& radius)
{
	size_t nv = vertices.size();
	Vector3 sum;
	for (size_t i=0; i<nv; ++i)
		sum += vertices[ i ];
	center = sum / float(nv);
	radius = 0.0f;
	for (size_t i=0; i<nv; ++i){
		Vector3 diff = vertices[ i ] - center;
		float mag = diff.Magnitude();
		radius = max(radius, mag);
	}
}

int NiGeometryData::GetVertexCount() const {
	return int(vertices.size());
}

short NiGeometryData::GetUVSetCount() const {
	return short(uvSets.size());
}

int NiGeometryData::GetVertexIndexCount() const {
	return int(vertexIndices.size());
}

vector<Vector3> NiGeometryData::GetVertices() const {
	return vertices;
}

vector<Vector3> NiGeometryData::GetNormals() const {
	return normals;
}

vector<Color4> NiGeometryData::GetColors() const {
	return vertexColors;
}

vector<TexCoord> NiGeometryData::GetUVSet( int index ) const {
	return uvSets[index];
}

vector<int> NiGeometryData::GetVertexIndices() const {
	return vertexIndices;
}

int NiGeometryData::GetUVSetIndex(int maxMapChannel) const
{
	if (uvSetMap.size() == 0) return -1;
	map<int,int>::const_iterator it = uvSetMap.find(maxMapChannel);
	if (it == uvSetMap.end()) return -1;
	return (*it).second;
}

void NiGeometryData::SetUVSetCount(int n) {
	uvSets.resize(n);
	hasUv = ( uvSets.size() != 0 );
   for (unsigned int i = 0; i < uvSets.size(); ++i ) {
      uvSets[i].resize( vertices.size() );
   }
}

//--Setters--//
void NiGeometryData::SetVertices( const vector<Vector3> & in ) {
	vertices = in;
	hasVertices = ( vertices.size() != 0 );

	//Clear out all other data as it is now based on old vertex information
	normals.clear();
	hasNormals = false;
	vertexColors.clear();
	this->hasVertexColors = false;
	for (unsigned int i = 0; i < uvSets.size(); ++i ) {
		uvSets[i].clear();
	}

	//If any vertices were given, calculate the new center and radius
	//Check if there are no vertices
	if ( vertices.size() == 0 ) {
		center.Set(0.0f, 0.0f, 0.0f);
		radius = 0.0f;
		return;
	}
	
	//Set lows and highs to first vertex
	Vector3 lows = vertices[0];
	Vector3 highs = vertices[0];

	//Iterate through the rest of the vertices, adjusting the stored values
	//if a vertex with lower or higher values is found
	for (vector<Vector3>::const_iterator i = vertices.begin()+1; i != vertices.end(); ++i ) {
		if ( i->x > highs.x ) highs.x = i->x;
		else if ( i->x < lows.x ) lows.x = i->x;

		if ( i->y > highs.y ) highs.y = i->y;
		else if ( i->y < lows.y ) lows.y = i->y;

		if ( i->z > highs.z ) highs.z = i->z;
		else if ( i->z < lows.z ) lows.z = i->z;
	}

	//Now we know the extent of the shape, so the center will be the average of the lows and highs.
	center.x = (highs.x + lows.x) / 2.0f;
	center.y = (highs.y + lows.y) / 2.0f;
	center.z = (highs.z + lows.z) / 2.0f;

	//The radius will be the largest distance from the center
	Vector3 diff;
	float dist2(0.0f), maxdist2(0.0f);
	for (vector<Vector3>::const_iterator i = vertices.begin(); i != vertices.end(); ++i ) {
		diff = center;
		diff.x -= i->x;
		diff.y -= i->y;
		diff.z -= i->z;
		dist2 = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
		if ( dist2 > maxdist2 ) maxdist2 = dist2;
	};
	radius = sqrt(maxdist2);
}

void NiGeometryData::SetNormals( const vector<Vector3> & in ) {
	if (in.size() != vertices.size() && in.size() != 0 )
		throw runtime_error("Vector size must equal Vertex Count or zero.");
	normals = in;
	hasNormals = ( normals.size() != 0 );
}

void NiGeometryData::SetVertexColors( const vector<Color4> & in ) {
	if (in.size() != vertices.size() && in.size() != 0 )
		throw runtime_error("Vector size must equal Vertex Count or zero.");
	vertexColors = in;
	hasVertexColors = ( vertexColors.size() != 0 );
}

void NiGeometryData::SetUVSet( int index, const vector<TexCoord> & in ) {
	if (in.size() != vertices.size())
		throw runtime_error("Vector size must equal Vertex Count.");
	uvSets[index] = in;
}

void NiGeometryData::SetVertexIndices( const vector<int> & in ) {
	if (in.size() != vertices.size() && in.size() != 0 )
		throw runtime_error("Vector size must equal Vertex Count or zero.");
	vertexIndices = in;
}

void NiGeometryData::SetUVSetMap( const std::map<int, int> & in ) {
	uvSetMap = in;
}


Vector3 NiGeometryData::GetCenter() const {
	return center;
}

float NiGeometryData::GetRadius() const {
	return radius;
}

void NiGeometryData::Transform( const Matrix44 & transform ) {
	Matrix44 rotation = Matrix44( transform.GetRotation() );

	//Apply the transformations
	for ( unsigned int i = 0; i < vertices.size(); ++i ) {
		vertices[i] = transform * vertices[i];
	}
	for ( unsigned int i = 0; i < normals.size(); ++i ) {
		normals[i] = rotation * normals[i];
	}
	CalcAxisAlignedBox(vertices, center, radius);
}

ConsistencyType NiGeometryData::GetConsistencyFlags() const {
	return consistencyFlags;
}

void NiGeometryData::SetConsistencyFlags( const ConsistencyType & value ) {
	consistencyFlags = value;
}

void NiGeometryData::SetBound(Vector3 const & center, float radius)
{
	this->center = center;
	this->radius = radius;
}


byte NiGeometryData::GetTspaceFlag() const {
   return (numUvSets | bsNumUvSets) >> 8;
}

void NiGeometryData::SetTspaceFlag( byte value ) {
   numUvSets = ((value << 8) | numUvSets);
   bsNumUvSets = ((value << 8) | bsNumUvSets);
}

bool NiGeometryData::GetHasNormals() const {
   return hasNormals;
}

void NiGeometryData::SetHasNormals( bool value ) {
   hasNormals = value;
}

vector<Vector3 > NiGeometryData::GetBitangents() const {
   return bitangents;
}

void NiGeometryData::SetBitangents( const vector<Vector3 >& value ) {
   bitangents = value;
}

vector<Vector3 > NiGeometryData::GetTangents() const {
   return tangents;
}

void NiGeometryData::SetTangents( const vector<Vector3 >& value ) {
   tangents = value;
}

unsigned short NiGeometryData::numUvSetsCalc(const NifInfo & info) const {
  return (numUvSets & (~63))  | (unsigned short)(uvSets.size() & 63);
}

unsigned short NiGeometryData::bsNumUvSetsCalc(const NifInfo & info) const {
  return (numUvSets & (~1)) | (bsNumUvSets & (~1)) | (unsigned short)(uvSets.size() & 1);
}

SkyrimHavokMaterial NiGeometryData::GetSkyrimMaterial() const {
	return skyrimMaterial;
}
//--END CUSTOM CODE--//
