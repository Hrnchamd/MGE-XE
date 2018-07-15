/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/TBC.h"
using namespace Niflib;

//Constructor
TBC::TBC() : t(0.0f), b(0.0f), c(0.0f) {};

//Copy Constructor
TBC::TBC( const TBC & src ) {
	*this = src;
};

//Copy Operator
TBC & TBC::operator=( const TBC & src ) {
	this->t = src.t;
	this->b = src.b;
	this->c = src.c;
	return *this;
};

//Destructor
TBC::~TBC() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
