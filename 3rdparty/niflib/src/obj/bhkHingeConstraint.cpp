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
#include "../../include/obj/bhkHingeConstraint.h"
#include "../../include/gen/HingeDescriptor.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkHingeConstraint::TYPE("bhkHingeConstraint", &bhkConstraint::TYPE );

bhkHingeConstraint::bhkHingeConstraint() {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkHingeConstraint::~bhkHingeConstraint() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkHingeConstraint::GetType() const {
	return TYPE;
}

NiObject * bhkHingeConstraint::Create() {
	return new bhkHingeConstraint;
}

void bhkHingeConstraint::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkConstraint::Read( in, link_stack, info );
	if ( info.version <= 0x14000005 ) {
		NifStream( hinge.pivotA, in, info );
		NifStream( hinge.perp2AxleInA1, in, info );
		NifStream( hinge.perp2AxleInA2, in, info );
		NifStream( hinge.pivotB, in, info );
		NifStream( hinge.axleB, in, info );
	};
	if ( info.version >= 0x14020007 ) {
		NifStream( hinge.axleA, in, info );
		NifStream( hinge.perp2AxleInA1, in, info );
		NifStream( hinge.perp2AxleInA2, in, info );
		NifStream( hinge.pivotA, in, info );
		NifStream( hinge.axleB, in, info );
		NifStream( hinge.perp2AxleInB1, in, info );
		NifStream( hinge.perp2AxleInB2, in, info );
		NifStream( hinge.pivotB, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkHingeConstraint::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkConstraint::Write( out, link_map, missing_link_stack, info );
	if ( info.version <= 0x14000005 ) {
		NifStream( hinge.pivotA, out, info );
		NifStream( hinge.perp2AxleInA1, out, info );
		NifStream( hinge.perp2AxleInA2, out, info );
		NifStream( hinge.pivotB, out, info );
		NifStream( hinge.axleB, out, info );
	};
	if ( info.version >= 0x14020007 ) {
		NifStream( hinge.axleA, out, info );
		NifStream( hinge.perp2AxleInA1, out, info );
		NifStream( hinge.perp2AxleInA2, out, info );
		NifStream( hinge.pivotA, out, info );
		NifStream( hinge.axleB, out, info );
		NifStream( hinge.perp2AxleInB1, out, info );
		NifStream( hinge.perp2AxleInB2, out, info );
		NifStream( hinge.pivotB, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkHingeConstraint::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << bhkConstraint::asString();
	out << "  Pivot A:  " << hinge.pivotA << endl;
	out << "  Perp2 Axle In A1:  " << hinge.perp2AxleInA1 << endl;
	out << "  Perp2 Axle In A2:  " << hinge.perp2AxleInA2 << endl;
	out << "  Pivot B:  " << hinge.pivotB << endl;
	out << "  Axle B:  " << hinge.axleB << endl;
	out << "  Axle A:  " << hinge.axleA << endl;
	out << "  Perp2 Axle In B1:  " << hinge.perp2AxleInB1 << endl;
	out << "  Perp2 Axle In B2:  " << hinge.perp2AxleInB2 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkHingeConstraint::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkConstraint::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkHingeConstraint::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkConstraint::GetRefs();
	return refs;
}

std::list<NiObject *> bhkHingeConstraint::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkConstraint::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
