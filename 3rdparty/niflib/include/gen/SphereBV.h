/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _SPHEREBV_H_
#define _SPHEREBV_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! A sphere. */
struct SphereBV {
	/*! Default Constructor */
	NIFLIB_API SphereBV();
	/*! Default Destructor */
	NIFLIB_API ~SphereBV();
	/*! Copy Constructor */
	NIFLIB_API SphereBV( const SphereBV & src );
	/*! Copy Operator */
	NIFLIB_API SphereBV & operator=( const SphereBV & src );
	/*! The sphere's center. */
	Vector3 center;
	/*! The sphere's radius. */
	float radius;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
