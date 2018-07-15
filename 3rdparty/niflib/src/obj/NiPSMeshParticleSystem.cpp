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
#include "../../include/obj/NiPSMeshParticleSystem.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSMeshParticleSystem::TYPE("NiPSMeshParticleSystem", &NiPSParticleSystem::TYPE );

NiPSMeshParticleSystem::NiPSMeshParticleSystem() : unknown23((int)0), unknown24((int)0), unknown25((int)0), unknown26((byte)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSMeshParticleSystem::~NiPSMeshParticleSystem() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSMeshParticleSystem::GetType() const {
	return TYPE;
}

NiObject * NiPSMeshParticleSystem::Create() {
	return new NiPSMeshParticleSystem;
}

void NiPSMeshParticleSystem::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSParticleSystem::Read( in, link_stack, info );
	NifStream( unknown23, in, info );
	NifStream( unknown24, in, info );
	NifStream( unknown25, in, info );
	NifStream( unknown26, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSMeshParticleSystem::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSParticleSystem::Write( out, link_map, missing_link_stack, info );
	NifStream( unknown23, out, info );
	NifStream( unknown24, out, info );
	NifStream( unknown25, out, info );
	NifStream( unknown26, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSMeshParticleSystem::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSParticleSystem::asString();
	out << "  Unknown 23:  " << unknown23 << endl;
	out << "  Unknown 24:  " << unknown24 << endl;
	out << "  Unknown 25:  " << unknown25 << endl;
	out << "  Unknown 26:  " << unknown26 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSMeshParticleSystem::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSParticleSystem::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSMeshParticleSystem::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSParticleSystem::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSMeshParticleSystem::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSParticleSystem::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
