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
#include "../../include/obj/NiRoom.h"
#include "../../include/obj/NiAVObject.h"
#include "../../include/obj/NiPortal.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiRoom::TYPE("NiRoom", &NiNode::TYPE );

NiRoom::NiRoom() : numWalls((int)0), numInPortals((int)0), numPortals2((int)0), numItems((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiRoom::~NiRoom() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiRoom::GetType() const {
	return TYPE;
}

NiObject * NiRoom::Create() {
	return new NiRoom;
}

void NiRoom::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiNode::Read( in, link_stack, info );
	NifStream( numWalls, in, info );
	wallPlane.resize(numWalls);
	for (unsigned int i1 = 0; i1 < wallPlane.size(); i1++) {
		NifStream( wallPlane[i1], in, info );
	};
	NifStream( numInPortals, in, info );
	inPortals.resize(numInPortals);
	for (unsigned int i1 = 0; i1 < inPortals.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( numPortals2, in, info );
	portals2.resize(numPortals2);
	for (unsigned int i1 = 0; i1 < portals2.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( numItems, in, info );
	items.resize(numItems);
	for (unsigned int i1 = 0; i1 < items.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiRoom::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiNode::Write( out, link_map, missing_link_stack, info );
	numItems = (int)(items.size());
	numPortals2 = (int)(portals2.size());
	numInPortals = (int)(inPortals.size());
	numWalls = (int)(wallPlane.size());
	NifStream( numWalls, out, info );
	for (unsigned int i1 = 0; i1 < wallPlane.size(); i1++) {
		NifStream( wallPlane[i1], out, info );
	};
	NifStream( numInPortals, out, info );
	for (unsigned int i1 = 0; i1 < inPortals.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*inPortals[i1]), out );
		} else {
			if ( inPortals[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(inPortals[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( inPortals[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( numPortals2, out, info );
	for (unsigned int i1 = 0; i1 < portals2.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*portals2[i1]), out );
		} else {
			if ( portals2[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(portals2[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( portals2[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( numItems, out, info );
	for (unsigned int i1 = 0; i1 < items.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*items[i1]), out );
		} else {
			if ( items[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(items[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( items[i1] );
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

std::string NiRoom::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiNode::asString();
	numItems = (int)(items.size());
	numPortals2 = (int)(portals2.size());
	numInPortals = (int)(inPortals.size());
	numWalls = (int)(wallPlane.size());
	out << "  Num Walls:  " << numWalls << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < wallPlane.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Wall Plane[" << i1 << "]:  " << wallPlane[i1] << endl;
		array_output_count++;
	};
	out << "  Num In Portals:  " << numInPortals << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < inPortals.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    In Portals[" << i1 << "]:  " << inPortals[i1] << endl;
		array_output_count++;
	};
	out << "  Num Portals 2:  " << numPortals2 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < portals2.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Portals 2[" << i1 << "]:  " << portals2[i1] << endl;
		array_output_count++;
	};
	out << "  Num Items:  " << numItems << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < items.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Items[" << i1 << "]:  " << items[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiRoom::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiNode::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < inPortals.size(); i1++) {
		inPortals[i1] = FixLink<NiPortal>( objects, link_stack, missing_link_stack, info );
	};
	for (unsigned int i1 = 0; i1 < portals2.size(); i1++) {
		portals2[i1] = FixLink<NiPortal>( objects, link_stack, missing_link_stack, info );
	};
	for (unsigned int i1 = 0; i1 < items.size(); i1++) {
		items[i1] = FixLink<NiAVObject>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiRoom::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiNode::GetRefs();
	for (unsigned int i1 = 0; i1 < inPortals.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < portals2.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < items.size(); i1++) {
	};
	return refs;
}

std::list<NiObject *> NiRoom::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiNode::GetPtrs();
	for (unsigned int i1 = 0; i1 < inPortals.size(); i1++) {
		if ( inPortals[i1] != NULL )
			ptrs.push_back((NiObject *)(inPortals[i1]));
	};
	for (unsigned int i1 = 0; i1 < portals2.size(); i1++) {
		if ( portals2[i1] != NULL )
			ptrs.push_back((NiObject *)(portals2[i1]));
	};
	for (unsigned int i1 = 0; i1 < items.size(); i1++) {
		if ( items[i1] != NULL )
			ptrs.push_back((NiObject *)(items[i1]));
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
