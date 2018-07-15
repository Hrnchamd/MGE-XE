/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/SkinTransform.h"
using namespace Niflib;

//Constructor
SkinTransform::SkinTransform() : scale(1.0f) {};

//Copy Constructor
SkinTransform::SkinTransform( const SkinTransform & src ) {
	*this = src;
};

//Copy Operator
SkinTransform & SkinTransform::operator=( const SkinTransform & src ) {
	this->rotation = src.rotation;
	this->translation = src.translation;
	this->scale = src.scale;
	return *this;
};

//Destructor
SkinTransform::~SkinTransform() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
