/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/Region.h"
using namespace Niflib;

//Constructor
Region::Region() : startIndex((unsigned int)0), numIndices((unsigned int)0) {};

//Copy Constructor
Region::Region( const Region & src ) {
	*this = src;
};

//Copy Operator
Region & Region::operator=( const Region & src ) {
	this->startIndex = src.startIndex;
	this->numIndices = src.numIndices;
	return *this;
};

//Destructor
Region::~Region() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
