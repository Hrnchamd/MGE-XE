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
#include "../../include/obj/NiPSysSpawnModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysSpawnModifier::TYPE("NiPSysSpawnModifier", &NiPSysModifier::TYPE );

NiPSysSpawnModifier::NiPSysSpawnModifier() : numSpawnGenerations((unsigned short)0), percentageSpawned(0.0f), minNumToSpawn((unsigned short)0), maxNumToSpawn((unsigned short)0), spawnSpeedChaos(0.0f), spawnDirChaos(0.0f), lifeSpan(0.0f), lifeSpanVariation(0.0f), unknownInt((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysSpawnModifier::~NiPSysSpawnModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysSpawnModifier::GetType() const {
	return TYPE;
}

NiObject * NiPSysSpawnModifier::Create() {
	return new NiPSysSpawnModifier;
}

void NiPSysSpawnModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::Read( in, link_stack, info );
	NifStream( numSpawnGenerations, in, info );
	NifStream( percentageSpawned, in, info );
	NifStream( minNumToSpawn, in, info );
	NifStream( maxNumToSpawn, in, info );
	NifStream( spawnSpeedChaos, in, info );
	NifStream( spawnDirChaos, in, info );
	NifStream( lifeSpan, in, info );
	NifStream( lifeSpanVariation, in, info );
	if ( ( info.version >= 0x0A040001 ) && ( info.version <= 0x0A040001 ) ) {
		NifStream( unknownInt, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysSpawnModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( numSpawnGenerations, out, info );
	NifStream( percentageSpawned, out, info );
	NifStream( minNumToSpawn, out, info );
	NifStream( maxNumToSpawn, out, info );
	NifStream( spawnSpeedChaos, out, info );
	NifStream( spawnDirChaos, out, info );
	NifStream( lifeSpan, out, info );
	NifStream( lifeSpanVariation, out, info );
	if ( ( info.version >= 0x0A040001 ) && ( info.version <= 0x0A040001 ) ) {
		NifStream( unknownInt, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPSysSpawnModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifier::asString();
	out << "  Num Spawn Generations:  " << numSpawnGenerations << endl;
	out << "  Percentage Spawned:  " << percentageSpawned << endl;
	out << "  Min Num to Spawn:  " << minNumToSpawn << endl;
	out << "  Max Num to Spawn:  " << maxNumToSpawn << endl;
	out << "  Spawn Speed Chaos:  " << spawnSpeedChaos << endl;
	out << "  Spawn Dir Chaos:  " << spawnDirChaos << endl;
	out << "  Life Span:  " << lifeSpan << endl;
	out << "  Life Span Variation:  " << lifeSpanVariation << endl;
	out << "  Unknown int:  " << unknownInt << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysSpawnModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysSpawnModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysSpawnModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
