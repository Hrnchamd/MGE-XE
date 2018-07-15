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
#include "../../include/obj/NiPSMeshEmitter.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSMeshEmitter::TYPE("NiPSMeshEmitter", &NiObject::TYPE );

NiPSMeshEmitter::NiPSMeshEmitter() : unknown1((int)0), unknown2((int)0), unknown3((int)0), unknown27((int)0), unknown4(0.0f), unknown5(0.0f), unknown6(0.0f), unknown28(0.0f), unknown7((int)0), unknown8(0.0f), unknown9(0.0f), unknown10(0.0f), unknown11(0.0f), unknown12(0.0f), unknown13((int)0), unknown14(0.0f), unknown15(0.0f), unknown16(0.0f), unknown17((int)0), unknown18((int)0), unknown19((short)0), unknown20((int)0), unknown21((int)0), unknown22(0.0f), unknown23((int)0), unknown24((int)0), unknown25((int)0), unknown26((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSMeshEmitter::~NiPSMeshEmitter() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSMeshEmitter::GetType() const {
	return TYPE;
}

NiObject * NiPSMeshEmitter::Create() {
	return new NiPSMeshEmitter;
}

void NiPSMeshEmitter::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( name, in, info );
	NifStream( unknown1, in, info );
	NifStream( unknown2, in, info );
	NifStream( unknown3, in, info );
	if ( info.version >= 0x1E000002 ) {
		NifStream( unknown27, in, info );
	};
	NifStream( unknown4, in, info );
	NifStream( unknown5, in, info );
	NifStream( unknown6, in, info );
	if ( info.version >= 0x1E000002 ) {
		NifStream( unknown28, in, info );
	};
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
	if ( info.version <= 0x14060000 ) {
		NifStream( unknown17, in, info );
		NifStream( unknown18, in, info );
	};
	NifStream( unknown19, in, info );
	NifStream( unknown20, in, info );
	NifStream( unknown21, in, info );
	if ( info.version <= 0x14060000 ) {
		NifStream( unknown22, in, info );
		NifStream( unknown23, in, info );
	};
	NifStream( unknown24, in, info );
	NifStream( unknown25, in, info );
	NifStream( unknown26, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSMeshEmitter::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	NifStream( name, out, info );
	NifStream( unknown1, out, info );
	NifStream( unknown2, out, info );
	NifStream( unknown3, out, info );
	if ( info.version >= 0x1E000002 ) {
		NifStream( unknown27, out, info );
	};
	NifStream( unknown4, out, info );
	NifStream( unknown5, out, info );
	NifStream( unknown6, out, info );
	if ( info.version >= 0x1E000002 ) {
		NifStream( unknown28, out, info );
	};
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
	if ( info.version <= 0x14060000 ) {
		NifStream( unknown17, out, info );
		NifStream( unknown18, out, info );
	};
	NifStream( unknown19, out, info );
	NifStream( unknown20, out, info );
	NifStream( unknown21, out, info );
	if ( info.version <= 0x14060000 ) {
		NifStream( unknown22, out, info );
		NifStream( unknown23, out, info );
	};
	NifStream( unknown24, out, info );
	NifStream( unknown25, out, info );
	NifStream( unknown26, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSMeshEmitter::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiObject::asString();
	out << "  Name:  " << name << endl;
	out << "  Unknown 1:  " << unknown1 << endl;
	out << "  Unknown 2:  " << unknown2 << endl;
	out << "  Unknown 3:  " << unknown3 << endl;
	out << "  Unknown 27:  " << unknown27 << endl;
	out << "  Unknown 4:  " << unknown4 << endl;
	out << "  Unknown 5:  " << unknown5 << endl;
	out << "  Unknown 6:  " << unknown6 << endl;
	out << "  Unknown 28:  " << unknown28 << endl;
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
	out << "  Unknown 23:  " << unknown23 << endl;
	out << "  Unknown 24:  " << unknown24 << endl;
	out << "  Unknown 25:  " << unknown25 << endl;
	out << "  Unknown 26:  " << unknown26 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSMeshEmitter::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSMeshEmitter::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSMeshEmitter::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
