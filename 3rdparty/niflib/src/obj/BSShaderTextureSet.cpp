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
#include "../../include/obj/BSShaderTextureSet.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSShaderTextureSet::TYPE("BSShaderTextureSet", &NiObject::TYPE );

BSShaderTextureSet::BSShaderTextureSet() : numTextures((int)6) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSShaderTextureSet::~BSShaderTextureSet() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSShaderTextureSet::GetType() const {
	return TYPE;
}

NiObject * BSShaderTextureSet::Create() {
	return new BSShaderTextureSet;
}

void BSShaderTextureSet::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( numTextures, in, info );
	textures.resize(numTextures);
	for (unsigned int i1 = 0; i1 < textures.size(); i1++) {
		NifStream( textures[i1], in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSShaderTextureSet::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	numTextures = (int)(textures.size());
	NifStream( numTextures, out, info );
	for (unsigned int i1 = 0; i1 < textures.size(); i1++) {
		NifStream( textures[i1], out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSShaderTextureSet::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numTextures = (int)(textures.size());
	out << "  Num Textures:  " << numTextures << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < textures.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Textures[" << i1 << "]:  " << textures[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSShaderTextureSet::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSShaderTextureSet::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> BSShaderTextureSet::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

vector<string > BSShaderTextureSet::GetTextures() const {
	return textures;
}

void BSShaderTextureSet::SetTextures( const vector<string >& value ) {
	textures = value;
}

string BSShaderTextureSet::GetTexture(size_t i) const {
	if (i >= textures.size())
		throw runtime_error("Invalid Texture Index specified");
	return textures[i];
}

void BSShaderTextureSet::SetTexture( size_t i, const string& value) {
	if (i >= textures.size())
		textures.resize(i+1);
	textures[i] = value;
}

//--END CUSTOM CODE--//
