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
#include "../../include/obj/bhkBallAndSocketConstraint.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkBallAndSocketConstraint::TYPE("bhkBallAndSocketConstraint", &bhkConstraint::TYPE );

bhkBallAndSocketConstraint::bhkBallAndSocketConstraint() : unknownInt1((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

bhkBallAndSocketConstraint::~bhkBallAndSocketConstraint() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & bhkBallAndSocketConstraint::GetType() const {
	return TYPE;
}

NiObject * bhkBallAndSocketConstraint::Create() {
	return new bhkBallAndSocketConstraint;
}

void bhkBallAndSocketConstraint::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkConstraint::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknown4Bytes[i1], in, info );
	};
	NifStream( unknownFloats1, in, info );
	NifStream( unknownFloats2, in, info );
	NifStream( unknownInt1, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void bhkBallAndSocketConstraint::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkConstraint::Write( out, link_map, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknown4Bytes[i1], out, info );
	};
	NifStream( unknownFloats1, out, info );
	NifStream( unknownFloats2, out, info );
	NifStream( unknownInt1, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string bhkBallAndSocketConstraint::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkConstraint::asString();
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 4 bytes[" << i1 << "]:  " << unknown4Bytes[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Floats 1:  " << unknownFloats1 << endl;
	out << "  Unknown Floats 2:  " << unknownFloats2 << endl;
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void bhkBallAndSocketConstraint::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkConstraint::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkBallAndSocketConstraint::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkConstraint::GetRefs();
	return refs;
}

std::list<NiObject *> bhkBallAndSocketConstraint::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkConstraint::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
