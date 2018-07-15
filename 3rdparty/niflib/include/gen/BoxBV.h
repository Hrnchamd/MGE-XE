/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BOXBV_H_
#define _BOXBV_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Box Bounding Volume */
struct BoxBV {
	/*! Default Constructor */
	NIFLIB_API BoxBV();
	/*! Default Destructor */
	NIFLIB_API ~BoxBV();
	/*! Copy Constructor */
	NIFLIB_API BoxBV( const BoxBV & src );
	/*! Copy Operator */
	NIFLIB_API BoxBV & operator=( const BoxBV & src );
	/*! Center */
	Vector3 center;
	/*! Axis */
	array<3,Vector3 > axis;
	/*! Extent */
	array<3,float > extent;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
