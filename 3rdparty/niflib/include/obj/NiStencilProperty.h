/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NISTENCILPROPERTY_H_
#define _NISTENCILPROPERTY_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiProperty.h"
namespace Niflib {

class NiStencilProperty;
typedef Ref<NiStencilProperty> NiStencilPropertyRef;

/*! Allows control of stencil testing. */
class NiStencilProperty : public NiProperty {
public:
	/*! Constructor */
	NIFLIB_API NiStencilProperty();

	/*! Destructor */
	NIFLIB_API virtual ~NiStencilProperty();

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
	 * Can be used to get the data stored in the flags field for this object.  It is usually better to call more specific flag-toggle functions if they are availiable.
	 * \return The flag data.
	 */
	NIFLIB_API unsigned short GetFlags() const;

	/*!
	 * Can be used to set the data stored in the flags field for this object.  It is usually better to call more specific flag-toggle functions if they are availiable.
	 * \param[in] value The new flag data.  Will overwrite any existing flag data.
	 */
	NIFLIB_API void SetFlags(unsigned short value);

	/*!
	 * Used to get the current stencil state buffer state.  This determines whether or not the stencil buffer is being used.
	 * \return True if the stencil buffer is enabled, false otherwise.
	 */
	NIFLIB_API bool GetStencilState() const;

	/*!
	 * Used to set the stencil state buffer state.  This determines whether or not the stencil buffer is being used.
	 * \param[in] value True to enable the stencil, false to disable it.
	 */
	NIFLIB_API void SetStencilState(bool value);

	/*!
	 * Used to get the current stencil buffer comparison function.  This function determines whether a particular pixel will be drawn based on the contents of the stencil buffer at that location.
	 * \return The current stencil buffer comparison function.
	 */
	NIFLIB_API StencilCompareMode GetStencilFunction() const;

	/*!
	 * Used to set the current stencil buffer comparison function.  This function determines whether a particular pixel will be drawn based on the contents of the stencil buffer at that location.
	 * \param[in] value The new stencil buffer comparison function.
	 */
	NIFLIB_API void SetStencilFunction( StencilCompareMode value );

	/*!
	 * Used to get the current reference value used in the stencil test.  This is the value that the stencil function compares against to determine whether a pixel is drawn.
	 * \return The current stencil reference value.
	 */
	NIFLIB_API unsigned int GetStencilRef() const;

	/*!
	 * Used to set the current reference value used in the stencil test.  This is the value that the stencil function compares against to determine whether a pixel is drawn.
	 * \param[in] value The new stencil reference value.
	 */
	NIFLIB_API void SetStencilRef(unsigned int value);

	/*!
	 * Used to get the current bit mask used in the stencil test.  The reference value and the stored stencil value are both bitwise ANDed with this mask before being compared.  The default is 0xFFFFFFFF.
	 * \return The current stencil test bit mask.
	 */
	NIFLIB_API unsigned int GetStencilMask() const;

	/*!
	 * Used to set the bit mask used in the stencil test.  The reference value and the stored stencil value are both bitwise ANDed with this mask before being compared.  The default is 0xFFFFFFFF.
	 * \param[in] value The new stencil test bit mask.
	 */
	NIFLIB_API void SetStencilMask(unsigned int value);

	/*!
	 * Used to get the current action that occurs if the stencil test fails (evaluates to false).  This involves whether the stencil buffer will be altered and how.
	 * \return The current action that occurs if the stencil test fails.
	 */
	NIFLIB_API StencilAction GetFailAction() const;

	/*!
	 * Used to set the action that will occur if the stencil test fails (evaluates to false).  This involves whether the stencil buffer will be altered and how.
	 * \param[in] value The new action that occur if the stencil test fails.
	 */
	NIFLIB_API void SetFailAction( StencilAction value );

	/*!
	 * Used to get the current action that occurs if the depth buffer test fails (evaluates to false).  This involves whether the stencil buffer will be altered and how.
	 * \return The current action that occurs if the depth buffer test fails.
	 */
	NIFLIB_API StencilAction GetZFailAction() const;

	/*!
	 * Used to set the action that will occur if the depth buffer (Z-buffer) fails (evaluates to false).  This involves whether the stencil buffer will be altered and how.
	 * \param[in] value The new action that occur if the depth buffer fails.
	 */
	NIFLIB_API void SetZFailAction( StencilAction  value );

	/*!
	 * Used to get the current action that occurs if the depth buffer (Z-buffer) test passes (evaluate to true).  This involves whether the stencil buffer will be altered and how.
	 * \return The current action that occurs if the depth buffer test passes.
	 */
	NIFLIB_API StencilAction GetPassAction() const;

	/*!
	 * Used to set the action that will occur if the depth buffer (Z-buffer) test passes (evaluate to true).  This involves whether the stencil buffer will be altered and how.
	 * \param[in] value The new action that occur if the depth buffer test passes.
	 */
	NIFLIB_API void SetPassAction( StencilAction value );

	/*!
	 * Used to determine whether the front, back, or both sides of triangles will be drawn.   This isn't related to the stencil buffer, but happens to be included in this propery, probably for conveniance.
	 * \return The current face drawing mode.
	 */
	NIFLIB_API FaceDrawMode GetFaceDrawMode() const;

	/*!
	 * Sets whether the front, back, or both sides of triangles will be drawn.   This isn't related to the stencil buffer, but happens to be included in this propery, probably for conveniance.
	 * \param[in] value The new face drawing mode.
	 */
	NIFLIB_API void SetFaceDrawMode( FaceDrawMode value );

	//--END CUSTOM CODE--//
protected:
	/*! Property flags. */
	unsigned short flags;
	/*! Enables or disables the stencil test. */
	byte stencilEnabled;
	/*! Selects the compare mode function (see: glStencilFunc). */
	StencilCompareMode stencilFunction;
	/*! Unknown.  Default is 0. */
	unsigned int stencilRef;
	/*! A bit mask. The default is 0xffffffff. */
	unsigned int stencilMask;
	/*! Unknown. */
	StencilAction failAction;
	/*! Unknown. */
	StencilAction zFailAction;
	/*! Unknown. */
	StencilAction passAction;
	/*! Used to enabled double sided faces. Default is 3 (DRAW_BOTH). */
	FaceDrawMode drawMode;
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
