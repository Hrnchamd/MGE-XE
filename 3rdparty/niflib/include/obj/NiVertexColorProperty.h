/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIVERTEXCOLORPROPERTY_H_
#define _NIVERTEXCOLORPROPERTY_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiProperty.h"
namespace Niflib {

class NiVertexColorProperty;
typedef Ref<NiVertexColorProperty> NiVertexColorPropertyRef;

/*!
 * Property of vertex colors. This object is referred to by the root object of the
 * NIF file whenever some NiTriShapeData object has vertex colors with non-default
 * settings; if not present, vertex colors have vertex_mode=2 and lighting_mode=1.
 */
class NiVertexColorProperty : public NiProperty {
public:
	/*! Constructor */
	NIFLIB_API NiVertexColorProperty();

	/*! Destructor */
	NIFLIB_API virtual ~NiVertexColorProperty();

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
	 * \param[in] value The new flag data.  Will overwrite any existing flag data.
	 */
	NIFLIB_API void SetFlags(unsigned short value);

	/*!
	 * Gets the current vertex mode.  This seems to specify how to apply vertex colors.
	 * \return The current vertex mode.
	 */
	NIFLIB_API VertMode GetVertexMode() const;

	/*!
	 * Sets the vertex mode.  This seems to specify how to apply vertex colors.
	 * \param[in] value The new vertex mode.
	 */
	NIFLIB_API void SetVertexMode(VertMode value);

	/*!
	 * Gets the current lighting mode.  This seems to specify how vertex colors influence lighting.
	 * \return The current lighting mode.
	 */
	NIFLIB_API LightMode GetLightingMode() const;

	/*!
	 * Sets the lighting mode.  This seems to specify how vertex colors influence lighting.
	 * \param[in] value The new lighting mode.
	 */
	NIFLIB_API void SetLightingMode(LightMode value);

	//--END CUSTOM CODE--//
protected:
	/*!
	 * Property flags. Appears to be unused until 20.1.0.3.
	 * 
	 *             Bits 0-2: Unknown
	 *             Bit 3: Lighting Mode?
	 *             Bits 4-5: Vertex Mode?
	 */
	unsigned short flags;
	/*!
	 * Determines how vertex and material colors are mixed.
	 *             related gl function: glColorMaterial
	 *             In Flags from version 20.1.0.3 onwards.
	 */
	VertMode vertexMode;
	/*! The light mode. In Flags from 20.1.0.3 on. */
	LightMode lightingMode;
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
