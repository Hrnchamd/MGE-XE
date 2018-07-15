/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NITEXTURETRANSFORMCONTROLLER_H_
#define _NITEXTURETRANSFORMCONTROLLER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiFloatInterpController.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiFloatData;
class NiTextureTransformController;
typedef Ref<NiTextureTransformController> NiTextureTransformControllerRef;

/*!
 * Texture transformation controller. The target texture slot should have "Has
 * Texture Transform" enabled.
 */
class NiTextureTransformController : public NiFloatInterpController {
public:
	/*! Constructor */
	NIFLIB_API NiTextureTransformController();

	/*! Destructor */
	NIFLIB_API virtual ~NiTextureTransformController();

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

	/*
	 * Retreives the texture slot that is the target of this texture transform controller.
	 * \return The texture slot that will be animated by this controller.
	 */
	NIFLIB_API TexType GetTargetTextureSlot();

	/*
	 * Retreives the texture slot that will be the target of this texture transform controller.
	 * \param[in] n The new texture slot that will be animated by this controller.
	 */
	NIFLIB_API void SetTargetTextureSlot( TexType n );

	/*
	 * Retreives the type of texture transformation that this controller applies.
	 * \return The way this controller will animate the target texture.
	 */
	NIFLIB_API TexTransform GetTextureTransformType();

	/*
	 * Sets the type of texture transformation that this controller applies.
	 * \param[in] n The new way that this controller will animate the target texture.
	 */
	NIFLIB_API void SetTextureTransformType( TexTransform n );

	/*!
	 * Retrives the float data used by this controller.
	 * \return The float data.
	 */
	NIFLIB_API Ref<NiFloatData> GetData() const;

	/*!
	 * Sets the float data used by this controller.
	 * \param[in] n The new float data.
	 */
	NIFLIB_API void SetData( NiFloatData * n );

	/*!
	 * This function will adjust the times in all the keys in the data objects
	 * referenced by this controller and any of its interpolators such that the
	 * phase will equal 0 and frequency will equal one.  In other words, it
	 * will cause the key times to be in seconds starting from zero.
	 */
	NIFLIB_API virtual void NormalizeKeys();

	//--END CUSTOM CODE--//
protected:
	/*! Unknown. */
	byte unknown2;
	/*! The target texture slot. */
	TexType textureSlot;
	/*! Determines how this controller animates the UV Coordinates. */
	TexTransform operation;
	/*! Link to NiFloatData. */
	Ref<NiFloatData > data;
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
