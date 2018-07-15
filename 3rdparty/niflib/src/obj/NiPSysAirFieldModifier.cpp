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
#include "../../include/obj/NiPSysAirFieldModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysAirFieldModifier::TYPE("NiPSysAirFieldModifier", &NiPSysFieldModifier::TYPE );

NiPSysAirFieldModifier::NiPSysAirFieldModifier() : unknownFloat2(0.0f), unknownFloat3(0.0f), unknownBoolean1(false), unknownBoolean2(false), unknownBoolean3(false), unknownFloat4(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSysAirFieldModifier::~NiPSysAirFieldModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSysAirFieldModifier::GetType() const {
	return TYPE;
}

NiObject * NiPSysAirFieldModifier::Create() {
	return new NiPSysAirFieldModifier;
}

void NiPSysAirFieldModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::Read( in, link_stack, info );
	NifStream( direction, in, info );
	NifStream( unknownFloat2, in, info );
	NifStream( unknownFloat3, in, info );
	NifStream( unknownBoolean1, in, info );
	NifStream( unknownBoolean2, in, info );
	NifStream( unknownBoolean3, in, info );
	NifStream( unknownFloat4, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysAirFieldModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( direction, out, info );
	NifStream( unknownFloat2, out, info );
	NifStream( unknownFloat3, out, info );
	NifStream( unknownBoolean1, out, info );
	NifStream( unknownBoolean2, out, info );
	NifStream( unknownBoolean3, out, info );
	NifStream( unknownFloat4, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSysAirFieldModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysFieldModifier::asString();
	out << "  Direction:  " << direction << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Unknown Float 3:  " << unknownFloat3 << endl;
	out << "  Unknown Boolean 1:  " << unknownBoolean1 << endl;
	out << "  Unknown Boolean 2:  " << unknownBoolean2 << endl;
	out << "  Unknown Boolean 3:  " << unknownBoolean3 << endl;
	out << "  Unknown Float 4:  " << unknownFloat4 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysAirFieldModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysFieldModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysAirFieldModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysFieldModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysAirFieldModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysFieldModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
