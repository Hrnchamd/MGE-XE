/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _AVOBJECT_H_
#define _AVOBJECT_H_

#include "../NIF_IO.h"

namespace Niflib {

// Forward define of referenced NIF objects
class NiAVObject;

/*! Used in NiDefaultAVObjectPalette. */
struct AVObject {
	/*! Default Constructor */
	NIFLIB_API AVObject();
	/*! Default Destructor */
	NIFLIB_API ~AVObject();
	/*! Copy Constructor */
	NIFLIB_API AVObject( const AVObject & src );
	/*! Copy Operator */
	NIFLIB_API AVObject & operator=( const AVObject & src );
	/*! Object name. */
	string name;
	/*! Object reference. */
	NiAVObject * avObject;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
