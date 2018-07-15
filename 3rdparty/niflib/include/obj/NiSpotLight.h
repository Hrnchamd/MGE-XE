/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NISPOTLIGHT_H_
#define _NISPOTLIGHT_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiPointLight.h"
namespace Niflib {

class NiSpotLight;
typedef Ref<NiSpotLight> NiSpotLightRef;

/*! A spot. */
class NiSpotLight : public NiPointLight {
public:
	/*! Constructor */
	NIFLIB_API NiSpotLight();

	/*! Destructor */
	NIFLIB_API virtual ~NiSpotLight();

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
	 * Retrieves the opening angle of the spot light.
	 * \return The cutoff angle.
	 */
	NIFLIB_API float GetCutoffAngle() const;

	/*!
	 * Sets the opening angle of the spot light.
	 * \param[in] value The new cutoff angle.
	 */
	NIFLIB_API void SetCutoffAngle( float value );

	/*!
	 * Retrieves the exponent of this spot light.  This describes the distribution of light.  See glLight in OpenGL.
	 * \return The exponent value.
	 */
	NIFLIB_API float GetExponent() const;

	/*!
	 * Sets the exponent of this spot light.  This describes the distribution of light.  See glLight in OpenGL.
	 * \param[in] value The new exponent value.
	 */
	NIFLIB_API void SetExponent( float value );

	//--END CUSTOM CODE--//
protected:
	/*! The opening angle of the spot. */
	float cutoffAngle;
	/*! Unknown */
	float unknownFloat;
	/*! Describes the distribution of light. (see: glLight) */
	float exponent;
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
