/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/OldSkinData.h"
using namespace Niflib;

//Constructor
OldSkinData::OldSkinData() : vertexWeight(0.0f), vertexIndex((unsigned short)0) {};

//Copy Constructor
OldSkinData::OldSkinData( const OldSkinData & src ) {
	*this = src;
};

//Copy Operator
OldSkinData & OldSkinData::operator=( const OldSkinData & src ) {
	this->vertexWeight = src.vertexWeight;
	this->vertexIndex = src.vertexIndex;
	this->unknownVector = src.unknownVector;
	return *this;
};

//Destructor
OldSkinData::~OldSkinData() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
