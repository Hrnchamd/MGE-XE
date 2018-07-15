/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIBSPLINECOMPFLOATINTERPOLATOR_H_
#define _NIBSPLINECOMPFLOATINTERPOLATOR_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiBSplineFloatInterpolator.h"
namespace Niflib {

class NiBSplineCompFloatInterpolator;
typedef Ref<NiBSplineCompFloatInterpolator> NiBSplineCompFloatInterpolatorRef;

/*! Unknown. */
class NiBSplineCompFloatInterpolator : public NiBSplineFloatInterpolator {
public:
	/*! Constructor */
	NIFLIB_API NiBSplineCompFloatInterpolator();

	/*! Destructor */
	NIFLIB_API virtual ~NiBSplineCompFloatInterpolator();

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
	* Gets the base value when a curve is not defined.
	* \return The base value.
	*/
	NIFLIB_API float GetBase() const;

	/*!
	* Sets the base value when a curve is not defined.
	* \param[in] value The new base value.
	*/
	NIFLIB_API void SetBase( float value );

	/*!
	* Gets value bias.
	* \return The value bias.
	*/
	NIFLIB_API float GetBias() const;

	/*!
	* Sets value bias.
	* \param[in] value The new value bias.
	*/
	NIFLIB_API void SetBias( float value );

	/*!
	* Gets value multiplier.
	* \return The value multiplier.
	*/
	NIFLIB_API float GetMultiplier() const;

	/*!
	* Sets value multiplier.
	* \param[in] value The new value multiplier.
	*/
	NIFLIB_API void SetMultiplier( float value );

	/*!
	* Retrieves the key data.
	* \return A vector containing control float data which specify a value over time.
	*/
	NIFLIB_API vector< float > GetControlData() const;

	/*!
	* Retrieves the sampled data between start and stop time.
	* \param npoints The number of data points to sample between start and stop time.
	* \param degree N-th order degree of polynomial used to fit the data.
	* \return A vector containing Key<float> data which specify a value over time.
	*/
	NIFLIB_API vector< Key<float> > SampleKeys(int npoints, int degree) const;

	/*!
	* Retrieves the number of control points used in the spline curve.
	* \return The number of control points used in the spline curve.
	*/
	NIFLIB_API int GetNumControlPoints() const;
	//--END CUSTOM CODE--//
protected:
	/*! Base value when curve not defined. */
	float base;
	/*! Starting offset for the data. (USHRT_MAX for no data.) */
	unsigned int offset;
	/*! Bias */
	float bias;
	/*! Multiplier */
	float multiplier;
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
