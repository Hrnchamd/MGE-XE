/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _FURNITUREPOSITION_H_
#define _FURNITUREPOSITION_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Describes a furniture position? */
struct FurniturePosition {
	/*! Default Constructor */
	NIFLIB_API FurniturePosition();
	/*! Default Destructor */
	NIFLIB_API ~FurniturePosition();
	/*! Copy Constructor */
	NIFLIB_API FurniturePosition( const FurniturePosition & src );
	/*! Copy Operator */
	NIFLIB_API FurniturePosition & operator=( const FurniturePosition & src );
	/*! Offset of furniture marker. */
	Vector3 offset;
	/*! Furniture marker orientation. */
	unsigned short orientation;
	/*!
	 * Refers to a furnituremarkerxx.nif file. Always seems to be the same as Position
	 * Ref 2.
	 */
	byte positionRef1;
	/*!
	 * Refers to a furnituremarkerxx.nif file. Always seems to be the same as Position
	 * Ref 1.
	 */
	byte positionRef2;
	/*! Similar to Orientation, in float form. */
	float heading;
	/*! Unknown */
	AnimationType animationType;
	/*! Unknown/unused in nif? */
	FurnitureEntryPoints entryProperties;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
