/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/DecalVectorArray.h"
using namespace Niflib;

//Constructor
DecalVectorArray::DecalVectorArray() : numVectors((short)0) {};

//Copy Constructor
DecalVectorArray::DecalVectorArray( const DecalVectorArray & src ) {
	*this = src;
};

//Copy Operator
DecalVectorArray & DecalVectorArray::operator=( const DecalVectorArray & src ) {
	this->numVectors = src.numVectors;
	this->points = src.points;
	this->normals = src.normals;
	return *this;
};

//Destructor
DecalVectorArray::~DecalVectorArray() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
