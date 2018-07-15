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
#include "../../include/obj/NiPSysEmitterCtlr.h"
#include "../../include/obj/NiInterpolator.h"
#include "../../include/obj/NiPSysEmitterCtlrData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysEmitterCtlr::TYPE("NiPSysEmitterCtlr", &NiPSysModifierCtlr::TYPE );

NiPSysEmitterCtlr::NiPSysEmitterCtlr() : data(NULL), visibilityInterpolator(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysEmitterCtlr::~NiPSysEmitterCtlr() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysEmitterCtlr::GetType() const {
	return TYPE;
}

NiObject * NiPSysEmitterCtlr::Create() {
	return new NiPSysEmitterCtlr;
}

void NiPSysEmitterCtlr::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiPSysModifierCtlr::Read( in, link_stack, info );
	if ( info.version <= 0x0A010000 ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	if ( info.version >= 0x0A020000 ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysEmitterCtlr::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifierCtlr::Write( out, link_map, missing_link_stack, info );
	if ( info.version <= 0x0A010000 ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*data), out );
		} else {
			if ( data != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(data) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( data );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( info.version >= 0x0A020000 ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*visibilityInterpolator), out );
		} else {
			if ( visibilityInterpolator != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(visibilityInterpolator) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( visibilityInterpolator );
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

std::string NiPSysEmitterCtlr::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifierCtlr::asString();
	out << "  Data:  " << data << endl;
	out << "  Visibility Interpolator:  " << visibilityInterpolator << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysEmitterCtlr::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifierCtlr::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( info.version <= 0x0A010000 ) {
		data = FixLink<NiPSysEmitterCtlrData>( objects, link_stack, missing_link_stack, info );
	};
	if ( info.version >= 0x0A020000 ) {
		visibilityInterpolator = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysEmitterCtlr::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifierCtlr::GetRefs();
	if ( data != NULL )
		refs.push_back(StaticCast<NiObject>(data));
	if ( visibilityInterpolator != NULL )
		refs.push_back(StaticCast<NiObject>(visibilityInterpolator));
	return refs;
}

std::list<NiObject *> NiPSysEmitterCtlr::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifierCtlr::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Ref<NiPSysEmitterCtlrData > NiPSysEmitterCtlr::GetData() const {
	return data;
}

void NiPSysEmitterCtlr::SetData( NiPSysEmitterCtlrData * value ) {
	data = value;
}

Ref<NiInterpolator > NiPSysEmitterCtlr::GetVisibilityInterpolator() const {
	return visibilityInterpolator;
}

void NiPSysEmitterCtlr::SetVisibilityInterpolator( NiInterpolator * value ) {
	visibilityInterpolator = value;
}

//--END CUSTOM CODE--//
