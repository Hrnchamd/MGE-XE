/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/BSSegment.h"
using namespace Niflib;

//Constructor
BSSegment::BSSegment() : internalIndex((int)0), flags((BSSegmentFlags)0), unknownByte1((byte)0) {};

//Copy Constructor
BSSegment::BSSegment( const BSSegment & src ) {
	*this = src;
};

//Copy Operator
BSSegment & BSSegment::operator=( const BSSegment & src ) {
	this->internalIndex = src.internalIndex;
	this->flags = src.flags;
	this->unknownByte1 = src.unknownByte1;
	return *this;
};

//Destructor
BSSegment::~BSSegment() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
