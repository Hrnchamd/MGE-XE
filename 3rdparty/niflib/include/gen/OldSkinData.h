/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _OLDSKINDATA_H_
#define _OLDSKINDATA_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Used to store skin weights in NiTriShapeSkinController. */
struct OldSkinData {
	/*! Default Constructor */
	NIFLIB_API OldSkinData();
	/*! Default Destructor */
	NIFLIB_API ~OldSkinData();
	/*! Copy Constructor */
	NIFLIB_API OldSkinData( const OldSkinData & src );
	/*! Copy Operator */
	NIFLIB_API OldSkinData & operator=( const OldSkinData & src );
	/*! The amount that this bone affects the vertex. */
	float vertexWeight;
	/*! The index of the vertex that this weight applies to. */
	unsigned short vertexIndex;
	/*! Unknown.  Perhaps some sort of offset? */
	Vector3 unknownVector;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
