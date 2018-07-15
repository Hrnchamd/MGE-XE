/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/QuaternionXYZW.h"
using namespace Niflib;

//Constructor
QuaternionXYZW::QuaternionXYZW() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {};

//Copy Constructor
QuaternionXYZW::QuaternionXYZW( const QuaternionXYZW & src ) {
	*this = src;
};

//Copy Operator
QuaternionXYZW & QuaternionXYZW::operator=( const QuaternionXYZW & src ) {
	this->x = src.x;
	this->y = src.y;
	this->z = src.z;
	this->w = src.w;
	return *this;
};

//Destructor
QuaternionXYZW::~QuaternionXYZW() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
