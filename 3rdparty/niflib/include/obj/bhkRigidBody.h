/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BHKRIGIDBODY_H_
#define _BHKRIGIDBODY_H_

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "bhkEntity.h"

// Include structures
#include "../gen/QuaternionXYZW.h"
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class bhkSerializable;
class bhkRigidBody;
typedef Ref<bhkRigidBody> bhkRigidBodyRef;

/*!
 * This is the default body type for all "normal" usable and static world objects.
 * The "T" suffix
 *         marks this body as active for translation and rotation, a normal
 * bhkRigidBody ignores those
 *         properties. Because the properties are equal, a bhkRigidBody may be
 * renamed
 *         into a bhkRigidBodyT and vice-versa.
 */
class bhkRigidBody : public bhkEntity {
public:
	/*! Constructor */
	NIFLIB_API bhkRigidBody();

	/*! Destructor */
	NIFLIB_API virtual ~bhkRigidBody();

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
	 * Retrieves what appears to be a copy of the layer value.
	 * \return The duplicate layer value.
	 */
	NIFLIB_API OblivionLayer GetLayerCopy() const;

	/*!
	 * Sets what appears to be a copy of the layer value.
	 * \param[in] value The new duplicate layer value.
	 */
	NIFLIB_API void SetLayerCopy( OblivionLayer value );

	NIFLIB_API SkyrimLayer GetSkyrimLayerCopy() const;
	NIFLIB_API void SetSkyrimLayerCopy( SkyrimLayer value );

	/*!
	 * Gets the current translation of this rigid body.
	 * \return The translation of this rigid body.
	 */
	NIFLIB_API Vector4 GetTranslation() const;

	/*!
	 * Sets a new translation for this rigid body.
	 * \param[in] value  The new translation for this rigid body.
	 */
	NIFLIB_API void SetTranslation( const Vector4 & value );

	/*!
	 * Gets the current rotation of this rigid body.
	 * \return The rotation of this rigid body.
	 */
	NIFLIB_API QuaternionXYZW GetRotation() const;

	/*!
	 * Sets a new rotation for this rigid body.
	 * \param[in] value The new rotation for this rigid body.
	 */
	NIFLIB_API void SetRotation( const QuaternionXYZW & value );

	/*!
	 * Gets the current linear velocity of this rigid body.
	 * \return The linear velocity of this rigid body.
	 */
	NIFLIB_API Vector4 GetLinearVelocity() const;

	/*!
	 * Sets a new linear velocity for this rigid body.
	 * \param[in] value The new linear velocity for this rigid body.
	 */
	NIFLIB_API void SetLinearVelocity( const Vector4 & value );

	/*!
	 * Gets the current angular velocity of this rigid body.
	 * \return The angular velocity of this rigid body.
	 */
	NIFLIB_API Vector4 GetAngularVelocity() const;

	/*!
	 * Sets a new angular velocity for this rigid body.
	 * \param[in] value The new angular velocity for this rigid body.
	 */
	NIFLIB_API void SetAngularVelocity( const Vector4 & value );

	/*!
	 * Gets the current inertia of this rigid body.
	 * \return The inertia of this rigid body.
	 */
	NIFLIB_API InertiaMatrix GetInertia() const;

	/*!
	 * Sets a new inertia for this rigid body.
	 * \param[in] value The new inertia for this rigid body.
	 */
	NIFLIB_API void SetInertia( const InertiaMatrix & value );

	/*!
	 * Gets the current center point of this rigid body.
	 * \return The center point of this rigid body.
	 */
	NIFLIB_API Vector4 GetCenter() const;

	/*!
	 * Sets a new center point for this rigid body.
	 * \param[in] value The new center point for this rigid body.
	 */
	NIFLIB_API void SetCenter( const Vector4 & value );

	/*!
	 * Gets the current mass of this rigid body.
	 * \return The mass of this rigid body.
	 */
	NIFLIB_API float GetMass() const;

	/*!
	 * Sets a new mass for this rigid body.
	 * \param[in] value The new mass for this rigid body.
	 */
	NIFLIB_API void SetMass( float value );

	/*!
	 * Gets the current linear damping level of this rigid body.
	 * \return The linear damping level of this rigid body.
	 */
	NIFLIB_API float GetLinearDamping() const;

	/*!
	 * Sets a new linear damping level for this rigid body.
	 * \param[in] value The new linear damping level for this rigid body.
	 */
	NIFLIB_API void SetLinearDamping( float value );

	/*!
	 * Gets the current angular damping level of this rigid body.
	 * \return The angular damping level of this rigid body.
	 */
	NIFLIB_API float GetAngularDamping() const;

	/*!
	 * Sets a new angular damping level for this rigid body.
	 * \param[in] value The new angular damping level for this rigid body.
	 */
	NIFLIB_API void SetAngularDamping( float value );

	/*!
	 * Gets the current friction of this rigid body.
	 * \return The friction of this rigid body.
	 */
	NIFLIB_API float GetFriction() const;

	/*!
	 * Sets a new friction for this rigid body.
	 * \param[in] value The new friction for this rigid body.
	 */
	NIFLIB_API void SetFriction( float value );

	/*!
	 * Gets the current restitution of this rigid body.
	 * \return The restitution of this rigid body.
	 */
	NIFLIB_API float GetRestitution() const;

	/*!
	 * Sets a new restitution for this rigid body.
	 * \param[in] value The new restitution for this rigid body.
	 */
	NIFLIB_API void SetRestitution( float value );

	/*!
	 * Gets the current maximum linear velocity of this rigid body.
	 * \return The maximum linear velocity of this rigid body.
	 */
	NIFLIB_API float GetMaxLinearVelocity() const;

	/*!
	 * Sets a new maximum linear velocit for this rigid body.
	 * \param[in] value The new maximum linear velocity for this rigid body.
	 */
	NIFLIB_API void SetMaxLinearVelocity( float value );

	/*!
	 * Gets the current maximum angular velocity of this rigid body.
	 * \return The maximum angular velocity of this rigid body.
	 */
	NIFLIB_API float GetMaxAngularVelocity() const;

	/*!
	 * Sets a new maximum angular velocity for this rigid body.
	 * \param[in] value The new maximum angular velocit for this rigid body.
	 */
	NIFLIB_API void SetMaxAngularVelocity( float value );

	/*!
	 * Gets the current allowable penetration depth of this rigid body.
	 * \return The allowable penetration depth of this rigid body.
	 */
	NIFLIB_API float GetPenetrationDepth() const;

	/*!
	 * Sets a new allowable penetration depth for this rigid body.
	 * \param[in] value The new allowable penetration depth for this rigid body.
	 */
	NIFLIB_API void SetPenetrationDepth( float value );

	/*!
	 * Sets the current motion system for this rigid body.  Seems to override motion quality when set to keyframed.
	 * \return The current motion system setting of this rigid body.
	 */
	NIFLIB_API MotionSystem GetMotionSystem() const;

	/*!
	 * Gets the current motion system of this rigid body.  Seems to override motion quality when set to keyframed.
	 * \param[in] value The new motion system setting for this rigid body.
	 */
	NIFLIB_API void SetMotionSystem( MotionSystem value );

	/*!
	 * Sets the quality of the calculations used to detect collisions for this object.  Essentially, the faster the object goes, the higher quality of motion it will require.
	 * \return The current motion quality setting of this rigid body.
	 */
	NIFLIB_API MotionQuality GetQualityType() const;

	/*!
	 * Gets the quality of the calculations used to detect collisions for this object.  Essentially, the faster the object goes, the higher quality of motion it will require.
	 * \param[in] value The new motion quality setting for this rigid body.
	 */
	NIFLIB_API void SetQualityType( MotionQuality value );

	// The initial deactivator type of the body.
	// \return The current value.
	NIFLIB_API DeactivatorType GetDeactivatorType() const;

	// The initial deactivator type of the body.
	// \param[in] value The new value.
	NIFLIB_API void SetDeactivatorType( const DeactivatorType & value );

	// Usually set to 1 for fixed objects, or set to 2 for moving ones.  Seems to
	// always be same as Unknown Byte 1.
	// \return The current value.
	NIFLIB_API SolverDeactivation GetSolverDeactivation() const;

	// Usually set to 1 for fixed objects, or set to 2 for moving ones.  Seems to
	// always be same as Unknown Byte 1.
	// \param[in] value The new value.
	NIFLIB_API void SetSolverDeactivation( const SolverDeactivation & value );

	/*!
	 * Adds a constraint to this bhkRigidBody.
	 */
	NIFLIB_API void AddConstraint( bhkSerializable * obj );

	/*!
	 * Removes a constraint from this bhkRigidBody.
	 */
	NIFLIB_API void RemoveConstraint( bhkSerializable * obj );

	/*!
	 * Removes all constraints from this bhkRigidBody.
	 */
	NIFLIB_API void ClearConstraints();

	/*!
	 * Retrieves all the constraints attached to this bhkRigidBody.
	 */
	NIFLIB_API vector< Ref<bhkSerializable> > GetConstraints() const;

	// Apply scale factor <scale> on data.
	// \param[in] scale Factor to scale by
	NIFLIB_API void ApplyScale(float scale);

	// Look at all the objects under this rigid body and update the mass
	//  center of gravity, and inertia tensor accordingly. If the mass parameter
	//  is given then the density argument is ignored.
	NIFLIB_API void UpdateMassProperties(float density = 1.0f, bool solid = true, float mass = 0.0f);

	/*!
	 * Returns the unknown 7 shorts
	 * \return An array containing the 7 unknown shorts within this object.
	 */
	NIFLIB_API virtual array<7,unsigned short > GetUnknown7Shorts() const;

	/*! Replaces the unknown 7 shorts with new data
	 * \param in An array containing the new data.  Size is 7.
	 */
	NIFLIB_API virtual void SetUnknown7Shorts( const array<7,unsigned short > & in );


	//--END CUSTOM CODE--//
protected:
	/*! Unknown. Could be 2 shorts corresponding to Unknown 7 Shorts[1] and [2]. */
	int unknownInt1;
	/*! Unknown. */
	int unknownInt2;
	/*! Unknown. Could be 3 floats. */
	array<3,int > unknown3Ints;
	/*! The collision response. See hkResponseType for hkpWorld default implementations. */
	hkResponseType collisionResponse_;
	/*! Unknown */
	byte unknownByte;
	/*!
	 * Lowers the frequency for processContactCallbacks. A value of 5 means that a
	 * callback is raised every 5th frame.
	 */
	unsigned short processContactCallbackDelay_;
	/*! Unknown. */
	array<2,unsigned short > unknown2Shorts;
	/*! Copy of Layer value? */
	OblivionLayer layerCopy;
	/*! Copy of Col Filter value? */
	byte colFilterCopy;
	/*! Copy of Layer value? */
	SkyrimLayer skyrimLayerCopy;
	/*! Copy of  value? */
	byte flagsAndPartNumberCopy;
	/*!
	 * Unknown.
	 *             Oblivion defaults: 0 21280 2481 62977 65535 44 0
	 *             Skyrim defaults: 0 56896 1343 0 0 1 65535 (fourth and fifth element
	 * *must* be zero)
	 */
	array<7,unsigned short > unknown7Shorts;
	/*!
	 * A vector that moves the body by the specified amount. Only enabled in
	 * bhkRigidBodyT objects.
	 */
	Vector4 translation;
	/*!
	 * The rotation Yaw/Pitch/Roll to apply to the body. Only enabled in bhkRigidBodyT
	 * objects.
	 */
	QuaternionXYZW rotation;
	/*! Linear velocity. */
	Vector4 linearVelocity;
	/*! Angular velocity. */
	Vector4 angularVelocity;
	/*! Defines how the mass is distributed among the body. */
	InertiaMatrix inertia;
	/*!
	 * This seems to be used to relocate the object's center of mass. Useful for
	 * balancing objects in contraints.
	 */
	Vector4 center;
	/*! The body's mass in kg. A mass of zero represents an immovable object. */
	float mass;
	/*!
	 * Damping value for linear movement. A value that is too small fixes the object in
	 * place.
	 */
	float linearDamping;
	/*! Damping value for angular movement. */
	float angularDamping;
	/*! Unknown. */
	float unknownTimefactorOrGravityfactor1;
	/*! Unknown. */
	float unknownTimefactorOrGravityfactor2;
	/*! The body's friction. */
	float friction;
	/*! Unknown. */
	float rollingfrictionmultiplier_;
	/*!
	 * The body's restitution (elasticity).
	 *             If the restitution is not 0.0 the object will need extra CPU for all
	 * new collisions.
	 *             Try to set restitution to 0 for maximum performance (e.g. collapsing
	 * buildings)
	 */
	float restitution;
	/*! Maximal linear velocity. */
	float maxLinearVelocity;
	/*! Maximal angular velocity. Pi x 10? */
	float maxAngularVelocity;
	/*!
	 * The maximum allowed penetration for this object.
	 *             This is a hint to the engine to see how much CPU the engine should
	 * invest to keep this object from penetrating.
	 *             A good choice is 5% - 20% of the smallest diameter of the object.
	 */
	float penetrationDepth;
	/*! Motion system? Overrides Quality when on Keyframed? */
	MotionSystem motionSystem;
	/*! The initial deactivator type of the body. */
	DeactivatorType deactivatorType;
	/*!
	 * Usually set to 1 for fixed objects, or set to 2 for moving ones.  Seems to
	 * always be same as Unknown Byte 1.
	 */
	SolverDeactivation solverDeactivation;
	/*! The motion type. Determines quality of motion? */
	MotionQuality qualityType;
	/*! Unknown. */
	unsigned int unknownInt6;
	/*! Unknown. */
	unsigned int unknownInt7;
	/*! Unknown. */
	unsigned int unknownInt8;
	/*! Unknown. Skyrim only. */
	unsigned int unknownInt81;
	/*! The number of constraints this object is bound to. */
	mutable unsigned int numConstraints;
	/*! Unknown. */
	vector<Ref<bhkSerializable > > constraints;
	/*! 0 = do not respond to wind, 1 = respond to wind (?) */
	unsigned int unknownInt9;
	/*! Unknown. */
	unsigned short unknownInt91;
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
