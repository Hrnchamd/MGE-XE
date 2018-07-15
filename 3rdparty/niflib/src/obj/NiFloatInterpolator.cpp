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
#include "../../include/obj/NiFloatInterpolator.h"
#include "../../include/obj/NiFloatData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiFloatInterpolator::TYPE("NiFloatInterpolator", &NiKeyBasedInterpolator::TYPE );

NiFloatInterpolator::NiFloatInterpolator() : floatValue(0.0f), data(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiFloatInterpolator::~NiFloatInterpolator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiFloatInterpolator::GetType() const {
	return TYPE;
}

NiObject * NiFloatInterpolator::Create() {
	return new NiFloatInterpolator;
}

void NiFloatInterpolator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiKeyBasedInterpolator::Read( in, link_stack, info );
	NifStream( floatValue, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiFloatInterpolator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiKeyBasedInterpolator::Write( out, link_map, missing_link_stack, info );
	NifStream( floatValue, out, info );
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

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiFloatInterpolator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiKeyBasedInterpolator::asString();
	out << "  Float Value:  " << floatValue << endl;
	out << "  Data:  " << data << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiFloatInterpolator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiKeyBasedInterpolator::FixLinks( objects, link_stack, missing_link_stack, info );
	data = FixLink<NiFloatData>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiFloatInterpolator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiKeyBasedInterpolator::GetRefs();
	if ( data != NULL )
		refs.push_back(StaticCast<NiObject>(data));
	return refs;
}

std::list<NiObject *> NiFloatInterpolator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiKeyBasedInterpolator::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

float NiFloatInterpolator::GetFloatValue() const {
	return floatValue;
}

void NiFloatInterpolator::SetFloatValue( float value ) {
	floatValue = value;
}

Ref<NiFloatData > NiFloatInterpolator::GetData() const {
	return data;
}

void NiFloatInterpolator::SetData( NiFloatData * value ) {
	data = value;
}

void NiFloatInterpolator::NormalizeKeys( float phase, float frequency ) {
	if ( data != NULL ) {
		data->NormalizeKeys( phase, frequency );
	}
}

//--END CUSTOM CODE--//
