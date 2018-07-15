/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _MIPMAP_H_
#define _MIPMAP_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Description of a MipMap within a NiPixelData object. */
struct MipMap {
	/*! Default Constructor */
	NIFLIB_API MipMap();
	/*! Default Destructor */
	NIFLIB_API ~MipMap();
	/*! Copy Constructor */
	NIFLIB_API MipMap( const MipMap & src );
	/*! Copy Operator */
	NIFLIB_API MipMap & operator=( const MipMap & src );
	/*! Width of the mipmap image. */
	unsigned int width;
	/*! Height of the mipmap image. */
	unsigned int height;
	/*! Offset into the pixel data array where this mipmap starts. */
	unsigned int offset;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
