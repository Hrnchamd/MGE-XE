/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _MATCHGROUP_H_
#define _MATCHGROUP_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Group of vertex indices of vertices that match. */
struct MatchGroup {
	/*! Default Constructor */
	NIFLIB_API MatchGroup();
	/*! Default Destructor */
	NIFLIB_API ~MatchGroup();
	/*! Copy Constructor */
	NIFLIB_API MatchGroup( const MatchGroup & src );
	/*! Copy Operator */
	NIFLIB_API MatchGroup & operator=( const MatchGroup & src );
	/*! Number of vertices in this group. */
	mutable unsigned short numVertices;
	/*! The vertex indices. */
	vector<unsigned short > vertexIndices;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
