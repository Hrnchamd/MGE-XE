/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include "../../include/obj/NiFloatInterpolator.h"
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiAlphaController.h"
#include "../../include/obj/NiFloatData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiAlphaController::TYPE("NiAlphaController", &NiFloatInterpController::TYPE );

NiAlphaController::NiAlphaController() : data(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiAlphaController::~NiAlphaController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiAlphaController::GetType() const {
	return TYPE;
}

NiObject * NiAlphaController::Create() {
	return new NiAlphaController;
}

void NiAlphaController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiFloatInterpController::Read( in, link_stack, info );
	if ( info.version <= 0x0A010000 ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiAlphaController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiFloatInterpController::Write( out, link_map, missing_link_stack, info );
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

std::string NiAlphaController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiFloatInterpController::asString();
	out << "  Data:  " << data << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiAlphaController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiFloatInterpController::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( info.version <= 0x0A010000 ) {
		data = FixLink<NiFloatData>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiAlphaController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiFloatInterpController::GetRefs();
	if ( data != NULL )
		refs.push_back(StaticCast<NiObject>(data));
	return refs;
}

std::list<NiObject *> NiAlphaController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiFloatInterpController::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Ref<NiFloatData> NiAlphaController::GetData() const {
	return data;
}

void NiAlphaController::SetData( NiFloatData * n ) {
	data = n;
}

void NiAlphaController::NormalizeKeys() {
	// If data is not the same as The interpolator data, which will be
	// normalized by the call to NiSingleInterpController's version of
	// this function, then normalize it here.
	NiFloatInterpolatorRef interp = DynamicCast<NiFloatInterpolator>(interpolator);
	if ( (interp->GetData() != data) && ( data != NULL ) ) {
		data->NormalizeKeys( this->phase, this->frequency );
	}

	//Call the parent version of this function to finish up
	NiSingleInterpController::NormalizeKeys();
}

//--END CUSTOM CODE--//
