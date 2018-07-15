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
#include "../../include/obj/NiPSysEmitter.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysEmitter::TYPE("NiPSysEmitter", &NiPSysModifier::TYPE );

NiPSysEmitter::NiPSysEmitter() : speed(0.0f), speedVariation(0.0f), declination(0.0f), declinationVariation(0.0f), planarAngle(0.0f), planarAngleVariation(0.0f), initialRadius(0.0f), radiusVariation(0.0f), lifeSpan(0.0f), lifeSpanVariation(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPSysEmitter::~NiPSysEmitter() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPSysEmitter::GetType() const {
	return TYPE;
}

NiObject * NiPSysEmitter::Create() {
	return new NiPSysEmitter;
}

void NiPSysEmitter::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::Read( in, link_stack, info );
	NifStream( speed, in, info );
	NifStream( speedVariation, in, info );
	NifStream( declination, in, info );
	NifStream( declinationVariation, in, info );
	NifStream( planarAngle, in, info );
	NifStream( planarAngleVariation, in, info );
	NifStream( initialColor, in, info );
	NifStream( initialRadius, in, info );
	if ( info.version >= 0x0A040001 ) {
		NifStream( radiusVariation, in, info );
	};
	NifStream( lifeSpan, in, info );
	NifStream( lifeSpanVariation, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysEmitter::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::Write( out, link_map, missing_link_stack, info );
	NifStream( speed, out, info );
	NifStream( speedVariation, out, info );
	NifStream( declination, out, info );
	NifStream( declinationVariation, out, info );
	NifStream( planarAngle, out, info );
	NifStream( planarAngleVariation, out, info );
	NifStream( initialColor, out, info );
	NifStream( initialRadius, out, info );
	if ( info.version >= 0x0A040001 ) {
		NifStream( radiusVariation, out, info );
	};
	NifStream( lifeSpan, out, info );
	NifStream( lifeSpanVariation, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPSysEmitter::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysModifier::asString();
	out << "  Speed:  " << speed << endl;
	out << "  Speed Variation:  " << speedVariation << endl;
	out << "  Declination:  " << declination << endl;
	out << "  Declination Variation:  " << declinationVariation << endl;
	out << "  Planar Angle:  " << planarAngle << endl;
	out << "  Planar Angle Variation:  " << planarAngleVariation << endl;
	out << "  Initial Color:  " << initialColor << endl;
	out << "  Initial Radius:  " << initialRadius << endl;
	out << "  Radius Variation:  " << radiusVariation << endl;
	out << "  Life Span:  " << lifeSpan << endl;
	out << "  Life Span Variation:  " << lifeSpanVariation << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPSysEmitter::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiPSysModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysEmitter::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysEmitter::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
