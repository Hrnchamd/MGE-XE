/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/SkinPartitionUnknownItem1.h"
using namespace Niflib;

//Constructor
SkinPartitionUnknownItem1::SkinPartitionUnknownItem1() : unknownFlags((unsigned int)0), f1(0.0f), f2(0.0f), f3(0.0f), f4(0.0f), f5(0.0f) {};

//Copy Constructor
SkinPartitionUnknownItem1::SkinPartitionUnknownItem1( const SkinPartitionUnknownItem1 & src ) {
	*this = src;
};

//Copy Operator
SkinPartitionUnknownItem1 & SkinPartitionUnknownItem1::operator=( const SkinPartitionUnknownItem1 & src ) {
	this->unknownFlags = src.unknownFlags;
	this->f1 = src.f1;
	this->f2 = src.f2;
	this->f3 = src.f3;
	this->f4 = src.f4;
	this->f5 = src.f5;
	return *this;
};

//Destructor
SkinPartitionUnknownItem1::~SkinPartitionUnknownItem1() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
