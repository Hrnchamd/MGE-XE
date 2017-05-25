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
	/*!
	 * Determines how UV coordinaes that are outside the 0-1 range will be mapped to
	 * the texture.
	 */
	TexClampMode clampMode;
	/*! Determines how the texture will be scaled up and down. */
	TexFilterMode filterMode;
	/*! The texture coordinate set in NiGeometryData that this texture slot will use. */
	unsigned int uvSet;
	/*! 0? */
	unsigned short ps2L;
	/*! 0xFFB5? */
	unsigned short ps2K;
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
};

}
#endif
