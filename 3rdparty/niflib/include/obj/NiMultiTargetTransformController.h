/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIMULTITARGETTRANSFORMCONTROLLER_H_
#define _NIMULTITARGETTRANSFORMCONTROLLER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiInterpController.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiAVObject;
class NiMultiTargetTransformController;
typedef Ref<NiMultiTargetTransformController> NiMultiTargetTransformControllerRef;

/*! Unknown. */
class NiMultiTargetTransformController : public NiInterpController {
public:
	/*! Constructor */
	NIFLIB_API NiMultiTargetTransformController();

	/*! Destructor */
	NIFLIB_API virtual ~NiMultiTargetTransformController();

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
	 * Retrieves a list of the extra NiAVObject targets to be controlled.
	 * \return The NiAVObject targets to be controlled.
	 */
	NIFLIB_API vector<Ref<NiAVObject> > GetExtraTargets() const;

	/*!
	 * Sets the list of the extra NiAVObject targets to be controlled.
	 * \param[in] value The new NiAVObject targets to be controlled.
	 */
	NIFLIB_API void SetExtraTargets( const vector< Ref<NiAVObject> > & value );
	
	/*!
	 * Adds a single extra target to the collection. The collection will expand if necessary.
	 * \param[in] mesh The avobject to add to the collection.
	 */
	NIFLIB_API bool AddExtraTarget( NiAVObject* target );

	/*!
	 * Remove a single extra target from the collection.
	 * \param[in] mesh The avobject remove from the collection.
	 */
	NIFLIB_API bool RemoveExtraTarget( NiAVObject* target );

	/*!
	 * Replace a single extra target by another in the specified extra target group.
	 * \param[in] newmesh The avobject put into the collection.
	 * \param[in] oldmesh The avobject remove from collection.
	 */
	NIFLIB_API bool ReplaceExtraTarget( NiAVObject* newtarget, NiAVObject* oldtarget );

	//--END CUSTOM CODE--//
protected:
	/*! The number of target pointers that follow. */
	mutable unsigned short numExtraTargets;
	/*! NiNode Targets to be controlled. */
	vector<NiAVObject * > extraTargets;
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
