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
#include "../../include/obj/NiPSysCollider.h"
#include "../../include/obj/NiNode.h"
#include "../../include/obj/NiObject.h"
#include "../../include/obj/NiPSysSpawnModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysCollider::TYPE("NiPSysCollider", &NiObject::TYPE );

NiPSysCollider::NiPSysCollider() : bounce(0.0f), spawnOnCollide(false), dieOnCollide(false), spawnModifier(NULL), parent(NULL), nextCollider(NULL), colliderObject(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysCollider::~NiPSysCollider() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysCollider::GetType() const {
	return TYPE;
}

NiObject * NiPSysCollider::Create() {
	return new NiPSysCollider;
}

void NiPSysCollider::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( bounce, in, info );
	NifStream( spawnOnCollide, in, info );
	NifStream( dieOnCollide, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysCollider::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	NifStream( bounce, out, info );
	NifStream( spawnOnCollide, out, info );
	NifStream( dieOnCollide, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*spawnModifier), out );
	} else {
		if ( spawnModifier != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(spawnModifier) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( spawnModifier );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*parent), out );
	} else {
		if ( parent != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(parent) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( parent );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*nextCollider), out );
	} else {
		if ( nextCollider != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(nextCollider) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( nextCollider );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*colliderObject), out );
	} else {
		if ( colliderObject != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(colliderObject) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( colliderObject );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPSysCollider::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiObject::asString();
	out << "  Bounce:  " << bounce << endl;
	out << "  Spawn on Collide:  " << spawnOnCollide << endl;
	out << "  Die on Collide:  " << dieOnCollide << endl;
	out << "  Spawn Modifier:  " << spawnModifier << endl;
	out << "  Parent:  " << parent << endl;
	out << "  Next Collider:  " << nextCollider << endl;
	out << "  Collider Object:  " << colliderObject << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysCollider::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	spawnModifier = FixLink<NiPSysSpawnModifier>( objects, link_stack, missing_link_stack, info );
	parent = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	nextCollider = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	colliderObject = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysCollider::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( spawnModifier != NULL )
		refs.push_back(StaticCast<NiObject>(spawnModifier));
	if ( nextCollider != NULL )
		refs.push_back(StaticCast<NiObject>(nextCollider));
	return refs;
}

std::list<NiObject *> NiPSysCollider::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	if ( parent != NULL )
		ptrs.push_back((NiObject *)(parent));
	if ( colliderObject != NULL )
		ptrs.push_back((NiObject *)(colliderObject));
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
