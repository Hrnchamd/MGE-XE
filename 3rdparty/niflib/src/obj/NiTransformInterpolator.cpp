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
#include "../../include/obj/NiTransformInterpolator.h"
#include "../../include/obj/NiTransformData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiTransformInterpolator::TYPE("NiTransformInterpolator", &NiKeyBasedInterpolator::TYPE );

NiTransformInterpolator::NiTransformInterpolator() : scale(0.0f), data(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiTransformInterpolator::~NiTransformInterpolator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiTransformInterpolator::GetType() const {
	return TYPE;
}

NiObject * NiTransformInterpolator::Create() {
	return new NiTransformInterpolator;
}

void NiTransformInterpolator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiKeyBasedInterpolator::Read( in, link_stack, info );
	NifStream( translation, in, info );
	NifStream( rotation, in, info );
	NifStream( scale, in, info );
	if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			NifStream( unknownBytes[i2], in, info );
		};
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTransformInterpolator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiKeyBasedInterpolator::Write( out, link_map, missing_link_stack, info );
	NifStream( translation, out, info );
	NifStream( rotation, out, info );
	NifStream( scale, out, info );
	if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			NifStream( unknownBytes[i2], out, info );
		};
	};
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

std::string NiTransformInterpolator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiKeyBasedInterpolator::asString();
	out << "  Translation:  " << translation << endl;
	out << "  Rotation:  " << rotation << endl;
	out << "  Scale:  " << scale << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 3; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Bytes[" << i1 << "]:  " << unknownBytes[i1] << endl;
		array_output_count++;
	};
	out << "  Data:  " << data << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTransformInterpolator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiKeyBasedInterpolator::FixLinks( objects, link_stack, missing_link_stack, info );
	data = FixLink<NiTransformData>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiTransformInterpolator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiKeyBasedInterpolator::GetRefs();
	if ( data != NULL )
		refs.push_back(StaticCast<NiObject>(data));
	return refs;
}

std::list<NiObject *> NiTransformInterpolator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiKeyBasedInterpolator::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Vector3 NiTransformInterpolator::GetTranslation() const {
	return translation;
}

void NiTransformInterpolator::SetTranslation( Vector3 value ) {
	translation = value;
}

Quaternion NiTransformInterpolator::GetRotation() const {
	return rotation;
}

void NiTransformInterpolator::SetRotation( Quaternion value ) {
	rotation = value;
}

float NiTransformInterpolator::GetScale() const {
	return scale;
}

void NiTransformInterpolator::SetScale( float value ) {
	scale = value;
}

Ref<NiTransformData> NiTransformInterpolator::GetData() const {
	return data;
}

void NiTransformInterpolator::SetData( NiTransformData * value ) {
	data = value;
}

void NiTransformInterpolator::NormalizeKeys( float phase, float frequency ) {
	if ( data != NULL ) {
		data->NormalizeKeys( phase, frequency );
	}
}

//--END CUSTOM CODE--//
