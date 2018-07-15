/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIMORPHDATA_H_
#define _NIMORPHDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiObject.h"

// Include structures
#include "../gen/Morph.h"
namespace Niflib {

class NiMorphData;
typedef Ref<NiMorphData> NiMorphDataRef;

/*! Geometry morphing data. */
class NiMorphData : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiMorphData();

	/*! Destructor */
	NIFLIB_API virtual ~NiMorphData();

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
	 * This function will adjust the times in all the keys stored in this data
	 * object such that phase will equal 0 and frequency will equal one.  In
	 * other words, it will cause the key times to be in seconds starting from
	 * zero.
	 * \param[in] frequency The frequency to normalize to 1.0 for any keys
	 * stored in this object
	 * \param[in] phase The phase shift to remove from any keys stored in this
	 * object.
	 */
	NIFLIB_API virtual void NormalizeKeys( float phase, float frequency );

	/*!
	 * Retrieves the number of verticies used in the morph targets.  This must be the same as the number of verticies in the base mesh that the morph controller for which this object stores data is attatched.  This is not done automatically by Niflib.
	 * \return The number of vertices used in the morph target meshes.
	 * \sa NiMorphData::SetVertexCount
	 */
	NIFLIB_API int GetVertexCount() const;

	/*!
	 * Sets the number of verticies used in the morph targets.  This must be the same as the number of verticies in the base mesh that the morph controller for which this object stores data is attatched.  This is not done automatically by Niflib.  If the new size is smaller, vertices at the ends of the morph targets will be lost.
	 * \param n The new size of the morph target's vertex arrays.
	 * \sa NiMorphData::GetVertexCount
	 */
	NIFLIB_API void SetVertexCount( int n );

	/*!
	 * Retrieves the number of morph targets used by this morph controller data.
	 * \return The number of morph targets used by this morph controller data.
	 * \sa NiMorphData::SetMorphCount
	 */
	NIFLIB_API int GetMorphCount() const;

	/*!
	 * Resizes the morph target array used by this morph controller data.  If the new size is smaller, morph targets at the end of the array and all associated data will be lost.
	 * \param n The new size of the morph target array.
	 * \sa NiMorphData::GetMorphCount
	 */
	NIFLIB_API void SetMorphCount( int n );

	/*!
	 * Retrieves the type of morph interpolation being used by a specific morph target.
	 * \param n The index of the morph to get the interpolation key type from.  A zero-based positive value which must be less than that returned by IMoprhData::GetMorphCount.
	 * \return The morph key type specifing the type of interpolation being used by the specified morph target.
	 * \sa NiMorphData::SetMorphKeyType
	 */
	NIFLIB_API KeyType GetMorphKeyType( int n ) const;
	
	/*!
	 * Sets the type of morph interpolation being used by a specific morph target.  Does not affect existing key data.
	 * \param n The index of the morph to get the interpolation key type from.  A zero-based positive value which must be less than that returned by IMoprhData::GetMorphCount.
	 * \param t The new morph key type specifing the type of interpolation to be used by the specified morph target.
	 * \sa NiMorphData::GetMorphKeyType
	 */
	NIFLIB_API void SetMorphKeyType( int n, KeyType t );

	/*!
	 * Retrieves the morph key data for a specified morph target.
	 * \return A vector containing Key<float> data which specify the influence of this morph target over time.
	 * \sa NiMorphData::SetMorphKeys, Key
	 */
	NIFLIB_API vector< Key<float> > GetMorphKeys( int n ) const;

	/*!
	 * Sets the morph key data.
	 * \param n The index of the morph target to set the keys for.
	 * \param keys A vector containing new Key<float> data which will replace any existing data for this morph target.
	 * \sa NiMorphData::GetMorphKeys, Key
	 */
	NIFLIB_API void SetMorphKeys( int n, vector< Key<float> > const & keys );

	/*!
	 * Retrieves the vertex data from the specified morph target
	 * \param n The index of the morph target to retrieve vertex data for.  This is a zero-based index whoes value that must be less than that returned by NiMorphData::GetMorphCount.
	 * \return A vector containing the vertices used by this morph target.  The size will be equal to the value returned by NiMorphData::GetVertexCount.
	 * \sa NiMorphData::SetMorphVerts
	 */
	NIFLIB_API vector<Vector3> GetMorphVerts( int n) const;

	/*!
	 * Sets the vertex data for a specified morph target
	 * \param n The index of the morph target to set vertex data for.  This is a zero-based index whoes value that must be less than that returned by NiMorphData::GetMorphCount.
	 * \param in A vector containing the new vertices to be used by this morph target.  The size will be equal to the value returned by NiMorphData::GetVertexCount.
	 * \sa NiMorphData::SetMorphVerts
	 */
	NIFLIB_API void SetMorphVerts( int n, const vector<Vector3> & in );

	/*!
	* Retrieves the morph frame name for a specified morph target.
	* \return A string which specifies the name of the morph frame.
	*/
	NIFLIB_API string GetFrameName( int n ) const;

	/*!
	* Sets the morph frame name for a specified morph target.
	* \param n The index of the morph target to set the name for.
	* \param keys A frame name which will replace any existing data for this morph target.
	*/
	NIFLIB_API void SetFrameName( int n, string const & key );

	//--END CUSTOM CODE--//
protected:
	/*! Number of morphing object. */
	mutable unsigned int numMorphs;
	/*! Number of vertices. */
	unsigned int numVertices;
	/*! This byte is always 1 in all official files. */
	byte relativeTargets;
	/*! The geometry morphing objects. */
	vector<Morph > morphs;
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
