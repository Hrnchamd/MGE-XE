/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BHKCMSDBIGTRIS_H_
#define _BHKCMSDBIGTRIS_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Triangle indices used in pair with "Big Verts" in a bhkCompressedMeshShapeData. */
struct bhkCMSDBigTris {
	/*! Default Constructor */
	NIFLIB_API bhkCMSDBigTris();
	/*! Default Destructor */
	NIFLIB_API ~bhkCMSDBigTris();
	/*! Copy Constructor */
	NIFLIB_API bhkCMSDBigTris( const bhkCMSDBigTris & src );
	/*! Copy Operator */
	NIFLIB_API bhkCMSDBigTris & operator=( const bhkCMSDBigTris & src );
	/*! Unknown. */
	unsigned short triangle1;
	/*! Unknown. */
	unsigned short triangle2;
	/*! Unknown. */
	unsigned short triangle3;
	/*! Always 0? */
	unsigned int unknownInt1;
	/*! Unknown. */
	unsigned short unknownShort1;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
