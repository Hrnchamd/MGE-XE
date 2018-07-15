/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Bounding box. */
struct BoundingBox {
	/*! Default Constructor */
	NIFLIB_API BoundingBox();
	/*! Default Destructor */
	NIFLIB_API ~BoundingBox();
	/*! Copy Constructor */
	NIFLIB_API BoundingBox( const BoundingBox & src );
	/*! Copy Operator */
	NIFLIB_API BoundingBox & operator=( const BoundingBox & src );
	/*! Usually 1. */
	unsigned int unknownInt;
	/*! Translation vector. */
	Vector3 translation;
	/*! Rotation matrix. */
	Matrix33 rotation;
	/*! Radius, per direction. */
	Vector3 radius;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
