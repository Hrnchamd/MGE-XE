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
#include "../../include/obj/bhkAabbPhantom.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkAabbPhantom::TYPE("bhkAabbPhantom", &bhkShapePhantom::TYPE );

bhkAabbPhantom::bhkAabbPhantom() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

bhkAabbPhantom::~bhkAabbPhantom() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & bhkAabbPhantom::GetType() const {
	return TYPE;
}

NiObject * bhkAabbPhantom::Create() {
	return new bhkAabbPhantom;
}

void bhkAabbPhantom::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkShapePhantom::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 15; i1++) {
		NifStream( unknownInts1[i1], in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void bhkAabbPhantom::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkShapePhantom::Write( out, link_map, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < 15; i1++) {
		NifStream( unknownInts1[i1], out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string bhkAabbPhantom::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkShapePhantom::asString();
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 15; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Ints 1[" << i1 << "]:  " << unknownInts1[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void bhkAabbPhantom::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkShapePhantom::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkAabbPhantom::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkShapePhantom::GetRefs();
	return refs;
}

std::list<NiObject *> bhkAabbPhantom::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkShapePhantom::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
