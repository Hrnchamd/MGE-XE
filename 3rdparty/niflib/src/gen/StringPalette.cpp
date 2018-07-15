/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/StringPalette.h"
using namespace Niflib;

//Constructor
StringPalette::StringPalette() : length((unsigned int)0) {};

//Copy Constructor
StringPalette::StringPalette( const StringPalette & src ) {
	*this = src;
};

//Copy Operator
StringPalette & StringPalette::operator=( const StringPalette & src ) {
	this->palette = src.palette;
	this->length = src.length;
	return *this;
};

//Destructor
StringPalette::~StringPalette() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
