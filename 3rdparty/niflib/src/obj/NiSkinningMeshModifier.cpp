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
#include "../../include/obj/NiSkinningMeshModifier.h"
#include "../../include/gen/SkinTransform.h"
#include "../../include/gen/SkinTransform.h"
#include "../../include/gen/SphereBV.h"
#include "../../include/obj/NiAVObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiSkinningMeshModifier::TYPE("NiSkinningMeshModifier", &NiMeshModifier::TYPE );

NiSkinningMeshModifier::NiSkinningMeshModifier() : flags((unsigned short)0), skeletonRoot(NULL), numBones((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiSkinningMeshModifier::~NiSkinningMeshModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiSkinningMeshModifier::GetType() const {
	return TYPE;
}

NiObject * NiSkinningMeshModifier::Create() {
	return new NiSkinningMeshModifier;
}

void NiSkinningMeshModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiMeshModifier::Read( in, link_stack, info );
	NifStream( flags, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( skeletonTransform.rotation, in, info );
	NifStream( skeletonTransform.translation, in, info );
	NifStream( skeletonTransform.scale, in, info );
	NifStream( numBones, in, info );
	bones.resize(numBones);
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	boneTransforms.resize(numBones);
	for (unsigned int i1 = 0; i1 < boneTransforms.size(); i1++) {
		NifStream( boneTransforms[i1].rotation, in, info );
		NifStream( boneTransforms[i1].translation, in, info );
		NifStream( boneTransforms[i1].scale, in, info );
	};
	if ( (flags & 2) ) {
		boneBounds.resize(numBones);
		for (unsigned int i2 = 0; i2 < boneBounds.size(); i2++) {
			NifStream( boneBounds[i2].center, in, info );
			NifStream( boneBounds[i2].radius, in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiSkinningMeshModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiMeshModifier::Write( out, link_map, missing_link_stack, info );
	numBones = (unsigned int)(bones.size());
	NifStream( flags, out, info );
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
	NifStream( skeletonTransform.rotation, out, info );
	NifStream( skeletonTransform.translation, out, info );
	NifStream( skeletonTransform.scale, out, info );
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
	for (unsigned int i1 = 0; i1 < boneTransforms.size(); i1++) {
		NifStream( boneTransforms[i1].rotation, out, info );
		NifStream( boneTransforms[i1].translation, out, info );
		NifStream( boneTransforms[i1].scale, out, info );
	};
	if ( (flags & 2) ) {
		for (unsigned int i2 = 0; i2 < boneBounds.size(); i2++) {
			NifStream( boneBounds[i2].center, out, info );
			NifStream( boneBounds[i2].radius, out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiSkinningMeshModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiMeshModifier::asString();
	numBones = (unsigned int)(bones.size());
	out << "  Flags:  " << flags << endl;
	out << "  Skeleton Root:  " << skeletonRoot << endl;
	out << "  Rotation:  " << skeletonTransform.rotation << endl;
	out << "  Translation:  " << skeletonTransform.translation << endl;
	out << "  Scale:  " << skeletonTransform.scale << endl;
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
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < boneTransforms.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Rotation:  " << boneTransforms[i1].rotation << endl;
		out << "    Translation:  " << boneTransforms[i1].translation << endl;
		out << "    Scale:  " << boneTransforms[i1].scale << endl;
	};
	if ( (flags & 2) ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < boneBounds.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			out << "      Center:  " << boneBounds[i2].center << endl;
			out << "      Radius:  " << boneBounds[i2].radius << endl;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiSkinningMeshModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiMeshModifier::FixLinks( objects, link_stack, missing_link_stack, info );
	skeletonRoot = FixLink<NiAVObject>( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		bones[i1] = FixLink<NiAVObject>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiSkinningMeshModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiMeshModifier::GetRefs();
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
	};
	return refs;
}

std::list<NiObject *> NiSkinningMeshModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiMeshModifier::GetPtrs();
	if ( skeletonRoot != NULL )
		ptrs.push_back((NiObject *)(skeletonRoot));
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		if ( bones[i1] != NULL )
			ptrs.push_back((NiObject *)(bones[i1]));
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
