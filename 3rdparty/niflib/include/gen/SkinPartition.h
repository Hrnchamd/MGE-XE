/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _SKINPARTITION_H_
#define _SKINPARTITION_H_

#include "../NIF_IO.h"

// Include structures
#include "SkinPartitionUnknownItem1.h"
namespace Niflib {


/*!
 * Skinning data for a submesh, optimized for hardware skinning. Part of
 * NiSkinPartition.
 */
struct SkinPartition {
	/*! Default Constructor */
	NIFLIB_API SkinPartition();
	/*! Default Destructor */
	NIFLIB_API ~SkinPartition();
	/*! Copy Constructor */
	NIFLIB_API SkinPartition( const SkinPartition & src );
	/*! Copy Operator */
	NIFLIB_API SkinPartition & operator=( const SkinPartition & src );
	/*! Number of vertices in this submesh. */
	mutable unsigned short numVertices;
	/*! Number of triangles in this submesh. */
	mutable unsigned short numTriangles;
	/*! Number of bones influencing this submesh. */
	mutable unsigned short numBones;
	/*! Number of strips in this submesh (zero if not stripped). */
	mutable unsigned short numStrips;
	/*!
	 * Number of weight coefficients per vertex. The Gamebryo engine seems to work well
	 * only if this number is equal to 4, even if there are less than 4 influences per
	 * vertex.
	 */
	mutable unsigned short numWeightsPerVertex;
	/*! List of bones. */
	vector<unsigned short > bones;
	/*! Do we have a vertex map? */
	bool hasVertexMap;
	/*!
	 * Maps the weight/influence lists in this submesh to the vertices in the shape
	 * being skinned.
	 */
	vector<unsigned short > vertexMap;
	/*! Do we have vertex weights? */
	bool hasVertexWeights;
	/*! The vertex weights. */
	vector< vector<float > > vertexWeights;
	/*! The strip lengths. */
	mutable vector<unsigned short > stripLengths;
	/*! Do we have triangle or strip data? */
	bool hasFaces;
	/*! The strips. */
	vector< vector<unsigned short > > strips;
	/*! The triangles. */
	vector<Triangle > triangles;
	/*! Do we have bone indices? */
	bool hasBoneIndices;
	/*! Bone indices, they index into 'Bones'. */
	vector< vector<byte > > boneIndices;
	/*! Unknown */
	unsigned short unknownShort;
	/*! Unknown. */
	unsigned short unknown83C3;
	/*! Unknown. */
	unsigned short unknown00001;
	/*! Unknown. */
	mutable unsigned short numVertices2;
	/*! Unknown. */
	unsigned short unknown00002;
	/*! Unknown. */
	unsigned short unknown00003;
	/*! Unknown. */
	unsigned short unknown00004;
	/*! Unknown. */
	vector<SkinPartitionUnknownItem1 > unknownArr1;
	//--BEGIN MISC CUSTOM CODE--//
	/*! Calculate proper value of numTriangles field. */
	unsigned short numTrianglesCalc() const;
	unsigned short numTrianglesCalc(const NifInfo &) const;
	//--END CUSTOM CODE--//
};

}
#endif
