/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _NIF_BASIC_TYPES_H_
#define _NIF_BASIC_TYPES_H_

#include <string>
#include "gen/enums.h"
#include "nif_versions.h"

namespace Niflib {
using namespace std;

struct HeaderString {
	string header;
};

struct ShortString {
	string str;
};

struct LineString {
	string line;
};

//--Non-mathematical Basic Types--//
#ifndef byte
typedef unsigned char	byte;
#endif

//--Structures--//

/*! 
 * Used to specify optional ways the NIF file is to be written or retrieve information about
 * the way an existing file was stored. 
 */
struct NifInfo {
	NifInfo() : version(VER_4_0_0_2), userVersion(0), userVersion2(0), endian(ENDIAN_LITTLE) {}
	NifInfo( unsigned version, unsigned userVersion = 0, unsigned userVersion2 = 0) {
		this->version = version;
		this->userVersion = userVersion;
		this->userVersion2 = userVersion2;
		endian = ENDIAN_LITTLE;
	}
	unsigned version;
	unsigned userVersion;
	unsigned userVersion2;
	/*! Specifies which low-level number storage format to use. Should match the processor type for the target system. */
	EndianType endian;
	/*! This is only supported in Oblivion.  It contains the name of the person who created the NIF file. */
	string creator;
	/*! This is only supported in Oblivion.  It seems to contiain the type of script or program used to export the file. */
	string exportInfo1;
	/*! This is only supported in Oblivion.  It seems to contain the more specific script or options of the above. */
	string exportInfo2;
};

/*! Used to enable static arrays to be members of vectors */
template<int size, class T>
struct array {
	array() {
		for ( size_t i = 0; i < size; ++i ) {
			data[i] = T();
		}
	}
	~array() {}
	T & operator[]( unsigned int index ) {
		return data[index];
	}
	const T & operator[]( unsigned int index ) const {
		return data[index];
	}
private:
	T data[size];
};

//TODO:  This is temporary to make it compile.  Should eventually be adjusted to display 1's and 0's insted of as an int.
typedef unsigned short Flags;
}
#endif
