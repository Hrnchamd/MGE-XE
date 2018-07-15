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
#include "../../include/obj/bhkWorldObject.h"
#include "../../include/obj/bhkShape.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkWorldObject::TYPE("bhkWorldObject", &bhkSerializable::TYPE );

bhkWorldObject::bhkWorldObject() : shape(NULL), layer((OblivionLayer)OL_STATIC), skyrimLayer((SkyrimLayer)SKYL_STATIC), colFilter((byte)0), flagsAndPartNumber((byte) 0), unknownShort((unsigned short)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkWorldObject::~bhkWorldObject() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkWorldObject::GetType() const {
	return TYPE;
}

NiObject * bhkWorldObject::Create() {
	return new bhkWorldObject;
}

void bhkWorldObject::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	bhkSerializable::Read( in, link_stack, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	if ( info.version < VER_20_2_0_7) {
	NifStream( layer, in, info );
	NifStream( colFilter, in, info );
	} else {
		NifStream( skyrimLayer, in, info );
		NifStream( flagsAndPartNumber, in, info );
	}
	NifStream( unknownShort, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkWorldObject::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkSerializable::Write( out, link_map, missing_link_stack, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*shape), out );
	} else {
		if ( shape != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(shape) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( shape );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_20_2_0_7) {
	NifStream( layer, out, info );
	NifStream( colFilter, out, info );
	} else {
		NifStream( skyrimLayer, out, info );
		NifStream( flagsAndPartNumber, out, info );
	}
	NifStream( unknownShort, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkWorldObject::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << bhkSerializable::asString();
	out << "  Shape:  " << shape << endl;
	out << "  Layer:  " << layer << endl;
	out << "  Col Filter:  " << colFilter << endl;
	out << "  SkyrimLayer:  " << skyrimLayer << endl;
	out << "  Flags and PartNumber:  " << flagsAndPartNumber << endl;
	out << "  Unknown Short:  " << unknownShort << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkWorldObject::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkSerializable::FixLinks( objects, link_stack, missing_link_stack, info );
	shape = FixLink<bhkShape>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkWorldObject::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkSerializable::GetRefs();
	if ( shape != NULL )
		refs.push_back(StaticCast<NiObject>(shape));
	return refs;
}

std::list<NiObject *> bhkWorldObject::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkSerializable::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Ref<bhkShape > bhkWorldObject::GetShape() const {
	return shape;
}

void bhkWorldObject::SetShape( bhkShape * value ) {
	shape = value;
}

OblivionLayer bhkWorldObject::GetLayer() const {
	return layer;
}

void bhkWorldObject::SetLayer( OblivionLayer value ) {
	layer = value;
}

SkyrimLayer bhkWorldObject::GetSkyrimLayer() const {
	return skyrimLayer;
}

void bhkWorldObject::SetSkyrimLayer( SkyrimLayer value ) {
	skyrimLayer = value;
}

//--END CUSTOM CODE--//
