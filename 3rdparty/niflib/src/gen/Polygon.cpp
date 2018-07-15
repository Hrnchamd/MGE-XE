/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/Polygon.h"
using namespace Niflib;

//Constructor
Polygon::Polygon() : numVertices((unsigned short)0), vertexOffset((unsigned short)0), numTriangles((unsigned short)0), triangleOffset((unsigned short)0) {};

//Copy Constructor
Polygon::Polygon( const Polygon & src ) {
	*this = src;
};

//Copy Operator
Polygon & Polygon::operator=( const Polygon & src ) {
	this->numVertices = src.numVertices;
	this->vertexOffset = src.vertexOffset;
	this->numTriangles = src.numTriangles;
	this->triangleOffset = src.triangleOffset;
	return *this;
};

//Destructor
Polygon::~Polygon() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
