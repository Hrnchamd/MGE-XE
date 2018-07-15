/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _SEMANTICDATA_H_
#define _SEMANTICDATA_H_

#include "../NIF_IO.h"

namespace Niflib {


/*!  */
struct SemanticData {
	/*! Default Constructor */
	NIFLIB_API SemanticData();
	/*! Default Destructor */
	NIFLIB_API ~SemanticData();
	/*! Copy Constructor */
	NIFLIB_API SemanticData( const SemanticData & src );
	/*! Copy Operator */
	NIFLIB_API SemanticData & operator=( const SemanticData & src );
	/*!
	 * Type of data (POSITION, POSITION_BP, INDEX, NORMAL, NORMAL_BP,
	 *             TEXCOORD, BLENDINDICES, BLENDWEIGHT, BONE_PALETTE, COLOR,
	 * DISPLAYLIST,
	 *             MORPH_POSITION, BINORMAL_BP, TANGENT_BP).
	 */
	IndexString name;
	/*!
	 * An extra index of the data. For example, if there are 3 uv maps,
	 *             then the corresponding TEXCOORD data components would have indices
	 *             0, 1, and 2, respectively.
	 */
	unsigned int index;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
