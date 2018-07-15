/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _LIMITEDHINGEDESCRIPTOR_H_
#define _LIMITEDHINGEDESCRIPTOR_H_

#include "../NIF_IO.h"

// Include structures
#include "MotorDescriptor.h"
namespace Niflib {


/*!
 * This constraint allows rotation about a specified axis, limited by specified
 * boundaries.
 */
struct LimitedHingeDescriptor {
	/*! Default Constructor */
	NIFLIB_API LimitedHingeDescriptor();
	/*! Default Destructor */
	NIFLIB_API ~LimitedHingeDescriptor();
	/*! Copy Constructor */
	NIFLIB_API LimitedHingeDescriptor( const LimitedHingeDescriptor & src );
	/*! Copy Operator */
	NIFLIB_API LimitedHingeDescriptor & operator=( const LimitedHingeDescriptor & src );
	/*! Pivot point around which the object will rotate. */
	Vector4 pivotA;
	/*! Axis of rotation. */
	Vector4 axleA;
	/*! Vector in the rotation plane which defines the zero angle. */
	Vector4 perp2AxleInA1;
	/*!
	 * Vector in the rotation plane, orthogonal on the previous one, which defines the
	 * positive direction of rotation. This is always the vector product of Axle A and
	 * Perp2 Axle In A1.
	 */
	Vector4 perp2AxleInA2;
	/*! Pivot A in second entity coordinate system. */
	Vector4 pivotB;
	/*! Axle A in second entity coordinate system. */
	Vector4 axleB;
	/*! Perp2 Axle In A2 in second entity coordinate system. */
	Vector4 perp2AxleInB2;
	/*! Perp2 Axle In A1 in second entity coordinate system. */
	Vector4 perp2AxleInB1;
	/*! Minimum rotation angle. */
	float minAngle;
	/*! Maximum rotation angle. */
	float maxAngle;
	/*! Maximum friction, typically either 0 or 10. In Fallout 3, typically 100. */
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
