/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIPARTICLESYSTEMCONTROLLER_H_
#define _NIPARTICLESYSTEMCONTROLLER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiTimeController.h"

// Include structures
#include "../Ref.h"
#include "../gen/Particle.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiObject;
class NiParticleModifier;
class NiColorData;
class NiParticleSystemController;
typedef Ref<NiParticleSystemController> NiParticleSystemControllerRef;

/*! A generic particle system time controller object. */
class NiParticleSystemController : public NiTimeController {
public:
	/*! Constructor */
	NIFLIB_API NiParticleSystemController();

	/*! Destructor */
	NIFLIB_API virtual ~NiParticleSystemController();

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
	/*! Particle speed in old files */
	unsigned int oldSpeed;
	/*! Particle speed */
	float speed;
	/*! Particle random speed modifier */
	float speedRandom;
	/*!
	 * vertical emit direction [radians]
	 *             0.0 : up
	 *             1.6 : horizontal
	 *             3.1416 : down
	 */
	float verticalDirection;
	/*! emitter's vertical opening angle [radians] */
	float verticalAngle;
	/*! horizontal emit direction */
	float horizontalDirection;
	/*! emitter's horizontal opening angle */
	float horizontalAngle;
	/*! Unknown. */
	Vector3 unknownNormal_;
	/*! Unknown. */
	Color4 unknownColor_;
	/*! Particle size */
	float size;
	/*! Particle emit start time */
	float emitStartTime;
	/*! Particle emit stop time */
	float emitStopTime;
	/*! Unknown byte, (=0) */
	byte unknownByte;
	/*! Particle emission rate in old files */
	unsigned int oldEmitRate;
	/*! Particle emission rate (particles per second) */
	float emitRate;
	/*! Particle lifetime */
	float lifetime;
	/*! Particle lifetime random modifier */
	float lifetimeRandom;
	/*! Bit 0: Emit Rate toggle bit (0 = auto adjust, 1 = use Emit Rate value) */
	unsigned short emitFlags;
	/*! Particle random start translation vector */
	Vector3 startRandom;
	/*!
	 * This index targets the particle emitter object (TODO: find out what type of
	 * object this refers to).
	 */
	NiObject * emitter;
	/*! ? short=0 ? */
	unsigned short unknownShort2_;
	/*! ? float=1.0 ? */
	float unknownFloat13_;
	/*! ? int=1 ? */
	unsigned int unknownInt1_;
	/*! ? int=0 ? */
	unsigned int unknownInt2_;
	/*! ? short=0 ? */
	unsigned short unknownShort3_;
	/*! Particle velocity */
	Vector3 particleVelocity;
	/*! Unknown */
	Vector3 particleUnknownVector;
	/*! The particle's age. */
	float particleLifetime;
	/*! Unknown. */
	Ref<NiObject > particleLink;
	/*! Timestamp of the last update. */
	unsigned int particleTimestamp;
	/*! Unknown short */
	mutable unsigned short particleUnknownShort;
	/*! Particle/vertex index matches array index */
	unsigned short particleVertexId;
	/*! Size of the following array. (Maximum number of simultaneous active particles) */
	mutable unsigned short numParticles;
	/*!
	 * Number of valid entries in the following array. (Number of active particles at
	 * the time the system was saved)
	 */
	unsigned short numValid;
	/*! Individual particle modifiers? */
	vector<Particle > particles;
	/*! unknown int (=0xffffffff) */
	Ref<NiObject > unknownLink;
	/*!
	 * Link to some optional particle modifiers (NiGravity, NiParticleGrowFade,
	 * NiParticleBomb, ...)
	 */
	Ref<NiParticleModifier > particleExtra;
	/*! Unknown int (=0xffffffff) */
	Ref<NiObject > unknownLink2;
	/*! Trailing null byte */
	byte trailer;
	/*! Unknown. */
	Ref<NiColorData > colorData;
	/*! Unknown. */
	float unknownFloat1;
	/*! Unknown. */
	vector<float > unknownFloats2;
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
