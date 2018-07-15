/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIDEFAULTAVOBJECTPALETTE_H_
#define _NIDEFAULTAVOBJECTPALETTE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiAVObjectPalette.h"

// Include structures
#include "../gen/AVObject.h"
namespace Niflib {

class NiDefaultAVObjectPalette;
typedef Ref<NiDefaultAVObjectPalette> NiDefaultAVObjectPaletteRef;

/*! Unknown. Refers to a list of objects. Used by NiControllerManager. */
class NiDefaultAVObjectPalette : public NiAVObjectPalette {
public:
	/*! Constructor */
	NIFLIB_API NiDefaultAVObjectPalette();

	/*! Destructor */
	NIFLIB_API virtual ~NiDefaultAVObjectPalette();

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
	 * Gets the AV Objects stored in this palette.
	 * \return The AV Objects stored in this palette.
	 */
	NIFLIB_API vector< Ref<NiAVObject> > GetObjs() const;

	/*!
	 * Sets the AV Objects stored in this palette.
	 * \return The new AV Objects to be stored in this palette.
	 */
	NIFLIB_API void SetObjs( const vector< Ref<NiAVObject> > & value );
	
	/*!
	 * Adds a single object to the collection. The collection will expand if necessary.
	 * \param[in] mesh The object to add to the collection.
	 */
	NIFLIB_API bool AddObj( Ref<NiAVObject> obj );

	/*!
	 * Remove a single object from the collection.
	 * \param[in] mesh The object remove from the collection.
	 */
	NIFLIB_API bool RemoveObj( Ref<NiAVObject> obj );

	/*!
	 * Replace a single object by another in the collection.
	 * \param[in] newobj The object put into the collection.
	 * \param[in] oldobj The object remove from the collection.
	 */
	NIFLIB_API void ReplaceObj( const Ref<NiAVObject> newobj, const Ref<NiAVObject> oldobj );

	//--END CUSTOM CODE--//
protected:
	/*! Unknown. */
	unsigned int unknownInt;
	/*! Number of objects. */
	mutable unsigned int numObjs;
	/*! The objects. */
	vector<AVObject > objs;
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
