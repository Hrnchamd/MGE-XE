/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/BSTreadTransformData.h"
using namespace Niflib;

//Constructor
BSTreadTransformData::BSTreadTransformData() : scale(0.0f) {};

//Copy Constructor
BSTreadTransformData::BSTreadTransformData( const BSTreadTransformData & src ) {
	*this = src;
};

//Copy Operator
BSTreadTransformData & BSTreadTransformData::operator=( const BSTreadTransformData & src ) {
	this->translation = src.translation;
	this->rotation = src.rotation;
	this->scale = src.scale;
	return *this;
};

//Destructor
BSTreadTransformData::~BSTreadTransformData() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
