/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! A sphere. */
struct Sphere {
	/*! Default Constructor */
	NIFLIB_API Sphere();
	/*! Default Destructor */
	NIFLIB_API ~Sphere();
	/*! Copy Constructor */
	NIFLIB_API Sphere( const Sphere & src );
	/*! Copy Operator */
	NIFLIB_API Sphere & operator=( const Sphere & src );
	/*! The sphere's center. */
	Vector3 center;
	/*! The sphere's radius. */
	float radius;
};

}
#endif
