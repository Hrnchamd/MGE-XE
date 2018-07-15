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
#include "../../include/obj/BSStripPSysData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSStripPSysData::TYPE("BSStripPSysData", &NiPSysData::TYPE );

BSStripPSysData::BSStripPSysData() : unknownShort5((short)0), unknownByte6((byte)0), unknownInt7((int)0), unknownFloat8(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSStripPSysData::~BSStripPSysData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSStripPSysData::GetType() const {
	return TYPE;
}

NiObject * BSStripPSysData::Create() {
	return new BSStripPSysData;
}

void BSStripPSysData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysData::Read( in, link_stack, info );
	NifStream( unknownShort5, in, info );
	NifStream( unknownByte6, in, info );
	NifStream( unknownInt7, in, info );
	NifStream( unknownFloat8, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSStripPSysData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysData::Write( out, link_map, missing_link_stack, info );
	NifStream( unknownShort5, out, info );
	NifStream( unknownByte6, out, info );
	NifStream( unknownInt7, out, info );
	NifStream( unknownFloat8, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSStripPSysData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysData::asString();
	out << "  Unknown Short 5:  " << unknownShort5 << endl;
	out << "  Unknown Byte 6:  " << unknownByte6 << endl;
	out << "  Unknown Int 7:  " << unknownInt7 << endl;
	out << "  Unknown Float 8:  " << unknownFloat8 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSStripPSysData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSStripPSysData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysData::GetRefs();
	return refs;
}

std::list<NiObject *> BSStripPSysData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
