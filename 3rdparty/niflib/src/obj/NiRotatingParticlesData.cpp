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
#include "../../include/obj/NiRotatingParticlesData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiRotatingParticlesData::TYPE("NiRotatingParticlesData", &NiParticlesData::TYPE );

NiRotatingParticlesData::NiRotatingParticlesData() : hasRotations2(false) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiRotatingParticlesData::~NiRotatingParticlesData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiRotatingParticlesData::GetType() const {
	return TYPE;
}

NiObject * NiRotatingParticlesData::Create() {
	return new NiRotatingParticlesData;
}

void NiRotatingParticlesData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticlesData::Read( in, link_stack, info );
	if ( info.version <= 0x04020200 ) {
		NifStream( hasRotations2, in, info );
		if ( hasRotations2 ) {
			rotations2.resize(numVertices);
			for (unsigned int i3 = 0; i3 < rotations2.size(); i3++) {
				NifStream( rotations2[i3], in, info );
			};
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiRotatingParticlesData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticlesData::Write( out, link_map, missing_link_stack, info );
	if ( info.version <= 0x04020200 ) {
		NifStream( hasRotations2, out, info );
		if ( hasRotations2 ) {
			for (unsigned int i3 = 0; i3 < rotations2.size(); i3++) {
				NifStream( rotations2[i3], out, info );
			};
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiRotatingParticlesData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiParticlesData::asString();
	out << "  Has Rotations 2:  " << hasRotations2 << endl;
	if ( hasRotations2 ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < rotations2.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Rotations 2[" << i2 << "]:  " << rotations2[i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiRotatingParticlesData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiParticlesData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiRotatingParticlesData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiParticlesData::GetRefs();
	return refs;
}

std::list<NiObject *> NiRotatingParticlesData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiParticlesData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
