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
#include "../../include/obj/NiSkinInstance.h"
#include "../../include/obj/NiNode.h"
#include "../../include/obj/NiSkinData.h"
#include "../../include/obj/NiSkinPartition.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiSkinInstance::TYPE("NiSkinInstance", &NiObject::TYPE );

NiSkinInstance::NiSkinInstance() : data(NULL), skinPartition(NULL), skeletonRoot(NULL), numBones((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiSkinInstance::~NiSkinInstance() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//Unflag any bones that were part of this skin instance
	for ( unsigned int i = 0; i < bones.size(); ++i ) {
		if (bones[i] != NULL)
			bones[i]->SetSkinFlag(false);
	}

	//Inform Skeleton Root of detatchment and clear it.
	if ( skeletonRoot != NULL ) {
		skeletonRoot->RemoveSkin( this );
		skeletonRoot = NULL;
	}

	//--END CUSTOM CODE--//
}

const Type & NiSkinInstance::GetType() const {
	return TYPE;
}

NiObject * NiSkinInstance::Create() {
	return new NiSkinInstance;
}

void NiSkinInstance::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	if ( info.version >= 0x0A020000 ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( numBones, in, info );
	bones.resize(numBones);
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiSkinInstance::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	numBones = (unsigned int)(bones.size());
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
	if ( info.version >= 0x0A020000 ) {
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
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*skeletonRoot), out );
	} else {
		if ( skeletonRoot != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(skeletonRoot) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( skeletonRoot );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	NifStream( numBones, out, info );
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*bones[i1]), out );
		} else {
			if ( bones[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(bones[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( bones[i1] );
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

std::string NiSkinInstance::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numBones = (unsigned int)(bones.size());
	out << "  Data:  " << data << endl;
	out << "  Skin Partition:  " << skinPartition << endl;
	out << "  Skeleton Root:  " << skeletonRoot << endl;
	out << "  Num Bones:  " << numBones << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Bones[" << i1 << "]:  " << bones[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiSkinInstance::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	data = FixLink<NiSkinData>( objects, link_stack, missing_link_stack, info );
	if ( info.version >= 0x0A020000 ) {
		skinPartition = FixLink<NiSkinPartition>( objects, link_stack, missing_link_stack, info );
	};
	skeletonRoot = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		bones[i1] = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//Inform newly fixed skeleton root of attachment
	if ( skeletonRoot != NULL ) {
		skeletonRoot->AddSkin( this );
	}

	//Ensure that bones have the flag set properly
	for ( unsigned int i = 0; i < bones.size(); ++i ) {
		if ( bones[i] != NULL ) {
			bones[i]->SetSkinFlag(true);
		}
	}

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiSkinInstance::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( data != NULL )
		refs.push_back(StaticCast<NiObject>(data));
	if ( skinPartition != NULL )
		refs.push_back(StaticCast<NiObject>(skinPartition));
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
	};
	return refs;
}

std::list<NiObject *> NiSkinInstance::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	if ( skeletonRoot != NULL )
		ptrs.push_back((NiObject *)(skeletonRoot));
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		if ( bones[i1] != NULL )
			ptrs.push_back((NiObject *)(bones[i1]));
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

vector< Ref<NiNode> > NiSkinInstance::GetBones() const {
	vector<NiNodeRef> ref_bones( bones.size() );
	for (unsigned int i = 0; i < bones.size(); ++i ) {
		ref_bones[i] = bones[i];
	}
	return ref_bones;
}

Ref<NiSkinData> NiSkinInstance::GetSkinData() const {
	return data;
}

void NiSkinInstance::SetSkinData( NiSkinData * n ) {
	data = n;
}

Ref<NiSkinPartition> NiSkinInstance::GetSkinPartition() const {
	return skinPartition;
}

void NiSkinInstance::SetSkinPartition( NiSkinPartition * n ) {
	skinPartition = n;
}

void NiSkinInstance::SkeletonLost() {
	skeletonRoot = NULL;

	//Clear bone list
	bones.clear();

	//Destroy skin data
	data = NULL;
	skinPartition = NULL;
}

unsigned int NiSkinInstance::GetBoneCount() const {
	return (unsigned int)(bones.size());
}

Ref<NiNode> NiSkinInstance::GetSkeletonRoot() const {
	return skeletonRoot;
}

void NiSkinInstance::BindSkin( NiNode * skeleton_root, vector< Ref<NiNode> > bone_nodes ) {
	//Call normal constructor
	//NiSkinInstance();

	//Ensure that all bones are below the skeleton root node on the scene graph
	for ( unsigned int i = 0; i < bone_nodes.size(); ++i ) {
		bool is_decended = false;
		NiNodeRef node = bone_nodes[i];
		while ( node != NULL ) {
			if ( node == skeleton_root ) {
				is_decended = true;
				break;
			}
			node = node->GetParent();
		}
		if ( is_decended == false ) {
			throw runtime_error( "All bones must be lower than the skeleton root in the scene graph." );
		}
	}

	//Add the bones to the internal list
	bones.resize( bone_nodes.size() );
	for ( unsigned int i = 0; i < bone_nodes.size(); ++i ) {
		bones[i] = bone_nodes[i];
	}

	//Flag any bones that are part of this skin instance
	for ( unsigned int i = 0; i < bones.size(); ++i ) {
		if ( bones[i] != NULL ) {
			bones[i]->SetSkinFlag(true);
		}
	}

	//Store skeleton root and inform it of this attachment
	skeletonRoot = skeleton_root;
	skeletonRoot->AddSkin( this );
}

//--END CUSTOM CODE--//
