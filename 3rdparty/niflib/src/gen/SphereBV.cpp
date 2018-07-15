/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/SphereBV.h"
using namespace Niflib;

//Constructor
SphereBV::SphereBV() : radius(0.0f) {};

//Copy Constructor
SphereBV::SphereBV( const SphereBV & src ) {
	*this = src;
};

//Copy Operator
SphereBV & SphereBV::operator=( const SphereBV & src ) {
	this->center = src.center;
	this->radius = src.radius;
	return *this;
};

//Destructor
SphereBV::~SphereBV() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
