/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BYTECOLOR4_H_
#define _BYTECOLOR4_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Unknown. */
struct ByteColor4 {
	/*! Default Constructor */
	NIFLIB_API ByteColor4();
	/*! Default Destructor */
	NIFLIB_API ~ByteColor4();
	/*! Copy Constructor */
	NIFLIB_API ByteColor4( const ByteColor4 & src );
	/*! Copy Operator */
	NIFLIB_API ByteColor4 & operator=( const ByteColor4 & src );
	/*! Red color component. */
	byte r;
	/*! Green color component. */
	byte g;
	/*! Blue color component. */
	byte b;
	/*! Alpha color component. */
	byte a;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
