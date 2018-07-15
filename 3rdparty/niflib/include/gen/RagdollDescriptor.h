/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _RAGDOLLDESCRIPTOR_H_
#define _RAGDOLLDESCRIPTOR_H_

#include "../NIF_IO.h"

// Include structures
#include "MotorDescriptor.h"
namespace Niflib {


/*!
 * This constraint defines a cone in which an object can rotate. The shape of the
 * cone can be controlled in two (orthogonal) directions.
 */
struct RagdollDescriptor {
	/*! Default Constructor */
	NIFLIB_API RagdollDescriptor();
	/*! Default Destructor */
	NIFLIB_API ~RagdollDescriptor();
	/*! Copy Constructor */
	NIFLIB_API RagdollDescriptor( const RagdollDescriptor & src );
	/*! Copy Operator */
	NIFLIB_API RagdollDescriptor & operator=( const RagdollDescriptor & src );
	/*! The point where the constraint is attached to its parent rigidbody. */
	Vector4 pivotA;
	/*!
	 * Defines the orthogonal plane in which the body can move, the orthogonal
	 * directions in which the shape can be controlled (the direction orthogonal on
	 * this one and Twist A).
	 */
	Vector4 planeA;
	/*!
	 * Central directed axis of the cone in which the object can rotate. Orthogonal on
	 * Plane A.
	 */
	Vector4 twistA;
	/*! The point where the constraint is attached to the other rigidbody. */
	Vector4 pivotB;
	/*!
	 * Defines the orthogonal plane in which the shape can be controlled (the direction
	 * orthogonal on this one and Twist B).
	 */
	Vector4 planeB;
	/*!
	 * Central directed axis of the cone in which the object can rotate. Orthogonal on
	 * Plane B.
	 */
	Vector4 twistB;
	/*!
	 * Defines the orthogonal directions in which the shape can be controlled (namely
	 * in this direction, and in the direction orthogonal on this one and Twist A).
	 */
	Vector4 motorA;
	/*!
	 * Defines the orthogonal directions in which the shape can be controlled (namely
	 * in this direction, and in the direction orthogonal on this one and Twist A).
	 */
	Vector4 motorB;
	/*!
	 * Maximum angle the object can rotate around the vector orthogonal on Plane A and
	 * Twist A relative to the Twist A vector. Note that Cone Min Angle is not stored,
	 * but is simply minus this angle.
	 */
	float coneMaxAngle;
	/*! Minimum angle the object can rotate around Plane A, relative to Twist A. */
	float planeMinAngle;
	/*! Maximum angle the object can rotate around Plane A, relative to Twist A. */
	float planeMaxAngle;
	/*! Minimum angle the object can rotate around Twist A, relative to Plane A. */
	float twistMinAngle;
	/*! Maximum angle the object can rotate around Twist A, relative to Plane A. */
	float twistMaxAngle;
	/*! Maximum friction, typically 0 or 10. In Fallout 3, typically 100. */
	float maxFriction;
	/*! Unknown */
	bool enableMotor;
	/*! Unknown. */
	MotorDescriptor motor;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
