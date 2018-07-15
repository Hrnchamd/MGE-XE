/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NICONTROLLERSEQUENCE_H_
#define _NICONTROLLERSEQUENCE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
namespace Niflib {
	class NiSingleInterpController;
}
//--END CUSTOM CODE--//

#include "NiSequence.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiTextKeyExtraData;
class NiControllerManager;
class NiStringPalette;
class BSAnimNotes;
class NiControllerSequence;
typedef Ref<NiControllerSequence> NiControllerSequenceRef;

/*! Root node in .kf files (version 10.0.1.0 and up). */
class NiControllerSequence : public NiSequence {
public:
	/*! Constructor */
	NIFLIB_API NiControllerSequence();

	/*! Destructor */
	NIFLIB_API virtual ~NiControllerSequence();

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
	 * Returns the name of this NiControllerSequence object. This is also the name of the action
	 * associated with this file. For instance, if the original NIF file is called
	 * "demon.nif" and this animation file contains an attack sequence, then
	 * the file would be called "demon_attack1.kf" and this field would
	 * contain the string "attack1".
	 * \return The name of this NiControllerSequence object.
	 */
	NIFLIB_API string GetName() const;

	/*!
	 * Sets the name of this NiControllerSequence object. This is also the name of the action
	 * associated with this file. For instance, if the original NIF file is called
	 * "demon.nif" and this animation file contains an attack sequence, then
	 * the file would be called "demon_attack1.kf" and this field would
	 * contain the string "attack1".
	 * \param[in] value The new name for this NiControllerSequence object.
	 */
	NIFLIB_API void SetName( const string & value );

	/*!
	 * Sets the name and reference to the NiTextKeyExtraData object which will be used by this controller sequence to specify the keyframe labels or "notes."
	 * \param[in] txt_key A reference to the NiTextKeyExtraData object to use.
	 * \sa NiTextKeyExtraData
	 */
	NIFLIB_API void SetTextKey( NiTextKeyExtraData * txt_key );

	/*! 
	 * Attatches a controler to this KF file for a KF file of version 10.2.0.0 or below.  Versions above this use interpolators.
	 * \param[in] obj A reference to the new NiTimeController to attach.
	 * \sa NiControllerSequence::ClearChildren, NiControllerSequence::AddInterpolator
	 */
	NIFLIB_API void AddController( NiTimeController * obj );

	/*! 
	* Attaches a controler to this KF file for a KF file of version 10.2.0.0 or below.  Versions above this use interpolators.
	* \param[in] obj A reference to the new NiTimeController to attach.
	* \sa NiControllerSequence::ClearChildren, NiControllerSequence::AddInterpolator
	*/
	NIFLIB_API void AddController( string const & targetName, NiTimeController * obj );

	/*!
	 * Attaches an interpolator to this KF file for a KF file of version greater than 10.2.0.0.  Versions below this use controllers.
	 * \param[in] obj A reference to the new controller which has an interpolator to attach.
	 * \param[in] priority Used only in Oblivion to set the priority of one controller over another when the two are merged.
	 * \sa NiControllerSequence::ClearChildren, NiControllerSequence::AddController
	 */
	NIFLIB_API void AddInterpolator( NiSingleInterpController * obj, byte priority = 0 );

	/*!
	 * Attaches an interpolator to this KF file for a KF file of version greater than 10.2.0.0.  Versions below this use controllers.
	 * \param[in] obj A reference to the new controller which has an interpolator to attach.
	 * \param[in] priority Used only in Oblivion to set the priority of one controller over another when the two are merged.
	 * \param[in] include_string_pallete Indicates if the resulting ControllerLinks will hold reference to the NiStringPallete in the NiControllerSequence
	 * \sa NiControllerSequence::ClearChildren, NiControllerSequence::AddController
	 */
	NIFLIB_API void AddInterpolator( NiSingleInterpController * obj, byte priority , bool include_string_pallete );

	/*!
	 * Attaches a generic interpolator to this KF file for a KF file of version greater than 10.2.0.0.  Versions below this use controllers.
	 * \param[in] interpolator A reference to the new interpolator to insert into the controllersequence
	 * \param[in] target The target object that the controller which held the interpolator would act on
	 * \param[in] controller_type_name The name of the type of the controller that held the interpolator
	 * \param[in] priority Used only in Oblivion to set the priority of one controller over another when the two are merged.
	 * \param[in] include_string_pallete Indicates if the resulting ControllerLinks will hold reference to the NiStringPallete in the NiControllerSequence
	 * \sa NiControllerSequence::ClearChildren, NiControllerSequence::AddController
	 */
	NIFLIB_API void AddGenericInterpolator( NiInterpolator * interpolator, NiObjectNET* target, string controller_type_name, byte priority = 0, bool include_string_pallete  = true);

	/*! 
	 * Removes all controllers and interpolators from this Kf file root object.
	 * \sa NiControllerSequence::AddController, NiControllerSequence::AddInterpolator
	 */
	NIFLIB_API void ClearControllerData();

	/*!
	 * Retrieves the data for the controllers or interpolators which are attached to this controller sequence.
	 * \return A vector containing the data for all controllers.
	 * \sa NiControllerSequence::AddController, NiControllerSequence::AddInterpolator, NiControllerSequence::SetContollerData
	 */
	NIFLIB_API vector<ControllerLink> GetControllerData() const;

	/*!
	* Retrieves the data for the controllers or interpolators which are attached to this controller sequence.
	* \return A vector containing the data for all controllers.
	* \sa NiControllerSequence::AddController, NiControllerSequence::AddInterpolator, NiControllerSequence::GetContollerData
	*/
	NIFLIB_API void SetControllerData(const vector<ControllerLink>& value);

	/*!
	 * Retrieves the text keys, which are tags associated with keyframe times that mark the start and stop of each sequence, among other things such as the triggering of sound effects.
	 * \return The text key data.
	 */
	NIFLIB_API Ref<NiTextKeyExtraData> GetTextKeyExtraData() const;

	/*!
	 * Gets the animation frequency.
	 * \return The animation frequency.
	 */
	NIFLIB_API float GetFrequency() const;

	/*!
	 * Sets the animation frequency.
	 * \param[in] value The animation frequency.
	 */
	NIFLIB_API void SetFrequency( float value );

	/*!
	 * Gets the controller sequence start time.
	 * \return The controller sequence start time.
	 */
	NIFLIB_API float GetStartTime() const;

	/*!
	 * Sets the controller sequence start time.
	 * \param[in] value The controller sequence start time.
	 */
	NIFLIB_API void SetStartTime( float value );

	/*!
	 * Gets the controller sequence stop time.
	 * \return The conroller sequence stop time.
	 */
	NIFLIB_API float GetStopTime() const;

	/*!
	 * Sets the controller sequence stop time.
	 * \param[in] value The conroller sequence stop time.
	 */
	NIFLIB_API void SetStopTime( float value );

	/*!
	 * Gets the controller cyle behavior. Can be loop, reverse, or clamp.
	 * \return The animation cycle behavior.
	 */
	NIFLIB_API CycleType GetCycleType() const;

	/*!
	 * Sets the controller cyle behavior. Can be loop, reverse, or clamp.
	 * \param[in] n The new animation cycle behavior.
	 */
	NIFLIB_API void SetCycleType( CycleType n );

	/*! 
	 * Gets the  number of controllers.
	 * \return Number of total controllers in this sequence
	 * \sa GetControllerData
	 */
	NIFLIB_API int GetNumControllers() const;

	/*! 
	 * Gets controller priority.  Oblivion Specific.
	 * \return Priority of a specific controller.
	 * \param[in] controller The index of the controller to get the priority for.
	 * \sa GetControllerData, GetNumControllers, SetControllerPriority
	 */
	NIFLIB_API int GetControllerPriority( int controller ) const;

	/*! 
	 * Sets controller priority.  Oblivion Specific.
	 * \param[in] controller The index of the controller to set the priority for.
	 * \param[in] priority The amount of priority the controller should have.
	 * \sa GetControllerData, GetNumControllers, GetControllerPriority
	 */
	NIFLIB_API void SetControllerPriority( int controller, int priority );

	/*!
	 * Gets weight/priority of animation?
	 * \return The weight/priority of the animation?
	 */
	NIFLIB_API float GetWeight() const;

	/*!
	 * Sets weight/priority of animation?
	 * \param[in] value The weight/priority of the animation?
	 */
	NIFLIB_API void SetWeight( float value );

	/*!
	 * Gets the name of target node this controller acts on.
	 * \return The target node name.
	 */
	NIFLIB_API string GetTargetName() const;

	/*!
	 * Sets the name of target node this controller acts on.
	 * \param[in] value The target node name.
	 */
	NIFLIB_API void SetTargetName( const string & value );

	/*!
	* Gets the string palette for this controller.
	* \return The string palette.
	*/
	NIFLIB_API Ref<NiStringPalette > GetStringPalette() const;

	/*!
	* Sets the string palette for this controller.
	* \param[in] value The string palette.
	*/
	NIFLIB_API void SetStringPalette( const Ref<NiStringPalette >& value );

protected:
   friend class NiControllerManager;
   NiControllerManager * GetParent() const;
   void SetParent( NiControllerManager * parent );

	//--END CUSTOM CODE--//
protected:
	/*! Weight/priority of animation? */
	float weight;
	/*!
	 * Link to NiTextKeyExtraData. Replaces the other Text Keys field in versions
	 * 10.1.0.106 and up.
	 */
	Ref<NiTextKeyExtraData > textKeys;
	/*! Anim cycle type? Is part of "Flags" in other objects? */
	CycleType cycleType;
	/*! Unknown. */
	unsigned int unknownInt0;
	/*! The animation frequency. */
	float frequency;
	/*! The controller sequence start time? */
	float startTime;
	/*! Unknown. */
	float unknownFloat2;
	/*! The controller sequence stop time? */
	float stopTime;
	/*! Unknown. */
	byte unknownByte;
	/*! Refers to NiControllerManager which references this object, if any. */
	NiControllerManager * manager;
	/*! Name of target node Controller acts on. */
	IndexString targetName;
	/*! Refers to NiStringPalette. */
	Ref<NiStringPalette > stringPalette;
	/*! Unknown */
	Ref<BSAnimNotes > animNotes;
	/*! Unknown */
	short unknownShort1;
	/*!
	 * Unknown, found in some Lazeska and Krazy Rain .KFs (seems to be 64 when
	 * present).
	 */
	unsigned int unknownInt3;
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
