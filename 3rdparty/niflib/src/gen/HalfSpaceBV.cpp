/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/HalfSpaceBV.h"
using namespace Niflib;

//Constructor
HalfSpaceBV::HalfSpaceBV() {};

//Copy Constructor
HalfSpaceBV::HalfSpaceBV( const HalfSpaceBV & src ) {
	*this = src;
};

//Copy Operator
HalfSpaceBV & HalfSpaceBV::operator=( const HalfSpaceBV & src ) {
	this->normal = src.normal;
	this->center = src.center;
	return *this;
};

//Destructor
HalfSpaceBV::~HalfSpaceBV() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
