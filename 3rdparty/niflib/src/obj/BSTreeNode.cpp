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
#include "../../include/obj/BSTreeNode.h"
#include "../../include/obj/NiNode.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSTreeNode::TYPE("BSTreeNode", &NiNode::TYPE );

BSTreeNode::BSTreeNode() : numBones1((unsigned int)0), numBones2((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSTreeNode::~BSTreeNode() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSTreeNode::GetType() const {
	return TYPE;
}

NiObject * BSTreeNode::Create() {
	return new BSTreeNode;
}

void BSTreeNode::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiNode::Read( in, link_stack, info );
	NifStream( numBones1, in, info );
	bones1.resize(numBones1);
	for (unsigned int i1 = 0; i1 < bones1.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( numBones2, in, info );
	bones.resize(numBones2);
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSTreeNode::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiNode::Write( out, link_map, missing_link_stack, info );
	numBones2 = (unsigned int)(bones.size());
	numBones1 = (unsigned int)(bones1.size());
	NifStream( numBones1, out, info );
	for (unsigned int i1 = 0; i1 < bones1.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*bones1[i1]), out );
		} else {
			if ( bones1[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(bones1[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( bones1[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( numBones2, out, info );
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

std::string BSTreeNode::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiNode::asString();
	numBones2 = (unsigned int)(bones.size());
	numBones1 = (unsigned int)(bones1.size());
	out << "  Num Bones 1:  " << numBones1 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < bones1.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Bones 1[" << i1 << "]:  " << bones1[i1] << endl;
		array_output_count++;
	};
	out << "  Num Bones 2:  " << numBones2 << endl;
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

void BSTreeNode::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiNode::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < bones1.size(); i1++) {
		bones1[i1] = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );
	};
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		bones[i1] = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSTreeNode::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiNode::GetRefs();
	for (unsigned int i1 = 0; i1 < bones1.size(); i1++) {
		if ( bones1[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(bones1[i1]));
	};
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		if ( bones[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(bones[i1]));
	};
	return refs;
}

std::list<NiObject *> BSTreeNode::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiNode::GetPtrs();
	for (unsigned int i1 = 0; i1 < bones1.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
