/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIGEOMETRYDATA_H_
#define _NIGEOMETRYDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiObject.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class AbstractAdditionalGeometryData;
class NiGeometryData;
typedef Ref<NiGeometryData> NiGeometryDataRef;

/*! Mesh data: vertices, vertex normals, etc. */
class NiGeometryData : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiGeometryData();

	/*! Destructor */
	NIFLIB_API virtual ~NiGeometryData();

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
protected:
	/*! The mesh vertex indices. */
	vector<int > vertexIndices;

	/*! The mapping between Nif & Max UV sets. */
	std::map<int, int>  uvSetMap; // first = Max index, second = Nif index
public:

	//--Counts--//

	/*! 
	 * Returns the number of verticies that make up this mesh.  This is also the number of normals, colors, and UV coordinates if these are used.
	 * \return The number of vertices that make up this mesh.
	 * \sa IShapeData::SetVertexCount
	 */
	NIFLIB_API int GetVertexCount() const;

	/*! 
	 * Returns the number of texture coordinate sets used by this mesh.  For each UV set, there is a pair of texture coordinates for every vertex in the mesh.  Each set corresponds to a texture entry in the NiTexturingPropery object.
	 * \return The number of texture cooridnate sets used by this mesh.  Can be zero.
	 * \sa IShapeData::SetUVSetCount, ITexturingProperty
	 */
	NIFLIB_API short GetUVSetCount() const;

	/*! 
	 * Changes the number of UV sets used by this mesh.  If the new size is smaller, data at the end of the array will be lost.  Otherwise it will be retained.  The number of UV sets must correspond with the number of textures defined in the corresponding NiTexturingProperty object.
	 * \param n The new size of the uv set array.
	 * \sa IShapeData::GetUVSetCount, ITexturingProperty
	 */
	NIFLIB_API void SetUVSetCount(int n);

	/*! 
	 * Returns the number of vertec indices that make up this mesh.
	 * \return The number of vertex indices that make up this mesh.
	 * \sa IShapeData::SetVertexIndexCount
	 */
	NIFLIB_API int GetVertexIndexCount() const;

	//--Getters--//

	/*! 
	 * Returns the 3D center of the mesh.
	 * \return The center of this mesh.
	 */
	NIFLIB_API Vector3 GetCenter() const;

	/*! 
	 * Returns the radius of the mesh.  That is the distance from the center to
	 * the farthest point from the center.
	 * \return The radius of this mesh.
	 */
	NIFLIB_API float GetRadius() const;

	/*! 
	 * Assigns the center and radius of the spherical bound of this data.
	 * \remark GeoMorpher controllers will alter the model bound.
	 */
	NIFLIB_API void SetBound(Vector3 const & center, float radius);

	/*! 
	 * Used to retrive the vertices used by this mesh.  The size of the vector will be the same as the vertex count retrieved with the IShapeData::GetVertexCount function.
	 * \return A vector cntaining the vertices used by this mesh.
	 * \sa IShapeData::SetVertices, IShapeData::GetVertexCount, IShapeData::SetVertexCount.
	 */
	NIFLIB_API vector<Vector3> GetVertices() const;

	/*! 
	 * Used to retrive the normals used by this mesh.  The size of the vector will either be zero if no normals are used, or be the same as the vertex count retrieved with the IShapeData::GetVertexCount function.
	 * \return A vector cntaining the normals used by this mesh, if any.
	 * \sa IShapeData::SetNormals, IShapeData::GetVertexCount, IShapeData::SetVertexCount.
	 */
	NIFLIB_API vector<Vector3> GetNormals() const;

	/*! 
	 * Used to retrive the vertex colors used by this mesh.  The size of the vector will either be zero if no vertex colors are used, or be the same as the vertex count retrieved with the IShapeData::GetVertexCount function.
	 * \return A vector cntaining the vertex colors used by this mesh, if any.
	 * \sa IShapeData::SetVertexColors, IShapeData::GetVertexCount, IShapeData::SetVertexCount.
	 */
	NIFLIB_API vector<Color4> GetColors() const;

	/*! 
	 * Used to retrive the texture coordinates from one of the texture sets used by this mesh.  The function will throw an exception if a texture set index that does not exist is specified.  The size of the vector will be the same as the vertex count retrieved with the IShapeData::GetVertexCount function.
	 * \param index The index of the texture coordinate set to retrieve the texture coordinates from.  This index is zero based and must be a positive number smaller than that returned by the IShapeData::GetUVSetCount function.  If there are no texture coordinate sets, this function will throw an exception.
	 * \return A vector cntaining the the texture coordinates used by the requested texture coordinate set.
	 * \sa IShapeData::SetUVSet, IShapeData::GetUVSetCount, IShapeData::SetUVSetCount, IShapeData::GetVertexCount, IShapeData::SetVertexCount.
	 */
	NIFLIB_API vector<TexCoord> GetUVSet( int index ) const;
	
	/*! 
	 * Used to retrive the vertex indices used by this mesh.  The size of the vector will be the same as the vertex count retrieved with the IShapeData::GetVertexIndexCount function.
	 * \return A vector containing the vertex indices used by this mesh.
	 * \sa IShapeData::SetVertexIndices, IShapeData::GetVertexIndexCount, IShapeData::SetVertexIndexCount.
	 */
	NIFLIB_API vector<int> GetVertexIndices() const;

	/*! 
	 * Used to retrive the the NIF index corresponding to the Max map channel. If there isn't one, -1 is returned.
	 * \param maxMapChannel The max map channel of the desired UV set.
	 * \return A int representing the NIF index of the UV se used.
	 */
	NIFLIB_API int GetUVSetIndex(int maxMapChannel) const;

	//--Setters--//

	/*! 
	 * Used to set the vertex data used by this mesh.  Calling this function will clear all other data in this object.
	 * \param in A vector containing the vertices to replace those in the mesh with.  Note that there is no way to set vertices one at a time, they must be sent in one batch.
	 * \sa IShapeData::GetVertices, IShapeData::GetVertexCount
	 */
	NIFLIB_API virtual void SetVertices( const vector<Vector3> & in );

	/*!
	 * Used to set the normal data used by this mesh.  The size of the vector must either be zero, or the same as the vertex count retrieved with the IShapeData::GetVertexCount function or the function will throw an exception.
	 * \param in A vector containing the normals to replace those in the mesh with.  Note that there is no way to set normals one at a time, they must be sent in one batch.  Use an empty vector to signify that this mesh will not be using normals.
	 * \sa IShapeData::GetNormals, IShapeData::GetVertexCount, IShapeData::SetVertexCount.
	 */
	NIFLIB_API void SetNormals( const vector<Vector3> & in );

	/*!
	 * Used to set the vertex color data used by this mesh.  The size of the vector must either be zero, or the same as the vertex count retrieved with the IShapeData::GetVertexCount function or the function will throw an exception.
	 * \param in A vector containing the vertex colors to replace those in the mesh with.  Note that there is no way to set vertex colors one at a time, they must be sent in one batch.  Use an empty vector to signify that this mesh will not be using vertex colors.
	 * \sa IShapeData::GetColors, IShapeData::GetVertexCount, IShapeData::SetVertexCount.
	 */
	NIFLIB_API void SetVertexColors( const vector<Color4> & in );

	/*!
	 * Used to set the texture coordinate data from one of the texture sets used by this mesh.  The function will throw an exception if a texture set index that does not exist is specified.  The size of the vector must be the same as the vertex count retrieved with the IShapeData::GetVertexCount function, or the function will throw an exception.
	 * \param index The index of the texture coordinate set to retrieve the texture coordinates from.  This index is zero based and must be a positive number smaller than that returned by the IShapeData::GetUVSetCount function.  If there are no texture coordinate sets, this function will throw an exception.
	 * \param in A vector containing the the new texture coordinates to replace those in the requested texture coordinate set.
	 * \sa IShapeData::GetUVSet, IShapeData::GetUVSetCount, IShapeData::SetUVSetCount, IShapeData::GetVertexCount, IShapeData::SetVertexCount.
	 */
	NIFLIB_API void SetUVSet( int index, const vector<TexCoord> & in );

	/*! 
	 * Used to set the vertex index data used by this mesh.  Calling this function will clear all other data in this object.
	 * \param in A vector containing the vertex indices to replace those in the mesh with.  Note that there is no way to set vertices one at a time, they must be sent in one batch.
	 * \sa IShapeData::GetVertexIndices, IShapeData::GetVertexIndexCount
	 */
	NIFLIB_API virtual void SetVertexIndices( const vector<int> & in );

	/*! 
	 * Used to set the UV set mapping data used by this mesh.  This info maps the Max map channel to the index used in the NIF.
	 * \param in A map of UV set indices; first is the Max map channel and the second is the index used in the Nif mesh.
	 */
	NIFLIB_API virtual void SetUVSetMap( const std::map<int, int> & in );

	/*!
	 * Used to apply a transformation directly to all the vertices and normals in
	 * this mesh.
	 * \param[in] transform The 4x4 transformation matrix to apply to the vertices and normals in this mesh.  Normals are only affected by the rotation portion of this matrix.
	 */
	NIFLIB_API void Transform( const Matrix44 & transform );

	// Consistency Flags
	// \return The current value.
	NIFLIB_API ConsistencyType GetConsistencyFlags() const;

	// Consistency Flags
	// \param[in] value The new value.
	NIFLIB_API void SetConsistencyFlags( const ConsistencyType & value );

   // Methods for saving bitangents and tangents saved in upper byte.
   // \return The current value.
   NIFLIB_API byte GetTspaceFlag() const;

   // Methods for saving bitangents and tangents saved in upper byte.
   // \param[in] value The new value.
   NIFLIB_API void SetTspaceFlag( byte value );

   // Do we have lighting normals? These are essential for proper lighting: if not
   // present, the model will only be influenced by ambient light.
   // \return The current value.
   NIFLIB_API bool GetHasNormals() const;

   // Do we have lighting normals? These are essential for proper lighting: if not
   // present, the model will only be influenced by ambient light.
   // \param[in] value The new value.
   NIFLIB_API void SetHasNormals( bool value );

   // Unknown. Binormal & tangents? has_normals must be set as well for this field to
   // be present.
   // \return The current value.
   NIFLIB_API vector<Vector3 > GetBitangents() const;

   // Unknown. Binormal & tangents? has_normals must be set as well for this field to
   // be present.
   // \param[in] value The new value.
   NIFLIB_API void SetBitangents( const vector<Vector3 >& value );

   // Unknown. Binormal & tangents?
   // \return The current value.
   NIFLIB_API vector<Vector3 > GetTangents() const;

   // Unknown. Binormal & tangents?
   // \param[in] value The new value.
   NIFLIB_API void SetTangents( const vector<Vector3 >& value );

   NIFLIB_API SkyrimHavokMaterial GetSkyrimMaterial() const;

private:
   unsigned short numUvSetsCalc(const NifInfo &) const;
   unsigned short bsNumUvSetsCalc(const NifInfo &) const;

	//--END CUSTOM CODE--//
protected:
	/*! Unknown identifier. Always 0. */
	int unknownInt;
	/*! Number of vertices. */
	mutable unsigned short numVertices;
	/*! Bethesda uses this for max number of particles in NiPSysData. */
	unsigned short bsMaxVertices;
	/*! Used with NiCollision objects when OBB or TRI is set. */
	byte keepFlags;
	/*! Unknown. */
	byte compressFlags;
	/*! Is the vertex array present? (Always non-zero.) */
	bool hasVertices;
	/*! The mesh vertices. */
	vector<Vector3 > vertices;
	/*! Flag for tangents and bitangents in upper byte. Texture flags in lower byte. */
	mutable unsigned short numUvSets;
	/*!
	 * Bethesda's version of this field for nif versions 20.2.0.7 and up. Only a single
	 * bit denotes whether uv's are present. For example, see
	 * meshes/architecture/megaton/megatonrampturn45sml.nif in Fallout 3.
	 */
	mutable unsigned short bsNumUvSets;
	/*! Unknown, seen in Skyrim. */
	SkyrimHavokMaterial skyrimMaterial;
	/*!
	 * Do we have lighting normals? These are essential for proper lighting: if not
	 * present, the model will only be influenced by ambient light.
	 */
	bool hasNormals;
	/*! The lighting normals. */
	vector<Vector3 > normals;
	/*! Tangent vectors. */
	vector<Vector3 > tangents;
	/*! Bitangent vectors. */
	vector<Vector3 > bitangents;
	/*!
	 * Center of the bounding box (smallest box that contains all vertices) of the
	 * mesh.
	 */
	Vector3 center;
	/*!
	 * Radius of the mesh: maximal Euclidean distance between the center and all
	 * vertices.
	 */
	float radius;
	/*! Unknown, always 0? */
	array<13,short > unknown13Shorts;
	/*!
	 * Do we have vertex colors? These are usually used to fine-tune the lighting of
	 * the model.
	 * 
	 *             Note: how vertex colors influence the model can be controlled by
	 * having a NiVertexColorProperty object as a property child of the root node. If
	 * this property object is not present, the vertex colors fine-tune lighting.
	 * 
	 *             Note 2: set to either 0 or 0xFFFFFFFF for NifTexture compatibility.
	 */
	bool hasVertexColors;
	/*! The vertex colors. */
	vector<Color4 > vertexColors;
	/*!
	 * Do we have UV coordinates?
	 * 
	 *             Note: for compatibility with NifTexture, set this value to either
	 * 0x00000000 or 0xFFFFFFFF.
	 */
	bool hasUv;
	/*!
	 * The UV texture coordinates. They follow the OpenGL standard: some programs may
	 * require you to flip the second coordinate.
	 */
	vector< vector<TexCoord > > uvSets;
	/*! Consistency Flags */
	ConsistencyType consistencyFlags;
	/*! Unknown. */
	Ref<AbstractAdditionalGeometryData > additionalData;
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
