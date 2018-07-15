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
#include "../../include/obj/NiMeshModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiMeshModifier::TYPE("NiMeshModifier", &NiObject::TYPE );

NiMeshModifier::NiMeshModifier() : numSubmitPoints((unsigned int)0), numCompletePoints((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiMeshModifier::~NiMeshModifier() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiMeshModifier::GetType() const {
	return TYPE;
}

NiObject * NiMeshModifier::Create() {
	return new NiMeshModifier;
}

void NiMeshModifier::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( numSubmitPoints, in, info );
	submitPoints.resize(numSubmitPoints);
	for (unsigned int i1 = 0; i1 < submitPoints.size(); i1++) {
		NifStream( submitPoints[i1], in, info );
	};
	NifStream( numCompletePoints, in, info );
	completePoints.resize(numCompletePoints);
	for (unsigned int i1 = 0; i1 < completePoints.size(); i1++) {
		NifStream( completePoints[i1], in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiMeshModifier::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	numCompletePoints = (unsigned int)(completePoints.size());
	numSubmitPoints = (unsigned int)(submitPoints.size());
	NifStream( numSubmitPoints, out, info );
	for (unsigned int i1 = 0; i1 < submitPoints.size(); i1++) {
		NifStream( submitPoints[i1], out, info );
	};
	NifStream( numCompletePoints, out, info );
	for (unsigned int i1 = 0; i1 < completePoints.size(); i1++) {
		NifStream( completePoints[i1], out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiMeshModifier::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numCompletePoints = (unsigned int)(completePoints.size());
	numSubmitPoints = (unsigned int)(submitPoints.size());
	out << "  Num Submit Points:  " << numSubmitPoints << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < submitPoints.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Submit Points[" << i1 << "]:  " << submitPoints[i1] << endl;
		array_output_count++;
	};
	out << "  Num Complete Points:  " << numCompletePoints << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < completePoints.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Complete Points[" << i1 << "]:  " << completePoints[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiMeshModifier::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiMeshModifier::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiMeshModifier::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
