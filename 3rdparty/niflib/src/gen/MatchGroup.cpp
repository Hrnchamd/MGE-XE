/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/MatchGroup.h"
using namespace Niflib;

//Constructor
MatchGroup::MatchGroup() : numVertices((unsigned short)0) {};

//Copy Constructor
MatchGroup::MatchGroup( const MatchGroup & src ) {
	*this = src;
};

//Copy Operator
MatchGroup & MatchGroup::operator=( const MatchGroup & src ) {
	this->numVertices = src.numVertices;
	this->vertexIndices = src.vertexIndices;
	return *this;
};

//Destructor
MatchGroup::~MatchGroup() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
