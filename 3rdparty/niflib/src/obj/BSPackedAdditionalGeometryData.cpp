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
#include "../../include/obj/BSPackedAdditionalGeometryData.h"
#include "../../include/gen/AdditionalDataInfo.h"
#include "../../include/gen/BSPackedAdditionalDataBlock.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSPackedAdditionalGeometryData::TYPE("BSPackedAdditionalGeometryData", &AbstractAdditionalGeometryData::TYPE );

BSPackedAdditionalGeometryData::BSPackedAdditionalGeometryData() : numVertices((unsigned short)0), numBlockInfos((unsigned int)0), numBlocks((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSPackedAdditionalGeometryData::~BSPackedAdditionalGeometryData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSPackedAdditionalGeometryData::GetType() const {
	return TYPE;
}

NiObject * BSPackedAdditionalGeometryData::Create() {
	return new BSPackedAdditionalGeometryData;
}

void BSPackedAdditionalGeometryData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	AbstractAdditionalGeometryData::Read( in, link_stack, info );
	NifStream( numVertices, in, info );
	NifStream( numBlockInfos, in, info );
	blockInfos.resize(numBlockInfos);
	for (unsigned int i1 = 0; i1 < blockInfos.size(); i1++) {
		NifStream( blockInfos[i1].dataType, in, info );
		NifStream( blockInfos[i1].numChannelBytesPerElement, in, info );
		NifStream( blockInfos[i1].numChannelBytes, in, info );
		NifStream( blockInfos[i1].numTotalBytesPerElement, in, info );
		NifStream( blockInfos[i1].blockIndex, in, info );
		NifStream( blockInfos[i1].channelOffset, in, info );
		NifStream( blockInfos[i1].unknownByte1, in, info );
	};
	NifStream( numBlocks, in, info );
	blocks.resize(numBlocks);
	for (unsigned int i1 = 0; i1 < blocks.size(); i1++) {
		NifStream( blocks[i1].hasData, in, info );
		if ( blocks[i1].hasData ) {
			NifStream( blocks[i1].numTotalBytes, in, info );
			NifStream( blocks[i1].numBlocks, in, info );
			blocks[i1].blockOffsets.resize(blocks[i1].numBlocks);
			for (unsigned int i3 = 0; i3 < blocks[i1].blockOffsets.size(); i3++) {
				NifStream( blocks[i1].blockOffsets[i3], in, info );
			};
			NifStream( blocks[i1].numAtoms, in, info );
			blocks[i1].atomSizes.resize(blocks[i1].numAtoms);
			for (unsigned int i3 = 0; i3 < blocks[i1].atomSizes.size(); i3++) {
				NifStream( blocks[i1].atomSizes[i3], in, info );
			};
			blocks[i1].data.resize(blocks[i1].numTotalBytes);
			for (unsigned int i3 = 0; i3 < blocks[i1].data.size(); i3++) {
				NifStream( blocks[i1].data[i3], in, info );
			};
		};
		NifStream( blocks[i1].unknownInt1, in, info );
		NifStream( blocks[i1].numTotalBytesPerElement, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSPackedAdditionalGeometryData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	AbstractAdditionalGeometryData::Write( out, link_map, missing_link_stack, info );
	numBlocks = (int)(blocks.size());
	numBlockInfos = (unsigned int)(blockInfos.size());
	NifStream( numVertices, out, info );
	NifStream( numBlockInfos, out, info );
	for (unsigned int i1 = 0; i1 < blockInfos.size(); i1++) {
		NifStream( blockInfos[i1].dataType, out, info );
		NifStream( blockInfos[i1].numChannelBytesPerElement, out, info );
		NifStream( blockInfos[i1].numChannelBytes, out, info );
		NifStream( blockInfos[i1].numTotalBytesPerElement, out, info );
		NifStream( blockInfos[i1].blockIndex, out, info );
		NifStream( blockInfos[i1].channelOffset, out, info );
		NifStream( blockInfos[i1].unknownByte1, out, info );
	};
	NifStream( numBlocks, out, info );
	for (unsigned int i1 = 0; i1 < blocks.size(); i1++) {
		blocks[i1].numAtoms = (int)(blocks[i1].atomSizes.size());
		blocks[i1].numBlocks = (int)(blocks[i1].blockOffsets.size());
		blocks[i1].numTotalBytes = (int)(blocks[i1].data.size());
		NifStream( blocks[i1].hasData, out, info );
		if ( blocks[i1].hasData ) {
			NifStream( blocks[i1].numTotalBytes, out, info );
			NifStream( blocks[i1].numBlocks, out, info );
			for (unsigned int i3 = 0; i3 < blocks[i1].blockOffsets.size(); i3++) {
				NifStream( blocks[i1].blockOffsets[i3], out, info );
			};
			NifStream( blocks[i1].numAtoms, out, info );
			for (unsigned int i3 = 0; i3 < blocks[i1].atomSizes.size(); i3++) {
				NifStream( blocks[i1].atomSizes[i3], out, info );
			};
			for (unsigned int i3 = 0; i3 < blocks[i1].data.size(); i3++) {
				NifStream( blocks[i1].data[i3], out, info );
			};
		};
		NifStream( blocks[i1].unknownInt1, out, info );
		NifStream( blocks[i1].numTotalBytesPerElement, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSPackedAdditionalGeometryData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << AbstractAdditionalGeometryData::asString();
	numBlocks = (int)(blocks.size());
	numBlockInfos = (unsigned int)(blockInfos.size());
	out << "  Num Vertices:  " << numVertices << endl;
	out << "  Num Block Infos:  " << numBlockInfos << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < blockInfos.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Data Type:  " << blockInfos[i1].dataType << endl;
		out << "    Num Channel Bytes Per Element:  " << blockInfos[i1].numChannelBytesPerElement << endl;
		out << "    Num Channel Bytes:  " << blockInfos[i1].numChannelBytes << endl;
		out << "    Num Total Bytes Per Element:  " << blockInfos[i1].numTotalBytesPerElement << endl;
		out << "    Block Index:  " << blockInfos[i1].blockIndex << endl;
		out << "    Channel Offset:  " << blockInfos[i1].channelOffset << endl;
		out << "    Unknown Byte 1:  " << blockInfos[i1].unknownByte1 << endl;
	};
	out << "  Num Blocks:  " << numBlocks << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < blocks.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		blocks[i1].numAtoms = (int)(blocks[i1].atomSizes.size());
		blocks[i1].numBlocks = (int)(blocks[i1].blockOffsets.size());
		blocks[i1].numTotalBytes = (int)(blocks[i1].data.size());
		out << "    Has Data:  " << blocks[i1].hasData << endl;
		if ( blocks[i1].hasData ) {
			out << "      Num Total Bytes:  " << blocks[i1].numTotalBytes << endl;
			out << "      Num Blocks:  " << blocks[i1].numBlocks << endl;
			array_output_count = 0;
			for (unsigned int i3 = 0; i3 < blocks[i1].blockOffsets.size(); i3++) {
				if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
					out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
					break;
				};
				if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
					break;
				};
				out << "        Block Offsets[" << i3 << "]:  " << blocks[i1].blockOffsets[i3] << endl;
				array_output_count++;
			};
			out << "      Num Atoms:  " << blocks[i1].numAtoms << endl;
			array_output_count = 0;
			for (unsigned int i3 = 0; i3 < blocks[i1].atomSizes.size(); i3++) {
				if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
					out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
					break;
				};
				if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
					break;
				};
				out << "        Atom Sizes[" << i3 << "]:  " << blocks[i1].atomSizes[i3] << endl;
				array_output_count++;
			};
			array_output_count = 0;
			for (unsigned int i3 = 0; i3 < blocks[i1].data.size(); i3++) {
				if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
					out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
					break;
				};
				if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
					break;
				};
				out << "        Data[" << i3 << "]:  " << blocks[i1].data[i3] << endl;
				array_output_count++;
			};
		};
		out << "    Unknown Int 1:  " << blocks[i1].unknownInt1 << endl;
		out << "    Num Total Bytes Per Element:  " << blocks[i1].numTotalBytesPerElement << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSPackedAdditionalGeometryData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	AbstractAdditionalGeometryData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSPackedAdditionalGeometryData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = AbstractAdditionalGeometryData::GetRefs();
	return refs;
}

std::list<NiObject *> BSPackedAdditionalGeometryData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = AbstractAdditionalGeometryData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
