/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _REF_OBJECT_H_
#define _REF_OBJECT_H_

#include "Type.h"
#include "Ref.h"
#include "nif_basic_types.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <vector>

namespace Niflib {

using namespace std;

class NiObject;
class RefObject;

/*! Abstract reference tracked object */
class RefObject {
public:
	/*! Constructor */
	NIFLIB_API RefObject();

	/*! Copy Constructor */
	NIFLIB_API RefObject(const RefObject& src);

	/*! Destructor */
	NIFLIB_API virtual ~RefObject();

	/*!
	 * A constant value which uniquly identifies objects of this type.
	 */
	NIFLIB_API static const Type TYPE;

	/*!
	 * Summarizes the information contained in this object in English.
	 * \param[in] verbose Determines whether or not detailed information about large areas of data will be printed out.
	 * \return A string containing a summary of the information within the object in English.  This is the function that Niflyze calls to generate its analysis, so the output is the same.
	 */
	NIFLIB_API virtual string asString( bool verbose = false ) const = 0;

	/*!
	 * Used to determine the type of a particular instance of this object.
	 * \return The type constant for the actual type of the object.
	 */
	NIFLIB_API virtual const Type & GetType() const;

	/*!
	 * Used to determine whether this object is exactly the same type as the given type constant.
	 * \return True if this object is exactly the same type as that represented by the given type constant.  False otherwise.
	 */
	NIFLIB_API bool IsSameType( const Type & compare_to ) const;

	/*!
	 * Used to determine whether this object is exactly the same type as another object.
	 * \return True if this object is exactly the same type as the given object.  False otherwise.
	 */
	NIFLIB_API bool IsSameType( const RefObject * object ) const;

	/*!
	 * Used to determine whether this object is a derived type of the given type constant.  For example, all NIF objects are derived types of NiObject, and a NiNode is also a derived type of NiObjectNET and NiAVObject.
	 * \return True if this object is derived from the type represented by the given type constant.  False otherwise.
	 */
	NIFLIB_API bool IsDerivedType( const Type & compare_to ) const;

	/*!
	 * Used to determine whether this object is a derived type of another object.  For example, all NIF objects are derived types of NiObject, and a NiNode is also a derived type of NiObjectNET and NiAVObject.
	 * \return True if this object is derived from the type of of the given object.  False otherwise.
	 */
	NIFLIB_API bool IsDerivedType( const RefObject * objct ) const;

	/*!
	 * Formats a human readable string that includes the type of the object, and its name, if it has one.
	 * \return A string in the form:  address(type), or adress(type) {name}
	 */
	NIFLIB_API virtual string GetIDString() const;
	
	/*!
	 * Returns the total number of reference-counted objects of any kind that have been allocated by Niflib for any reason.  This is for debugging or informational purpouses.  Mostly usful for tracking down memory leaks.
	 * \return The total number of reference-counted objects that have been allocated.
	 */
	NIFLIB_API static unsigned int NumObjectsInMemory();

	/*!
	 * Increments the reference count on this object.  This should be taken care of automatically as long as you use Ref<T> smart pointers.  However, if you use bare pointers you may call this function yourself, though it is not recomended.
	 */
	NIFLIB_API void AddRef() const;

	/*!
	 * Decriments the reference count on this object.  This should be taken care of automatically as long as you use Ref<T> smart pointers.  However, if you use bare pointers you may call this function yourself, though it is not recomended.
	 */
	NIFLIB_API void SubtractRef() const;

	/*!
	 * Returns the number of references that currently exist for this object.
	 * \return The number of references to this object that are in use.
	 */
	NIFLIB_API unsigned int GetNumRefs();

private:
	mutable unsigned int _ref_count;
	static unsigned int objectsInMemory;

public:
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) = 0;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void Write( ostream& out, const map< Ref<NiObject>, unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const = 0;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void FixLinks( const map<unsigned int, Ref<NiObject> > & objects, list<unsigned int> & link_stack, list<Ref<NiObject> > & missing_link_stack, const NifInfo & info ) = 0;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual list< Ref<NiObject> > GetRefs() const = 0;
};

} //End Niflib namespace
#endif
