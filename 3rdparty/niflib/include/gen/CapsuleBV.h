/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _CAPSULEBV_H_
#define _CAPSULEBV_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Capsule Bounding Volume */
struct CapsuleBV {
	/*! Default Constructor */
	NIFLIB_API CapsuleBV();
	/*! Default Destructor */
	NIFLIB_API ~CapsuleBV();
	/*! Copy Constructor */
	NIFLIB_API CapsuleBV( const CapsuleBV & src );
	/*! Copy Operator */
	NIFLIB_API CapsuleBV & operator=( const CapsuleBV & src );
	/*! Center */
	Vector3 center;
	/*! Origin */
	Vector3 origin;
	/*! Unknown. */
	float unknownFloat1;
	/*! Unknown. */
	float unknownFloat2;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
