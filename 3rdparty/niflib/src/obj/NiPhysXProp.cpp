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
#include "../../include/obj/NiPhysXProp.h"
#include "../../include/obj/NiObject.h"
#include "../../include/obj/NiPhysXPropDesc.h"
#include "../../include/obj/NiPhysXTransformDest.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPhysXProp::TYPE("NiPhysXProp", &NiObjectNET::TYPE );

NiPhysXProp::NiPhysXProp() : unknownFloat1(0.0f), unknownInt1((unsigned int)0), numDests((int)0), unknownByte((byte)0), unknownInt((int)0), propDescription(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPhysXProp::~NiPhysXProp() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPhysXProp::GetType() const {
	return TYPE;
}

NiObject * NiPhysXProp::Create() {
	return new NiPhysXProp;
}

void NiPhysXProp::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObjectNET::Read( in, link_stack, info );
	NifStream( unknownFloat1, in, info );
	NifStream( unknownInt1, in, info );
	unknownRefs1.resize(unknownInt1);
	for (unsigned int i1 = 0; i1 < unknownRefs1.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( numDests, in, info );
	transformDests.resize(numDests);
	for (unsigned int i1 = 0; i1 < transformDests.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( unknownByte, in, info );
	if ( info.version >= 0x14050000 ) {
		NifStream( unknownInt, in, info );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPhysXProp::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObjectNET::Write( out, link_map, missing_link_stack, info );
	numDests = (int)(transformDests.size());
	unknownInt1 = (unsigned int)(unknownRefs1.size());
	NifStream( unknownFloat1, out, info );
	NifStream( unknownInt1, out, info );
	for (unsigned int i1 = 0; i1 < unknownRefs1.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*unknownRefs1[i1]), out );
		} else {
			if ( unknownRefs1[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(unknownRefs1[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( unknownRefs1[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( numDests, out, info );
	for (unsigned int i1 = 0; i1 < transformDests.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*transformDests[i1]), out );
		} else {
			if ( transformDests[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(transformDests[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( transformDests[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( unknownByte, out, info );
	if ( info.version >= 0x14050000 ) {
		NifStream( unknownInt, out, info );
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*propDescription), out );
	} else {
		if ( propDescription != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(propDescription) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( propDescription );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPhysXProp::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObjectNET::asString();
	numDests = (int)(transformDests.size());
	unknownInt1 = (unsigned int)(unknownRefs1.size());
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknownRefs1.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Refs 1[" << i1 << "]:  " << unknownRefs1[i1] << endl;
		array_output_count++;
	};
	out << "  Num Dests:  " << numDests << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < transformDests.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Transform Dests[" << i1 << "]:  " << transformDests[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Byte:  " << unknownByte << endl;
	out << "  Unknown Int:  " << unknownInt << endl;
	out << "  Prop Description:  " << propDescription << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPhysXProp::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObjectNET::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < unknownRefs1.size(); i1++) {
		unknownRefs1[i1] = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	};
	for (unsigned int i1 = 0; i1 < transformDests.size(); i1++) {
		transformDests[i1] = FixLink<NiPhysXTransformDest>( objects, link_stack, missing_link_stack, info );
	};
	propDescription = FixLink<NiPhysXPropDesc>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPhysXProp::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObjectNET::GetRefs();
	for (unsigned int i1 = 0; i1 < unknownRefs1.size(); i1++) {
		if ( unknownRefs1[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(unknownRefs1[i1]));
	};
	for (unsigned int i1 = 0; i1 < transformDests.size(); i1++) {
		if ( transformDests[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(transformDests[i1]));
	};
	if ( propDescription != NULL )
		refs.push_back(StaticCast<NiObject>(propDescription));
	return refs;
}

std::list<NiObject *> NiPhysXProp::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObjectNET::GetPtrs();
	for (unsigned int i1 = 0; i1 < unknownRefs1.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < transformDests.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
