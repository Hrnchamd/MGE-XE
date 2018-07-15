/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/BSTreadTransform.h"
#include "../../include/gen/BSTreadTransformData.h"
#include "../../include/gen/BSTreadTransformData.h"
using namespace Niflib;

//Constructor
BSTreadTransform::BSTreadTransform() {};

//Copy Constructor
BSTreadTransform::BSTreadTransform( const BSTreadTransform & src ) {
	*this = src;
};

//Copy Operator
BSTreadTransform & BSTreadTransform::operator=( const BSTreadTransform & src ) {
	this->name = src.name;
	this->transform1 = src.transform1;
	this->transform2 = src.transform2;
	return *this;
};

//Destructor
BSTreadTransform::~BSTreadTransform() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
