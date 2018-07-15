/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/BSTreadTransfInfo.h"
#include "../../include/gen/BSTreadTransfSubInfo.h"
using namespace Niflib;

//Constructor
BSTreadTransfInfo::BSTreadTransfInfo() : unknownFloat1(0.0f) {};

//Copy Constructor
BSTreadTransfInfo::BSTreadTransfInfo( const BSTreadTransfInfo & src ) {
	*this = src;
};

//Copy Operator
BSTreadTransfInfo & BSTreadTransfInfo::operator=( const BSTreadTransfInfo & src ) {
	this->unknownFloat1 = src.unknownFloat1;
	this->data = src.data;
	return *this;
};

//Destructor
BSTreadTransfInfo::~BSTreadTransfInfo() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
