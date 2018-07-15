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
#include "../../include/obj/NiRawImageData.h"
#include "../../include/gen/ByteColor3.h"
#include "../../include/gen/ByteColor4.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiRawImageData::TYPE("NiRawImageData", &NiObject::TYPE );

NiRawImageData::NiRawImageData() : width((unsigned int)0), height((unsigned int)0), imageType((ImageType)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiRawImageData::~NiRawImageData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiRawImageData::GetType() const {
	return TYPE;
}

NiObject * NiRawImageData::Create() {
	return new NiRawImageData;
}

void NiRawImageData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( width, in, info );
	NifStream( height, in, info );
	NifStream( imageType, in, info );
	if ( (imageType == 1) ) {
		rgbImageData.resize(width);
		for (unsigned int i2 = 0; i2 < rgbImageData.size(); i2++) {
			rgbImageData[i2].resize(height);
			for (unsigned int i3 = 0; i3 < rgbImageData[i2].size(); i3++) {
				NifStream( rgbImageData[i2][i3].r, in, info );
				NifStream( rgbImageData[i2][i3].g, in, info );
				NifStream( rgbImageData[i2][i3].b, in, info );
			};
		};
	};
	if ( (imageType == 2) ) {
		rgbaImageData.resize(width);
		for (unsigned int i2 = 0; i2 < rgbaImageData.size(); i2++) {
			rgbaImageData[i2].resize(height);
			for (unsigned int i3 = 0; i3 < rgbaImageData[i2].size(); i3++) {
				NifStream( rgbaImageData[i2][i3].r, in, info );
				NifStream( rgbaImageData[i2][i3].g, in, info );
				NifStream( rgbaImageData[i2][i3].b, in, info );
				NifStream( rgbaImageData[i2][i3].a, in, info );
			};
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiRawImageData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	height = (unsigned int)((rgbImageData.size() > 0) ? rgbImageData[0].size() : 0);
	width = (unsigned int)(rgbImageData.size());
	NifStream( width, out, info );
	NifStream( height, out, info );
	NifStream( imageType, out, info );
	if ( (imageType == 1) ) {
		for (unsigned int i2 = 0; i2 < rgbImageData.size(); i2++) {
			for (unsigned int i3 = 0; i3 < rgbImageData[i2].size(); i3++) {
				NifStream( rgbImageData[i2][i3].r, out, info );
				NifStream( rgbImageData[i2][i3].g, out, info );
				NifStream( rgbImageData[i2][i3].b, out, info );
			};
		};
	};
	if ( (imageType == 2) ) {
		for (unsigned int i2 = 0; i2 < rgbaImageData.size(); i2++) {
			for (unsigned int i3 = 0; i3 < rgbaImageData[i2].size(); i3++) {
				NifStream( rgbaImageData[i2][i3].r, out, info );
				NifStream( rgbaImageData[i2][i3].g, out, info );
				NifStream( rgbaImageData[i2][i3].b, out, info );
				NifStream( rgbaImageData[i2][i3].a, out, info );
			};
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiRawImageData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	height = (unsigned int)((rgbImageData.size() > 0) ? rgbImageData[0].size() : 0);
	width = (unsigned int)(rgbImageData.size());
	out << "  Width:  " << width << endl;
	out << "  Height:  " << height << endl;
	out << "  Image Type:  " << imageType << endl;
	if ( (imageType == 1) ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < rgbImageData.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			for (unsigned int i3 = 0; i3 < rgbImageData[i2].size(); i3++) {
				out << "        r:  " << rgbImageData[i2][i3].r << endl;
				out << "        g:  " << rgbImageData[i2][i3].g << endl;
				out << "        b:  " << rgbImageData[i2][i3].b << endl;
			};
		};
	};
	if ( (imageType == 2) ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < rgbaImageData.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			for (unsigned int i3 = 0; i3 < rgbaImageData[i2].size(); i3++) {
				out << "        r:  " << rgbaImageData[i2][i3].r << endl;
				out << "        g:  " << rgbaImageData[i2][i3].g << endl;
				out << "        b:  " << rgbaImageData[i2][i3].b << endl;
				out << "        a:  " << rgbaImageData[i2][i3].a << endl;
			};
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiRawImageData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiRawImageData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiRawImageData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
