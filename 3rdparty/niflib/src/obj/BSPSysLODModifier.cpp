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
#include "../../include/obj/BSPSysLODModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSPSysLODModifier::TYPE("BSPSysLODModifier", &NiPSysModifier::TYPE );

BSPSysLODModifier::BSPSysLODModifier() : uknownFloat1(0.0f), uknownFloat2(0.0f), uknownFloat3(0.0f), uknownFloat4(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSPSysLODModifier::~BSPSysLODModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSPSysLODModifier::GetType() const {
	return TYPE;
}

NiObject * BSPSysLODModifier::Create() {
	return new BSPSysLODModifier;
}

void BSPSysLODModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifier::Read( in, link_stack, info );
	NifStream( uknownFloat1, in, info );
	NifStream( uknownFloat2, in, info );
	NifStream( uknownFloat3, in, info );
	NifStream( uknownFloat4, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSPSysLODModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( uknownFloat1, out, info );
	NifStream( uknownFloat2, out, info );
	NifStream( uknownFloat3, out, info );
	NifStream( uknownFloat4, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSPSysLODModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifier::asString();
	out << "  Uknown Float 1:  " << uknownFloat1 << endl;
	out << "  Uknown Float 2:  " << uknownFloat2 << endl;
	out << "  Uknown Float 3:  " << uknownFloat3 << endl;
	out << "  Uknown Float 4:  " << uknownFloat4 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSPSysLODModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSPSysLODModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifier::GetRefs();
	return refs;
}

std::list<NiObject *> BSPSysLODModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
