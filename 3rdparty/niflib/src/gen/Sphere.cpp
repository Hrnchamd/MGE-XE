/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/Sphere.h"
using namespace Niflib;

//Constructor
Sphere::Sphere() : radius(0.0f) {};

//Copy Constructor
Sphere::Sphere( const Sphere & src ) {
	*this = src;
};

//Copy Operator
Sphere & Sphere::operator=( const Sphere & src ) {
	this->center = src.center;
	this->radius = src.radius;
	return *this;
};

//Destructor
Sphere::~Sphere() {};
