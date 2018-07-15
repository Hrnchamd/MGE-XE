/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/Header.h"
#include "../../include/gen/ExportInfo.h"
#include "../../include/gen/ExportInfo.h"
using namespace Niflib;

//Constructor
Header::Header() : version((unsigned int)0x04000002), endianType((EndianType)ENDIAN_LITTLE), userVersion((unsigned int)0), numBlocks((unsigned int)0), userVersion2((unsigned int)0), unknownInt3((unsigned int)0), numBlockTypes((unsigned short)0), numStrings((unsigned int)0), maxStringLength((unsigned int)0), unknownInt2((unsigned int)0) {};

//Copy Constructor
Header::Header( const Header & src ) {
	*this = src;
};

//Copy Operator
Header & Header::operator=( const Header & src ) {
	this->headerString = src.headerString;
	this->copyright = src.copyright;
	this->version = src.version;
	this->endianType = src.endianType;
	this->userVersion = src.userVersion;
	this->numBlocks = src.numBlocks;
	this->userVersion2 = src.userVersion2;
	this->unknownInt3 = src.unknownInt3;
	this->exportInfo = src.exportInfo;
	this->numBlockTypes = src.numBlockTypes;
	this->blockTypes = src.blockTypes;
	this->blockTypeIndex = src.blockTypeIndex;
	this->blockSize = src.blockSize;
	this->numStrings = src.numStrings;
	this->maxStringLength = src.maxStringLength;
	this->strings = src.strings;
	this->unknownInt2 = src.unknownInt2;
	return *this;
};

//Destructor
Header::~Header() {};
NifInfo Header::Read( istream& in ) {
	//Declare NifInfo structure
	NifInfo info;

	NifStream( headerString, in, info );
	if ( info.version <= 0x03010000 ) {
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			NifStream( copyright[i2], in, info );
		};
	};
	if ( info.version >= 0x0303000D ) {
		NifStream( version, in, info );
	};
	if ( info.version >= 0x14000004 ) {
		NifStream( endianType, in, info );
	};
	if ( info.version >= 0x0A010000 ) {
		NifStream( userVersion, in, info );
	};
	if ( info.version >= 0x0303000D ) {
		NifStream( numBlocks, in, info );
	};
	if ( info.version >= 0x0A010000 ) {
		if ( ((userVersion >= 10) || ((userVersion == 1) && (version != 0x0A020000))) ) {
			NifStream( userVersion2, in, info );
		};
	};
	if ( info.version >= 0x1E000002 ) {
		NifStream( unknownInt3, in, info );
	};
	if ( ( info.version >= 0x0A000102 ) && ( info.version <= 0x0A000102 ) ) {
		if ( info.version <= 0x0A000102 ) {
			NifStream( exportInfo.unknown, in, info );
		};
		NifStream( exportInfo.creator, in, info );
		NifStream( exportInfo.exportInfo1, in, info );
		NifStream( exportInfo.exportInfo2, in, info );
	};
	if ( info.version >= 0x0A010000 ) {
		if ( ((userVersion >= 10) || ((userVersion == 1) && (version != 0x0A020000))) ) {
			if ( info.version <= 0x0A000102 ) {
				NifStream( exportInfo.unknown, in, info );
			};
			NifStream( exportInfo.creator, in, info );
			NifStream( exportInfo.exportInfo1, in, info );
			NifStream( exportInfo.exportInfo2, in, info );
		};
	};
	if ( info.version >= 0x0A000100 ) {
		NifStream( numBlockTypes, in, info );
		blockTypes.resize(numBlockTypes);
		for (unsigned int i2 = 0; i2 < blockTypes.size(); i2++) {
			NifStream( blockTypes[i2], in, info );
		};
		blockTypeIndex.resize(numBlocks);
		for (unsigned int i2 = 0; i2 < blockTypeIndex.size(); i2++) {
			NifStream( blockTypeIndex[i2], in, info );
		};
	};
	if ( info.version >= 0x14020007 ) {
		blockSize.resize(numBlocks);
		for (unsigned int i2 = 0; i2 < blockSize.size(); i2++) {
			NifStream( blockSize[i2], in, info );
		};
	};
	if ( info.version >= 0x14010003 ) {
		NifStream( numStrings, in, info );
		NifStream( maxStringLength, in, info );
		strings.resize(numStrings);
		for (unsigned int i2 = 0; i2 < strings.size(); i2++) {
			NifStream( strings[i2], in, info );
		};
	};
	if ( info.version >= 0x0A000100 ) {
		NifStream( unknownInt2, in, info );
	};

	//Copy info.version to local version var.
	version = info.version;

	//Fill out and return NifInfo structure.
	info.userVersion = userVersion;
	info.userVersion2 = userVersion2;
	info.endian = EndianType(endianType);
	info.creator = exportInfo.creator.str;
	info.exportInfo1 = exportInfo.exportInfo1.str;
	info.exportInfo2 = exportInfo.exportInfo2.str;

	return info;

}

void Header::Write( ostream& out, const NifInfo & info ) const {
	numStrings = (unsigned int)(strings.size());
	numBlockTypes = (unsigned short)(blockTypes.size());
	numBlocks = (unsigned int)(blockTypeIndex.size());
	NifStream( headerString, out, info );
	if ( info.version <= 0x03010000 ) {
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			NifStream( copyright[i2], out, info );
		};
	};
	if ( info.version >= 0x0303000D ) {
		NifStream( version, out, info );
	};
	if ( info.version >= 0x14000004 ) {
		NifStream( endianType, out, info );
	};
	if ( info.version >= 0x0A010000 ) {
		NifStream( userVersion, out, info );
	};
	if ( info.version >= 0x0303000D ) {
		NifStream( numBlocks, out, info );
	};
	if ( info.version >= 0x0A010000 ) {
		if ( ((userVersion >= 10) || ((userVersion == 1) && (version != 0x0A020000))) ) {
			NifStream( userVersion2, out, info );
		};
	};
	if ( info.version >= 0x1E000002 ) {
		NifStream( unknownInt3, out, info );
	};
	if ( ( info.version >= 0x0A000102 ) && ( info.version <= 0x0A000102 ) ) {
		if ( info.version <= 0x0A000102 ) {
			NifStream( exportInfo.unknown, out, info );
		};
		NifStream( exportInfo.creator, out, info );
		NifStream( exportInfo.exportInfo1, out, info );
		NifStream( exportInfo.exportInfo2, out, info );
	};
	if ( info.version >= 0x0A010000 ) {
		if ( ((userVersion >= 10) || ((userVersion == 1) && (version != 0x0A020000))) ) {
			if ( info.version <= 0x0A000102 ) {
				NifStream( exportInfo.unknown, out, info );
			};
			NifStream( exportInfo.creator, out, info );
			NifStream( exportInfo.exportInfo1, out, info );
			NifStream( exportInfo.exportInfo2, out, info );
		};
	};
	if ( info.version >= 0x0A000100 ) {
		NifStream( numBlockTypes, out, info );
		for (unsigned int i2 = 0; i2 < blockTypes.size(); i2++) {
			NifStream( blockTypes[i2], out, info );
		};
		for (unsigned int i2 = 0; i2 < blockTypeIndex.size(); i2++) {
			NifStream( blockTypeIndex[i2], out, info );
		};
	};
	if ( info.version >= 0x14020007 ) {
		for (unsigned int i2 = 0; i2 < blockSize.size(); i2++) {
			NifStream( blockSize[i2], out, info );
		};
	};
	if ( info.version >= 0x14010003 ) {
		NifStream( numStrings, out, info );
		NifStream( maxStringLength, out, info );
		for (unsigned int i2 = 0; i2 < strings.size(); i2++) {
			NifStream( strings[i2], out, info );
		};
	};
	if ( info.version >= 0x0A000100 ) {
		NifStream( unknownInt2, out, info );
	};
}

string Header::asString( bool verbose ) const {
	stringstream out;
	unsigned int array_output_count = 0;
	numStrings = (unsigned int)(strings.size());
	numBlockTypes = (unsigned short)(blockTypes.size());
	numBlocks = (unsigned int)(blockTypeIndex.size());
	out << "  Header String:  " << headerString << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 3; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Copyright[" << i1 << "]:  " << copyright[i1] << endl;
		array_output_count++;
	};
	out << "  Version:  " << version << endl;
	out << "  Endian Type:  " << endianType << endl;
	out << "  User Version:  " << userVersion << endl;
	out << "  Num Blocks:  " << numBlocks << endl;
	if ( ((userVersion >= 10) || ((userVersion == 1) && (version != 0x0A020000))) ) {
		out << "    User Version 2:  " << userVersion2 << endl;
	};
	out << "  Unknown Int 3:  " << unknownInt3 << endl;
	out << "  Unknown:  " << exportInfo.unknown << endl;
	out << "  Creator:  " << exportInfo.creator << endl;
	out << "  Export Info 1:  " << exportInfo.exportInfo1 << endl;
	out << "  Export Info 2:  " << exportInfo.exportInfo2 << endl;
	out << "  Num Block Types:  " << numBlockTypes << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < blockTypes.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Block Types[" << i1 << "]:  " << blockTypes[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < blockTypeIndex.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Block Type Index[" << i1 << "]:  " << blockTypeIndex[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < blockSize.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Block Size[" << i1 << "]:  " << blockSize[i1] << endl;
		array_output_count++;
	};
	out << "  Num Strings:  " << numStrings << endl;
	out << "  Max String Length:  " << maxStringLength << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < strings.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Strings[" << i1 << "]:  " << strings[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	return out.str();
}

//--BEGIN MISC CUSTOM CODE--//

HeaderString Header::getHeaderString() {
	return headerString;
}

unsigned int Header::getVersion() {
	return version;
}

EndianType Header::getEndianType() {
	return endianType;
}

unsigned int Header::getUserVersion() {
	return userVersion;
}

unsigned int Header::getUserVersion2() {
	return userVersion2;
}

vector<string> Header::getBlockTypes() {
	return blockTypes;
}


vector<unsigned short> Niflib::Header::getBlockTypeIndex() {
	return blockTypeIndex;
}

//--END CUSTOM CODE--//
