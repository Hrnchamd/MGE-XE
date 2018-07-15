/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/bhkCMSDTransform.h"
#include "../../include/gen/QuaternionXYZW.h"
using namespace Niflib;

//Constructor
bhkCMSDTransform::bhkCMSDTransform() {};

//Copy Constructor
bhkCMSDTransform::bhkCMSDTransform( const bhkCMSDTransform & src ) {
	*this = src;
};

//Copy Operator
bhkCMSDTransform & bhkCMSDTransform::operator=( const bhkCMSDTransform & src ) {
	this->translation = src.translation;
	this->rotation = src.rotation;
	return *this;
};

//Destructor
bhkCMSDTransform::~bhkCMSDTransform() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
