/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIPSYSMESHEMITTER_H_
#define _NIPSYSMESHEMITTER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiPSysEmitter.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiTriBasedGeom;
class NiPSysMeshEmitter;
typedef Ref<NiPSysMeshEmitter> NiPSysMeshEmitterRef;

/*! Particle emitter that uses points on a specified mesh to emit from. */
class NiPSysMeshEmitter : public NiPSysEmitter {
public:
	/*! Constructor */
	NIFLIB_API NiPSysMeshEmitter();

	/*! Destructor */
	NIFLIB_API virtual ~NiPSysMeshEmitter();

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
	 * Adds a single geometry to the collection. The collection will expand if necessary.
	 * \param[in] mesh The shape to add to the collection.
	 */
	NIFLIB_API bool AddEmitterMesh( Ref<NiTriBasedGeom > mesh );

	/*!
	 * Remove a single geometry from the collection.
	 * \param[in] mesh The shape remove from the collection.
	 */
	NIFLIB_API bool RemoveEmitterMesh( Ref<NiTriBasedGeom > mesh );

	/*!
	 * Replace a single geometry by another in the specified shape group.
	 * \param[in] newmesh The geometry put into the collection.
	 * \param[in] oldmesh The geometry remove from collection.
	 */
	NIFLIB_API bool ReplaceEmitterMesh( Ref<NiTriBasedGeom > newmesh, Ref<NiTriBasedGeom > oldmesh );

	//--END CUSTOM CODE--//
protected:
	/*! The number of references to emitter meshes that follow. */
	mutable unsigned int numEmitterMeshes;
	/*! Links to meshes used for emitting. */
	vector<Ref<NiTriBasedGeom > > emitterMeshes;
	/*! The way the particles get their initial direction and speed. */
	VelocityType initialVelocityType;
	/*! The parts of the mesh that the particles emit from. */
	EmitFrom emissionType;
	/*! The emission axis. */
	Vector3 emissionAxis;
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
