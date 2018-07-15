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
#include "../../include/obj/NiPSysDragFieldModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysDragFieldModifier::TYPE("NiPSysDragFieldModifier", &NiPSysFieldModifier::TYPE );

NiPSysDragFieldModifier::NiPSysDragFieldModifier() : useDirection_(false) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSysDragFieldModifier::~NiPSysDragFieldModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSysDragFieldModifier::GetType() const {
	return TYPE;
}

NiObject * NiPSysDragFieldModifier::Create() {
	return new NiPSysDragFieldModifier;
}

void NiPSysDragFieldModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::Read( in, link_stack, info );
	NifStream( useDirection_, in, info );
	NifStream( direction, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysDragFieldModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( useDirection_, out, info );
	NifStream( direction, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSysDragFieldModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysFieldModifier::asString();
	out << "  Use Direction?:  " << useDirection_ << endl;
	out << "  Direction:  " << direction << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysDragFieldModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysDragFieldModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysFieldModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysDragFieldModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysFieldModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
