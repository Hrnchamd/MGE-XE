/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/CapsuleBV.h"
using namespace Niflib;

//Constructor
CapsuleBV::CapsuleBV() : unknownFloat1(0.0f), unknownFloat2(0.0f) {};

//Copy Constructor
CapsuleBV::CapsuleBV( const CapsuleBV & src ) {
	*this = src;
};

//Copy Operator
CapsuleBV & CapsuleBV::operator=( const CapsuleBV & src ) {
	this->center = src.center;
	this->origin = src.origin;
	this->unknownFloat1 = src.unknownFloat1;
	this->unknownFloat2 = src.unknownFloat2;
	return *this;
};

//Destructor
CapsuleBV::~CapsuleBV() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
