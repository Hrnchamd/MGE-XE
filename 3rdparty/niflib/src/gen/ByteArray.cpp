/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/ByteArray.h"
using namespace Niflib;

//Constructor
ByteArray::ByteArray() : dataSize((unsigned int)0) {};

//Copy Constructor
ByteArray::ByteArray( const ByteArray & src ) {
	*this = src;
};

//Copy Operator
ByteArray & ByteArray::operator=( const ByteArray & src ) {
	this->dataSize = src.dataSize;
	this->data = src.data;
	return *this;
};

//Destructor
ByteArray::~ByteArray() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
