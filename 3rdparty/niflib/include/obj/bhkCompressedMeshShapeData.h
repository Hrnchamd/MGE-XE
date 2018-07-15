/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BHKCOMPRESSEDMESHSHAPEDATA_H_
#define _BHKCOMPRESSEDMESHSHAPEDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "bhkRefObject.h"

// Include structures
#include "../gen/bhkCMSDMaterial.h"
#include "../gen/bhkCMSDTransform.h"
#include "../gen/bhkCMSDBigTris.h"
#include "../gen/bhkCMSDChunk.h"
namespace Niflib {

class bhkCompressedMeshShapeData;
typedef Ref<bhkCompressedMeshShapeData> bhkCompressedMeshShapeDataRef;

/*! A compressed mesh shape for collision in Skyrim. */
class bhkCompressedMeshShapeData : public bhkRefObject {
public:
	/*! Constructor */
	NIFLIB_API bhkCompressedMeshShapeData();

	/*! Destructor */
	NIFLIB_API virtual ~bhkCompressedMeshShapeData();

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
	 * Retrieve bitsPerIndex
	 * \return bitsPerIndex
     */
	NIFLIB_API virtual const unsigned int GetBitsPerIndex() const;
	
	/*!
	 * Set bitsPerIndex 
	 * \param[in] value bitsPerIndex
     */
	NIFLIB_API virtual void SetBitsPerIndex(unsigned int value);

	/*!
	 * Retrieve bitsPerWIndex
	 * \return bitsPerWIndex
     */
	NIFLIB_API virtual const unsigned int GetBitsPerWIndex() const;
	
	/*!
	 * Set bitsPerWIndex 
	 * \param[in] value bitsPerWIndex
     */
	NIFLIB_API virtual void SetBitsPerWIndex(unsigned int value);

	/*!
	 * Retrieve maskWIndex
	 * \return maskWIndex
     */
	NIFLIB_API virtual const unsigned int GetMaskWIndex() const;
	
	/*!
	 * Set maskWIndex 
	 * \param[in] value maskWIndex
     */
	NIFLIB_API virtual void SetMaskWIndex(unsigned int value);

	/*!
	 * Retrieve maskIndex
	 * \return maskIndex
     */
	NIFLIB_API virtual const unsigned int GetMaskIndex() const;
	
	/*!
	 * Set maskIndex
	 * \param[in] value maskIndex
     */
	NIFLIB_API virtual void SetMaskIndex(unsigned int value);

	/*!
	 * Retrieve error
	 * \return error
     */
	NIFLIB_API virtual const float GetError() const;
	
	/*!
	 * Set error
	 * \param[in] value error
     */
	NIFLIB_API virtual void SetError(float value);

	/*!
	 * Retrieve boundsMin
	 * \return boundsMin
     */
	NIFLIB_API virtual const Vector4 GetBoundsMin() const;
	
	/*!
	 * Set boundsMin
	 * \param[in] value boundsMin
     */
	NIFLIB_API virtual void SetBoundsMin(Vector4 value);

	/*!
	 * Retrieve boundsMax
	 * \return boundsMax
     */
	NIFLIB_API virtual const Vector4 GetBoundsMax() const;
	
	/*!
	 * Set boundsMax
	 * \param[in] value boundsMax
     */
	NIFLIB_API virtual void SetBoundsMax(Vector4 value);

	/*!
	 * Retrieve numMaterials
	 * \return numMaterials
     */
	NIFLIB_API virtual unsigned int GetNumMaterials() const;
	
	/*!
	 * Set numMaterials
	 * \param[in] value numMaterials
     */
	NIFLIB_API virtual void SetNumMaterials(unsigned int value);

	/*!
	 * Retrieve list of chunkMaterials
	 * \return List of the chunkMaterials
     */
	NIFLIB_API virtual const vector<bhkCMSDMaterial> & GetChunkMaterials() const;
	
	/*!
	 * Set list of chunkMaterials 
	 * \param[in] List of the chunkMaterials
     */
	NIFLIB_API virtual unsigned int SetChunkMaterials(vector<bhkCMSDMaterial>& theChunkMaterials);

	/*!
	 * Retrieve numTransforms
	 * \return numTransforms
     */
	NIFLIB_API virtual unsigned int GetNumTransforms() const;
	
	/*!
	 * Set numTransforms
	 * \param[in] value numTransforms
     */
	NIFLIB_API virtual void SetNumTransforms(unsigned int value);

	/*!
	 * Retrieve list of chunkTransforms
	 * \return List of the chunkTransforms
     */
	NIFLIB_API virtual const vector<bhkCMSDTransform> & GetChunkTransforms() const;
	
	/*!
	 * Set list of chunkTransforms 
	 * \param[in] List of the chunkTransforms
     */
	NIFLIB_API virtual unsigned int SetChunkTransforms(vector<bhkCMSDTransform>& theChunkTransforms);

	/*!
	 * Retrieve numBigVerts
	 * \return numBigVerts
     */
	NIFLIB_API virtual unsigned int GetNumBigVerts() const;
	
	/*!
	 * Set numBigVerts
	 * \param[in] value numBigVerts
     */
	NIFLIB_API virtual void SetNumBigVerts(unsigned int value);

	/*!
	 * Retrieve list of bigVerts
	 * \return List of the bigVerts
     */
	NIFLIB_API virtual const vector<Vector4> & GetBigVerts() const;
	
	/*!
	 * Set list of bigVerts 
	 * \param[in] List of the bigVerts
     */
	NIFLIB_API virtual unsigned int SetBigVerts(vector<Vector4>& theBigVerts);

	/*!
	 * Retrieve numBigTris
	 * \return numBigTris
     */
	NIFLIB_API virtual unsigned int GetNumBigTris() const;
	
	/*!
	 * Set numBigTris
	 * \param[in] value numBigTris
     */
	NIFLIB_API virtual void SetNumBigTris(unsigned int value);

	/*!
	 * Retrieve list of bigTris
	 * \return List of the bigTris
     */
	NIFLIB_API virtual const vector<bhkCMSDBigTris> & GetBigTris() const;
	
	/*!
	 * Set list of bigTris 
	 * \param[in] List of the bigTris
     */
	NIFLIB_API virtual unsigned int SetBigTris(vector<bhkCMSDBigTris>& theBigVerts);

	/*!
	 * Retrieve numChunks
	 * \return numChunks
     */
	NIFLIB_API virtual unsigned int GetNumChunks() const;
	
	/*!
	 * Set numChunks
	 * \param[in] value numChunks
     */
	NIFLIB_API virtual void SetNumChunks(unsigned int value);

	/*!
	 * Retrieve list of chunks
	 * \return List of the chunks
     */
	NIFLIB_API virtual const vector<bhkCMSDChunk> & GetChunks() const;
	
	/*!
	 * Set list of chunks 
	 * \param[in] List of the chunks
     */
	NIFLIB_API virtual unsigned int SetChunks(vector<bhkCMSDChunk>& theChunks);

	//--END CUSTOM CODE--//
protected:
	/*! Number of bits in the shape-key reserved for a triangle index */
	unsigned int bitsPerIndex;
	/*! Number of bits in the shape-key reserved for a triangle index and its winding */
	unsigned int bitsPerWIndex;
	/*!
	 * Mask used to get the triangle index and winding from a shape-key (common: 262143
	 * = 0x3ffff)
	 */
	unsigned int maskWIndex;
	/*! Mask used to get the triangle index from a shape-key (common: 131071 = 0x1ffff) */
	unsigned int maskIndex;
	/*! The radius of the storage mesh shape? Quantization error? */
	float error;
	/*!
	 * The minimum boundary of the AABB (the coordinates of the corner with the lowest
	 * numerical values)
	 */
	Vector4 boundsMin;
	/*!
	 * The maximum boundary of the AABB (the coordinates of the corner with the highest
	 * numerical values)
	 */
	Vector4 boundsMax;
	/*! Unknown */
	byte unknownByte1;
	/*! Unknown */
	unsigned int unknownInt3;
	/*! Unknown */
	unsigned int unknownInt4;
	/*! Unknown */
	unsigned int unknownInt5;
	/*! Unknown */
	byte unknownByte2;
	/*! Number of chunk materials */
	mutable unsigned int numMaterials;
	/*! Table (array) with sets of materials. Chunks refers to this table by index. */
	vector<bhkCMSDMaterial > chunkMaterials;
	/*! Unknown */
	unsigned int unknownInt6;
	/*! Number of chunk transformations */
	mutable unsigned int numTransforms;
	/*!
	 * Table (array) with sets of transformations. Chunks refers to this table by
	 * index.
	 */
	vector<bhkCMSDTransform > chunkTransforms;
	/*! Unknown */
	mutable unsigned int numBigVerts;
	/*! Compressed Vertices? */
	vector<Vector4 > bigVerts;
	/*! Unknown */
	mutable unsigned int numBigTris;
	/*! Unknown */
	vector<bhkCMSDBigTris > bigTris;
	/*! Unknown */
	mutable unsigned int numChunks;
	/*! Unknown. */
	vector<bhkCMSDChunk > chunks;
	/*! Unknown, end of block. */
	unsigned int unknownInt12;
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
