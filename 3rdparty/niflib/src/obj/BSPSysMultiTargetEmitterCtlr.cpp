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
#include "../../include/obj/BSPSysMultiTargetEmitterCtlr.h"
#include "../../include/obj/NiInterpolator.h"
#include "../../include/obj/NiPSysEmitterCtlrData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSPSysMultiTargetEmitterCtlr::TYPE("BSPSysMultiTargetEmitterCtlr", &NiPSysModifierCtlr::TYPE );

BSPSysMultiTargetEmitterCtlr::BSPSysMultiTargetEmitterCtlr() : data(NULL), visibilityInterpolator(NULL), unknownShort1((short)0), unknownInt1((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSPSysMultiTargetEmitterCtlr::~BSPSysMultiTargetEmitterCtlr() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSPSysMultiTargetEmitterCtlr::GetType() const {
	return TYPE;
}

NiObject * BSPSysMultiTargetEmitterCtlr::Create() {
	return new BSPSysMultiTargetEmitterCtlr;
}

void BSPSysMultiTargetEmitterCtlr::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
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
	NifStream( unknownShort1, in, info );
	NifStream( unknownInt1, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSPSysMultiTargetEmitterCtlr::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
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
	NifStream( unknownShort1, out, info );
	NifStream( unknownInt1, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSPSysMultiTargetEmitterCtlr::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifierCtlr::asString();
	out << "  Data:  " << data << endl;
	out << "  Visibility Interpolator:  " << visibilityInterpolator << endl;
	out << "  Unknown Short 1:  " << unknownShort1 << endl;
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSPSysMultiTargetEmitterCtlr::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
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

std::list<NiObjectRef> BSPSysMultiTargetEmitterCtlr::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifierCtlr::GetRefs();
	if ( data != NULL )
		refs.push_back(StaticCast<NiObject>(data));
	if ( visibilityInterpolator != NULL )
		refs.push_back(StaticCast<NiObject>(visibilityInterpolator));
	return refs;
}

std::list<NiObject *> BSPSysMultiTargetEmitterCtlr::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifierCtlr::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
