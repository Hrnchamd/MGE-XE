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
#include "../../include/obj/NiEnvMappedTriShape.h"
#include "../../include/obj/NiAVObject.h"
#include "../../include/obj/NiObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiEnvMappedTriShape::TYPE("NiEnvMappedTriShape", &NiObjectNET::TYPE );

NiEnvMappedTriShape::NiEnvMappedTriShape() : unknown1((unsigned short)0), numChildren((unsigned int)0), child2(NULL), child3(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiEnvMappedTriShape::~NiEnvMappedTriShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiEnvMappedTriShape::GetType() const {
	return TYPE;
}

NiObject * NiEnvMappedTriShape::Create() {
	return new NiEnvMappedTriShape;
}

void NiEnvMappedTriShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObjectNET::Read( in, link_stack, info );
	NifStream( unknown1, in, info );
	NifStream( unknownMatrix, in, info );
	NifStream( numChildren, in, info );
	children.resize(numChildren);
	for (unsigned int i1 = 0; i1 < children.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiEnvMappedTriShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObjectNET::Write( out, link_map, missing_link_stack, info );
	numChildren = (unsigned int)(children.size());
	NifStream( unknown1, out, info );
	NifStream( unknownMatrix, out, info );
	NifStream( numChildren, out, info );
	for (unsigned int i1 = 0; i1 < children.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*children[i1]), out );
		} else {
			if ( children[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(children[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( children[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*child2), out );
	} else {
		if ( child2 != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(child2) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( child2 );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*child3), out );
	} else {
		if ( child3 != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(child3) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( child3 );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiEnvMappedTriShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObjectNET::asString();
	numChildren = (unsigned int)(children.size());
	out << "  Unknown 1:  " << unknown1 << endl;
	out << "  Unknown Matrix:  " << unknownMatrix << endl;
	out << "  Num Children:  " << numChildren << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < children.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Children[" << i1 << "]:  " << children[i1] << endl;
		array_output_count++;
	};
	out << "  Child 2:  " << child2 << endl;
	out << "  Child 3:  " << child3 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiEnvMappedTriShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObjectNET::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < children.size(); i1++) {
		children[i1] = FixLink<NiAVObject>( objects, link_stack, missing_link_stack, info );
	};
	child2 = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	child3 = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiEnvMappedTriShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObjectNET::GetRefs();
	for (unsigned int i1 = 0; i1 < children.size(); i1++) {
		if ( children[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(children[i1]));
	};
	if ( child2 != NULL )
		refs.push_back(StaticCast<NiObject>(child2));
	if ( child3 != NULL )
		refs.push_back(StaticCast<NiObject>(child3));
	return refs;
}

std::list<NiObject *> NiEnvMappedTriShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObjectNET::GetPtrs();
	for (unsigned int i1 = 0; i1 < children.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
