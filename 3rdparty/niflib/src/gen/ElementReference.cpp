/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/ElementReference.h"
#include "../../include/gen/SemanticData.h"
using namespace Niflib;

//Constructor
ElementReference::ElementReference() : normalizeFlag((unsigned int)0) {};

//Copy Constructor
ElementReference::ElementReference( const ElementReference & src ) {
	*this = src;
};

//Copy Operator
ElementReference & ElementReference::operator=( const ElementReference & src ) {
	this->semantic = src.semantic;
	this->normalizeFlag = src.normalizeFlag;
	return *this;
};

//Destructor
ElementReference::~ElementReference() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
