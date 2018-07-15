/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIPSSIMULATORGENERALSTEP_H_
#define _NIPSSIMULATORGENERALSTEP_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

#include "../gen/ByteColor4.h"

//--END CUSTOM CODE--//

#include "NiPSSimulatorStep.h"
namespace Niflib {

class NiPSSimulatorGeneralStep;
typedef Ref<NiPSSimulatorGeneralStep> NiPSSimulatorGeneralStepRef;

/*!
 * Encapsulates a floodgate kernel that updates particle size, colors, and
 * rotations.
 */
class NiPSSimulatorGeneralStep : public NiPSSimulatorStep {
public:
	/*! Constructor */
	NIFLIB_API NiPSSimulatorGeneralStep();

	/*! Destructor */
	NIFLIB_API virtual ~NiPSSimulatorGeneralStep();

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

	//--END CUSTOM CODE--//
protected:
	/*! The number of size animation keys. */
	mutable byte numSizeKeys;
	/*! The particle size keys. */
	vector<Key<float > > sizeKeys;
	/*! The loop behavior for the size keys. */
	PSLoopBehavior sizeLoopBehavior;
	/*! Unknown. */
	float unknown1;
	/*! Unknown. */
	float unknown2;
	/*! Unknown. */
	float unknown3;
	/*! The number of color animation keys. */
	mutable byte numColorKeys;
	/*! The particle color keys. */
	vector<Key<ByteColor4 > > colorKeys;
	/*! The loop behavior for the color keys. */
	PSLoopBehavior colorLoopBehavior;
	/*! The number of rotatoin animation keys. */
	mutable byte numRotationKeys;
	/*! The particle rotation keys. */
	vector<Key<Quaternion > > rotationKeys;
	/*! The loop behavior for the rotation keys. */
	PSLoopBehavior rotationLoopBehavior;
	/*!
	 * The the amount of time over which a particle's size is ramped from 0.0 to 1.0 in
	 * seconds
	 */
	float growTime;
	/*!
	 * The the amount of time over which a particle's size is ramped from 1.0 to 0.0 in
	 * seconds
	 */
	float shrinkTime;
	/*!
	 * Specifies the particle generation to which the grow effect should be applied.
	 * This is usually generation 0, so that newly created particles will grow.
	 */
	unsigned short growGeneration;
	/*!
	 * Specifies the particle generation to which the shrink effect should be applied.
	 * This is usually the highest supported generation for the particle system, so
	 * that particles will shrink immediately before getting killed.
	 */
	unsigned short shrinkGeneration;
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
