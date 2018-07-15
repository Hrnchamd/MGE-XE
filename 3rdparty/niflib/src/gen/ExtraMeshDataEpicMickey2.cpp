/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/ExtraMeshDataEpicMickey2.h"
using namespace Niflib;

//Constructor
ExtraMeshDataEpicMickey2::ExtraMeshDataEpicMickey2() : start((int)0), end((int)0) {};

//Copy Constructor
ExtraMeshDataEpicMickey2::ExtraMeshDataEpicMickey2( const ExtraMeshDataEpicMickey2 & src ) {
	*this = src;
};

//Copy Operator
ExtraMeshDataEpicMickey2 & ExtraMeshDataEpicMickey2::operator=( const ExtraMeshDataEpicMickey2 & src ) {
	this->start = src.start;
	this->end = src.end;
	this->unknownShorts = src.unknownShorts;
	return *this;
};

//Destructor
ExtraMeshDataEpicMickey2::~ExtraMeshDataEpicMickey2() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
