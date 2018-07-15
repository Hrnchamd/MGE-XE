/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _QTRANSFORM_H_
#define _QTRANSFORM_H_

#include "../NIF_IO.h"

namespace Niflib {


/*!  */
struct QTransform {
	/*! Default Constructor */
	NIFLIB_API QTransform();
	/*! Default Destructor */
	NIFLIB_API ~QTransform();
	/*! Copy Constructor */
	NIFLIB_API QTransform( const QTransform & src );
	/*! Copy Operator */
	NIFLIB_API QTransform & operator=( const QTransform & src );
	/*! Translation. */
	Vector3 translation;
	/*! Rotation. */
	Quaternion rotation;
	/*! Scale. */
	float scale;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
