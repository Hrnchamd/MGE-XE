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
#include "../../include/obj/NiPSysTrailEmitter.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSysTrailEmitter::TYPE("NiPSysTrailEmitter", &NiPSysEmitter::TYPE );

NiPSysTrailEmitter::NiPSysTrailEmitter() : unknownInt1((int)0), unknownFloat1(0.0f), unknownFloat2(0.0f), unknownFloat3(0.0f), unknownInt2((int)0), unknownFloat4(0.0f), unknownInt3((int)0), unknownFloat5(0.0f), unknownInt4((int)0), unknownFloat6(0.0f), unknownFloat7(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSysTrailEmitter::~NiPSysTrailEmitter() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSysTrailEmitter::GetType() const {
	return TYPE;
}

NiObject * NiPSysTrailEmitter::Create() {
	return new NiPSysTrailEmitter;
}

void NiPSysTrailEmitter::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysEmitter::Read( in, link_stack, info );
	NifStream( unknownInt1, in, info );
	NifStream( unknownFloat1, in, info );
	NifStream( unknownFloat2, in, info );
	NifStream( unknownFloat3, in, info );
	NifStream( unknownInt2, in, info );
	NifStream( unknownFloat4, in, info );
	NifStream( unknownInt3, in, info );
	NifStream( unknownFloat5, in, info );
	NifStream( unknownInt4, in, info );
	NifStream( unknownFloat6, in, info );
	NifStream( unknownFloat7, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysTrailEmitter::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysEmitter::Write( out, link_map, missing_link_stack, info );
	NifStream( unknownInt1, out, info );
	NifStream( unknownFloat1, out, info );
	NifStream( unknownFloat2, out, info );
	NifStream( unknownFloat3, out, info );
	NifStream( unknownInt2, out, info );
	NifStream( unknownFloat4, out, info );
	NifStream( unknownInt3, out, info );
	NifStream( unknownFloat5, out, info );
	NifStream( unknownInt4, out, info );
	NifStream( unknownFloat6, out, info );
	NifStream( unknownFloat7, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSysTrailEmitter::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiPSysEmitter::asString();
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Unknown Float 3:  " << unknownFloat3 << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Unknown Float 4:  " << unknownFloat4 << endl;
	out << "  Unknown Int 3:  " << unknownInt3 << endl;
	out << "  Unknown Float 5:  " << unknownFloat5 << endl;
	out << "  Unknown Int 4:  " << unknownInt4 << endl;
	out << "  Unknown Float 6:  " << unknownFloat6 << endl;
	out << "  Unknown Float 7:  " << unknownFloat7 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSysTrailEmitter::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSysEmitter::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSysTrailEmitter::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSysEmitter::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSysTrailEmitter::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSysEmitter::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
