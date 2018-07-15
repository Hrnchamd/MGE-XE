/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIOBJECTNET_H_
#define _NIOBJECTNET_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiObject.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiExtraData;
class NiTimeController;
class NiObjectNET;
typedef Ref<NiObjectNET> NiObjectNETRef;

/*! An object that can be controlled by a controller. */
class NiObjectNET : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiObjectNET();

	/*! Destructor */
	NIFLIB_API virtual ~NiObjectNET();

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

	NIFLIB_API string GetName();
	NIFLIB_API void SetName( const string & new_name );

	/*!
	 * Formats a human readable string that includes the type of the object
	 * \return A string in the form:  address(type) {name}
	 */
	NIFLIB_API virtual string GetIDString() const;

	/*! 
	 * Adds an extra data object to this one.  The way this data is stored changed after version 10.0.1.0, so the version
	 * can optionally be included to specify the old storage method.
	 * \param[in] obj The NiExtraData object to attach to this object.
	 * \param[in] version The way the extra data is arranged internally varies with the NIF version, so if a file is to be written, it is best to pass the intended version.  The default is 10.0.1.0, which specifies the newer behavior.
	 */
	NIFLIB_API void AddExtraData( NiExtraData * obj, unsigned version = VER_10_0_1_0 );

	/*! 
	 * Removes an extra data object to this one.
	 * \param[in] obj The NiExtraData object to remove from this object.
	 */
	NIFLIB_API void RemoveExtraData( NiExtraData * obj );

	/*! 
	 * Changes the internal storage method of the extra data in preparation for writing to a file.  This is only necessary if the
	 * extra data was added in one way and needs to be output in another.  This would happen if extra data was loaded from an old file and needed to be written to a file with a newer version.
	 * \param[in] version Specifies the NIF version that the internal data should be arranged for.
	 */
	NIFLIB_API void ShiftExtraData( unsigned int version = VER_10_0_1_0 );

	/*!
	 * Removes all extra data from this object.
	 */
	NIFLIB_API void ClearExtraData();

	/*!
	 * Returns a list of references to all the extra data referenced by this object.
	 * \return All the extra data objects referenced by this one.
	 */
	NIFLIB_API list< Ref<NiExtraData> > GetExtraData() const;

	/*!
	 * Used to determine whether this object is animated.  In other words, whether it has any controllers.
	 * \return True if the object has controllers, false otherwise.
	 */
	NIFLIB_API bool IsAnimated();

	/*!
	 * Adds a controller to this object.  Controllers allow various properties to be animated over time.
	 * \param[in] obj The controller to add.
	 */
	NIFLIB_API void AddController( NiTimeController * obj );

	/*!
	 * Removes a controller from this object.  Controllers allow various properties to be animated over time.
	 * \param[in] obj The controller to remove.
	 */
	NIFLIB_API void RemoveController( NiTimeController * obj );

	/*!
	 * Removes all controllers from this object.  This will remove any animation from it.
	 */
	NIFLIB_API void ClearControllers();

	/*!
	 * Gets a list of all controllers affecting this object.
	 * \return All the controllers affecting this object.
	 */
	NIFLIB_API list< Ref<NiTimeController> > GetControllers() const;

	/*!
	* Gets the skyrim shader type
	* \return The skyrim shader flag value
	*/
	NIFLIB_API BSLightingShaderPropertyShaderType GetSkyrimShaderType() const;

	/*!
	* Set the skyrim shader type
	* \param[in] The new skyrim shader value
	*/
	NIFLIB_API void SetSkyrimShaderType(BSLightingShaderPropertyShaderType value);

	//--END CUSTOM CODE--//
protected:
	/*! Configures the main shader path */
	BSLightingShaderPropertyShaderType skyrimShaderType;
	/*! Name of this controllable object, used to refer to the object in .kf files. */
	IndexString name;
	/*! Extra data for pre-3.0 versions. */
	bool hasOldExtraData;
	/*! (=NiStringExtraData) */
	IndexString oldExtraPropName;
	/*! ref */
	unsigned int oldExtraInternalId;
	/*! Extra string data. */
	IndexString oldExtraString;
	/*! Always 0. */
	byte unknownByte;
	/*! Extra data object index. (The first in a chain) */
	Ref<NiExtraData > extraData;
	/*! The number of Extra Data objects referenced through the list. */
	mutable unsigned int numExtraDataList;
	/*! List of extra data indices. */
	vector<Ref<NiExtraData > > extraDataList;
	/*! Controller object index. (The first in a chain) */
	Ref<NiTimeController > controller;
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
