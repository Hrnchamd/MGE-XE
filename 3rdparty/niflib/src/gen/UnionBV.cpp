/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/UnionBV.h"
#include "../../include/gen/BoundingVolume.h"
#include "../../include/gen/SphereBV.h"
#include "../../include/gen/BoxBV.h"
#include "../../include/gen/CapsuleBV.h"
#include "../../include/gen/HalfSpaceBV.h"
using namespace Niflib;

//Constructor
UnionBV::UnionBV() : numBv((unsigned int)0) {};

//Copy Constructor
UnionBV::UnionBV( const UnionBV & src ) {
	*this = src;
};

//Copy Operator
UnionBV & UnionBV::operator=( const UnionBV & src ) {
	this->numBv = src.numBv;
	this->boundingVolumes = src.boundingVolumes;
	return *this;
};

//Destructor
UnionBV::~UnionBV() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
