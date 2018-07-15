/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/MorphWeight.h"
#include "../../include/obj/NiInterpolator.h"
using namespace Niflib;

//Constructor
MorphWeight::MorphWeight() : interpolator(NULL), weight_(0.0f) {};

//Copy Constructor
MorphWeight::MorphWeight( const MorphWeight & src ) {
	*this = src;
};

//Copy Operator
MorphWeight & MorphWeight::operator=( const MorphWeight & src ) {
	this->interpolator = src.interpolator;
	this->weight_ = src.weight_;
	return *this;
};

//Destructor
MorphWeight::~MorphWeight() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
