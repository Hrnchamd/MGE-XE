/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include "../../include/obj/NiSkinInstance.h"
#include "../../include/obj/NiTriBasedGeom.h"
#include "../../include/obj/NiSkinData.h"
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiNode.h"
#include "../../include/obj/NiAVObject.h"
#include "../../include/obj/NiDynamicEffect.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiNode::TYPE("NiNode", &NiAVObject::TYPE );

NiNode::NiNode() : numChildren((unsigned int)0), numEffects((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//Set flag to default of 8: not a skin influence
	flags = 8;

	//--END CUSTOM CODE--//
}

NiNode::~NiNode() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//Unbind any attached skins - must happen before children are cleared
	for ( list<NiSkinInstance*>::iterator it = skins.begin(); it != skins.end(); ++it ) {
		(*it)->SkeletonLost();
	}

	//Clear Children
	ClearChildren();

	//--END CUSTOM CODE--//
}

const Type & NiNode::GetType() const {
	return TYPE;
}

NiObject * NiNode::Create() {
	return new NiNode;
}

void NiNode::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiAVObject::Read( in, link_stack, info );
	NifStream( numChildren, in, info );
	children.resize(numChildren);
	for (unsigned int i1 = 0; i1 < children.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( numEffects, in, info );
	effects.resize(numEffects);
	for (unsigned int i1 = 0; i1 < effects.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiNode::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiAVObject::Write( out, link_map, missing_link_stack, info );
	numEffects = (unsigned int)(effects.size());
	numChildren = (unsigned int)(children.size());
	NifStream( numChildren, out, info );
	for (unsigned int i1 = 0; i1 < children.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*children[i1]), out );
		} else {
			if ( children[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(children[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( children[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( numEffects, out, info );
	for (unsigned int i1 = 0; i1 < effects.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*effects[i1]), out );
		} else {
			if ( effects[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(effects[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( effects[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiNode::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiAVObject::asString();
	numEffects = (unsigned int)(effects.size());
	numChildren = (unsigned int)(children.size());
	out << "  Num Children:  " << numChildren << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < children.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Children[" << i1 << "]:  " << children[i1] << endl;
		array_output_count++;
	};
	out << "  Num Effects:  " << numEffects << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < effects.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Effects[" << i1 << "]:  " << effects[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiNode::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiAVObject::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < children.size(); i1++) {
		children[i1] = FixLink<NiAVObject>( objects, link_stack, missing_link_stack, info );
	};
	for (unsigned int i1 = 0; i1 < effects.size(); i1++) {
		effects[i1] = FixLink<NiDynamicEffect>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//Connect children to their parents and remove any NULL ones
	for ( vector< NiAVObjectRef >::iterator it = children.begin(); it != children.end(); ) {
		if ( *it == NULL) {
			it = children.erase( it );
		} else {
			(*it)->SetParent(this);
			++it;
		}
	}

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiNode::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiAVObject::GetRefs();
	for (unsigned int i1 = 0; i1 < children.size(); i1++) {
		if ( children[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(children[i1]));
	};
	for (unsigned int i1 = 0; i1 < effects.size(); i1++) {
		if ( effects[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(effects[i1]));
	};
	return refs;
}

std::list<NiObject *> NiNode::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiAVObject::GetPtrs();
	for (unsigned int i1 = 0; i1 < children.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < effects.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

void NiNode::AddChild( Ref<NiAVObject> obj ) {
	if ( obj->GetParent() != NULL ) {
		throw runtime_error( "You have attempted to add a child to a NiNode which already is the child of another NiNode." );
	}
	obj->SetParent( this );
	//Sometimes NiTriBasedGeom with skins can be siblings of NiNodes that
	//represent joints for that same skin.  When this is the case, NiTriBasedGeom
	//must com first, so we enforce that by always adding NiTriBasedGeom to the
	//begining of the child list.
	NiTriBasedGeomRef niGeom = DynamicCast<NiTriBasedGeom>(obj);
	if ( niGeom != NULL ) {
		//This is a NiTriBasedGeom, so shift all children to the right
		size_t old_size = children.size();
		children.resize( children.size() + 1 );
		for ( size_t i = children.size() - 1; i >= 1; --i ) {
			children[i] = children[i-1];
		}

		//Now add the new child to the begining of the list
		children[0] = obj;
	} else {
		//This is some other type of object.  Just add it to the end of the list.
		children.push_back( obj );
	}
}

void NiNode::RemoveChild( Ref<NiAVObject> obj ) {
	//Search child list for the one to remove
	for ( vector< NiAVObjectRef >::iterator it = children.begin(); it != children.end(); ) {
		if ( *it == obj ) {
			(*it)->SetParent(NULL);
			it = children.erase( it );
		} else {
			++it;
		}
	}
}

void NiNode::ClearChildren() {
	for ( vector< NiAVObjectRef >::iterator it = children.begin(); it != children.end(); ++it) {
		if ( *it != NULL ) {
			(*it)->SetParent(NULL);
		}
	}
	children.clear();
}

vector< Ref<NiAVObject> > NiNode::GetChildren() const {
	return children;
}


void NiNode::AddEffect( NiDynamicEffect * obj ) {
   obj->SetParent( this );
   effects.push_back( obj );
}

void NiNode::RemoveEffect( NiDynamicEffect * obj ) {
   //Search Effect list for the one to remove
   for ( vector< NiDynamicEffectRef >::iterator it = effects.begin(); it != effects.end(); ) {
      if ( *it == obj ) {
         (*it)->SetParent(NULL);
         it = effects.erase( it );
      } else {
         ++it;
      }
   }
}

void NiNode::ClearEffects() {
   for ( vector< NiDynamicEffectRef >::iterator it = effects.begin(); it != effects.end(); ++it) {
      if (*it) (*it)->SetParent(NULL);
   }
   effects.clear();
}

vector< Ref<NiDynamicEffect> > NiNode::GetEffects() const {
   return effects;
}

bool NiNode::IsSkeletonRoot() const {
	return ( skins.size() > 0 );
}

bool NiNode::IsSkinInfluence() const {
	return ((flags & 8) == 0);
}

void NiNode::AddSkin( NiSkinInstance * skin_inst ) {
	skins.push_back( skin_inst );
}

void NiNode::RemoveSkin( NiSkinInstance * skin_inst ) {
	//Remove the reference
	skins.remove( skin_inst);

	//Ensure that any multiply referenced bone nodes still
	//have their skin flag set
	vector<NiNodeRef> bones;
	for ( list<NiSkinInstance*>::iterator it = skins.begin(); it != skins.end(); ++it ) {
		bones = (*it)->GetBones();
		for ( unsigned int i = 0; i < bones.size(); ++i ) {
			bones[i]->SetSkinFlag(true);
		}
	}
}

void NiNode::SetSkinFlag( bool n ) {
	if ( IsSkinInfluence() == n ) {
		//Already set to the requested value
		return;
	} else {
		//Requested value is different, flip bit
		flags ^= 8;
	}
}

void NiNode::GoToSkeletonBindPosition() {
	//map<NiNodeRef, Matrix44> world_positions;
	
	//Loop through all attached skins, straightening the skeleton on each
	for ( list<NiSkinInstance*>::iterator it = skins.begin(); it != skins.end(); ++it ) {
		//Get Bone list and Skin Data
		vector<NiNodeRef> bone_nodes = (*it)->GetBones();
		NiSkinDataRef skin_data = (*it)->GetSkinData();

		if ( skin_data == NULL ) {
			//There's no skin data for this skin instance; skip it.
			continue;
		}

		//Make sure the counts match
		if ( bone_nodes.size() != skin_data->GetBoneCount() ) {
			throw runtime_error( "Bone counts in NiSkinInstance and attached NiSkinData must match" );
		}

		//Loop through all bones influencing this skin
		for ( unsigned int i = 0; i < bone_nodes.size(); ++i ) {
			//Get current offset Matrix for this bone
			Matrix44 parent_offset = skin_data->GetBoneTransform(i);

			//Loop through all bones again, checking for any that have this bone as a parent
			for ( unsigned int j = 0; j < bone_nodes.size(); ++j ) {
				if ( bone_nodes[j]->GetParent() == bone_nodes[i] ) {
					//Node 2 has node 1 as a parent

					//Get child offset Matrix33
					Matrix44 child_offset = skin_data->GetBoneTransform(j);

					//Do calculation to get correct bone postion in relation to parent
					Matrix44 child_pos = child_offset.Inverse() * parent_offset;

					//bones[j]->SetWorldBindPos( child_pos );
					bone_nodes[j]->SetLocalRotation( child_pos.GetRotation() );
					bone_nodes[j]->SetLocalScale( 1.0f );
					bone_nodes[j]->SetLocalTranslation( child_pos.GetTranslation() );
				}
			}
		}
	}
}

void NiNode::PropagateTransform() {

	Matrix44 par_trans = this->GetLocalTransform();

	//Loop through each child and apply this node's transform to it
	for ( unsigned i = 0; i < children.size(); ++i ) {
		children[i]->SetLocalTransform(
			children[i]->GetLocalTransform() * par_trans
		);
	}

	//Nowthat the transforms have been propogated, clear them out
	this->SetLocalTransform( Matrix44::IDENTITY );
}

bool NiNode::IsSplitMeshProxy() const {
	//Let us guess that a node is a split mesh proxy if:
	// 1)  It is not a skin influence
	// 2)  All its children are NiTriBasedGeom derived objects.
	// 3)  All its children have identity transforms.
	// 4)  It has more than one child
	// 5)  All meshes are visible
	// 6)  ????  May need more criteria as time goes on.

	if ( this->IsSkinInfluence() ) {
		return false;
	}

	if ( children.size() < 2 ) {
		return false;
	}

	for ( unsigned i = 0; i < children.size(); ++i ) {
		if ( children[i]->IsDerivedType( NiTriBasedGeom::TYPE ) == false ) {
			return false;
		}
		if ( children[i]->GetLocalTransform() != Matrix44::IDENTITY ) {
			return false;
		}
		if ( children[i]->GetVisibility() == false ) {
			return false;
		}
	}

	//Made it all the way through the loop without returning false
	return true;
}

//--END CUSTOM CODE--//
