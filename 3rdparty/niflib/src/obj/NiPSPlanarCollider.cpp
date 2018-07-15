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
#include "../../include/obj/NiPSPlanarCollider.h"
#include "../../include/obj/NiNode.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSPlanarCollider::TYPE("NiPSPlanarCollider", &NiObject::TYPE );

NiPSPlanarCollider::NiPSPlanarCollider() : unknownInt1((int)0), unknownInt2((int)0), unknownShort3((short)0), unknownByte4((byte)0), unknownLink6(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSPlanarCollider::~NiPSPlanarCollider() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSPlanarCollider::GetType() const {
	return TYPE;
}

NiObject * NiPSPlanarCollider::Create() {
	return new NiPSPlanarCollider;
}

void NiPSPlanarCollider::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( name, in, info );
	NifStream( unknownInt1, in, info );
	NifStream( unknownInt2, in, info );
	NifStream( unknownShort3, in, info );
	NifStream( unknownByte4, in, info );
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( unknownFloats5[i1], in, info );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSPlanarCollider::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	NifStream( name, out, info );
	NifStream( unknownInt1, out, info );
	NifStream( unknownInt2, out, info );
	NifStream( unknownShort3, out, info );
	NifStream( unknownByte4, out, info );
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( unknownFloats5[i1], out, info );
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*unknownLink6), out );
	} else {
		if ( unknownLink6 != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(unknownLink6) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( unknownLink6 );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSPlanarCollider::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	out << "  Name:  " << name << endl;
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Unknown Short 3:  " << unknownShort3 << endl;
	out << "  Unknown Byte 4:  " << unknownByte4 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Floats 5[" << i1 << "]:  " << unknownFloats5[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Link 6:  " << unknownLink6 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSPlanarCollider::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	unknownLink6 = FixLink<NiNode>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSPlanarCollider::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( unknownLink6 != NULL )
		refs.push_back(StaticCast<NiObject>(unknownLink6));
	return refs;
}

std::list<NiObject *> NiPSPlanarCollider::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
