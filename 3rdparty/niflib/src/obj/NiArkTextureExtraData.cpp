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
#include "../../include/obj/NiArkTextureExtraData.h"
#include "../../include/gen/ArkTexture.h"
#include "../../include/obj/NiTexturingProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiArkTextureExtraData::TYPE("NiArkTextureExtraData", &NiExtraData::TYPE );

NiArkTextureExtraData::NiArkTextureExtraData() : unknownByte((byte)0), unknownInt2((int)0), numTextures((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiArkTextureExtraData::~NiArkTextureExtraData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiArkTextureExtraData::GetType() const {
	return TYPE;
}

NiObject * NiArkTextureExtraData::Create() {
	return new NiArkTextureExtraData;
}

void NiArkTextureExtraData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiExtraData::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		NifStream( unknownInts1[i1], in, info );
	};
	NifStream( unknownByte, in, info );
	if ( info.version <= 0x0401000C ) {
		NifStream( unknownInt2, in, info );
	};
	NifStream( numTextures, in, info );
	textures.resize(numTextures);
	for (unsigned int i1 = 0; i1 < textures.size(); i1++) {
		NifStream( textures[i1].textureName, in, info );
		NifStream( textures[i1].unknownInt3, in, info );
		NifStream( textures[i1].unknownInt4, in, info );
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		for (unsigned int i2 = 0; i2 < 9; i2++) {
			NifStream( textures[i1].unknownBytes[i2], in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiArkTextureExtraData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::Write( out, link_map, missing_link_stack, info );
	numTextures = (int)(textures.size());
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		NifStream( unknownInts1[i1], out, info );
	};
	NifStream( unknownByte, out, info );
	if ( info.version <= 0x0401000C ) {
		NifStream( unknownInt2, out, info );
	};
	NifStream( numTextures, out, info );
	for (unsigned int i1 = 0; i1 < textures.size(); i1++) {
		NifStream( textures[i1].textureName, out, info );
		NifStream( textures[i1].unknownInt3, out, info );
		NifStream( textures[i1].unknownInt4, out, info );
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*textures[i1].texturingProperty), out );
		} else {
			if ( textures[i1].texturingProperty != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(textures[i1].texturingProperty) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( textures[i1].texturingProperty );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		for (unsigned int i2 = 0; i2 < 9; i2++) {
			NifStream( textures[i1].unknownBytes[i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiArkTextureExtraData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiExtraData::asString();
	numTextures = (int)(textures.size());
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
	out << "  Unknown Byte:  " << unknownByte << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Num Textures:  " << numTextures << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < textures.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Texture Name:  " << textures[i1].textureName << endl;
		out << "    Unknown Int 3:  " << textures[i1].unknownInt3 << endl;
		out << "    Unknown Int 4:  " << textures[i1].unknownInt4 << endl;
		out << "    Texturing Property:  " << textures[i1].texturingProperty << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < 9; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown Bytes[" << i2 << "]:  " << textures[i1].unknownBytes[i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiArkTextureExtraData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < textures.size(); i1++) {
		textures[i1].texturingProperty = FixLink<NiTexturingProperty>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiArkTextureExtraData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiExtraData::GetRefs();
	for (unsigned int i1 = 0; i1 < textures.size(); i1++) {
		if ( textures[i1].texturingProperty != NULL )
			refs.push_back(StaticCast<NiObject>(textures[i1].texturingProperty));
	};
	return refs;
}

std::list<NiObject *> NiArkTextureExtraData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiExtraData::GetPtrs();
	for (unsigned int i1 = 0; i1 < textures.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
