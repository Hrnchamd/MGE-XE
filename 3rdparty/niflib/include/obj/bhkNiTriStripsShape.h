/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BHKNITRISTRIPSSHAPE_H_
#define _BHKNITRISTRIPSSHAPE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "bhkShapeCollection.h"

// Include structures
#include "../Ref.h"
#include "../gen/OblivionColFilter.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiTriStripsData;
class bhkNiTriStripsShape;
typedef Ref<bhkNiTriStripsShape> bhkNiTriStripsShapeRef;

/*! A shape constructed from a bunch of strips. */
class bhkNiTriStripsShape : public bhkShapeCollection {
public:
	/*! Constructor */
	NIFLIB_API bhkNiTriStripsShape();

	/*! Destructor */
	NIFLIB_API virtual ~bhkNiTriStripsShape();

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
	 * Gets the scale. Usually (1.0, 1.0, 1.0).
	 * \return The scale.
	 */
	NIFLIB_API Vector3 GetScale() const;

	/*!
	 * Sets the scale. Usually (1.0, 1.0, 1.0).
	 * \param[in] n The new scale.
	 */
	NIFLIB_API void SetScale( const Vector3 & n );

	/*!
	 * Gets the number of NiTriStripsData objects referenced by this shape.
	 */
	NIFLIB_API int GetNumStripsData( );

	/*!
	 * Sets the number of NiTriStripsData objects referenced by this shape.
	 * \param[in] i The new number of NiTriStripsData objects.
	 */
	NIFLIB_API void	SetNumStripsData( int i );

	/*!
	 * Gets the NiTriStripsData object referenced by this shape at the specified index.
	 * \param[in] index The index at which the given NiTriStripsData object will be referenced.  Should be lower than the value set with bhkNiTriStripsShape::SetNumStripsData.
	 */
	NIFLIB_API Ref<NiTriStripsData> GetStripsData( int index );

	/*!
	 * Sets the NiTriStripsData object referenced by this shape at the specified index.
	 * \param[in] index The index at which the given NiTriStripsData object will be referenced.  Should be lower than the value set with bhkNiTriStripsShape::SetNumStripsData.
	 * \param[in] strips The new NiTriStripsData object to be referenced by this shape at the specified index.
	 */
	NIFLIB_API void	SetStripsData( int index, NiTriStripsData * strips );

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

	unsigned int GetNumDataLayers() const;

	/*!
	* Sets the number of OblivionColFilter objects referenced by this shape.
	* \param[in] i The new number of OblivionColFilter objects.
	*/
	NIFLIB_API void	SetNumDataLayers( unsigned int i );

	/*!
	 * Gets the OblivionLayer referenced for the filter at the specified index.
	 * \param[in] index The index at which the given OblivionLayer will be referenced.  Should be lower than the value set with bhkNiTriStripsShape::SetNumDataLayers.
	 */
	NIFLIB_API OblivionLayer GetOblivionLayer( unsigned int index ) const;

	/*!
 	 * Sets the OblivionLayer referenced for the filter at the specified index.
	 * \param[in] index The index at which the given OblivionLayer will be referenced.  Should be lower than the value set with bhkNiTriStripsShape::SetNumDataLayers.
	 */
	NIFLIB_API void SetOblivionLayer( unsigned int index, OblivionLayer layer );

	NIFLIB_API unsigned char GetOblivionFilter( unsigned int index ) const;
	NIFLIB_API void SetOblivionFilter( unsigned int index, unsigned char filter ); 

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
	/*! Unknown. */
	float unknownFloat1;
	/*! Unknown. */
	unsigned int unknownInt1;
	/*! Unknown. */
	array<4,unsigned int > unknownInts1;
	/*! Unknown */
	unsigned int unknownInt2;
	/*! Scale. Usually (1.0, 1.0, 1.0). */
	Vector3 scale;
	/*! Unknown. */
	unsigned int unknownInt3;
	/*! The number of strips data objects referenced. */
	mutable unsigned int numStripsData;
	/*! Refers to a bunch of NiTriStripsData objects that make up this shape. */
	vector<Ref<NiTriStripsData > > stripsData;
	/*! Number of Havok Layers, equal to Number of strips data objects. */
	mutable unsigned int numDataLayers;
	/*! Havok Layers for each strip data. */
	vector<OblivionColFilter > dataLayers;
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
