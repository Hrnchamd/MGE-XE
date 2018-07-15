/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/ParticleDesc.h"
using namespace Niflib;

//Constructor
ParticleDesc::ParticleDesc() : unknownFloat1(0.9f), unknownFloat2(0.9f), unknownFloat3(3.0f), unknownInt1((int)0) {};

//Copy Constructor
ParticleDesc::ParticleDesc( const ParticleDesc & src ) {
	*this = src;
};

//Copy Operator
ParticleDesc & ParticleDesc::operator=( const ParticleDesc & src ) {
	this->translation = src.translation;
	this->unknownFloats1 = src.unknownFloats1;
	this->unknownFloat1 = src.unknownFloat1;
	this->unknownFloat2 = src.unknownFloat2;
	this->unknownFloat3 = src.unknownFloat3;
	this->unknownInt1 = src.unknownInt1;
	return *this;
};

//Destructor
ParticleDesc::~ParticleDesc() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
