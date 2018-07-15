/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BODYPARTLIST_H_
#define _BODYPARTLIST_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Body part list for DismemberSkinInstance */
struct BodyPartList {
	/*! Default Constructor */
	NIFLIB_API BodyPartList();
	/*! Default Destructor */
	NIFLIB_API ~BodyPartList();
	/*! Copy Constructor */
	NIFLIB_API BodyPartList( const BodyPartList & src );
	/*! Copy Operator */
	NIFLIB_API BodyPartList & operator=( const BodyPartList & src );
	/*! Flags related to the Body Partition */
	BSPartFlag partFlag;
	/*! Body Part Index */
	BSDismemberBodyPartType bodyPart;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
