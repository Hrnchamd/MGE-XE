/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/BodyPartList.h"
using namespace Niflib;

//Constructor
BodyPartList::BodyPartList() : partFlag((BSPartFlag)257), bodyPart((BSDismemberBodyPartType)0) {};

//Copy Constructor
BodyPartList::BodyPartList( const BodyPartList & src ) {
	*this = src;
};

//Copy Operator
BodyPartList & BodyPartList::operator=( const BodyPartList & src ) {
	this->partFlag = src.partFlag;
	this->bodyPart = src.bodyPart;
	return *this;
};

//Destructor
BodyPartList::~BodyPartList() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
