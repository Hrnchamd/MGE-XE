/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _HKPACKEDNITRISTRIPSDATA_H_
#define _HKPACKEDNITRISTRIPSDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "bhkShapeCollection.h"

// Include structures
#include "../gen/hkTriangle.h"
#include "../gen/OblivionSubShape.h"
namespace Niflib {

class hkPackedNiTriStripsData;
typedef Ref<hkPackedNiTriStripsData> hkPackedNiTriStripsDataRef;

/*! NiTriStripsData for havok data? */
class hkPackedNiTriStripsData : public bhkShapeCollection {
public:
	/*! Constructor */
	NIFLIB_API hkPackedNiTriStripsData();

	/*! Destructor */
	NIFLIB_API virtual ~hkPackedNiTriStripsData();

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
	 * Returns the triangle faces that make up this mesh.
	 * \return A vector containing the triangle faces that make up this mesh.
	 * \sa hkPackedNiTriStripsData::SetTriangles
	 */
	NIFLIB_API virtual vector<Triangle> GetTriangles() const;
	
	/*!
	 * Returns the triangle data that make up this mesh.
	 * \return A vector containing the triangle data that make up this mesh.
	 * \sa hkPackedNiTriStripsData::SetTriangles
	 */
	NIFLIB_API virtual vector<hkTriangle> GetHavokTriangles() const;

	/*! 
	 * Returns the number of vertices that make up this mesh.  This is also the number of normals, colors, and UV coordinates if these are used.
	 * \return The number of vertices that make up this mesh.
	 */
	NIFLIB_API int GetVertexCount() const;

	/*! 
	 * Used to retrieve the vertices used by this mesh.  The size of the vector will be the same as the vertex count retrieved with the IShapeData::GetVertexCount function.
	 * \return A vector containing the vertices used by this mesh.
	 */
	NIFLIB_API vector<Vector3> GetVertices() const;

	/*! 
	 * Used to retrieve the normals used by this mesh.  The size of the vector will either be zero if no normals are used, or be the same as the vertex count retrieved with the IShapeData::GetVertexCount function.
	 * \return A vector containing the normals used by this mesh, if any.
	 */
	NIFLIB_API vector<Vector3> GetNormals() const;

	/*! Returns the number of vertices that make up this mesh.
	* \return The number of faces that make up this mesh.
	*/
	NIFLIB_API virtual int GetNumFace( ) const;

	/*! Returns the number of vertices that make up this mesh.
	* \param value The number of faces that make up this mesh.
	*/
	NIFLIB_API virtual void SetNumFaces( int value );

	/*! Replaces the triangle face data in this mesh with new data.
	* \param in A vector containing the new face data.  Maximum size is 65,535.
	* \sa ITriShapeData::GetTriangles
	*/
	NIFLIB_API virtual void SetTriangles( const vector<Triangle> & in );
	
	/*! Replaces the triangle face data in this mesh with new data.
	* \param in A vector containing the new face data.  Maximum size is 65,535.
	* \sa ITriShapeData::GetHavokTriangles
	*/
	NIFLIB_API virtual void SetHavokTriangles( const vector<hkTriangle> & in );

	/*! Replaces the face normal data in this mesh with new data.
	* \param in A vector containing the new face normal data.
	*/
	NIFLIB_API virtual void SetNormals( const vector<Vector3> & in );

	/*! Replaces the vertex data in this mesh with new data.
	* \param in A vector containing the new vertex data.
	*/
	NIFLIB_API virtual void SetVertices( const vector<Vector3> & in );

	/*!
	* Retrieves the subshape data object used by this geometry node, if any.
	* \return The subshape data object.
	*/
	NIFLIB_API vector<OblivionSubShape> GetSubShapes() const;

	/*!
	* Sets the subshape data object used by this geometry node. 
	* \param[in] value The subshape data.
	*/
	NIFLIB_API void SetSubShapes( vector<OblivionSubShape>& value );	

	//--END CUSTOM CODE--//
protected:
	/*! Number of triangles? */
	mutable unsigned int numTriangles;
	/*! The physics triangles? */
	vector<hkTriangle > triangles;
	/*! Number of vertices. */
	mutable unsigned int numVertices;
	/*! Unknown. */
	byte unknownByte1;
	/*! The vertices? */
	vector<Vector3 > vertices;
	/*! Number of subparts. */
	mutable unsigned short numSubShapes;
	/*! The subparts. */
	vector<OblivionSubShape > subShapes;
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
