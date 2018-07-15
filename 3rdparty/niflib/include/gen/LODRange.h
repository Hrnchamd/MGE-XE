/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _LODRANGE_H_
#define _LODRANGE_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! The distance range where a specific level of detail applies. */
struct LODRange {
	/*! Default Constructor */
	NIFLIB_API LODRange();
	/*! Default Destructor */
	NIFLIB_API ~LODRange();
	/*! Copy Constructor */
	NIFLIB_API LODRange( const LODRange & src );
	/*! Copy Operator */
	NIFLIB_API LODRange & operator=( const LODRange & src );
	/*! Begining of range. */
	float nearExtent;
	/*! End of Range. */
	float farExtent;
	/*! Unknown (0,0,0). */
	array<3,unsigned int > unknownInts;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
