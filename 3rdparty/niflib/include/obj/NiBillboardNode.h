/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIBILLBOARDNODE_H_
#define _NIBILLBOARDNODE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiNode.h"
namespace Niflib {

class NiBillboardNode;
typedef Ref<NiBillboardNode> NiBillboardNodeRef;

/*!
 * These nodes will always be rotated to face the camera creating a billboard
 * effect for any attached objects.
 * 
 *         In pre-10.1.0.0 the Flags field is used for BillboardMode.
 *         Bit 0: hidden
 *         Bits 1-2: collision mode
 *         Bit 3: unknown (set in most official meshes)
 *         Bits 5-6: billboard mode
 * 
 *         Collision modes:
 *         00 NONE
 *         01 USE_TRIANGLES
 *         10 USE_OBBS
 *         11 CONTINUE
 * 
 *         Billboard modes:
 *         00 ALWAYS_FACE_CAMERA
 *         01 ROTATE_ABOUT_UP
 *         10 RIGID_FACE_CAMERA
 *         11 ALWAYS_FACE_CENTER
 */
class NiBillboardNode : public NiNode {
public:
	/*! Constructor */
	NIFLIB_API NiBillboardNode();

	/*! Destructor */
	NIFLIB_API virtual ~NiBillboardNode();

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
	 * Retreives the current bilboard mode of this bilboard node.  This determines how it will cause the node to face the camera.
	 * \return The current bilboard mode.
	 */
	NIFLIB_API BillboardMode GetBillboardMode() const;

	/*!
	 * Sets the bilboard mode of this bilboard node.  This determines how it will cause the node to face the camera.
	 * \param[in] value The new bilboard mode.
	 */
	NIFLIB_API void SetBillboardMode( BillboardMode value );

	//--END CUSTOM CODE--//
protected:
	/*! The way the billboard will react to the camera. */
	BillboardMode billboardMode;
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
