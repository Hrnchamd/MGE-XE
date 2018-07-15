/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BSTREADTRANSFSUBINFO_H_
#define _BSTREADTRANSFSUBINFO_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Bethesda-specific node. */
struct BSTreadTransfSubInfo {
	/*! Default Constructor */
	NIFLIB_API BSTreadTransfSubInfo();
	/*! Default Destructor */
	NIFLIB_API ~BSTreadTransfSubInfo();
	/*! Copy Constructor */
	NIFLIB_API BSTreadTransfSubInfo( const BSTreadTransfSubInfo & src );
	/*! Copy Operator */
	NIFLIB_API BSTreadTransfSubInfo & operator=( const BSTreadTransfSubInfo & src );
	/*! Unknown */
	int unknownInt1;
	/*! Unknown */
	int unknownInt2;
	/*! Unknown */
	int unknownInt3;
	/*! Unknown */
	int unknownInt4;
	/*! Unknown */
	int unknownInt5;
	/*! Unknown */
	int unknownInt6;
	/*! Unknown */
	int unknownInt7;
	/*! Unknown */
	int unknownInt8;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
