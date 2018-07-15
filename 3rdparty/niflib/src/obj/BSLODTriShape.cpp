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
#include "../../include/obj/BSLODTriShape.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSLODTriShape::TYPE("BSLODTriShape", &NiTriBasedGeom::TYPE );

BSLODTriShape::BSLODTriShape() : level0Size((unsigned int)0), level1Size((unsigned int)0), level2Size((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSLODTriShape::~BSLODTriShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSLODTriShape::GetType() const {
	return TYPE;
}

unsigned int BSLODTriShape::GetLODLevelSize(const unsigned int level) const {
	switch (level)
	{
		case 0:		return level0Size;
		case 1:		return level1Size;
		case 2:		return level2Size;
	}

	return 0;
}

void BSLODTriShape::SetLODLevelSize(const unsigned int level, unsigned int size) {
	switch (level)
	{
		case 0:		{ level0Size = size; break; }
		case 1:		{ level1Size = size; break; }
		case 2:		{ level2Size = size; break; }
	}
}			

NiObject * BSLODTriShape::Create() {
	return new BSLODTriShape;
}

void BSLODTriShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiTriBasedGeom::Read( in, link_stack, info );
	NifStream( level0Size, in, info );
	NifStream( level1Size, in, info );
	NifStream( level2Size, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSLODTriShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiTriBasedGeom::Write( out, link_map, missing_link_stack, info );
	NifStream( level0Size, out, info );
	NifStream( level1Size, out, info );
	NifStream( level2Size, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSLODTriShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiTriBasedGeom::asString();
	out << "  Level 0 Size:  " << level0Size << endl;
	out << "  Level 1 Size:  " << level1Size << endl;
	out << "  Level 2 Size:  " << level2Size << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSLODTriShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiTriBasedGeom::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSLODTriShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiTriBasedGeom::GetRefs();
	return refs;
}

std::list<NiObject *> BSLODTriShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiTriBasedGeom::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
