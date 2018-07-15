/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NISTRINGPALETTE_H_
#define _NISTRINGPALETTE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiObject.h"

// Include structures
#include "../gen/StringPalette.h"
namespace Niflib {

class NiStringPalette;
typedef Ref<NiStringPalette> NiStringPaletteRef;

/*!
 * List of 0x00-seperated strings, which are names of controlled objects and
 * controller types. Used in .kf files in conjunction with NiControllerSequence.
 */
class NiStringPalette : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiStringPalette();

	/*! Destructor */
	NIFLIB_API virtual ~NiStringPalette();

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
	 * Retrieves the entire palette string.  This is a buffer of characters that will contain the all the strings stored in this palette.  It is usually better to get individual strings with the NiStringPalette::GetSubStr function.
	 * \return The entire palette string.
	 */
	NIFLIB_API string GetPaletteString() const;

	/*!
	 * Sets the contents of the entire palette string.  This is a buffer of characters that will contain the all the strings stored in this palette.  It is usually better to add individual strings with the NiStringPalette::AddSubStr function.
	 * \param[in] n The new palette string.  This will overwrite all existing strings stored in the palette.
	 */
	NIFLIB_API void SetPaletteString( const string & n );

	/*!
	 * Retrieves a particular sub string from the palette by offset into the string palette.
	 * \param[in] offset The offset into the string palette where the desired sub string starts.  I.e. the number of characters that preceed it in the string palette.
	 * \return The sub string starting at the specified offset in the string palette.
	 */
	NIFLIB_API string GetSubStr( short offset ) const;

	/*!
	 * Adds a new sub string to the end of the string palete and returns the offset position where it was added.
	 * \param[in] n The new sub string to add.
	 * \return The offset into the string palette where the new sub string was added.  I.e. the number of characters that preceed it in the string palette.
	 */
	NIFLIB_API unsigned int AddSubStr( const string & n );

	//--END CUSTOM CODE--//
protected:
	/*! A bunch of 0x00 seperated strings. */
	StringPalette palette;
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
