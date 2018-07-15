/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIRANGELODDATA_H_
#define _NIRANGELODDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiLODData.h"

// Include structures
#include "../gen/LODRange.h"
namespace Niflib {

class NiRangeLODData;
typedef Ref<NiRangeLODData> NiRangeLODDataRef;

/*! Describes levels of detail based on distance of object from camera. */
class NiRangeLODData : public NiLODData {
public:
	/*! Constructor */
	NIFLIB_API NiRangeLODData();

	/*! Destructor */
	NIFLIB_API virtual ~NiRangeLODData();

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
	 * Get the point to calculate distance from for switching?
	 * \return The point to calculate distance from for switching?
	 */
	NIFLIB_API Vector3 GetLODCenter() const;

	/*!
	 * Set the point to calculate distance from for switching?
	 * \param[in] value The new point to calculate distance from for switching?
	 */
	NIFLIB_API void SetLODCenter( const Vector3 & value );

	/*!
	 * Get the ranges of distance that each level of detail applies in.
	 * \return The ranges of distance that each level of detail applies in.
	 */
	NIFLIB_API vector<LODRange > GetLODLevels() const;

	/*!
	 * Set the ranges of distance that each level of detail applies in.
	 * \param[in] value The new ranges of distance that each level of detail applies in.
	 */
	NIFLIB_API void SetLODLevels( const vector<LODRange> & value );

	//--END CUSTOM CODE--//
protected:
	/*! ? */
	Vector3 lodCenter;
	/*! Number of levels of detail. */
	mutable unsigned int numLodLevels;
	/*! The ranges of distance that each level of detail applies in. */
	vector<LODRange > lodLevels;
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
