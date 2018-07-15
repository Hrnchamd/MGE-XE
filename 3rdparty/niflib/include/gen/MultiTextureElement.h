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
	/*! May be texture clamp mode. */
	TexClampMode clamp_;
	/*! May be texture filter mode. */
	TexFilterMode filter_;
	/*! This may be the UV set counting from 1 instead of zero. */
	unsigned int uvSet_;
	/*! 0? */
	short ps2L;
	/*! -75? */
	short ps2K;
	/*! Unknown.  Usually 0 but sometimes 257 */
	short unknownShort3;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
