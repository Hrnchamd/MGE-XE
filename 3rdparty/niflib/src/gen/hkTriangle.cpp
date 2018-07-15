/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/hkTriangle.h"
using namespace Niflib;

//Constructor
hkTriangle::hkTriangle() : weldingInfo((unsigned short)0) {};

//Copy Constructor
hkTriangle::hkTriangle( const hkTriangle & src ) {
	*this = src;
};

//Copy Operator
hkTriangle & hkTriangle::operator=( const hkTriangle & src ) {
	this->triangle = src.triangle;
	this->weldingInfo = src.weldingInfo;
	this->normal = src.normal;
	return *this;
};

//Destructor
hkTriangle::~hkTriangle() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
