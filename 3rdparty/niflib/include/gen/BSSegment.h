/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BSSEGMENT_H_
#define _BSSEGMENT_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Bethesda-specific node. */
struct BSSegment {
	/*! Default Constructor */
	NIFLIB_API BSSegment();
	/*! Default Destructor */
	NIFLIB_API ~BSSegment();
	/*! Copy Constructor */
	NIFLIB_API BSSegment( const BSSegment & src );
	/*! Copy Operator */
	NIFLIB_API BSSegment & operator=( const BSSegment & src );
	/*! Index multiplied by 1536 (0x0600) */
	int internalIndex;
	/*! Geometry present in the segment */
	BSSegmentFlags flags;
	/*! Unknown */
	byte unknownByte1;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
