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
#include "../../include/obj/NiRoomGroup.h"
#include "../../include/obj/NiNode.h"
#include "../../include/obj/NiRoom.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiRoomGroup::TYPE("NiRoomGroup", &NiNode::TYPE );

NiRoomGroup::NiRoomGroup() : shellLink(NULL), numRooms((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiRoomGroup::~NiRoomGroup() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiRoomGroup::GetType() const {
	return TYPE;
}

NiObject * NiRoomGroup::Create() {
	return new NiRoomGroup;
}

void NiRoomGroup::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiNode::Read( in, link_stack, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( numRooms, in, info );
	rooms.resize(numRooms);
	for (unsigned int i1 = 0; i1 < rooms.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiRoomGroup::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiNode::Write( out, link_map, missing_link_stack, info );
	numRooms = (int)(rooms.size());
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*shellLink), out );
	} else {
		if ( shellLink != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(shellLink) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( shellLink );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	NifStream( numRooms, out, info );
	for (unsigned int i1 = 0; i1 < rooms.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*rooms[i1]), out );
		} else {
			if ( rooms[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(rooms[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( rooms[i1] );
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

std::string NiRoomGroup::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiNode::asString();
	numRooms = (int)(rooms.size());
	out << "  Shell Link:  " << shellLink << endl;
	out << "  Num Rooms:  " << numRooms << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < rooms.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Rooms[" << i1 << "]:  " << rooms[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiRoomGroup::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiNode::FixLinks( objects, link_stack, missing_link_stack, info );
	shellLink = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < rooms.size(); i1++) {
		rooms[i1] = FixLink<NiRoom>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiRoomGroup::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiNode::GetRefs();
	for (unsigned int i1 = 0; i1 < rooms.size(); i1++) {
	};
	return refs;
}

std::list<NiObject *> NiRoomGroup::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiNode::GetPtrs();
	if ( shellLink != NULL )
		ptrs.push_back((NiObject *)(shellLink));
	for (unsigned int i1 = 0; i1 < rooms.size(); i1++) {
		if ( rooms[i1] != NULL )
			ptrs.push_back((NiObject *)(rooms[i1]));
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
