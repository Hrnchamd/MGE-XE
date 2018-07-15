/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _HKTRIANGLE_H_
#define _HKTRIANGLE_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! A triangle with extra data used for physics. */
struct hkTriangle {
	/*! Default Constructor */
	NIFLIB_API hkTriangle();
	/*! Default Destructor */
	NIFLIB_API ~hkTriangle();
	/*! Copy Constructor */
	NIFLIB_API hkTriangle( const hkTriangle & src );
	/*! Copy Operator */
	NIFLIB_API hkTriangle & operator=( const hkTriangle & src );
	/*! The triangle. */
	Triangle triangle;
	/*! Additional havok information on how triangles are welded. */
	unsigned short weldingInfo;
	/*! This is the triangle's normal. */
	Vector3 normal;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
