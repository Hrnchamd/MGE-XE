/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NISKINPARTITION_H_
#define _NISKINPARTITION_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
namespace Niflib {
class NiTriBasedGeom;
}
//--END CUSTOM CODE--//

#include "NiObject.h"

// Include structures
#include "../gen/SkinPartition.h"
namespace Niflib {

class NiSkinPartition;
typedef Ref<NiSkinPartition> NiSkinPartitionRef;

/*!
 * Skinning data, optimized for hardware skinning. The mesh is partitioned in
 * submeshes such that each vertex of a submesh is influenced only by a limited and
 * fixed number of bones.
 */
class NiSkinPartition : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiSkinPartition();

	/*! Destructor */
	NIFLIB_API virtual ~NiSkinPartition();

	/*!
	 * A constant value which uniquly identifies objects of this type.
	 */
	NIFLIB_API static const Type TYPE;

	/*!
	 * A factory function used during file reading to create an instance of this type of object.
	 * \return A pointer to a newly allocated instance of this type of object.
	 */
	NIFLIB_API static NiObject * Create();

	/*!
	 * Summarizes the information contained in this object in English.
	 * \param[in] verbose Determines whether or not detailed information about large areas of data will be printed out.
	 * \return A string containing a summary of the information within the object in English.  This is the function that Niflyze calls to generate its analysis, so the output is the same.
	 */
	NIFLIB_API virtual string asString( bool verbose = false ) const;

	/*!
	 * Used to determine the type of a particular instance of this object.
	 * \return The type constant for the actual type of the object.
	 */
	NIFLIB_API virtual const Type & GetType() const;

	//--BEGIN MISC CUSTOM CODE--//

	/*!
	 * Retrieves the number of partitions that the triangles in the skin are divided into within this skin partition data object.
	 * \return The number of skin partitions.
	 */
	NIFLIB_API int GetNumPartitions() const;

	/*!
	 * Retrieves the the number of skin weights for each vertex that a particular partition stores.
	 * \param[in] partition The index of the skin partition to get the data for.  Must be >= 0 and < the result of NiSkinPartition::GetNumPartitions.
	 * \return The number of weights per vertex in the specified partition.
	 */
	NIFLIB_API unsigned short GetWeightsPerVertex( int partition ) const;

	/*!
	 * Retrieves the the vertices in a particular partition.
	 * \param[in] partition The index of the skin partition to get the data for.  Must be >= 0 and < the result of NiSkinPartition::GetNumPartitions.
	 * \return The number of vertices in the specified partition.
	 */
	NIFLIB_API unsigned short GetNumVertices( int partition ) const;

	/*!
	 * Retrieves the the vertex map for a particular partition.  This maps the weight/influence lists in the submesh to the vertices in the skin shape.
	 * \param[in] partition The index of the skin partition to get the data for.  Must be >= 0 and < the result of NiSkinPartition::GetNumPartitions.
	 * \return The vertex map for the specified partition.
	 */
	NIFLIB_API vector<unsigned short> GetVertexMap( int partition ) const;

	/*!
	 * Retrieves the the bone map for a particular partition.  This is a list of bones that affect this partition by index.
	 * \param[in] partition The index of the skin partition to get the data for.  Must be >= 0 and < the result of NiSkinPartition::GetNumPartitions.
	 * \return The bone map for the specified partition.
	 */
	NIFLIB_API vector<unsigned short> GetBoneMap( int partition ) const;

	/*!
	 * Used to determine whether a particular partition has vertex weights.
	 * \param[in] partition The index of the skin partition to get the data for.  Must be >= 0 and < the result of NiSkinPartition::GetNumPartitions.
	 * \return True if the specified partition has vertex weights, false otherwise.
	 */
	NIFLIB_API bool HasVertexWeights( int partition ) const;

	/*!
	 * Retrieves the the vertex weights for a particular vertex in a particular partition.
	 * \param[in] partition The index of the skin partition to get the data for.  Must be >= 0 and < the result of NiSkinPartition::GetNumPartitions.
	 * \param[in] vertex The index of the vertex to get the data for.  Must be >= 0 and < the result of NiSkinPartition::GetNumVertices.
	 * \return The vertex weights for the specified vertex of the specified partition.
	 */
	NIFLIB_API vector<float> GetVertexWeights( int partition, int vertex ) const;

	/*!
	 * Used to determine whether a particular partition has vertex bone indices.  In other words, that it has bones influencing it.
	 * \param[in] partition The index of the skin partition to get the data for.  Must be >= 0 and < the result of NiSkinPartition::GetNumPartitions.
	 * \return True if the specified partition has vertex bone indices, false otherwise.
	 */
	NIFLIB_API bool HasVertexBoneIndices( int partition ) const;

	/*!
	 * Retrieves the the vertex bone indices for a particular vertex in a particular partition.
	 * \param[in] partition The index of the skin partition to get the data for.  Must be >= 0 and < the result of NiSkinPartition::GetNumPartitions.
	 * \param[in] vertex The index of the vertex to get the data for.  Must be >= 0 and < the result of NiSkinPartition::GetNumVertices.
	 * \return The vertex bone indices for the specified vertex of the specified partition.
	 */
	NIFLIB_API vector<unsigned short> GetVertexBoneIndices( int partition, int vertex ) const;

	/*!
	 * Used to get the number of triangle strips that a particular skin partition is divided into.
	 * \param[in] partition The specific partition to get the strip count from.
	 * \return The number of triangle strips used by this mesh.
	 * \sa NiSkinPartition::SetStripCount
	 */
	NIFLIB_API unsigned short GetStripCount( int partition ) const;

	/*!
	 * Used to retrieve all the triangles from a specific triangle strip in a
	 * particular skin partition.
	 * \param[in] partition The specific partition to get the triangles from.
	 * \param[in] index The index of the triangle strip to retrieve the triangles from.  This is a zero-based index which must be a positive number less than that returned by NiTriStripsData::GetStripCount.
	 * \return A vector containing all the triangle faces from the triangle strip specified by index.
	 * \sa NiSkinPartition::SetStrip
	 */
	NIFLIB_API vector<unsigned short> GetStrip( int partition, int index ) const;

	/*!
	 * Retrieves the triangles that make up a particular partition.
	 * \param[in] partition The index of the skin partition to get the data for.  Must be >= 0 and < the result of NiSkinPartition::GetNumPartitions.
	 * \return The triangles that make up the specified partition.
	 */
	NIFLIB_API vector<Triangle> GetTriangles( int partition ) const;

protected:
	friend class NiTriBasedGeom;
	NiSkinPartition(Ref<NiTriBasedGeom> shape);
	NiSkinPartition(Ref<NiTriBasedGeom> shape, int maxBonesPerPartition, int maxBonesPerVertex, bool bStrippify, int *faceMap);

public:
	NIFLIB_API void SetNumPartitions( int value );
	NIFLIB_API void SetWeightsPerVertex( int partition, unsigned short value );
	NIFLIB_API void SetNumVertices( int partition, unsigned short value );
	NIFLIB_API void SetVertexMap( int partition, const vector<unsigned short>& vertexMap );
	NIFLIB_API void SetBoneMap( int partition, const vector<unsigned short>& boneMap );

	NIFLIB_API void EnableVertexWeights( int partition, bool enable);
	NIFLIB_API void SetVertexWeights( int partition, int vertex, const vector<float> & n );

	NIFLIB_API void EnableVertexBoneIndices( int partition, bool enable);
	NIFLIB_API void SetVertexBoneIndices( int partition, int vertex, const vector<unsigned short>& boneList );

	/*!
	 * Used to resize the triangle strips array from a particular skin partition.
	 * If the new size is smaller, strips at the end of the array will be deleted.
	 * \param[in] partition The specific partition to strip array from.
	 * \param[in] n The new size of the triangle strips array.
	 * \sa NiSkinPartition::GetStripCount
	 */
	NIFLIB_API void SetStripCount( int partition, int n );

	/*!
	 * Used to set the triangle face data in a specific triangle strip from a
	 * particular skin partition.
	 * \param[in] partition The specific partition to get the strip count from.
	 * \param[in] index The index of the triangle strip to set the face data for.  This is a zero-based index which must be a positive number less than that returned by NiTriStripsData::GetStripCount.
	 * \param[in] in The vertex indices that make up this strip, in standard OpenGL triangle strip order.
	 * \sa NiSkinPartition::GetStrip
	 */
	NIFLIB_API void SetStrip( int partition, int index, const vector<unsigned short> & in );

	NIFLIB_API void SetTriangles( int partition, const vector<Triangle> & in );

	//--END CUSTOM CODE--//
protected:
	/*! Unknown. */
	mutable unsigned int numSkinPartitionBlocks;
	/*! Skin partition objects. */
	vector<SkinPartition > skinPartitionBlocks;
public:
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info );
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info );
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual list<NiObjectRef> GetRefs() const;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual list<NiObject *> GetPtrs() const;
};

//--BEGIN FILE FOOT CUSTOM CODE--//
//--END CUSTOM CODE--//

} //End Niflib namespace
#endif
