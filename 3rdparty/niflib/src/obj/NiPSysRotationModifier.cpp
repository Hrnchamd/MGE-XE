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
#include "../../include/obj/NiPSysRotationModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysRotationModifier::TYPE("NiPSysRotationModifier", &NiPSysModifier::TYPE );

NiPSysRotationModifier::NiPSysRotationModifier() : initialRotationSpeed(0.0f), initialRotationSpeedVariation(0.0f), initialRotationAngle(0.0f), initialRotationAngleVariation(0.0f), randomRotSpeedSign(false), randomInitialAxis(false) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysRotationModifier::~NiPSysRotationModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysRotationModifier::GetType() const {
	return TYPE;
}

NiObject * NiPSysRotationModifier::Create() {
	return new NiPSysRotationModifier;
}

void NiPSysRotationModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::Read( in, link_stack, info );
	NifStream( initialRotationSpeed, in, info );
	if ( info.version >= 0x14000004 ) {
		NifStream( initialRotationSpeedVariation, in, info );
		NifStream( initialRotationAngle, in, info );
		NifStream( initialRotationAngleVariation, in, info );
		NifStream( randomRotSpeedSign, in, info );
	};
	NifStream( randomInitialAxis, in, info );
	NifStream( initialAxis, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysRotationModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( initialRotationSpeed, out, info );
	if ( info.version >= 0x14000004 ) {
		NifStream( initialRotationSpeedVariation, out, info );
		NifStream( initialRotationAngle, out, info );
		NifStream( initialRotationAngleVariation, out, info );
		NifStream( randomRotSpeedSign, out, info );
	};
	NifStream( randomInitialAxis, out, info );
	NifStream( initialAxis, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPSysRotationModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifier::asString();
	out << "  Initial Rotation Speed:  " << initialRotationSpeed << endl;
	out << "  Initial Rotation Speed Variation:  " << initialRotationSpeedVariation << endl;
	out << "  Initial Rotation Angle:  " << initialRotationAngle << endl;
	out << "  Initial Rotation Angle Variation:  " << initialRotationAngleVariation << endl;
	out << "  Random Rot Speed Sign:  " << randomRotSpeedSign << endl;
	out << "  Random Initial Axis:  " << randomInitialAxis << endl;
	out << "  Initial Axis:  " << initialAxis << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysRotationModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysRotationModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysRotationModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
