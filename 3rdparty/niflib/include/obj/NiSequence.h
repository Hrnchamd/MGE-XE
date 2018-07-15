/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NISEQUENCE_H_
#define _NISEQUENCE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiObject.h"

// Include structures
#include "../Ref.h"
#include "../gen/ControllerLink.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiTextKeyExtraData;
class NiSequence;
typedef Ref<NiSequence> NiSequenceRef;

/*! Root node used in some Empire Earth II .kf files (version 4.2.2.0). */
class NiSequence : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiSequence();

	/*! Destructor */
	NIFLIB_API virtual ~NiSequence();

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

   // Name of this object. This is also the name of the action associated with this
   // file. For instance, if the original NIF file is called "demon.nif" and this
   // animation file contains an attack sequence, then the file would be called
   // "demon_attack1.kf" and this field would contain the string "attack1".
   // \return The current value.
   string GetName() const;

   // Name of this object. This is also the name of the action associated with this
   // file. For instance, if the original NIF file is called "demon.nif" and this
   // animation file contains an attack sequence, then the file would be called
   // "demon_attack1.kf" and this field would contain the string "attack1".
   // \param[in] value The new value.
   void SetName( const string & value );

   // Name of following referenced NiTextKeyExtraData class.
   // \return The current value.
   string GetTextKeysName() const;

   // Name of following referenced NiTextKeyExtraData class.
   // \param[in] value The new value.
   void SetTextKeysName( const string & value );

   // Link to NiTextKeyExtraData.
   // \return The current value.
   Ref<NiTextKeyExtraData > GetTextKeys() const;

   // Link to NiTextKeyExtraData.
   // \param[in] value The new value.
   void SetTextKeys( Ref<NiTextKeyExtraData > value );

   // Refers to controlled objects.
   // \return The current value.
   vector<ControllerLink > GetControlledBlocks() const;

   // Refers to controlled objects.
   // \param[in] value The new value.
   void SetControlledBlocks( const vector<ControllerLink >& value );

	//--END CUSTOM CODE--//
protected:
	/*!
	 * Name of this object. This is also the name of the action associated with this
	 * file. For instance, if the original NIF file is called "demon.nif" and this
	 * animation file contains an attack sequence, then the file would be called
	 * "demon_attack1.kf" and this field would contain the string "attack1".
	 */
	IndexString name;
	/*! Name of following referenced NiTextKeyExtraData class. */
	IndexString textKeysName;
	/*! Link to NiTextKeyExtraData. */
	Ref<NiTextKeyExtraData > textKeys;
	/*! Unknown */
	int unknownInt4;
	/*! Unknown */
	int unknownInt5;
	/*! Number of controlled objects. */
	mutable unsigned int numControlledBlocks;
	/*! Unknown. */
	unsigned int unknownInt1;
	/*! Refers to controlled objects. */
	vector<ControllerLink > controlledBlocks;
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
