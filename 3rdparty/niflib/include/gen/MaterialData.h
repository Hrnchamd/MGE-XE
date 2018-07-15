/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _MATERIALDATA_H_
#define _MATERIALDATA_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Data stored per-material by NiRenderObject */
struct MaterialData {
	/*! Default Constructor */
	NIFLIB_API MaterialData();
	/*! Default Destructor */
	NIFLIB_API ~MaterialData();
	/*! Copy Constructor */
	NIFLIB_API MaterialData( const MaterialData & src );
	/*! Copy Operator */
	NIFLIB_API MaterialData & operator=( const MaterialData & src );
	/*! The name of the material. */
	IndexString materialName;
	/*! Extra data associated with the material? */
	unsigned int materialExtraData;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
