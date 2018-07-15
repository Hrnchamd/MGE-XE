/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BYTECOLOR3_H_
#define _BYTECOLOR3_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Unknown. */
struct ByteColor3 {
	/*! Default Constructor */
	NIFLIB_API ByteColor3();
	/*! Default Destructor */
	NIFLIB_API ~ByteColor3();
	/*! Copy Constructor */
	NIFLIB_API ByteColor3( const ByteColor3 & src );
	/*! Copy Operator */
	NIFLIB_API ByteColor3 & operator=( const ByteColor3 & src );
	/*! Red color component. */
	byte r;
	/*! Green color component. */
	byte g;
	/*! Blue color component. */
	byte b;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
