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
#include "../../include/obj/NiTriBasedGeomData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiTriBasedGeomData::TYPE("NiTriBasedGeomData", &NiGeometryData::TYPE );

NiTriBasedGeomData::NiTriBasedGeomData() : numTriangles((unsigned short)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiTriBasedGeomData::~NiTriBasedGeomData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiTriBasedGeomData::GetType() const {
	return TYPE;
}

NiObject * NiTriBasedGeomData::Create() {
	return new NiTriBasedGeomData;
}

void NiTriBasedGeomData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiGeometryData::Read( in, link_stack, info );
	NifStream( numTriangles, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTriBasedGeomData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiGeometryData::Write( out, link_map, missing_link_stack, info );
	NifStream( numTriangles, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiTriBasedGeomData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiGeometryData::asString();
	out << "  Num Triangles:  " << numTriangles << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTriBasedGeomData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiGeometryData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiTriBasedGeomData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiGeometryData::GetRefs();
	return refs;
}

std::list<NiObject *> NiTriBasedGeomData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiGeometryData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

void NiTriBasedGeomData::SetTriangles( const vector<Triangle> & in ) {
   throw runtime_error("SetTriangles is not implemented for this object.");
}

vector<Triangle> NiTriBasedGeomData::GetTriangles() const {
	return vector<Triangle>();
}

//--END CUSTOM CODE--//
