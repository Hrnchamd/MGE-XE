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
#include "../../include/obj/NiPathInterpolator.h"
#include "../../include/obj/NiFloatData.h"
#include "../../include/obj/NiPosData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPathInterpolator::TYPE("NiPathInterpolator", &NiKeyBasedInterpolator::TYPE );

NiPathInterpolator::NiPathInterpolator() : unknownShort((unsigned short)0), unknownInt((unsigned int)0), unknownFloat1(0.0f), unknownFloat2(0.0f), unknownShort2((unsigned short)0), posData(NULL), floatData(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPathInterpolator::~NiPathInterpolator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPathInterpolator::GetType() const {
	return TYPE;
}

NiObject * NiPathInterpolator::Create() {
	return new NiPathInterpolator;
}

void NiPathInterpolator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiKeyBasedInterpolator::Read( in, link_stack, info );
	NifStream( unknownShort, in, info );
	NifStream( unknownInt, in, info );
	NifStream( unknownFloat1, in, info );
	NifStream( unknownFloat2, in, info );
	NifStream( unknownShort2, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPathInterpolator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiKeyBasedInterpolator::Write( out, link_map, missing_link_stack, info );
	NifStream( unknownShort, out, info );
	NifStream( unknownInt, out, info );
	NifStream( unknownFloat1, out, info );
	NifStream( unknownFloat2, out, info );
	NifStream( unknownShort2, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*posData), out );
	} else {
		if ( posData != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(posData) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( posData );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*floatData), out );
	} else {
		if ( floatData != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(floatData) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( floatData );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPathInterpolator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiKeyBasedInterpolator::asString();
	out << "  Unknown Short:  " << unknownShort << endl;
	out << "  Unknown Int:  " << unknownInt << endl;
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Unknown Short 2:  " << unknownShort2 << endl;
	out << "  Pos Data:  " << posData << endl;
	out << "  Float Data:  " << floatData << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPathInterpolator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiKeyBasedInterpolator::FixLinks( objects, link_stack, missing_link_stack, info );
	posData = FixLink<NiPosData>( objects, link_stack, missing_link_stack, info );
	floatData = FixLink<NiFloatData>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPathInterpolator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiKeyBasedInterpolator::GetRefs();
	if ( posData != NULL )
		refs.push_back(StaticCast<NiObject>(posData));
	if ( floatData != NULL )
		refs.push_back(StaticCast<NiObject>(floatData));
	return refs;
}

std::list<NiObject *> NiPathInterpolator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiKeyBasedInterpolator::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Ref<NiPosData > NiPathInterpolator::GetPosData() const {
	return posData;
}

void NiPathInterpolator::SetPosData( NiPosData * value ) {
	posData = value;
}

Ref<NiFloatData > NiPathInterpolator::GetFloatData() const {
	return floatData;
}

void NiPathInterpolator::SetFloatData( NiFloatData * value ) {
	floatData = value;
}

void NiPathInterpolator::NormalizeKeys( float phase, float frequency ) {
	if ( posData != NULL ) {
		posData->NormalizeKeys( phase, frequency );
	}
	if ( floatData != NULL ) {
		floatData->NormalizeKeys( phase, frequency );
	}
}


//--END CUSTOM CODE--//
