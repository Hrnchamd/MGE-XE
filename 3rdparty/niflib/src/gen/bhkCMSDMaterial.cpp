/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/bhkCMSDMaterial.h"
using namespace Niflib;

//Constructor
bhkCMSDMaterial::bhkCMSDMaterial() : skyrimMaterial((SkyrimHavokMaterial)0), skyrimLayer((unsigned int)0) {};

//Copy Constructor
bhkCMSDMaterial::bhkCMSDMaterial( const bhkCMSDMaterial & src ) {
	*this = src;
};

//Copy Operator
bhkCMSDMaterial & bhkCMSDMaterial::operator=( const bhkCMSDMaterial & src ) {
	this->skyrimMaterial = src.skyrimMaterial;
	this->skyrimLayer = src.skyrimLayer;
	return *this;
};

//Destructor
bhkCMSDMaterial::~bhkCMSDMaterial() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
