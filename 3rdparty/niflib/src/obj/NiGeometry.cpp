/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include "../../include/niflib.h"
#include "../../include/obj/NiNode.h"
#include "../../include/obj/NiSkinData.h"
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiGeometry.h"
#include "../../include/obj/NiGeometryData.h"
#include "../../include/obj/NiProperty.h"
#include "../../include/obj/NiSkinInstance.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiGeometry::TYPE("NiGeometry", &NiAVObject::TYPE );

NiGeometry::NiGeometry() : data(NULL), skinInstance(NULL), numMaterials((unsigned int)0), activeMaterial((int)0), hasShader(false), unknownInteger((int)0), unknownByte((byte)255), unknownInteger2((int)0), dirtyFlag(false) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiGeometry::~NiGeometry() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiGeometry::GetType() const {
	return TYPE;
}

NiObject * NiGeometry::Create() {
	return new NiGeometry;
}

void NiGeometry::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiAVObject::Read( in, link_stack, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	if ( info.version >= 0x0303000D ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	if ( info.version >= 0x14020007 ) {
		NifStream( numMaterials, in, info );
		materialName.resize(numMaterials);
		for (unsigned int i2 = 0; i2 < materialName.size(); i2++) {
			NifStream( materialName[i2], in, info );
		};
		materialExtraData.resize(numMaterials);
		for (unsigned int i2 = 0; i2 < materialExtraData.size(); i2++) {
			NifStream( materialExtraData[i2], in, info );
		};
		NifStream( activeMaterial, in, info );
	};
	if ( ( info.version >= 0x0A000100 ) && ( info.version <= 0x14010003 ) ) {
		NifStream( hasShader, in, info );
		if ( hasShader ) {
			NifStream( shaderName, in, info );
			NifStream( unknownInteger, in, info );
		};
	};
	if ( info.userVersion == 1 ) {
		NifStream( unknownByte, in, info );
	};
	if ( ( info.version >= 0x0A040001 ) && ( info.version <= 0x0A040001 ) ) {
		NifStream( unknownInteger2, in, info );
	};
	if ( info.version >= 0x14020007 ) {
		NifStream( dirtyFlag, in, info );
	};
	if ( ( info.version >= 0x14020007 ) && ( info.userVersion == 12 ) ) {
		for (unsigned int i2 = 0; i2 < 2; i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiGeometry::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiAVObject::Write( out, link_map, missing_link_stack, info );
	numMaterials = (unsigned int)(materialName.size());
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
	if ( info.version >= 0x0303000D ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*skinInstance), out );
		} else {
			if ( skinInstance != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(skinInstance) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( skinInstance );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( info.version >= 0x14020007 ) {
		NifStream( numMaterials, out, info );
		for (unsigned int i2 = 0; i2 < materialName.size(); i2++) {
			NifStream( materialName[i2], out, info );
		};
		for (unsigned int i2 = 0; i2 < materialExtraData.size(); i2++) {
			NifStream( materialExtraData[i2], out, info );
		};
		NifStream( activeMaterial, out, info );
	};
	if ( ( info.version >= 0x0A000100 ) && ( info.version <= 0x14010003 ) ) {
		NifStream( hasShader, out, info );
		if ( hasShader ) {
			NifStream( shaderName, out, info );
			NifStream( unknownInteger, out, info );
		};
	};
	if ( info.userVersion == 1 ) {
		NifStream( unknownByte, out, info );
	};
	if ( ( info.version >= 0x0A040001 ) && ( info.version <= 0x0A040001 ) ) {
		NifStream( unknownInteger2, out, info );
	};
	if ( info.version >= 0x14020007 ) {
		NifStream( dirtyFlag, out, info );
	};
	if ( ( info.version >= 0x14020007 ) && ( info.userVersion == 12 ) ) {
		for (unsigned int i2 = 0; i2 < 2; i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*bsProperties[i2]), out );
			} else {
				if ( bsProperties[i2] != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(bsProperties[i2]) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( bsProperties[i2] );
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

std::string NiGeometry::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiAVObject::asString();
	numMaterials = (unsigned int)(materialName.size());
	out << "  Data:  " << data << endl;
	out << "  Skin Instance:  " << skinInstance << endl;
	out << "  Num Materials:  " << numMaterials << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < materialName.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Material Name[" << i1 << "]:  " << materialName[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < materialExtraData.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Material Extra Data[" << i1 << "]:  " << materialExtraData[i1] << endl;
		array_output_count++;
	};
	out << "  Active Material:  " << activeMaterial << endl;
	out << "  Has Shader:  " << hasShader << endl;
	if ( hasShader ) {
		out << "    Shader Name:  " << shaderName << endl;
		out << "    Unknown Integer:  " << unknownInteger << endl;
	};
	out << "  Unknown Byte:  " << unknownByte << endl;
	out << "  Unknown Integer 2:  " << unknownInteger2 << endl;
	out << "  Dirty Flag:  " << dirtyFlag << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    BS Properties[" << i1 << "]:  " << bsProperties[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiGeometry::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiAVObject::FixLinks( objects, link_stack, missing_link_stack, info );
	data = FixLink<NiGeometryData>( objects, link_stack, missing_link_stack, info );
	if ( info.version >= 0x0303000D ) {
		skinInstance = FixLink<NiSkinInstance>( objects, link_stack, missing_link_stack, info );
	};
	if ( ( info.version >= 0x14020007 ) && ( info.userVersion == 12 ) ) {
		for (unsigned int i2 = 0; i2 < 2; i2++) {
			bsProperties[i2] = FixLink<NiProperty>( objects, link_stack, missing_link_stack, info );
		};
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiGeometry::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiAVObject::GetRefs();
	if ( data != NULL )
		refs.push_back(StaticCast<NiObject>(data));
	if ( skinInstance != NULL )
		refs.push_back(StaticCast<NiObject>(skinInstance));
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		if ( bsProperties[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(bsProperties[i1]));
	};
	return refs;
}

std::list<NiObject *> NiGeometry::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiAVObject::GetPtrs();
	for (unsigned int i1 = 0; i1 < 2; i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Ref<NiGeometryData> NiGeometry::GetData() const {
	return DynamicCast<NiGeometryData>(data);
}

void NiGeometry::SetData( NiGeometryData * n ) {
	data = n;
}

string NiGeometry::GetShader() const {
	return shaderName;
}

void NiGeometry::SetShader( const string & n ) {
	//Check if name is blank, if so clear shader
	if ( n.size() == 0 ) {
		hasShader = false;
		shaderName.clear();
	} else {
		shaderName = n;
	}
}

Ref<NiSkinInstance> NiGeometry::GetSkinInstance() const {
	return skinInstance;
}

void NiGeometry::SetSkinInstance(Ref<NiSkinInstance> skin) {
	skinInstance = skin;
}

void NiGeometry::BindSkin( vector< Ref<NiNode> >& bone_nodes ) {
   BindSkinWith(bone_nodes, NULL);
}

void NiGeometry::BindSkinWith( vector< Ref<NiNode> >& bone_nodes,  NiObject * (*SkinInstConstructor)())
{
   if (SkinInstConstructor == NULL) {
      SkinInstConstructor = NiSkinInstance::Create;      
   }

	//Ensure skin is not aleady bound
	if ( skinInstance != 0 ) {
		throw runtime_error("You have attempted to re-bind a skin that is already bound.  Unbind it first.");
	}

	//Ensure that some bones are given
	if ( bone_nodes.size() == 0 ) {
		throw runtime_error("You must specify at least one bone node.");
	}

	//--Find a suitable skeleton root--//

	//The skeleton root will be the common ancestor of all bones which influence this skin,
	//and the skin object itself.

	vector<NiAVObjectRef> objects;
	objects.push_back( NiAVObjectRef(this) );
	for ( size_t i = 0; i < bone_nodes.size(); ++i ) {
		objects.push_back( StaticCast<NiAVObject>(bone_nodes[i]) );
	}

	NiNodeRef skeleton_root = FindCommonAncestor( objects );

	if ( skeleton_root == NULL ) {
		throw runtime_error("Failed to find suitable skeleton root.");
	}

	//Create a skin instance using the bone and root data
   skinInstance = DynamicCast<NiSkinInstance>( SkinInstConstructor() );
   if (skinInstance == NULL) {
      throw runtime_error("Failed to construct NiSkinInstance");
   }

	skinInstance->BindSkin( skeleton_root, bone_nodes );

	//Create a NiSkinData object based on this mesh
	skinInstance->SetSkinData( new NiSkinData( this ) );
};

void NiGeometry::ApplySkinOffset() {
	if ( GetParent() == NULL ) {
		throw runtime_error("Attempted to apply skin transforms on a shape with no parent.");
	}

	if ( skinInstance == NULL ) {
		throw runtime_error("Attempted to apply skin transforms on a shape with no skin instance.");
	}

	if ( skinInstance->GetSkinData() == NULL ) {
		throw runtime_error("Attempted to apply skin transforms on a shape with no skin data.");
	}
	
	//Get ancestors
	list<NiNodeRef> ancestors;
	ancestors = ListAncestors( this );

	//Propagate transforms on ancestors below skeleton root
	bool below_root = false;

	for ( list<NiNodeRef>::iterator it = ancestors.begin(); it != ancestors.end(); ++it ) {
		if ( *it == skinInstance->GetSkeletonRoot() ) {
			below_root = true;
			continue;
		}
		if ( below_root ) {
			(*it)->PropagateTransform();
		}
	}

	//Now apply the transforms to the vertices and normals of this mesh
	this->ApplyTransforms();

	//Set the skin overall transform to the identity
	skinInstance->GetSkinData()->SetOverallTransform( Matrix44::IDENTITY );	

	//Reset skin offsets
	skinInstance->GetSkinData()->ResetOffsets( this );
}

void NiGeometry::NormalizeSkinWeights() {
	if ( IsSkin() == false ) {
		throw runtime_error( "NormalizeSkinWeights called on a mesh that is not a skin." );
	}
	NiSkinDataRef niSkinData = this->GetSkinInstance()->GetSkinData();

	NiGeometryDataRef niGeomData = this->GetData();
	if ( niGeomData == NULL ) {
		throw runtime_error( "NormalizeSkinWeights called on a mesh with no geometry data." );
	}

	niSkinData->NormalizeWeights( niGeomData->GetVertexCount() );
}

bool NiGeometry::IsSkin() {
	//Determine whether this is a skin by looking for a skin instance and
	//skin data
	if ( skinInstance != NULL && skinInstance->GetSkinData() != NULL ) {
		return true;
	} else {
		return false;
	}
}

void NiGeometry::UnbindSkin() {
	//Clear skin instance
	skinInstance = NULL;
}

void NiGeometry::GetSkinDeformation( vector<Vector3> & vertices, vector<Vector3> & normals ) const{
	//--Get required data & insure validity--//

	NiGeometryDataRef geom_data = GetData();

	if ( geom_data == NULL ) {
		throw runtime_error("This NiGeometry has no NiGeometryData so there are no vertices to get.");
	}

	NiSkinInstanceRef skin_inst = GetSkinInstance();
	

	if ( skin_inst == NULL ) {
		throw runtime_error("This NiGeometry is not influenced by a skin.");
	}

	NiSkinDataRef skin_data = skin_inst->GetSkinData();

	if ( skin_data == NULL ) {
		throw runtime_error("Skin Data is missing, cannot calculate skin influenced vertex position.");
	}

	//Ensure that skin instance bone count & skin data bone count match
	if ( skin_inst->GetBoneCount() != skin_data->GetBoneCount() ) {
		throw runtime_error("Skin Instance and Skin Data bone count do not match.");
	}

	//Get skeleton root
	NiNodeRef skel_root = skin_inst->GetSkeletonRoot();
	if ( skel_root == NULL ) {
		throw runtime_error("Skin Instance is not bound to a skeleton root.");
	}

	//Get the vertices & bone nodes
	vector<Vector3> in_verts = geom_data->GetVertices();
	vector<Vector3> in_norms = geom_data->GetNormals();

	vector<NiNodeRef> bone_nodes = skin_inst->GetBones();

	//Set up output arrays to hold the transformed vertices and normals
	vertices.resize( in_verts.size() );
	normals.resize( in_norms.size() );

	//Transform vertices into position based on skin data
	Matrix44 root_world = skel_root->GetWorldTransform();
	Matrix44 geom_world = GetWorldTransform();
	for ( unsigned int i = 0; i < skin_data->GetBoneCount(); ++i ) {
		Matrix44 bone_world = bone_nodes[i]->GetWorldTransform();
		Matrix44 bone_offset = skin_data->GetBoneTransform(i);
		vector<SkinWeight> weights = skin_data->GetBoneWeights(i);
		Matrix44 vert_trans =  bone_offset * bone_world;
		Matrix44 norm_trans = Matrix44( vert_trans.GetRotation() );
		for ( unsigned int j = 0; j < weights.size(); ++j ) {
			unsigned int index = weights[j].index;
			float weight = weights[j].weight;
			if ( index < vertices.size() ) {
				vertices[index] += (vert_trans * in_verts[index] ) * weight;
			}
			if ( index < normals.size() ) {
				normals[index] += (norm_trans * in_norms[index] ) * weight;
			}
		}
	}

	//Transform all vertices to final position
	Matrix44 geom_world_inv = geom_world.Inverse();
	Matrix44 geom_world_inv_rot = Matrix44( geom_world_inv.GetRotation() );
	for ( unsigned int i = 0; i < vertices.size(); ++i ) {
		vertices[i] = geom_world_inv * vertices[i];
	}
	for ( unsigned int i = 0; i < normals.size(); ++i ) {
		normals[i] = geom_world_inv_rot * normals[i];
		//normals[i] = normals[i].Normalized();
	}
}

void NiGeometry::ApplyTransforms() {
	//Get Data
	NiGeometryDataRef geom_data = this->GetData();
	if ( geom_data == NULL ) {
		throw runtime_error( "Called ApplyTransform on a NiGeometry object that has no NiGeometryData attached.");
	}

	//Transform the vertices by the local transform of this mesh
	geom_data->Transform( this->GetLocalTransform() );

	//Now that the transforms have been applied, clear them to the identity
	this->SetLocalTransform( Matrix44::IDENTITY );
}

// Calculate bounding sphere using minimum-volume axis-align bounding box.  Its fast but not a very good fit.
static void CalcAxisAlignedBox(const vector<SkinWeight> & n, const vector<Vector3>& vertices, Vector3& center, float& radius)
{
   //--Calculate center & radius--//

   //Set lows and highs to first vertex
   Vector3 lows = vertices[ n[0].index ];
   Vector3 highs = vertices[ n[0].index ];

   //Iterate through the vertices, adjusting the stored values
   //if a vertex with lower or higher values is found
   for ( unsigned int i = 0; i < n.size(); ++i ) {
      const Vector3 & v = vertices[ n[i].index ];

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
   for ( unsigned int i = 0; i < n.size(); ++i ) {
      const Vector3 & v = vertices[ n[i].index ];

      diff = center - v;
      dist2 = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
      if ( dist2 > maxdist2 ) maxdist2 = dist2;
   };
   radius = sqrt(maxdist2);
}

// Calculate bounding sphere using average position of the points.  Better fit but slower.
static void CalcCenteredSphere(const vector<SkinWeight> & n, const vector<Vector3>& vertices, Vector3& center, float& radius)
{
   size_t nv = n.size();
   Vector3 sum;
   for (size_t i=0; i<nv; ++i)
      sum += vertices[ n[i].index ];
   center = sum / float(nv);
   radius = 0.0f;
   for (size_t i=0; i<nv; ++i){
      Vector3 diff = vertices[ n[i].index ] - center;
      float mag = diff.Magnitude();
      radius = max(radius, mag);
   }
}

void NiGeometry::SetBoneWeights( unsigned int bone_index, const vector<SkinWeight> & n ) {
	
	if ( n.size() == 0 ) {
		throw runtime_error( "You must specify at least one weight value." );
	}

	NiSkinInstanceRef skinInst = GetSkinInstance();

	if ( skinInst == NULL ) {
		throw runtime_error( "You must bind a skin before setting vertex weights.  No NiSkinInstance found." );
	}

	NiSkinDataRef skinData = skinInst->GetSkinData();

	if ( skinData == NULL ) {
		throw runtime_error( "You must bind a skin before setting vertex weights.  No NiSkinData found." );
	}

	NiGeometryDataRef geomData = GetData();

	if ( geomData == NULL ) {
		throw runtime_error( "Attempted to set weights on a mesh with no geometry data." );
	}

	//Get vertex array
	vector<Vector3> vertices = geomData->GetVertices();

   Vector3 center; float radius;
   //CalcCenteredSphere(n, vertices, center, radius);
   CalcAxisAlignedBox(n, vertices, center, radius);

	//Translate center by bone matrix
	center = skinData->GetBoneTransform( bone_index ) * center;

	skinData->SetBoneWeights( bone_index, n, center, radius );
}

int NiGeometry::GetActiveMaterial() const {
   return activeMaterial;
}

void NiGeometry::SetActiveMaterial( int value ) {
   activeMaterial = value;
}

bool NiGeometry::HasShader() const {
   return hasShader;
}

Ref<NiProperty> NiGeometry::GetBSProperty(short index) {
	if ((index < 0) || (index > 1))   return NULL;
	return bsProperties[index];
}

void NiGeometry::SetBSProperty(short index, Niflib::Ref<NiProperty> value) {
	if ((index >= 0) && (index <= 1))
	{
		bsProperties[index] = value;
	}
}

array<2,Ref<NiProperty > > Niflib::NiGeometry::GetBSProperties() {
	return this->bsProperties;
}

void Niflib::NiGeometry::SetBSProperties( array<2, Ref<NiProperty> > value ) {
	this->bsProperties = value;
}

//--END CUSTOM CODE--//
