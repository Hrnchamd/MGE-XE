/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIPIXELDATA_H_
#define _NIPIXELDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "ATextureRenderData.h"
namespace Niflib {

class NiPixelData;
typedef Ref<NiPixelData> NiPixelDataRef;

/*! A texture. */
class NiPixelData : public ATextureRenderData {
public:
	/*! Constructor */
	NIFLIB_API NiPixelData();

	/*! Destructor */
	NIFLIB_API virtual ~NiPixelData();

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
	 * Retrieves the height of the texture image stored in this object.
	 * \return The height of the texture image stored in this object.
	 * \sa NiPixelData::GetWidth, NiPixelData::GetPixelFormat
	 */
	NIFLIB_API int GetHeight() const;

	/*!
	 * Retrieves the width of the texture image stored in this object.
	 * \return The width of the texture image stored in this object.
	 * \sa NiPixelData::GetHeight, NiPixelData::GetPixelFormat
	 */
	NIFLIB_API int GetWidth() const;

    /*!
	 * Retrieves the pixel format of the texture image stored in this object.
	 * \return The pixel format of the texture image stored in this object.
	 * \sa NiPixelData::GetWidth, NiPixelData::GetHeight
	 */
	NIFLIB_API PixelFormat GetPixelFormat() const;

    /*!
	 * Deletes all image data and sets a new size and format in preparation for new data to be provided.
	 * \param new_width The width of the new texture image.
	 * \param new_height The height of the new texture image.
	 * \param px_fmt The pixel format of the new texture image.
	 * \sa NiPixelData::GetWidth, NiPixelData::GetHeight
	 */
	NIFLIB_API void Reset( int new_width, int new_height, PixelFormat px_fmt );
	
	/*!
	 * Retrieves the the pixels of the texture image stored in this object.  This function does not work on palettized textures.
	 * \return A vector containing the colors of each pixel in the texture image stored in this object, one row after another starting from the bottom of the image.  The width of the image must be used to interpret them correctly.
	 * \sa NiPixelData::SetColors, NiPixelData::GetWidth
	 */
	NIFLIB_API vector<Color4> GetColors() const;

	/*!
	 * Sets the the pixels of the texture image stored in this object and optionally generates mipmaps.  This function does not work for palettized textures.
	 * \param new_pixels A vector containing the colors of each new pixel to be set in the texture image stored in this object, one row after another starting from the botom of the image.
	 * \param generate_mipmaps If true, mipmaps will be generated for the new image and stored in the file.
	 * \sa NiPixelData::GetColors, NiPixelData::GetWidth
	 */
	NIFLIB_API void SetColors( const vector<Color4> & new_pixels, bool generate_mipmaps );

	//--END CUSTOM CODE--//
protected:
	/*! Total number of pixels */
	mutable unsigned int numPixels;
	/*! Unknown */
	mutable unsigned int numFaces;
	/*!
	 * Raw pixel data holding the mipmaps.  Mipmap zero is the full-size texture and
	 * they get smaller by half as the number increases.
	 */
	vector< vector<byte > > pixelData;
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
