/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/BSSegmentedTriangle.h"
using namespace Niflib;

//Constructor
BSSegmentedTriangle::BSSegmentedTriangle() : unknownInt1((int)0), unknownInt2((int)0), unknownByte1((byte)0) {};

//Copy Constructor
BSSegmentedTriangle::BSSegmentedTriangle( const BSSegmentedTriangle & src ) {
	*this = src;
};

//Copy Operator
BSSegmentedTriangle & BSSegmentedTriangle::operator=( const BSSegmentedTriangle & src ) {
	this->unknownInt1 = src.unknownInt1;
	this->unknownInt2 = src.unknownInt2;
	this->unknownByte1 = src.unknownByte1;
	return *this;
};

//Destructor
BSSegmentedTriangle::~BSSegmentedTriangle() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
