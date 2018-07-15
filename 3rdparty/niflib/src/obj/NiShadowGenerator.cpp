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
#include "../../include/obj/NiShadowGenerator.h"
#include "../../include/obj/NiLight.h"
#include "../../include/obj/NiNode.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiShadowGenerator::TYPE("NiShadowGenerator", &NiObject::TYPE );

NiShadowGenerator::NiShadowGenerator() : unknownFlags((unsigned short)0), numUnknownLinks1((unsigned int)0), unkownInt2((int)0), target(NULL), unkownFloat4(0.98f), unkownByte5((byte)0), unkownInt6((int)2), unkownInt7((int)0), unkownInt8((int)0), unkownByte9((byte)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiShadowGenerator::~NiShadowGenerator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiShadowGenerator::GetType() const {
	return TYPE;
}

NiObject * NiShadowGenerator::Create() {
	return new NiShadowGenerator;
}

void NiShadowGenerator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( name, in, info );
	NifStream( unknownFlags, in, info );
	NifStream( numUnknownLinks1, in, info );
	unknownLinks1.resize(numUnknownLinks1);
	for (unsigned int i1 = 0; i1 < unknownLinks1.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( unkownInt2, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( unkownFloat4, in, info );
	NifStream( unkownByte5, in, info );
	NifStream( unkownInt6, in, info );
	NifStream( unkownInt7, in, info );
	NifStream( unkownInt8, in, info );
	NifStream( unkownByte9, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiShadowGenerator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	numUnknownLinks1 = (unsigned int)(unknownLinks1.size());
	NifStream( name, out, info );
	NifStream( unknownFlags, out, info );
	NifStream( numUnknownLinks1, out, info );
	for (unsigned int i1 = 0; i1 < unknownLinks1.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*unknownLinks1[i1]), out );
		} else {
			if ( unknownLinks1[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(unknownLinks1[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( unknownLinks1[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( unkownInt2, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*target), out );
	} else {
		if ( target != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(target) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( target );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	NifStream( unkownFloat4, out, info );
	NifStream( unkownByte5, out, info );
	NifStream( unkownInt6, out, info );
	NifStream( unkownInt7, out, info );
	NifStream( unkownInt8, out, info );
	NifStream( unkownByte9, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiShadowGenerator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numUnknownLinks1 = (unsigned int)(unknownLinks1.size());
	out << "  Name:  " << name << endl;
	out << "  Unknown Flags:  " << unknownFlags << endl;
	out << "  Num Unknown Links 1:  " << numUnknownLinks1 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknownLinks1.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Links 1[" << i1 << "]:  " << unknownLinks1[i1] << endl;
		array_output_count++;
	};
	out << "  Unkown Int 2:  " << unkownInt2 << endl;
	out << "  Target:  " << target << endl;
	out << "  Unkown Float 4:  " << unkownFloat4 << endl;
	out << "  Unkown Byte 5:  " << unkownByte5 << endl;
	out << "  Unkown Int 6:  " << unkownInt6 << endl;
	out << "  Unkown Int 7:  " << unkownInt7 << endl;
	out << "  Unkown Int 8:  " << unkownInt8 << endl;
	out << "  Unkown Byte 9:  " << unkownByte9 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiShadowGenerator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < unknownLinks1.size(); i1++) {
		unknownLinks1[i1] = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );
	};
	target = FixLink<NiLight>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiShadowGenerator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	for (unsigned int i1 = 0; i1 < unknownLinks1.size(); i1++) {
		if ( unknownLinks1[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(unknownLinks1[i1]));
	};
	return refs;
}

std::list<NiObject *> NiShadowGenerator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	for (unsigned int i1 = 0; i1 < unknownLinks1.size(); i1++) {
	};
	if ( target != NULL )
		ptrs.push_back((NiObject *)(target));
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
