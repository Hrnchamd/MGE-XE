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
#include "../../include/obj/NiBoolInterpolator.h"
#include "../../include/obj/NiBoolData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiBoolInterpolator::TYPE("NiBoolInterpolator", &NiKeyBasedInterpolator::TYPE );

NiBoolInterpolator::NiBoolInterpolator() : boolValue(false), data(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiBoolInterpolator::~NiBoolInterpolator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiBoolInterpolator::GetType() const {
	return TYPE;
}

NiObject * NiBoolInterpolator::Create() {
	return new NiBoolInterpolator;
}

void NiBoolInterpolator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiKeyBasedInterpolator::Read( in, link_stack, info );
	NifStream( boolValue, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBoolInterpolator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiKeyBasedInterpolator::Write( out, link_map, missing_link_stack, info );
	NifStream( boolValue, out, info );
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

std::string NiBoolInterpolator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiKeyBasedInterpolator::asString();
	out << "  Bool Value:  " << boolValue << endl;
	out << "  Data:  " << data << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBoolInterpolator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiKeyBasedInterpolator::FixLinks( objects, link_stack, missing_link_stack, info );
	data = FixLink<NiBoolData>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBoolInterpolator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiKeyBasedInterpolator::GetRefs();
	if ( data != NULL )
		refs.push_back(StaticCast<NiObject>(data));
	return refs;
}

std::list<NiObject *> NiBoolInterpolator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiKeyBasedInterpolator::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

bool NiBoolInterpolator::GetBoolValue() const {
	return boolValue;
}

void NiBoolInterpolator::SetBoolValue( bool value ) {
	boolValue = value;
}

Ref<NiBoolData > NiBoolInterpolator::GetData() const {
	return data;
}

void NiBoolInterpolator::SetData( NiBoolData * value ) {
	data = value;
}

void NiBoolInterpolator::NormalizeKeys( float phase, float frequency ) {
	if ( data != NULL ) {
		data->NormalizeKeys( phase, frequency );
	}
}


//--END CUSTOM CODE--//
