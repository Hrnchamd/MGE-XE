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
#include "../../include/obj/BSDecalPlacementVectorExtraData.h"
#include "../../include/gen/DecalVectorArray.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSDecalPlacementVectorExtraData::TYPE("BSDecalPlacementVectorExtraData", &NiExtraData::TYPE );

BSDecalPlacementVectorExtraData::BSDecalPlacementVectorExtraData() : unknownFloat1(0.0f), numVectorBlocks((short)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSDecalPlacementVectorExtraData::~BSDecalPlacementVectorExtraData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSDecalPlacementVectorExtraData::GetType() const {
	return TYPE;
}

NiObject * BSDecalPlacementVectorExtraData::Create() {
	return new BSDecalPlacementVectorExtraData;
}

void BSDecalPlacementVectorExtraData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::Read( in, link_stack, info );
	NifStream( unknownFloat1, in, info );
	NifStream( numVectorBlocks, in, info );
	vectorBlocks.resize(numVectorBlocks);
	for (unsigned int i1 = 0; i1 < vectorBlocks.size(); i1++) {
		NifStream( vectorBlocks[i1].numVectors, in, info );
		vectorBlocks[i1].points.resize(vectorBlocks[i1].numVectors);
		for (unsigned int i2 = 0; i2 < vectorBlocks[i1].points.size(); i2++) {
			NifStream( vectorBlocks[i1].points[i2], in, info );
		};
		vectorBlocks[i1].normals.resize(vectorBlocks[i1].numVectors);
		for (unsigned int i2 = 0; i2 < vectorBlocks[i1].normals.size(); i2++) {
			NifStream( vectorBlocks[i1].normals[i2], in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSDecalPlacementVectorExtraData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::Write( out, link_map, missing_link_stack, info );
	numVectorBlocks = (short)(vectorBlocks.size());
	NifStream( unknownFloat1, out, info );
	NifStream( numVectorBlocks, out, info );
	for (unsigned int i1 = 0; i1 < vectorBlocks.size(); i1++) {
		vectorBlocks[i1].numVectors = (short)(vectorBlocks[i1].points.size());
		NifStream( vectorBlocks[i1].numVectors, out, info );
		for (unsigned int i2 = 0; i2 < vectorBlocks[i1].points.size(); i2++) {
			NifStream( vectorBlocks[i1].points[i2], out, info );
		};
		for (unsigned int i2 = 0; i2 < vectorBlocks[i1].normals.size(); i2++) {
			NifStream( vectorBlocks[i1].normals[i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSDecalPlacementVectorExtraData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiExtraData::asString();
	numVectorBlocks = (short)(vectorBlocks.size());
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	out << "  Num Vector Blocks:  " << numVectorBlocks << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < vectorBlocks.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		vectorBlocks[i1].numVectors = (short)(vectorBlocks[i1].points.size());
		out << "    Num Vectors:  " << vectorBlocks[i1].numVectors << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < vectorBlocks[i1].points.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Points[" << i2 << "]:  " << vectorBlocks[i1].points[i2] << endl;
			array_output_count++;
		};
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < vectorBlocks[i1].normals.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Normals[" << i2 << "]:  " << vectorBlocks[i1].normals[i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSDecalPlacementVectorExtraData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiExtraData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSDecalPlacementVectorExtraData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiExtraData::GetRefs();
	return refs;
}

std::list<NiObject *> BSDecalPlacementVectorExtraData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiExtraData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
