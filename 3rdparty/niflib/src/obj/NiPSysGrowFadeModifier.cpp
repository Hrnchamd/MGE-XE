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
#include "../../include/obj/NiPSysGrowFadeModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysGrowFadeModifier::TYPE("NiPSysGrowFadeModifier", &NiPSysModifier::TYPE );

NiPSysGrowFadeModifier::NiPSysGrowFadeModifier() : growTime(0.0f), growGeneration((unsigned short)0), fadeTime(0.0f), fadeGeneration((unsigned short)0), baseScale(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysGrowFadeModifier::~NiPSysGrowFadeModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysGrowFadeModifier::GetType() const {
	return TYPE;
}

NiObject * NiPSysGrowFadeModifier::Create() {
	return new NiPSysGrowFadeModifier;
}

void NiPSysGrowFadeModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::Read( in, link_stack, info );
	NifStream( growTime, in, info );
	NifStream( growGeneration, in, info );
	NifStream( fadeTime, in, info );
	NifStream( fadeGeneration, in, info );
	if ( ( info.version >= 0x14020007 ) && ( info.userVersion == 11 ) ) {
		NifStream( baseScale, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysGrowFadeModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( growTime, out, info );
	NifStream( growGeneration, out, info );
	NifStream( fadeTime, out, info );
	NifStream( fadeGeneration, out, info );
	if ( ( info.version >= 0x14020007 ) && ( info.userVersion == 11 ) ) {
		NifStream( baseScale, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPSysGrowFadeModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifier::asString();
	out << "  Grow Time:  " << growTime << endl;
	out << "  Grow Generation:  " << growGeneration << endl;
	out << "  Fade Time:  " << fadeTime << endl;
	out << "  Fade Generation:  " << fadeGeneration << endl;
	out << "  Base Scale:  " << baseScale << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysGrowFadeModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysGrowFadeModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysGrowFadeModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
