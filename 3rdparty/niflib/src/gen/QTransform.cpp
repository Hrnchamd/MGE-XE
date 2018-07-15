/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/QTransform.h"
using namespace Niflib;

//Constructor
QTransform::QTransform() : scale(1.0f) {};

//Copy Constructor
QTransform::QTransform( const QTransform & src ) {
	*this = src;
};

//Copy Operator
QTransform & QTransform::operator=( const QTransform & src ) {
	this->translation = src.translation;
	this->rotation = src.rotation;
	this->scale = src.scale;
	return *this;
};

//Destructor
QTransform::~QTransform() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
