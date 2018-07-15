/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/physXMaterialRef.h"
#include "../../include/obj/NiPhysXMaterialDesc.h"
using namespace Niflib;

//Constructor
physXMaterialRef::physXMaterialRef() : number((byte)0), unknownByte1((byte)0), materialDesc(NULL) {};

//Copy Constructor
physXMaterialRef::physXMaterialRef( const physXMaterialRef & src ) {
	*this = src;
};

//Copy Operator
physXMaterialRef & physXMaterialRef::operator=( const physXMaterialRef & src ) {
	this->number = src.number;
	this->unknownByte1 = src.unknownByte1;
	this->materialDesc = src.materialDesc;
	return *this;
};

//Destructor
physXMaterialRef::~physXMaterialRef() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
