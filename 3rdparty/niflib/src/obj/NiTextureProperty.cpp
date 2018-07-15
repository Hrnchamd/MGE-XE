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
#include "../../include/obj/NiTextureProperty.h"
#include "../../include/obj/NiImage.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiTextureProperty::TYPE("NiTextureProperty", &NiProperty::TYPE );

NiTextureProperty::NiTextureProperty() : flags((unsigned short)0), image(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiTextureProperty::~NiTextureProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiTextureProperty::GetType() const {
	return TYPE;
}

NiObject * NiTextureProperty::Create() {
	return new NiTextureProperty;
}

void NiTextureProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiProperty::Read( in, link_stack, info );
	if ( info.version <= 0x02030000 ) {
		for (unsigned int i2 = 0; i2 < 2; i2++) {
			NifStream( unknownInts1[i2], in, info );
		};
	};
	if ( info.version >= 0x03000000 ) {
		NifStream( flags, in, info );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	if ( ( info.version >= 0x03000000 ) && ( info.version <= 0x03000300 ) ) {
		for (unsigned int i2 = 0; i2 < 2; i2++) {
			NifStream( unknownInts2[i2], in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTextureProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Write( out, link_map, missing_link_stack, info );
	if ( info.version <= 0x02030000 ) {
		for (unsigned int i2 = 0; i2 < 2; i2++) {
			NifStream( unknownInts1[i2], out, info );
		};
	};
	if ( info.version >= 0x03000000 ) {
		NifStream( flags, out, info );
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*image), out );
	} else {
		if ( image != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(image) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( image );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( ( info.version >= 0x03000000 ) && ( info.version <= 0x03000300 ) ) {
		for (unsigned int i2 = 0; i2 < 2; i2++) {
			NifStream( unknownInts2[i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiTextureProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiProperty::asString();
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Ints 1[" << i1 << "]:  " << unknownInts1[i1] << endl;
		array_output_count++;
	};
	out << "  Flags:  " << flags << endl;
	out << "  Image:  " << image << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Ints 2[" << i1 << "]:  " << unknownInts2[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTextureProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::FixLinks( objects, link_stack, missing_link_stack, info );
	image = FixLink<NiImage>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiTextureProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiProperty::GetRefs();
	if ( image != NULL )
		refs.push_back(StaticCast<NiObject>(image));
	return refs;
}

std::list<NiObject *> NiTextureProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiProperty::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Ref<NiImage> NiTextureProperty::GetImage() const {
	return image;
}

void NiTextureProperty::SetImage( NiImage * n ) {
	image = n;
}

//--END CUSTOM CODE--//
