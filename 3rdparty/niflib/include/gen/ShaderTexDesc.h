/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _SHADERTEXDESC_H_
#define _SHADERTEXDESC_H_

#include "../NIF_IO.h"

// Include structures
#include "TexDesc.h"
namespace Niflib {


/*! An extended texture description for shader textures. */
struct ShaderTexDesc {
	/*! Default Constructor */
	NIFLIB_API ShaderTexDesc();
	/*! Default Destructor */
	NIFLIB_API ~ShaderTexDesc();
	/*! Copy Constructor */
	NIFLIB_API ShaderTexDesc( const ShaderTexDesc & src );
	/*! Copy Operator */
	NIFLIB_API ShaderTexDesc & operator=( const ShaderTexDesc & src );
	/*! Is it used? */
	bool isUsed;
	/*! The texture data. */
	TexDesc textureData;
	/*! Map Index */
	unsigned int mapIndex;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
