/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! particle array entry */
struct Particle {
	/*! Default Constructor */
	NIFLIB_API Particle();
	/*! Default Destructor */
	NIFLIB_API ~Particle();
	/*! Copy Constructor */
	NIFLIB_API Particle( const Particle & src );
	/*! Copy Operator */
	NIFLIB_API Particle & operator=( const Particle & src );
	/*! Particle velocity */
	Vector3 velocity;
	/*! Unknown */
	Vector3 unknownVector;
	/*! The particle's age. */
	float lifetime;
	/*! Maximum age of the particle. */
	float lifespan;
	/*! Timestamp of the last update. */
	float timestamp;
	/*! Unknown short */
	unsigned short unknownShort;
	/*! Particle/vertex index matches array index */
	unsigned short vertexId;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
