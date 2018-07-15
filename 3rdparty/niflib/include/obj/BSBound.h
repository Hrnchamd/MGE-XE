/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BSBOUND_H_
#define _BSBOUND_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiExtraData.h"
namespace Niflib {

class BSBound;
typedef Ref<BSBound> BSBoundRef;

/*! Bethesda-specific collision bounding box for skeletons. */
class BSBound : public NiExtraData {
public:
	/*! Constructor */
	NIFLIB_API BSBound();

	/*! Destructor */
	NIFLIB_API virtual ~BSBound();

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
	 * Gets the center point of the bounding box.
	 * \return The center point of the bounding box.
	 */
	NIFLIB_API Vector3 GetCenter() const;

	/*!
	 * Sets the center point of the bounding box.
	 * \param[in] value The new center point of the bounding box.
	 */
	NIFLIB_API void SetCenter( const Vector3 & value );

	/*!
	 * Gets the dimensions of the bounding box from center.  The three radii.
	 * \return The radius of the bounding box along each axis.
	 */
	NIFLIB_API Vector3 GetDimensions() const;

	/*!
	 * Gets the dimensions of the bounding box from center.  The three radii.
	 * \param[in] value The new radius of the bounding box along each axis.
	 */
	NIFLIB_API void SetDimensions( const Vector3 & value );

	//--END CUSTOM CODE--//
protected:
	/*! Center of the bounding box. */
	Vector3 center;
	/*! Dimensions of the bounding box from center. */
	Vector3 dimensions;
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
