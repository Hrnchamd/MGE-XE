/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BYTEMATRIX_H_
#define _BYTEMATRIX_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! An array of bytes. */
struct ByteMatrix {
	/*! Default Constructor */
	NIFLIB_API ByteMatrix();
	/*! Default Destructor */
	NIFLIB_API ~ByteMatrix();
	/*! Copy Constructor */
	NIFLIB_API ByteMatrix( const ByteMatrix & src );
	/*! Copy Operator */
	NIFLIB_API ByteMatrix & operator=( const ByteMatrix & src );
	/*! The number of bytes in this array */
	mutable unsigned int dataSize1;
	/*! The number of bytes in this array */
	mutable unsigned int dataSize2;
	/*! The bytes which make up the array */
	vector< vector<byte > > data;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
