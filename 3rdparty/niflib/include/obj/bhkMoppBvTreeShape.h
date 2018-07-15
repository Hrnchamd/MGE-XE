/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BHKMOPPBVTREESHAPE_H_
#define _BHKMOPPBVTREESHAPE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "bhkBvTreeShape.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class bhkShape;
class bhkMoppBvTreeShape;
typedef Ref<bhkMoppBvTreeShape> bhkMoppBvTreeShapeRef;

/*! Memory optimized partial polytope bounding volume tree shape (not an entity). */
class bhkMoppBvTreeShape : public bhkBvTreeShape {
public:
	/*! Constructor */
	NIFLIB_API bhkMoppBvTreeShape();

	/*! Destructor */
	NIFLIB_API virtual ~bhkMoppBvTreeShape();

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
	 * Retrieves the shape object that this body is using.
	 * \return The shape object being used by this body.
	 */
	NIFLIB_API Ref<bhkShape > GetShape() const;

	/*!
	 * Sets the shape object that this body will use.
	 * \param[in] value The new shape object for this body to use.
	 */
	NIFLIB_API void SetShape( bhkShape * value );

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
	* Get the shape's bounding volume code.  The code is specific to the Havok Physics engine.
	* \return A byte vector containing the code representing the MOPP.
	*/
	NIFLIB_API vector<byte> GetMoppCode() const;

	/*!
	* Sets the shape's bounding volume code.  The code is specific to the Havok Physics engine.
	* \param[in] value A byte vector containing the code representing the MOPP.
	*/
	NIFLIB_API void SetMoppCode( vector<byte> & value );

	/*!
	* Get the origin for the shape's mopp code in mopp coordinates. This is the minimum of all vertices in
	* the packed shape along each axis, minus 0.1.
	* \return The origin value in mopp coordinates.
	*/
	NIFLIB_API Vector3 GetMoppOrigin() const;

	/*!
	* Sets the origin for the shape's mopp code in mopp coordinates. This is the minimum of all vertices in
	* the packed shape along each axis, minus 0.1.
	* \param[in] value The origin in mopp coordinates.
	*/
	NIFLIB_API void SetMoppOrigin( Vector3 value );


	/*!
	* Gets the scale for the shape's mopp code in mopp coordinates. 
	*   The scaling factor to quantize the MOPP: the quantization factor is equal to
	*   256*256 divided by this number. In Oblivion files, scale is taken equal to
	*   256*256*254 / (size + 0.2) where size is the largest dimension of the bounding
	*   box of the packed shape.	
	* \return The scale value in mopp coordinates.
	*/
	NIFLIB_API float GetMoppScale() const;

	/*!
	* Sets the scale for the shape's mopp code in mopp coordinates. 
	*   The scaling factor to quantize the MOPP: the quantization factor is equal to
	*   256*256 divided by this number. In Oblivion files, scale is taken equal to
	*   256*256*254 / (size + 0.2) where size is the largest dimension of the bounding
	*   box of the packed shape.	
	* \param[in] value The scale in mopp coordinates.
	*/
	NIFLIB_API void SetMoppScale( float value );

	/*! Helper routine for calculating mass properties.
	 *  \param[in]  density Uniform density of object
	 *  \param[in]  solid Determines whether the object is assumed to be solid or not
	 *  \param[out] mass Calculated mass of the object
	 *  \param[out] center Center of mass
	 *  \param[out] inertia Mass Inertia Tensor
	 *  \return Return mass, center, and inertia tensor.
	 */
	NIFLIB_API virtual void CalcMassProperties(float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia);

private:
	unsigned int moppDataSizeCalc(const NifInfo & info) const {
		return (unsigned int)((info.version <= 0x0A000100) ? (oldMoppData.size() + 1) : moppData.size());
	};

	//--END CUSTOM CODE--//
protected:
	/*! The shape. */
	Ref<bhkShape > shape;
	/*! The shape's material. */
	HavokMaterial material;
	/*! The shape's material. */
	SkyrimHavokMaterial skyrimMaterial;
	/*! Unknown bytes. */
	array<8,byte > unknown8Bytes;
	/*! Unknown float, might be scale. */
	float unknownFloat;
	/*! Number of bytes for MOPP data. */
	mutable unsigned int moppDataSize;
	/*!
	 * Origin of the object in mopp coordinates. This is the minimum of all vertices in
	 * the packed shape along each axis, minus 0.1.
	 */
	Vector3 origin;
	/*!
	 * The scaling factor to quantize the MOPP: the quantization factor is equal to
	 * 256*256 divided by this number. In Oblivion files, scale is taken equal to
	 * 256*256*254 / (size + 0.2) where size is the largest dimension of the bounding
	 * box of the packed shape.
	 */
	float scale;
	/*!
	 * The tree of bounding volume data (old style, contains more than just the mopp
	 * script).
	 */
	vector<byte > oldMoppData;
	/*! The tree of bounding volume data. */
	vector<byte > moppData;
	/*! Unknown */
	byte unknownByte1;
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
