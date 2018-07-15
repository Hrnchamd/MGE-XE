/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include "../../include/obj/NiKeyBasedInterpolator.h"
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiSingleInterpController.h"
#include "../../include/obj/NiInterpolator.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiSingleInterpController::TYPE("NiSingleInterpController", &NiInterpController::TYPE );

NiSingleInterpController::NiSingleInterpController() : interpolator(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiSingleInterpController::~NiSingleInterpController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiSingleInterpController::GetType() const {
	return TYPE;
}

NiObject * NiSingleInterpController::Create() {
	return new NiSingleInterpController;
}

void NiSingleInterpController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiInterpController::Read( in, link_stack, info );
	if ( info.version >= 0x0A020000 ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiSingleInterpController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiInterpController::Write( out, link_map, missing_link_stack, info );
	if ( info.version >= 0x0A020000 ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*interpolator), out );
		} else {
			if ( interpolator != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolator) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( interpolator );
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

std::string NiSingleInterpController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiInterpController::asString();
	out << "  Interpolator:  " << interpolator << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiSingleInterpController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiInterpController::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( info.version >= 0x0A020000 ) {
		interpolator = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiSingleInterpController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiInterpController::GetRefs();
	if ( interpolator != NULL )
		refs.push_back(StaticCast<NiObject>(interpolator));
	return refs;
}

std::list<NiObject *> NiSingleInterpController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiInterpController::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Ref<NiInterpolator > NiSingleInterpController::GetInterpolator() const {
	return interpolator;
}

void NiSingleInterpController::SetInterpolator( NiInterpolator * value ) {
	interpolator = value;
}

void NiSingleInterpController::NormalizeKeys() {
	//If this interpolator is key-based, normalize its keys
	NiKeyBasedInterpolatorRef keyBased = DynamicCast<NiKeyBasedInterpolator>(this->interpolator);
	if ( keyBased != NULL ) {
		keyBased->NormalizeKeys( this->phase, this->frequency );
	}

	//Call the NiTimeController version of this function to normalize the start
	//and stop times and reset the phase and frequency
	NiTimeController::NormalizeKeys();
}

//--END CUSTOM CODE--//
