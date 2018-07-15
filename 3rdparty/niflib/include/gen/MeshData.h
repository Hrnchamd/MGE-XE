/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _MESHDATA_H_
#define _MESHDATA_H_

#include "../NIF_IO.h"

// Include structures
#include "../Ref.h"
#include "SemanticData.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiDataStream;

/*!  */
struct MeshData {
	/*! Default Constructor */
	NIFLIB_API MeshData();
	/*! Default Destructor */
	NIFLIB_API ~MeshData();
	/*! Copy Constructor */
	NIFLIB_API MeshData( const MeshData & src );
	/*! Copy Operator */
	NIFLIB_API MeshData & operator=( const MeshData & src );
	/*!
	 * Reference to a data stream object which holds the data used by
	 *             this reference.
	 */
	Ref<NiDataStream > stream;
	/*!
	 * Sets whether this stream data is per-instance data for use in
	 *             hardware instancing.
	 */
	bool isPerInstance;
	/*!
	 * The number of submesh-to-region mappings that this data stream
	 *             has.
	 */
	mutable unsigned short numSubmeshes;
	/*!  */
	vector<unsigned short > submeshToRegionMap;
	/*! Unknown. */
	mutable int numComponents;
	/*! Describes the semantic of each component. */
	vector<SemanticData > componentSemantics;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
