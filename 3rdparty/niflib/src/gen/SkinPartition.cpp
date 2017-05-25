/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/SkinPartition.h"
using namespace Niflib;

//Constructor
SkinPartition::SkinPartition() : numVertices((unsigned short)0), numTriangles((unsigned short)0), numBones((unsigned short)0), numStrips((unsigned short)0), numWeightsPerVertex((unsigned short)0), hasVertexMap(false), hasVertexWeights(false), hasStrips(false), hasBoneIndices(false) {};

//Copy Constructor
SkinPartition::SkinPartition( const SkinPartition & src ) {
	*this = src;
};

//Copy Operator
SkinPartition & SkinPartition::operator=( const SkinPartition & src ) {
	this->numVertices = src.numVertices;
	this->numTriangles = src.numTriangles;
	this->numBones = src.numBones;
	this->numStrips = src.numStrips;
	this->numWeightsPerVertex = src.numWeightsPerVertex;
	this->bones = src.bones;
	this->hasVertexMap = src.hasVertexMap;
	this->vertexMap = src.vertexMap;
	this->hasVertexWeights = src.hasVertexWeights;
	this->vertexWeights = src.vertexWeights;
	this->stripLengths = src.stripLengths;
	this->hasStrips = src.hasStrips;
	this->strips = src.strips;
	this->triangles = src.triangles;
	this->hasBoneIndices = src.hasBoneIndices;
	this->boneIndices = src.boneIndices;
	return *this;
};

//Destructor
SkinPartition::~SkinPartition() {};
