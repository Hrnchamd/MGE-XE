/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _NIF_BASIC_TYPES_H_
#define _NIF_BASIC_TYPES_H_

#include <string>
#include <stdarg.h>
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

struct IndexString : public std::string {
	IndexString() {}
	IndexString( const IndexString & ref ) : std::string((std::string const &)ref) {}
	IndexString( const std::string & ref ) : std::string(ref) {}
	IndexString& operator=( const IndexString & ref ) { assign((std::string const &)ref); return *this; }
	IndexString& operator=( const std::string & ref ) { assign(ref); return *this; }
	operator std::string const &() const { return *this; }
	operator std::string &() { return *this; }
};

struct Char8String : public std::string {
	Char8String() {}
	Char8String( const Char8String & ref ) : std::string((std::string const &)ref) {}
	Char8String( const std::string & ref ) : std::string(ref) {}
	Char8String& operator=( const Char8String & ref ) { assign((std::string const &)ref); return *this; }
	Char8String& operator=( const std::string & ref ) { assign(ref); return *this; }
	operator std::string const &() const { return *this; }
	operator std::string &() { return *this; }
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
	/*! This is only supported in Oblivion.  It seems to contain the type of script or program used to export the file. */
	string exportInfo1;
	/*! This is only supported in Oblivion.  It seems to contain the more specific script or options of the above. */
	string exportInfo2;
};

/*! Used to enable static arrays to be members of vectors */
template<int size, class T>
struct array {
	array() {
		for ( size_t i = 0; i < size; ++i )
			data[i] = T();
	}
// XXX ellipsis does not work when T = float
// XXX see for instance http://support.microsoft.com/kb/71424
/*
	array(size_t n, ...) {
		va_list argptr;
		va_start(argptr, n);
		for ( size_t i = 0; i < n && i < size; ++i )
			data[i] = va_arg( argptr, T );
		for ( size_t i = n; i < size; ++i )
			data[i] = T();
	}
*/
	array(size_t n, T t0) {
		data[0] = t0;
		for ( size_t i = 1; i < size; ++i )
			data[i] = T();
	}
	array(size_t n, T t0, T t1) {
		data[0] = t0;
		data[1] = t1;
		for ( size_t i = 2; i < size; ++i )
			data[i] = T();
	}
	array(size_t n, T t0, T t1, T t2) {
		data[0] = t0;
		data[1] = t1;
		data[2] = t2;
		for ( size_t i = 3; i < size; ++i )
			data[i] = T();
	}
	array(size_t n, T t0, T t1, T t2, T t3) {
		data[0] = t0;
		data[1] = t1;
		data[2] = t2;
		data[3] = t3;
		for ( size_t i = 4; i < size; ++i )
			data[i] = T();
	}
	array(size_t n, T t0, T t1, T t2, T t3, T t4) {
		data[0] = t0;
		data[1] = t1;
		data[2] = t2;
		data[3] = t3;
		data[4] = t4;
		for ( size_t i = 5; i < size; ++i )
			data[i] = T();
	}
	array(size_t n, T t0, T t1, T t2, T t3, T t4, T t5) {
		data[0] = t0;
		data[1] = t1;
		data[2] = t2;
		data[3] = t3;
		data[4] = t4;
		data[5] = t5;
		for ( size_t i = 6; i < size; ++i )
			data[i] = T();
	}
  array(size_t n, T t0, T t1, T t2, T t3, T t4, T t5, T t6) {
		data[0] = t0;
		data[1] = t1;
		data[2] = t2;
		data[3] = t3;
		data[4] = t4;
		data[5] = t5;
		data[6] = t6;
		for ( size_t i = 7; i < size; ++i )
			data[i] = T();
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
