/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _MTRANSFORM_H_
#define _MTRANSFORM_H_

#include "../NIF_IO.h"

namespace Niflib {


/*!  */
struct MTransform {
	/*! Default Constructor */
	NIFLIB_API MTransform();
	/*! Default Destructor */
	NIFLIB_API ~MTransform();
	/*! Copy Constructor */
	NIFLIB_API MTransform( const MTransform & src );
	/*! Copy Operator */
	NIFLIB_API MTransform & operator=( const MTransform & src );
	/*! Translation. */
	Vector3 translation;
	/*! Rotation. */
	Matrix33 rotation;
	/*! Scale. */
	float scale;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
