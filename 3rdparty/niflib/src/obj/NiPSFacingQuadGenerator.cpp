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
#include "../../include/obj/NiPSFacingQuadGenerator.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSFacingQuadGenerator::TYPE("NiPSFacingQuadGenerator", &NiObject::TYPE );

NiPSFacingQuadGenerator::NiPSFacingQuadGenerator() : unknown1((byte)0), unknown2((byte)0), unknown3((byte)0), unknown4((byte)0), unknown5((byte)0), unknown6((byte)0), unknown7((byte)0), unknown8((byte)0), unknown9((byte)0), unknown10((byte)0), unknown11((byte)0), unknown12((byte)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSFacingQuadGenerator::~NiPSFacingQuadGenerator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSFacingQuadGenerator::GetType() const {
	return TYPE;
}

NiObject * NiPSFacingQuadGenerator::Create() {
	return new NiPSFacingQuadGenerator;
}

void NiPSFacingQuadGenerator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
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
	NifStream( unknown8, in, info );
	NifStream( unknown9, in, info );
	NifStream( unknown10, in, info );
	NifStream( unknown11, in, info );
	NifStream( unknown12, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSFacingQuadGenerator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
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
	NifStream( unknown8, out, info );
	NifStream( unknown9, out, info );
	NifStream( unknown10, out, info );
	NifStream( unknown11, out, info );
	NifStream( unknown12, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSFacingQuadGenerator::asString( bool verbose ) const {
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
	out << "  Unknown 8:  " << unknown8 << endl;
	out << "  Unknown 9:  " << unknown9 << endl;
	out << "  Unknown 10:  " << unknown10 << endl;
	out << "  Unknown 11:  " << unknown11 << endl;
	out << "  Unknown 12:  " << unknown12 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSFacingQuadGenerator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSFacingQuadGenerator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSFacingQuadGenerator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
