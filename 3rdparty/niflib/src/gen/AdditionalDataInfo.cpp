/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/AdditionalDataInfo.h"
using namespace Niflib;

//Constructor
AdditionalDataInfo::AdditionalDataInfo() : dataType((int)0), numChannelBytesPerElement((int)0), numChannelBytes((int)0), numTotalBytesPerElement((int)0), blockIndex((int)0), channelOffset((int)0), unknownByte1((byte)2) {};

//Copy Constructor
AdditionalDataInfo::AdditionalDataInfo( const AdditionalDataInfo & src ) {
	*this = src;
};

//Copy Operator
AdditionalDataInfo & AdditionalDataInfo::operator=( const AdditionalDataInfo & src ) {
	this->dataType = src.dataType;
	this->numChannelBytesPerElement = src.numChannelBytesPerElement;
	this->numChannelBytes = src.numChannelBytes;
	this->numTotalBytesPerElement = src.numTotalBytesPerElement;
	this->blockIndex = src.blockIndex;
	this->channelOffset = src.channelOffset;
	this->unknownByte1 = src.unknownByte1;
	return *this;
};

//Destructor
AdditionalDataInfo::~AdditionalDataInfo() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
