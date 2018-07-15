/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIDYNAMICEFFECT_H_
#define _NIDYNAMICEFFECT_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiAVObject.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiAVObject;
class NiDynamicEffect;
typedef Ref<NiDynamicEffect> NiDynamicEffectRef;

/*! A dynamic effect such as a light or environment map. */
class NiDynamicEffect : public NiAVObject {
public:
	/*! Constructor */
	NIFLIB_API NiDynamicEffect();

	/*! Destructor */
	NIFLIB_API virtual ~NiDynamicEffect();

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
	 * Gets the current switch state for this effect.  Perhaps this turns effect on and off?
	 * \return The current switch state for this object.
	 */
	NIFLIB_API bool GetSwitchState() const;

	/*!
	 * Sets the current switch state for this effect.  Perhaps this turns effect on and off?
	 * \param[in] value The new switch state for this object.
	 */
	NIFLIB_API void SetSwitchState( bool value );

	/*!
	 * Retrieves what appears to be a list of the nodes that will be affected by this effect.
	 * \return A list of the nodes that will be affected by this effect.
	 */
	NIFLIB_API vector<Ref<NiAVObject > > GetAffectedNodes() const;

	/*!
	 * Sets what appears to be a list of the nodes that will be affected by this effect.
	 * \param[in] value A list of the new nodes that will be affected by this effect.
	 */
	NIFLIB_API void SetAffectedNodes( const vector<Ref<NiAVObject > >& value );

	//--END CUSTOM CODE--//
protected:
	/*! Turns effect on and off?  Switches list to list of unaffected nodes? */
	bool switchState;
	/*! The number of affected nodes referenced. */
	mutable unsigned int numAffectedNodeListPointers;
	/*! The number of affected nodes referenced. */
	mutable unsigned int numAffectedNodes;
	/*!
	 * This is probably the list of affected nodes. For some reason i do not know the
	 * max exporter seems to write pointers instead of links. But it doesn't matter
	 * because at least in version 4.0.0.2 the list is automagically updated by the
	 * engine during the load stage.
	 */
	vector<unsigned int > affectedNodeListPointers;
	/*! The list of affected nodes? */
	vector<Ref<NiAVObject > > affectedNodes;
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
