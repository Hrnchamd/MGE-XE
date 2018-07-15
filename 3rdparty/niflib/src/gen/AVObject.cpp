/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/AVObject.h"
#include "../../include/obj/NiAVObject.h"
using namespace Niflib;

//Constructor
AVObject::AVObject() : avObject(NULL) {};

//Copy Constructor
AVObject::AVObject( const AVObject & src ) {
	*this = src;
};

//Copy Operator
AVObject & AVObject::operator=( const AVObject & src ) {
	this->name = src.name;
	this->avObject = src.avObject;
	return *this;
};

//Destructor
AVObject::~AVObject() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
