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
#include "../../include/obj/BSPSysInheritVelocityModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSPSysInheritVelocityModifier::TYPE("BSPSysInheritVelocityModifier", &NiPSysModifier::TYPE );

BSPSysInheritVelocityModifier::BSPSysInheritVelocityModifier() : unknownInt1((unsigned int)0), unknownFloat1(0.0f), unknownFloat2(0.0f), unknownFloat3(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSPSysInheritVelocityModifier::~BSPSysInheritVelocityModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSPSysInheritVelocityModifier::GetType() const {
	return TYPE;
}

NiObject * BSPSysInheritVelocityModifier::Create() {
	return new BSPSysInheritVelocityModifier;
}

void BSPSysInheritVelocityModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifier::Read( in, link_stack, info );
	NifStream( unknownInt1, in, info );
	NifStream( unknownFloat1, in, info );
	NifStream( unknownFloat2, in, info );
	NifStream( unknownFloat3, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSPSysInheritVelocityModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( unknownInt1, out, info );
	NifStream( unknownFloat1, out, info );
	NifStream( unknownFloat2, out, info );
	NifStream( unknownFloat3, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSPSysInheritVelocityModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifier::asString();
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Unknown Float 3:  " << unknownFloat3 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSPSysInheritVelocityModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSPSysInheritVelocityModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifier::GetRefs();
	return refs;
}

std::list<NiObject *> BSPSysInheritVelocityModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
