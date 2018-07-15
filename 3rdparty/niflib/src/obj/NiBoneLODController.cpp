/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include <algorithm>
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiBoneLODController.h"
#include "../../include/gen/NodeGroup.h"
#include "../../include/obj/NiNode.h"
#include "../../include/gen/SkinShapeGroup.h"
#include "../../include/gen/SkinShape.h"
#include "../../include/obj/NiSkinInstance.h"
#include "../../include/obj/NiTriBasedGeom.h"
#include "../../include/gen/SkinShapeGroup.h"
#include "../../include/gen/SkinShape.h"
#include "../../include/obj/NiSkinInstance.h"
#include "../../include/obj/NiTriBasedGeom.h"
#include "../../include/obj/NiTriBasedGeom.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiBoneLODController::TYPE("NiBoneLODController", &NiTimeController::TYPE );

NiBoneLODController::NiBoneLODController() : unknownInt1((unsigned int)0), numNodeGroups((unsigned int)0), numNodeGroups2((unsigned int)0), numShapeGroups((unsigned int)0), numShapeGroups2((unsigned int)0), unknownInt2((int)0), unknownInt3((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiBoneLODController::~NiBoneLODController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiBoneLODController::GetType() const {
	return TYPE;
}

NiObject * NiBoneLODController::Create() {
	return new NiBoneLODController;
}

void NiBoneLODController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiTimeController::Read( in, link_stack, info );
	NifStream( unknownInt1, in, info );
	NifStream( numNodeGroups, in, info );
	NifStream( numNodeGroups2, in, info );
	nodeGroups.resize(numNodeGroups);
	for (unsigned int i1 = 0; i1 < nodeGroups.size(); i1++) {
		NifStream( nodeGroups[i1].numNodes, in, info );
		nodeGroups[i1].nodes.resize(nodeGroups[i1].numNodes);
		for (unsigned int i2 = 0; i2 < nodeGroups[i1].nodes.size(); i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
	};
	if ( ( info.version >= 0x04020200 ) && ( info.userVersion == 0 ) ) {
		NifStream( numShapeGroups, in, info );
	};
	if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x0A020000 ) && ( info.userVersion == 1 ) ) {
		NifStream( numShapeGroups, in, info );
	};
	if ( ( info.version >= 0x04020200 ) && ( info.userVersion == 0 ) ) {
		shapeGroups1.resize(numShapeGroups);
		for (unsigned int i2 = 0; i2 < shapeGroups1.size(); i2++) {
			NifStream( shapeGroups1[i2].numLinkPairs, in, info );
			shapeGroups1[i2].linkPairs.resize(shapeGroups1[i2].numLinkPairs);
			for (unsigned int i3 = 0; i3 < shapeGroups1[i2].linkPairs.size(); i3++) {
				NifStream( block_num, in, info );
				link_stack.push_back( block_num );
				NifStream( block_num, in, info );
				link_stack.push_back( block_num );
			};
		};
	};
	if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x0A020000 ) && ( info.userVersion == 1 ) ) {
		shapeGroups1.resize(numShapeGroups);
		for (unsigned int i2 = 0; i2 < shapeGroups1.size(); i2++) {
			NifStream( shapeGroups1[i2].numLinkPairs, in, info );
			shapeGroups1[i2].linkPairs.resize(shapeGroups1[i2].numLinkPairs);
			for (unsigned int i3 = 0; i3 < shapeGroups1[i2].linkPairs.size(); i3++) {
				NifStream( block_num, in, info );
				link_stack.push_back( block_num );
				NifStream( block_num, in, info );
				link_stack.push_back( block_num );
			};
		};
	};
	if ( ( info.version >= 0x04020200 ) && ( info.userVersion == 0 ) ) {
		NifStream( numShapeGroups2, in, info );
	};
	if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x0A020000 ) && ( info.userVersion == 1 ) ) {
		NifStream( numShapeGroups2, in, info );
	};
	if ( ( info.version >= 0x04020200 ) && ( info.userVersion == 0 ) ) {
		shapeGroups2.resize(numShapeGroups2);
		for (unsigned int i2 = 0; i2 < shapeGroups2.size(); i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
	};
	if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x0A020000 ) && ( info.userVersion == 1 ) ) {
		shapeGroups2.resize(numShapeGroups2);
		for (unsigned int i2 = 0; i2 < shapeGroups2.size(); i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
	};
	if ( ( info.version >= 0x14030009 ) && ( info.version <= 0x14030009 ) && ( info.userVersion == 131072 ) ) {
		NifStream( unknownInt2, in, info );
		NifStream( unknownInt3, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBoneLODController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTimeController::Write( out, link_map, missing_link_stack, info );
	numShapeGroups2 = (unsigned int)(shapeGroups2.size());
	numShapeGroups = (unsigned int)(shapeGroups1.size());
	numNodeGroups = (unsigned int)(nodeGroups.size());
	NifStream( unknownInt1, out, info );
	NifStream( numNodeGroups, out, info );
	NifStream( numNodeGroups2, out, info );
	for (unsigned int i1 = 0; i1 < nodeGroups.size(); i1++) {
		nodeGroups[i1].numNodes = (unsigned int)(nodeGroups[i1].nodes.size());
		NifStream( nodeGroups[i1].numNodes, out, info );
		for (unsigned int i2 = 0; i2 < nodeGroups[i1].nodes.size(); i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*nodeGroups[i1].nodes[i2]), out );
			} else {
				if ( nodeGroups[i1].nodes[i2] != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(nodeGroups[i1].nodes[i2]) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( nodeGroups[i1].nodes[i2] );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
	};
	if ( ( info.version >= 0x04020200 ) && ( info.userVersion == 0 ) ) {
		NifStream( numShapeGroups, out, info );
	};
	if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x0A020000 ) && ( info.userVersion == 1 ) ) {
		NifStream( numShapeGroups, out, info );
	};
	if ( ( info.version >= 0x04020200 ) && ( info.userVersion == 0 ) ) {
		for (unsigned int i2 = 0; i2 < shapeGroups1.size(); i2++) {
			shapeGroups1[i2].numLinkPairs = (unsigned int)(shapeGroups1[i2].linkPairs.size());
			NifStream( shapeGroups1[i2].numLinkPairs, out, info );
			for (unsigned int i3 = 0; i3 < shapeGroups1[i2].linkPairs.size(); i3++) {
				if ( info.version < VER_3_3_0_13 ) {
					WritePtr32( &(*shapeGroups1[i2].linkPairs[i3].shape), out );
				} else {
					if ( shapeGroups1[i2].linkPairs[i3].shape != NULL ) {
						map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(shapeGroups1[i2].linkPairs[i3].shape) );
						if (it != link_map.end()) {
							NifStream( it->second, out, info );
							missing_link_stack.push_back( NULL );
						} else {
							NifStream( 0xFFFFFFFF, out, info );
							missing_link_stack.push_back( shapeGroups1[i2].linkPairs[i3].shape );
						}
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( NULL );
					}
				}
				if ( info.version < VER_3_3_0_13 ) {
					WritePtr32( &(*shapeGroups1[i2].linkPairs[i3].skinInstance), out );
				} else {
					if ( shapeGroups1[i2].linkPairs[i3].skinInstance != NULL ) {
						map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(shapeGroups1[i2].linkPairs[i3].skinInstance) );
						if (it != link_map.end()) {
							NifStream( it->second, out, info );
							missing_link_stack.push_back( NULL );
						} else {
							NifStream( 0xFFFFFFFF, out, info );
							missing_link_stack.push_back( shapeGroups1[i2].linkPairs[i3].skinInstance );
						}
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( NULL );
					}
				}
			};
		};
	};
	if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x0A020000 ) && ( info.userVersion == 1 ) ) {
		for (unsigned int i2 = 0; i2 < shapeGroups1.size(); i2++) {
			shapeGroups1[i2].numLinkPairs = (unsigned int)(shapeGroups1[i2].linkPairs.size());
			NifStream( shapeGroups1[i2].numLinkPairs, out, info );
			for (unsigned int i3 = 0; i3 < shapeGroups1[i2].linkPairs.size(); i3++) {
				if ( info.version < VER_3_3_0_13 ) {
					WritePtr32( &(*shapeGroups1[i2].linkPairs[i3].shape), out );
				} else {
					if ( shapeGroups1[i2].linkPairs[i3].shape != NULL ) {
						map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(shapeGroups1[i2].linkPairs[i3].shape) );
						if (it != link_map.end()) {
							NifStream( it->second, out, info );
							missing_link_stack.push_back( NULL );
						} else {
							NifStream( 0xFFFFFFFF, out, info );
							missing_link_stack.push_back( shapeGroups1[i2].linkPairs[i3].shape );
						}
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( NULL );
					}
				}
				if ( info.version < VER_3_3_0_13 ) {
					WritePtr32( &(*shapeGroups1[i2].linkPairs[i3].skinInstance), out );
				} else {
					if ( shapeGroups1[i2].linkPairs[i3].skinInstance != NULL ) {
						map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(shapeGroups1[i2].linkPairs[i3].skinInstance) );
						if (it != link_map.end()) {
							NifStream( it->second, out, info );
							missing_link_stack.push_back( NULL );
						} else {
							NifStream( 0xFFFFFFFF, out, info );
							missing_link_stack.push_back( shapeGroups1[i2].linkPairs[i3].skinInstance );
						}
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( NULL );
					}
				}
			};
		};
	};
	if ( ( info.version >= 0x04020200 ) && ( info.userVersion == 0 ) ) {
		NifStream( numShapeGroups2, out, info );
	};
	if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x0A020000 ) && ( info.userVersion == 1 ) ) {
		NifStream( numShapeGroups2, out, info );
	};
	if ( ( info.version >= 0x04020200 ) && ( info.userVersion == 0 ) ) {
		for (unsigned int i2 = 0; i2 < shapeGroups2.size(); i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*shapeGroups2[i2]), out );
			} else {
				if ( shapeGroups2[i2] != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(shapeGroups2[i2]) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( shapeGroups2[i2] );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
	};
	if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x0A020000 ) && ( info.userVersion == 1 ) ) {
		for (unsigned int i2 = 0; i2 < shapeGroups2.size(); i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*shapeGroups2[i2]), out );
			} else {
				if ( shapeGroups2[i2] != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(shapeGroups2[i2]) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( shapeGroups2[i2] );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
	};
	if ( ( info.version >= 0x14030009 ) && ( info.version <= 0x14030009 ) && ( info.userVersion == 131072 ) ) {
		NifStream( unknownInt2, out, info );
		NifStream( unknownInt3, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiBoneLODController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiTimeController::asString();
	numShapeGroups2 = (unsigned int)(shapeGroups2.size());
	numShapeGroups = (unsigned int)(shapeGroups1.size());
	numNodeGroups = (unsigned int)(nodeGroups.size());
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Num Node Groups:  " << numNodeGroups << endl;
	out << "  Num Node Groups 2:  " << numNodeGroups2 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < nodeGroups.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		nodeGroups[i1].numNodes = (unsigned int)(nodeGroups[i1].nodes.size());
		out << "    Num Nodes:  " << nodeGroups[i1].numNodes << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < nodeGroups[i1].nodes.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Nodes[" << i2 << "]:  " << nodeGroups[i1].nodes[i2] << endl;
			array_output_count++;
		};
	};
	out << "  Num Shape Groups:  " << numShapeGroups << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < shapeGroups1.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		shapeGroups1[i1].numLinkPairs = (unsigned int)(shapeGroups1[i1].linkPairs.size());
		out << "    Num Link Pairs:  " << shapeGroups1[i1].numLinkPairs << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < shapeGroups1[i1].linkPairs.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			out << "      Shape:  " << shapeGroups1[i1].linkPairs[i2].shape << endl;
			out << "      Skin Instance:  " << shapeGroups1[i1].linkPairs[i2].skinInstance << endl;
		};
	};
	out << "  Num Shape Groups 2:  " << numShapeGroups2 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < shapeGroups2.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Shape Groups 2[" << i1 << "]:  " << shapeGroups2[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Unknown Int 3:  " << unknownInt3 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBoneLODController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTimeController::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < nodeGroups.size(); i1++) {
		for (unsigned int i2 = 0; i2 < nodeGroups[i1].nodes.size(); i2++) {
			nodeGroups[i1].nodes[i2] = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );
		};
	};
	if ( ( info.version >= 0x04020200 ) && ( info.userVersion == 0 ) ) {
		for (unsigned int i2 = 0; i2 < shapeGroups1.size(); i2++) {
			for (unsigned int i3 = 0; i3 < shapeGroups1[i2].linkPairs.size(); i3++) {
				shapeGroups1[i2].linkPairs[i3].shape = FixLink<NiTriBasedGeom>( objects, link_stack, missing_link_stack, info );
				shapeGroups1[i2].linkPairs[i3].skinInstance = FixLink<NiSkinInstance>( objects, link_stack, missing_link_stack, info );
			};
		};
	};
	if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x0A020000 ) && ( info.userVersion == 1 ) ) {
		for (unsigned int i2 = 0; i2 < shapeGroups1.size(); i2++) {
			for (unsigned int i3 = 0; i3 < shapeGroups1[i2].linkPairs.size(); i3++) {
				shapeGroups1[i2].linkPairs[i3].shape = FixLink<NiTriBasedGeom>( objects, link_stack, missing_link_stack, info );
				shapeGroups1[i2].linkPairs[i3].skinInstance = FixLink<NiSkinInstance>( objects, link_stack, missing_link_stack, info );
			};
		};
	};
	if ( ( info.version >= 0x04020200 ) && ( info.userVersion == 0 ) ) {
		for (unsigned int i2 = 0; i2 < shapeGroups2.size(); i2++) {
			shapeGroups2[i2] = FixLink<NiTriBasedGeom>( objects, link_stack, missing_link_stack, info );
		};
	};
	if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x0A020000 ) && ( info.userVersion == 1 ) ) {
		for (unsigned int i2 = 0; i2 < shapeGroups2.size(); i2++) {
			shapeGroups2[i2] = FixLink<NiTriBasedGeom>( objects, link_stack, missing_link_stack, info );
		};
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBoneLODController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiTimeController::GetRefs();
	for (unsigned int i1 = 0; i1 < nodeGroups.size(); i1++) {
		for (unsigned int i2 = 0; i2 < nodeGroups[i1].nodes.size(); i2++) {
		};
	};
	for (unsigned int i1 = 0; i1 < shapeGroups1.size(); i1++) {
		for (unsigned int i2 = 0; i2 < shapeGroups1[i1].linkPairs.size(); i2++) {
			if ( shapeGroups1[i1].linkPairs[i2].skinInstance != NULL )
				refs.push_back(StaticCast<NiObject>(shapeGroups1[i1].linkPairs[i2].skinInstance));
		};
	};
	for (unsigned int i1 = 0; i1 < shapeGroups1.size(); i1++) {
		for (unsigned int i2 = 0; i2 < shapeGroups1[i1].linkPairs.size(); i2++) {
			if ( shapeGroups1[i1].linkPairs[i2].skinInstance != NULL )
				refs.push_back(StaticCast<NiObject>(shapeGroups1[i1].linkPairs[i2].skinInstance));
		};
	};
	for (unsigned int i1 = 0; i1 < shapeGroups2.size(); i1++) {
		if ( shapeGroups2[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(shapeGroups2[i1]));
	};
	for (unsigned int i1 = 0; i1 < shapeGroups2.size(); i1++) {
	};
	return refs;
}

std::list<NiObject *> NiBoneLODController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiTimeController::GetPtrs();
	for (unsigned int i1 = 0; i1 < nodeGroups.size(); i1++) {
		for (unsigned int i2 = 0; i2 < nodeGroups[i1].nodes.size(); i2++) {
			if ( nodeGroups[i1].nodes[i2] != NULL )
				ptrs.push_back((NiObject *)(nodeGroups[i1].nodes[i2]));
		};
	};
	for (unsigned int i1 = 0; i1 < shapeGroups1.size(); i1++) {
		for (unsigned int i2 = 0; i2 < shapeGroups1[i1].linkPairs.size(); i2++) {
			if ( shapeGroups1[i1].linkPairs[i2].shape != NULL )
				ptrs.push_back((NiObject *)(shapeGroups1[i1].linkPairs[i2].shape));
		};
	};
	for (unsigned int i1 = 0; i1 < shapeGroups1.size(); i1++) {
		for (unsigned int i2 = 0; i2 < shapeGroups1[i1].linkPairs.size(); i2++) {
			if ( shapeGroups1[i1].linkPairs[i2].shape != NULL )
				ptrs.push_back((NiObject *)(shapeGroups1[i1].linkPairs[i2].shape));
		};
	};
	for (unsigned int i1 = 0; i1 < shapeGroups2.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < shapeGroups2.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

/*!
 * A list of node groups (each group a sequence of bones?).
 */
int NiBoneLODController::GetNodeGroupCount() const {
   return int(nodeGroups.size());
}

vector<Ref<NiNode> > NiBoneLODController::GetNodeGroup( int index ) const {
   if (index < 0 || index >= int(nodeGroups.size()) ) {
      throw runtime_error("Invalid index referenced.");
   }
   vector<NiNodeRef> value;
   const vector<NiNode*>& nodes = nodeGroups[index].nodes;
   for (vector<NiNode*>::const_iterator itr = nodes.begin(); itr != nodes.end(); ++itr)
      value.push_back(*itr);
   return value;
}

void NiBoneLODController::AddNodeToGroup( int index, NiNode * node ) {
   while (index >= int(nodeGroups.size()))
      nodeGroups.insert(nodeGroups.end(), NodeGroup() );
   numNodeGroups2 = int(nodeGroups.size());

   vector<NiNode*>& nodes = nodeGroups[index].nodes;
   vector<NiNode*>::iterator itr = std::find(nodes.begin(), nodes.end(), node);
   if (itr == nodes.end())
      nodes.push_back(node);
}

void NiBoneLODController::RemoveNodeFromGroup( int index, NiNode * node ) {
   if (index < 0 || index >= int(nodeGroups.size()) ) {
      throw runtime_error("Invalid index referenced.");
   }
   vector<NiNode*>& nodes = nodeGroups[index].nodes;
   vector<NiNode*>::iterator itr = std::find(nodes.begin(), nodes.end(), node);
   if (itr == nodes.end())
      return;
   nodes.erase(itr);
}

void NiBoneLODController::SetNodeGroup( int index, const vector<Ref<NiNode> >& group ) {
   while (index >= int(nodeGroups.size()))
      nodeGroups.insert(nodeGroups.end(), NodeGroup() );
   numNodeGroups2 = int(nodeGroups.size());
   nodeGroups[index].nodes.assign(group.begin(), group.end());
}

void NiBoneLODController::RemoveNodeGroup( int index ) {
   if (index < 0 || index >= int(nodeGroups.size()) ) {
      throw runtime_error("Invalid index referenced.");
   }
   vector<NodeGroup>::iterator itr = nodeGroups.begin();
   std::advance(itr, index);
   nodeGroups.erase(itr);
   numNodeGroups2 = int(nodeGroups.size());
}

void NiBoneLODController::ClearNodeGroups() {
   nodeGroups.clear();
   numNodeGroups2 = int(nodeGroups.size());
}

bool NiBoneLODController::AddShapeToGroup( Ref<NiTriBasedGeom > shape ) {
    vector<Ref<NiTriBasedGeom > >& shapes = shapeGroups2;
    vector<Ref<NiTriBasedGeom > >::iterator itr = std::find(shapes.begin(), shapes.end(), shape);
    if (itr == shapes.end()) {
	shapes.push_back(shape);
	numShapeGroups2++;

	return true;
    }

    return false;
}

bool NiBoneLODController::RemoveShapeFromGroup( Ref<NiTriBasedGeom > shape ) {
    vector<Ref<NiTriBasedGeom > >& shapes = shapeGroups2;
    vector<Ref<NiTriBasedGeom > >::iterator itr = std::find(shapes.begin(), shapes.end(), shape);
    if (itr != shapes.end()) {
	shapes.erase(itr);
	numShapeGroups2--;

	return true;
    }

    return false;
}

bool NiBoneLODController::ReplaceShapeInGroup( Ref<NiTriBasedGeom > newshape, Ref<NiTriBasedGeom > oldshape ) {
    vector<Ref<NiTriBasedGeom > >& shapes = shapeGroups2;
    vector<Ref<NiTriBasedGeom > >::iterator itr = std::find(shapes.begin(), shapes.end(), oldshape);
    if (itr != shapes.end()) {
	*itr = newshape;

	return true;
    }

    return false;
}


//--END CUSTOM CODE--//
