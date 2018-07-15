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
#include "../../include/obj/NiPSysVolumeEmitter.h"
#include "../../include/obj/NiNode.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysVolumeEmitter::TYPE("NiPSysVolumeEmitter", &NiPSysEmitter::TYPE );

NiPSysVolumeEmitter::NiPSysVolumeEmitter() : emitterObject(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysVolumeEmitter::~NiPSysVolumeEmitter() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysVolumeEmitter::GetType() const {
	return TYPE;
}

NiObject * NiPSysVolumeEmitter::Create() {
	return new NiPSysVolumeEmitter;
}

void NiPSysVolumeEmitter::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiPSysEmitter::Read( in, link_stack, info );
	if ( info.version >= 0x0A010000 ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysVolumeEmitter::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysEmitter::Write( out, link_map, missing_link_stack, info );
	if ( info.version >= 0x0A010000 ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*emitterObject), out );
		} else {
			if ( emitterObject != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(emitterObject) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( emitterObject );
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

std::string NiPSysVolumeEmitter::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysEmitter::asString();
	out << "  Emitter Object:  " << emitterObject << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysVolumeEmitter::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysEmitter::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( info.version >= 0x0A010000 ) {
		emitterObject = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysVolumeEmitter::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysEmitter::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysVolumeEmitter::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysEmitter::GetPtrs();
	if ( emitterObject != NULL )
		ptrs.push_back((NiObject *)(emitterObject));
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
