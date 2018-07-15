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
#include "../../include/obj/NiTimeController.h"
#include "../../include/obj/NiObjectNET.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiTimeController::TYPE("NiTimeController", &NiObject::TYPE );

NiTimeController::NiTimeController() : nextController(NULL), flags((unsigned short)0), frequency(0.0f), phase(0.0f), startTime(0.0f), stopTime(0.0f), target(NULL), unknownInteger((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiTimeController::~NiTimeController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiTimeController::GetType() const {
	return TYPE;
}

NiObject * NiTimeController::Create() {
	return new NiTimeController;
}

void NiTimeController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( flags, in, info );
	NifStream( frequency, in, info );
	NifStream( phase, in, info );
	NifStream( startTime, in, info );
	NifStream( stopTime, in, info );
	if ( info.version >= 0x0303000D ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	if ( info.version <= 0x03010000 ) {
		NifStream( unknownInteger, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTimeController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*nextController), out );
	} else {
		if ( nextController != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(nextController) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( nextController );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	NifStream( flags, out, info );
	NifStream( frequency, out, info );
	NifStream( phase, out, info );
	NifStream( startTime, out, info );
	NifStream( stopTime, out, info );
	if ( info.version >= 0x0303000D ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*target), out );
		} else {
			if ( target != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(target) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( target );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( info.version <= 0x03010000 ) {
		NifStream( unknownInteger, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiTimeController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiObject::asString();
	out << "  Next Controller:  " << nextController << endl;
	out << "  Flags:  " << flags << endl;
	out << "  Frequency:  " << frequency << endl;
	out << "  Phase:  " << phase << endl;
	out << "  Start Time:  " << startTime << endl;
	out << "  Stop Time:  " << stopTime << endl;
	out << "  Target:  " << target << endl;
	out << "  Unknown Integer:  " << unknownInteger << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTimeController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	nextController = FixLink<NiTimeController>( objects, link_stack, missing_link_stack, info );
	if ( info.version >= 0x0303000D ) {
		target = FixLink<NiObjectNET>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiTimeController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( nextController != NULL )
		refs.push_back(StaticCast<NiObject>(nextController));
	return refs;
}

std::list<NiObject *> NiTimeController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	if ( target != NULL )
		ptrs.push_back((NiObject *)(target));
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

NiTimeControllerRef NiTimeController::GetNextController() const {
	return nextController;
}

void NiTimeController::SetNextController( const NiTimeControllerRef & obj ) {
	nextController = obj;
}

void NiTimeController::SetTarget( NiObjectNET * new_target ) {
	target = new_target;
}

Ref<NiObjectNET> NiTimeController::GetTarget() {
	return target;
}

unsigned short NiTimeController::GetFlags() const {
	return flags;
}

void NiTimeController::SetFlags( unsigned short n ) {
	flags = n;
}

float NiTimeController::GetFrequency() const {
	return frequency;
}

void NiTimeController::SetFrequency( float n ) {
	frequency = n;
}

float NiTimeController::GetPhase() const {
	return phase;
}

void NiTimeController::SetPhase( float n ) {
	phase = n;
}

void NiTimeController::NormalizeKeys() {
	//Normalize the start and stop times
	startTime = frequency * startTime + phase;
	stopTime = frequency * stopTime + phase;

	//Set phase to 0 and frequency to 1
	phase = 0.0f;
	frequency = 0.0f;
}

float NiTimeController::GetStartTime() const {
	return startTime;
}

void NiTimeController::SetStartTime( float n ) {
	startTime = n;
}

float NiTimeController::GetStopTime() const {
	return stopTime;
}

void NiTimeController::SetStopTime( float n ) {
	stopTime = n;
}

//--END CUSTOM CODE--//
