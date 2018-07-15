/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIPSMESHEMITTER_H_
#define _NIPSMESHEMITTER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "NiObject.h"
namespace Niflib {

class NiPSMeshEmitter;
typedef Ref<NiPSMeshEmitter> NiPSMeshEmitterRef;

/*!  */
class NiPSMeshEmitter : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiPSMeshEmitter();

	/*! Destructor */
	NIFLIB_API virtual ~NiPSMeshEmitter();

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
	/*! Unknown. */
	IndexString name;
	/*! Unknown. */
	int unknown1;
	/*! Unknown. */
	int unknown2;
	/*! Unknown. */
	int unknown3;
	/*! Unknown. */
	int unknown27;
	/*! Unknown. */
	float unknown4;
	/*! Unknown. */
	float unknown5;
	/*! Unknown. */
	float unknown6;
	/*! Unknown. */
	float unknown28;
	/*! Unknown. */
	int unknown7;
	/*! Unknown. */
	float unknown8;
	/*! Unknown. */
	float unknown9;
	/*! Unknown. */
	float unknown10;
	/*! Unknown. */
	float unknown11;
	/*! Unknown. */
	float unknown12;
	/*! Unknown. */
	int unknown13;
	/*! Unknown. */
	float unknown14;
	/*! Unknown. */
	float unknown15;
	/*! Unknown. */
	float unknown16;
	/*! Unknown. */
	int unknown17;
	/*! Unknown. */
	int unknown18;
	/*! Unknown. */
	short unknown19;
	/*! Unknown. */
	int unknown20;
	/*! Unknown. */
	int unknown21;
	/*! Unknown. */
	float unknown22;
	/*! Unknown. */
	int unknown23;
	/*! Unknown. */
	int unknown24;
	/*! Unknown. */
	int unknown25;
	/*! Unknown. */
	int unknown26;
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
