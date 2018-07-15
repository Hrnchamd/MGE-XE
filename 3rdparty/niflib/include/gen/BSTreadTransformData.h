/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BSTREADTRANSFORMDATA_H_
#define _BSTREADTRANSFORMDATA_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Bethesda-specific node. */
struct BSTreadTransformData {
	/*! Default Constructor */
	NIFLIB_API BSTreadTransformData();
	/*! Default Destructor */
	NIFLIB_API ~BSTreadTransformData();
	/*! Copy Constructor */
	NIFLIB_API BSTreadTransformData( const BSTreadTransformData & src );
	/*! Copy Operator */
	NIFLIB_API BSTreadTransformData & operator=( const BSTreadTransformData & src );
	/*! Translation. */
	Vector3 translation;
	/*! Rotation. */
	Quaternion rotation;
	/*! Scale (usually float_min). */
	float scale;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
