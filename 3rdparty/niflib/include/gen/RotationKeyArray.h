/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _ROTATIONKEYARRAY_H_
#define _ROTATIONKEYARRAY_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Rotation key array. */
template <class T >
struct RotationKeyArray {
	/*! Number of keys. */
	mutable unsigned int numKeys;
	/*! Key type (LINEAR_KEY, QUADRATIC_KEY, TBC_KEY, or XYZ_ROTATION_KEY). */
	KeyType keyType;
	/*! The rotation keys. */
	vector<Key<T > > keys;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
