/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIMATERIALPROPERTY_H_
#define _NIMATERIALPROPERTY_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiProperty.h"
namespace Niflib {

class NiMaterialProperty;
typedef Ref<NiMaterialProperty> NiMaterialPropertyRef;

/*! Describes the material shading properties. */
class NiMaterialProperty : public NiProperty {
public:
	/*! Constructor */
	NIFLIB_API NiMaterialProperty();

	/*! Destructor */
	NIFLIB_API virtual ~NiMaterialProperty();

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
	 * Can be used to get the data stored in the flags field for this object.  It is usually better to call more specific flag-toggle functions if they are availiable.
	 * \return The flag data.
	 */
	NIFLIB_API unsigned short GetFlags() const;

	/*!
	 * Can be used to set the data stored in the flags field for this object.  It is usually better to call more specific flag-toggle functions if they are availiable.
	 * \param[in] n The new flag data.  Will overwrite any existing flag data.
	 */
	NIFLIB_API void SetFlags( unsigned short n );

	/*!
	 * Gets the current transparency of this material.
	 * \return The current transparency.
	 */
	NIFLIB_API float GetTransparency() const;

	/*!
	 * Sets the current transparency of this material.
	 * \param[in] n The new transparency.
	 */
	NIFLIB_API void SetTransparency( float n );

	/*!
	 * Gets the current ambient color of this material.  This determines how the material reacts to the ambient color of any lights shining on it.  Should ususally be (1,1,1).
	 * \return The current ambient color.
	 */
	NIFLIB_API Color3 GetAmbientColor() const;

	/*!
	 * Sets the ambient color of this material.  This determines how the material reacts to the ambient color of any lights shining on it.  Should ususally be (1,1,1).
	 * \param[in] n The new ambient color.
	 */
	NIFLIB_API void SetAmbientColor( const Color3 & n );

	/*!
	 * Gets the diffuse color of this material.  This is the main color of the material.  Should be (1,1,1) if a texture is present.
	 * \return The current diffuse color.
	 */
	NIFLIB_API Color3 GetDiffuseColor() const;

	/*!
	 * Sets the diffuse color of this material.  This is the main color of the material.  Should be (1,1,1) if a texture is present.
	 * \param[in] n The new diffuse color.
	 */
	NIFLIB_API void SetDiffuseColor( const Color3 & n );

	/*!
	 * Gets the current emissive color of this material.  This is an extra color component use for objects that glow.  It makes affected objects look brighter than they would normally if set to something other than black.
	 * \return The current emissive color.
	 */
	NIFLIB_API Color3 GetEmissiveColor() const;

	/*!
	 * Sets the emissive color of this material.  This is an extra color component use for objects that glow.  It makes affected objects look brighter than they would normally if set to something other than black.
	 * \param[in] n The new emissive color.
	 */
	NIFLIB_API void SetEmissiveColor( const Color3 & n );

	/*!
	 * Gets the current specular color of this material.  This is the color of bright highlights that appear if specular lighting is enabled.  The exact look of the hilights depends on the glossiness setting of the material.
	 * \return The current specular color.
	 */
	NIFLIB_API Color3 GetSpecularColor() const;

	/*!
	 * Sets the specular color of this material.  This is the color of bright highlights that appear if specular lighting is enabled.  The exact look of the hilights depends on the glossiness setting of the material.
	 * \param[in] n The new specular color.
	 */
	NIFLIB_API void SetSpecularColor( const Color3 & n );

	/*!
	 * Gets the current glossiness of this material.  This determines how it reflects specular light.  Also known as shininess.
	 * \return The current glossiness.
	 */
	NIFLIB_API float GetGlossiness() const;

	/*!
	 * Sets the glossiness of this material.  This determines how it reflects specular light.  Also known as shininess.
	 * \param[in] n The new glossiness.
	 */
	NIFLIB_API void SetGlossiness( float n );

	//--END CUSTOM CODE--//
protected:
	/*! Property flags. */
	unsigned short flags;
	/*! How much the material reflects ambient light. */
	Color3 ambientColor;
	/*! How much the material reflects diffuse light. */
	Color3 diffuseColor;
	/*! How much light the material reflects in a specular manner. */
	Color3 specularColor;
	/*! How much light the material emits. */
	Color3 emissiveColor;
	/*! The material's glossiness. */
	float glossiness;
	/*!
	 * The material transparency (1=non-transparant). Refer to a NiAlphaProperty object
	 * in this material's parent NiTriShape object, when alpha is not 1.
	 */
	float alpha;
	/*! Unknown */
	float emitMulti;
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
