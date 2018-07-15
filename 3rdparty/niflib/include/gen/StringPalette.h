/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _STRINGPALETTE_H_
#define _STRINGPALETTE_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! A list of \\0 terminated strings. */
struct StringPalette {
	/*! Default Constructor */
	NIFLIB_API StringPalette();
	/*! Default Destructor */
	NIFLIB_API ~StringPalette();
	/*! Copy Constructor */
	NIFLIB_API StringPalette( const StringPalette & src );
	/*! Copy Operator */
	NIFLIB_API StringPalette & operator=( const StringPalette & src );
	/*! A bunch of 0x00 seperated strings. */
	string palette;
	/*! Length of the palette string is repeated here. */
	unsigned int length;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
