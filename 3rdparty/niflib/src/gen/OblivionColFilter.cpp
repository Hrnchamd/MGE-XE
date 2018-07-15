/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/OblivionColFilter.h"
using namespace Niflib;

//Constructor
OblivionColFilter::OblivionColFilter() : layer((OblivionLayer)0), colFilter((byte)0), unknownShort((unsigned short)0) {};

//Copy Constructor
OblivionColFilter::OblivionColFilter( const OblivionColFilter & src ) {
	*this = src;
};

//Copy Operator
OblivionColFilter & OblivionColFilter::operator=( const OblivionColFilter & src ) {
	this->layer = src.layer;
	this->colFilter = src.colFilter;
	this->unknownShort = src.unknownShort;
	return *this;
};

//Destructor
OblivionColFilter::~OblivionColFilter() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
