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
#include "../../include/obj/NiLODNode.h"
#include "../../include/gen/LODRange.h"
#include "../../include/obj/NiLODData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiLODNode::TYPE("NiLODNode", &NiSwitchNode::TYPE );

NiLODNode::NiLODNode() : numLodLevels((unsigned int)0), lodLevelData(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiLODNode::~NiLODNode() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiLODNode::GetType() const {
	return TYPE;
}

NiObject * NiLODNode::Create() {
	return new NiLODNode;
}

void NiLODNode::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiSwitchNode::Read( in, link_stack, info );
	if ( ( info.version >= 0x04000002 ) && ( info.version <= 0x0A000100 ) ) {
		NifStream( lodCenter, in, info );
	};
	if ( info.version <= 0x0A000100 ) {
		NifStream( numLodLevels, in, info );
		lodLevels.resize(numLodLevels);
		for (unsigned int i2 = 0; i2 < lodLevels.size(); i2++) {
			NifStream( lodLevels[i2].nearExtent, in, info );
			NifStream( lodLevels[i2].farExtent, in, info );
			if ( info.version <= 0x03010000 ) {
				for (unsigned int i4 = 0; i4 < 3; i4++) {
					NifStream( lodLevels[i2].unknownInts[i4], in, info );
				};
			};
		};
	};
	if ( info.version >= 0x0A010000 ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiLODNode::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiSwitchNode::Write( out, link_map, missing_link_stack, info );
	numLodLevels = (unsigned int)(lodLevels.size());
	if ( ( info.version >= 0x04000002 ) && ( info.version <= 0x0A000100 ) ) {
		NifStream( lodCenter, out, info );
	};
	if ( info.version <= 0x0A000100 ) {
		NifStream( numLodLevels, out, info );
		for (unsigned int i2 = 0; i2 < lodLevels.size(); i2++) {
			NifStream( lodLevels[i2].nearExtent, out, info );
			NifStream( lodLevels[i2].farExtent, out, info );
			if ( info.version <= 0x03010000 ) {
				for (unsigned int i4 = 0; i4 < 3; i4++) {
					NifStream( lodLevels[i2].unknownInts[i4], out, info );
				};
			};
		};
	};
	if ( info.version >= 0x0A010000 ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*lodLevelData), out );
		} else {
			if ( lodLevelData != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(lodLevelData) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( lodLevelData );
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

std::string NiLODNode::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiSwitchNode::asString();
	numLodLevels = (unsigned int)(lodLevels.size());
	out << "  LOD Center:  " << lodCenter << endl;
	out << "  Num LOD Levels:  " << numLodLevels << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < lodLevels.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Near Extent:  " << lodLevels[i1].nearExtent << endl;
		out << "    Far Extent:  " << lodLevels[i1].farExtent << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown Ints[" << i2 << "]:  " << lodLevels[i1].unknownInts[i2] << endl;
			array_output_count++;
		};
	};
	out << "  LOD Level Data:  " << lodLevelData << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiLODNode::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiSwitchNode::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( info.version >= 0x0A010000 ) {
		lodLevelData = FixLink<NiLODData>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiLODNode::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiSwitchNode::GetRefs();
	if ( lodLevelData != NULL )
		refs.push_back(StaticCast<NiObject>(lodLevelData));
	return refs;
}

std::list<NiObject *> NiLODNode::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiSwitchNode::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Vector3 NiLODNode::GetLODCenter() const {
	return lodCenter;
}

void NiLODNode::SetLODCenter( const Vector3 & value ) {
	lodCenter = value;
}

vector<LODRange > NiLODNode::GetLODLevels() const {
	return lodLevels;
}

void NiLODNode::SetLODLevels( const vector<LODRange >& value ) {
	lodLevels = value;
}

Ref<NiLODData > NiLODNode::GetLODLevelData() const {
	return lodLevelData;
}

void NiLODNode::SetLODLevelData( Ref<NiLODData > value ) {
	lodLevelData = value;
}

//--END CUSTOM CODE--//
