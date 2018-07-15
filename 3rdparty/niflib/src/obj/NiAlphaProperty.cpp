/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiAlphaProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiAlphaProperty::TYPE("NiAlphaProperty", &NiProperty::TYPE );

NiAlphaProperty::NiAlphaProperty() : flags((unsigned short)237), threshold((byte)0), unknownShort1((unsigned short)0), unknownInt2((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiAlphaProperty::~NiAlphaProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiAlphaProperty::GetType() const {
	return TYPE;
}

NiObject * NiAlphaProperty::Create() {
	return new NiAlphaProperty;
}

void NiAlphaProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Read( in, link_stack, info );
	NifStream( flags, in, info );
	NifStream( threshold, in, info );
	if ( info.version <= 0x02030000 ) {
		NifStream( unknownShort1, in, info );
		NifStream( unknownInt2, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiAlphaProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Write( out, link_map, missing_link_stack, info );
	NifStream( flags, out, info );
	NifStream( threshold, out, info );
	if ( info.version <= 0x02030000 ) {
		NifStream( unknownShort1, out, info );
		NifStream( unknownInt2, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiAlphaProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiProperty::asString();
	out << "  Flags:  " << flags << endl;
	out << "  Threshold:  " << threshold << endl;
	out << "  Unknown Short 1:  " << unknownShort1 << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiAlphaProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiAlphaProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiProperty::GetRefs();
	return refs;
}

std::list<NiObject *> NiAlphaProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiProperty::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

unsigned short NiAlphaProperty::GetFlags() const {
	return flags;
}

void NiAlphaProperty::SetFlags( unsigned short n ) {
	flags = n;
}

byte NiAlphaProperty::GetTestThreshold() const {
	return threshold;
}

void NiAlphaProperty::SetTestThreshold( byte n ) {
	threshold = n;
}

NiAlphaProperty::BlendFunc NiAlphaProperty::GetSourceBlendFunc() const {
	return (BlendFunc)UnpackField( flags, 1, 4 );
}

void NiAlphaProperty::SetSourceBlendFunc(BlendFunc value) {
	PackField( flags, value, 1, 4 );
}

NiAlphaProperty::BlendFunc NiAlphaProperty::GetDestBlendFunc() const {
	return (BlendFunc)UnpackField( flags, 5, 4 );
}

void NiAlphaProperty::SetDestBlendFunc(BlendFunc value) {
   PackField( flags, value, 5, 4 );
}

NiAlphaProperty::TestFunc NiAlphaProperty::GetTestFunc() const {
	return (TestFunc)UnpackField( flags, 10, 3 );
}

void NiAlphaProperty::SetTestFunc(TestFunc value) {
	PackField( flags, value, 10, 3 );
}

bool NiAlphaProperty::GetBlendState() const {
   return UnpackFlag( flags, 0);
}

void NiAlphaProperty::SetBlendState(bool value) {
	PackFlag( flags, value, 0 );
}

bool NiAlphaProperty::GetTestState() const {
	return UnpackFlag( flags, 9 );
}

void NiAlphaProperty::SetTestState(bool value) {
	PackFlag( flags, value, 9 );
}

bool NiAlphaProperty::GetTriangleSortMode() const {
	return UnpackFlag( flags, 13 );
}
void NiAlphaProperty::SetTriangleSortMode(bool value) {
	PackFlag( flags, value, 13 );
}

//--END CUSTOM CODE--//
