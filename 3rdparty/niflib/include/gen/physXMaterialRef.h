/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _PHYSXMATERIALREF_H_
#define _PHYSXMATERIALREF_H_

#include "../NIF_IO.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiPhysXMaterialDesc;

/*!  */
struct physXMaterialRef {
	/*! Default Constructor */
	NIFLIB_API physXMaterialRef();
	/*! Default Destructor */
	NIFLIB_API ~physXMaterialRef();
	/*! Copy Constructor */
	NIFLIB_API physXMaterialRef( const physXMaterialRef & src );
	/*! Copy Operator */
	NIFLIB_API physXMaterialRef & operator=( const physXMaterialRef & src );
	/*! Unknown */
	byte number;
	/*! Unknown */
	byte unknownByte1;
	/*! PhysX Material Description */
	Ref<NiPhysXMaterialDesc > materialDesc;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
