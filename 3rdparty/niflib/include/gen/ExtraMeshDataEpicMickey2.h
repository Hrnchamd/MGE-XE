/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _EXTRAMESHDATAEPICMICKEY2_H_
#define _EXTRAMESHDATAEPICMICKEY2_H_

#include "../NIF_IO.h"

namespace Niflib {


/*!  */
struct ExtraMeshDataEpicMickey2 {
	/*! Default Constructor */
	NIFLIB_API ExtraMeshDataEpicMickey2();
	/*! Default Destructor */
	NIFLIB_API ~ExtraMeshDataEpicMickey2();
	/*! Copy Constructor */
	NIFLIB_API ExtraMeshDataEpicMickey2( const ExtraMeshDataEpicMickey2 & src );
	/*! Copy Operator */
	NIFLIB_API ExtraMeshDataEpicMickey2 & operator=( const ExtraMeshDataEpicMickey2 & src );
	/*! Unknown. */
	int start;
	/*! Unknown. */
	int end;
	/*! Unknown. */
	array<10,short > unknownShorts;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
