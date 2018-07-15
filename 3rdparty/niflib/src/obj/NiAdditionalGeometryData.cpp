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
#include "../../include/obj/NiAdditionalGeometryData.h"
#include "../../include/gen/AdditionalDataInfo.h"
#include "../../include/gen/AdditionalDataBlock.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiAdditionalGeometryData::TYPE("NiAdditionalGeometryData", &AbstractAdditionalGeometryData::TYPE );

NiAdditionalGeometryData::NiAdditionalGeometryData() : numVertices((unsigned short)0), numBlockInfos((unsigned int)0), numBlocks((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiAdditionalGeometryData::~NiAdditionalGeometryData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiAdditionalGeometryData::GetType() const {
	return TYPE;
}

NiObject * NiAdditionalGeometryData::Create() {
	return new NiAdditionalGeometryData;
}

void NiAdditionalGeometryData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
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
			NifStream( blocks[i1].blockSize, in, info );
			NifStream( blocks[i1].numBlocks, in, info );
			blocks[i1].blockOffsets.resize(blocks[i1].numBlocks);
			for (unsigned int i3 = 0; i3 < blocks[i1].blockOffsets.size(); i3++) {
				NifStream( blocks[i1].blockOffsets[i3], in, info );
			};
			NifStream( blocks[i1].numData, in, info );
			blocks[i1].dataSizes.resize(blocks[i1].numData);
			for (unsigned int i3 = 0; i3 < blocks[i1].dataSizes.size(); i3++) {
				NifStream( blocks[i1].dataSizes[i3], in, info );
			};
			blocks[i1].data.resize(blocks[i1].numData);
			for (unsigned int i3 = 0; i3 < blocks[i1].data.size(); i3++) {
				blocks[i1].data[i3].resize(blocks[i1].blockSize);
				for (unsigned int i4 = 0; i4 < blocks[i1].data[i3].size(); i4++) {
					NifStream( blocks[i1].data[i3][i4], in, info );
				};
			};
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiAdditionalGeometryData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
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
		blocks[i1].numData = (int)(blocks[i1].dataSizes.size());
		blocks[i1].numBlocks = (int)(blocks[i1].blockOffsets.size());
		blocks[i1].blockSize = (int)((blocks[i1].data.size() > 0) ? blocks[i1].data[0].size() : 0);
		NifStream( blocks[i1].hasData, out, info );
		if ( blocks[i1].hasData ) {
			NifStream( blocks[i1].blockSize, out, info );
			NifStream( blocks[i1].numBlocks, out, info );
			for (unsigned int i3 = 0; i3 < blocks[i1].blockOffsets.size(); i3++) {
				NifStream( blocks[i1].blockOffsets[i3], out, info );
			};
			NifStream( blocks[i1].numData, out, info );
			for (unsigned int i3 = 0; i3 < blocks[i1].dataSizes.size(); i3++) {
				NifStream( blocks[i1].dataSizes[i3], out, info );
			};
			for (unsigned int i3 = 0; i3 < blocks[i1].data.size(); i3++) {
				for (unsigned int i4 = 0; i4 < blocks[i1].data[i3].size(); i4++) {
					NifStream( blocks[i1].data[i3][i4], out, info );
				};
			};
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiAdditionalGeometryData::asString( bool verbose ) const {
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
		blocks[i1].numData = (int)(blocks[i1].dataSizes.size());
		blocks[i1].numBlocks = (int)(blocks[i1].blockOffsets.size());
		blocks[i1].blockSize = (int)((blocks[i1].data.size() > 0) ? blocks[i1].data[0].size() : 0);
		out << "    Has Data:  " << blocks[i1].hasData << endl;
		if ( blocks[i1].hasData ) {
			out << "      Block Size:  " << blocks[i1].blockSize << endl;
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
			out << "      Num Data:  " << blocks[i1].numData << endl;
			array_output_count = 0;
			for (unsigned int i3 = 0; i3 < blocks[i1].dataSizes.size(); i3++) {
				if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
					out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
					break;
				};
				if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
					break;
				};
				out << "        Data Sizes[" << i3 << "]:  " << blocks[i1].dataSizes[i3] << endl;
				array_output_count++;
			};
			array_output_count = 0;
			for (unsigned int i3 = 0; i3 < blocks[i1].data.size(); i3++) {
				if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
					out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
					break;
				};
				for (unsigned int i4 = 0; i4 < blocks[i1].data[i3].size(); i4++) {
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						break;
					};
					out << "          Data[" << i4 << "]:  " << blocks[i1].data[i3][i4] << endl;
					array_output_count++;
				};
			};
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiAdditionalGeometryData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	AbstractAdditionalGeometryData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiAdditionalGeometryData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = AbstractAdditionalGeometryData::GetRefs();
	return refs;
}

std::list<NiObject *> NiAdditionalGeometryData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = AbstractAdditionalGeometryData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
