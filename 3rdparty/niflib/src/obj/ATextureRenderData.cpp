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
#include "../../include/obj/ATextureRenderData.h"
#include "../../include/gen/ChannelData.h"
#include "../../include/gen/MipMap.h"
#include "../../include/obj/NiPalette.h"
using namespace Niflib;

//Definition of TYPE constant
const Type ATextureRenderData::TYPE("ATextureRenderData", &NiObject::TYPE );

ATextureRenderData::ATextureRenderData() : pixelFormat((PixelFormat)0), redMask((unsigned int)0), greenMask((unsigned int)0), blueMask((unsigned int)0), alphaMask((unsigned int)0), bitsPerPixel((byte)0), unknownInt((unsigned int)0), unknownInt2((int)0), unknownInt3((unsigned int)0), flags((byte)0), unknownInt4((unsigned int)0), unknownByte1((byte)0), palette(NULL), numMipmaps((unsigned int)0), bytesPerPixel((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

ATextureRenderData::~ATextureRenderData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & ATextureRenderData::GetType() const {
	return TYPE;
}

NiObject * ATextureRenderData::Create() {
	return new ATextureRenderData;
}

void ATextureRenderData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( pixelFormat, in, info );
	if ( info.version <= 0x0A020000 ) {
		NifStream( redMask, in, info );
		NifStream( greenMask, in, info );
		NifStream( blueMask, in, info );
		NifStream( alphaMask, in, info );
		NifStream( bitsPerPixel, in, info );
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			NifStream( unknown3Bytes[i2], in, info );
		};
		for (unsigned int i2 = 0; i2 < 8; i2++) {
			NifStream( unknown8Bytes[i2], in, info );
		};
	};
	if ( ( info.version >= 0x0A010000 ) && ( info.version <= 0x0A020000 ) ) {
		NifStream( unknownInt, in, info );
	};
	if ( info.version >= 0x14000004 ) {
		NifStream( bitsPerPixel, in, info );
		NifStream( unknownInt2, in, info );
		NifStream( unknownInt3, in, info );
		NifStream( flags, in, info );
		NifStream( unknownInt4, in, info );
	};
	if ( info.version >= 0x14030006 ) {
		NifStream( unknownByte1, in, info );
	};
	if ( info.version >= 0x14000004 ) {
		for (unsigned int i2 = 0; i2 < 4; i2++) {
			NifStream( channels[i2].type, in, info );
			NifStream( channels[i2].convention, in, info );
			NifStream( channels[i2].bitsPerChannel, in, info );
			NifStream( channels[i2].unknownByte1, in, info );
		};
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( numMipmaps, in, info );
	NifStream( bytesPerPixel, in, info );
	mipmaps.resize(numMipmaps);
	for (unsigned int i1 = 0; i1 < mipmaps.size(); i1++) {
		NifStream( mipmaps[i1].width, in, info );
		NifStream( mipmaps[i1].height, in, info );
		NifStream( mipmaps[i1].offset, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void ATextureRenderData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	numMipmaps = (unsigned int)(mipmaps.size());
	NifStream( pixelFormat, out, info );
	if ( info.version <= 0x0A020000 ) {
		NifStream( redMask, out, info );
		NifStream( greenMask, out, info );
		NifStream( blueMask, out, info );
		NifStream( alphaMask, out, info );
		NifStream( bitsPerPixel, out, info );
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			NifStream( unknown3Bytes[i2], out, info );
		};
		for (unsigned int i2 = 0; i2 < 8; i2++) {
			NifStream( unknown8Bytes[i2], out, info );
		};
	};
	if ( ( info.version >= 0x0A010000 ) && ( info.version <= 0x0A020000 ) ) {
		NifStream( unknownInt, out, info );
	};
	if ( info.version >= 0x14000004 ) {
		NifStream( bitsPerPixel, out, info );
		NifStream( unknownInt2, out, info );
		NifStream( unknownInt3, out, info );
		NifStream( flags, out, info );
		NifStream( unknownInt4, out, info );
	};
	if ( info.version >= 0x14030006 ) {
		NifStream( unknownByte1, out, info );
	};
	if ( info.version >= 0x14000004 ) {
		for (unsigned int i2 = 0; i2 < 4; i2++) {
			NifStream( channels[i2].type, out, info );
			NifStream( channels[i2].convention, out, info );
			NifStream( channels[i2].bitsPerChannel, out, info );
			NifStream( channels[i2].unknownByte1, out, info );
		};
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*palette), out );
	} else {
		if ( palette != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(palette) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( palette );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	NifStream( numMipmaps, out, info );
	NifStream( bytesPerPixel, out, info );
	for (unsigned int i1 = 0; i1 < mipmaps.size(); i1++) {
		NifStream( mipmaps[i1].width, out, info );
		NifStream( mipmaps[i1].height, out, info );
		NifStream( mipmaps[i1].offset, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string ATextureRenderData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numMipmaps = (unsigned int)(mipmaps.size());
	out << "  Pixel Format:  " << pixelFormat << endl;
	out << "  Red Mask:  " << redMask << endl;
	out << "  Green Mask:  " << greenMask << endl;
	out << "  Blue Mask:  " << blueMask << endl;
	out << "  Alpha Mask:  " << alphaMask << endl;
	out << "  Bits Per Pixel:  " << bitsPerPixel << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 3; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 3 Bytes[" << i1 << "]:  " << unknown3Bytes[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 8 Bytes[" << i1 << "]:  " << unknown8Bytes[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Int:  " << unknownInt << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Unknown Int 3:  " << unknownInt3 << endl;
	out << "  Flags:  " << flags << endl;
	out << "  Unknown Int 4:  " << unknownInt4 << endl;
	out << "  Unknown Byte 1:  " << unknownByte1 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Type:  " << channels[i1].type << endl;
		out << "    Convention:  " << channels[i1].convention << endl;
		out << "    Bits Per Channel:  " << channels[i1].bitsPerChannel << endl;
		out << "    Unknown Byte 1:  " << channels[i1].unknownByte1 << endl;
	};
	out << "  Palette:  " << palette << endl;
	out << "  Num Mipmaps:  " << numMipmaps << endl;
	out << "  Bytes Per Pixel:  " << bytesPerPixel << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < mipmaps.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Width:  " << mipmaps[i1].width << endl;
		out << "    Height:  " << mipmaps[i1].height << endl;
		out << "    Offset:  " << mipmaps[i1].offset << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void ATextureRenderData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	palette = FixLink<NiPalette>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> ATextureRenderData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( palette != NULL )
		refs.push_back(StaticCast<NiObject>(palette));
	return refs;
}

std::list<NiObject *> ATextureRenderData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
