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
#include "../../include/obj/NiPersistentSrcTextureRendererData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPersistentSrcTextureRendererData::TYPE("NiPersistentSrcTextureRendererData", &ATextureRenderData::TYPE );

NiPersistentSrcTextureRendererData::NiPersistentSrcTextureRendererData() : numPixels((unsigned int)0), unknownInt6((unsigned int)0), numFaces((unsigned int)0), unknownInt7((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPersistentSrcTextureRendererData::~NiPersistentSrcTextureRendererData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPersistentSrcTextureRendererData::GetType() const {
	return TYPE;
}

NiObject * NiPersistentSrcTextureRendererData::Create() {
	return new NiPersistentSrcTextureRendererData;
}

void NiPersistentSrcTextureRendererData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	ATextureRenderData::Read( in, link_stack, info );
	NifStream( numPixels, in, info );
	NifStream( unknownInt6, in, info );
	NifStream( numFaces, in, info );
	NifStream( unknownInt7, in, info );
	pixelData.resize(numFaces);
	for (unsigned int i1 = 0; i1 < pixelData.size(); i1++) {
		pixelData[i1].resize(numPixels);
		for (unsigned int i2 = 0; i2 < pixelData[i1].size(); i2++) {
			NifStream( pixelData[i1][i2], in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPersistentSrcTextureRendererData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	ATextureRenderData::Write( out, link_map, missing_link_stack, info );
	numFaces = (unsigned int)(pixelData.size());
	numPixels = (unsigned int)((pixelData.size() > 0) ? pixelData[0].size() : 0);
	NifStream( numPixels, out, info );
	NifStream( unknownInt6, out, info );
	NifStream( numFaces, out, info );
	NifStream( unknownInt7, out, info );
	for (unsigned int i1 = 0; i1 < pixelData.size(); i1++) {
		for (unsigned int i2 = 0; i2 < pixelData[i1].size(); i2++) {
			NifStream( pixelData[i1][i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPersistentSrcTextureRendererData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << ATextureRenderData::asString();
	numFaces = (unsigned int)(pixelData.size());
	numPixels = (unsigned int)((pixelData.size() > 0) ? pixelData[0].size() : 0);
	out << "  Num Pixels:  " << numPixels << endl;
	out << "  Unknown Int 6:  " << unknownInt6 << endl;
	out << "  Num Faces:  " << numFaces << endl;
	out << "  Unknown Int 7:  " << unknownInt7 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < pixelData.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		for (unsigned int i2 = 0; i2 < pixelData[i1].size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Pixel Data[" << i2 << "]:  " << pixelData[i1][i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPersistentSrcTextureRendererData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	ATextureRenderData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPersistentSrcTextureRendererData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = ATextureRenderData::GetRefs();
	return refs;
}

std::list<NiObject *> NiPersistentSrcTextureRendererData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = ATextureRenderData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
