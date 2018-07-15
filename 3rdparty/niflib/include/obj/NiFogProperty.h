/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIFOGPROPERTY_H_
#define _NIFOGPROPERTY_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiProperty.h"
namespace Niflib {

class NiFogProperty;
typedef Ref<NiFogProperty> NiFogPropertyRef;

/*! Describes... fog? */
class NiFogProperty : public NiProperty {
public:
	/*! Constructor */
	NIFLIB_API NiFogProperty();

	/*! Destructor */
	NIFLIB_API virtual ~NiFogProperty();

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
	 * Used to get the current distance when fog begins to appear, also known as fog density.
	 * \return The current fog depth.
	 */
	NIFLIB_API float GetFogDepth() const;

	/*!
	 * Used to set the distance when fog begins to appear, also known as fog density.
	 * \param[in] value The new fog depth.
	 */
	NIFLIB_API void SetFogDepth(float value);

	/*!
	 * Used to get the current color of the fog.
	 * \return The current fog color.
	 */
	NIFLIB_API Color3 GetFogColor() const;

	/*!
	 * Used to set the color of the fog.
	 * \param[in] value The new fog color.
	 */
	NIFLIB_API void SetFogColor(Color3 value);

	//--END CUSTOM CODE--//
protected:
	/*!
	 * 1's bit: Enables Fog
	 *             2's bit: Sets Fog Function to FOG_RANGE_SQ
	 *             4's bit: Sets Fog Function to FOG_VERTEX_ALPHA
	 * 
	 *             If 2's and 4's bit are not set, but fog is enabled, Fog function is
	 * FOG_Z_LINEAR.
	 */
	unsigned short flags;
	/*! The thickness of the fog?  Default is 1.0 */
	float fogDepth;
	/*! The color of the fog. */
	Color3 fogColor;
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
