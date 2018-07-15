/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _SKINSHAPE_H_
#define _SKINSHAPE_H_

#include "../NIF_IO.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiTriBasedGeom;
class NiSkinInstance;

/*! Reference to shape and skin instance. */
struct SkinShape {
	/*! Default Constructor */
	NIFLIB_API SkinShape();
	/*! Default Destructor */
	NIFLIB_API ~SkinShape();
	/*! Copy Constructor */
	NIFLIB_API SkinShape( const SkinShape & src );
	/*! Copy Operator */
	NIFLIB_API SkinShape & operator=( const SkinShape & src );
	/*! The shape. */
	NiTriBasedGeom * shape;
	/*! Skinning instance for the shape? */
	Ref<NiSkinInstance > skinInstance;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
