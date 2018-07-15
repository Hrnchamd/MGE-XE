/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/ControllerLink.h"
#include "../../include/obj/NiInterpolator.h"
#include "../../include/obj/NiObject.h"
#include "../../include/obj/NiStringPalette.h"
#include "../../include/obj/NiTimeController.h"
using namespace Niflib;

//Constructor
ControllerLink::ControllerLink() : controller(NULL), interpolator(NULL), unknownLink2(NULL), unknownShort0((unsigned short)0), priority((byte)0), stringPalette(NULL), nodeNameOffset((unsigned int)-1), propertyTypeOffset((unsigned int)-1), controllerTypeOffset((unsigned int)-1), variable1Offset((unsigned int)-1), variable2Offset((unsigned int)-1) {};

//Copy Constructor
ControllerLink::ControllerLink( const ControllerLink & src ) {
	*this = src;
};

//Copy Operator
ControllerLink & ControllerLink::operator=( const ControllerLink & src ) {
	this->targetName = src.targetName;
	this->controller = src.controller;
	this->interpolator = src.interpolator;
	this->unknownLink2 = src.unknownLink2;
	this->unknownShort0 = src.unknownShort0;
	this->priority = src.priority;
	this->stringPalette = src.stringPalette;
	this->nodeName = src.nodeName;
	this->nodeNameOffset = src.nodeNameOffset;
	this->propertyType = src.propertyType;
	this->propertyTypeOffset = src.propertyTypeOffset;
	this->controllerType = src.controllerType;
	this->controllerTypeOffset = src.controllerTypeOffset;
	this->variable1 = src.variable1;
	this->variable1Offset = src.variable1Offset;
	this->variable2 = src.variable2;
	this->variable2Offset = src.variable2Offset;
	return *this;
};

//Destructor
ControllerLink::~ControllerLink() {};

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
