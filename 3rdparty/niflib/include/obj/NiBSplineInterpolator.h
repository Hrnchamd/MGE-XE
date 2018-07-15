/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIBSPLINEINTERPOLATOR_H_
#define _NIBSPLINEINTERPOLATOR_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiInterpolator.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiBSplineData;
class NiBSplineBasisData;
class NiBSplineInterpolator;
typedef Ref<NiBSplineInterpolator> NiBSplineInterpolatorRef;

/*! For interpolators storing data via a B-spline. */
class NiBSplineInterpolator : public NiInterpolator {
public:
	/*! Constructor */
	NIFLIB_API NiBSplineInterpolator();

	/*! Destructor */
	NIFLIB_API virtual ~NiBSplineInterpolator();

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
	 * Retrieves the animation start time.
	 * \return The animation start time
	 */
	NIFLIB_API float GetStartTime() const;

	/*!
	 * Sets the animation start time.
	 * \param[in] value The new animation start time
	 */
	NIFLIB_API void SetStartTime( float value );

	/*!
	 * Retrieves the animation stop time.
	 * \return The animation stop time
	 */
	NIFLIB_API float GetStopTime() const;

	/*!
	 * Sets the animation stop time.
	 * \param[in] value The new animation stop time
	 */
	NIFLIB_API void SetStopTime( float value );

	/*!
	 * Gets the NiBSplineData used by this interpolator.
	 * \return the NiBSplineData used by this interpolator.
	 */
	NIFLIB_API Ref<NiBSplineData > GetSplineData() const;

	/*!
	 * Sets the NiBSplineData used by this interpolator.
	 * \param[in] value The NiBSplineData used by this interpolator.
	 */
	NIFLIB_API void SetSplineData( NiBSplineData * value );

	/*!
	 * Gets the NiBSplineBasisData used by this interpolator.
	 * \return the NiBSplineBasisData used by this interpolator.
	 */
	NIFLIB_API Ref<NiBSplineBasisData > GetBasisData() const;

	/*!
	 * Sets the SetBasisData used by this interpolator.
	 * \param[in] value The SetBasisData used by this interpolator.
	 */
	NIFLIB_API void SetBasisData( NiBSplineBasisData * value );

protected:
	// internal method for bspline calculation in child classes
	static void bspline(int n, int t, int l, float *control, float *output, int num_output);

	//--END CUSTOM CODE--//
protected:
	/*! Animation start time. */
	float startTime;
	/*! Animation stop time. */
	float stopTime;
	/*! Refers to NiBSplineData. */
	Ref<NiBSplineData > splineData;
	/*! Refers to NiBSPlineBasisData. */
	Ref<NiBSplineBasisData > basisData;
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
