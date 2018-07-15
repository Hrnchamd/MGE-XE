/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _HEADER_H_
#define _HEADER_H_

#include "../NIF_IO.h"
#include "../obj/NiObject.h"

// Include structures
#include "ExportInfo.h"
namespace Niflib {


/*! The NIF file header. */
struct Header {
	/*! Default Constructor */
	NIFLIB_API Header();
	/*! Default Destructor */
	NIFLIB_API ~Header();
	/*! Copy Constructor */
	NIFLIB_API Header( const Header & src );
	/*! Copy Operator */
	NIFLIB_API Header & operator=( const Header & src );
	/*!
	 * 'NetImmerse File Format x.x.x.x' (versions <= 10.0.1.2) or 'Gamebryo File Format
	 * x.x.x.x' (versions >= 10.1.0.0), with x.x.x.x the version written out. Ends with
	 * a newline character (0x0A).
	 */
	HeaderString headerString;
	/*! Unknown. */
	array<3,LineString > copyright;
	/*!
	 * The NIF version, in hexadecimal notation: 0x04000002, 0x0401000C, 0x04020002,
	 * 0x04020100, 0x04020200, 0x0A000100, 0x0A010000, 0x0A020000, 0x14000004, ...
	 */
	unsigned int version;
	/*! Determines the endianness of the data in the file. */
	EndianType endianType;
	/*! An extra version number, for companies that decide to modify the file format. */
	unsigned int userVersion;
	/*! Number of file objects. */
	mutable unsigned int numBlocks;
	/*!
	 * This also appears to be the extra user version number and must be set in some
	 * circumstances. Probably used by Bethesda to denote the Havok version.
	 */
	unsigned int userVersion2;
	/*! Unknown. Possibly User Version 2? */
	unsigned int unknownInt3;
	/*! Unknown. */
	ExportInfo exportInfo;
	/*! Number of object types in this NIF file. */
	mutable unsigned short numBlockTypes;
	/*! List of all object types used in this NIF file. */
	vector<string > blockTypes;
	/*!
	 * Maps file objects on their corresponding type: first file object is of type
	 * object_types[object_type_index[0]], the second of
	 * object_types[object_type_index[1]], etc.
	 */
	vector<unsigned short > blockTypeIndex;
	/*! Array of block sizes? */
	vector<unsigned int > blockSize;
	/*! Number of strings. */
	mutable unsigned int numStrings;
	/*! Maximum string length. */
	unsigned int maxStringLength;
	/*! Strings. */
	vector<string > strings;
	/*! Unknown. */
	unsigned int unknownInt2;
	NIFLIB_HIDDEN NifInfo Read( istream& in );
	NIFLIB_HIDDEN void Write( ostream& out, const NifInfo & info = NifInfo() ) const;
	NIFLIB_HIDDEN string asString( bool verbose = false ) const;
	//--BEGIN MISC CUSTOM CODE--//

	/*! HeaderString
	 * \return The header string
	 */
	NIFLIB_API HeaderString getHeaderString();

	/*! Nif Version
	 * \return The current nif version
	 */
	NIFLIB_API unsigned int getVersion();

	/*! Endian type
	 * \return The endian type. Intel machines use small endian
	 */
	NIFLIB_API EndianType getEndianType();

	/*! User version
	 * \return The user version of this file which refers to the company/game that used the netimmerse/gamebryo engine
	 */
	NIFLIB_API unsigned int getUserVersion();

	/*! User version2
	 * \return The user version of this file which refers to the company/game that used the netimmerse/gamebryo engine
	 */
	NIFLIB_API unsigned int getUserVersion2();

	/*! Block type
	 * \return A vector containing all the names of the block types in the nif file. Useful for determing what does the nif contain
	 */
	NIFLIB_API vector<string> getBlockTypes();

	/*! Block type
	 * \return A vector containing all the indexes in the block types list that denote the type of each block in the nif
	 */
	NIFLIB_API vector<unsigned short> getBlockTypeIndex(); 

	//--END CUSTOM CODE--//
};

}
#endif
