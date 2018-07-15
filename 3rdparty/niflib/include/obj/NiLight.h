/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NILIGHT_H_
#define _NILIGHT_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiDynamicEffect.h"
namespace Niflib {

class NiLight;
typedef Ref<NiLight> NiLightRef;

/*! Light source. */
class NiLight : public NiDynamicEffect {
public:
	/*! Constructor */
	NIFLIB_API NiLight();

	/*! Destructor */
	NIFLIB_API virtual ~NiLight();

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
	 * Gets the current dimmer value for this light.  Used to turn the light intensity up or down.
	 * \return The current dimmer value.
	 */
	NIFLIB_API float GetDimmer() const;

	/*!
	 * Sets the dimmer value for this light.  Used to turn the light intensity up or down.
	 * \param[in] value The new dimmer value.
	 */
	NIFLIB_API void SetDimmer( float value );

	/*!
	 * Gets the current ambient color of this light.
	 * \return The current ambient color.
	 */
	NIFLIB_API Color3 GetAmbientColor() const;

	/*!
	 * Sets the ambient color of this light.
	 * \param[in] value The new ambient color.
	 */
	NIFLIB_API void SetAmbientColor( Color3 value );

	/*!
	 * Gets the current diffuse color of this light.
	 * \return The current diffuse color.
	 */
	NIFLIB_API Color3 GetDiffuseColor() const;

	/*!
	 * Sets the diffuse color of this light.
	 * \param[in] value The new diffuse color.
	 */
	NIFLIB_API void SetDiffuseColor( Color3 value );

	/*!
	 * Gets the current specular color of this light.
	 * \return The current specular color.
	 */
	NIFLIB_API Color3 GetSpecularColor() const;

	/*!
	 * Sets the specular color of this light.
	 * \param[in] value The new specular color.
	 */
	NIFLIB_API void SetSpecularColor( Color3 value );

	//--END CUSTOM CODE--//
protected:
	/*! Dimmer. */
	float dimmer;
	/*! Ambient color. */
	Color3 ambientColor;
	/*! Diffuse color. */
	Color3 diffuseColor;
	/*! Specular color. */
	Color3 specularColor;
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
