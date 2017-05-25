/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/MultiTextureElement.h"
#include "../../include/obj/NiImage.h"
using namespace Niflib;

//Constructor
MultiTextureElement::MultiTextureElement() : hasImage(false), image(NULL), unknownInt1((unsigned int)3), unknownInt2((unsigned int)2), unknownInt3((unsigned int)1), unknownShort1((short)0), unknownShort2((short)-75), unknownShort3((short)0) {};

//Copy Constructor
MultiTextureElement::MultiTextureElement( const MultiTextureElement & src ) {
	*this = src;
};

//Copy Operator
MultiTextureElement & MultiTextureElement::operator=( const MultiTextureElement & src ) {
	this->hasImage = src.hasImage;
	this->image = src.image;
	this->unknownInt1 = src.unknownInt1;
	this->unknownInt2 = src.unknownInt2;
	this->unknownInt3 = src.unknownInt3;
	this->unknownShort1 = src.unknownShort1;
	this->unknownShort2 = src.unknownShort2;
	this->unknownShort3 = src.unknownShort3;
	return *this;
};

//Destructor
MultiTextureElement::~MultiTextureElement() {};
