/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _NIF_IO_H
#define _NIF_IO_H

//--Includes--//
#include <string>
#include <sstream>
#include <vector>
#include "Key.h"
#include "gen/enums_intl.h"
#include "nif_math.h"
#include "nif_versions.h"

namespace Niflib {
using namespace std;

#ifndef NULL
#define NULL 0
#endif

#define MAXARRAYDUMP 20

//--IO Functions--//

//-- Read Utility Functions--//
int ReadInt( istream& in );
unsigned int ReadUInt( istream& in );
unsigned short ReadUShort( istream& in );
short ReadShort( istream& in );
byte ReadByte( istream& in );
float ReadFloat( istream &in );
string ReadString( istream &in );
bool ReadBool( istream &in, unsigned int version );

//-- Write Utility Functions --//
void WriteInt( int val, ostream& out );
void WriteUInt( unsigned int val, ostream& out );
void WritePtr32( void * val, ostream& out );
void WriteUShort( unsigned short val, ostream& out );
void WriteShort( short val, ostream& out );
void WriteByte( byte val, ostream& out );
void WriteFloat( float val, ostream& out );
void WriteString( string const & val, ostream& out );
void WriteBool( bool val, ostream& out, unsigned int version );

//-- BitField Helper functions --//

template <class storage>
bool UnpackFlag( storage src, size_t lshift ) {
	//Generate mask
	storage mask = 1 << lshift;

	return (( src & mask) >> lshift) != 0;
}

template <class storage>
void PackFlag( storage & dest, bool new_value, size_t lshift ) {
	//Generate mask
	storage mask = 1 << lshift;

	//Clear current value of requested flag
	dest &= ~mask;

	//Pack in the new value
	dest |= ( ((storage)new_value << lshift) & mask );
}

template <class storage>
storage UnpackField( storage src, size_t lshift, size_t num_bits ) {
	//Generate mask
	storage mask = 0;
	for ( size_t i = lshift; i < num_bits + lshift; ++i ) {
		mask |= (1 << i);
	}

	return (storage)(( src & mask) >> lshift);
}

template <class storage, class T>
void PackField( storage & dest, T new_value, size_t lshift, size_t num_bits ) {
	//Generate Mask
	storage mask = 0;
	for ( size_t i = lshift; i < num_bits + lshift; ++i ) {
		mask |= (1 << i);
	}

	//Clear current value of requested field
	dest &= ~mask;

	//Pack in the new value
	dest |= ( ((storage)new_value << lshift) & mask );
}

//-- NifStream And ostream Functions --//
// The NifStream functions allow each built-in type to be streamed to and from a file.
// The ostream functions are for writing out a debug string.

//--Basic Types--//

//int
void NifStream( int & val, istream& in, const NifInfo & info);
void NifStream( int const & val, ostream& out, const NifInfo & info );

//unsigned int
void NifStream( unsigned int & val, istream& in, const NifInfo & info);
void NifStream( unsigned int const & val, ostream& out, const NifInfo & info);

//unsigned short
void NifStream( unsigned short & val, istream& in, const NifInfo & info);
void NifStream( unsigned short const & val, ostream& out, const NifInfo & info );

//short
void NifStream( short & val, istream& in, const NifInfo & info);
void NifStream( short const & val, ostream& out, const NifInfo & info);

//byte
void NifStream( byte & val, istream& in, const NifInfo & info);
void NifStream( byte const & val, ostream& out, const NifInfo & info);

//bool
void NifStream( bool & val, istream& in, const NifInfo & info);  // version is significant
void NifStream( bool const & val, ostream& out, const NifInfo & info); // version is significant

//float
void NifStream( float & val, istream& in, const NifInfo & info);
void NifStream( float const & val, ostream& out, const NifInfo & info);

//string
void NifStream( string & val, istream& in, const NifInfo & info);
void NifStream( string const & val, ostream& out, const NifInfo & info);

//--Structs--//

//TexCoord
void NifStream( TexCoord & val, istream& in, const NifInfo & info);
void NifStream( TexCoord const & val, ostream& out, const NifInfo & info);

//Triangle
void NifStream( Triangle & val, istream& in, const NifInfo & info);
void NifStream( Triangle const & val, ostream& out, const NifInfo & info);

//Vector3
void NifStream( Vector3 & val, istream& in, const NifInfo & info);
void NifStream( Vector3 const & val, ostream& out, const NifInfo & info );

//Vector4
void NifStream( Vector4 & val, istream& in, const NifInfo & info);
void NifStream( Vector4 const & val, ostream& out, const NifInfo & info );

//Float2
void NifStream( Float2 & val, istream& in, const NifInfo & info);
void NifStream( Float2 const & val, ostream& out, const NifInfo & info );

//Matrix22
void NifStream( Matrix22 & val, istream& in, const NifInfo & info);
void NifStream( Matrix22 const & val, ostream& out, const NifInfo & info);

//Float3
void NifStream( Float3 & val, istream& in, const NifInfo & info);
void NifStream( Float3 const & val, ostream& out, const NifInfo & info );

//Matrix33
void NifStream( Matrix33 & val, istream& in, const NifInfo & info);
void NifStream( Matrix33 const & val, ostream& out, const NifInfo & info);

//Float4
void NifStream( Float4 & val, istream& in, const NifInfo & info);
void NifStream( Float4 const & val, ostream& out, const NifInfo & info );

//Matrix44
void NifStream( Matrix44 & val, istream& in, const NifInfo & info);
void NifStream( Matrix44 const & val, ostream& out, const NifInfo & info);

//Color3
void NifStream( Color3 & val, istream& in, const NifInfo & info);
void NifStream( Color3 const & val, ostream& out, const NifInfo & info );

//Color4
void NifStream( Color4 & val, istream& in, const NifInfo & info);
void NifStream( Color4 const & val, ostream& out, const NifInfo & info );

//Quaternion
void NifStream( Quaternion & val, istream& in, const NifInfo & info);
void NifStream( Quaternion const & val, ostream& out, const NifInfo & info );

//HeaderString
void NifStream( HeaderString & val, istream& in, NifInfo & info ); //Sets the passed in info
void NifStream( HeaderString const & val, ostream& out, const NifInfo & info );
ostream & operator<<( ostream & out, HeaderString const & val );

//LineString
void NifStream( LineString & val, istream& in, const NifInfo & info);
void NifStream( LineString const & val, ostream& out, const NifInfo & info );
ostream & operator<<( ostream & out, LineString const & val );

//ShortString
void NifStream( ShortString & val, istream& in, const NifInfo & info);
void NifStream( ShortString const & val, ostream& out, const NifInfo & info );
ostream & operator<<( ostream & out, ShortString const & val );

//IndexString
void NifStream( IndexString & val, istream& in, const NifInfo & info );
void NifStream( IndexString const & val, ostream& out, const NifInfo & info );
ostream & operator<<( ostream & out, IndexString const & val );

//Char8String
void NifStream( Char8String & val, istream& in, const NifInfo & info );
void NifStream( Char8String const & val, ostream& out, const NifInfo & info );
ostream & operator<<( ostream & out, Char8String const & val );

//InertiaMatrix
void NifStream( InertiaMatrix & val, istream& in, const NifInfo & info);
void NifStream( InertiaMatrix const & val, ostream& out, const NifInfo & info);

//ByteColor4
struct ByteColor4;
void NifStream( ByteColor4 & val, istream& in, const NifInfo & info);
void NifStream( ByteColor4 const & val, ostream& out, const NifInfo & info);
ostream & operator<<( ostream & out, ByteColor4 const & val );

//--Templates--//

void NifStream( Key<Quaternion> & key, istream& file, const NifInfo & info, KeyType type );
void NifStream( Key<Quaternion> const & key, ostream& file, const NifInfo & info,  KeyType type );

//Key<T>
template <class T> 
void NifStream( Key<T> & key, istream& file, const NifInfo & info, KeyType type ) {
	key.time = ReadFloat( file );

	//If key type is not 1, 2, or 3, throw an exception
	if ( type < 1 || type > 3 ) {
		type = LINEAR_KEY;
		//throw runtime_error("Invalid key type.");
	}

	//Read data based on the type of key
	NifStream( key.data, file, info );
	if ( type == QUADRATIC_KEY ) {
		//Uses Quadratic interpolation
		NifStream( key.forward_tangent, file, info );
		NifStream( key.backward_tangent, file, info );
	} else if ( type == TBC_KEY ) {
		//Uses TBC interpolation
		key.tension = ReadFloat( file );
		key.bias = ReadFloat( file );
		key.continuity = ReadFloat( file );
	}
}

template <class T> 
void NifStream( Key<T> & key, istream & file, const NifInfo & info, int type ) {
	NifStream( key, file, info, (KeyType)type );
}

template <class T> 
void NifStream( Key<T> const & key, ostream& file, const NifInfo & info, KeyType type ) {
	WriteFloat( key.time, file );

	//If key type is not 1, 2, or 3, throw an exception
	if ( type < 1 || type > 3 ) {
		type = LINEAR_KEY;
		//throw runtime_error("Invalid key type.");
	}

	//Read data based on the type of key
	NifStream( key.data, file, info );
	if ( type == QUADRATIC_KEY ) {
		//Uses Quadratic interpolation
		NifStream( key.forward_tangent, file, info );
		NifStream( key.backward_tangent, file, info );
	} else if ( type == TBC_KEY ) {
		//Uses TBC interpolation
		WriteFloat( key.tension, file);
		WriteFloat( key.bias, file);
		WriteFloat( key.continuity, file);
	}
}

template <class T> 
void NifStream( Key<T> const & key, ostream & file, const NifInfo & info, int type ) {
	NifStream( key, file, info, (KeyType)type );
}

template <> void NifStream( Key<IndexString> & key, istream& file, const NifInfo & info, KeyType type );
template <> void NifStream( Key<IndexString> const & key, ostream& file, const NifInfo & info,  KeyType type );


//The HexString function creates a formatted hex display of the given data for use in printing
//a debug string for information that is not understood
string HexString( const byte * src, unsigned int len );

//Byte
ostream & operator<<( ostream & out, byte const & val );

// strInfo
struct NifInfo;
class strInfo
{
public:
	strInfo(NifInfo * value) : info(value) {}
private:
	NifInfo *info;
	static const int infoIdx;
	friend ostream & operator<<( ostream & out, strInfo const & val );
	friend istream & operator>>( istream & out, strInfo & val );
public:
	static NifInfo * getInfo(ios_base& str) {
		return (NifInfo *)str.pword(infoIdx);
	}
};


// hdrInfo
struct Header;
class hdrInfo
{
public:
	hdrInfo(Header * value) : info(value) {}
private:
	Header *info;
	static const int infoIdx;
	friend ostream & operator<<( ostream & out, hdrInfo const & val );
	friend istream & operator>>( istream & out, hdrInfo & val );
public:
	static Header * getInfo(ios_base& str) {
		return (Header *)str.pword(infoIdx);
	}
};

class NifStreamBuf : public std::streambuf {
	streamsize size; 
	pos_type pos;
public:
	NifStreamBuf () : size(0), pos(0) {}
private:
	friend class NifSizeStream;
    char *pbase( ) const { return NULL; }
    char *pptr( ) const { return NULL; }
    char *epptr( ) const { return NULL; }
    // disable spurious msvc warning about xsgetn
    #pragma warning (disable : 4996)
    virtual streamsize xsgetn( char_type *_Ptr, streamsize _Count ) { return 0; }
    virtual streamsize xsputn(const char_type *_Ptr, streamsize _Count);
	virtual streampos seekoff(streamoff, ios_base::seekdir, ios_base::openmode = ios_base::in | ios_base::out);
	virtual streampos seekpos(streampos, ios_base::openmode = ios_base::in | ios_base::out);

	void reset() { size = 0; pos = 0; }
};

class NifSizeStream : public std::ostream {
	NifStreamBuf _buf;
public:
	NifSizeStream() : std::ostream( &_buf ) {}
	void reset() { _buf.reset(); }
};

}
#endif
