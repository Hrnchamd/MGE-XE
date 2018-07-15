/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BONELOD_H_
#define _BONELOD_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Stores Bone Level of Detail info in a BSBoneLODExtraData */
struct BoneLOD {
	/*! Default Constructor */
	NIFLIB_API BoneLOD();
	/*! Default Destructor */
	NIFLIB_API ~BoneLOD();
	/*! Copy Constructor */
	NIFLIB_API BoneLOD( const BoneLOD & src );
	/*! Copy Operator */
	NIFLIB_API BoneLOD & operator=( const BoneLOD & src );
	/*! Distance to cull? */
	unsigned int distance;
	/*! The bones name */
	IndexString boneName;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
