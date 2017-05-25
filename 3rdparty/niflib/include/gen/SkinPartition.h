/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _SKINPARTITION_H_
#define _SKINPARTITION_H_

#include "../NIF_IO.h"

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
	/*! Number of weight coefficients per vertex. */
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
	/*! Do we have strip data? */
	bool hasStrips;
	/*! The strips. */
	vector< vector<unsigned short > > strips;
	/*! The triangles. */
	vector<Triangle > triangles;
	/*! Do we have bone indices? */
	bool hasBoneIndices;
	/*! Bone indices, they index into 'Bones'. */
	vector< vector<byte > > boneIndices;
};

}
#endif
