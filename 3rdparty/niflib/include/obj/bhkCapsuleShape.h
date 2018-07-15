/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BHKCAPSULESHAPE_H_
#define _BHKCAPSULESHAPE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "bhkConvexShape.h"
namespace Niflib {

class bhkCapsuleShape;
typedef Ref<bhkCapsuleShape> bhkCapsuleShapeRef;

/*! A capsule. */
class bhkCapsuleShape : public bhkConvexShape {
public:
	/*! Constructor */
	NIFLIB_API bhkCapsuleShape();

	/*! Destructor */
	NIFLIB_API virtual ~bhkCapsuleShape();

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
	 * Gets the capsule's radius.
	 * \return The radius of the capsule.
	 */
	NIFLIB_API float GetRadius() const;

	/*!
	 * Sets the capsule's radius.
	 * \param[in] value The new radius for the capsule.
	 */
	NIFLIB_API void SetRadius( float value );

	/*!
	 * Gets the first point on the capsule's axis.
	 * \return The first point on the capsule's axis.
	 */
	NIFLIB_API Vector3 GetFirstPoint() const;

	/*!
	 * Sets the first point on the capsule's axis.
	 * \return The new first point on the capsule's axis.
	 */
	NIFLIB_API void SetFirstPoint( const Vector3 & value );

	/*!
	 * Gets the second capsule radius.  Seems to match the first capsule radius.
	 * \return The second capsule radius.
	 */
	NIFLIB_API float GetRadius1() const;

	/*!
	 * Sets the second capsule radius.  Seems to match the first capsule radius.
	 * \param[in] value The new second capsule radius.
	 */
	NIFLIB_API void SetRadius1( float value );

	/*!
	 * Gets the second point on the capsule's axis.
	 * \return The second point on the capsule's axis.
	 */
	NIFLIB_API Vector3 GetSecondPoint() const;

	/*!
	 * Sets the second point on the capsule's axis.
	 * \return The new second point on the capsule's axis.
	 */
	NIFLIB_API void SetSecondPoint( const Vector3 & value );

	/*!
	 * Gets the third capsule radius.  Seems to match the second capsule radius.
	 * \return The third capsule radius.
	 */
	NIFLIB_API float GetRadius2() const;

	/*!
	 * Sets the third capsule radius.  Seems to match the second capsule radius.
	 * \param[in] value The new third capsule radius.
	 */
	NIFLIB_API void SetRadius2( float value );

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
	/*! First point on the capsule's axis. */
	Vector3 firstPoint;
	/*! Matches first capsule radius. */
	float radius1;
	/*! Second point on the capsule's axis. */
	Vector3 secondPoint;
	/*! Matches second capsule radius. */
	float radius2;
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
