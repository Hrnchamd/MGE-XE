/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NICAMERA_H_
#define _NICAMERA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiAVObject.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiObject;
class NiCamera;
typedef Ref<NiCamera> NiCameraRef;

/*! Camera object. */
class NiCamera : public NiAVObject {
public:
	/*! Constructor */
	NIFLIB_API NiCamera();

	/*! Destructor */
	NIFLIB_API virtual ~NiCamera();

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
	 * Retrieves the frustum left value.
	 * \return The frstum left value.
	 */
	NIFLIB_API float GetFrustumLeft() const;

	/*!
	 * Sets the frustum left value.
	 * \param[in] value The new frstum left value.
	 */
	NIFLIB_API void SetFrustumLeft( float value );

	/*!
	 * Retrieves the frustum right value.
	 * \return The frstum right value.
	 */
	NIFLIB_API float GetFrustumRight() const;

	/*!
	 * Sets the frustum right value.
	 * \param[in] value The new frstum right value.
	 */
	NIFLIB_API void SetFrustumRight( float value );

	/*!
	 * Retrieves the frustum top value.
	 * \return The frstum top value.
	 */
	NIFLIB_API float GetFrustumTop() const;
	NIFLIB_API void SetFrustumTop( float value );

	/*!
	 * Retrieves the frustum bottom value.
	 * \return The frstum bottom value.
	 */
	NIFLIB_API float GetFrustumBottom() const;

	/*!
	 * Sets the frustum top value.
	 * \param[in] value The new frstum top value.
	 */
	NIFLIB_API void SetFrustumBottom( float value );

	/*!
	 * Retrieves the frustum near value.
	 * \return The frstum near value.
	 */
	NIFLIB_API float GetFrustumNear() const;

	/*!
	 * Sets the frustum near value.
	 * \param[in] value The new frstum near value.
	 */
	NIFLIB_API void SetFrustumNear( float value );

	/*!
	 * Retrieves the frustum far value.
	 * \return The frstum far value.
	 */
	NIFLIB_API float GetFrustumFar() const;

	/*!
	 * Sets the frustum far value.
	 * \param[in] value The new frstum far value.
	 */
	NIFLIB_API void SetFrustumFar( float value );

	/*!
	 * Determines whether perspective is used.  Orthographic means no perspective.
	 * \return True if projection is orthographic, false otherwise.
	 */
	NIFLIB_API bool GetUseOrthographicProjection() const;

	/*!
	 * Sets whether perspective is used.  Orthographic means no perspective.
	 * \param[in] value True if projection is to be orthographic, false otherwise.
	 */
	NIFLIB_API void SetUseOrthographicProjection( bool value );

	/*!
	 * Retrieves the viewport left value.
	 * \return The viewport left value.
	 */
	NIFLIB_API float GetViewportLeft() const;

	/*!
	 * Sets the viewport left value.
	 * \param[in] value The new viewport left value.
	 */
	NIFLIB_API void SetViewportLeft( float value );

	/*!
	 * Retrieves the viewport right value.
	 * \return The viewport right value.
	 */
	NIFLIB_API float GetViewportRight() const;

	/*!
	 * Sets the viewport right value.
	 * \param[in] value The new viewport right value.
	 */
	NIFLIB_API void SetViewportRight( float value );

	/*!
	 * Retrieves the viewport top value.
	 * \return The viewport top value.
	 */
	NIFLIB_API float GetViewportTop() const;

	/*!
	 * Sets the viewport top value.
	 * \param[in] value The new viewport top value.
	 */
	NIFLIB_API void SetViewportTop( float value );

	/*!
	 * Retrieves the viewport bottom value.
	 * \return The viewport bottom value.
	 */
	NIFLIB_API float GetViewportBottom() const;

	/*!
	 * Sets the viewport bottom value.
	 * \param[in] value The new viewport bottom value.
	 */
	NIFLIB_API void SetViewportBottom( float value );

	/*!
	 * Retrieves the level of detail adjustment value.
	 * \return The LOD adjustment value.
	 */
	NIFLIB_API float GetLodAdjust() const;

	/*!
	 * Sets the level of detail adjustment value.
	 * \param[in] value The new LOD adjustment value.
	 */
	NIFLIB_API void SetLodAdjust( float value );

	//--END CUSTOM CODE--//
protected:
	/*! Unknown. */
	unsigned short unknownShort;
	/*! Frustrum left. */
	float frustumLeft;
	/*! Frustrum right. */
	float frustumRight;
	/*! Frustrum top. */
	float frustumTop;
	/*! Frustrum bottom. */
	float frustumBottom;
	/*! Frustrum near. */
	float frustumNear;
	/*! Frustrum far. */
	float frustumFar;
	/*! Determines whether perspective is used.  Orthographic means no perspective. */
	bool useOrthographicProjection;
	/*! Viewport left. */
	float viewportLeft;
	/*! Viewport right. */
	float viewportRight;
	/*! Viewport top. */
	float viewportTop;
	/*! Viewport bottom. */
	float viewportBottom;
	/*! Level of detail adjust. */
	float lodAdjust;
	/*! Unknown. */
	Ref<NiObject > unknownLink;
	/*! Unknown.  Changing value crashes viewer. */
	unsigned int unknownInt;
	/*! Unknown.  Changing value crashes viewer. */
	unsigned int unknownInt2;
	/*! Unknown. */
	unsigned int unknownInt3;
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
