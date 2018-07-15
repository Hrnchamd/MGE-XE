/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NISKININSTANCE_H_
#define _NISKININSTANCE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiObject.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiSkinData;
class NiSkinPartition;
class NiNode;
class NiSkinInstance;
typedef Ref<NiSkinInstance> NiSkinInstanceRef;

/*! Skinning instance. */
class NiSkinInstance : public NiObject {
public:
	/*! Constructor */
	NIFLIB_API NiSkinInstance();

	/*! Destructor */
	NIFLIB_API virtual ~NiSkinInstance();

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
	 * Retrieves the number of NiNode bones that influence this skin.
	 * \return The number of bones that influence this skin.
	 */
	NIFLIB_API unsigned int GetBoneCount() const;

	/*!
	 * Retrieves a list of references to all the NiNode bones that influence this skin.
	 * \return All the bones that influence this skin.
	 */
	NIFLIB_API vector< Ref<NiNode> > GetBones() const;

	/*!
	 * Retrieves the root node of the skeleton that influences this skin.  This is the common ancestor of all bones and the skin itself.
	 * \return The skeleton root.
	 */
	NIFLIB_API Ref<NiNode> GetSkeletonRoot() const;

	/*!
	 * Retrieves the root node of the skeleton that influences this skin.  This is the common ancestor of all bones and the skin itself.
	 * \return The skeleton root.
	 */
	NIFLIB_API Ref<NiSkinData> GetSkinData() const;

	/*!
	 * Retrieves the hardare skin partition, if any.
	 * \return The skeleton root.
	 */
	NIFLIB_API Ref<NiSkinPartition> GetSkinPartition() const;

	/*!
	 * This constructor is called by NiGeometry when it creates a new skin
	 * instance using the BindSkin function.
	 */
	NIFLIB_HIDDEN void BindSkin( NiNode * skeleton_root, vector< Ref<NiNode> > bone_nodes );

	/*! 
	 * NIFLIB_HIDDEN function.  For internal use only.
	 * Called by NiGeometry during the skin binding process.
	 */
	NIFLIB_HIDDEN void SetSkinData( NiSkinData * n );

	/*
	 * NIFLIB_HIDDEN function.  For internal use only.
	 * This can be used to set or clear the hardware skin partition data.  To create partition data, the NiTriBasedGeom::GenHardwareSkinInfo function should be used.
	 * \param[in] n The new hardware skin partition data object to use, or NULL to clear the existing one.
	 */
	NIFLIB_HIDDEN void SetSkinPartition( NiSkinPartition * n );

	/*! 
	 * NIFLIB_HIDDEN function.  For internal use only.
	 * Called by skeleton root NiNode when it self destructs to inform this skin
	 * instance that the skeleton has been lost.  Should not be called directly.
	 */
	NIFLIB_HIDDEN void SkeletonLost();

	//--END CUSTOM CODE--//
protected:
	/*! Skinning data reference. */
	Ref<NiSkinData > data;
	/*!
	 * Refers to a NiSkinPartition objects, which partitions the mesh such that every
	 * vertex is only influenced by a limited number of bones.
	 */
	Ref<NiSkinPartition > skinPartition;
	/*! Armature root node. */
	NiNode * skeletonRoot;
	/*! The number of node bones referenced as influences. */
	mutable unsigned int numBones;
	/*! List of all armature bones. */
	vector<NiNode * > bones;
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
