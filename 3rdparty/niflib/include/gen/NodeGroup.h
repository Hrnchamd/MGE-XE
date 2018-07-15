/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _NODEGROUP_H_
#define _NODEGROUP_H_

#include "../NIF_IO.h"

namespace Niflib {

// Forward define of referenced NIF objects
class NiNode;

/*! A group of NiNodes references. */
struct NodeGroup {
	/*! Default Constructor */
	NIFLIB_API NodeGroup();
	/*! Default Destructor */
	NIFLIB_API ~NodeGroup();
	/*! Copy Constructor */
	NIFLIB_API NodeGroup( const NodeGroup & src );
	/*! Copy Operator */
	NIFLIB_API NodeGroup & operator=( const NodeGroup & src );
	/*! Number of node references that follow. */
	mutable unsigned int numNodes;
	/*! The list of NiNode references. */
	vector<NiNode * > nodes;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
