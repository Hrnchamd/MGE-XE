/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIBONELODCONTROLLER_H_
#define _NIBONELODCONTROLLER_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "NiTimeController.h"

// Include structures
#include "../gen/NodeGroup.h"
#include "../gen/SkinShapeGroup.h"
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiTriBasedGeom;
class NiBoneLODController;
typedef Ref<NiBoneLODController> NiBoneLODControllerRef;

/*! Level of detail controller for bones.  Priority is arranged from low to high. */
class NiBoneLODController : public NiTimeController {
public:
	/*! Constructor */
	NIFLIB_API NiBoneLODController();

	/*! Destructor */
	NIFLIB_API virtual ~NiBoneLODController();

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
	 * Returns the number of node groups (each group a sequence of bones).
	 * \return The number of node groups.
	 */
	NIFLIB_API int GetNodeGroupCount() const;

	/*!
	 * Returns a specific node group (each group a sequence of bones).
	 * \param[in] index The index of the node group to return the data for.  This must be >= 0 and < the result of ABoneLODController::GetNodeGroupCount.
	 * \return The specified node group.
	 */
	NIFLIB_API vector<Ref<NiNode> > GetNodeGroup( int index ) const;

	/*!
	 * Adds a single node to the specified group. The group list will expand if necessary.
	 * \param[in] index The index of the node group to add a node to.  This must be >= 0 and < the result of ABoneLODController::GetNodeGroupCount.
	 * \param[in] node The node to add to the group.
	 */
	NIFLIB_API void AddNodeToGroup( int index, NiNode * node );

	/*!
	 * Remove a single node from the specified node group. 
	 * \param[in] index The index of the node group to remove a node from.  This must be >= 0 and < the result of ABoneLODController::GetNodeGroupCount.
	 * \param[in] node The node remove from the group.
	 */
	NIFLIB_API void RemoveNodeFromGroup( int index, NiNode * node );

	/*!
	 * Assigns an entire node group, replacing any nodes that were in the group before.
	 * \param[in] index The index of the node group to assign a list of nodes to.  This must be >= 0 and < the result of ABoneLODController::GetNodeGroupCount.
	 * \param[in] group The list of nodes to assign to the specified node group.
	 */
	NIFLIB_API void SetNodeGroup( int index, const vector<Ref<NiNode> > & group );


	/*!
	 * Removes an entire node group.  This will cause the indices of any subsequent node groups to shift.
	 * \param[in] index The index of the node group to remove.  This must be >= 0 and < the result of ABoneLODController::GetNodeGroupCount.
	 */
	NIFLIB_API void RemoveNodeGroup( int index );

	/*!
	 * Clears all node groups.
	 */
	NIFLIB_API void ClearNodeGroups();
	
	/*!
	 * Adds a single shape to the specified group. The group list will expand if necessary.
	 * \param[in] shape The shape to add to the group.
	 */
	NIFLIB_API bool AddShapeToGroup( Ref<NiTriBasedGeom > shape );

	/*!
	 * Remove a single shape from the specified shape group.
	 * \param[in] shape The shape remove from the group.
	 */
	NIFLIB_API bool RemoveShapeFromGroup( Ref<NiTriBasedGeom > shape );

	/*!
	 * Replace a single shape by another in the specified shape group.
	 * \param[in] newshape The shape put from the group.
	 * \param[in] oldshape The shape remove from the group.
	 */
	NIFLIB_API bool ReplaceShapeInGroup( Ref<NiTriBasedGeom > newshape, Ref<NiTriBasedGeom > oldshape );

	//--END CUSTOM CODE--//
protected:
	/*! Unknown. */
	unsigned int unknownInt1;
	/*! Number of node groups. */
	mutable unsigned int numNodeGroups;
	/*! Number of node groups. */
	unsigned int numNodeGroups2;
	/*! A list of node groups (each group a sequence of bones). */
	vector<NodeGroup > nodeGroups;
	/*! Number of shape groups. */
	mutable unsigned int numShapeGroups;
	/*! List of shape groups. */
	vector<SkinShapeGroup > shapeGroups1;
	/*! The size of the second list of shape groups. */
	mutable unsigned int numShapeGroups2;
	/*! Group of NiTriShape indices. */
	vector<Ref<NiTriBasedGeom > > shapeGroups2;
	/*! Unknown. */
	int unknownInt2;
	/*! Unknown. */
	int unknownInt3;
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
