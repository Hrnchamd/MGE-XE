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
#include "../../include/obj/NiPSGravityForce.h"
#include "../../include/obj/NiObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSGravityForce::TYPE("NiPSGravityForce", &NiObject::TYPE );

NiPSGravityForce::NiPSGravityForce() : unknown1((byte)0), unknown2((byte)0), unknown3((byte)0), unknown4((byte)0), unknown5((byte)0), unknown6((byte)0), unknown7((byte)0), unknown8((byte)0), unknown9((byte)0), unknown10((byte)0), unknown11((byte)0), unknown12((byte)0), unknown13((byte)0), unknown14((byte)0), unknown15((byte)0), unknown16((byte)0), unknown17((byte)0), unknown18(0.0f), unknown19((byte)0), unknown20((byte)0), unknown21((byte)0), unknown22((byte)0), unknown23((byte)0), unknown24((byte)0), unknown25((byte)0), unknown26((byte)0), unknown27((byte)0), unknown28((byte)0), unknown29((byte)0), unknown30((byte)0), unknown31((byte)0), unknown32((byte)0), unknown33((byte)0), unknown34((byte)0), unknown35(0.0f), unknown36(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSGravityForce::~NiPSGravityForce() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSGravityForce::GetType() const {
	return TYPE;
}

NiObject * NiPSGravityForce::Create() {
	return new NiPSGravityForce;
}

void NiPSGravityForce::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( unknown1, in, info );
	NifStream( unknown2, in, info );
	NifStream( unknown3, in, info );
	NifStream( unknown4, in, info );
	NifStream( unknown5, in, info );
	NifStream( unknown6, in, info );
	NifStream( unknown7, in, info );
	NifStream( unknown8, in, info );
	NifStream( unknown9, in, info );
	NifStream( unknown10, in, info );
	NifStream( unknown11, in, info );
	NifStream( unknown12, in, info );
	NifStream( unknown13, in, info );
	NifStream( unknown14, in, info );
	NifStream( unknown15, in, info );
	NifStream( unknown16, in, info );
	NifStream( unknown17, in, info );
	NifStream( unknown18, in, info );
	NifStream( unknown19, in, info );
	NifStream( unknown20, in, info );
	NifStream( unknown21, in, info );
	NifStream( unknown22, in, info );
	NifStream( unknown23, in, info );
	NifStream( unknown24, in, info );
	NifStream( unknown25, in, info );
	NifStream( unknown26, in, info );
	NifStream( unknown27, in, info );
	NifStream( unknown28, in, info );
	NifStream( unknown29, in, info );
	NifStream( unknown30, in, info );
	NifStream( unknown31, in, info );
	NifStream( unknown32, in, info );
	NifStream( unknown33, in, info );
	NifStream( unknown34, in, info );
	NifStream( unknown35, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSGravityForce::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	NifStream( unknown1, out, info );
	NifStream( unknown2, out, info );
	NifStream( unknown3, out, info );
	NifStream( unknown4, out, info );
	NifStream( unknown5, out, info );
	NifStream( unknown6, out, info );
	NifStream( unknown7, out, info );
	NifStream( unknown8, out, info );
	NifStream( unknown9, out, info );
	NifStream( unknown10, out, info );
	NifStream( unknown11, out, info );
	NifStream( unknown12, out, info );
	NifStream( unknown13, out, info );
	NifStream( unknown14, out, info );
	NifStream( unknown15, out, info );
	NifStream( unknown16, out, info );
	NifStream( unknown17, out, info );
	NifStream( unknown18, out, info );
	NifStream( unknown19, out, info );
	NifStream( unknown20, out, info );
	NifStream( unknown21, out, info );
	NifStream( unknown22, out, info );
	NifStream( unknown23, out, info );
	NifStream( unknown24, out, info );
	NifStream( unknown25, out, info );
	NifStream( unknown26, out, info );
	NifStream( unknown27, out, info );
	NifStream( unknown28, out, info );
	NifStream( unknown29, out, info );
	NifStream( unknown30, out, info );
	NifStream( unknown31, out, info );
	NifStream( unknown32, out, info );
	NifStream( unknown33, out, info );
	NifStream( unknown34, out, info );
	NifStream( unknown35, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*unknown36), out );
	} else {
		if ( unknown36 != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(unknown36) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( unknown36 );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSGravityForce::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiObject::asString();
	out << "  Unknown 1:  " << unknown1 << endl;
	out << "  Unknown 2:  " << unknown2 << endl;
	out << "  Unknown 3:  " << unknown3 << endl;
	out << "  Unknown 4:  " << unknown4 << endl;
	out << "  Unknown 5:  " << unknown5 << endl;
	out << "  Unknown 6:  " << unknown6 << endl;
	out << "  Unknown 7:  " << unknown7 << endl;
	out << "  Unknown 8:  " << unknown8 << endl;
	out << "  Unknown 9:  " << unknown9 << endl;
	out << "  Unknown 10:  " << unknown10 << endl;
	out << "  Unknown 11:  " << unknown11 << endl;
	out << "  Unknown 12:  " << unknown12 << endl;
	out << "  Unknown 13:  " << unknown13 << endl;
	out << "  Unknown 14:  " << unknown14 << endl;
	out << "  Unknown 15:  " << unknown15 << endl;
	out << "  Unknown 16:  " << unknown16 << endl;
	out << "  Unknown 17:  " << unknown17 << endl;
	out << "  Unknown 18:  " << unknown18 << endl;
	out << "  Unknown 19:  " << unknown19 << endl;
	out << "  Unknown 20:  " << unknown20 << endl;
	out << "  Unknown 21:  " << unknown21 << endl;
	out << "  Unknown 22:  " << unknown22 << endl;
	out << "  Unknown 23:  " << unknown23 << endl;
	out << "  Unknown 24:  " << unknown24 << endl;
	out << "  Unknown 25:  " << unknown25 << endl;
	out << "  Unknown 26:  " << unknown26 << endl;
	out << "  Unknown 27:  " << unknown27 << endl;
	out << "  Unknown 28:  " << unknown28 << endl;
	out << "  Unknown 29:  " << unknown29 << endl;
	out << "  Unknown 30:  " << unknown30 << endl;
	out << "  Unknown 31:  " << unknown31 << endl;
	out << "  Unknown 32:  " << unknown32 << endl;
	out << "  Unknown 33:  " << unknown33 << endl;
	out << "  Unknown 34:  " << unknown34 << endl;
	out << "  Unknown 35:  " << unknown35 << endl;
	out << "  Unknown 36:  " << unknown36 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSGravityForce::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	unknown36 = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSGravityForce::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( unknown36 != NULL )
		refs.push_back(StaticCast<NiObject>(unknown36));
	return refs;
}

std::list<NiObject *> NiPSGravityForce::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
