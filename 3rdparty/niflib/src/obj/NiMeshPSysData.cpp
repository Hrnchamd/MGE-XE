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
#include "../../include/obj/NiMeshPSysData.h"
#include "../../include/obj/NiNode.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiMeshPSysData::TYPE("NiMeshPSysData", &NiPSysData::TYPE );

NiMeshPSysData::NiMeshPSysData() : unknownInt2((unsigned int)0), unknownByte3((byte)0), numUnknownInts1((unsigned int)0), unknownNode(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiMeshPSysData::~NiMeshPSysData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiMeshPSysData::GetType() const {
	return TYPE;
}

NiObject * NiMeshPSysData::Create() {
	return new NiMeshPSysData;
}

void NiMeshPSysData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiPSysData::Read( in, link_stack, info );
	if ( info.version >= 0x0A020000 ) {
		NifStream( unknownInt2, in, info );
		NifStream( unknownByte3, in, info );
		NifStream( numUnknownInts1, in, info );
		unknownInts1.resize(numUnknownInts1);
		for (unsigned int i2 = 0; i2 < unknownInts1.size(); i2++) {
			NifStream( unknownInts1[i2], in, info );
		};
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiMeshPSysData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysData::Write( out, link_map, missing_link_stack, info );
	numUnknownInts1 = (unsigned int)(unknownInts1.size());
	if ( info.version >= 0x0A020000 ) {
		NifStream( unknownInt2, out, info );
		NifStream( unknownByte3, out, info );
		NifStream( numUnknownInts1, out, info );
		for (unsigned int i2 = 0; i2 < unknownInts1.size(); i2++) {
			NifStream( unknownInts1[i2], out, info );
		};
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*unknownNode), out );
	} else {
		if ( unknownNode != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(unknownNode) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( unknownNode );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiMeshPSysData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiPSysData::asString();
	numUnknownInts1 = (unsigned int)(unknownInts1.size());
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Unknown Byte 3:  " << unknownByte3 << endl;
	out << "  Num Unknown Ints 1:  " << numUnknownInts1 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknownInts1.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Ints 1[" << i1 << "]:  " << unknownInts1[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Node:  " << unknownNode << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiMeshPSysData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysData::FixLinks( objects, link_stack, missing_link_stack, info );
	unknownNode = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiMeshPSysData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysData::GetRefs();
	if ( unknownNode != NULL )
		refs.push_back(StaticCast<NiObject>(unknownNode));
	return refs;
}

std::list<NiObject *> NiMeshPSysData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
