/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIPATHCONTROLLER_H_
#define _NIPATHCONTROLLER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiTimeController.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiPosData;
class NiFloatData;
class NiPathController;
typedef Ref<NiPathController> NiPathControllerRef;

/*! Time controller for a path. */
class NiPathController : public NiTimeController {
public:
	/*! Constructor */
	NIFLIB_API NiPathController();

	/*! Destructor */
	NIFLIB_API virtual ~NiPathController();

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

	//TODO:  This class has a lot of unknown data

	/*!
	 * Retrives the float data used by this controller.
	 * \return The float data.
	 */
	NIFLIB_API Ref<NiFloatData> GetFloatData() const;

	/*!
	 * Sets the float data used by this controller.
	 * \param[in] n The new float data.
	 */
	NIFLIB_API void SetFloatData( NiFloatData * n );

	/*!
	 * Retrives the pos data used by this controller.
	 * \return The pos data.
	 */
	NIFLIB_API Ref<NiPosData> GetPosData() const;

	/*!
	 * Sets the pos data used by this controller.
	 * \param[in] n The new pos data.
	 */
	NIFLIB_API void SetPosData( NiPosData * n );

	//--END CUSTOM CODE--//
protected:
	/*! Unknown. */
	unsigned short unknownShort2;
	/*! Unknown, always 1? */
	unsigned int unknownInt1;
	/*! Unknown, often 0? */
	float unknownFloat2;
	/*! Unknown, often 0? */
	float unknownFloat3;
	/*! Unknown, always 0? */
	unsigned short unknownShort;
	/*! Path controller data index (position data). ? */
	Ref<NiPosData > posData;
	/*! Path controller data index (float data). ? */
	Ref<NiFloatData > floatData;
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
