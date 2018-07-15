/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIKEYFRAMEDATA_H_
#define _NIKEYFRAMEDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiObject.h"

// Include structures
#include "../gen/KeyGroup.h"
namespace Niflib {

class NiKeyframeData;
typedef Ref<NiKeyframeData> NiKeyframeDataRef;

/*! Keyframes for mesh animation. */
class NiKeyframeData : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiKeyframeData();

	/*! Destructor */
	NIFLIB_API virtual ~NiKeyframeData();

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


	//--Rotate--//

	/*! Retrieves the type of rotation interpolation being used.
		* \return The rotation key type specifing the type of interpolation being used.
		* \sa IKeyframeData::SetRotateType
		*/
	NIFLIB_API KeyType GetRotateType() const;

	/*! Sets the type of rotation interpolation being used.  Does not affect existing key data.
	 * \param t The new rotation key type specifing the type of interpolation to be used.
	 * \sa IKeyframeData::GetRotateType
	 */
	NIFLIB_API void SetRotateType( KeyType t );

	/*! Retrieves the quaternion rotation key data.
	 * \return A vector containing Key<Quaternion> data which specify rotation over time.
	 * \sa IKeyframeData::SetQuatRotateKeys, Key
	 */
	NIFLIB_API vector< Key<Quaternion> > GetQuatRotateKeys() const;

	/*! Sets the quaternion rotation key data.
	 * \param keys A vector containing new Key<Quaternion> data which will replace any existing data.
	 * \sa IKeyframeData::GetQuatRotateKeys, Key
	 */
	NIFLIB_API void SetQuatRotateKeys( const vector< Key<Quaternion> > & keys );

	/*! Retrieves the type of x-rotation interpolation being used.  XYZ data is only used if rotation type is set to XYZ_ROTATION_KEY.
	 * \return The x-rotation key type specifing the type of interpolation being used.
	 * \sa IKeyframeData::SetXRotateType
	 */
	NIFLIB_API KeyType GetXRotateType() const;

	/*! Sets the type of x-rotation interpolation being used.  Does not affect existing key data.  XYZ data is only used if rotation type is set to XYZ_ROTATION_KEY.
	 * \param t The new x-rotation key type specifing the type of interpolation to be used.
	 * \sa IKeyframeData::GetXRotateType
	 */
	NIFLIB_API void SetXRotateType( KeyType t );

	/*! Retrieves the x-rotation key data.  XYZ data is only used if rotation type is set to XYZ_ROTATION_KEY.
	 * \return A vector containing Key<float> data which specify rotation over time in the x axis.
	 * \sa IKeyframeData::SetXRotateKeys, Key
	 */
	NIFLIB_API vector< Key<float> > GetXRotateKeys() const;

	/*! Sets the x-rotation key data.  XYZ data is only used if rotation type is set to XYZ_ROTATION_KEY.
	 * \param keys A vector containing new Key<float> data which will replace any existing data.
	 * \sa IKeyframeData::GetXRotateKeys, Key
	 */
	NIFLIB_API void SetXRotateKeys( const vector< Key<float> > & keys );

	/*! Retrieves the type of y-rotation interpolation being used.  XYZ data is only used if rotation type is set to XYZ_ROTATION_KEY.
	 * \return The y-rotation key type specifing the type of interpolation being used.
	 * \sa IKeyframeData::SetYRotateType
	 */
	NIFLIB_API KeyType GetYRotateType() const;

	/*! Sets the type of y-rotation interpolation being used.  Does not affect existing key data.  XYZ data is only used if rotation type is set to XYZ_ROTATION_KEY.
	 * \param t The new y-rotation key type specifing the type of interpolation to be used.
	 * \sa IKeyframeData::GetYRotateType
	 */
	NIFLIB_API void SetYRotateType( KeyType t );

	/*! Retrieves the y-rotation key data.  XYZ data is only used if rotation type is set to XYZ_ROTATION_KEY.
	 * \return A vector containing Key<float> data which specify rotation over time in the y axis.
	 * \sa IKeyframeData::SetXRotateKeys, Key
	 */
	NIFLIB_API vector< Key<float> > GetYRotateKeys() const;

	/*! Sets the y-rotation key data.  XYZ data is only used if rotation type is set to XYZ_ROTATION_KEY.
	 * \param keys A vector containing new Key<float> data which will replace any existing data.
	 * \sa IKeyframeData::GetXRotateKeys, Key
	 */
	NIFLIB_API void SetYRotateKeys( const vector< Key<float> > & keys );

	/*! Retrieves the type of z-rotation interpolation being used.  XYZ data is only used if rotation type is set to XYZ_ROTATION_KEZ.
	 * \return The z-rotation key type specifing the type of interpolation being used.
	 * \sa IKeyframeData::SetZRotateType
	 */
	NIFLIB_API KeyType GetZRotateType() const;

	/*! Sets the type of z-rotation interpolation being used.  Does not affect existing key data.  XYZ data is only used if rotation type is set to XYZ_ROTATION_KEZ.
	 * \param t The new z-rotation key type specifing the type of interpolation to be used.
	 * \sa IKeyframeData::GetZRotateType
	 */
	NIFLIB_API void SetZRotateType( KeyType t );

	/*! Retrieves the z-rotation key data.  XYZ data is only used if rotation type is set to XYZ_ROTATION_KEZ.
	 * \return A vector containing Key<float> data which specify rotation over time in the z axis.
	 * \sa IKeyframeData::SetXRotateKeys, Key
	 */
	NIFLIB_API vector< Key<float> > GetZRotateKeys() const;

	/*! Sets the z-rotation key data.  XYZ data is only used if rotation type is set to XYZ_ROTATION_KEZ.
	 * \param keys A vector containing new Key<float> data which will replace any existing data.
	 * \sa IKeyframeData::GetXRotateKeys, Key
	 */
	NIFLIB_API void SetZRotateKeys( const vector< Key<float> > & keys );

	//--Translate--//

	/*! Retrieves the type of translation interpolation being used.
	 * \return The translation key type specifing the type of interpolation being used.
	 * \sa IKeyframeData::SetTranslateType
	 */
	NIFLIB_API KeyType GetTranslateType() const;

	/*! Sets the type of translation interpolation being used.  Does not affect existing key data.
	 * \param t The new translation key type specifing the type of interpolation to be used.
	 * \sa IKeyframeData::GetTranslateType
	 */
	NIFLIB_API void SetTranslateType( KeyType t );

	/*! Retrieves the translation key data.
	 * \return A vector containing Key<Vector3> data which specify translation over time.
	 * \sa IKeyframeData::SetTranslateKeys, Key
	 */
	NIFLIB_API vector< Key<Vector3> > GetTranslateKeys() const;

	/*! Sets the translation key data.
	 * \param keys A vector containing new Key<Vector3> data which will replace any existing data.
	 * \sa IKeyframeData::GetTranslateKeys, Key
	 */
	NIFLIB_API void SetTranslateKeys( vector< Key<Vector3> > const & keys );

	//--Scale--//

	/*! Retrieves the type of scale interpolation being used.
	 * \return The scale key type specifing the type of interpolation being used.
	 * \sa IKeyframeData::SetTranslateType
	 */
	NIFLIB_API KeyType GetScaleType() const;

	/*! Sets the type of scale interpolation being used.  Does not affect existing key data.
	 * \param t The new scale key type specifing the type of interpolation to be used.
	 * \sa IKeyframeData::GetScaleType
	 */
	NIFLIB_API void SetScaleType( KeyType t );

	/*! Retrieves the scale key data.
	 * \return A vector containing Key<float> data which specify scale over time.
	 * \sa IKeyframeData::SetScaleKeys, Key
	 */
	NIFLIB_API vector< Key<float> > GetScaleKeys() const;

	/*! Sets the scale key data.
	 * \param keys A vector containing new Key<float> data which will replace any existing data.
	 * \sa IKeyframeData::GetScaleKeys, Key
	 */
	NIFLIB_API void SetScaleKeys( vector< Key<float> > const & keys );

protected:
	void UpdateRotationKeyCount();

	//--END CUSTOM CODE--//
protected:
	/*!
	 * The number of quaternion rotation keys. If the rotation type is XYZ (type 4)
	 * then this *must* be set to 1, and in this case the actual number of keys is
	 * stored in the XYZ Rotations field.
	 */
	mutable unsigned int numRotationKeys;
	/*!
	 * The type of interpolation to use for rotation.  Can also be 4 to indicate that
	 * separate X, Y, and Z values are used for the rotation instead of Quaternions.
	 */
	KeyType rotationType;
	/*! The rotation keys if Quaternion rotation is used. */
	vector<Key<Quaternion > > quaternionKeys;
	/*! Possibly a vestigial time value?  Doesn't appear to be significant. */
	float unknownFloat;
	/*! Individual arrays of keys for rotating X, Y, and Z individually. */
	array<3,KeyGroup<float > > xyzRotations;
	/*! Translation keys. */
	KeyGroup<Vector3 > translations;
	/*! Scale keys. */
	KeyGroup<float > scales;
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
