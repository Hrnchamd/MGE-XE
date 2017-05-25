/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _LIMITEDHINGEDESCRIPTOR_H_
#define _LIMITEDHINGEDESCRIPTOR_H_

#include "../NIF_IO.h"

namespace Niflib {


/*!  */
struct LimitedHingeDescriptor {
	/*! Default Constructor */
	NIFLIB_API LimitedHingeDescriptor();
	/*! Default Destructor */
	NIFLIB_API ~LimitedHingeDescriptor();
	/*! Copy Constructor */
	NIFLIB_API LimitedHingeDescriptor( const LimitedHingeDescriptor & src );
	/*! Copy Operator */
	NIFLIB_API LimitedHingeDescriptor & operator=( const LimitedHingeDescriptor & src );
	/*! Unknown. */
	Float4 pivotA;
	/*! Unknown. */
	Float4 axleA;
	/*! Unknown. */
	Float4 perp2axleina1;
	/*! Unknown. */
	Float4 perp2axleina2;
	/*! Unknown. */
	Float4 pivotB;
	/*! Unknown. */
	Float4 axleB;
	/*! Unknown. */
	Float4 perp2axleinb2;
	/*! Unknown. */
	float minAngle;
	/*! Unknown. */
	float maxAngle;
	/*! Unknown. */
	float maxFriction;
};

}
#endif
