/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BSTREADTRANSFINFO_H_
#define _BSTREADTRANSFINFO_H_

#include "../NIF_IO.h"

// Include structures
#include "BSTreadTransfSubInfo.h"
namespace Niflib {


/*! Bethesda-specific node. */
struct BSTreadTransfInfo {
	/*! Default Constructor */
	NIFLIB_API BSTreadTransfInfo();
	/*! Default Destructor */
	NIFLIB_API ~BSTreadTransfInfo();
	/*! Copy Constructor */
	NIFLIB_API BSTreadTransfInfo( const BSTreadTransfInfo & src );
	/*! Copy Operator */
	NIFLIB_API BSTreadTransfInfo & operator=( const BSTreadTransfInfo & src );
	/*! Unknown Flag */
	float unknownFloat1;
	/*! Data */
	array<2,BSTreadTransfSubInfo > data;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
