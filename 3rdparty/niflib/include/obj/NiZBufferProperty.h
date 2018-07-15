/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIZBUFFERPROPERTY_H_
#define _NIZBUFFERPROPERTY_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiProperty.h"
namespace Niflib {

class NiZBufferProperty;
typedef Ref<NiZBufferProperty> NiZBufferPropertyRef;

/*! This Property controls the Z buffer (OpenGL: depth buffer). */
class NiZBufferProperty : public NiProperty {
public:
	/*! Constructor */
	NIFLIB_API NiZBufferProperty();

	/*! Destructor */
	NIFLIB_API virtual ~NiZBufferProperty();

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
	NIFLIB_API void SetFlags( unsigned short value );

	/*!
	 * Used to get the current depth buffer (Z-Buffer) test function, which determine whether a pixel is drawn based on the value of the depth buffer at the same location.
	 * \return The current depth buffer test function.
	 */
	NIFLIB_API ZCompareMode GetDepthFunction() const;

	/*!
	 * Used to set the depth buffer (Z-Buffer) test function, which determine whether a pixel is drawn based on the value of the depth buffer at the same location.
	 * \param[in] value The new depth buffer test function.
	 */
	NIFLIB_API void SetDepthFunction(ZCompareMode value);

	//--END CUSTOM CODE--//
protected:
	/*!
	 * Bit 0 enables the z test
	 *             Bit 1 controls wether the Z buffer is read only (0) or read/write
	 * (1)
	 */
	unsigned short flags;
	/*! Z-Test function (see: glDepthFunc). In Flags from 20.1.0.3 on. */
	ZCompareMode function;
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
