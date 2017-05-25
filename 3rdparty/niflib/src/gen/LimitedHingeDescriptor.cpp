/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/LimitedHingeDescriptor.h"
using namespace Niflib;

//Constructor
LimitedHingeDescriptor::LimitedHingeDescriptor() : minAngle(0.0f), maxAngle(0.0f), maxFriction(0.0f) {};

//Copy Constructor
LimitedHingeDescriptor::LimitedHingeDescriptor( const LimitedHingeDescriptor & src ) {
	*this = src;
};

//Copy Operator
LimitedHingeDescriptor & LimitedHingeDescriptor::operator=( const LimitedHingeDescriptor & src ) {
	this->pivotA = src.pivotA;
	this->axleA = src.axleA;
	this->perp2axleina1 = src.perp2axleina1;
	this->perp2axleina2 = src.perp2axleina2;
	this->pivotB = src.pivotB;
	this->axleB = src.axleB;
	this->perp2axleinb2 = src.perp2axleinb2;
	this->minAngle = src.minAngle;
	this->maxAngle = src.maxAngle;
	this->maxFriction = src.maxFriction;
	return *this;
};

//Destructor
LimitedHingeDescriptor::~LimitedHingeDescriptor() {};
