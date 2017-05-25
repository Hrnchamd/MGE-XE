/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/RagdollDescriptor.h"
using namespace Niflib;

//Constructor
RagdollDescriptor::RagdollDescriptor() : coneMinAngle(0.0f), planeMinAngle(0.0f), planeMaxAngle(0.0f), twistMinAngle(0.0f), twistMaxAngle(0.0f), maxFriction(0.0f) {};

//Copy Constructor
RagdollDescriptor::RagdollDescriptor( const RagdollDescriptor & src ) {
	*this = src;
};

//Copy Operator
RagdollDescriptor & RagdollDescriptor::operator=( const RagdollDescriptor & src ) {
	this->pivotA = src.pivotA;
	this->planeA = src.planeA;
	this->twistA = src.twistA;
	this->pivotB = src.pivotB;
	this->planeB = src.planeB;
	this->twistB = src.twistB;
	this->coneMinAngle = src.coneMinAngle;
	this->planeMinAngle = src.planeMinAngle;
	this->planeMaxAngle = src.planeMaxAngle;
	this->twistMinAngle = src.twistMinAngle;
	this->twistMaxAngle = src.twistMaxAngle;
	this->maxFriction = src.maxFriction;
	return *this;
};

//Destructor
RagdollDescriptor::~RagdollDescriptor() {};
