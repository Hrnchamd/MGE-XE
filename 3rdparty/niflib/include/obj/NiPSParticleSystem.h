/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIPSPARTICLESYSTEM_H_
#define _NIPSPARTICLESYSTEM_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "NiAVObject.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiObject;
class NiPSParticleSystem;
typedef Ref<NiPSParticleSystem> NiPSParticleSystemRef;

/*!  */
class NiPSParticleSystem : public NiAVObject {
public:
	/*! Constructor */
	NIFLIB_API NiPSParticleSystem();

	/*! Destructor */
	NIFLIB_API virtual ~NiPSParticleSystem();

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
	/*! 0? */
	mutable int unknown3;
	/*! Unknown. */
	vector<int > unknown38;
	/*! -1? */
	int unknown4;
	/*! 0? */
	int unknown5;
	/*! Unknown. */
	vector<int > unknown39;
	/*! 256? */
	int unknown6;
	/*! 0? */
	int unknown7;
	/*! 0? */
	int unknown8;
	/*! 0? */
	int unknown9;
	/*! 0? */
	float unknown10;
	/*! 0? */
	int unknown11;
	/*! Counter? */
	int unknown12;
	/*! Simulator? */
	Ref<NiObject > simulator;
	/*! Generator? */
	Ref<NiObject > generator;
	/*! Simulator? */
	int unknown15;
	/*! Updater? */
	int unknown16;
	/*! 1? */
	int unknown17;
	/*! Emitter? */
	Ref<NiObject > emitter;
	/*! 0? */
	int unknown19;
	/*! Spawner? */
	int unknown20;
	/*! Unknown */
	int unknown21;
	/*! Unknown */
	array<4,byte > unknown22;
	/*! Unknown. */
	int unknown27;
	/*! Unknown. */
	int unknown28;
	/*! Unknown. */
	int unknown29;
	/*! Unknown. */
	int unknown30;
	/*! Unknown. */
	int unknown31;
	/*! Unknown. */
	int unknown32;
	/*! Unknown. */
	int unknown33;
	/*! Unknown. */
	int unknown34;
	/*! Unknown. */
	byte unknown35;
	/*! -1? */
	int unknown36;
	/*! Unknown. */
	short unknown37;
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
