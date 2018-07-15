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
#include "../../include/obj/bhkBreakableConstraint.h"
#include "../../include/obj/bhkEntity.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkBreakableConstraint::TYPE("bhkBreakableConstraint", &bhkConstraint::TYPE );

bhkBreakableConstraint::bhkBreakableConstraint() : unknownShort1((short)0), unknownInt1((unsigned int)0), numEntities2((unsigned int)0), priority2((unsigned int)1), unknownInt2((unsigned int)0), unknownInt3((unsigned int)0), threshold(0.0f), unknownFloat1(0.0f), removeIfBroken((byte)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

bhkBreakableConstraint::~bhkBreakableConstraint() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & bhkBreakableConstraint::GetType() const {
	return TYPE;
}

NiObject * bhkBreakableConstraint::Create() {
	return new bhkBreakableConstraint;
}

void bhkBreakableConstraint::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	bhkConstraint::Read( in, link_stack, info );
	if ( (info.userVersion <= 11) ) {
		for (unsigned int i2 = 0; i2 < 41; i2++) {
			NifStream( unknownInts1[i2], in, info );
		};
		NifStream( unknownShort1, in, info );
	};
	if ( (info.userVersion == 12) ) {
		NifStream( unknownInt1, in, info );
		NifStream( numEntities2, in, info );
		entities2.resize(numEntities2);
		for (unsigned int i2 = 0; i2 < entities2.size(); i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
		NifStream( priority2, in, info );
		NifStream( unknownInt2, in, info );
		NifStream( position, in, info );
		NifStream( rotation, in, info );
		NifStream( unknownInt3, in, info );
		NifStream( threshold, in, info );
		if ( (unknownInt1 >= 1) ) {
			NifStream( unknownFloat1, in, info );
		};
		NifStream( removeIfBroken, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void bhkBreakableConstraint::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkConstraint::Write( out, link_map, missing_link_stack, info );
	numEntities2 = (unsigned int)(entities2.size());
	if ( (info.userVersion <= 11) ) {
		for (unsigned int i2 = 0; i2 < 41; i2++) {
			NifStream( unknownInts1[i2], out, info );
		};
		NifStream( unknownShort1, out, info );
	};
	if ( (info.userVersion == 12) ) {
		NifStream( unknownInt1, out, info );
		NifStream( numEntities2, out, info );
		for (unsigned int i2 = 0; i2 < entities2.size(); i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*entities2[i2]), out );
			} else {
				if ( entities2[i2] != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(entities2[i2]) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( entities2[i2] );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
		NifStream( priority2, out, info );
		NifStream( unknownInt2, out, info );
		NifStream( position, out, info );
		NifStream( rotation, out, info );
		NifStream( unknownInt3, out, info );
		NifStream( threshold, out, info );
		if ( (unknownInt1 >= 1) ) {
			NifStream( unknownFloat1, out, info );
		};
		NifStream( removeIfBroken, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string bhkBreakableConstraint::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkConstraint::asString();
	numEntities2 = (unsigned int)(entities2.size());
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 41; i1++) {
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
	out << "  Unknown Short 1:  " << unknownShort1 << endl;
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Num Entities 2:  " << numEntities2 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < entities2.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Entities 2[" << i1 << "]:  " << entities2[i1] << endl;
		array_output_count++;
	};
	out << "  Priority 2:  " << priority2 << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Position:  " << position << endl;
	out << "  Rotation:  " << rotation << endl;
	out << "  Unknown Int 3:  " << unknownInt3 << endl;
	out << "  Threshold:  " << threshold << endl;
	if ( (unknownInt1 >= 1) ) {
		out << "    Unknown Float 1:  " << unknownFloat1 << endl;
	};
	out << "  Remove if Broken:  " << removeIfBroken << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void bhkBreakableConstraint::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkConstraint::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( (info.userVersion == 12) ) {
		for (unsigned int i2 = 0; i2 < entities2.size(); i2++) {
			entities2[i2] = FixLink<bhkEntity>( objects, link_stack, missing_link_stack, info );
		};
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkBreakableConstraint::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkConstraint::GetRefs();
	for (unsigned int i1 = 0; i1 < entities2.size(); i1++) {
	};
	return refs;
}

std::list<NiObject *> bhkBreakableConstraint::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkConstraint::GetPtrs();
	for (unsigned int i1 = 0; i1 < entities2.size(); i1++) {
		if ( entities2[i1] != NULL )
			ptrs.push_back((NiObject *)(entities2[i1]));
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
