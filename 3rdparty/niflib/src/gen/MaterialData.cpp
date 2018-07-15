/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/MaterialData.h"
using namespace Niflib;

//Constructor
MaterialData::MaterialData() : materialExtraData((unsigned int)0) {};

//Copy Constructor
MaterialData::MaterialData( const MaterialData & src ) {
	*this = src;
};

//Copy Operator
MaterialData & MaterialData::operator=( const MaterialData & src ) {
	this->materialName = src.materialName;
	this->materialExtraData = src.materialExtraData;
	return *this;
};

//Destructor
MaterialData::~MaterialData() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
