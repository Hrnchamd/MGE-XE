/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIPARTICLESDATA_H_
#define _NIPARTICLESDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiGeometryData.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiObject;
class NiParticlesData;
typedef Ref<NiParticlesData> NiParticlesDataRef;

/*! Generic rotating particles data object. */
class NiParticlesData : public NiGeometryData {
public:
	/*! Constructor */
	NIFLIB_API NiParticlesData();

	/*! Destructor */
	NIFLIB_API virtual ~NiParticlesData();

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
	/*! The maximum number of particles (matches the number of vertices). */
	unsigned short numParticles;
	/*! The particles' size. */
	float particleRadius;
	/*! Is the particle size array present? */
	bool hasRadii;
	/*! The individual particel sizes. */
	vector<float > radii;
	/*!
	 * The number of active particles at the time the system was saved. This is also
	 * the number of valid entries in the following arrays.
	 */
	unsigned short numActive;
	/*! Is the particle size array present? */
	bool hasSizes;
	/*! The individual particel sizes. */
	vector<float > sizes;
	/*! Is the particle rotation array present? */
	bool hasRotations;
	/*! The individual particle rotations. */
	vector<Quaternion > rotations;
	/*! Unknown, probably a boolean. */
	byte unknownByte1;
	/*! Unknown */
	Ref<NiObject > unknownLink;
	/*! Are the angles of rotation present? */
	bool hasRotationAngles;
	/*! Angles of rotation */
	vector<float > rotationAngles;
	/*! Are axes of rotation present? */
	bool hasRotationAxes;
	/*! Unknown */
	vector<Vector3 > rotationAxes;
	/*! if value is no, a single image rendered */
	bool hasUvQuadrants;
	/*!
	 * 2,4,8,16,32,64 are potential values. If "Has" was no then this should be 256,
	 * which represents a 16x16 framed image, which is invalid
	 */
	mutable byte numUvQuadrants;
	/*! Unknown. */
	vector<Vector4 > uvQuadrants;
	/*! Unknown */
	byte unknownByte2;
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
