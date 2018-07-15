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
#include "../../include/obj/NiPSSimulator.h"
#include "../../include/obj/NiPSSimulatorStep.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSSimulator::TYPE("NiPSSimulator", &NiMeshModifier::TYPE );

NiPSSimulator::NiPSSimulator() : numSimulationSteps((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSSimulator::~NiPSSimulator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSSimulator::GetType() const {
	return TYPE;
}

NiObject * NiPSSimulator::Create() {
	return new NiPSSimulator;
}

void NiPSSimulator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiMeshModifier::Read( in, link_stack, info );
	NifStream( numSimulationSteps, in, info );
	simulationSteps.resize(numSimulationSteps);
	for (unsigned int i1 = 0; i1 < simulationSteps.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSSimulator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiMeshModifier::Write( out, link_map, missing_link_stack, info );
	numSimulationSteps = (unsigned int)(simulationSteps.size());
	NifStream( numSimulationSteps, out, info );
	for (unsigned int i1 = 0; i1 < simulationSteps.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*simulationSteps[i1]), out );
		} else {
			if ( simulationSteps[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(simulationSteps[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( simulationSteps[i1] );
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

std::string NiPSSimulator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiMeshModifier::asString();
	numSimulationSteps = (unsigned int)(simulationSteps.size());
	out << "  Num Simulation Steps:  " << numSimulationSteps << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < simulationSteps.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Simulation Steps[" << i1 << "]:  " << simulationSteps[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSSimulator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiMeshModifier::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < simulationSteps.size(); i1++) {
		simulationSteps[i1] = FixLink<NiPSSimulatorStep>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSSimulator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiMeshModifier::GetRefs();
	for (unsigned int i1 = 0; i1 < simulationSteps.size(); i1++) {
		if ( simulationSteps[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(simulationSteps[i1]));
	};
	return refs;
}

std::list<NiObject *> NiPSSimulator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiMeshModifier::GetPtrs();
	for (unsigned int i1 = 0; i1 < simulationSteps.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
