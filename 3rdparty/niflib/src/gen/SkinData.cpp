/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/SkinData.h"
#include "../../include/gen/SkinWeight.h"
#include "../../include/gen/SkinWeight.h"
using namespace Niflib;

//Constructor
SkinData::SkinData() : scale(0.0f), boundingSphereRadius(0.0f), numVertices((unsigned short)0) {};

//Copy Constructor
SkinData::SkinData( const SkinData & src ) {
	*this = src;
};

//Copy Operator
SkinData & SkinData::operator=( const SkinData & src ) {
	this->rotation = src.rotation;
	this->translation = src.translation;
	this->scale = src.scale;
	this->boundingSphereOffset = src.boundingSphereOffset;
	this->boundingSphereRadius = src.boundingSphereRadius;
	this->numVertices = src.numVertices;
	this->vertexWeights = src.vertexWeights;
	return *this;
};

//Destructor
SkinData::~SkinData() {};
