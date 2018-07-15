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
#include "../../include/obj/NiPSSimulatorMeshAlignStep.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSSimulatorMeshAlignStep::TYPE("NiPSSimulatorMeshAlignStep", &NiPSSimulatorStep::TYPE );

NiPSSimulatorMeshAlignStep::NiPSSimulatorMeshAlignStep() : numRotationKeys((byte)0), rotationLoopBehavior((PSLoopBehavior)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSSimulatorMeshAlignStep::~NiPSSimulatorMeshAlignStep() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSSimulatorMeshAlignStep::GetType() const {
	return TYPE;
}

NiObject * NiPSSimulatorMeshAlignStep::Create() {
	return new NiPSSimulatorMeshAlignStep;
}

void NiPSSimulatorMeshAlignStep::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSSimulatorStep::Read( in, link_stack, info );
	NifStream( numRotationKeys, in, info );
	rotationKeys.resize(numRotationKeys);
	for (unsigned int i1 = 0; i1 < rotationKeys.size(); i1++) {
		NifStream( rotationKeys[i1], in, info, 1 );
	};
	NifStream( rotationLoopBehavior, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSSimulatorMeshAlignStep::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSSimulatorStep::Write( out, link_map, missing_link_stack, info );
	numRotationKeys = (byte)(rotationKeys.size());
	NifStream( numRotationKeys, out, info );
	for (unsigned int i1 = 0; i1 < rotationKeys.size(); i1++) {
		NifStream( rotationKeys[i1], out, info, 1 );
	};
	NifStream( rotationLoopBehavior, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSSimulatorMeshAlignStep::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiPSSimulatorStep::asString();
	numRotationKeys = (byte)(rotationKeys.size());
	out << "  Num Rotation Keys:  " << numRotationKeys << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < rotationKeys.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Rotation Keys[" << i1 << "]:  " << rotationKeys[i1] << endl;
		array_output_count++;
	};
	out << "  Rotation Loop Behavior:  " << rotationLoopBehavior << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSSimulatorMeshAlignStep::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSSimulatorStep::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSSimulatorMeshAlignStep::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSSimulatorStep::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSSimulatorMeshAlignStep::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSSimulatorStep::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
