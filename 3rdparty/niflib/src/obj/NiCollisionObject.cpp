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
#include "../../include/obj/NiCollisionObject.h"
#include "../../include/obj/NiAVObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiCollisionObject::TYPE("NiCollisionObject", &NiObject::TYPE );

NiCollisionObject::NiCollisionObject() : target(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiCollisionObject::~NiCollisionObject() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiCollisionObject::GetType() const {
	return TYPE;
}

NiObject * NiCollisionObject::Create() {
	return new NiCollisionObject;
}

void NiCollisionObject::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiCollisionObject::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
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

std::string NiCollisionObject::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiObject::asString();
	out << "  Target:  " << target << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiCollisionObject::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	target = FixLink<NiAVObject>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiCollisionObject::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiCollisionObject::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	if ( target != NULL )
		ptrs.push_back((NiObject *)(target));
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Ref<NiAVObject> NiCollisionObject::GetTarget() const {
	return target;
}

void NiCollisionObject::SetTarget( NiAVObject * value ) {
	target = value;
}

//--END CUSTOM CODE--//
