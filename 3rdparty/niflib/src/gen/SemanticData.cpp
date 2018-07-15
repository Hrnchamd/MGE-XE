/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/SemanticData.h"
using namespace Niflib;

//Constructor
SemanticData::SemanticData() : index((unsigned int)0) {};

//Copy Constructor
SemanticData::SemanticData( const SemanticData & src ) {
	*this = src;
};

//Copy Operator
SemanticData & SemanticData::operator=( const SemanticData & src ) {
	this->name = src.name;
	this->index = src.index;
	return *this;
};

//Destructor
SemanticData::~SemanticData() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
