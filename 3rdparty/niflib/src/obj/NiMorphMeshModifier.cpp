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
#include "../../include/obj/NiMorphMeshModifier.h"
#include "../../include/gen/ElementReference.h"
#include "../../include/gen/SemanticData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiMorphMeshModifier::TYPE("NiMorphMeshModifier", &NiMeshModifier::TYPE );

NiMorphMeshModifier::NiMorphMeshModifier() : flags((byte)0), numTargets((unsigned short)0), numElements((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiMorphMeshModifier::~NiMorphMeshModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiMorphMeshModifier::GetType() const {
	return TYPE;
}

NiObject * NiMorphMeshModifier::Create() {
	return new NiMorphMeshModifier;
}

void NiMorphMeshModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiMeshModifier::Read( in, link_stack, info );
	NifStream( flags, in, info );
	NifStream( numTargets, in, info );
	NifStream( numElements, in, info );
	elements.resize(numElements);
	for (unsigned int i1 = 0; i1 < elements.size(); i1++) {
		NifStream( elements[i1].semantic.name, in, info );
		NifStream( elements[i1].semantic.index, in, info );
		NifStream( elements[i1].normalizeFlag, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiMorphMeshModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiMeshModifier::Write( out, link_map, missing_link_stack, info );
	numElements = (unsigned int)(elements.size());
	NifStream( flags, out, info );
	NifStream( numTargets, out, info );
	NifStream( numElements, out, info );
	for (unsigned int i1 = 0; i1 < elements.size(); i1++) {
		NifStream( elements[i1].semantic.name, out, info );
		NifStream( elements[i1].semantic.index, out, info );
		NifStream( elements[i1].normalizeFlag, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiMorphMeshModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiMeshModifier::asString();
	numElements = (unsigned int)(elements.size());
	out << "  Flags:  " << flags << endl;
	out << "  Num Targets:  " << numTargets << endl;
	out << "  Num Elements:  " << numElements << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < elements.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Name:  " << elements[i1].semantic.name << endl;
		out << "    Index:  " << elements[i1].semantic.index << endl;
		out << "    Normalize Flag:  " << elements[i1].normalizeFlag << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiMorphMeshModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiMeshModifier::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiMorphMeshModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiMeshModifier::GetRefs();
	return refs;
}

std::list<NiObject *> NiMorphMeshModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiMeshModifier::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
