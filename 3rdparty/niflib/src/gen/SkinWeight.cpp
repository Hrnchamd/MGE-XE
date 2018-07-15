/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/SkinWeight.h"
using namespace Niflib;

//Constructor
SkinWeight::SkinWeight() : index((unsigned short)0), weight(0.0f) {};

//Copy Constructor
SkinWeight::SkinWeight( const SkinWeight & src ) {
	*this = src;
};

//Copy Operator
SkinWeight & SkinWeight::operator=( const SkinWeight & src ) {
	this->index = src.index;
	this->weight = src.weight;
	return *this;
};

//Destructor
SkinWeight::~SkinWeight() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
