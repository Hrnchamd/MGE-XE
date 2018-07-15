/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _SKINTRANSFORM_H_
#define _SKINTRANSFORM_H_

#include "../NIF_IO.h"

namespace Niflib {


/*!  */
struct SkinTransform {
	/*! Default Constructor */
	NIFLIB_API SkinTransform();
	/*! Default Destructor */
	NIFLIB_API ~SkinTransform();
	/*! Copy Constructor */
	NIFLIB_API SkinTransform( const SkinTransform & src );
	/*! Copy Operator */
	NIFLIB_API SkinTransform & operator=( const SkinTransform & src );
	/*! The rotation part of the transformation matrix. */
	Matrix33 rotation;
	/*! The translation vector. */
	Vector3 translation;
	/*! Scaling part (only uniform scaling is supported). */
	float scale;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
