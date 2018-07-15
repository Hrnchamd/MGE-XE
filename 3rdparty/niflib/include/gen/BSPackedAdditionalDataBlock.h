/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BSPACKEDADDITIONALDATABLOCK_H_
#define _BSPACKEDADDITIONALDATABLOCK_H_

#include "../NIF_IO.h"

namespace Niflib {


/*!  */
struct BSPackedAdditionalDataBlock {
	/*! Default Constructor */
	NIFLIB_API BSPackedAdditionalDataBlock();
	/*! Default Destructor */
	NIFLIB_API ~BSPackedAdditionalDataBlock();
	/*! Copy Constructor */
	NIFLIB_API BSPackedAdditionalDataBlock( const BSPackedAdditionalDataBlock & src );
	/*! Copy Operator */
	NIFLIB_API BSPackedAdditionalDataBlock & operator=( const BSPackedAdditionalDataBlock & src );
	/*! Has data */
	bool hasData;
	/*!
	 * Total number of bytes (over all channels and all elements, equals num total
	 * bytes per element times num vertices).
	 */
	mutable int numTotalBytes;
	/*! Number of blocks? Usually equal to one. */
	mutable int numBlocks;
	/*! Block offsets in the data? Usually equal to zero. */
	vector<int > blockOffsets;
	/*! Number of atoms? */
	mutable int numAtoms;
	/*!
	 * The sum of all of these equal num total bytes per element, so this probably
	 * describes how each data element breaks down into smaller chunks (i.e. atoms).
	 */
	vector<int > atomSizes;
	/*! Unknown */
	vector<byte > data;
	/*! Unknown. */
	int unknownInt1;
	/*!
	 * Unsure, but this seems to correspond again to the number of total bytes per
	 * element.
	 */
	int numTotalBytesPerElement;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
