/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NITIMECONTROLLER_H_
#define _NITIMECONTROLLER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiObject.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiObjectNET;
class NiTimeController;
typedef Ref<NiTimeController> NiTimeControllerRef;

/*! A generic time controller object. */
class NiTimeController : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiTimeController();

	/*! Destructor */
	NIFLIB_API virtual ~NiTimeController();

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
	 * Returns a reference to the next controller in a linked list.
	 * This function should only be called by NiObjectNET.
	 * \return A reference to the next controller in the linked list.
	 */
	NIFLIB_HIDDEN NiTimeControllerRef GetNextController() const;

	/*! 
	 * Sets the next controller in a linked list.
	 * This function should only be called by NiObjectNET.
	 * \param obj A reference to the object to set as the one after this in the chain.
	 */
	NIFLIB_HIDDEN void SetNextController( const NiTimeControllerRef & obj );

	/*! 
	 * This function should only be called by NiObjectNET.  It sets the target of
	 * this controller when it is attatched to the NiObjectNET class. */
	NIFLIB_HIDDEN void SetTarget( NiObjectNET * new_target );

	/*! 
	 * This function returns the current target NiObjectNET, if any, that this controller
	 * is acting on.
	 * \return A reference to the current target of this controller.
	 */
	NIFLIB_API Ref<NiObjectNET> GetTarget();

	/*!
	 * Can be used to get the data stored in the flags field for this object.  It is usually better to call more specific flag-toggle functions if they are availiable.
	 * \return The flag data.
	 */
	NIFLIB_API unsigned short GetFlags() const;

	/*!
	 * Can be used to set the data stored in the flags field for this object.  It is usually better to call more specific flag-toggle functions if they are availiable.
	 * \param[in] n The new flag data.  Will overwrite any existing flag data.
	 */
	NIFLIB_API void SetFlags( unsigned short n );

	/*!
	 * Gets the frequency value of this controller.  This is used to map the time indices stored in the controller to seconds.  The value is multiplied by the application time to arrive at the controller time, so the default value of 1.0 means that the times in the controller are already in seconds.
	 * \return The frequency.
	 */
	NIFLIB_API float GetFrequency() const;

	/*!
	 * Sets the frequency value of this controller.  This is used to map the time indices stored in the controller to seconds.  The value is multiplied by the application time to arrive at the controller time, so the default value of 1.0 means that the times in the controller are already in seconds.  Calling this function with a new value will not cause any changes to the data stored in the controller.
	 * \param[in] n The new frequency.
	 */
	NIFLIB_API void SetFrequency( float n );

	/*!
	 * Gets the phase value of this controller.  This is used to map the time indices stored in the controller to seconds.  The value is is added to the result of the multiplication of application time by frequency to arrive at the controller time, so the default value of 0.0 means that there is no phase shift in the time indices.
	 * \return The phase.
	 */
	NIFLIB_API float GetPhase() const;

	/*!
	 * Sets the phase value of this controller.  This is used to map the time indices stored in the controller to seconds.  The value is is added to the result of the multiplication of application time by frequency to arrive at the controller time, so the default value of 0.0 means that there is no phase shift in the time indices.  Calling this function with a new value will not cause any changes to the data stored in the controller.
	 * \param[in] n The new phase.
	 */
	NIFLIB_API void SetPhase( float n );

	/*!
	 * This function will adjust the times in all the keys in the data objects
	 * referenced by this controller and any of its interpolators such that the
	 * phase will equal 0 and frequency will equal one.  In other words, it
	 * will cause the key times to be in seconds starting from zero.
	 */
	NIFLIB_API virtual void NormalizeKeys();

	/*!
	 * Retrieves the time index where this controller begins to take affect.  If the animation type is set to wrap or cycle, the animation will not occur only between these time intervals but will be mapped to the right spot between them.  This value is in controller time, i.e. phase and frequency are applied to transform it to application time.
	 * \return The start time for the controller animation.
	 */
	NIFLIB_API float GetStartTime() const;

	/*!
	 * Sets the time index where this controller begins to take affect.  If the animation type is set to wrap or cycle, the animation will not occur only between these time intervals but will be mapped to the right spot between them.  This value is in controller time, i.e. phase and frequency are applied to transform it to application time.
	 * \param[in] n The new start time for the controller animation.
	 */
	NIFLIB_API void SetStartTime( float n );

	/*!
	 * Retrieves the time index where this controller stops taking affect.  If the animation type is set to wrap or cycle, the animation will not occur only between these time intervals but will be mapped to the right spot between them.  This value is in controller time, i.e. phase and frequency are applied to transform it to application time.
	 * \return The end time for the controller animation.
	 */
	NIFLIB_API float GetStopTime() const;

	/*!
	 * Sets the time index where this controller stops taking affect.  If the animation type is set to wrap or cycle, the animation will not occur only between these time intervals but will be mapped to the right spot between them.  This value is in controller time, i.e. phase and frequency are applied to transform it to application time.
	 * \param[in] n The new end time for the controller animation.
	 */
	NIFLIB_API void SetStopTime( float n );

	//--END CUSTOM CODE--//
protected:
	/*! Index of the next controller. */
	Ref<NiTimeController > nextController;
	/*!
	 * Controller flags (usually 0x000C). Probably controls loops.
	 *             Bit 0 : Anim type, 0=APP_TIME 1=APP_INIT
	 *             Bit 1-2 : Cycle type  00=Loop 01=Reverse 10=Loop
	 *             Bit 3 : Active
	 *             Bit 4 : Play backwards
	 */
	unsigned short flags;
	/*! Frequency (is usually 1.0). */
	float frequency;
	/*! Phase (usually 0.0). */
	float phase;
	/*! Controller start time. */
	float startTime;
	/*! Controller stop time. */
	float stopTime;
	/*!
	 * Controller target (object index of the first controllable ancestor of this
	 * object).
	 */
	NiObjectNET * target;
	/*! Unknown integer. */
	unsigned int unknownInteger;
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
