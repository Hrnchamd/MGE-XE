/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIOBJECT_H_
#define _NIOBJECT_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "../RefObject.h"
#include "../Type.h"
#include "../Ref.h"
#include "../nif_basic_types.h"
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
typedef Ref<NiObject> NiObjectRef;

/*! Abstract object type. */
class NiObject : public RefObject {
public:
	/*! Constructor */
	NIFLIB_API NiObject();

	/*! Destructor */
	NIFLIB_API virtual ~NiObject();

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

	/*! Returns A new object that contains all the same data that this object does,
	 * but occupies a different part of memory.  The data stored in a NIF file varies
	 * from version to version.  Usually you are safe with the default option
	 * (the highest availiable version) but you may need to use an earlier version
	 * if you need to clone an obsolete piece of information.
	 * \param[in] version The version number to use in the memory streaming operation.  Default is the highest version availiable.
	 * \param[in] user_version The game-specific version number extention.
	 * \return A cloned copy of this object as a new object.
	 */
	NIFLIB_API Ref<NiObject> Clone( unsigned int version = 0xFFFFFFFF, unsigned int user_version = 0 );
	
public:
	/*! Block number in the nif file. Only set when you read
            blocks from the file. */
	int internal_block_number;

	//--END CUSTOM CODE--//
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

/*
* Casting Templates
*/

template <class T> Ref<T> StaticCast( NiObject * object ) {
	return (T*)object;
}

template <class T> Ref<const T> StaticCast (const NiObject * object) {
	return (const T*)object;
}

template <class T> Ref<T> DynamicCast( NiObject * object ) {
	if ( object && object->IsDerivedType(T::TYPE) ) {
		return (T*)object;
	} else {
		return NULL;
	}
}

template <class T> Ref<const T> DynamicCast( const NiObject * object ) {
	if ( object && object->IsDerivedType(T::TYPE) ) {
		return (const T*)object;
	} else {
		return NULL;
	}
}

#ifdef USE_NIFLIB_TEMPLATE_HELPERS
template <typename T, typename U> Ref<T> StaticCast( Ref<U>& object ) {
	return object;
}

template <typename T, typename U> Ref<T> DynamicCast( Ref<U>& object ) {
	return object;
}

template <typename T, typename U> Ref<T> StaticCast( const Ref<U>& object ) {
	return Ref<T>(object);
}

template <typename T, typename U> Ref<T> DynamicCast( const Ref<U>& object ) {
	return Ref<T>(object);
}

/*!
* Dynamically cast from a collection of objects to another collection
* \param objs A collection of object references to be dynamically casted to the specified type.
* \return A collection of objects that support the requested type.
*/
template <typename U, typename T>
inline vector<Ref<U> > DynamicCast( vector<Ref<T> > const & objs ) {
	vector<Ref<U> > retval;
	for (vector<Ref<T> >::const_iterator itr = objs.begin(), end = objs.end(); itr != end; ++itr) {
		Ref<U> obj = DynamicCast<U>(*itr);
		if (obj) retval.insert(retval.end(), obj);
	}
	return retval;
}

/*!
* Dynamically cast from a collection of objects to another collection
* \param objs A collection of object references to be dynamically casted to the specified type.
* \return A collection of objects that support the requested type.
*/
template <typename U, typename T>
inline list<Ref<U> > DynamicCast( list<Ref<T> > const & objs ) {
	list<Ref<U> > retval;
	for (list<Ref<T> >::const_iterator itr = objs.begin(), end = objs.end(); itr != end; ++itr) {
		Ref<U> obj = DynamicCast<U>(*itr);
		if (obj) retval.insert(retval.end(), obj);
	}
	return retval;
}
#endif


//--END CUSTOM CODE--//

} //End Niflib namespace
#endif
