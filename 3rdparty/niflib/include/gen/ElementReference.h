/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _ELEMENTREFERENCE_H_
#define _ELEMENTREFERENCE_H_

#include "../NIF_IO.h"

// Include structures
#include "SemanticData.h"
namespace Niflib {


/*!  */
struct ElementReference {
	/*! Default Constructor */
	NIFLIB_API ElementReference();
	/*! Default Destructor */
	NIFLIB_API ~ElementReference();
	/*! Copy Constructor */
	NIFLIB_API ElementReference( const ElementReference & src );
	/*! Copy Operator */
	NIFLIB_API ElementReference & operator=( const ElementReference & src );
	/*! The element semantic. */
	SemanticData semantic;
	/*! Whether or not to normalize the data. */
	unsigned int normalizeFlag;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
