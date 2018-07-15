/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIBSPLINETRANSFORMINTERPOLATOR_H_
#define _NIBSPLINETRANSFORMINTERPOLATOR_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiBSplineInterpolator.h"
namespace Niflib {

class NiBSplineTransformInterpolator;
typedef Ref<NiBSplineTransformInterpolator> NiBSplineTransformInterpolatorRef;

/*! An interpolator for storing transform keyframes via a B-spline. */
class NiBSplineTransformInterpolator : public NiBSplineInterpolator {
public:
	/*! Constructor */
	NIFLIB_API NiBSplineTransformInterpolator();

	/*! Destructor */
	NIFLIB_API virtual ~NiBSplineTransformInterpolator();

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
	* Gets the base translation when a translate curve is not defined.
	* \return The base translation.
	*/
	NIFLIB_API Vector3 GetTranslation() const;

	/*!
	* Sets the base translation when a translate curve is not defined.
	* \param[in] value The new base translation.
	*/
	NIFLIB_API void SetTranslation( Vector3 value );

	/*!
	* Gets the translation offset for the control points in the NiSplineData
	* \return The translation offset
	*/
	NIFLIB_API int GetTranslationOffset();

	/*!
	* Sets the translation offset for the control points in the NiSplineData
	* \param[in] The new translation offset
	*/
	NIFLIB_API void SetTranslationOffset( int value );

	/*!
	* Gets the base rotation when a translate curve is not defined.
	* \return The base rotation.
	*/
	NIFLIB_API Quaternion GetRotation() const;

	/*!
	* Sets the base rotation when a translate curve is not defined.
	* \param[in] value The new base rotation.
	*/
	NIFLIB_API void SetRotation( Quaternion value );

	/*!
	* Gets the rotation offset for the control points in the NiSplineData
	* \return The rotation offset
	*/
	NIFLIB_API int GetRotationOffset();

	/*!
	* Sets the rotation offset for the control points in the NiSplineData
	* \param[in] The new rotation offset
	*/
	NIFLIB_API void SetRotationOffset( int value );

	/*!
	* Gets the base scale when a translate curve is not defined.
	* \return The base scale.
	*/
	NIFLIB_API float GetScale() const;

	/*!
	* Sets the base scale when a translate curve is not defined.
	* \param[in] value The new base scale.
	*/
	NIFLIB_API void SetScale( float value );

	/*!
	* Gets the scale offset for the control points in the NiSplineData
	* \return The scale offset
	*/
	NIFLIB_API int GetScaleOffset();

	/*!
	* Sets the scale offset for the control points in the NiSplineData
	* \param[in] The new scale offset
	*/
	NIFLIB_API void SetScaleOffset( int value );


	/*!
	* Retrieves the control quaternion rotation data.
	* \return A vector containing control Quaternion data which specify rotation over time.
	*/
	NIFLIB_API virtual vector< Quaternion > GetQuatRotateControlData() const;

	/*!
	* Retrieves the control translation data.
	* \return A vector containing control Vector3 data which specify translation over time.
	*/
	NIFLIB_API virtual vector< Vector3 > GetTranslateControlData() const;

	/*!
	* Retrieves the scale key data.
	* \return A vector containing control float data which specify scale over time.
	*/
	NIFLIB_API virtual vector< float > GetScaleControlData() const;

	/*!
	* Retrieves the sampled quaternion rotation key data between start and stop time.
	* \param npoints The number of data points to sample between start and stop time.
	* \param degree N-th order degree of polynomial used to fit the data.
	* \return A vector containing Key<Quaternion> data which specify rotation over time.
	*/
	NIFLIB_API virtual vector< Key<Quaternion> > SampleQuatRotateKeys(int npoints, int degree) const;

	/*!
	* Retrieves the sampled scale key data between start and stop time.
	* \param npoints The number of data points to sample between start and stop time.
	* \param degree N-th order degree of polynomial used to fit the data.
	* \return A vector containing Key<Vector3> data which specify translation over time.
	*/
	NIFLIB_API virtual vector< Key<Vector3> > SampleTranslateKeys(int npoints, int degree) const;

	/*!
	* Retrieves the sampled scale key data between start and stop time.
	* \param npoints The number of data points to sample between start and stop time.
	* \param degree N-th order degree of polynomial used to fit the data.
	* \return A vector containing Key<float> data which specify scale over time.
	*/
	NIFLIB_API virtual vector< Key<float> > SampleScaleKeys(int npoints, int degree) const;

	/*!
	* Retrieves the number of control points used in the spline curve.
	* \return The number of control points used in the spline curve.
	*/
	NIFLIB_API virtual int GetNumControlPoints() const;
	//--END CUSTOM CODE--//
protected:
	/*! Base translation when translate curve not defined. */
	Vector3 translation;
	/*! Base rotation when rotation curve not defined. */
	Quaternion rotation;
	/*! Base scale when scale curve not defined. */
	float scale;
	/*! Starting offset for the translation data. (USHRT_MAX for no data.) */
	unsigned int translationOffset;
	/*! Starting offset for the rotation data. (USHRT_MAX for no data.) */
	unsigned int rotationOffset;
	/*! Starting offset for the scale data. (USHRT_MAX for no data.) */
	unsigned int scaleOffset;
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
