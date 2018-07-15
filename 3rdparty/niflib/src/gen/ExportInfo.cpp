/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/ExportInfo.h"
using namespace Niflib;

//Constructor
ExportInfo::ExportInfo() : unknown((unsigned int)3) {};

//Copy Constructor
ExportInfo::ExportInfo( const ExportInfo & src ) {
	*this = src;
};

//Copy Operator
ExportInfo & ExportInfo::operator=( const ExportInfo & src ) {
	this->unknown = src.unknown;
	this->creator = src.creator;
	this->exportInfo1 = src.exportInfo1;
	this->exportInfo2 = src.exportInfo2;
	return *this;
};

//Destructor
ExportInfo::~ExportInfo() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
