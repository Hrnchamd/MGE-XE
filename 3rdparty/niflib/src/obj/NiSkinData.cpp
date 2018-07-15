/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include "../../include/obj/NiSkinInstance.h"
#include "../../include/obj/NiGeometry.h"
#include "../../include/obj/NiNode.h"
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiSkinData.h"
#include "../../include/gen/SkinTransform.h"
#include "../../include/gen/SkinData.h"
#include "../../include/gen/SkinTransform.h"
#include "../../include/gen/SkinWeight.h"
#include "../../include/gen/SkinWeight.h"
#include "../../include/obj/NiSkinPartition.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiSkinData::TYPE("NiSkinData", &NiObject::TYPE );

NiSkinData::NiSkinData() : numBones((unsigned int)0), skinPartition(NULL), hasVertexWeights((byte)1) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiSkinData::~NiSkinData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiSkinData::GetType() const {
	return TYPE;
}

NiObject * NiSkinData::Create() {
	return new NiSkinData;
}

void NiSkinData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( skinTransform.rotation, in, info );
	NifStream( skinTransform.translation, in, info );
	NifStream( skinTransform.scale, in, info );
	NifStream( numBones, in, info );
	if ( ( info.version >= 0x04000002 ) && ( info.version <= 0x0A010000 ) ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	if ( info.version >= 0x04020100 ) {
		NifStream( hasVertexWeights, in, info );
	};
	boneList.resize(numBones);
	for (unsigned int i1 = 0; i1 < boneList.size(); i1++) {
		NifStream( boneList[i1].skinTransform.rotation, in, info );
		NifStream( boneList[i1].skinTransform.translation, in, info );
		NifStream( boneList[i1].skinTransform.scale, in, info );
		NifStream( boneList[i1].boundingSphereOffset, in, info );
		NifStream( boneList[i1].boundingSphereRadius, in, info );
		if ( ( info.version >= 0x14030009 ) && ( info.version <= 0x14030009 ) && ( info.userVersion == 131072 ) ) {
			for (unsigned int i3 = 0; i3 < 13; i3++) {
				NifStream( boneList[i1].unknown13Shorts[i3], in, info );
			};
		};
		NifStream( boneList[i1].numVertices, in, info );
		if ( info.version <= 0x04020100 ) {
			boneList[i1].vertexWeights.resize(boneList[i1].numVertices);
			for (unsigned int i3 = 0; i3 < boneList[i1].vertexWeights.size(); i3++) {
				NifStream( boneList[i1].vertexWeights[i3].index, in, info );
				NifStream( boneList[i1].vertexWeights[i3].weight, in, info );
			};
		};
		if ( info.version >= 0x04020200 ) {
			if ( (hasVertexWeights != 0) ) {
				boneList[i1].vertexWeights.resize(boneList[i1].numVertices);
				for (unsigned int i4 = 0; i4 < boneList[i1].vertexWeights.size(); i4++) {
					NifStream( boneList[i1].vertexWeights[i4].index, in, info );
					NifStream( boneList[i1].vertexWeights[i4].weight, in, info );
				};
			};
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiSkinData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	numBones = (unsigned int)(boneList.size());
	NifStream( skinTransform.rotation, out, info );
	NifStream( skinTransform.translation, out, info );
	NifStream( skinTransform.scale, out, info );
	NifStream( numBones, out, info );
	if ( ( info.version >= 0x04000002 ) && ( info.version <= 0x0A010000 ) ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*skinPartition), out );
		} else {
			if ( skinPartition != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(skinPartition) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( skinPartition );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( info.version >= 0x04020100 ) {
		NifStream( hasVertexWeights, out, info );
	};
	for (unsigned int i1 = 0; i1 < boneList.size(); i1++) {
		boneList[i1].numVertices = (unsigned short)(boneList[i1].vertexWeights.size());
		NifStream( boneList[i1].skinTransform.rotation, out, info );
		NifStream( boneList[i1].skinTransform.translation, out, info );
		NifStream( boneList[i1].skinTransform.scale, out, info );
		NifStream( boneList[i1].boundingSphereOffset, out, info );
		NifStream( boneList[i1].boundingSphereRadius, out, info );
		if ( ( info.version >= 0x14030009 ) && ( info.version <= 0x14030009 ) && ( info.userVersion == 131072 ) ) {
			for (unsigned int i3 = 0; i3 < 13; i3++) {
				NifStream( boneList[i1].unknown13Shorts[i3], out, info );
			};
		};
		NifStream( boneList[i1].numVertices, out, info );
		if ( info.version <= 0x04020100 ) {
			for (unsigned int i3 = 0; i3 < boneList[i1].vertexWeights.size(); i3++) {
				NifStream( boneList[i1].vertexWeights[i3].index, out, info );
				NifStream( boneList[i1].vertexWeights[i3].weight, out, info );
			};
		};
		if ( info.version >= 0x04020200 ) {
			if ( (hasVertexWeights != 0) ) {
				for (unsigned int i4 = 0; i4 < boneList[i1].vertexWeights.size(); i4++) {
					NifStream( boneList[i1].vertexWeights[i4].index, out, info );
					NifStream( boneList[i1].vertexWeights[i4].weight, out, info );
				};
			};
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiSkinData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numBones = (unsigned int)(boneList.size());
	out << "  Rotation:  " << skinTransform.rotation << endl;
	out << "  Translation:  " << skinTransform.translation << endl;
	out << "  Scale:  " << skinTransform.scale << endl;
	out << "  Num Bones:  " << numBones << endl;
	out << "  Skin Partition:  " << skinPartition << endl;
	out << "  Has Vertex Weights:  " << hasVertexWeights << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < boneList.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		boneList[i1].numVertices = (unsigned short)(boneList[i1].vertexWeights.size());
		out << "    Rotation:  " << boneList[i1].skinTransform.rotation << endl;
		out << "    Translation:  " << boneList[i1].skinTransform.translation << endl;
		out << "    Scale:  " << boneList[i1].skinTransform.scale << endl;
		out << "    Bounding Sphere Offset:  " << boneList[i1].boundingSphereOffset << endl;
		out << "    Bounding Sphere Radius:  " << boneList[i1].boundingSphereRadius << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < 13; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown 13 Shorts[" << i2 << "]:  " << boneList[i1].unknown13Shorts[i2] << endl;
			array_output_count++;
		};
		out << "    Num Vertices:  " << boneList[i1].numVertices << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < boneList[i1].vertexWeights.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			out << "      Index:  " << boneList[i1].vertexWeights[i2].index << endl;
			out << "      Weight:  " << boneList[i1].vertexWeights[i2].weight << endl;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiSkinData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( ( info.version >= 0x04000002 ) && ( info.version <= 0x0A010000 ) ) {
		skinPartition = FixLink<NiSkinPartition>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiSkinData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( skinPartition != NULL )
		refs.push_back(StaticCast<NiObject>(skinPartition));
	return refs;
}

std::list<NiObject *> NiSkinData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

unsigned int NiSkinData::GetBoneCount() const {
	return (unsigned int)( boneList.size() );
}

Matrix44 NiSkinData::GetBoneTransform( unsigned int bone_index ) const {
	if ( bone_index > boneList.size() ) {
		throw runtime_error( "The specified bone index was larger than the number of bones in this NiSkinData." );
	}

	return Matrix44( boneList[bone_index].skinTransform.translation, boneList[bone_index].skinTransform.rotation, boneList[bone_index].skinTransform.scale );
}

vector<SkinWeight> NiSkinData::GetBoneWeights( unsigned int bone_index ) const {
	if ( bone_index > boneList.size() ) {
		throw runtime_error( "The specified bone index was larger than the number of bones in this NiSkinData." );
	}

	return boneList[bone_index].vertexWeights;
}

void NiSkinData::SetBoneWeights( unsigned int bone_index, const vector<SkinWeight> & weights, Vector3 center, float radius ) {
	if ( bone_index > boneList.size() ) {
		throw runtime_error( "The specified bone index was larger than the number of bones in this NiSkinData." );
	}

	hasVertexWeights = true;
	boneList[bone_index].vertexWeights = weights;
    boneList[bone_index].boundingSphereOffset = center;
    boneList[bone_index].boundingSphereRadius = radius;
}

void NiSkinData::SetBoneWeights( unsigned int bone_index, const vector<SkinWeight> & weights ) {
	if ( bone_index > boneList.size() ) {
		throw runtime_error( "The specified bone index was larger than the number of bones in this NiSkinData." );
	}

	hasVertexWeights = true;
	boneList[bone_index].vertexWeights = weights;
}

Matrix44 NiSkinData::GetOverallTransform() const {
	return Matrix44( skinTransform.translation, skinTransform.rotation, skinTransform.scale );
}

void NiSkinData::SetOverallTransform( const Matrix44 & transform ) {
	transform.Decompose( skinTransform.translation, skinTransform.rotation, skinTransform.scale );
}

NiSkinData::NiSkinData( NiGeometry * owner ) {
	//Call normal constructor
	NiSkinData();

	ResetOffsets( owner );
}

void NiSkinData::NormalizeWeights( unsigned numVertices ) {
	vector<double> totals(numVertices);
	vector<int> counts(numVertices);

	//Set all totals to 1.0 and all counts to 0
	for ( unsigned v = 0; v < numVertices; ++v ) {
		totals[v] = 1.0;
		counts[v] = 0;
	}

	//Calculate the total error for each vertex by subtracting the weight from
	//each bone from the starting total of 1.0
	//Also count the number of bones affecting each vertex
	for ( unsigned b = 0; b < boneList.size(); ++b ) {
		for ( unsigned w = 0; w < boneList[b].vertexWeights.size(); ++w ) {
			SkinWeight & sw = boneList[b].vertexWeights[w];
			totals[sw.index] -= sw.weight;
			counts[sw.index]++;
		}
	}

	//Divide all error amounts by the number of bones affecting that vertex to
	//get the amount of error that should be distributed to each bone.
	for ( unsigned v = 0; v < numVertices; ++v ) {
		totals[v] = totals[v] / double(counts[v]);
	}

	//Distribute the calculated error to each weight
	for ( unsigned b = 0; b < boneList.size(); ++b ) {
		for ( unsigned w = 0; w < boneList[b].vertexWeights.size(); ++w ) {
			SkinWeight & sw = boneList[b].vertexWeights[w];
			double temp = double(sw.weight) + totals[sw.index];
			sw.weight = float(temp);
		}
	}	
}

void NiSkinData::ResetOffsets( NiGeometry * owner ) {

	//Get skin instance
	NiSkinInstanceRef skinInst = owner->GetSkinInstance();

	if ( skinInst == NULL ) {
		throw runtime_error("Skin instance should have already been created.");
	}

	boneList.resize( skinInst->GetBoneCount() );
	vector< Ref<NiNode> > bone_nodes = skinInst->GetBones();

	//--Calculate Overall Offset--//

	//Get TriBasedGeom world transform
	Matrix44 owner_mat = owner->GetWorldTransform();

	//Get Skeleton root world transform
	Matrix44 sr_world = skinInst->GetSkeletonRoot()->GetWorldTransform();

	//Inverse owner NiGeometry matrix & multiply with skeleton root matrix
	Matrix44 overall_mat = (owner_mat * sr_world.Inverse()).Inverse();

	//Store result
	overall_mat.Decompose( skinTransform.translation, skinTransform.rotation, skinTransform.scale );

	//--Calculate Bone Offsets--//
	Matrix44 res_mat;
	Matrix44 bone_mat;
	for (unsigned int i = 0; i < boneList.size(); ++i ) {
		//--Get Bone Bind Pose--//

		//Get bone world position
		bone_mat = bone_nodes[i]->GetWorldTransform();

		//Multiply NiGeometry matrix with inversed bone matrix
		res_mat = owner_mat * bone_mat.Inverse();

		//Store result
		res_mat.Decompose( boneList[i].skinTransform.translation, boneList[i].skinTransform.rotation, boneList[i].skinTransform.scale );
	}
}

Ref<NiSkinPartition> NiSkinData::GetSkinPartition() const {
   return skinPartition;
}

void NiSkinData::SetSkinPartition( NiSkinPartition * value ) {
   skinPartition = value;
}

//--END CUSTOM CODE--//
