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
#include "../../include/obj/BSPSysSubTexModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSPSysSubTexModifier::TYPE("BSPSysSubTexModifier", &NiPSysModifier::TYPE );

BSPSysSubTexModifier::BSPSysSubTexModifier() : startFrame((unsigned int)0), startFrameFudge(0.0f), endFrame(0.0f), loopStartFrame(0.0f), loopStartFrameFudge(0.0f), frameCount(0.0f), frameCountFudge(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSPSysSubTexModifier::~BSPSysSubTexModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSPSysSubTexModifier::GetType() const {
	return TYPE;
}

NiObject * BSPSysSubTexModifier::Create() {
	return new BSPSysSubTexModifier;
}

void BSPSysSubTexModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifier::Read( in, link_stack, info );
	NifStream( startFrame, in, info );
	NifStream( startFrameFudge, in, info );
	NifStream( endFrame, in, info );
	NifStream( loopStartFrame, in, info );
	NifStream( loopStartFrameFudge, in, info );
	NifStream( frameCount, in, info );
	NifStream( frameCountFudge, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSPSysSubTexModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( startFrame, out, info );
	NifStream( startFrameFudge, out, info );
	NifStream( endFrame, out, info );
	NifStream( loopStartFrame, out, info );
	NifStream( loopStartFrameFudge, out, info );
	NifStream( frameCount, out, info );
	NifStream( frameCountFudge, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSPSysSubTexModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifier::asString();
	out << "  Start Frame:  " << startFrame << endl;
	out << "  Start Frame Fudge:  " << startFrameFudge << endl;
	out << "  End Frame:  " << endFrame << endl;
	out << "  Loop Start Frame:  " << loopStartFrame << endl;
	out << "  Loop Start Frame Fudge:  " << loopStartFrameFudge << endl;
	out << "  Frame Count:  " << frameCount << endl;
	out << "  Frame Count Fudge:  " << frameCountFudge << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSPSysSubTexModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSPSysSubTexModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifier::GetRefs();
	return refs;
}

std::list<NiObject *> BSPSysSubTexModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
