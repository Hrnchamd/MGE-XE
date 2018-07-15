/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _EXPORTINFO_H_
#define _EXPORTINFO_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Information about how the file was exported */
struct ExportInfo {
	/*! Default Constructor */
	NIFLIB_API ExportInfo();
	/*! Default Destructor */
	NIFLIB_API ~ExportInfo();
	/*! Copy Constructor */
	NIFLIB_API ExportInfo( const ExportInfo & src );
	/*! Copy Operator */
	NIFLIB_API ExportInfo & operator=( const ExportInfo & src );
	/*! Probably the number of strings that follow. */
	unsigned int unknown;
	/*! Could be the name of the creator of the NIF file? */
	ShortString creator;
	/*! Unknown. Can be something like 'TriStrip Process Script'. */
	ShortString exportInfo1;
	/*!
	 * Unknown. Possibly the selected option of the export script. Can be something
	 * like 'Default Export Script'.
	 */
	ShortString exportInfo2;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
