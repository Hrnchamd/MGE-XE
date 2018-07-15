/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _ARKTEXTURE_H_
#define _ARKTEXTURE_H_

#include "../NIF_IO.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiTexturingProperty;

/*! A texture reference used by NiArkTextureExtraData. */
struct ArkTexture {
	/*! Default Constructor */
	NIFLIB_API ArkTexture();
	/*! Default Destructor */
	NIFLIB_API ~ArkTexture();
	/*! Copy Constructor */
	NIFLIB_API ArkTexture( const ArkTexture & src );
	/*! Copy Operator */
	NIFLIB_API ArkTexture & operator=( const ArkTexture & src );
	/*! Unknown. */
	IndexString textureName;
	/*! Unknown. */
	int unknownInt3;
	/*! Unknown. */
	int unknownInt4;
	/*! Unknown. */
	Ref<NiTexturingProperty > texturingProperty;
	/*! Unknown. */
	array<9,byte > unknownBytes;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
