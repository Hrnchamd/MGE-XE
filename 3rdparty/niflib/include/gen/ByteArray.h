/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BYTEARRAY_H_
#define _BYTEARRAY_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! An array of bytes. */
struct ByteArray {
	/*! Default Constructor */
	NIFLIB_API ByteArray();
	/*! Default Destructor */
	NIFLIB_API ~ByteArray();
	/*! Copy Constructor */
	NIFLIB_API ByteArray( const ByteArray & src );
	/*! Copy Operator */
	NIFLIB_API ByteArray & operator=( const ByteArray & src );
	/*! The number of bytes in this array */
	mutable unsigned int dataSize;
	/*! The bytes which make up the array */
	vector<byte > data;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
