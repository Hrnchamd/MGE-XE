/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NITRISHAPEDATA_H_
#define _NITRISHAPEDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiTriBasedGeomData.h"

// Include structures
#include "../gen/MatchGroup.h"
namespace Niflib {

class NiTriShapeData;
typedef Ref<NiTriShapeData> NiTriShapeDataRef;

/*! Holds mesh data using a list of singular triangles. */
class NiTriShapeData : public NiTriBasedGeomData {
public:
	/*! Constructor */
	NIFLIB_API NiTriShapeData();

	/*! Destructor */
	NIFLIB_API virtual ~NiTriShapeData();

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
	 * A constructor which can be used to create a NiTriShapeData and initialize it with vertices.
	 * \param[in] verts The verticies to initialize the NiTriShapeData with.
	 */
	NIFLIB_API NiTriShapeData( const vector<Triangle>& verts );

	//--Match Detection--//
	
	//Reimplemented only to casue match detection data to be cleared
	//when vertices are updated.
	NIFLIB_API virtual void SetVertices( const vector<Vector3> & in );

	/*!
	 * This function generates match detection data based on the current
	 * vertex list.  The function of this data is unknown and appears to be
	 * optional.  The data contains a list of all the vertices that have
	 * identical positions are stored in the file.  If the vertex data is
	 * updated, match detection data will be cleared.
	 * \sa NiTriShapeData::HasMatchData
	 */
	NIFLIB_API void DoMatchDetection();

	/*!
	 * Remove match detection data.
	 */
	NIFLIB_API void RemoveMatchData();

	/*!
	 * Used to determine whether current match detection data has been previously
	 * generated.
	 * \return true if there is current match data, false otherwise.
	 * \sa NiTriShapeData::DoMatchDetection
	 */
	NIFLIB_API bool HasMatchData();

	//--Getters--//

	/*!
	 * Returns the triangle faces that make up this mesh.
	 * \return A vector containing the triangle faces that make up this mesh.
	 * \sa ITriShapeData::SetTriangles
	 */
	NIFLIB_API virtual vector<Triangle> GetTriangles() const;

	//--Setters--//

	/*! Replaces the triangle face data in this mesh with new data.
	 * \param in A vector containing the new face data.  Maximum size is 65,535.
	 * \sa ITriShapeData::GetTriangles
	 */
	NIFLIB_API virtual void SetTriangles( const vector<Triangle> & in );

private:
	bool hasTrianglesCalc(const NifInfo & info) const {
		return (triangles.size() > 0);
	};

	//--END CUSTOM CODE--//
protected:
	/*! Num Triangles times 3. */
	unsigned int numTrianglePoints;
	/*! Do we have triangle data? */
	mutable bool hasTriangles;
	/*! Triangle data. */
	vector<Triangle > triangles;
	/*! Number of shared normals groups. */
	mutable unsigned short numMatchGroups;
	/*! The shared normals. */
	vector<MatchGroup > matchGroups;
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
