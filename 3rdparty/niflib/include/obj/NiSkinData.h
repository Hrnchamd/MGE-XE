/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NISKINDATA_H_
#define _NISKINDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
namespace Niflib {
	class NiGeometry;
}
//--END CUSTOM CODE--//

#include "NiObject.h"

// Include structures
#include "../gen/SkinTransform.h"
#include "../Ref.h"
#include "../gen/SkinData.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiSkinPartition;
class NiSkinData;
typedef Ref<NiSkinData> NiSkinDataRef;

/*! Skinning data. */
class NiSkinData : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiSkinData();

	/*! Destructor */
	NIFLIB_API virtual ~NiSkinData();

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
	 * Retrieves the current overall transform for this skin.  This is the transform from the geometry node back to its skeleton root.
	 * \return The current overall transform for this skin.
	 */
	NIFLIB_API Matrix44 GetOverallTransform() const;

	/*!
	 * Sets the overall transform for this skin.  This is the transform from the geometry node back to the skeleton root.
	 * \param[in] transform The new overall transform for this skin.
	 */
	NIFLIB_API void SetOverallTransform( const Matrix44 & transform );

	/*!
	 * Retrieves the number of bones influences affecting this skin.  These are NiNodes which cause the skin to deform when they move.
	 * \return The number of bonees influencing this skin.
	 */
	NIFLIB_API unsigned int GetBoneCount() const;

	/*!
	 * Retrieves the transform for a particular bone.  This is the transform from geometry node back to this bone in skeleton root coordinates.
	 * \param[in] bone_index The numeric index of the bone that the transform matrix should be returned for.  Must be >= zero and < the number returned by GetBoneCount.
	 * \return The transform matrix for the specified bone.
	 */
	NIFLIB_API Matrix44 GetBoneTransform( unsigned int bone_index ) const;

	/*!
	 * Retrieves the skin weights for a particular bone.  This information includes the vertex index into the geometry data's vertex array, and the percentage weight that defines how much the movement of this bone influences its position.
	 * \param[in] bone_index The numeric index of the bone that the skin weight data should be returned for.  Must be >= zero and < the number returned by GetBoneCount.
	 * \return The skin weight data for the specified bone.
	 */
	NIFLIB_API vector<SkinWeight> GetBoneWeights( unsigned int bone_index ) const;

	/*!
	 * Sets the skin weights for a particular bone.  This information includes the vertex index into the geometry data's vertex array, and the percentage weight that defines how much the movement of this bone influences its position.
	 * \param[in] bone_index The numeric index of the bone that the skin weight data should be set for.  Must be >= zero and < the number returned by GetBoneCount.
	 * \param[in] weights The new skin weight data for the specified bone.
	 * \param[in] center The center point of all the vertices affected by this bone.  This is the mid point between the minimums and maximums in each of the 3 directions.
	 * \param[in] radius The radius of a bounding circle centered at the center point which contains all the vertices affected by this bone.  This is the distance from the center to vertex that is the greatest distance away.
	 * \return The skin weight data for the specified bone.
	 */
	NIFLIB_API void SetBoneWeights( unsigned int bone_index, const vector<SkinWeight> & weights, Vector3 center, float radius );
	
	/*!
	 * Sets the skin weights for a particular bone, without changing center and radius
	 * \sa NiSkinData::SetBoneWeights
	 */
	NIFLIB_API void SetBoneWeights( unsigned int bone_index, const vector<SkinWeight> & weights );

	/*!
	 * Returns a reference to the hardware skin partition data object, if any.
	 * \return The hardware skin partition data, or NULL if none is used.
	 */
	NIFLIB_API Ref<NiSkinPartition> GetSkinPartition() const;

	/*!
	 * NIFLIB_HIDDEN function.  For internal use only.
	 * This constructor is called by NiGeometry when it creates a new skin instance using the BindSkin function.
	 */
	NIFLIB_HIDDEN NiSkinData( NiGeometry * owner );

	/*
	 * NIFLIB_HIDDEN function.  For internal use only.
	 * This can be used to set or clear the hardware skin partition data.  To create partition data, the NiTriBasedGeom::GenHardwareSkinInfo function should be used.
	 * \param[in] skinPartition The new hardware skin partition data object to use, or NULL to clear the existing one.
	 */
	NIFLIB_HIDDEN void SetSkinPartition( NiSkinPartition * skinPartition );

	/*
	 * NIFLIB_HIDDEN function.  For internal use only.
	 * This is called by NiGeometry when the NormalizeSkinWeights function of that object is called, which is a public function.
	 */
	NIFLIB_HIDDEN void NormalizeWeights( unsigned numVertices );
	/*!
	 * NIFLIB_HIDDEN function.  For internal use only.
	 * This function resets the bone offsets to their current positions, effetivley changing the bind pose.  This does not cause any tranformations to the vertex positions, however, so is mostly usful for instances where the world positions of the old and new bind pose are equivalent, but result from different local transformations along the way.  It is called by NiGeometry when the interum transforms are flattened.
	 */
	NIFLIB_HIDDEN void ResetOffsets( NiGeometry * owner );

	//--END CUSTOM CODE--//
protected:
	/*! Offset of the skin from this bone in bind position. */
	SkinTransform skinTransform;
	/*! Number of bones. */
	mutable unsigned int numBones;
	/*! This optionally links a NiSkinPartition for hardware-acceleration information. */
	Ref<NiSkinPartition > skinPartition;
	/*! Enables Vertex Weights for this NiSkinData. */
	byte hasVertexWeights;
	/*! Contains offset data for each node that this skin is influenced by. */
	vector<SkinData > boneList;
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
