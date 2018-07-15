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
#include "../../include/obj/NiPlanarCollider.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPlanarCollider::TYPE("NiPlanarCollider", &NiParticleModifier::TYPE );

NiPlanarCollider::NiPlanarCollider() : unknownShort((unsigned short)0), unknownFloat1(0.0f), unknownFloat2(0.0f), unknownShort2((unsigned short)0), unknownFloat3(0.0f), unknownFloat4(0.0f), unknownFloat5(0.0f), unknownFloat6(0.0f), unknownFloat7(0.0f), unknownFloat8(0.0f), unknownFloat9(0.0f), unknownFloat10(0.0f), unknownFloat11(0.0f), unknownFloat12(0.0f), unknownFloat13(0.0f), unknownFloat14(0.0f), unknownFloat15(0.0f), unknownFloat16(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiPlanarCollider::~NiPlanarCollider() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiPlanarCollider::GetType() const {
	return TYPE;
}

NiObject * NiPlanarCollider::Create() {
	return new NiPlanarCollider;
}

void NiPlanarCollider::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::Read( in, link_stack, info );
	if ( info.version >= 0x0A000100 ) {
		NifStream( unknownShort, in, info );
	};
	NifStream( unknownFloat1, in, info );
	NifStream( unknownFloat2, in, info );
	if ( ( info.version >= 0x04020200 ) && ( info.version <= 0x04020200 ) ) {
		NifStream( unknownShort2, in, info );
	};
	NifStream( unknownFloat3, in, info );
	NifStream( unknownFloat4, in, info );
	NifStream( unknownFloat5, in, info );
	NifStream( unknownFloat6, in, info );
	NifStream( unknownFloat7, in, info );
	NifStream( unknownFloat8, in, info );
	NifStream( unknownFloat9, in, info );
	NifStream( unknownFloat10, in, info );
	NifStream( unknownFloat11, in, info );
	NifStream( unknownFloat12, in, info );
	NifStream( unknownFloat13, in, info );
	NifStream( unknownFloat14, in, info );
	NifStream( unknownFloat15, in, info );
	NifStream( unknownFloat16, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPlanarCollider::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::Write( out, link_map, missing_link_stack, info );
	if ( info.version >= 0x0A000100 ) {
		NifStream( unknownShort, out, info );
	};
	NifStream( unknownFloat1, out, info );
	NifStream( unknownFloat2, out, info );
	if ( ( info.version >= 0x04020200 ) && ( info.version <= 0x04020200 ) ) {
		NifStream( unknownShort2, out, info );
	};
	NifStream( unknownFloat3, out, info );
	NifStream( unknownFloat4, out, info );
	NifStream( unknownFloat5, out, info );
	NifStream( unknownFloat6, out, info );
	NifStream( unknownFloat7, out, info );
	NifStream( unknownFloat8, out, info );
	NifStream( unknownFloat9, out, info );
	NifStream( unknownFloat10, out, info );
	NifStream( unknownFloat11, out, info );
	NifStream( unknownFloat12, out, info );
	NifStream( unknownFloat13, out, info );
	NifStream( unknownFloat14, out, info );
	NifStream( unknownFloat15, out, info );
	NifStream( unknownFloat16, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiPlanarCollider::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiParticleModifier::asString();
	out << "  Unknown Short:  " << unknownShort << endl;
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Unknown Short 2:  " << unknownShort2 << endl;
	out << "  Unknown Float 3:  " << unknownFloat3 << endl;
	out << "  Unknown Float 4:  " << unknownFloat4 << endl;
	out << "  Unknown Float 5:  " << unknownFloat5 << endl;
	out << "  Unknown Float 6:  " << unknownFloat6 << endl;
	out << "  Unknown Float 7:  " << unknownFloat7 << endl;
	out << "  Unknown Float 8:  " << unknownFloat8 << endl;
	out << "  Unknown Float 9:  " << unknownFloat9 << endl;
	out << "  Unknown Float 10:  " << unknownFloat10 << endl;
	out << "  Unknown Float 11:  " << unknownFloat11 << endl;
	out << "  Unknown Float 12:  " << unknownFloat12 << endl;
	out << "  Unknown Float 13:  " << unknownFloat13 << endl;
	out << "  Unknown Float 14:  " << unknownFloat14 << endl;
	out << "  Unknown Float 15:  " << unknownFloat15 << endl;
	out << "  Unknown Float 16:  " << unknownFloat16 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiPlanarCollider::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticleModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPlanarCollider::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiParticleModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiPlanarCollider::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiParticleModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
