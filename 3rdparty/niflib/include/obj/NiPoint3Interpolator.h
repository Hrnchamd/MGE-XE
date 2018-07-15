/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIPOINT3INTERPOLATOR_H_
#define _NIPOINT3INTERPOLATOR_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiKeyBasedInterpolator.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiPosData;
class NiPoint3Interpolator;
typedef Ref<NiPoint3Interpolator> NiPoint3InterpolatorRef;

/*! Unknown. */
class NiPoint3Interpolator : public NiKeyBasedInterpolator {
public:
	/*! Constructor */
	NIFLIB_API NiPoint3Interpolator();

	/*! Destructor */
	NIFLIB_API virtual ~NiPoint3Interpolator();

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
	 * Gets the 3D point value stored in this object.  Perhaps this is the current interpolated value, the value when posed, or at time index 0.
	 * \return The 3D point value stored in this object.
	 */
	NIFLIB_API Vector3 GetPoint3Value() const;

	/*!
	 * Sets the 3D point value stored in this object.  Perhaps this is the current interpolated value, the value when posed, or at time index 0.
	 * \param[in] value The new 3D point value to store in this object.
	 */
	NIFLIB_API void SetPoint3Value( Vector3 value );

	/*!
	 * Gets the NiPosData object that this interpolator links to, if any.
	 * \return The NiPosData object that this interpolator links to, or NULL if one is not linked.
	 */
	NIFLIB_API Ref<NiPosData> GetData() const;

	/*!
	 * Sets the NiPosData object that this interpolator links to, if any.
	 * \return The NiPosData object that this interpolator should now link to, or NULL to clear the current one.
	 */
	NIFLIB_API void SetData( NiPosData * value );

	/*!
	 * This function will adjust the times in all the keys stored in the data
	 * objects referenced by this interpolator such that phase will equal 0 and
	 * frequency will equal one.  In other words, it will cause the key times
	 * to be in seconds starting from zero.
	 * \param[in] phase The phase shift to remove from any keys stored in this
	 * object.
	 * \param[in] frequency The frequency to normalize to 1.0 for any keys
	 * stored in this object
	 */
	NIFLIB_API virtual void NormalizeKeys( float phase, float frequency );

	//--END CUSTOM CODE--//
protected:
	/*! Value when posed?  Value at time 0? */
	Vector3 point3Value;
	/*! Reference to NiPosData. */
	Ref<NiPosData > data;
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
