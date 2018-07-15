/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIALPHAPROPERTY_H_
#define _NIALPHAPROPERTY_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiProperty.h"
namespace Niflib {

class NiAlphaProperty;
typedef Ref<NiAlphaProperty> NiAlphaPropertyRef;

/*! Transparency. Flags 0x00ED. */
class NiAlphaProperty : public NiProperty {
public:
	/*! Constructor */
	NIFLIB_API NiAlphaProperty();

	/*! Destructor */
	NIFLIB_API virtual ~NiAlphaProperty();

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

	/*! Used to specify the source and destination blending functions.  The function of each value is equivalent to the OpenGL blending function of similar name. */
	enum BlendFunc {
		BF_ONE = 0, 
		BF_ZERO = 1,
		BF_SRC_COLOR = 2,
		BF_ONE_MINUS_SRC_COLOR = 3,
		BF_DST_COLOR = 4,
		BF_ONE_MINUS_DST_COLOR = 5,
		BF_SRC_ALPHA = 6,
		BF_ONE_MINUS_SRC_ALPHA = 7,
		BF_DST_ALPHA = 8,
		BF_ONE_MINUS_DST_ALPHA = 9,
		BF_SRC_ALPHA_SATURATE = 10
	};

	/*! Used to set the alpha test function.  The function of each value is equivalent to the OpenGL test function of similar name. */
	enum TestFunc {
		TF_ALWAYS = 0,
		TF_LESS = 1,
		TF_EQUAL = 2,
		TF_LEQUAL = 3,
		TF_GREATER = 4,
		TF_NOTEQUAL = 5,
		TF_GEQUAL = 6,
		TF_NEVER = 7
	};

	/*!
	 * Used to get the current alpha blending state.  If alpha blending is turned on, the blending functions will be used to mix the values based on the alpha component of each pixel in the texture.
	 * \return True if alpha blending is enabled, false otherwise.
	 */
	NIFLIB_API bool GetBlendState() const;

	/*!
	 * Used to set the alpha blending state.  If alpha blending is turned on, the blending functions will be used to mix the values based on the alpha component of each pixel in the texture.
	 * \param[in] value True to enable alpha blending, false to disable it.
	 */
	NIFLIB_API void SetBlendState(bool value);


	/*!
	 * Used to get the current source blend function which determines how alpha blending occurs if it is enabled.
	 * \return The current soucre blend function.
	 */
	NIFLIB_API BlendFunc GetSourceBlendFunc() const;

	/*!
	 * Used to set the source blend function which determines how alpha blending occurs if it is enabled.
	 * \param[in] value The new soucre blend function.
	 */
	NIFLIB_API void SetSourceBlendFunc(BlendFunc value);

	/*!
	 * Used to get the current destination blend function which determines how alpha blending occurs if it is enabled.
	 * \return The current destination blend function.
	 */
	NIFLIB_API BlendFunc GetDestBlendFunc() const;

	/*!
	 * Used to set the destination blend function which determines how alpha blending occurs if it is enabled.
	 * \param[in] value The new destination blend function.
	 */
	NIFLIB_API void SetDestBlendFunc(BlendFunc value);

	/*!
	 * Used to get the current alpha testing state.  If alpha testing is turned on, the alpha test function will be used to compare each pixel's alpha value to the threshold.  If the function is true, the pixel will be drawn, otherwise it will not.
	 * \return True if alpha testing is enabled, false otherwise.
	 */
	NIFLIB_API bool GetTestState() const;

	/*!
	 * Used to set the alpha testing state.  If alpha testing is turned on, the alpha test function will be used to compare each pixel's alpha value to the threshold.  If the function is true, the pixel will be drawn, otherwise it will not.
	 * \param[in] value True to enable alpha testing, false to disable it.
	 */
	NIFLIB_API void SetTestState(bool value);

	/*!
	 * Used to get the current alpha test function which determines the cut-off alpha value between fully transparent and fully opaque parts of a texture.
	 * \return The current alpha test function.
	 */
	NIFLIB_API TestFunc GetTestFunc() const;

	/*!
	 * Used to set the alpha test function which determines the cut-off alpha value between fully transparent and fully opaque parts of a texture.
	 * \param[in] value The new alpha test function.
	 */
	NIFLIB_API void SetTestFunc(TestFunc value);

	/*!
	 * Used to get the current threshold value that will be used with the alpha test function to determine whether a particular pixel will be drawn.
	 * \return The current alpha test threshold.
	 */
	NIFLIB_API byte GetTestThreshold() const;

	/*!
	 * Used to set the threshold value that will be used with the alpha test function to determine whether a particular pixel will be drawn.
	 * \param[in] n The new alpha test threshold.
	 */
	NIFLIB_API void SetTestThreshold( byte n );

	/*!
	 * Used to get the current triangle sort mode.  If triangle sorting is enabled, the triangles that make up an object will be sorted based on distance, and drawn from farthest away to closest.  This reduces errors when using alpha blending.
	 * \return True if triangles will be sorted, false otherwise.
	 */
	NIFLIB_API bool GetTriangleSortMode() const;

	/*!
	 * Used to set the triangle sort mode.  If triangle sorting is enabled, the triangles that make up an object will be sorted based on distance, and drawn from farthest away to closest.  This reduces errors when using alpha blending.
	 * \param[in] value True to enable triangle sorting, false to disable it.
	 */
	NIFLIB_API void SetTriangleSortMode(bool value);

	/*!
	 * Can be used to get the data stored in the flags field for this object.  It is usually better to call more specific flag-toggle functions if they are availiable.
	 * \return The flag data.
	 */
	NIFLIB_API unsigned short GetFlags() const;

	/*!
	 * Can be used to set the data stored in the flags field for this object.  It is usually better to call more specific flag-toggle functions if they are availiable.
	 * \param[in] n The new flag data.  Will overwrite any existing flag data.
	 */
	NIFLIB_API void SetFlags( unsigned short n );

	//--END CUSTOM CODE--//
protected:
	/*!
	 * Bit 0 : alpha blending enable
	 *             Bits 1-4 : source blend mode
	 *             Bits 5-8 : destination blend mode
	 *             Bit 9 : alpha test enable
	 *             Bit 10-12 : alpha test mode
	 *             Bit 13 : no sorter flag ( disables triangle sorting )
	 * 
	 *             blend modes (glBlendFunc):
	 *             0000 GL_ONE
	 *             0001 GL_ZERO
	 *             0010 GL_SRC_COLOR
	 *             0011 GL_ONE_MINUS_SRC_COLOR
	 *             0100 GL_DST_COLOR
	 *             0101 GL_ONE_MINUS_DST_COLOR
	 *             0110 GL_SRC_ALPHA
	 *             0111 GL_ONE_MINUS_SRC_ALPHA
	 *             1000 GL_DST_ALPHA
	 *             1001 GL_ONE_MINUS_DST_ALPHA
	 *             1010 GL_SRC_ALPHA_SATURATE
	 * 
	 *             test modes (glAlphaFunc):
	 *             000 GL_ALWAYS
	 *             001 GL_LESS
	 *             010 GL_EQUAL
	 *             011 GL_LEQUAL
	 *             100 GL_GREATER
	 *             101 GL_NOTEQUAL
	 *             110 GL_GEQUAL
	 *             111 GL_NEVER
	 */
	unsigned short flags;
	/*! Threshold for alpha testing (see: glAlphaFunc) */
	byte threshold;
	/*! Unknown */
	unsigned short unknownShort1;
	/*! Unknown */
	unsigned int unknownInt2;
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
