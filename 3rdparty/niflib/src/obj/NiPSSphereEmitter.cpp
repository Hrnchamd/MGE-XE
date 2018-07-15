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
#include "../../include/obj/NiPSSphereEmitter.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSSphereEmitter::TYPE("NiPSSphereEmitter", &NiObject::TYPE );

NiPSSphereEmitter::NiPSSphereEmitter() : unknown2((int)0), unknown3((int)0), unknown4((int)0), unknown5((int)0), unknown6(0.0f), unknown7((int)0), unknown8(0.0f), unknown9(0.0f), unknown10((int)0), unknown11(0.0f), unknown12((int)0), unknown13((int)0), unknown14((int)0), unknown15((int)0), unknown16((int)0), unknown17(0.0f), unknown18((int)0), unknown19((int)0), unknown20((short)0), unknown21((int)0), unknown22(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSSphereEmitter::~NiPSSphereEmitter() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSSphereEmitter::GetType() const {
	return TYPE;
}

NiObject * NiPSSphereEmitter::Create() {
	return new NiPSSphereEmitter;
}

void NiPSSphereEmitter::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( name, in, info );
	NifStream( unknown2, in, info );
	NifStream( unknown3, in, info );
	NifStream( unknown4, in, info );
	NifStream( unknown5, in, info );
	NifStream( unknown6, in, info );
	NifStream( unknown7, in, info );
	NifStream( unknown8, in, info );
	NifStream( unknown9, in, info );
	NifStream( unknown10, in, info );
	NifStream( unknown11, in, info );
	NifStream( unknown12, in, info );
	NifStream( unknown13, in, info );
	NifStream( unknown14, in, info );
	NifStream( unknown15, in, info );
	NifStream( unknown16, in, info );
	NifStream( unknown17, in, info );
	NifStream( unknown18, in, info );
	NifStream( unknown19, in, info );
	NifStream( unknown20, in, info );
	NifStream( unknown21, in, info );
	NifStream( unknown22, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSSphereEmitter::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	NifStream( name, out, info );
	NifStream( unknown2, out, info );
	NifStream( unknown3, out, info );
	NifStream( unknown4, out, info );
	NifStream( unknown5, out, info );
	NifStream( unknown6, out, info );
	NifStream( unknown7, out, info );
	NifStream( unknown8, out, info );
	NifStream( unknown9, out, info );
	NifStream( unknown10, out, info );
	NifStream( unknown11, out, info );
	NifStream( unknown12, out, info );
	NifStream( unknown13, out, info );
	NifStream( unknown14, out, info );
	NifStream( unknown15, out, info );
	NifStream( unknown16, out, info );
	NifStream( unknown17, out, info );
	NifStream( unknown18, out, info );
	NifStream( unknown19, out, info );
	NifStream( unknown20, out, info );
	NifStream( unknown21, out, info );
	NifStream( unknown22, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSSphereEmitter::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiObject::asString();
	out << "  Name:  " << name << endl;
	out << "  Unknown 2:  " << unknown2 << endl;
	out << "  Unknown 3:  " << unknown3 << endl;
	out << "  Unknown 4:  " << unknown4 << endl;
	out << "  Unknown 5:  " << unknown5 << endl;
	out << "  Unknown 6:  " << unknown6 << endl;
	out << "  Unknown 7:  " << unknown7 << endl;
	out << "  Unknown 8:  " << unknown8 << endl;
	out << "  Unknown 9:  " << unknown9 << endl;
	out << "  Unknown 10:  " << unknown10 << endl;
	out << "  Unknown 11:  " << unknown11 << endl;
	out << "  Unknown 12:  " << unknown12 << endl;
	out << "  Unknown 13:  " << unknown13 << endl;
	out << "  Unknown 14:  " << unknown14 << endl;
	out << "  Unknown 15:  " << unknown15 << endl;
	out << "  Unknown 16:  " << unknown16 << endl;
	out << "  Unknown 17:  " << unknown17 << endl;
	out << "  Unknown 18:  " << unknown18 << endl;
	out << "  Unknown 19:  " << unknown19 << endl;
	out << "  Unknown 20:  " << unknown20 << endl;
	out << "  Unknown 21:  " << unknown21 << endl;
	out << "  Unknown 22:  " << unknown22 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSSphereEmitter::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSSphereEmitter::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSSphereEmitter::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
