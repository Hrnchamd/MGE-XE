/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/SkinShape.h"
#include "../../include/obj/NiSkinInstance.h"
#include "../../include/obj/NiTriBasedGeom.h"
using namespace Niflib;

//Constructor
SkinShape::SkinShape() : shape(NULL), skinInstance(NULL) {};

//Copy Constructor
SkinShape::SkinShape( const SkinShape & src ) {
	*this = src;
};

//Copy Operator
SkinShape & SkinShape::operator=( const SkinShape & src ) {
	this->shape = src.shape;
	this->skinInstance = src.skinInstance;
	return *this;
};

//Destructor
SkinShape::~SkinShape() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
