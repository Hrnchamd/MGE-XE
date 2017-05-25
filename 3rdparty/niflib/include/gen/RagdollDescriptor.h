/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _RAGDOLLDESCRIPTOR_H_
#define _RAGDOLLDESCRIPTOR_H_

#include "../NIF_IO.h"

namespace Niflib {


/*!  */
struct RagdollDescriptor {
	/*! Default Constructor */
	NIFLIB_API RagdollDescriptor();
	/*! Default Destructor */
	NIFLIB_API ~RagdollDescriptor();
	/*! Copy Constructor */
	NIFLIB_API RagdollDescriptor( const RagdollDescriptor & src );
	/*! Copy Operator */
	NIFLIB_API RagdollDescriptor & operator=( const RagdollDescriptor & src );
	/*! Unknown. */
	Float4 pivotA;
	/*! Unknown. */
	Float4 planeA;
	/*! Unknown. */
	Float4 twistA;
	/*! Unknown. */
	Float4 pivotB;
	/*! Unknown. */
	Float4 planeB;
	/*! Unknown. */
	Float4 twistB;
	/*! Unknown. */
	float coneMinAngle;
	/*! Unknown. */
	float planeMinAngle;
	/*! Unknown. */
	float planeMaxAngle;
	/*! Unknown. */
	float twistMinAngle;
	/*! Unknown. */
	float twistMaxAngle;
	/*! Unknown. */
	float maxFriction;
};

}
#endif
