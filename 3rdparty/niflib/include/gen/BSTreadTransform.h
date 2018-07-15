/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BSTREADTRANSFORM_H_
#define _BSTREADTRANSFORM_H_

#include "../NIF_IO.h"

// Include structures
#include "BSTreadTransformData.h"
namespace Niflib {


/*! Bethesda-specific node. */
struct BSTreadTransform {
	/*! Default Constructor */
	NIFLIB_API BSTreadTransform();
	/*! Default Destructor */
	NIFLIB_API ~BSTreadTransform();
	/*! Copy Constructor */
	NIFLIB_API BSTreadTransform( const BSTreadTransform & src );
	/*! Copy Operator */
	NIFLIB_API BSTreadTransform & operator=( const BSTreadTransform & src );
	/*! Name of affected node? */
	IndexString name;
	/*! Transform data. */
	BSTreadTransformData transform1;
	/*! Transform data. */
	BSTreadTransformData transform2;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
