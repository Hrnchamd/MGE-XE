/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/BoxBV.h"
using namespace Niflib;

//Constructor
BoxBV::BoxBV() {};

//Copy Constructor
BoxBV::BoxBV( const BoxBV & src ) {
	*this = src;
};

//Copy Operator
BoxBV & BoxBV::operator=( const BoxBV & src ) {
	this->center = src.center;
	this->axis = src.axis;
	this->extent = src.extent;
	return *this;
};

//Destructor
BoxBV::~BoxBV() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
