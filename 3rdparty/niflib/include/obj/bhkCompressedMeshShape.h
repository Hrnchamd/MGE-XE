/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BHKCOMPRESSEDMESHSHAPE_H_
#define _BHKCOMPRESSEDMESHSHAPE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "bhkShape.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiAVObject;
class bhkCompressedMeshShapeData;
class bhkCompressedMeshShape;
typedef Ref<bhkCompressedMeshShape> bhkCompressedMeshShapeRef;

/*! Compressed collision mesh. */
class bhkCompressedMeshShape : public bhkShape {
public:
	/*! Constructor */
	NIFLIB_API bhkCompressedMeshShape();

	/*! Destructor */
	NIFLIB_API virtual ~bhkCompressedMeshShape();

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
	 * Retrieve target
	 * \return target
     */
	NIFLIB_API  NiAVObject* GetTarget() const;
	
	/*!
	 * Set target 
	 * \param[in] value target
     */
	NIFLIB_API void SetTarget(NiAVObject* value);

	/*!
	 * Retrieve data
	 * \return data
     */
	NIFLIB_API  Ref<bhkCompressedMeshShapeData > GetData() const;

	/*!
	 * Set data
	 * \param[in] value data
     */
	NIFLIB_API void SetData(Ref<bhkCompressedMeshShapeData > value);

	//--END CUSTOM CODE--//
protected:
	/*! Points to root node? */
	NiAVObject * target;
	/*! The shape's material. */
	SkyrimHavokMaterial skyrimMaterial;
	/*! Unknown. */
	float unknownFloat1;
	/*! Unknown. */
	array<4,byte > unknown4Bytes;
	/*! Unknown */
	Vector4 unknownFloats1;
	/*! A shell with that radius is added around the shape. */
	float radius;
	/*! Scale */
	float scale;
	/*! Unknown */
	float unknownFloat3;
	/*! Unknown */
	float unknownFloat4;
	/*! Unknown */
	float unknownFloat5;
	/*! The collision mesh data. */
	Ref<bhkCompressedMeshShapeData > data;
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
