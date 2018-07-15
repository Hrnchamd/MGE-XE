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
#include "../../include/obj/bhkBallSocketConstraintChain.h"
#include "../../include/obj/NiObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkBallSocketConstraintChain::TYPE("bhkBallSocketConstraintChain", &bhkSerializable::TYPE );

bhkBallSocketConstraintChain::bhkBallSocketConstraintChain() : numFloats((unsigned int)0), unknownFloat1(0.0f), unknownFloat2(0.0f), unknownInt1((unsigned int)0), unknownInt2((unsigned int)0), numLinks((unsigned int)0), numLinks2((unsigned int)0), unknownInt3((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

bhkBallSocketConstraintChain::~bhkBallSocketConstraintChain() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & bhkBallSocketConstraintChain::GetType() const {
	return TYPE;
}

NiObject * bhkBallSocketConstraintChain::Create() {
	return new bhkBallSocketConstraintChain;
}

void bhkBallSocketConstraintChain::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	bhkSerializable::Read( in, link_stack, info );
	NifStream( numFloats, in, info );
	floats1.resize(numFloats);
	for (unsigned int i1 = 0; i1 < floats1.size(); i1++) {
		NifStream( floats1[i1], in, info );
	};
	NifStream( unknownFloat1, in, info );
	NifStream( unknownFloat2, in, info );
	NifStream( unknownInt1, in, info );
	NifStream( unknownInt2, in, info );
	NifStream( numLinks, in, info );
	links.resize(numLinks);
	for (unsigned int i1 = 0; i1 < links.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( numLinks2, in, info );
	links2.resize(numLinks2);
	for (unsigned int i1 = 0; i1 < links2.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( unknownInt3, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void bhkBallSocketConstraintChain::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkSerializable::Write( out, link_map, missing_link_stack, info );
	numLinks2 = (unsigned int)(links2.size());
	numLinks = (unsigned int)(links.size());
	numFloats = (unsigned int)(floats1.size());
	NifStream( numFloats, out, info );
	for (unsigned int i1 = 0; i1 < floats1.size(); i1++) {
		NifStream( floats1[i1], out, info );
	};
	NifStream( unknownFloat1, out, info );
	NifStream( unknownFloat2, out, info );
	NifStream( unknownInt1, out, info );
	NifStream( unknownInt2, out, info );
	NifStream( numLinks, out, info );
	for (unsigned int i1 = 0; i1 < links.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*links[i1]), out );
		} else {
			if ( links[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(links[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( links[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( numLinks2, out, info );
	for (unsigned int i1 = 0; i1 < links2.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*links2[i1]), out );
		} else {
			if ( links2[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(links2[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( links2[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( unknownInt3, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string bhkBallSocketConstraintChain::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkSerializable::asString();
	numLinks2 = (unsigned int)(links2.size());
	numLinks = (unsigned int)(links.size());
	numFloats = (unsigned int)(floats1.size());
	out << "  Num Floats:  " << numFloats << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < floats1.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Floats 1[" << i1 << "]:  " << floats1[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Num Links:  " << numLinks << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < links.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Links[" << i1 << "]:  " << links[i1] << endl;
		array_output_count++;
	};
	out << "  Num Links 2:  " << numLinks2 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < links2.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Links 2[" << i1 << "]:  " << links2[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Int 3:  " << unknownInt3 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void bhkBallSocketConstraintChain::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkSerializable::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < links.size(); i1++) {
		links[i1] = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	};
	for (unsigned int i1 = 0; i1 < links2.size(); i1++) {
		links2[i1] = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkBallSocketConstraintChain::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkSerializable::GetRefs();
	for (unsigned int i1 = 0; i1 < links.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < links2.size(); i1++) {
	};
	return refs;
}

std::list<NiObject *> bhkBallSocketConstraintChain::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkSerializable::GetPtrs();
	for (unsigned int i1 = 0; i1 < links.size(); i1++) {
		if ( links[i1] != NULL )
			ptrs.push_back((NiObject *)(links[i1]));
	};
	for (unsigned int i1 = 0; i1 < links2.size(); i1++) {
		if ( links2[i1] != NULL )
			ptrs.push_back((NiObject *)(links2[i1]));
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
