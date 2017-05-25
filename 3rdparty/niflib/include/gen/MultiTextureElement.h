/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _MULTITEXTUREELEMENT_H_
#define _MULTITEXTUREELEMENT_H_

#include "../NIF_IO.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiImage;

/*!  */
struct MultiTextureElement {
	/*! Default Constructor */
	NIFLIB_API MultiTextureElement();
	/*! Default Destructor */
	NIFLIB_API ~MultiTextureElement();
	/*! Copy Constructor */
	NIFLIB_API MultiTextureElement( const MultiTextureElement & src );
	/*! Copy Operator */
	NIFLIB_API MultiTextureElement & operator=( const MultiTextureElement & src );
	/*! Looks like a memory address, so probably a bool. */
	bool hasImage;
	/*! Link to the texture image. */
	Ref<NiImage > image;
	/*! Unkown.  Usually 3 but sometimes 0. */
	unsigned int unknownInt1;
	/*! Unkown. Usually 2. */
	unsigned int unknownInt2;
	/*! Unkown. Usually 1. */
	unsigned int unknownInt3;
	/*! Unknown.  Usually 0. */
	short unknownShort1;
	/*! Unknown.  Usually -75. */
	short unknownShort2;
	/*! Unknown.  Usually 0 but sometimes 257 */
	short unknownShort3;
};

}
#endif
