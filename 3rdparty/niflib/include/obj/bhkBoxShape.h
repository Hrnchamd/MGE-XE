/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BHKBOXSHAPE_H_
#define _BHKBOXSHAPE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "bhkConvexShape.h"
namespace Niflib {

class bhkBoxShape;
typedef Ref<bhkBoxShape> bhkBoxShapeRef;

/*! A box. */
class bhkBoxShape : public bhkConvexShape {
public:
	/*! Constructor */
	NIFLIB_API bhkBoxShape();

	/*! Destructor */
	NIFLIB_API virtual ~bhkBoxShape();

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
	 * Gets the dimensions of the box.
	 * \return The dimensions of the bounding box.
	 */
	NIFLIB_API Vector3 GetDimensions() const;

	/*!
	 * Sets the dimensions of the box.
	 * \param value The new dimensions for the bounding box.
	 */
	NIFLIB_API void SetDimensions( const Vector3 & value );

	/*! Helper routine for calculating mass properties.
	*  \param[in]  density Uniform density of object
	*  \param[in]  solid Determines whether the object is assumed to be solid or not
	*  \param[out] mass Calculated mass of the object
	*  \param[out] center Center of mass
	*  \param[out] inertia Mass Inertia Tensor
	*  \return Return mass, center, and inertia tensor.
	*/
	NIFLIB_API virtual void CalcMassProperties(float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia);

	//--END CUSTOM CODE--//
protected:
	/*! Unknown. */
	array<8,byte > unknown8Bytes;
	/*! Looks like this could be the box size. */
	Vector3 dimensions;
	/*! The smallest of the three sizes. Might be used for optimization. */
	float minimumSize;
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
