/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIBSPLINECOMPTRANSFORMINTERPOLATOR_H_
#define _NIBSPLINECOMPTRANSFORMINTERPOLATOR_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiBSplineTransformInterpolator.h"
namespace Niflib {

class NiBSplineCompTransformInterpolator;
typedef Ref<NiBSplineCompTransformInterpolator> NiBSplineCompTransformInterpolatorRef;

/*!
 * An interpolator for storing transform keyframes via a compressed
 *         B-spline (that is, using shorts rather than floats in the B-spline
 *         data).
 */
class NiBSplineCompTransformInterpolator : public NiBSplineTransformInterpolator {
public:
	/*! Constructor */
	NIFLIB_API NiBSplineCompTransformInterpolator();

	/*! Destructor */
	NIFLIB_API virtual ~NiBSplineCompTransformInterpolator();

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
	 * Gets translate bias.
	 * \return The translate bias.
	 */
	NIFLIB_API float GetTranslateBias() const;

	/*!
	 * Sets translate bias.
	 * \param[in] value The new translate bias.
	 */
	NIFLIB_API void SetTranslateBias( float value );

	/*!
	 * Gets translate multiplier.
	 * \return The translate bias.
	 */
	NIFLIB_API float GetTranslateMultiplier() const;

	/*!
	 * Sets translate multiplier.
	 * \param[in] value The new translate bias.
	 */
	NIFLIB_API void SetTranslateMultiplier( float value );

	/*!
	 * Gets rotation bias.
	 * \return The rotation bias.
	 */
	NIFLIB_API float GetRotationBias() const;

	/*!
	 * Sets rotation bias.
	 * \param[in] value The new rotation bias.
	 */
	NIFLIB_API void SetRotationBias( float value );

	/*!
	 * Gets rotation multiplier.
	 * \return The translate bias.
	 */
	NIFLIB_API float GetRotationMultiplier() const;

	/*!
	 * Sets rotation multiplier.
	 * \param[in] value The new translate bias.
	 */
	NIFLIB_API void SetRotationMultiplier( float value );

	/*!
	 * Gets scale bias.
	 * \return The scale bias.
	 */
	NIFLIB_API float GetScaleBias() const;

	/*!
	 * Sets scale bias.
	 * \param[in] value The new scale bias.
	 */
	NIFLIB_API void SetScaleBias( float value );

	/*!
	 * Gets scale multiplier.
	 * \return The scale multiplier.
	 */
	NIFLIB_API float GetScaleMultiplier() const;

	/*!
	 * Sets scale multiplier.
	 * \param[in] value The new scale multiplier.
	 */
	NIFLIB_API void SetScaleMultiplier( float value );

	/*!
	 * Retrieves the control quaternion rotation data.
	 * \return A vector containing control Quaternion data which specify rotation over time.
	 */
	NIFLIB_API vector< Quaternion > GetQuatRotateControlData() const;

	/*!
	 * Retrieves the control translation data.
	 * \return A vector containing control Vector3 data which specify translation over time.
	 */
	NIFLIB_API vector< Vector3 > GetTranslateControlData() const;

	/*!
	 * Retrieves the scale key data.
	 * \return A vector containing control float data which specify scale over time.
	 */
	NIFLIB_API vector< float > GetScaleControlData() const;

	/*!
	 * Retrieves the sampled quaternion rotation key data between start and stop time.
	 * \param npoints The number of data points to sample between start and stop time.
	 * \param degree N-th order degree of polynomial used to fit the data.
	 * \return A vector containing Key<Quaternion> data which specify rotation over time.
	 */
	NIFLIB_API vector< Key<Quaternion> > SampleQuatRotateKeys(int npoints, int degree) const;

	/*!
	 * Retrieves the sampled scale key data between start and stop time.
	 * \param npoints The number of data points to sample between start and stop time.
	 * \param degree N-th order degree of polynomial used to fit the data.
	 * \return A vector containing Key<Vector3> data which specify translation over time.
	 */
	NIFLIB_API vector< Key<Vector3> > SampleTranslateKeys(int npoints, int degree) const;

	/*!
	 * Retrieves the sampled scale key data between start and stop time.
	 * \param npoints The number of data points to sample between start and stop time.
	 * \param degree N-th order degree of polynomial used to fit the data.
	 * \return A vector containing Key<float> data which specify scale over time.
	 */
	NIFLIB_API vector< Key<float> > SampleScaleKeys(int npoints, int degree) const;

	/*!
	 * Retrieves the number of control points used in the spline curve.
	 * \return The number of control points used in the spline curve.
	 */
	NIFLIB_API int GetNumControlPoints() const;

	//--END CUSTOM CODE--//
protected:
	/*! Translation Bias */
	float translationBias;
	/*! Translation Multiplier */
	float translationMultiplier;
	/*! Rotation Bias */
	float rotationBias;
	/*! Rotation Multiplier */
	float rotationMultiplier;
	/*! Scale Bias */
	float scaleBias;
	/*! Scale Multiplier */
	float scaleMultiplier;
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
