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
#include "../../include/obj/NiPortal.h"
#include "../../include/obj/NiNode.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPortal::TYPE("NiPortal", &NiAVObject::TYPE );

NiPortal::NiPortal() : unknownFlags((unsigned short)0), unknownShort2((short)0), numVertices((unsigned short)0), target(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPortal::~NiPortal() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPortal::GetType() const {
	return TYPE;
}

NiObject * NiPortal::Create() {
	return new NiPortal;
}

void NiPortal::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiAVObject::Read( in, link_stack, info );
	NifStream( unknownFlags, in, info );
	NifStream( unknownShort2, in, info );
	NifStream( numVertices, in, info );
	vertices.resize(numVertices);
	for (unsigned int i1 = 0; i1 < vertices.size(); i1++) {
		NifStream( vertices[i1], in, info );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPortal::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiAVObject::Write( out, link_map, missing_link_stack, info );
	numVertices = (unsigned short)(vertices.size());
	NifStream( unknownFlags, out, info );
	NifStream( unknownShort2, out, info );
	NifStream( numVertices, out, info );
	for (unsigned int i1 = 0; i1 < vertices.size(); i1++) {
		NifStream( vertices[i1], out, info );
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*target), out );
	} else {
		if ( target != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(target) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( target );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPortal::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiAVObject::asString();
	numVertices = (unsigned short)(vertices.size());
	out << "  Unknown Flags:  " << unknownFlags << endl;
	out << "  Unknown Short 2:  " << unknownShort2 << endl;
	out << "  Num Vertices:  " << numVertices << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < vertices.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Vertices[" << i1 << "]:  " << vertices[i1] << endl;
		array_output_count++;
	};
	out << "  Target:  " << target << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPortal::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiAVObject::FixLinks( objects, link_stack, missing_link_stack, info );
	target = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPortal::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiAVObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiPortal::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiAVObject::GetPtrs();
	if ( target != NULL )
		ptrs.push_back((NiObject *)(target));
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
