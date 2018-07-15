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
#include "../../include/obj/NiImage.h"
#include "../../include/obj/NiRawImageData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiImage::TYPE("NiImage", &NiObject::TYPE );

NiImage::NiImage() : useExternal((byte)0), imageData(NULL), unknownInt((unsigned int)7), unknownFloat(128.5f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiImage::~NiImage() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiImage::GetType() const {
	return TYPE;
}

NiObject * NiImage::Create() {
	return new NiImage;
}

void NiImage::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( useExternal, in, info );
	if ( (useExternal != 0) ) {
		NifStream( fileName, in, info );
	};
	if ( (useExternal == 0) ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( unknownInt, in, info );
	if ( info.version >= 0x03010000 ) {
		NifStream( unknownFloat, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiImage::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	NifStream( useExternal, out, info );
	if ( (useExternal != 0) ) {
		NifStream( fileName, out, info );
	};
	if ( (useExternal == 0) ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*imageData), out );
		} else {
			if ( imageData != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(imageData) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( imageData );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( unknownInt, out, info );
	if ( info.version >= 0x03010000 ) {
		NifStream( unknownFloat, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiImage::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiObject::asString();
	out << "  Use External:  " << useExternal << endl;
	if ( (useExternal != 0) ) {
		out << "    File Name:  " << fileName << endl;
	};
	if ( (useExternal == 0) ) {
		out << "    Image Data:  " << imageData << endl;
	};
	out << "  Unknown Int:  " << unknownInt << endl;
	out << "  Unknown Float:  " << unknownFloat << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiImage::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( (useExternal == 0) ) {
		imageData = FixLink<NiRawImageData>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiImage::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( imageData != NULL )
		refs.push_back(StaticCast<NiObject>(imageData));
	return refs;
}

std::list<NiObject *> NiImage::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

bool NiImage::IsTextureExternal() const {
	return (useExternal != 0);
}

void NiImage::SetExternalTexture( string file_name ) {
	imageData = NULL;
	useExternal = 1;
	fileName = file_name;
}

void NiImage::SetInternalTexture( NiRawImageData * raw_image_data ) {
	useExternal = 0;
	fileName.clear();
	imageData = raw_image_data;
}

string NiImage::GetTextureFileName() const {
	return fileName;
}

Ref<NiRawImageData> NiImage::GetRawImageData() const {
	return imageData;
}

//--END CUSTOM CODE--//
