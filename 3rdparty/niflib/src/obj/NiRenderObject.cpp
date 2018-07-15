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
#include "../../include/obj/NiRenderObject.h"
#include "../../include/gen/MaterialData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiRenderObject::TYPE("NiRenderObject", &NiAVObject::TYPE );

NiRenderObject::NiRenderObject() : numMaterials((unsigned int)0), activeMaterial((int)-1), materialNeedsUpdateDefault(false) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiRenderObject::~NiRenderObject() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiRenderObject::GetType() const {
	return TYPE;
}

NiObject * NiRenderObject::Create() {
	return new NiRenderObject;
}

void NiRenderObject::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiAVObject::Read( in, link_stack, info );
	NifStream( numMaterials, in, info );
	materialData.resize(numMaterials);
	for (unsigned int i1 = 0; i1 < materialData.size(); i1++) {
		NifStream( materialData[i1].materialName, in, info );
		NifStream( materialData[i1].materialExtraData, in, info );
	};
	NifStream( activeMaterial, in, info );
	NifStream( materialNeedsUpdateDefault, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiRenderObject::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiAVObject::Write( out, link_map, missing_link_stack, info );
	numMaterials = (unsigned int)(materialData.size());
	NifStream( numMaterials, out, info );
	for (unsigned int i1 = 0; i1 < materialData.size(); i1++) {
		NifStream( materialData[i1].materialName, out, info );
		NifStream( materialData[i1].materialExtraData, out, info );
	};
	NifStream( activeMaterial, out, info );
	NifStream( materialNeedsUpdateDefault, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiRenderObject::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiAVObject::asString();
	numMaterials = (unsigned int)(materialData.size());
	out << "  Num Materials:  " << numMaterials << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < materialData.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Material Name:  " << materialData[i1].materialName << endl;
		out << "    Material Extra Data:  " << materialData[i1].materialExtraData << endl;
	};
	out << "  Active Material:  " << activeMaterial << endl;
	out << "  Material Needs Update Default:  " << materialNeedsUpdateDefault << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiRenderObject::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiAVObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiRenderObject::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiAVObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiRenderObject::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiAVObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
