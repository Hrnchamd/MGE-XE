/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/SkinPartition.h"
#include "../../include/gen/SkinPartitionUnknownItem1.h"
using namespace Niflib;

//Constructor
SkinPartition::SkinPartition() : numVertices((unsigned short)0), numTriangles((unsigned short)0), numBones((unsigned short)0), numStrips((unsigned short)0), numWeightsPerVertex((unsigned short)0), hasVertexMap(false), hasVertexWeights(false), hasFaces(false), hasBoneIndices(false), unknownShort((unsigned short)0), unknown83C3((unsigned short)0), unknown00001((unsigned short)0), numVertices2((unsigned short)0), unknown00002((unsigned short)0), unknown00003((unsigned short)0), unknown00004((unsigned short)0) {};

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
	this->hasFaces = src.hasFaces;
	this->strips = src.strips;
	this->triangles = src.triangles;
	this->hasBoneIndices = src.hasBoneIndices;
	this->boneIndices = src.boneIndices;
	this->unknownShort = src.unknownShort;
	this->unknown83C3 = src.unknown83C3;
	this->unknown00001 = src.unknown00001;
	this->numVertices2 = src.numVertices2;
	this->unknown00002 = src.unknown00002;
	this->unknown00003 = src.unknown00003;
	this->unknown00004 = src.unknown00004;
	this->unknownArr1 = src.unknownArr1;
	return *this;
};

//Destructor
SkinPartition::~SkinPartition() {};

//--BEGIN MISC CUSTOM CODE--//

unsigned short SkinPartition::numTrianglesCalc() const {
	int len = 0;
	if (numStrips == 0) {
		len = triangles.size();
	} else {
		for (vector<unsigned short>::iterator itr = stripLengths.begin(); itr != stripLengths.end(); ++itr) {
			len += ((*itr) - 2);
		}
	};
	// ensure proper unsigned short range
	if (len < 0)
		len = 0;
	if (len > 65535)
		len = 65535; // or raise runtime error?
	return len;
};

unsigned short SkinPartition::numTrianglesCalc(const NifInfo & info) const {
	return numTrianglesCalc();
}

//--END CUSTOM CODE--//
