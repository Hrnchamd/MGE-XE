/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _UNKNOWNMATRIX1_H_
#define _UNKNOWNMATRIX1_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Unknown Matrix; for deathposes.psa */
struct UnknownMatrix1 {
	/*! Default Constructor */
	NIFLIB_API UnknownMatrix1();
	/*! Default Destructor */
	NIFLIB_API ~UnknownMatrix1();
	/*! Copy Constructor */
	NIFLIB_API UnknownMatrix1( const UnknownMatrix1 & src );
	/*! Copy Operator */
	NIFLIB_API UnknownMatrix1 & operator=( const UnknownMatrix1 & src );
	/*! Unknown uint 1 */
	unsigned int unknownUint1;
	/*! Unknown. */
	float m11;
	/*! Unknown. */
	float m12;
	/*! Unknown. */
	float m13;
	/*! Unknown. */
	float m21;
	/*! Unknown. */
	float m22;
	/*! Unknown. */
	float m23;
	/*! Unknown. */
	float m31;
	/*! Unknown. */
	float m32;
	/*! Unknown. */
	float m33;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
