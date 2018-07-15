/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/TexSource.h"
#include "../../include/obj/NiObject.h"
#include "../../include/obj/NiPixelData.h"
using namespace Niflib;

//Constructor
TexSource::TexSource() : useExternal((byte)0), unknownLink(NULL), unknownByte((byte)0), pixelData(NULL) {};

//Copy Constructor
TexSource::TexSource( const TexSource & src ) {
	*this = src;
};

//Copy Operator
TexSource & TexSource::operator=( const TexSource & src ) {
	this->useExternal = src.useExternal;
	this->fileName = src.fileName;
	this->unknownLink = src.unknownLink;
	this->unknownByte = src.unknownByte;
	this->pixelData = src.pixelData;
	return *this;
};

//Destructor
TexSource::~TexSource() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
