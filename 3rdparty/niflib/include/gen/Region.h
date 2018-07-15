/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _REGION_H_
#define _REGION_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! A range of indices, which make up a region (such as a submesh). */
struct Region {
	/*! Default Constructor */
	NIFLIB_API Region();
	/*! Default Destructor */
	NIFLIB_API ~Region();
	/*! Copy Constructor */
	NIFLIB_API Region( const Region & src );
	/*! Copy Operator */
	NIFLIB_API Region & operator=( const Region & src );
	/*! Unknown. */
	unsigned int startIndex;
	/*! Unknown. */
	unsigned int numIndices;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
