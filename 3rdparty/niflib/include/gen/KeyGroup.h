/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _KEYGROUP_H_
#define _KEYGROUP_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Array of vector keys (anything that can be interpolated, except rotations). */
template <class T >
struct KeyGroup {
	/*! Number of keys in the array. */
	mutable unsigned int numKeys;
	/*! The key type. */
	KeyType interpolation;
	/*! The keys. */
	vector<Key<T > > keys;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
