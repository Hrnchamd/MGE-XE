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
#include "../../include/obj/bhkNiCollisionObject.h"
#include "../../include/obj/NiObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkNiCollisionObject::TYPE("bhkNiCollisionObject", &NiCollisionObject::TYPE );

bhkNiCollisionObject::bhkNiCollisionObject() : flags((unsigned short)1), body(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkNiCollisionObject::~bhkNiCollisionObject() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkNiCollisionObject::GetType() const {
	return TYPE;
}

NiObject * bhkNiCollisionObject::Create() {
	return new bhkNiCollisionObject;
}

void bhkNiCollisionObject::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiCollisionObject::Read( in, link_stack, info );
	NifStream( flags, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkNiCollisionObject::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiCollisionObject::Write( out, link_map, missing_link_stack, info );
	NifStream( flags, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*body), out );
	} else {
		if ( body != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(body) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( body );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkNiCollisionObject::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiCollisionObject::asString();
	out << "  Flags:  " << flags << endl;
	out << "  Body:  " << body << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkNiCollisionObject::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiCollisionObject::FixLinks( objects, link_stack, missing_link_stack, info );
	body = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkNiCollisionObject::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiCollisionObject::GetRefs();
	if ( body != NULL )
		refs.push_back(StaticCast<NiObject>(body));
	return refs;
}

std::list<NiObject *> bhkNiCollisionObject::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiCollisionObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Ref<NiObject > bhkNiCollisionObject::GetBody() const {
   return body;
}

void bhkNiCollisionObject::SetBody( NiObject * value ) {
   body = value;
}

unsigned short bhkNiCollisionObject::GetFlags() const {
  return flags;
}

void bhkNiCollisionObject::SetFlags(unsigned short value) {
  flags = value;
}
//--END CUSTOM CODE--//
