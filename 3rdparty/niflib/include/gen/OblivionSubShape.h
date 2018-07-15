/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _OBLIVIONSUBSHAPE_H_
#define _OBLIVIONSUBSHAPE_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Havok Information for packed TriStrip shapes. */
struct OblivionSubShape {
	/*! Default Constructor */
	NIFLIB_API OblivionSubShape();
	/*! Default Destructor */
	NIFLIB_API ~OblivionSubShape();
	/*! Copy Constructor */
	NIFLIB_API OblivionSubShape( const OblivionSubShape & src );
	/*! Copy Operator */
	NIFLIB_API OblivionSubShape & operator=( const OblivionSubShape & src );
	/*! Sets mesh color in Oblivion Construction Set. */
	OblivionLayer layer;
	/*!
	 * The first bit sets the LINK property and controls whether this body is
	 * physically linked to others. The next bit turns collision off. Then, the next
	 * bit sets the SCALED property in Oblivion. The next five bits make up the number
	 * of this part in a linked body list.
	 */
	byte colFilter;
	/*! Unknown. Perhaps the vertex wielding type? */
	unsigned short unknownShort;
	/*! The number of vertices that form this sub shape. */
	unsigned int numVertices;
	/*! The material of the subshape. */
	HavokMaterial material;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
