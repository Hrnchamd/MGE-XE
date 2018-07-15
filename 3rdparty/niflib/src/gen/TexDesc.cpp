/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/TexDesc.h"
#include "../../include/obj/NiSourceTexture.h"
using namespace Niflib;

//Constructor
TexDesc::TexDesc() : source(NULL), clampMode((TexClampMode)WRAP_S_WRAP_T), filterMode((TexFilterMode)FILTER_TRILERP), flags((unsigned short)0), unknownShort((short)0), uvSet((unsigned int)0), ps2L((short)0), ps2K((short)-75), unknown1((unsigned short)0), hasTextureTransform(false), tiling(1.0, 1.0), wRotation(0.0f), transformType_((unsigned int)0) {};

//Copy Constructor
TexDesc::TexDesc( const TexDesc & src ) {
	*this = src;
};

//Copy Operator
TexDesc & TexDesc::operator=( const TexDesc & src ) {
	this->source = src.source;
	this->clampMode = src.clampMode;
	this->filterMode = src.filterMode;
	this->flags = src.flags;
	this->unknownShort = src.unknownShort;
	this->uvSet = src.uvSet;
	this->ps2L = src.ps2L;
	this->ps2K = src.ps2K;
	this->unknown1 = src.unknown1;
	this->hasTextureTransform = src.hasTextureTransform;
	this->translation = src.translation;
	this->tiling = src.tiling;
	this->wRotation = src.wRotation;
	this->transformType_ = src.transformType_;
	this->centerOffset = src.centerOffset;
	return *this;
};

//Destructor
TexDesc::~TexDesc() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
