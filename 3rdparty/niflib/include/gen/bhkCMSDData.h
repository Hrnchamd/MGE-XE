/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BHKCMSDDATA_H_
#define _BHKCMSDDATA_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Unknown, used in bhkCompressedMeshShapeData */
struct bhkCMSDData {
	/*! Default Constructor */
	NIFLIB_API bhkCMSDData();
	/*! Default Destructor */
	NIFLIB_API ~bhkCMSDData();
	/*! Copy Constructor */
	NIFLIB_API bhkCMSDData( const bhkCMSDData & src );
	/*! Copy Operator */
	NIFLIB_API bhkCMSDData & operator=( const bhkCMSDData & src );
	/*! Unknown */
	Vector3 unknownFloats1;
	/*! Unknown */
	unsigned int unknownInt1;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
