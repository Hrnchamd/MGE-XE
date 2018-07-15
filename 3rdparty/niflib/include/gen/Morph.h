/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _MORPH_H_
#define _MORPH_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Geometry morphing data component. */
struct Morph {
	/*! Default Constructor */
	NIFLIB_API Morph();
	/*! Default Destructor */
	NIFLIB_API ~Morph();
	/*! Copy Constructor */
	NIFLIB_API Morph( const Morph & src );
	/*! Copy Operator */
	NIFLIB_API Morph & operator=( const Morph & src );
	/*! Name of the frame. */
	IndexString frameName;
	/*! The number of morph keys that follow. */
	mutable unsigned int numKeys;
	/*!
	 * Unlike most objects, the presense of this value is not conditional on there
	 * being keys.
	 */
	KeyType interpolation;
	/*! The morph key frames. */
	vector<Key<float > > keys;
	/*! Unknown. */
	unsigned int unknownInt;
	/*! Morph vectors. */
	vector<Vector3 > vectors;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
