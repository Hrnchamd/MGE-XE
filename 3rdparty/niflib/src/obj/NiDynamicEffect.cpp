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
#include "../../include/obj/NiDynamicEffect.h"
#include "../../include/obj/NiAVObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiDynamicEffect::TYPE("NiDynamicEffect", &NiAVObject::TYPE );

NiDynamicEffect::NiDynamicEffect() : switchState(false), numAffectedNodeListPointers((unsigned int)0), numAffectedNodes((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiDynamicEffect::~NiDynamicEffect() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiDynamicEffect::GetType() const {
	return TYPE;
}

NiObject * NiDynamicEffect::Create() {
	return new NiDynamicEffect;
}

void NiDynamicEffect::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiAVObject::Read( in, link_stack, info );
	if ( info.version >= 0x0A01006A ) {
		NifStream( switchState, in, info );
	};
	if ( info.version <= 0x04000002 ) {
		NifStream( numAffectedNodeListPointers, in, info );
	};
	if ( info.version >= 0x0A010000 ) {
		NifStream( numAffectedNodes, in, info );
	};
	if ( info.version <= 0x04000002 ) {
		affectedNodeListPointers.resize(numAffectedNodeListPointers);
		for (unsigned int i2 = 0; i2 < affectedNodeListPointers.size(); i2++) {
			NifStream( affectedNodeListPointers[i2], in, info );
		};
	};
	if ( info.version >= 0x0A010000 ) {
		affectedNodes.resize(numAffectedNodes);
		for (unsigned int i2 = 0; i2 < affectedNodes.size(); i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiDynamicEffect::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiAVObject::Write( out, link_map, missing_link_stack, info );
	numAffectedNodes = (unsigned int)(affectedNodes.size());
	numAffectedNodeListPointers = (unsigned int)(affectedNodeListPointers.size());
	if ( info.version >= 0x0A01006A ) {
		NifStream( switchState, out, info );
	};
	if ( info.version <= 0x04000002 ) {
		NifStream( numAffectedNodeListPointers, out, info );
	};
	if ( info.version >= 0x0A010000 ) {
		NifStream( numAffectedNodes, out, info );
	};
	if ( info.version <= 0x04000002 ) {
		for (unsigned int i2 = 0; i2 < affectedNodeListPointers.size(); i2++) {
			NifStream( affectedNodeListPointers[i2], out, info );
		};
	};
	if ( info.version >= 0x0A010000 ) {
		for (unsigned int i2 = 0; i2 < affectedNodes.size(); i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*affectedNodes[i2]), out );
			} else {
				if ( affectedNodes[i2] != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(affectedNodes[i2]) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( affectedNodes[i2] );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiDynamicEffect::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiAVObject::asString();
	numAffectedNodes = (unsigned int)(affectedNodes.size());
	numAffectedNodeListPointers = (unsigned int)(affectedNodeListPointers.size());
	out << "  Switch State:  " << switchState << endl;
	out << "  Num Affected Node List Pointers:  " << numAffectedNodeListPointers << endl;
	out << "  Num Affected Nodes:  " << numAffectedNodes << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < affectedNodeListPointers.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Affected Node List Pointers[" << i1 << "]:  " << affectedNodeListPointers[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < affectedNodes.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Affected Nodes[" << i1 << "]:  " << affectedNodes[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiDynamicEffect::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiAVObject::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( info.version >= 0x0A010000 ) {
		for (unsigned int i2 = 0; i2 < affectedNodes.size(); i2++) {
			affectedNodes[i2] = FixLink<NiAVObject>( objects, link_stack, missing_link_stack, info );
		};
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiDynamicEffect::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiAVObject::GetRefs();
	for (unsigned int i1 = 0; i1 < affectedNodes.size(); i1++) {
		if ( affectedNodes[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(affectedNodes[i1]));
	};
	return refs;
}

std::list<NiObject *> NiDynamicEffect::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiAVObject::GetPtrs();
	for (unsigned int i1 = 0; i1 < affectedNodes.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

bool NiDynamicEffect::GetSwitchState() const {
	return switchState;
}

void NiDynamicEffect::SetSwitchState( bool value ) {
	switchState = value;
}

vector<Ref<NiAVObject > > NiDynamicEffect::GetAffectedNodes() const {
	return affectedNodes;
}

void NiDynamicEffect::SetAffectedNodes( const vector<Ref<NiAVObject > >& value ) {
	affectedNodes = value;
}

//--END CUSTOM CODE--//
