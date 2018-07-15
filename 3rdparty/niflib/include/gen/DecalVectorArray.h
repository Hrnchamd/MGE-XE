/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _DECALVECTORARRAY_H_
#define _DECALVECTORARRAY_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Array of Vectors for Decal placement in BSDecalPlacementVectorExtraData. */
struct DecalVectorArray {
	/*! Default Constructor */
	NIFLIB_API DecalVectorArray();
	/*! Default Destructor */
	NIFLIB_API ~DecalVectorArray();
	/*! Copy Constructor */
	NIFLIB_API DecalVectorArray( const DecalVectorArray & src );
	/*! Copy Operator */
	NIFLIB_API DecalVectorArray & operator=( const DecalVectorArray & src );
	/*! Number of sets */
	mutable short numVectors;
	/*! Vector XYZ coords */
	vector<Vector3 > points;
	/*! Vector Normals */
	vector<Vector3 > normals;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
