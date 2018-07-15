/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#include "../include/RefObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type RefObject::TYPE("RefObject", NULL );

RefObject::RefObject() {
	_ref_count = 0;
	objectsInMemory++;
}

RefObject::RefObject(const RefObject& src) {
	_ref_count = 0;
	objectsInMemory++;
}

RefObject::~RefObject() {
	objectsInMemory--;
}

const Type & RefObject::GetType() const {
	return TYPE;
}


unsigned int RefObject::objectsInMemory = 0;

bool RefObject::IsSameType( const Type & compare_to) const {
	return GetType().IsSameType( compare_to );
}

bool RefObject::IsSameType( const RefObject * object ) const {
	return GetType().IsSameType( object->GetType() );
}

bool RefObject::IsDerivedType( const Type & compare_to) const {
	return GetType().IsDerivedType( compare_to );
}

bool RefObject::IsDerivedType( const RefObject * object ) const {
	return GetType().IsDerivedType( object->GetType() );
}

void RefObject::AddRef() const {
	++_ref_count;
}

void RefObject::SubtractRef() const {
	_ref_count--;
	if ( _ref_count < 1 ) {
		delete this;
	}
}

unsigned int RefObject::NumObjectsInMemory() {
	return objectsInMemory;
}

/*! Used to format a human readable string that includes the type of the object */
string RefObject::GetIDString() const {
	stringstream out;
	out << this << "(" << this->GetType().GetTypeName() << ")";
	return out.str();
}