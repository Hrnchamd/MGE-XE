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
#include "../../include/obj/BSPSysHavokUpdateModifier.h"
#include "../../include/obj/NiNode.h"
#include "../../include/obj/NiPSysModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSPSysHavokUpdateModifier::TYPE("BSPSysHavokUpdateModifier", &NiPSysModifier::TYPE );

BSPSysHavokUpdateModifier::BSPSysHavokUpdateModifier() : numNodes((unsigned int)0), modifier(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSPSysHavokUpdateModifier::~BSPSysHavokUpdateModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSPSysHavokUpdateModifier::GetType() const {
	return TYPE;
}

NiObject * BSPSysHavokUpdateModifier::Create() {
	return new BSPSysHavokUpdateModifier;
}

void BSPSysHavokUpdateModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiPSysModifier::Read( in, link_stack, info );
	NifStream( numNodes, in, info );
	nodes.resize(numNodes);
	for (unsigned int i1 = 0; i1 < nodes.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSPSysHavokUpdateModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifier::Write( out, link_map, missing_link_stack, info );
	numNodes = (unsigned int)(nodes.size());
	NifStream( numNodes, out, info );
	for (unsigned int i1 = 0; i1 < nodes.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*nodes[i1]), out );
		} else {
			if ( nodes[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(nodes[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( nodes[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*modifier), out );
	} else {
		if ( modifier != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(modifier) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( modifier );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSPSysHavokUpdateModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiPSysModifier::asString();
	numNodes = (unsigned int)(nodes.size());
	out << "  Num Nodes:  " << numNodes << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < nodes.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Nodes[" << i1 << "]:  " << nodes[i1] << endl;
		array_output_count++;
	};
	out << "  Modifier:  " << modifier << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSPSysHavokUpdateModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifier::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < nodes.size(); i1++) {
		nodes[i1] = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );
	};
	modifier = FixLink<NiPSysModifier>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSPSysHavokUpdateModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifier::GetRefs();
	for (unsigned int i1 = 0; i1 < nodes.size(); i1++) {
		if ( nodes[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(nodes[i1]));
	};
	if ( modifier != NULL )
		refs.push_back(StaticCast<NiObject>(modifier));
	return refs;
}

std::list<NiObject *> BSPSysHavokUpdateModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifier::GetPtrs();
	for (unsigned int i1 = 0; i1 < nodes.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
