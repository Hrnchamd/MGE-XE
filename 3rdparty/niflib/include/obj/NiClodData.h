/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NICLODDATA_H_
#define _NICLODDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiTriBasedGeomData.h"
namespace Niflib {

class NiClodData;
typedef Ref<NiClodData> NiClodDataRef;

/*!
 * Holds mesh data for continuous level of detail shapes.
 *         Pesumably a progressive mesh with triangles specified by edge splits.
 *         Seems to be specific to Freedom Force.
 *         The structure of this is uncertain and highly experimental at this
 * point.
 *         No file with this data can currently be read properly.
 */
class NiClodData : public NiTriBasedGeomData {
public:
	/*! Constructor */
	NIFLIB_API NiClodData();

	/*! Destructor */
	NIFLIB_API virtual ~NiClodData();

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
	unsigned short unknownShorts;
	/*! Unknown. */
	mutable unsigned short unknownCount1;
	/*! Unknown. */
	mutable unsigned short unknownCount2;
	/*! Unknown. */
	mutable unsigned short unknownCount3;
	/*! Unknown. */
	float unknownFloat;
	/*! Unknown. */
	unsigned short unknownShort;
	/*! Unknown. */
	vector< array<6,unsigned short > > unknownClodShorts1;
	/*! Unknown. */
	vector<unsigned short > unknownClodShorts2;
	/*! Unknown. */
	vector< array<6,unsigned short > > unknownClodShorts3;
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
