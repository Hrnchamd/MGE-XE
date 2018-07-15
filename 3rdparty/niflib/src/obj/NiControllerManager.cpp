/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include <algorithm>
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiControllerManager.h"
#include "../../include/obj/NiControllerSequence.h"
#include "../../include/obj/NiDefaultAVObjectPalette.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiControllerManager::TYPE("NiControllerManager", &NiTimeController::TYPE );

NiControllerManager::NiControllerManager() : cumulative(false), numControllerSequences((unsigned int)0), objectPalette(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiControllerManager::~NiControllerManager() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiControllerManager::GetType() const {
	return TYPE;
}

NiObject * NiControllerManager::Create() {
	return new NiControllerManager;
}

void NiControllerManager::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiTimeController::Read( in, link_stack, info );
	NifStream( cumulative, in, info );
	NifStream( numControllerSequences, in, info );
	controllerSequences.resize(numControllerSequences);
	for (unsigned int i1 = 0; i1 < controllerSequences.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiControllerManager::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTimeController::Write( out, link_map, missing_link_stack, info );
	numControllerSequences = (unsigned int)(controllerSequences.size());
	NifStream( cumulative, out, info );
	NifStream( numControllerSequences, out, info );
	for (unsigned int i1 = 0; i1 < controllerSequences.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*controllerSequences[i1]), out );
		} else {
			if ( controllerSequences[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(controllerSequences[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( controllerSequences[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*objectPalette), out );
	} else {
		if ( objectPalette != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(objectPalette) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( objectPalette );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiControllerManager::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiTimeController::asString();
	numControllerSequences = (unsigned int)(controllerSequences.size());
	out << "  Cumulative:  " << cumulative << endl;
	out << "  Num Controller Sequences:  " << numControllerSequences << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < controllerSequences.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Controller Sequences[" << i1 << "]:  " << controllerSequences[i1] << endl;
		array_output_count++;
	};
	out << "  Object Palette:  " << objectPalette << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiControllerManager::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTimeController::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < controllerSequences.size(); i1++) {
		controllerSequences[i1] = FixLink<NiControllerSequence>( objects, link_stack, missing_link_stack, info );
	};
	objectPalette = FixLink<NiDefaultAVObjectPalette>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiControllerManager::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiTimeController::GetRefs();
	for (unsigned int i1 = 0; i1 < controllerSequences.size(); i1++) {
		if ( controllerSequences[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(controllerSequences[i1]));
	};
	if ( objectPalette != NULL )
		refs.push_back(StaticCast<NiObject>(objectPalette));
	return refs;
}

std::list<NiObject *> NiControllerManager::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiTimeController::GetPtrs();
	for (unsigned int i1 = 0; i1 < controllerSequences.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

bool NiControllerManager::GetCumulative() const {
	return cumulative;
}

void NiControllerManager::SetCumulative( bool value ) {
	cumulative = value;
}

vector<Ref<NiControllerSequence > > NiControllerManager::GetControllerSequences() const {
	return controllerSequences;
}

void NiControllerManager::SetControllerSequences( const vector<Ref<NiControllerSequence > >& value ) {
   ClearSequences();
	controllerSequences = value;
   for (vector<NiControllerSequenceRef>::iterator it = controllerSequences.begin(); it != controllerSequences.end(); ++it) {
      (*it)->SetParent(this);
   }
}

void NiControllerManager::AddSequence( NiControllerSequence * obj ) {
   vector<NiControllerSequenceRef>::iterator begin = controllerSequences.begin();
   vector<NiControllerSequenceRef>::iterator end = controllerSequences.end();
   vector<NiControllerSequenceRef>::iterator it = std::find(begin, end, obj);
   if (it == end) {
      controllerSequences.insert(end, obj);  
      obj->SetParent(this);
   }
}

void NiControllerManager::RemoveSequence( NiControllerSequence * obj ) {
   vector<NiControllerSequenceRef>::iterator begin = controllerSequences.begin();
   vector<NiControllerSequenceRef>::iterator end = controllerSequences.end();
   vector<NiControllerSequenceRef>::iterator it = std::find(begin, end, obj);
   if (it != end) {
      (*it)->SetParent(NULL);
      controllerSequences.erase(it);  
   }
}

void NiControllerManager::ClearSequences() {
   for (vector<NiControllerSequenceRef>::iterator it = controllerSequences.begin(); it != controllerSequences.end(); ++it) {
      (*it)->SetParent(NULL);
   }
   controllerSequences.clear();
}


Ref<NiDefaultAVObjectPalette > NiControllerManager::GetObjectPalette() const {
	return objectPalette;
}

void NiControllerManager::SetObjectPalette( NiDefaultAVObjectPalette * value ) {
	objectPalette = value;
}

//--END CUSTOM CODE--//
