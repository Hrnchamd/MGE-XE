/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/BoneLOD.h"
using namespace Niflib;

//Constructor
BoneLOD::BoneLOD() : distance((unsigned int)0) {};

//Copy Constructor
BoneLOD::BoneLOD( const BoneLOD & src ) {
	*this = src;
};

//Copy Operator
BoneLOD & BoneLOD::operator=( const BoneLOD & src ) {
	this->distance = src.distance;
	this->boneName = src.boneName;
	return *this;
};

//Destructor
BoneLOD::~BoneLOD() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
