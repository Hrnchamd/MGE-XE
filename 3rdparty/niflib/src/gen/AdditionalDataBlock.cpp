/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/AdditionalDataBlock.h"
using namespace Niflib;

//Constructor
AdditionalDataBlock::AdditionalDataBlock() : hasData(false), blockSize((int)0), numBlocks((int)0), numData((int)0) {};

//Copy Constructor
AdditionalDataBlock::AdditionalDataBlock( const AdditionalDataBlock & src ) {
	*this = src;
};

//Copy Operator
AdditionalDataBlock & AdditionalDataBlock::operator=( const AdditionalDataBlock & src ) {
	this->hasData = src.hasData;
	this->blockSize = src.blockSize;
	this->numBlocks = src.numBlocks;
	this->blockOffsets = src.blockOffsets;
	this->numData = src.numData;
	this->dataSizes = src.dataSizes;
	this->data = src.data;
	return *this;
};

//Destructor
AdditionalDataBlock::~AdditionalDataBlock() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
