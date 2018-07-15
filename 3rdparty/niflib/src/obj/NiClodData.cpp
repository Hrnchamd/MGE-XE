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
#include "../../include/obj/NiClodData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiClodData::TYPE("NiClodData", &NiTriBasedGeomData::TYPE );

NiClodData::NiClodData() : unknownShorts((unsigned short)0), unknownCount1((unsigned short)0), unknownCount2((unsigned short)0), unknownCount3((unsigned short)0), unknownFloat(0.0f), unknownShort((unsigned short)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiClodData::~NiClodData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiClodData::GetType() const {
	return TYPE;
}

NiObject * NiClodData::Create() {
	return new NiClodData;
}

void NiClodData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTriBasedGeomData::Read( in, link_stack, info );
	NifStream( unknownShorts, in, info );
	NifStream( unknownCount1, in, info );
	NifStream( unknownCount2, in, info );
	NifStream( unknownCount3, in, info );
	NifStream( unknownFloat, in, info );
	NifStream( unknownShort, in, info );
	unknownClodShorts1.resize(unknownCount1);
	for (unsigned int i1 = 0; i1 < unknownClodShorts1.size(); i1++) {
		for (unsigned int i2 = 0; i2 < 6; i2++) {
			NifStream( unknownClodShorts1[i1][i2], in, info );
		};
	};
	unknownClodShorts2.resize(unknownCount2);
	for (unsigned int i1 = 0; i1 < unknownClodShorts2.size(); i1++) {
		NifStream( unknownClodShorts2[i1], in, info );
	};
	unknownClodShorts3.resize(unknownCount3);
	for (unsigned int i1 = 0; i1 < unknownClodShorts3.size(); i1++) {
		for (unsigned int i2 = 0; i2 < 6; i2++) {
			NifStream( unknownClodShorts3[i1][i2], in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiClodData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTriBasedGeomData::Write( out, link_map, missing_link_stack, info );
	unknownCount3 = (unsigned short)(unknownClodShorts3.size());
	unknownCount2 = (unsigned short)(unknownClodShorts2.size());
	unknownCount1 = (unsigned short)(unknownClodShorts1.size());
	NifStream( unknownShorts, out, info );
	NifStream( unknownCount1, out, info );
	NifStream( unknownCount2, out, info );
	NifStream( unknownCount3, out, info );
	NifStream( unknownFloat, out, info );
	NifStream( unknownShort, out, info );
	for (unsigned int i1 = 0; i1 < unknownClodShorts1.size(); i1++) {
		for (unsigned int i2 = 0; i2 < 6; i2++) {
			NifStream( unknownClodShorts1[i1][i2], out, info );
		};
	};
	for (unsigned int i1 = 0; i1 < unknownClodShorts2.size(); i1++) {
		NifStream( unknownClodShorts2[i1], out, info );
	};
	for (unsigned int i1 = 0; i1 < unknownClodShorts3.size(); i1++) {
		for (unsigned int i2 = 0; i2 < 6; i2++) {
			NifStream( unknownClodShorts3[i1][i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiClodData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiTriBasedGeomData::asString();
	unknownCount3 = (unsigned short)(unknownClodShorts3.size());
	unknownCount2 = (unsigned short)(unknownClodShorts2.size());
	unknownCount1 = (unsigned short)(unknownClodShorts1.size());
	out << "  Unknown Shorts:  " << unknownShorts << endl;
	out << "  Unknown Count 1:  " << unknownCount1 << endl;
	out << "  Unknown Count 2:  " << unknownCount2 << endl;
	out << "  Unknown Count 3:  " << unknownCount3 << endl;
	out << "  Unknown Float:  " << unknownFloat << endl;
	out << "  Unknown Short:  " << unknownShort << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknownClodShorts1.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		for (unsigned int i2 = 0; i2 < 6; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown Clod Shorts 1[" << i2 << "]:  " << unknownClodShorts1[i1][i2] << endl;
			array_output_count++;
		};
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknownClodShorts2.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Clod Shorts 2[" << i1 << "]:  " << unknownClodShorts2[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknownClodShorts3.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		for (unsigned int i2 = 0; i2 < 6; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown Clod Shorts 3[" << i2 << "]:  " << unknownClodShorts3[i1][i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiClodData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTriBasedGeomData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiClodData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiTriBasedGeomData::GetRefs();
	return refs;
}

std::list<NiObject *> NiClodData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiTriBasedGeomData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
