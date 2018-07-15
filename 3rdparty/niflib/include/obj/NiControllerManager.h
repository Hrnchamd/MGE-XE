/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NICONTROLLERMANAGER_H_
#define _NICONTROLLERMANAGER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiTimeController.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiControllerSequence;
class NiDefaultAVObjectPalette;
class NiControllerManager;
typedef Ref<NiControllerManager> NiControllerManagerRef;

/*! Unknown. Root of all controllers? */
class NiControllerManager : public NiTimeController {
public:
	/*! Constructor */
	NIFLIB_API NiControllerManager();

	/*! Destructor */
	NIFLIB_API virtual ~NiControllerManager();

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
	 *  Used to determine whether or not the animation sequences are cumulative.
	 * \return True if animation sequences are cumulative, false otherwise.
	 */
	NIFLIB_API bool GetCumulative() const;

	/*!
	 *  Used to set whether or not the animation sequences are cumulative.
	 * \param[in] value True if animation sequences are to be cumulative, false otherwise.
	 */
	NIFLIB_API void SetCumulative( bool value );

	/*!
	 * Retrives the list of controller sequences that this controller manager references.
	 * \return The controller sequences.
	 */
	NIFLIB_API vector< Ref<NiControllerSequence> > GetControllerSequences() const;

	/*!
	 * Sets the list of controller sequences that this controller manager references.
	 * \param[in] value The new controller sequences.
	 */
	NIFLIB_API void SetControllerSequences( const vector< Ref<NiControllerSequence> > & value );

	/*!
	 * Adds a new controller sequence to this controller manager.
	 * \param[in] obj The new controller sequence to add.
	 */
	NIFLIB_API void AddSequence( NiControllerSequence * obj );

	/*!
	 * Removes a single controller sequence from this controller manager.
	 * \param[in] obj The controller sequence to remove.
	 */
	NIFLIB_API void RemoveSequence( NiControllerSequence * obj );

	/*!
	 * Removes all controller sequences from this controller manager.
	 */
	NIFLIB_API void ClearSequences();

	/*!
	 * Retrives the oject pallete object used by this controller manager.
	 * \return The object pallete.
	 */
	NIFLIB_API Ref<NiDefaultAVObjectPalette > GetObjectPalette() const;

	/*!
	 * Sets the object pallete object used by this controller manager.
	 * \param[in] value The new object pallete.
	 */
	NIFLIB_API void SetObjectPalette( NiDefaultAVObjectPalette * value );

	//--END CUSTOM CODE--//
protected:
	/*! Designates whether animation sequences are cumulative? */
	bool cumulative;
	/*! The number of controller sequence objects. */
	mutable unsigned int numControllerSequences;
	/*! Refers to a list of NiControllerSequence object. */
	vector<Ref<NiControllerSequence > > controllerSequences;
	/*! Refers to a NiDefaultAVObjectPalette. */
	Ref<NiDefaultAVObjectPalette > objectPalette;
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
