/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NITRISTRIPSDATA_H_
#define _NITRISTRIPSDATA_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiTriBasedGeomData.h"
namespace Niflib {

class NiTriStripsData;
typedef Ref<NiTriStripsData> NiTriStripsDataRef;

/*! Holds mesh data using strips of triangles. */
class NiTriStripsData : public NiTriBasedGeomData {
public:
	/*! Constructor */
	NIFLIB_API NiTriStripsData();

	/*! Destructor */
	NIFLIB_API virtual ~NiTriStripsData();

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
	 * A constructor which can be used to create a NiTriStripsData and initialize it with triangles.
	 * \param[in] tris The triangles to use to initialize the NiTriShapeData with.
	 * \param[in] nvtristrips Whether or not to use the NvTriStrips library from nVidia to generate triangle strips from the given data.
	 */
	NIFLIB_API NiTriStripsData(const vector<Triangle> & tris, bool nvtristrips = true);

	//--Counts--//

	/*!
	 * Used to get the number of triangle strips that this mesh is divided into.
	 * \return The number of triangle strips used by this mesh.
	 * \sa NiTriStripData::SetStripCount
	 */
	NIFLIB_API unsigned short GetStripCount() const;

	/*!
	 * Used to resize the triangle strips array.  If the new size is smaller, strips at the end of the array will be deleted.
	 * \param n The new size of the triangle strips array.
	 * \sa NiTriStripData::GetStripCount
	 */
	NIFLIB_API void SetStripCount(int n);
	
	//--Getters--//

	/*!
	 * Used to retrieve all the triangles from a specific triangle strip.
	 * \param index The index of the triangle strip to retrieve the triangles from.  This is a zero-based index which must be a positive number less than that returned by NiTriStripsData::GetStripCount.
	 * \return A vector containing all the triangle faces from the triangle strip specified by index.
	 * \sa NiTriStripData::SetStrip, NiTriStripData::GetTriangles
	 */
	NIFLIB_API vector<unsigned short> GetStrip( int index ) const;

	/*!
	 * This is a conveniance function which returns all triangle faces in all triangle strips that make up this mesh.  It is similar to the ITriShapeData::GetTriangles function.
	 * \return A vector containing all the triangle faces from all the triangle strips that make up this mesh.
	 * \sa NiTriStripData::GetTriangles, NiTriStripData::GetStrip, NiTriStripData::SetStrip
	 */
	vector<Triangle> GetTriangles() const;

	//--Setter--/

	/*!
	 * Used to set the triangle face data in a specific triangle strip.
	 * \param index The index of the triangle strip to set the face data for.  This is a zero-based index which must be a positive number less than that returned by NiTriStripsData::GetStripCount.
	 * \param in The vertex indices that make up this strip, in standard OpenGL triangle strip order.
	 * \sa NiTriStripData::GetStrip, NiTriStripData::GetTriangles
	 */
	NIFLIB_API void SetStrip( int index, const vector<unsigned short> & in );

	/*!
	 * Replaces the triangle face data in this mesh with new data.
	 * \param in A vector containing the new face data.  Maximum size is 65,535.
	 * \sa GetTriangles
	 */
	NIFLIB_API virtual void SetTriangles( const vector<Triangle> & in );

private:
	void SetNvTriangles( const vector<Triangle> & in );
	void SetTSTriangles( const vector<Triangle> & in );
	unsigned short CalcTriangleCount() const;

	//--END CUSTOM CODE--//
protected:
	/*! Number of OpenGL triangle strips that are present. */
	mutable unsigned short numStrips;
	/*! The number of points in each triangle strip. */
	mutable vector<unsigned short > stripLengths;
	/*! Do we have strip point data? */
	bool hasPoints;
	/*!
	 * The points in the Triangle strips.  Size is the sum of all entries in Strip
	 * Lengths.
	 */
	vector< vector<unsigned short > > points;
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
