/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/bhkCMSDData.h"
using namespace Niflib;

//Constructor
bhkCMSDData::bhkCMSDData() : unknownInt1((unsigned int)0) {};

//Copy Constructor
bhkCMSDData::bhkCMSDData( const bhkCMSDData & src ) {
	*this = src;
};

//Copy Operator
bhkCMSDData & bhkCMSDData::operator=( const bhkCMSDData & src ) {
	this->unknownFloats1 = src.unknownFloats1;
	this->unknownInt1 = src.unknownInt1;
	return *this;
};

//Destructor
bhkCMSDData::~bhkCMSDData() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
