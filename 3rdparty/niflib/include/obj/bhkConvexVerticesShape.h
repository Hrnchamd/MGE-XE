/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BHKCONVEXVERTICESSHAPE_H_
#define _BHKCONVEXVERTICESSHAPE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "bhkConvexShape.h"
namespace Niflib {

class bhkConvexVerticesShape;
typedef Ref<bhkConvexVerticesShape> bhkConvexVerticesShapeRef;

/*!
 * A convex shape built from vertices. Note that if the shape is used in
 *         a non-static object (such as clutter), then they will simply fall
 *         through ground when they are under a bhkListShape.
 */
class bhkConvexVerticesShape : public bhkConvexShape {
public:
	/*! Constructor */
	NIFLIB_API bhkConvexVerticesShape();

	/*! Destructor */
	NIFLIB_API virtual ~bhkConvexVerticesShape();

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

	/*! 
	* Used to retrieve the distance to center for vertices.  The size of the vector will either be zero if no normals are used, or be the same as the vertex count retrieved with the IShapeData::GetVertexCount function.
	* \return A vector containing the normals used by this mesh, if any.
	*/
	NIFLIB_API vector<float> GetDistToCenter() const;

	/*! 
	* Used to set the vertex data used by this mesh.  Calling this function will clear all other data in this object.
	* \param in A vector containing the vertices to replace those in the mesh with.  Note that there is no way to set vertices one at a time, they must be sent in one batch.
	*/
	NIFLIB_API void SetVertices( const vector<Vector3> & in );

	/*!
	* Used to set the normal data used by this mesh.  The size of the vector must either be zero, or the same as the vertex count retrieved with the IShapeData::GetVertexCount function or the function will throw an exception.
	* \param in A vector containing the normals to replace those in the mesh with.  Note that there is no way to set normals one at a time, they must be sent in one batch.  Use an empty vector to signify that this mesh will not be using normals.
	*/
	NIFLIB_API void SetNormals( const vector<Vector3> & in );

	/*!
	* Used to sets the distance to center for vertices.  The size of the vector must either be zero, or the same as the vertex count retrieved with the IShapeData::GetVertexCount function or the function will throw an exception.
	* \param in A vector containing the normals to replace those in the mesh with.  Note that there is no way to set normals one at a time, they must be sent in one batch.  Use an empty vector to signify that this mesh will not be using normals.
	*/
	NIFLIB_API void SetDistToCenter( const vector<float> & in );

	/*! 
	* Used to retrieve the normal and the distance to center for vertices.  The size of the vector will either be zero if no normals are used, or be the same as the vertex count retrieved with the IShapeData::GetVertexCount function.
	* \return A vector containing the normals used by this mesh, if any.
	*/
	NIFLIB_API vector<Vector4> GetNormalsAndDist() const;

	/*! 
	* Used to set the normal and the distance to center for vertices.  The size of the vector will either be zero if no normals are used, or be the same as the vertex count retrieved with the IShapeData::GetVertexCount function.
	*/
	NIFLIB_API void SetNormalsAndDist(const vector<Vector4>& value);

	/*! Helper routine for calculating mass properties.
	 *  \param[in]  density Uniform density of object
	 *  \param[in]  solid Determines whether the object is assumed to be solid or not
	 *  \param[out] mass Calculated mass of the object
	 *  \param[out] center Center of mass
	 *  \param[out] inertia Mass Inertia Tensor
	 *  \return Return mass, center, and inertia tensor.
	 */
	NIFLIB_API virtual void CalcMassProperties(float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia);

	//--END CUSTOM CODE--//
protected:
	/*!
	 * Unknown. Must be (0.0,0.0,-0.0,0.0,0.0,-0.0) for arrow detection to work (mind
	 * the minus signs, -0.0 is 0x80000000 in hex).
	 */
	array<6,float > unknown6Floats;
	/*! Number of vertices. */
	mutable unsigned int numVertices;
	/*! Vertices. Fourth component is 0. Lexicographically sorted. */
	vector<Vector4 > vertices;
	/*! The number of half spaces. */
	mutable unsigned int numNormals;
	/*!
	 * Half spaces as determined by the set of vertices above. First three components
	 * define the normal pointing to the exterior, fourth component is the signed
	 * distance of the separating plane to the origin: it is minus the dot product of v
	 * and n, where v is any vertex on the separating plane, and n is the normal.
	 * Lexicographically sorted.
	 */
	vector<Vector4 > normals;
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
