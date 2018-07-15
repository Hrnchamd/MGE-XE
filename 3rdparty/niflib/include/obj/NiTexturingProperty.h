/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NITEXTURINGPROPERTY_H_
#define _NITEXTURINGPROPERTY_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiProperty.h"

// Include structures
#include "../gen/TexDesc.h"
#include "../gen/ShaderTexDesc.h"
namespace Niflib {

class NiTexturingProperty;
typedef Ref<NiTexturingProperty> NiTexturingPropertyRef;

/*! Describes an object's textures. */
class NiTexturingProperty : public NiProperty {
public:
	/*! Constructor */
	NIFLIB_API NiTexturingProperty();

	/*! Destructor */
	NIFLIB_API virtual ~NiTexturingProperty();

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
	 * Retrieves the number of texture slots defined by this texturing propery.  Texture slots may or may not actually contain textures, but each slot has a different meaning so the way a texture is used is dependant upon which slot it is in.
	 * \return The number of texture slots defined by this texturing property.
	 * \sa NiTexturingProperty::SetTextureCount
	 */
	NIFLIB_API int GetTextureCount() const;

	/*!
	 * Sets the number of texture slots defined by this texturing propery.  Known valid values are 7 and 8.
	 * \param new_count The new size of the texture slot array.
	 * \sa NiTexturingProperty::GetTextureCount
	 */
	NIFLIB_API void SetTextureCount( int new_count );

	/*! 
	 * Retrieves the number of extra texture slots defined by this texturing propery.  These only exist in later Nif versions and their function is unknown.
	 * \return The number of extra texture slots defined by this texturing property.
	 * \sa NiTexturingProperty::SetExtraTextureCount
	 */
	NIFLIB_API int GetShaderTextureCount() const;

	/*! 
	 * Sets the number of extra texture slots defined by this texturing propery.  Often zero.
	 * \param new_count The new size of the extra texture slot array.
	 * \sa NiTexturingProperty::GetExtraTextureCount
	 */
	NIFLIB_API void SetShaderTextureCount( int new_count );

	/*! 
	 * Retrieves the current apply mode for this texturing propery.  This enum value affects the way the textures will be drawn.
	 * \return The current apply mode for this texturing property.
	 * \sa NiTexturingProperty::SetApplyMode
	 */
	NIFLIB_API ApplyMode GetApplyMode() const;

	/*! 
	 * Sets the current apply mode for this texturing propery.  This enum value affects the way the textures will be drawn.
	 * \param new_val The new apply mode for this texturing property.
	 * \sa NiTexturingProperty::GetApplyMode
	 */
	NIFLIB_API void SetApplyMode( ApplyMode new_val );

	/*! 
	 * Retrieves the texture desription structure that describes a texture by slot number.  The TexType enum is provided to make it easy to select the texture slot with the specific qualities that you want.
	 * \param n The slot number of the texture to get the texture description of.  This is a positive zero based index that must be less than the value returned by NiTexturingProperty::GetTextureCount.
	 * \sa NiTexturingProperty::SetTexture, TexType
	 */
	NIFLIB_API TexDesc & GetTexture( int n );

	/*! 
	 * Checks whether a particular texture type is being used
	 * \param n The slot number of the texture to check.  This is a positive zero based index that must be less than the value returned by NiTexturingProperty::GetTextureCount.
	 * \return true if the texture in this slot is used, false otherwise.
	 */
	NIFLIB_API bool HasTexture( int n ) const;

	/*! 
	 * Clears a specific texture slot.
	 * \param n The slot number of the texture to clear.  This is a positive zero based index that must be less than the value returned by NiTexturingProperty::GetTextureCount.
	 */
	NIFLIB_API void ClearTexture( int n );

	/*! 
	 * Sets a new description for the texture in the given slot number.  The TexType enum is provided to make it easy to select the texture slot with the specific qualities that you want.
	 * \param n The slot number of the texture to set the texture description of.  This is a positive zero based index that must be less than the value returned by NiTexturingProperty::GetTextureCount.
	 * \param new_val Thew new texture descriptoin for the texture at the given slot number.
	 * \sa NiTexturingProperty::GetTexture, TexType
	 */
	NIFLIB_API void SetTexture( int n, TexDesc & new_val );

	/*! 
	 * Retrieves the texture desription structure that describes an extra texture by slot number.  These only exist in the later Nif versions and their function is unknown.
	 * \param n The slot number of the extra texture to get the texture description of.  This is a positive zero based index that must be less than the value returned by NiTexturingProperty::GetExtraTextureCount.
	 * \sa NiTexturingProperty::SetExtraTexture
	 */
	NIFLIB_API TexDesc GetShaderTexture( int n ) const;

	/*! 
	 * Sets a new description for the texture in the given slot number.  These only exist in the later Nif versions and their function is unknown.
	 * \param n The slot number of the extra texture to set the texture description of.  This is a positive zero based index that must be less than the value returned by NiTexturingProperty::GetTextureCount.
	 * \param new_val Thew new texture descriptoin for the extra texture at the given slot number.
	 * \sa NiTexturingProperty::GetTexture, TexType
	 */
	NIFLIB_API void SetShaderTexture( int n, TexDesc & new_val );

	/*! 
	 * Retrieves the bump map luma offset.  This is only relevant if a texture is defined in the BUMP_MAP texture slot.  The function of this is unknown.
	 * \return The bump map luma offset.
	 * \sa NiTexturingProperty::SetLumaOffset
	 */
	NIFLIB_API float GetLumaOffset() const;

	/*! 
	 * Sets the bump map luma offset.  This is only relevant if a texture is defined in the BUMP_MAP texture slot.  The function of this is unknown.
	 * \param new_val The new bump map luma offset.
	 * \sa NiTexturingProperty::GetLumaOffset
	 */
	NIFLIB_API void SetLumaOffset( float new_val );

	/*! 
	 * Retrieves the bump map luma scale.  This is only relevant if a texture is defined in the BUMP_MAP texture slot.  The function of this is unknown.
	 * \return The bump map luma scale.
	 * \sa NiTexturingProperty::SetLumaScale
	 */
	NIFLIB_API float GetLumaScale() const;

	/*! 
	 * Sets the bump map luma scale.  This is only relevant if a texture is defined in the BUMP_MAP texture slot.  The function of this is unknown.
	 * \param new_val The new bump map luma scale.
	 * \sa NiTexturingProperty::GetLumaScale
	 */
	NIFLIB_API void SetLumaScale( float new_val );

	/*! 
	 * Retrieves the bump map matrix.  This is only relevant if a texture is defined in the BUMP_MAP texture slot.  The function of this is unknown.
	 * \return the bump map matrix.
	 * \sa NiTexturingProperty::SetBumpMapMatrix
	 */
	NIFLIB_API Matrix22 GetBumpMapMatrix() const;

	/*! 
	 * Sets the bump map matrix.  This is only relevant if a texture is defined in the BUMP_MAP texture slot.  The function of this is unknown.
	 * \param new_val The new bump map matrix.
	 * \sa NiTexturingProperty::GetBumpMapMatrix
	 */
	NIFLIB_API void SetBumpMapMatrix( Matrix22 & new_val );

	//--END CUSTOM CODE--//
protected:
	/*! Property flags. */
	unsigned short flags;
	/*!
	 * Determines how the texture will be applied.  Seems to have special functions in
	 * Oblivion.
	 */
	ApplyMode applyMode;
	/*!
	 * Number of textures. Always 7 in versions < 20.0.0.4. Can also be 8 in >=
	 * 20.0.0.4.
	 */
	unsigned int textureCount;
	/*! Do we have a base texture? */
	bool hasBaseTexture;
	/*! The base texture. */
	TexDesc baseTexture;
	/*! Do we have a dark texture? */
	bool hasDarkTexture;
	/*! The dark texture. */
	TexDesc darkTexture;
	/*! Do we have a detail texture? */
	bool hasDetailTexture;
	/*! The detail texture. */
	TexDesc detailTexture;
	/*! Do we have a gloss texture? */
	bool hasGlossTexture;
	/*! The gloss texture. */
	TexDesc glossTexture;
	/*! Do we have a glow texture? */
	bool hasGlowTexture;
	/*! The glowing texture. */
	TexDesc glowTexture;
	/*! Do we have a bump map texture? */
	bool hasBumpMapTexture;
	/*! The bump map texture. */
	TexDesc bumpMapTexture;
	/*! Unknown. */
	float bumpMapLumaScale;
	/*! Unknown. */
	float bumpMapLumaOffset;
	/*! Unknown. */
	Matrix22 bumpMapMatrix;
	/*!
	 * Do we have a normal texture?  (Noraml guess based on file suffix in sample
	 * files)
	 */
	bool hasNormalTexture;
	/*! Normal texture. */
	TexDesc normalTexture;
	/*! Do we have a unknown texture 2? */
	bool hasUnknown2Texture;
	/*! Unknown texture 2. */
	TexDesc unknown2Texture;
	/*! Unknown. */
	float unknown2Float;
	/*! Do we have a decal 0 texture? */
	bool hasDecal0Texture;
	/*! The decal texture. */
	TexDesc decal0Texture;
	/*! Do we have a decal 1 texture? */
	bool hasDecal1Texture;
	/*! Another decal texture. */
	TexDesc decal1Texture;
	/*! Do we have a decal 2 texture? */
	bool hasDecal2Texture;
	/*! Another decal texture. */
	TexDesc decal2Texture;
	/*! Do we have a decal 3 texture? */
	bool hasDecal3Texture;
	/*! Another decal texture. Who knows the limit. */
	TexDesc decal3Texture;
	/*! Number of Shader textures that follow. */
	mutable unsigned int numShaderTextures;
	/*! Shader textures. */
	vector<ShaderTexDesc > shaderTextures;
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
