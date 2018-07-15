/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _ATEXTURERENDERDATA_H_
#define _ATEXTURERENDERDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "NiObject.h"

// Include structures
#include "../gen/ChannelData.h"
#include "../Ref.h"
#include "../gen/MipMap.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiPalette;
class ATextureRenderData;
typedef Ref<ATextureRenderData> ATextureRenderDataRef;

/*!  */
class ATextureRenderData : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API ATextureRenderData();

	/*! Destructor */
	NIFLIB_API virtual ~ATextureRenderData();

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
	/*! The format of the pixels in this internally stored image. */
	PixelFormat pixelFormat;
	/*! 0x000000ff (for 24bpp and 32bpp) or 0x00000000 (for 8bpp) */
	unsigned int redMask;
	/*! 0x0000ff00 (for 24bpp and 32bpp) or 0x00000000 (for 8bpp) */
	unsigned int greenMask;
	/*! 0x00ff0000 (for 24bpp and 32bpp) or 0x00000000 (for 8bpp) */
	unsigned int blueMask;
	/*! 0xff000000 (for 32bpp) or 0x00000000 (for 24bpp and 8bpp) */
	unsigned int alphaMask;
	/*! Bits per pixel, 0 (?), 8, 24 or 32. */
	byte bitsPerPixel;
	/*! Zero? */
	array<3,byte > unknown3Bytes;
	/*!
	 * [96,8,130,0,0,65,0,0] if 24 bits per pixel
	 *             [129,8,130,32,0,65,12,0] if 32 bits per pixel
	 *             [34,0,0,0,0,0,0,0] if 8 bits per pixel
	 *             [4,0,0,0,0,0,0,0] if 0 (?) bits per pixel
	 */
	array<8,byte > unknown8Bytes;
	/*! Seems to always be zero. */
	unsigned int unknownInt;
	/*! Unknown.  Could be reference pointer. */
	int unknownInt2;
	/*! Seems to always be zero. */
	unsigned int unknownInt3;
	/*! Flags */
	byte flags;
	/*! Unkown. Often zero. */
	unsigned int unknownInt4;
	/*! Unknown. */
	byte unknownByte1;
	/*! Channel Data */
	array<4,ChannelData > channels;
	/*! Link to NiPalette, for 8-bit textures. */
	Ref<NiPalette > palette;
	/*! Number of mipmaps in the texture. */
	mutable unsigned int numMipmaps;
	/*! Bytes per pixel (Bits Per Pixel / 8). */
	unsigned int bytesPerPixel;
	/*! Mipmap descriptions (width, height, offset). */
	vector<MipMap > mipmaps;
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
