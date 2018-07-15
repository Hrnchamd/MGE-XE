/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BHKNICOLLISIONOBJECT_H_
#define _BHKNICOLLISIONOBJECT_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiCollisionObject.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiObject;
class bhkNiCollisionObject;
typedef Ref<bhkNiCollisionObject> bhkNiCollisionObjectRef;

/*! Havok related collision object? */
class bhkNiCollisionObject : public NiCollisionObject {
public:
	/*! Constructor */
	NIFLIB_API bhkNiCollisionObject();

	/*! Destructor */
	NIFLIB_API virtual ~bhkNiCollisionObject();

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
   * Gets the rigid body that this collision object uses, if any.
   * \return The rigid body that this object references, or a NULL reference if it does not reference any.
   */
   NIFLIB_API Ref<NiObject> GetBody() const;

   /*!
   * Sets the new rigid body that this collision object uses.
   * \param[in] value The new rigid body for this collision object to use, or NULL to clear the current reference.
   */
   NIFLIB_API void SetBody( NiObject * value );

   /*!
   * Gets the flags field
   * \return flags
   */
   NIFLIB_API unsigned short GetFlags() const;

   /*!
   * Sets the flags field
   * \param[in] flags The new flags to be set
   */
   NIFLIB_API void SetFlags(unsigned short value);

	//--END CUSTOM CODE--//
protected:
	/*!
	 * Set to 1 for most objects, and to 41 for animated objects (OL_ANIM_STATIC).
	 * Bits: 0=Active 2=Notify 3=Set Local 6=Reset.
	 */
	unsigned short flags;
	/*! Links to the collision object data */
	Ref<NiObject > body;
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
