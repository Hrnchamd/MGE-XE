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
#include "../../include/obj/NiPhysXShapeDesc.h"
#include "../../include/obj/NiPhysXMeshDesc.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPhysXShapeDesc::TYPE("NiPhysXShapeDesc", &NiObject::TYPE );

NiPhysXShapeDesc::NiPhysXShapeDesc() : unknownInt1((int)0), unknownShort1((short)0), unknownInt2((int)0), unknownShort2((short)0), unknownFloat1(0.0f), unknownFloat2(0.0f), unknownFloat3(0.0f), unknownInt3((int)0), unknownInt4((int)0), unknownInt5((int)0), unknownInt7((int)0), unknownInt8((int)0), meshDescription(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPhysXShapeDesc::~NiPhysXShapeDesc() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPhysXShapeDesc::GetType() const {
	return TYPE;
}

NiObject * NiPhysXShapeDesc::Create() {
	return new NiPhysXShapeDesc;
}

void NiPhysXShapeDesc::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( unknownInt1, in, info );
	NifStream( unknownQuat1, in, info );
	NifStream( unknownQuat2, in, info );
	NifStream( unknownQuat3, in, info );
	NifStream( unknownShort1, in, info );
	NifStream( unknownInt2, in, info );
	NifStream( unknownShort2, in, info );
	NifStream( unknownFloat1, in, info );
	NifStream( unknownFloat2, in, info );
	NifStream( unknownFloat3, in, info );
	NifStream( unknownInt3, in, info );
	NifStream( unknownInt4, in, info );
	NifStream( unknownInt5, in, info );
	NifStream( unknownInt7, in, info );
	NifStream( unknownInt8, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPhysXShapeDesc::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	NifStream( unknownInt1, out, info );
	NifStream( unknownQuat1, out, info );
	NifStream( unknownQuat2, out, info );
	NifStream( unknownQuat3, out, info );
	NifStream( unknownShort1, out, info );
	NifStream( unknownInt2, out, info );
	NifStream( unknownShort2, out, info );
	NifStream( unknownFloat1, out, info );
	NifStream( unknownFloat2, out, info );
	NifStream( unknownFloat3, out, info );
	NifStream( unknownInt3, out, info );
	NifStream( unknownInt4, out, info );
	NifStream( unknownInt5, out, info );
	NifStream( unknownInt7, out, info );
	NifStream( unknownInt8, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*meshDescription), out );
	} else {
		if ( meshDescription != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(meshDescription) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( meshDescription );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPhysXShapeDesc::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiObject::asString();
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Unknown Quat 1:  " << unknownQuat1 << endl;
	out << "  Unknown Quat 2:  " << unknownQuat2 << endl;
	out << "  Unknown Quat 3:  " << unknownQuat3 << endl;
	out << "  Unknown Short 1:  " << unknownShort1 << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Unknown Short 2:  " << unknownShort2 << endl;
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Unknown Float 2:  " << unknownFloat2 << endl;
	out << "  Unknown Float 3:  " << unknownFloat3 << endl;
	out << "  Unknown Int 3:  " << unknownInt3 << endl;
	out << "  Unknown Int 4:  " << unknownInt4 << endl;
	out << "  Unknown Int 5:  " << unknownInt5 << endl;
	out << "  Unknown Int 7:  " << unknownInt7 << endl;
	out << "  Unknown Int 8:  " << unknownInt8 << endl;
	out << "  Mesh Description:  " << meshDescription << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPhysXShapeDesc::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	meshDescription = FixLink<NiPhysXMeshDesc>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPhysXShapeDesc::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( meshDescription != NULL )
		refs.push_back(StaticCast<NiObject>(meshDescription));
	return refs;
}

std::list<NiObject *> NiPhysXShapeDesc::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
