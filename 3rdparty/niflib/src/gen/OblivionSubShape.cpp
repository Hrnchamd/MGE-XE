/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/OblivionSubShape.h"
using namespace Niflib;

//Constructor
OblivionSubShape::OblivionSubShape() : layer((OblivionLayer)0), colFilter((byte)0), unknownShort((unsigned short)0), numVertices((unsigned int)0), material((HavokMaterial)0) {};

//Copy Constructor
OblivionSubShape::OblivionSubShape( const OblivionSubShape & src ) {
	*this = src;
};

//Copy Operator
OblivionSubShape & OblivionSubShape::operator=( const OblivionSubShape & src ) {
	this->layer = src.layer;
	this->colFilter = src.colFilter;
	this->unknownShort = src.unknownShort;
	this->numVertices = src.numVertices;
	this->material = src.material;
	return *this;
};

//Destructor
OblivionSubShape::~OblivionSubShape() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
