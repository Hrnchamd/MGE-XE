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
#include "../../include/obj/NiFurSpringController.h"
#include "../../include/obj/NiNode.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiFurSpringController::TYPE("NiFurSpringController", &NiTimeController::TYPE );

NiFurSpringController::NiFurSpringController() : unknownFloat(0.0f), unknownFloat2(0.0f), numBones((unsigned int)0), numBones2((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiFurSpringController::~NiFurSpringController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiFurSpringController::GetType() const {
	return TYPE;
}

NiObject * NiFurSpringController::Create() {
	return new NiFurSpringController;
}

void NiFurSpringController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiTimeController::Read( in, link_stack, info );
	NifStream( unknownFloat, in, info );
	NifStream( unknownFloat2, in, info );
	NifStream( numBones, in, info );
	bones.resize(numBones);
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( numBones2, in, info );
	bones2.resize(numBones2);
	for (unsigned int i1 = 0; i1 < bones2.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiFurSpringController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiTimeController::Write( out, link_map, missing_link_stack, info );
	numBones2 = (unsigned int)(bones2.size());
	numBones = (unsigned int)(bones.size());
	NifStream( unknownFloat, out, info );
	NifStream( unknownFloat2, out, info );
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
	NifStream( numBones2, out, info );
	for (unsigned int i1 = 0; i1 < bones2.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*bones2[i1]), out );
		} else {
			if ( bones2[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(bones2[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( bones2[i1] );
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

std::string NiFurSpringController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiTimeController::asString();
	numBones2 = (unsigned int)(bones2.size());
	numBones = (unsigned int)(bones.size());
	out << "  Unknown Float:  " << unknownFloat << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
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
	out << "  Num Bones 2:  " << numBones2 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < bones2.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Bones 2[" << i1 << "]:  " << bones2[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiFurSpringController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiTimeController::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		bones[i1] = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );
	};
	for (unsigned int i1 = 0; i1 < bones2.size(); i1++) {
		bones2[i1] = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiFurSpringController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiTimeController::GetRefs();
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < bones2.size(); i1++) {
	};
	return refs;
}

std::list<NiObject *> NiFurSpringController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiTimeController::GetPtrs();
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		if ( bones[i1] != NULL )
			ptrs.push_back((NiObject *)(bones[i1]));
	};
	for (unsigned int i1 = 0; i1 < bones2.size(); i1++) {
		if ( bones2[i1] != NULL )
			ptrs.push_back((NiObject *)(bones2[i1]));
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
