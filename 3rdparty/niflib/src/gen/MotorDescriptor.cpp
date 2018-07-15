/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/MotorDescriptor.h"
using namespace Niflib;

//Constructor
MotorDescriptor::MotorDescriptor() : unknownFloat1(-1000000.0f), unknownFloat2(1000000.0f), unknownFloat3(0.8f), unknownFloat4(1.0f), unknownFloat5(2.0f), unknownFloat6(1.0f), unknownByte1((byte)0) {};

//Copy Constructor
MotorDescriptor::MotorDescriptor( const MotorDescriptor & src ) {
	*this = src;
};

//Copy Operator
MotorDescriptor & MotorDescriptor::operator=( const MotorDescriptor & src ) {
	this->unknownFloat1 = src.unknownFloat1;
	this->unknownFloat2 = src.unknownFloat2;
	this->unknownFloat3 = src.unknownFloat3;
	this->unknownFloat4 = src.unknownFloat4;
	this->unknownFloat5 = src.unknownFloat5;
	this->unknownFloat6 = src.unknownFloat6;
	this->unknownByte1 = src.unknownByte1;
	return *this;
};

//Destructor
MotorDescriptor::~MotorDescriptor() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
