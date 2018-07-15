/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/HingeDescriptor.h"
using namespace Niflib;

//Constructor
HingeDescriptor::HingeDescriptor() {};

//Copy Constructor
HingeDescriptor::HingeDescriptor( const HingeDescriptor & src ) {
	*this = src;
};

//Copy Operator
HingeDescriptor & HingeDescriptor::operator=( const HingeDescriptor & src ) {
	this->pivotA = src.pivotA;
	this->perp2AxleInA1 = src.perp2AxleInA1;
	this->perp2AxleInA2 = src.perp2AxleInA2;
	this->pivotB = src.pivotB;
	this->axleB = src.axleB;
	this->axleA = src.axleA;
	this->perp2AxleInB1 = src.perp2AxleInB1;
	this->perp2AxleInB2 = src.perp2AxleInB2;
	return *this;
};

//Destructor
HingeDescriptor::~HingeDescriptor() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
