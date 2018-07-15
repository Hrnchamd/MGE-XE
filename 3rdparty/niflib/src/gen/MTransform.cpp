/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/MTransform.h"
using namespace Niflib;

//Constructor
MTransform::MTransform() : scale(1.0f) {};

//Copy Constructor
MTransform::MTransform( const MTransform & src ) {
	*this = src;
};

//Copy Operator
MTransform & MTransform::operator=( const MTransform & src ) {
	this->translation = src.translation;
	this->rotation = src.rotation;
	this->scale = src.scale;
	return *this;
};

//Destructor
MTransform::~MTransform() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
