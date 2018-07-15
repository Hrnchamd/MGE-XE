/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BSSEGMENTEDTRIANGLE_H_
#define _BSSEGMENTEDTRIANGLE_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Bethesda-specific node. */
struct BSSegmentedTriangle {
	/*! Default Constructor */
	NIFLIB_API BSSegmentedTriangle();
	/*! Default Destructor */
	NIFLIB_API ~BSSegmentedTriangle();
	/*! Copy Constructor */
	NIFLIB_API BSSegmentedTriangle( const BSSegmentedTriangle & src );
	/*! Copy Operator */
	NIFLIB_API BSSegmentedTriangle & operator=( const BSSegmentedTriangle & src );
	/*! Unknown */
	int unknownInt1;
	/*! Unknown */
	int unknownInt2;
	/*! Unknown */
	byte unknownByte1;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
