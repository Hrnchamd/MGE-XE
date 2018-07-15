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
#include "../../include/obj/NiPSSimulatorForcesStep.h"
#include "../../include/obj/NiObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSSimulatorForcesStep::TYPE("NiPSSimulatorForcesStep", &NiPSSimulatorStep::TYPE );

NiPSSimulatorForcesStep::NiPSSimulatorForcesStep() : numForces((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSSimulatorForcesStep::~NiPSSimulatorForcesStep() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSSimulatorForcesStep::GetType() const {
	return TYPE;
}

NiObject * NiPSSimulatorForcesStep::Create() {
	return new NiPSSimulatorForcesStep;
}

void NiPSSimulatorForcesStep::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiPSSimulatorStep::Read( in, link_stack, info );
	NifStream( numForces, in, info );
	forces.resize(numForces);
	for (unsigned int i1 = 0; i1 < forces.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSSimulatorForcesStep::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSSimulatorStep::Write( out, link_map, missing_link_stack, info );
	numForces = (unsigned int)(forces.size());
	NifStream( numForces, out, info );
	for (unsigned int i1 = 0; i1 < forces.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*forces[i1]), out );
		} else {
			if ( forces[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(forces[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( forces[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSSimulatorForcesStep::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiPSSimulatorStep::asString();
	numForces = (unsigned int)(forces.size());
	out << "  Num Forces:  " << numForces << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < forces.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Forces[" << i1 << "]:  " << forces[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSSimulatorForcesStep::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSSimulatorStep::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < forces.size(); i1++) {
		forces[i1] = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSSimulatorForcesStep::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSSimulatorStep::GetRefs();
	for (unsigned int i1 = 0; i1 < forces.size(); i1++) {
		if ( forces[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(forces[i1]));
	};
	return refs;
}

std::list<NiObject *> NiPSSimulatorForcesStep::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSSimulatorStep::GetPtrs();
	for (unsigned int i1 = 0; i1 < forces.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
