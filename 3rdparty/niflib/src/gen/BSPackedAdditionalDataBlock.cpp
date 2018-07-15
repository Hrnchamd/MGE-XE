/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/BSPackedAdditionalDataBlock.h"
using namespace Niflib;

//Constructor
BSPackedAdditionalDataBlock::BSPackedAdditionalDataBlock() : hasData(false), numTotalBytes((int)0), numBlocks((int)0), numAtoms((int)0), unknownInt1((int)0), numTotalBytesPerElement((int)0) {};

//Copy Constructor
BSPackedAdditionalDataBlock::BSPackedAdditionalDataBlock( const BSPackedAdditionalDataBlock & src ) {
	*this = src;
};

//Copy Operator
BSPackedAdditionalDataBlock & BSPackedAdditionalDataBlock::operator=( const BSPackedAdditionalDataBlock & src ) {
	this->hasData = src.hasData;
	this->numTotalBytes = src.numTotalBytes;
	this->numBlocks = src.numBlocks;
	this->blockOffsets = src.blockOffsets;
	this->numAtoms = src.numAtoms;
	this->atomSizes = src.atomSizes;
	this->data = src.data;
	this->unknownInt1 = src.unknownInt1;
	this->numTotalBytesPerElement = src.numTotalBytesPerElement;
	return *this;
};

//Destructor
BSPackedAdditionalDataBlock::~BSPackedAdditionalDataBlock() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
