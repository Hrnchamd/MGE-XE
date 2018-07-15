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
#include "../../include/obj/NiPhysXPropDesc.h"
#include "../../include/gen/physXMaterialRef.h"
#include "../../include/obj/NiPhysXMaterialDesc.h"
#include "../../include/obj/NiPhysXActorDesc.h"
#include "../../include/obj/NiPhysXD6JointDesc.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPhysXPropDesc::TYPE("NiPhysXPropDesc", &NiObject::TYPE );

NiPhysXPropDesc::NiPhysXPropDesc() : numDests((int)0), numJoints((unsigned int)0), unknownInt1((int)0), numMaterials((unsigned int)0), unknownInt2((unsigned int)0), unknownInt3((unsigned int)0), unknownInt5((unsigned int)0), unknownByte6((byte)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPhysXPropDesc::~NiPhysXPropDesc() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPhysXPropDesc::GetType() const {
	return TYPE;
}

NiObject * NiPhysXPropDesc::Create() {
	return new NiPhysXPropDesc;
}

void NiPhysXPropDesc::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( numDests, in, info );
	actorDescs.resize(numDests);
	for (unsigned int i1 = 0; i1 < actorDescs.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( numJoints, in, info );
	jointDescs.resize(numJoints);
	for (unsigned int i1 = 0; i1 < jointDescs.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( unknownInt1, in, info );
	NifStream( numMaterials, in, info );
	materialDescs.resize(numMaterials);
	for (unsigned int i1 = 0; i1 < materialDescs.size(); i1++) {
		NifStream( materialDescs[i1].number, in, info );
		NifStream( materialDescs[i1].unknownByte1, in, info );
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( unknownInt2, in, info );
	if ( info.version >= 0x14050000 ) {
		NifStream( unknownInt3, in, info );
		NifStream( unknownString4, in, info );
		NifStream( unknownInt5, in, info );
		NifStream( unknownByte6, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPhysXPropDesc::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	numMaterials = (unsigned int)(materialDescs.size());
	numJoints = (unsigned int)(jointDescs.size());
	numDests = (int)(actorDescs.size());
	NifStream( numDests, out, info );
	for (unsigned int i1 = 0; i1 < actorDescs.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*actorDescs[i1]), out );
		} else {
			if ( actorDescs[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(actorDescs[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( actorDescs[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( numJoints, out, info );
	for (unsigned int i1 = 0; i1 < jointDescs.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*jointDescs[i1]), out );
		} else {
			if ( jointDescs[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(jointDescs[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( jointDescs[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( unknownInt1, out, info );
	NifStream( numMaterials, out, info );
	for (unsigned int i1 = 0; i1 < materialDescs.size(); i1++) {
		NifStream( materialDescs[i1].number, out, info );
		NifStream( materialDescs[i1].unknownByte1, out, info );
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*materialDescs[i1].materialDesc), out );
		} else {
			if ( materialDescs[i1].materialDesc != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(materialDescs[i1].materialDesc) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( materialDescs[i1].materialDesc );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( unknownInt2, out, info );
	if ( info.version >= 0x14050000 ) {
		NifStream( unknownInt3, out, info );
		NifStream( unknownString4, out, info );
		NifStream( unknownInt5, out, info );
		NifStream( unknownByte6, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPhysXPropDesc::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numMaterials = (unsigned int)(materialDescs.size());
	numJoints = (unsigned int)(jointDescs.size());
	numDests = (int)(actorDescs.size());
	out << "  Num Dests:  " << numDests << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < actorDescs.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Actor Descs[" << i1 << "]:  " << actorDescs[i1] << endl;
		array_output_count++;
	};
	out << "  Num Joints:  " << numJoints << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < jointDescs.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Joint Descs[" << i1 << "]:  " << jointDescs[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Num Materials:  " << numMaterials << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < materialDescs.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Number:  " << materialDescs[i1].number << endl;
		out << "    Unknown Byte 1:  " << materialDescs[i1].unknownByte1 << endl;
		out << "    Material Desc:  " << materialDescs[i1].materialDesc << endl;
	};
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Unknown Int 3:  " << unknownInt3 << endl;
	out << "  Unknown String 4:  " << unknownString4 << endl;
	out << "  Unknown Int 5:  " << unknownInt5 << endl;
	out << "  Unknown Byte 6:  " << unknownByte6 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPhysXPropDesc::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < actorDescs.size(); i1++) {
		actorDescs[i1] = FixLink<NiPhysXActorDesc>( objects, link_stack, missing_link_stack, info );
	};
	for (unsigned int i1 = 0; i1 < jointDescs.size(); i1++) {
		jointDescs[i1] = FixLink<NiPhysXD6JointDesc>( objects, link_stack, missing_link_stack, info );
	};
	for (unsigned int i1 = 0; i1 < materialDescs.size(); i1++) {
		materialDescs[i1].materialDesc = FixLink<NiPhysXMaterialDesc>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPhysXPropDesc::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	for (unsigned int i1 = 0; i1 < actorDescs.size(); i1++) {
		if ( actorDescs[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(actorDescs[i1]));
	};
	for (unsigned int i1 = 0; i1 < jointDescs.size(); i1++) {
		if ( jointDescs[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(jointDescs[i1]));
	};
	for (unsigned int i1 = 0; i1 < materialDescs.size(); i1++) {
		if ( materialDescs[i1].materialDesc != NULL )
			refs.push_back(StaticCast<NiObject>(materialDescs[i1].materialDesc));
	};
	return refs;
}

std::list<NiObject *> NiPhysXPropDesc::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	for (unsigned int i1 = 0; i1 < actorDescs.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < jointDescs.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < materialDescs.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
