/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _TEXDESC_H_
#define _TEXDESC_H_

#include "../NIF_IO.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiSourceTexture;

/*! Texture description. */
struct TexDesc {
	/*! Default Constructor */
	NIFLIB_API TexDesc();
	/*! Default Destructor */
	NIFLIB_API ~TexDesc();
	/*! Copy Constructor */
	NIFLIB_API TexDesc( const TexDesc & src );
	/*! Copy Operator */
	NIFLIB_API TexDesc & operator=( const TexDesc & src );
	/*! NiSourceTexture object index. */
	Ref<NiSourceTexture > source;
	/*! 0=clamp S clamp T, 1=clamp S wrap T, 2=wrap S clamp T, 3=wrap S wrap T */
	TexClampMode clampMode;
	/*! 0=nearest, 1=bilinear, 2=trilinear, 3=..., 4=..., 5=... */
	TexFilterMode filterMode;
	/*!
	 * Texture mode flags; clamp and filter mode stored in upper byte with 0xYZ00 =
	 * clamp mode Y, filter mode Z.
	 */
	unsigned short flags;
	/*! Unknown, seems to always be 1 */
	short unknownShort;
	/*! The texture coordinate set in NiGeometryData that this texture slot will use. */
	unsigned int uvSet;
	/*!
	 * PS2 only; from the Freedom Force docs, "L values can range from 0 to 3 and are
	 * used to specify how fast a texture gets blurry".
	 */
	short ps2L;
	/*!
	 * PS2 only; from the Freedom Force docs, "The K value is used as an offset into
	 * the mipmap levels and can range from -2047 to 2047. Positive values push the
	 * mipmap towards being blurry and negative values make the mipmap sharper." -75
	 * for most v4.0.0.2 meshes.
	 */
	short ps2K;
	/*! Unknown, 0 or 0x0101? */
	unsigned short unknown1;
	/*! Determines whether or not the texture's coordinates are transformed. */
	bool hasTextureTransform;
	/*! The amount to translate the texture coordinates in each direction? */
	TexCoord translation;
	/*! The number of times the texture is tiled in each direction? */
	TexCoord tiling;
	/*! 2D Rotation of texture image around third W axis after U and V. */
	float wRotation;
	/*! The texture transform type?  Doesn't seem to do anything. */
	unsigned int transformType_;
	/*! The offset from the origin? */
	TexCoord centerOffset;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
