/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _ADDITIONALDATABLOCK_H_
#define _ADDITIONALDATABLOCK_H_

#include "../NIF_IO.h"

namespace Niflib {


/*!  */
struct AdditionalDataBlock {
	/*! Default Constructor */
	NIFLIB_API AdditionalDataBlock();
	/*! Default Destructor */
	NIFLIB_API ~AdditionalDataBlock();
	/*! Copy Constructor */
	NIFLIB_API AdditionalDataBlock( const AdditionalDataBlock & src );
	/*! Copy Operator */
	NIFLIB_API AdditionalDataBlock & operator=( const AdditionalDataBlock & src );
	/*! Has data */
	bool hasData;
	/*! Size of Block */
	mutable int blockSize;
	/*! Unknown */
	mutable int numBlocks;
	/*! Unknown */
	vector<int > blockOffsets;
	/*! Unknown */
	mutable int numData;
	/*! Unknown */
	vector<int > dataSizes;
	/*! Unknown */
	vector< vector<byte > > data;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
