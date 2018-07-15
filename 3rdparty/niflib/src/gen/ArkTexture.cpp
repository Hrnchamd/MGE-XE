/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/ArkTexture.h"
#include "../../include/obj/NiTexturingProperty.h"
using namespace Niflib;

//Constructor
ArkTexture::ArkTexture() : unknownInt3((int)0), unknownInt4((int)0), texturingProperty(NULL) {};

//Copy Constructor
ArkTexture::ArkTexture( const ArkTexture & src ) {
	*this = src;
};

//Copy Operator
ArkTexture & ArkTexture::operator=( const ArkTexture & src ) {
	this->textureName = src.textureName;
	this->unknownInt3 = src.unknownInt3;
	this->unknownInt4 = src.unknownInt4;
	this->texturingProperty = src.texturingProperty;
	this->unknownBytes = src.unknownBytes;
	return *this;
};

//Destructor
ArkTexture::~ArkTexture() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
