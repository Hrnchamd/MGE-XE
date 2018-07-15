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
#include "../../include/obj/NiStringPalette.h"
#include "../../include/gen/StringPalette.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiStringPalette::TYPE("NiStringPalette", &NiObject::TYPE );

NiStringPalette::NiStringPalette() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiStringPalette::~NiStringPalette() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiStringPalette::GetType() const {
	return TYPE;
}

NiObject * NiStringPalette::Create() {
	return new NiStringPalette;
}

void NiStringPalette::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( palette.palette, in, info );
	NifStream( palette.length, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiStringPalette::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	NifStream( palette.palette, out, info );
	NifStream( palette.length, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiStringPalette::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiObject::asString();
	out << "  Palette:  " << palette.palette << endl;
	out << "  Length:  " << palette.length << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiStringPalette::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiStringPalette::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiStringPalette::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

string NiStringPalette::GetPaletteString() const {
	return palette.palette;
}
	
void NiStringPalette::SetPaletteString( const string & n ) {
	palette.palette = n;
}

string NiStringPalette::GetSubStr( short offset ) const {
	string out;
	
	// -1 is a null offset
	if ( offset == -1 ) {
		return out;
	}

	for ( unsigned int i = offset; i < palette.palette.size(); ++i ) {
		if ( palette.palette[i] == '\0' ) {
			break;
		}
		out.push_back( palette.palette[i] );
	}

	return out;
}

unsigned int NiStringPalette::AddSubStr( const string & n ) {
	//Search for the string
   //  When searching for strings also search for ending null.
	unsigned int offset = (unsigned int)palette.palette.find( n.c_str(), 0, n.size()+1 );
	
	//If string was not found, append it
	if ( offset == 0xFFFFFFFF ) {
		offset = (unsigned int)palette.palette.size();
		palette.palette.append( n + '\0' );
	}

	//Return the offset where the string was found or appended
	return offset;
}

//--END CUSTOM CODE--//
