/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/MeshData.h"
#include "../../include/gen/SemanticData.h"
#include "../../include/obj/NiDataStream.h"
using namespace Niflib;

//Constructor
MeshData::MeshData() : stream(NULL), isPerInstance(0), numSubmeshes((unsigned short)1), numComponents((int)1) {};

//Copy Constructor
MeshData::MeshData( const MeshData & src ) {
	*this = src;
};

//Copy Operator
MeshData & MeshData::operator=( const MeshData & src ) {
	this->stream = src.stream;
	this->isPerInstance = src.isPerInstance;
	this->numSubmeshes = src.numSubmeshes;
	this->submeshToRegionMap = src.submeshToRegionMap;
	this->numComponents = src.numComponents;
	this->componentSemantics = src.componentSemantics;
	return *this;
};

//Destructor
MeshData::~MeshData() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
