/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _PARTICLEDESC_H_
#define _PARTICLEDESC_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Particle Description. */
struct ParticleDesc {
	/*! Default Constructor */
	NIFLIB_API ParticleDesc();
	/*! Default Destructor */
	NIFLIB_API ~ParticleDesc();
	/*! Copy Constructor */
	NIFLIB_API ParticleDesc( const ParticleDesc & src );
	/*! Copy Operator */
	NIFLIB_API ParticleDesc & operator=( const ParticleDesc & src );
	/*! Unknown. */
	Vector3 translation;
	/*! Unknown. */
	array<3,float > unknownFloats1;
	/*! Unknown. */
	float unknownFloat1;
	/*! Unknown. */
	float unknownFloat2;
	/*! Unknown. */
	float unknownFloat3;
	/*! Unknown. */
	int unknownInt1;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
