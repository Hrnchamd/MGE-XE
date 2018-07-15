/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIBSPLINEDATA_H_
#define _NIBSPLINEDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiObject.h"
namespace Niflib {

class NiBSplineData;
typedef Ref<NiBSplineData> NiBSplineDataRef;

/*! B-spline data points as floats, or as shorts for compressed B-splines. */
class NiBSplineData : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiBSplineData();

	/*! Destructor */
	NIFLIB_API virtual ~NiBSplineData();

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
	 * Get floats representing the spline data.
	 * \return The spline data.
	 */
	NIFLIB_API vector<float> GetFloatControlPoints() const;

	/*!
	* Sets the float control points representing the spline data
	* \param[in] The new float control points to replace the current ones
	*/
	NIFLIB_API void SetFloatControlPoints(vector<float> value);

	/*!
	* Adds float control points at the end of the float control points collection 
	* \param[in] The float points to add at the end of the collection
	*/
	NIFLIB_API void AppendFloatControlPoints(vector<float> value);

	/*!
	* Get the number of float control points stored in the data
	* \return The number of float control points
	*/
	NIFLIB_API int GetNumFloatControlPoints();

	/*!
	 * Get Range of signed shorts representing the data scaled by SHRT_MAX.
	 * \param[in] offset The start of the range.
	 * \param[in] count The number of control points to get.
	 * \return The control points that fall within the specified range.
	 */
	NIFLIB_API vector<float> GetFloatControlPointRange(int offset, int count) const;

	/*!
	 * Get Signed shorts representing the spline data scaled by SHRT_MAX.
	 * \return The spline data.
	 */
	NIFLIB_API vector<short> GetShortControlPoints() const;

	/*!
	* Sets the short control points representing the spline data
	* \param[in] The new short control points to replace the current ones
	*/
	NIFLIB_API void SetShortControlPoints(vector<short> value);

	/*!
	* Adds short control points at the end of the short control points collection 
	* \param[in] The short points to add at the end of the collection
	*/
	NIFLIB_API void AppendShortControlPoints(vector<short> value);

	/*!
	* Get the number of short control points stored in the data
	* \return The number of short control points
	*/
	NIFLIB_API int GetNumShortControlPoints();

	/*!
	 * Get Range of signed shorts representing the data scaled by SHRT_MAX.
	 * \param[in] offset The start of the range.
	 * \param[in] count The number of control points to get.
	 * \return The control points that fall within the specified range.
	 */
	NIFLIB_API vector<short> GetShortControlPointRange(int offset, int count) const;

	//--END CUSTOM CODE--//
protected:
	/*! Number of Float Data Points */
	mutable unsigned int numFloatControlPoints;
	/*! Float values representing the control data. */
	vector<float > floatControlPoints;
	/*! Number of Short Data Points */
	mutable unsigned int numShortControlPoints;
	/*! Signed shorts representing the data from 0 to 1 (scaled by SHRT_MAX). */
	vector<short > shortControlPoints;
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
