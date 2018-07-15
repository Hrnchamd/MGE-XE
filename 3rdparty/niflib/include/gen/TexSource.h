/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _TEXSOURCE_H_
#define _TEXSOURCE_H_

#include "../NIF_IO.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiObject;
class NiPixelData;

/*! A texture source. */
struct TexSource {
	/*! Default Constructor */
	NIFLIB_API TexSource();
	/*! Default Destructor */
	NIFLIB_API ~TexSource();
	/*! Copy Constructor */
	NIFLIB_API TexSource( const TexSource & src );
	/*! Copy Operator */
	NIFLIB_API TexSource & operator=( const TexSource & src );
	/*! Is the texture external? */
	byte useExternal;
	/*!
	 * The external texture file name.
	 * 
	 *             Note: all original morrowind nifs use name.ext only for addressing
	 * the textures, but most mods use something like textures/[subdir/]name.ext. This
	 * is due to a feature in Morrowind resource manager: it loads name.ext,
	 * textures/name.ext and textures/subdir/name.ext but NOT subdir/name.ext.
	 */
	IndexString fileName;
	/*! Unknown. */
	Ref<NiObject > unknownLink;
	/*! Unknown. */
	byte unknownByte;
	/*! Pixel data object index. */
	Ref<NiPixelData > pixelData;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
