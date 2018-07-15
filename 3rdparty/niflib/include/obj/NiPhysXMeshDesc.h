/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIPHYSXMESHDESC_H_
#define _NIPHYSXMESHDESC_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "NiObject.h"
namespace Niflib {

class NiPhysXMeshDesc;
typedef Ref<NiPhysXMeshDesc> NiPhysXMeshDescRef;

/*! Unknown PhysX node. */
class NiPhysXMeshDesc : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiPhysXMeshDesc();

	/*! Destructor */
	NIFLIB_API virtual ~NiPhysXMeshDesc();

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
	/*! Unknown */
	short unknownShort1;
	/*! Unknown */
	float unknownFloat1;
	/*! Unknown */
	short unknownShort2;
	/*! NXS */
	array<3,byte > unknownBytes0;
	/*! Unknown */
	byte unknownByte1;
	/*! MESH */
	array<4,byte > unknownBytes1;
	/*! Unknown */
	array<8,byte > unknownBytes2;
	/*! Unknown */
	float unknownFloat2;
	/*! Unknown */
	int unknownInt1;
	/*! Unknown */
	int unknownInt2;
	/*! Number of mesh vertices */
	mutable int numVertices;
	/*! Unknown */
	int unknownInt4;
	/*! Vertices */
	vector<Vector3 > vertices;
	/*! Unknown */
	array<982,byte > unknownBytes3;
	/*! Unknown */
	array<368,short > unknownShorts1;
	/*! Unknown */
	array<3328,unsigned int > unknownInts1;
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
