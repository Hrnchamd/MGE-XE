/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NINODE_H_
#define _NINODE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
namespace Niflib {
	class NiSkinInstance;
}
//--END CUSTOM CODE--//

#include "NiAVObject.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiAVObject;
class NiDynamicEffect;
class NiNode;
typedef Ref<NiNode> NiNodeRef;

/*! Generic node object for grouping. */
class NiNode : public NiAVObject {
public:
	/*! Constructor */
	NIFLIB_API NiNode();

	/*! Destructor */
	NIFLIB_API virtual ~NiNode();

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
	 * Adds a child AV Object to this node.  This is a sub-leaf in the scene graph contained in a NIF file.  Each AV Object can only be the child of one node.
	 * \param[in] obj The AV Object to add as a child of this node.
	 */
	NIFLIB_API void AddChild( Ref<NiAVObject> obj );

	/*!
	 * Removes an AV Object child from this node.  This is a sub-leaf in the scene graph contained in a NIF file.  Each AV Object can only be the child of one node.
	 * The caller is responsible that the child is no longer weakly linked elsewhere, for instance, as a skin influence.
	 * \param[in] obj The AV Object to remove as a child from this node.
	 */
	NIFLIB_API void RemoveChild( Ref<NiAVObject> obj );

	/*!
	 * Removes all AV Object children from this node.  These are a sub-leafs in the scene graph contained in a NIF file.  Each AV Object can only be the child of one node.
	 * The caller is responsible that no child is still weakly linked elsewhere, for instance, as a skin influence.
	 */
	NIFLIB_API void ClearChildren();

	/*!
	 * Retrieves all AV Object children from this node.  These are a sub-leafs in the scene graph contained in a NIF file.  Each AV Object can only be the child of one node.
	 * \return A list of all the AV Objects that are children of this node in the scene graph.
	 */
	NIFLIB_API vector< Ref<NiAVObject> > GetChildren() const;

#ifdef USE_NIFLIB_TEMPLATE_HELPERS
	template <typename ChildEquivalence>
	inline void SortChildren(ChildEquivalence pred) {
		std::stable_sort(children.begin(), children.end(), pred);
	}
#endif

	/*!
	 * Adds a dynamic effect to this node.  This is usually a light, but can also be a texture effect or something else.  Can affect nodes further down the scene graph from this one as well.
	 * \param[in] effect The new dynamic effect to add to this node.
	 */
	NIFLIB_API void AddEffect( NiDynamicEffect * effect );

	/*!
	 * Removes a dynamic effect to this node.  This is usually a light, but can also be a texture effect or something else.  Can affect nodes further down the scene graph from this one as well.
	 * \param[in] effect The dynamic effect to remove from this node.
	 */
	NIFLIB_API void RemoveEffect( NiDynamicEffect * effect );

	/*!
	 * Removes all dynamic effects from this node.  These is usually lights, but can also be a texture effects or something else.  Can affect nodes further down the scene graph from this one as well.
	 */
	NIFLIB_API void ClearEffects();

	/*!
	 * Retrieves all the dynamic effects attached to this node.  This is usually a light, but can also be a texture effect or something else.  Can affect nodes further down the scene graph from this one as well.
	 * \return The dynamic effects attached to this node.
	 */
	NIFLIB_API vector< Ref<NiDynamicEffect> > GetEffects() const;

	/*! Checks if this node has any skins attached. */
	NIFLIB_API bool IsSkeletonRoot() const;

	/*! Checks if this node influences the vertices in any skins. */
	NIFLIB_API bool IsSkinInfluence() const;

	/*! 
	 * Applies a huristic to guess whether this node was created as a proxy
	 * when a mesh which had more than one material in the original model
	 * was split in an exporter.
	 * /return Whether or not this node is probably a split mesh proxy
	 */
	NIFLIB_API bool IsSplitMeshProxy() const;
	   

	/*! 
	 * Causes all children's transforms to be changed so that all the skin
	 * pieces line up without any vertex transformations.
	 */
	NIFLIB_API void GoToSkeletonBindPosition();

	/*!
	 * Applies the local transforms of this node to its children,
	 * causing itself to be cleared to identity transforms.
	 */
	NIFLIB_API void PropagateTransform();

	/*! 
	 * NIFLIB_HIDDEN function.  For internal use only.
	 * Should only be called by NiTriBasedGeom.  Adds a new SkinInstance to the specified mesh.  The bones must be below this node in the scene graph tree
	 */
	NIFLIB_HIDDEN void AddSkin( NiSkinInstance * skin_inst );

	/*! 
	 * NIFLIB_HIDDEN function.  For internal use only.
	 * Should only be called by NiTriBasedGeom.  Detaches the skin associated with a child mesh.
	 */
	NIFLIB_HIDDEN void RemoveSkin( NiSkinInstance * skin_inst );

	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN void SetSkinFlag( bool n );

private:
	void RepositionGeom( NiAVObjectRef root );
protected:
	list<NiSkinInstance*> skins;

	//--END CUSTOM CODE--//
protected:
	/*! The number of child objects. */
	mutable unsigned int numChildren;
	/*! List of child node object indices. */
	vector<Ref<NiAVObject > > children;
	/*! The number of references to effect objects that follow. */
	mutable unsigned int numEffects;
	/*! List of node effects. ADynamicEffect? */
	vector<Ref<NiDynamicEffect > > effects;
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
