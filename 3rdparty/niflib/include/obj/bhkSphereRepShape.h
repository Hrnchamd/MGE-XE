/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BHKSPHEREREPSHAPE_H_
#define _BHKSPHEREREPSHAPE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "bhkShape.h"
namespace Niflib {

class bhkSphereRepShape;
typedef Ref<bhkSphereRepShape> bhkSphereRepShapeRef;

/*!
 * A havok shape, perhaps with a bounding sphere for quick rejection in addition to
 * more detailed shape data?
 */
class bhkSphereRepShape : public bhkShape {
public:
	/*! Constructor */
	NIFLIB_API bhkSphereRepShape();

	/*! Destructor */
	NIFLIB_API virtual ~bhkSphereRepShape();

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
	 * Get the shape's material.  This determines the type of noises the object makes as it collides in Oblivion.
	 * \return The Oblivion material used by this collision shape.
	 */
	NIFLIB_API HavokMaterial GetMaterial() const;

	/*!
	 * Sets the shape's material.  This determines the type of noises the object makes as it collides in Oblivion.
	 * \param[in] value The new material for this shape to use.
	 */
	NIFLIB_API void SetMaterial( HavokMaterial value );

	/*!
	 * Get the shape's material (Skyrim version).  This determines the type of noises the object makes as it collides in Oblivion.
	 * \return The Oblivion material used by this collision shape.
	 */
	NIFLIB_API SkyrimHavokMaterial GetSkyrimMaterial() const;

	/*!
	 * Sets the shape's material (Skyrim version).  This determines the type of noises the object makes as it collides in Oblivion.
	 * \param[in] value The new material for this shape to use.
	 */
	NIFLIB_API void SetSkyrimMaterial( SkyrimHavokMaterial value );

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
	/*! The shape's material. */
	HavokMaterial material;
	/*! The shape's material. */
	SkyrimHavokMaterial skyrimMaterial;
	/*! The radius of the sphere that encloses the shape. */
	float radius;
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
