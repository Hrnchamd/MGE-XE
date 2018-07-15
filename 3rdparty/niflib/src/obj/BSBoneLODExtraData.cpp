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
#include "../../include/obj/BSBoneLODExtraData.h"
#include "../../include/gen/BoneLOD.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSBoneLODExtraData::TYPE("BSBoneLODExtraData", &NiExtraData::TYPE );

BSBoneLODExtraData::BSBoneLODExtraData() : bonelodCount((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSBoneLODExtraData::~BSBoneLODExtraData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSBoneLODExtraData::GetType() const {
	return TYPE;
}

NiObject * BSBoneLODExtraData::Create() {
	return new BSBoneLODExtraData;
}

void BSBoneLODExtraData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::Read( in, link_stack, info );
	NifStream( bonelodCount, in, info );
	bonelodInfo.resize(bonelodCount);
	for (unsigned int i1 = 0; i1 < bonelodInfo.size(); i1++) {
		NifStream( bonelodInfo[i1].distance, in, info );
		NifStream( bonelodInfo[i1].boneName, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSBoneLODExtraData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::Write( out, link_map, missing_link_stack, info );
	bonelodCount = (unsigned int)(bonelodInfo.size());
	NifStream( bonelodCount, out, info );
	for (unsigned int i1 = 0; i1 < bonelodInfo.size(); i1++) {
		NifStream( bonelodInfo[i1].distance, out, info );
		NifStream( bonelodInfo[i1].boneName, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSBoneLODExtraData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiExtraData::asString();
	bonelodCount = (unsigned int)(bonelodInfo.size());
	out << "  BoneLOD Count:  " << bonelodCount << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < bonelodInfo.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Distance:  " << bonelodInfo[i1].distance << endl;
		out << "    Bone Name:  " << bonelodInfo[i1].boneName << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSBoneLODExtraData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSBoneLODExtraData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiExtraData::GetRefs();
	return refs;
}

std::list<NiObject *> BSBoneLODExtraData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiExtraData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
