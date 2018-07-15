/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _HINGEDESCRIPTOR_H_
#define _HINGEDESCRIPTOR_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! This constraint allows rotation about a specified axis. */
struct HingeDescriptor {
	/*! Default Constructor */
	NIFLIB_API HingeDescriptor();
	/*! Default Destructor */
	NIFLIB_API ~HingeDescriptor();
	/*! Copy Constructor */
	NIFLIB_API HingeDescriptor( const HingeDescriptor & src );
	/*! Copy Operator */
	NIFLIB_API HingeDescriptor & operator=( const HingeDescriptor & src );
	/*! Pivot point around which the object will rotate. */
	Vector4 pivotA;
	/*! Vector in the rotation plane which defines the zero angle. */
	Vector4 perp2AxleInA1;
	/*!
	 * Vector in the rotation plane, orthogonal on the previous one, which defines the
	 * positive direction of rotation.
	 */
	Vector4 perp2AxleInA2;
	/*! Pivot A in second entity coordinate system. */
	Vector4 pivotB;
	/*! Axle A (vector orthogonal on Perp2 Axles) in second entity coordinate system. */
	Vector4 axleB;
	/*! Axis of rotation. */
	Vector4 axleA;
	/*! Perp2 Axle In A1 in second entity coordinate system. */
	Vector4 perp2AxleInB1;
	/*! Perp2 Axle In A2 in second entity coordinate system. */
	Vector4 perp2AxleInB2;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
