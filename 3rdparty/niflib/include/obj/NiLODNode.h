/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NILODNODE_H_
#define _NILODNODE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiSwitchNode.h"

// Include structures
#include "../gen/LODRange.h"
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiLODData;
class NiLODNode;
typedef Ref<NiLODNode> NiLODNodeRef;

/*!
 * Level of detail selector. Links to different levels of detail of the same model,
 * used to switch a geometry at a specified distance.
 */
class NiLODNode : public NiSwitchNode {
public:
	/*! Constructor */
	NIFLIB_API NiLODNode();

	/*! Destructor */
	NIFLIB_API virtual ~NiLODNode();

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
	 * \return The LOD center.
	 */
	NIFLIB_API Vector3 GetLODCenter() const;

	/*!
	 * Set the point to calculate distance from for switching?
	 * \param[in] value The new LOD center.
	 */
	NIFLIB_API void SetLODCenter( const Vector3 & value );

	/*!
	 * Get the ranges of distance that each level of detail applies in.
	 * \return The LOD levels.
	 */
	NIFLIB_API vector<LODRange > GetLODLevels() const;

	/*!
	 * Set the ranges of distance that each level of detail applies in.
	 * \param[in] value The new LOD levels.
	 */
	NIFLIB_API void SetLODLevels( const vector<LODRange >& value );

	/*!
	 * Get the data object that refers to LOD level information.
	 * \return The LOD level data object or NULL if there is none.
	 */
	NIFLIB_API Ref<NiLODData > GetLODLevelData() const;
	
	/*!
	 * Set the data object that refers to LOD level information.
	 * \param[in] value The new LOD level data object or NULL to clear the current one.
	 */
	NIFLIB_API void SetLODLevelData( Ref<NiLODData > value );

	//--END CUSTOM CODE--//
protected:
	/*! Point to calculate distance from for switching? */
	Vector3 lodCenter;
	/*! Number of levels of detail. */
	mutable unsigned int numLodLevels;
	/*! The ranges of distance that each level of detail applies in. */
	vector<LODRange > lodLevels;
	/*! Refers to LOD level information, either distance or screen size based. */
	Ref<NiLODData > lodLevelData;
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
