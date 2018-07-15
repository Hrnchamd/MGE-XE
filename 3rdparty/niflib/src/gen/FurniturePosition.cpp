/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/FurniturePosition.h"
using namespace Niflib;

//Constructor
FurniturePosition::FurniturePosition() : orientation((unsigned short)0), positionRef1((byte)0), positionRef2((byte)0), heading(0.0f), animationType((AnimationType)0), entryProperties((FurnitureEntryPoints)0) {};

//Copy Constructor
FurniturePosition::FurniturePosition( const FurniturePosition & src ) {
	*this = src;
};

//Copy Operator
FurniturePosition & FurniturePosition::operator=( const FurniturePosition & src ) {
	this->offset = src.offset;
	this->orientation = src.orientation;
	this->positionRef1 = src.positionRef1;
	this->positionRef2 = src.positionRef2;
	this->heading = src.heading;
	this->animationType = src.animationType;
	this->entryProperties = src.entryProperties;
	return *this;
};

//Destructor
FurniturePosition::~FurniturePosition() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
