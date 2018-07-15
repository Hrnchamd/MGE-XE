/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _SKINPARTITIONUNKNOWNITEM1_H_
#define _SKINPARTITIONUNKNOWNITEM1_H_

#include "../NIF_IO.h"

namespace Niflib {


/*!  */
struct SkinPartitionUnknownItem1 {
	/*! Default Constructor */
	NIFLIB_API SkinPartitionUnknownItem1();
	/*! Default Destructor */
	NIFLIB_API ~SkinPartitionUnknownItem1();
	/*! Copy Constructor */
	NIFLIB_API SkinPartitionUnknownItem1( const SkinPartitionUnknownItem1 & src );
	/*! Copy Operator */
	NIFLIB_API SkinPartitionUnknownItem1 & operator=( const SkinPartitionUnknownItem1 & src );
	/*! Unknown. */
	unsigned int unknownFlags;
	/*! Unknown. */
	float f1;
	/*! Unknown. */
	float f2;
	/*! Unknown. */
	float f3;
	/*! Unknown. */
	float f4;
	/*! Unknown. */
	float f5;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
