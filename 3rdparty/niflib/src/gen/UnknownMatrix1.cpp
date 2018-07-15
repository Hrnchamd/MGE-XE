/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/UnknownMatrix1.h"
using namespace Niflib;

//Constructor
UnknownMatrix1::UnknownMatrix1() : unknownUint1((unsigned int)0), m11(0.0f), m12(0.0f), m13(0.0f), m21(0.0f), m22(0.0f), m23(0.0f), m31(0.0f), m32(0.0f), m33(0.0f) {};

//Copy Constructor
UnknownMatrix1::UnknownMatrix1( const UnknownMatrix1 & src ) {
	*this = src;
};

//Copy Operator
UnknownMatrix1 & UnknownMatrix1::operator=( const UnknownMatrix1 & src ) {
	this->unknownUint1 = src.unknownUint1;
	this->m11 = src.m11;
	this->m12 = src.m12;
	this->m13 = src.m13;
	this->m21 = src.m21;
	this->m22 = src.m22;
	this->m23 = src.m23;
	this->m31 = src.m31;
	this->m32 = src.m32;
	this->m33 = src.m33;
	return *this;
};

//Destructor
UnknownMatrix1::~UnknownMatrix1() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
