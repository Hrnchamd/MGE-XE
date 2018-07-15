/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _NIAVOBJECT_H_
#define _NIAVOBJECT_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
namespace Niflib {
	class NiNode;
}
//--END CUSTOM CODE--//

#include "NiObjectNET.h"

// Include structures
#include "../Ref.h"
#include "../gen/BoundingBox.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiProperty;
class NiCollisionObject;
class NiAVObject;
typedef Ref<NiAVObject> NiAVObjectRef;

/*! Generic node object. */
class NiAVObject : public NiObjectNET {
public:
	/*! Constructor */
	NIFLIB_API NiAVObject();

	/*! Destructor */
	NIFLIB_API virtual ~NiAVObject();

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
	 * Clears all embedded bounding box information.  Older NIF files can have a bounding box specified in them which will be used for collision detection instead of evaluating the triangles.
	 */
	NIFLIB_API void ClearBoundingBox();

	/*!
	 * Returns any embedded bounding box information.  NiAVObject::HasBoundingBox should be called first, as this function will throw an exception if there is no bounding box information in this object.  Older NIF files can have a bounding box specified in them which will be used for collision detection instead of evaluating the triangles.
	 * \return The embedded bounding box dimentions.
	 * \sa NiAVObject::HasBoundingBox
	 */
	NIFLIB_API BoundingBox GetBoundingBox() const;

	/*!
	 * Sets new embedded bounding box information.  Older NIF files can have a bounding box specified in them which will be used for collision detection instead of evaluating the triangles.
	 * \param[in] n The new bounding box dimentions.
	 */
	NIFLIB_API void SetBoundingBox( const BoundingBox & n );

	/*!
	 * Determines whether this object has embedded bounding box information.  Older NIF files can have a bounding box specified in them which will be used for collision detection instead of evaluating the triangles.
	 * \return True if this object has an embedded bounding box, false otherwise.
	 */
	NIFLIB_API bool HasBoundingBox() const;
	
	/*! 
	 * This is a conveniance function that allows you to retrieve the full 4x4 matrix transform of a node.  It accesses the "Rotation," "Translation," and "Scale" attributes and builds a complete 4x4 transformation matrix from them.
	 * \return A 4x4 transformation matrix built from the node's transform attributes.
	 * \sa INode::GetWorldTransform
	 */
	NIFLIB_API Matrix44 GetLocalTransform() const;

	/*! 
	 * This is a conveniance function that allows you to set the rotation, scale, and translation of an AV object with a 4x4 matrix transform.
	 * \n A 4x4 transformation matrix to set the AVObject's transform attributes with.
	 * \sa INode::GetLocalTransform
	 */
	NIFLIB_API void SetLocalTransform( const Matrix44 & n );

	/*! 
	 * This function will return a transform matrix that represents the location of this node in world space.  In other words, it concatenates all parent transforms up to the root of the scene to give the ultimate combined transform from the origin for this node.
	 * \return The 4x4 world transform matrix of this node.
	 * \sa INode::GetLocalTransform
	 */
	NIFLIB_API Matrix44 GetWorldTransform() const;

	/*!
	 * Returns the parent of this object in the scene graph.  May be NULL.
	 * \return The parent of this object in the scene graph.
	 */
	NIFLIB_API Ref<NiNode> GetParent() const;

	/*!
	 * Adds a property to this object.  Properties specify various charactaristics of the object that affect rendering.  They may be shared among objects.
	 * \param[in] obj The new property that is to affect this object.
	 */
	NIFLIB_API void AddProperty( NiProperty * obj );

	/*!
	 * Removes a property from this object.  Properties specify various charactaristics of the object that affect rendering.  They may be shared among objects.
	 * \param[in] obj The property that is no longer to affect this object.
	 */
	NIFLIB_API void RemoveProperty( NiProperty * obj );

	/*!
	 * Removes all properties from this object.  Properties specify various charactaristics of the object that affect rendering.  They may be shared among objects.
	 */
	NIFLIB_API void ClearProperties();

	/*!
	 * Retrieves a list of all properties that affect this object.  Properties specify various charactaristics of the object that affect rendering.  They may be shared among objects.
	 * \return All the properties that affect this object.
	 */
	NIFLIB_API vector< Ref<NiProperty> > GetProperties() const;

	/*!
	 * Retrieves the property that matches the specified type, if there is one.  A valid object should not have more than one property of the same type.  Properties specify various charactaristics of the object that affect rendering.  They may be shared among objects.
	 * \param[in] compare_to The type constant of the desired property type.
	 * \return The property that matches the specified type, or NULL if there isn't a match.
	 * \sa NiObject::TypeConst
	 */
	NIFLIB_API Ref<NiProperty> GetPropertyByType( const Type & compare_to );

	/*!
	 * Can be used to get the data stored in the flags field for this object.  It is usually better to call more specific flag-toggle functions if they are availiable.
	 * \return The flag data.
	 */
	NIFLIB_API unsigned short GetFlags() const;

	/*!
	 * Can be used to set the data stored in the flags field for this object.  It is usually better to call more specific flag-toggle functions if they are availiable.
	 * \param[in] n The new flag data.  Will overwrite any existing flag data.
	 */
	NIFLIB_API void SetFlags( unsigned short n );

	/*!
	 * Used to get the local rotation matrix for this object.  This is a 3x3 matrix that should not include scale or translation components.
	 * \return The local 3x3 rotation matrix for this object.
	 */
	NIFLIB_API Matrix33 GetLocalRotation() const;

	/*!
	 * Used to set the local rotation matrix for this object.  This is a 3x3 matrix that should not include scale or translation components.
	 * \param[in] n The new local 3x3 rotation matrix for this object.
	 */
	NIFLIB_API void SetLocalRotation( const Matrix33 & n );

	/*!
	 * Used to get the local translation vector for this object.  This determines the object's offset from its parent.
	 * \return The local translation vector for this object.
	 */
	NIFLIB_API Vector3 GetLocalTranslation() const;

	/*!
	 * Used to set the local translation vector for this object.  This determines the object's offset from its parent.
	 * \param[in] n The new local translation vector for this object.
	 */
	NIFLIB_API void SetLocalTranslation( const Vector3 & n );

	/*!
	 * Used to get the local scale factor for this object.  The NIF format does not support separate scales along different axis, and many games do not react well to scale factors other than 1.0.
	 * \return The local scale factor for this object.
	 */
	NIFLIB_API float GetLocalScale() const;

	/*!
	 * Used to set the local scale factor for this object.  The NIF format does not support separate scales along different axis, and many games do not react well to scale factors other than 1.0.
	 * \param[in] n The new local scale factor for this object.
	 */
	NIFLIB_API void SetLocalScale( float n );

	/*!
	 * Gets the velocity vector for this object.  This vector exists in older NIF files and seems to have no function.
	 * \return The velocity vector for this object.
	 */
	NIFLIB_API Vector3 GetVelocity() const;

	/*!
	 * Sets the velocity vector for this object.  This vector exists in older NIF files and seems to have no function.
	 * \param[in] n The new velocity vector for this object.
	 */
	NIFLIB_API void SetVelocity( const Vector3 & n );

	/*!
	 * Gets the current visibility of this object as specified in its flag data.
	 * \return True if the object is visible, false otherwise.
	 */
	NIFLIB_API bool GetVisibility() const;

	/*!
	 * Sets the current visibility of this object by altering its flag data.
	 * \param[in] n Whether or not the object will now be visible.  True if visible, false otherwise.
	 */
	NIFLIB_API void SetVisibility( bool n );

	/*!
	 * Gets the current collision object for this object.  Usually a bounding box.  In Oblivion this links to the Havok objects.
	 * \return The current collision object for this object.
	 */
	NIFLIB_API Ref<NiCollisionObject > GetCollisionObject() const;

	/*!
	 * Sets the collision object for this object.  Usually a bounding box.  In Oblivion this links to the Havok objects.
	 * \param[in] value The new collision object to use.
	 */
	NIFLIB_API void SetCollisionObject( NiCollisionObject * value );

	/*!
	 * Used to get and set the collision type of a NiAVObject.
	 */
	enum CollisionType {
		/*! No collision */
		CT_NONE = 0,
		/*! Collision detection will use the triangles themselves.  Possibly incompatible with triangle strips. */
		CT_TRIANGLES = 1,
		/*! Collision detection will use the embedded bounding box information. */
		CT_BOUNDINGBOX = 2,
		/*! Collision detection will continue on to the lower objects in the scene graph. */
		CT_CONTINUE = 3
	};

	/*!
	 * Gets the current collision detection setting from the object's flag data.
	 * \return The collision detection setting for this object.
	 */
	NIFLIB_API CollisionType GetCollisionMode() const;

	/*!
	 * Sets the current collision detection setting in the object's flag data.
	 * \param[in] value The new collision detection setting for this object.
	 */
	NIFLIB_API void SetCollisionMode( CollisionType value );

   	/*!
	 * NIFLIB_HIDDEN function.  For internal use only.
	 * Called by NiNode during the addition of new children.
	 */
	NIFLIB_HIDDEN void SetParent( NiNode * new_parent );

protected:
	NiNode * parent;

	//--END CUSTOM CODE--//
protected:
	/*! Some flags; commonly 0x000C or 0x000A. */
	unsigned short flags;
	/*! Unknown Flag */
	unsigned short unknownShort1;
	/*! The translation vector. */
	Vector3 translation;
	/*! The rotation part of the transformation matrix. */
	Matrix33 rotation;
	/*! Scaling part (only uniform scaling is supported). */
	float scale;
	/*! Unknown function. Always seems to be (0, 0, 0) */
	Vector3 velocity;
	/*! The number of property objects referenced. */
	mutable unsigned int numProperties;
	/*! List of node properties. */
	vector<Ref<NiProperty > > properties;
	/*! Always 2,0,2,0. */
	array<4,unsigned int > unknown1;
	/*! 0 or 1. */
	byte unknown2;
	/*! Do we have a bounding box? */
	bool hasBoundingBox;
	/*! The bounding box. */
	BoundingBox boundingBox;
	/*!
	 * Refers to NiCollisionObject, which is usually a bounding box or other simple
	 * collision shape.  In Oblivion this links the Havok objects.
	 */
	Ref<NiCollisionObject > collisionObject;
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
