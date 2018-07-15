/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _MOTORDESCRIPTOR_H_
#define _MOTORDESCRIPTOR_H_

#include "../NIF_IO.h"

namespace Niflib {


/*!  */
struct MotorDescriptor {
	/*! Default Constructor */
	NIFLIB_API MotorDescriptor();
	/*! Default Destructor */
	NIFLIB_API ~MotorDescriptor();
	/*! Copy Constructor */
	NIFLIB_API MotorDescriptor( const MotorDescriptor & src );
	/*! Copy Operator */
	NIFLIB_API MotorDescriptor & operator=( const MotorDescriptor & src );
	/*! Unknown */
	float unknownFloat1;
	/*! Unknown */
	float unknownFloat2;
	/*! Unknown */
	float unknownFloat3;
	/*! Unknown */
	float unknownFloat4;
	/*! Unknown */
	float unknownFloat5;
	/*! Unknown */
	float unknownFloat6;
	/*! Unknown */
	byte unknownByte1;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
