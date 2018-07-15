/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/LimitedHingeDescriptor.h"
#include "../../include/gen/MotorDescriptor.h"
using namespace Niflib;

//Constructor
LimitedHingeDescriptor::LimitedHingeDescriptor() : minAngle(0.0f), maxAngle(0.0f), maxFriction(0.0f), enableMotor(false) {};

//Copy Constructor
LimitedHingeDescriptor::LimitedHingeDescriptor( const LimitedHingeDescriptor & src ) {
	*this = src;
};

//Copy Operator
LimitedHingeDescriptor & LimitedHingeDescriptor::operator=( const LimitedHingeDescriptor & src ) {
	this->pivotA = src.pivotA;
	this->axleA = src.axleA;
	this->perp2AxleInA1 = src.perp2AxleInA1;
	this->perp2AxleInA2 = src.perp2AxleInA2;
	this->pivotB = src.pivotB;
	this->axleB = src.axleB;
	this->perp2AxleInB2 = src.perp2AxleInB2;
	this->perp2AxleInB1 = src.perp2AxleInB1;
	this->minAngle = src.minAngle;
	this->maxAngle = src.maxAngle;
	this->maxFriction = src.maxFriction;
	this->enableMotor = src.enableMotor;
	this->motor = src.motor;
	return *this;
};

//Destructor
LimitedHingeDescriptor::~LimitedHingeDescriptor() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
