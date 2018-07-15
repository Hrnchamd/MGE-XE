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
#include "../../include/obj/NiPoint3InterpController.h"
#include "../../include/obj/NiPosData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPoint3InterpController::TYPE("NiPoint3InterpController", &NiSingleInterpController::TYPE );

NiPoint3InterpController::NiPoint3InterpController() : targetColor((TargetColor)0), data(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPoint3InterpController::~NiPoint3InterpController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPoint3InterpController::GetType() const {
	return TYPE;
}

NiObject * NiPoint3InterpController::Create() {
	return new NiPoint3InterpController;
}

void NiPoint3InterpController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiSingleInterpController::Read( in, link_stack, info );
	if ( info.version >= 0x0A010000 ) {
		NifStream( targetColor, in, info );
	};
	if ( info.version <= 0x0A010000 ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPoint3InterpController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiSingleInterpController::Write( out, link_map, missing_link_stack, info );
	if ( info.version >= 0x0A010000 ) {
		NifStream( targetColor, out, info );
	};
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

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPoint3InterpController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiSingleInterpController::asString();
	out << "  Target Color:  " << targetColor << endl;
	out << "  Data:  " << data << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPoint3InterpController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiSingleInterpController::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( info.version <= 0x0A010000 ) {
		data = FixLink<NiPosData>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPoint3InterpController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiSingleInterpController::GetRefs();
	if ( data != NULL )
		refs.push_back(StaticCast<NiObject>(data));
	return refs;
}

std::list<NiObject *> NiPoint3InterpController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiSingleInterpController::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Ref<NiPosData > NiPoint3InterpController::GetData() const {
	return data;
}

void NiPoint3InterpController::SetData( NiPosData * value ) {
	data = value;
}

//--END CUSTOM CODE--//
