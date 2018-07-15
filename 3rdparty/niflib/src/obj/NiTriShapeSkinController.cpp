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
#include "../../include/obj/NiTriShapeSkinController.h"
#include "../../include/gen/OldSkinData.h"
#include "../../include/obj/NiBone.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiTriShapeSkinController::TYPE("NiTriShapeSkinController", &NiTimeController::TYPE );

NiTriShapeSkinController::NiTriShapeSkinController() : numBones((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiTriShapeSkinController::~NiTriShapeSkinController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiTriShapeSkinController::GetType() const {
	return TYPE;
}

NiObject * NiTriShapeSkinController::Create() {
	return new NiTriShapeSkinController;
}

void NiTriShapeSkinController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiTimeController::Read( in, link_stack, info );
	NifStream( numBones, in, info );
	vertexCounts.resize(numBones);
	for (unsigned int i1 = 0; i1 < vertexCounts.size(); i1++) {
		NifStream( vertexCounts[i1], in, info );
	};
	bones.resize(numBones);
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	boneData.resize(numBones);
	for (unsigned int i1 = 0; i1 < boneData.size(); i1++) {
		boneData[i1].resize(vertexCounts[i1]);
		for (unsigned int i2 = 0; i2 < vertexCounts[i1]; i2++) {
			NifStream( boneData[i1][i2].vertexWeight, in, info );
			NifStream( boneData[i1][i2].vertexIndex, in, info );
			NifStream( boneData[i1][i2].unknownVector, in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTriShapeSkinController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTimeController::Write( out, link_map, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < boneData.size(); i1++)
		vertexCounts[i1] = (unsigned int)(boneData[i1].size());
	numBones = (unsigned int)(vertexCounts.size());
	NifStream( numBones, out, info );
	for (unsigned int i1 = 0; i1 < vertexCounts.size(); i1++) {
		NifStream( vertexCounts[i1], out, info );
	};
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
	for (unsigned int i1 = 0; i1 < boneData.size(); i1++) {
		for (unsigned int i2 = 0; i2 < vertexCounts[i1]; i2++) {
			NifStream( boneData[i1][i2].vertexWeight, out, info );
			NifStream( boneData[i1][i2].vertexIndex, out, info );
			NifStream( boneData[i1][i2].unknownVector, out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiTriShapeSkinController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiTimeController::asString();
	for (unsigned int i1 = 0; i1 < boneData.size(); i1++)
		vertexCounts[i1] = (unsigned int)(boneData[i1].size());
	numBones = (unsigned int)(vertexCounts.size());
	out << "  Num Bones:  " << numBones << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < vertexCounts.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Vertex Counts[" << i1 << "]:  " << vertexCounts[i1] << endl;
		array_output_count++;
	};
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
	for (unsigned int i1 = 0; i1 < boneData.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		for (unsigned int i2 = 0; i2 < vertexCounts[i1]; i2++) {
			out << "      Vertex Weight:  " << boneData[i1][i2].vertexWeight << endl;
			out << "      Vertex Index:  " << boneData[i1][i2].vertexIndex << endl;
			out << "      Unknown Vector:  " << boneData[i1][i2].unknownVector << endl;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTriShapeSkinController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTimeController::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		bones[i1] = FixLink<NiBone>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiTriShapeSkinController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiTimeController::GetRefs();
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
	};
	return refs;
}

std::list<NiObject *> NiTriShapeSkinController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiTimeController::GetPtrs();
	for (unsigned int i1 = 0; i1 < bones.size(); i1++) {
		if ( bones[i1] != NULL )
			ptrs.push_back((NiObject *)(bones[i1]));
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
