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
#include "../../include/obj/NiPalette.h"
#include "../../include/gen/ByteColor4.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPalette::TYPE("NiPalette", &NiObject::TYPE );

NiPalette::NiPalette() : unknownByte((byte)0), numEntries((unsigned int)256) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPalette::~NiPalette() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPalette::GetType() const {
	return TYPE;
}

NiObject * NiPalette::Create() {
	return new NiPalette;
}

void NiPalette::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( unknownByte, in, info );
	NifStream( numEntries, in, info );
	for (unsigned int i1 = 0; i1 < 256; i1++) {
		NifStream( palette[i1].r, in, info );
		NifStream( palette[i1].g, in, info );
		NifStream( palette[i1].b, in, info );
		NifStream( palette[i1].a, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPalette::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	NifStream( unknownByte, out, info );
	NifStream( numEntries, out, info );
	for (unsigned int i1 = 0; i1 < 256; i1++) {
		NifStream( palette[i1].r, out, info );
		NifStream( palette[i1].g, out, info );
		NifStream( palette[i1].b, out, info );
		NifStream( palette[i1].a, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPalette::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	out << "  Unknown Byte:  " << unknownByte << endl;
	out << "  Num Entries:  " << numEntries << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 256; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    r:  " << palette[i1].r << endl;
		out << "    g:  " << palette[i1].g << endl;
		out << "    b:  " << palette[i1].b << endl;
		out << "    a:  " << palette[i1].a << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPalette::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPalette::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiPalette::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

vector<Color4> NiPalette::GetPalette() const {
	vector<Color4> color_pal(256);

	for ( unsigned int i = 0; i < 256; ++i ) {
		
		color_pal[i].r = float(palette[i].r) / 255.0f;
		color_pal[i].g = float(palette[i].g) / 255.0f;
		color_pal[i].b = float(palette[i].b) / 255.0f;
		color_pal[i].a = float(palette[i].a) / 255.0f;
	}

	return color_pal;
}

void NiPalette::SetPalette( const vector<Color4> & new_pal ) {
	if ( new_pal.size() != 256 ) {
		throw runtime_error( "Palette size must be 256" );
	}

	for ( unsigned int i = 0; i < 256; ++i ) {
		palette[i].r = int( new_pal[i].r * 255.0f );
		palette[i].g = int( new_pal[i].g * 255.0f );
		palette[i].b = int( new_pal[i].b * 255.0f );
		palette[i].a = int( new_pal[i].a * 255.0f );
	}
}

//--END CUSTOM CODE--//
