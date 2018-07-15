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
#include "../../include/obj/NiPSSphericalCollider.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSSphericalCollider::TYPE("NiPSSphericalCollider", &NiObject::TYPE );

NiPSSphericalCollider::NiPSSphericalCollider() : unknown1((int)0), unknown2((int)0), unknown3((byte)0), unknown4(0.0f), unknown5((int)0), unknown6((short)0), unknown7((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSSphericalCollider::~NiPSSphericalCollider() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSSphericalCollider::GetType() const {
	return TYPE;
}

NiObject * NiPSSphericalCollider::Create() {
	return new NiPSSphericalCollider;
}

void NiPSSphericalCollider::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( unknown1, in, info );
	NifStream( unknown2, in, info );
	NifStream( unknown3, in, info );
	NifStream( unknown4, in, info );
	NifStream( unknown5, in, info );
	NifStream( unknown6, in, info );
	NifStream( unknown7, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSSphericalCollider::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	NifStream( unknown1, out, info );
	NifStream( unknown2, out, info );
	NifStream( unknown3, out, info );
	NifStream( unknown4, out, info );
	NifStream( unknown5, out, info );
	NifStream( unknown6, out, info );
	NifStream( unknown7, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSSphericalCollider::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiObject::asString();
	out << "  Unknown 1:  " << unknown1 << endl;
	out << "  Unknown 2:  " << unknown2 << endl;
	out << "  Unknown 3:  " << unknown3 << endl;
	out << "  Unknown 4:  " << unknown4 << endl;
	out << "  Unknown 5:  " << unknown5 << endl;
	out << "  Unknown 6:  " << unknown6 << endl;
	out << "  Unknown 7:  " << unknown7 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSSphericalCollider::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSSphericalCollider::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSSphericalCollider::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
