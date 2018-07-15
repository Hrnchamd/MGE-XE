/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#include "../include/NIF_IO.h"
#include "../include/niflib.h"
#include "../include/gen/Header.h"
#include "../include/gen/ByteColor4.h"
namespace Niflib {

//--Endian Support Functions--//
EndianType DetectEndianType();
int SwapEndian( int in );
unsigned int SwapEndian( unsigned int in );
short SwapEndian( short in );
unsigned short SwapEndian( unsigned short in );
float SwapEndian( float in );

//Constant that stores the detected endian storage type of the current system
const EndianType sys_endian = DetectEndianType();

//--Endian Function Bodies--//

EndianType DetectEndianType() {
	//Simple endian test
	unsigned char test[2] = { 1, 0 };
	short r = *(short *)test;

	if ( r == 1 ) {
		return ENDIAN_LITTLE;
	} else {
		return ENDIAN_BIG;
	}		
}

int SwapEndian( int in ) {
	int out = 0;
	char * temp_in;
	char * temp_out;

	temp_in = (char*)&in;
	temp_out = (char*)&out;

	temp_out[0] = temp_in[3];
	temp_out[1] = temp_in[2];
	temp_out[2] = temp_in[1];
	temp_out[3] = temp_in[0];

	return out;
}

unsigned int SwapEndian( unsigned int in ) {
	unsigned int out = 0;
	char * temp_in;
	char * temp_out;

	temp_in = (char*)&in;
	temp_out = (char*)&out;

	temp_out[0] = temp_in[3];
	temp_out[1] = temp_in[2];
	temp_out[2] = temp_in[1];
	temp_out[3] = temp_in[0];

	return out;
}

short SwapEndian( short in ) {
	short out = 0;
	char * temp_in;
	char * temp_out;

	temp_in = (char*)&in;
	temp_out = (char*)&out;

	temp_out[0] = temp_in[1];
	temp_out[1] = temp_in[0];

	return out;
}

unsigned short SwapEndian( unsigned short in ) {
	unsigned short out = 0;
	char * temp_in;
	char * temp_out;

	temp_in = (char*)&in;
	temp_out = (char*)&out;

	temp_out[0] = temp_in[1];
	temp_out[1] = temp_in[0];

	return out;
}

float SwapEndian( float in ) {
	float out = 0;
	char * temp_in;
	char * temp_out;

	temp_in = (char*)&in;
	temp_out = (char*)&out;

	temp_out[0] = temp_in[3];
	temp_out[1] = temp_in[2];
	temp_out[2] = temp_in[1];
	temp_out[3] = temp_in[0];

	return out;
}

//--Read utility functions--//

int ReadInt( istream& in ){

	int tmp = 0;
	in.read( (char*)&tmp, 4 );
	if (in.fail())
	  throw runtime_error("premature end of stream");
	return tmp;
}

unsigned int ReadUInt( istream& in ){

	unsigned int tmp = 0;
	in.read( (char*)&tmp, 4 );
	if (in.fail())
	  throw runtime_error("premature end of stream");
	return tmp;
}

unsigned short ReadUShort( istream& in ){

	unsigned short tmp = 0;
	in.read( (char*)&tmp, 2 );
	if (in.fail())
	  throw runtime_error("premature end of stream");
	return tmp;
}

short ReadShort( istream& in ){

	short tmp = 0;
	in.read( (char*)&tmp, 2 );
	if (in.fail())
	  throw runtime_error("premature end of stream");
	return tmp;
}

byte ReadByte( istream& in ){

	byte tmp = 0;
	in.read( (char*)&tmp, 1 );
	if (in.fail())
	  throw runtime_error("premature end of stream");
	return tmp;
}
float ReadFloat( istream &in ){

	float tmp = 0;
	in.read( reinterpret_cast<char*>(&tmp), sizeof(tmp) );
	if (in.fail())
	  throw runtime_error("premature end of stream");
	return tmp;
}

string ReadString( istream &in ) {
	unsigned int len = ReadUInt( in );
	string out;
	if ( len > 0x4000 )
	    throw runtime_error("String too long. Not a NIF file or unsupported format?");
	if ( len > 0 ) {
	    out.resize(len);
	    in.read( (char*)&out[0], len );
	    if (in.fail())
	      throw runtime_error("premature end of stream");
	}
	return out;
}

bool ReadBool( istream &in, unsigned int version ) {
	if ( version <= 0x04010001 ) {
		//Bools are stored as integers before version 4.1.0.1
		return (ReadUInt( in ) != 0);
	} else {
		//And as bytes from 4.1.0.1 on
		return (ReadByte( in ) != 0);
	}
}

//-- Write utility functions--//

void WriteInt( int val, ostream& out ){

	out.write( (char*)&val, 4 );
}

void WriteUInt( unsigned int val, ostream& out ){

	out.write( (char*)&val, 4 );
}

void WritePtr32( void * val, ostream& out ){
#if __SIZEOF_POINTER__ == 4
  // 32 bit
  WriteUInt( (unsigned int)val, out );
#else
  // 64 bit
  union intpoint_t {
    void *ptr;
    struct {
      unsigned int id1;
      unsigned int id2;
    };
  } ptr;
  ptr.id1 = 0;		//  just for compiler warning C4700 (VS2010)
  ptr.id2 = 0;		//  just for compiler warning C4700 (VS2010)
  ptr.ptr = val;
  // xor the two parts
  // (maybe a more advanced hash function would be better, experience will tell)
  WriteUInt(ptr.id1 ^ ptr.id2, out);
#endif
}

void WriteUShort( unsigned short val, ostream& out ){

	out.write( (char*)&val, 2 );
}

void WriteShort( short val, ostream& out ){

	out.write( (char*)&val, 2 );
}

void WriteByte( byte val, ostream& out ){

	out.write( (char*)&val, 1 );
}

void WriteFloat( float val, ostream& out ){
	out.write( reinterpret_cast<char*>(&val), sizeof(val) );
}

void WriteString( string const & val, ostream& out ) {
	WriteUInt( (unsigned int)(val.size()), out );
	out.write( val.c_str(), std::streamsize(val.size()) );
}

void WriteBool( bool val, ostream& out, unsigned int version ) {
	if ( version < 0x04010001 ) {
		//Bools are stored as integers before version 4.1.0.1
		if (val)
			WriteUInt( 1, out );
		else
			WriteUInt( 0, out );
	} else {
		//And as bytes from 4.1.0.1 on
		if (val)
			WriteByte( 1, out );
		else
			WriteByte( 0, out );
	}
}

//-- NifStream And ostream Functions --//

// The NifStream functions allow each built-in type to be streamed to and from a file.
// The ostream functions are for writing out a debug string.

//--Basic Types--//

//int
void NifStream( int & val, istream& in, const NifInfo & info ) {
	if ( info.endian == sys_endian ) {
		val = ReadInt( in );
	} else {
		val = SwapEndian( ReadInt( in ) );
	}
}

void NifStream( int const & val, ostream& out, const NifInfo & info ) {
	if ( info.endian == sys_endian ) {
		WriteInt( val, out );
	} else {
		WriteInt( SwapEndian(val), out );
	}
}

//unsigned int
void NifStream( unsigned int & val, istream& in, const NifInfo & info ) {
	if ( info.endian == sys_endian ) {
		val = ReadUInt( in );
	} else {
		val = SwapEndian( ReadUInt( in ) );
	}
};

void NifStream( unsigned int const & val, ostream& out, const NifInfo & info ) {
	if ( info.endian == sys_endian ) {
		WriteUInt( val, out );
	} else {
		WriteUInt( SwapEndian(val), out );
	}
}

//unsigned short
void NifStream( unsigned short & val, istream& in, const NifInfo & info ) {
	if ( info.endian == sys_endian ) {
		val = ReadUShort( in );
	} else {
		val = SwapEndian( ReadUShort( in ) );
	}
}

void NifStream( unsigned short const & val, ostream& out, const NifInfo & info ) {
	if ( info.endian == sys_endian ) {
		WriteUShort( val, out );
	} else {
		WriteUShort( SwapEndian(val), out );
	}
}

//short
void NifStream( short & val, istream& in, const NifInfo & info ) {
	if ( info.endian == sys_endian ) {
		val = ReadShort( in );
	} else {
		val = SwapEndian( ReadShort( in ) );
	}
}

void NifStream( short const & val, ostream& out, const NifInfo & info ) {
	if ( info.endian == sys_endian ) {
		WriteShort( val, out );
	} else {
		WriteShort( SwapEndian(val), out );
	}
}

//byte
void NifStream( byte & val, istream& in, const NifInfo & info ) {
	val = ReadByte( in );
}

void NifStream( byte const & val, ostream& out, const NifInfo & info ) {
	WriteByte( val, out );
}

//bool
void NifStream( bool & val, istream& in, const NifInfo & info ) {
	val = ReadBool( in, info.version );
}

void NifStream( bool const & val, ostream& out, const NifInfo & info ) {
	WriteBool( val, out, info.version );
}

//float
void NifStream( float & val, istream& in, const NifInfo & info ) {
	if ( info.endian == sys_endian ) {
		val = ReadFloat( in );
	} else {
		val = SwapEndian( ReadFloat( in ) );
	}
}

void NifStream( float const & val, ostream& out, const NifInfo & info ) {
	if ( info.endian == sys_endian ) {
		WriteFloat( val, out );
	} else {
		WriteFloat( SwapEndian(val), out );
	}
}

//string
void NifStream( string & val, istream& in, const NifInfo & info ) {
	val = ReadString( in );
}

void NifStream( string const & val, ostream& out, const NifInfo & info ) {
	WriteString( val, out );
}

//--Structs--//

//HeaderString
void NifStream( HeaderString & val, istream& in, NifInfo & info ) {
	char tmp[256];
	in.getline( tmp, 256 );
	val.header = tmp;

	// make sure this is a NIF file
	unsigned ver_start = 0;
	if ( val.header.substr(0, 22) == "NetImmerse File Format" ) {
		ver_start = 32;
	} else if ( val.header.substr(0, 20) == "Gamebryo File Format" ) {
		ver_start = 30;
	} else if ( val.header.substr(0, 6) == "NDSNIF" ) {
		ver_start = 30;
	} else {
		//Not a NIF file
		info.version = VER_INVALID;
	}

	//Parse version string and return result.
	info.version = ParseVersionString( val.header.substr( ver_start ) );

	////Temporarily read the next 3 strings if this is a < 4 file
	//if ( info.version < VER_3_3_0_13 ) {
	//	in.getline( tmp, 256 );
	//	in.getline( tmp, 256 );
	//	in.getline( tmp, 256 );
	//}

	//if ( version < VER_4_0_0_0 ) {
	//	throw runtime_error("NIF Versions below 4.0.0.0 are not yet supported");
	//}
};

void NifStream( HeaderString const & val, ostream& out, const NifInfo & info ) {
	stringstream header_string;
	if ( info.version <= VER_10_0_1_0 ) {
		header_string << "NetImmerse File Format, Version ";
	} else {
		header_string << "Gamebryo File Format, Version ";
	}

	header_string << FormatVersionString(info.version);
	out << header_string.str() << "\n";
};

ostream & operator<<( ostream & out, HeaderString const & val ) {
	return out << val.header;
}

//LineString
void NifStream( LineString & val, istream& in, const NifInfo & info ) {
	char tmp[256];
	in.getline( tmp, 256 );
	val.line = tmp;
};

void NifStream( LineString const & val, ostream& out, const NifInfo & info ) {
	out << val.line << "\n";
};

ostream & operator<<( ostream & out, LineString const & val ) {
	return out << val.line;
}

//ShortString
void NifStream( ShortString & val, istream& in, const NifInfo & info ) {
	byte len = ReadByte( in );
	char * buffer = new char[len];
	in.read( buffer, len );
	if (in.fail())
	  throw runtime_error("premature end of stream");
	val.str = buffer;
	delete [] buffer;
};

void NifStream( ShortString const & val, ostream& out, const NifInfo & info ) {
	WriteByte( byte(val.str.size() + 1), out );
	out.write( val.str.c_str(), std::streamsize(val.str.size()) );
	WriteByte( 0, out );
};

ostream & operator<<( ostream & out, ShortString const & val ) {
	return out << val.str;
}

//TexCoord
void NifStream( TexCoord & val, istream& in, const NifInfo & info ) {
	val.u = ReadFloat( in );
	val.v = ReadFloat( in );
};

void NifStream( TexCoord const & val, ostream& out, const NifInfo & info ) {
	WriteFloat( val.u, out );
	WriteFloat( val.v, out );
};

//Triangle
void NifStream( Triangle & val, istream& in, const NifInfo & info ) {
	val.v1 = ReadUShort( in );
	val.v2 = ReadUShort( in );
	val.v3 = ReadUShort( in );
};

void NifStream( Triangle const & val, ostream& out, const NifInfo & info ) {
	WriteUShort( val.v1, out );
	WriteUShort( val.v2, out );
	WriteUShort( val.v3, out );
};

//Vector3
void NifStream( Vector3 & val, istream& in, const NifInfo & info ) {
	val.x = ReadFloat( in );
	val.y = ReadFloat( in );
	val.z = ReadFloat( in );
};

void NifStream( Vector3 const & val, ostream& out, const NifInfo & info ) {
	WriteFloat( val.x, out );
	WriteFloat( val.y, out );
	WriteFloat( val.z, out );
};

//Vector3
void NifStream( Vector4 & val, istream& in, const NifInfo & info ) {
	val.x = ReadFloat( in );
	val.y = ReadFloat( in );
	val.z = ReadFloat( in );
	val.w = ReadFloat( in );
};

void NifStream( Vector4 const & val, ostream& out, const NifInfo & info ) {
	WriteFloat( val.x, out );
	WriteFloat( val.y, out );
	WriteFloat( val.z, out );
	WriteFloat( val.w, out );
};

//Float2
void NifStream( Float2 & val, istream& in, const NifInfo & info ) {
	val.data[0] = ReadFloat( in );
	val.data[1] = ReadFloat( in );
};

void NifStream( Float2 const & val, ostream& out, const NifInfo & info ) {
	WriteFloat( val.data[0], out );
	WriteFloat( val.data[1], out );
};

//Matrix22
void NifStream( Matrix22 & val, istream& in, const NifInfo & info ) {
	for (int c = 0; c < 2; ++c) {
		for (int r = 0; r < 2; ++r) {
			val[r][c] = ReadFloat( in );
		}
	}
}

void NifStream( Matrix22 const & val, ostream& out, const NifInfo & info ) {
	for (int c = 0; c < 2; ++c) {
		for (int r = 0; r < 2; ++r) {
			WriteFloat( val[r][c], out );
		}
	}
}

//Float3
void NifStream( Float3 & val, istream& in, const NifInfo & info ) {
	val.data[0] = ReadFloat( in );
	val.data[1] = ReadFloat( in );
	val.data[2] = ReadFloat( in );
};

void NifStream( Float3 const & val, ostream& out, const NifInfo & info ) {
	WriteFloat( val.data[0], out );
	WriteFloat( val.data[1], out );
	WriteFloat( val.data[2], out );
};

//Matrix33
void NifStream( Matrix33 & val, istream& in, const NifInfo & info ) {
	for (int c = 0; c < 3; ++c) {
		for (int r = 0; r < 3; ++r) {
			val[r][c] = ReadFloat( in );
		}
	}
}

void NifStream( Matrix33 const & val, ostream& out, const NifInfo & info ) {
	for (int c = 0; c < 3; ++c) {
		for (int r = 0; r < 3; ++r) {
			WriteFloat( val[r][c], out );
		}
	}
}

//Float4
void NifStream( Float4 & val, istream& in, const NifInfo & info ) {
	val.data[0] = ReadFloat( in );
	val.data[1] = ReadFloat( in );
	val.data[2] = ReadFloat( in );
	val.data[3] = ReadFloat( in );
};

void NifStream( Float4 const & val, ostream& out, const NifInfo & info ) {
	WriteFloat( val.data[0], out );
	WriteFloat( val.data[1], out );
	WriteFloat( val.data[2], out );
	WriteFloat( val.data[3], out );
};

//Matrix44
void NifStream( Matrix44 & val, istream& in, const NifInfo & info ) {
	for (int c = 0; c < 4; ++c) {
		for (int r = 0; r < 4; ++r) {
			val[r][c] = ReadFloat( in );
		}
	}
}

void NifStream( Matrix44 const & val, ostream& out, const NifInfo & info ) {
	for (int c = 0; c < 4; ++c) {
		for (int r = 0; r < 4; ++r) {
			WriteFloat( val[r][c], out );
		}
	}
}

//Color3
void NifStream( Color3 & val, istream& in, const NifInfo & info ) {
	val.r = ReadFloat( in );
	val.g = ReadFloat( in );
	val.b = ReadFloat( in );
};

void NifStream( Color3 const & val, ostream& out, const NifInfo & info ) {
	WriteFloat( val.r, out );
	WriteFloat( val.g, out );
	WriteFloat( val.b, out );
};

//Color4
void NifStream( Color4 & val, istream& in, const NifInfo & info ) {
	val.r = ReadFloat( in );
	val.g = ReadFloat( in );
	val.b = ReadFloat( in );
	val.a = ReadFloat( in );
};

void NifStream( Color4 const & val, ostream& out, const NifInfo & info ) {
	WriteFloat( val.r, out );
	WriteFloat( val.g, out );
	WriteFloat( val.b, out );
	WriteFloat( val.a, out );
};

//Quaternion
void NifStream( Quaternion & val, istream& in, const NifInfo & info ) {
	val.w = ReadFloat( in );
	val.x = ReadFloat( in );
	val.y = ReadFloat( in );
	val.z = ReadFloat( in );
};

void NifStream( Quaternion const & val, ostream& out, const NifInfo & info ) {
	WriteFloat( val.w, out );
	WriteFloat( val.x, out );
	WriteFloat( val.y, out );
	WriteFloat( val.z, out );
};

//The HexString function creates a formatted hex display of the given data for use in printing
//a debug string for information that is not understood
string HexString( const byte * src, unsigned int len ) {
	stringstream out;
	
	//Display Data in Hex form
	out << hex << setfill('0');

	for ( unsigned int i = 0; i < len; ++i ) {
		out << uppercase << setw(2) << (unsigned int)(src[i]);
		if (i % 16 == 15 || i == len - 1)
			out << endl;
		else if (i % 16 == 7)
			out << "   ";
		else if (i % 8 == 3)
			out << "  ";
		else
			out << " ";
	}

	return out.str();

}

//Byte
ostream & operator<<( ostream & out, byte const & val ) {
	return out << (unsigned int)(val);
}

void NifStream( Key<Quaternion> & key, istream& file, const NifInfo & info, KeyType type ) {
	key.time = ReadFloat( file );

	//If key type is not 1, 2, or 3, throw an exception
	if ( type < 1 || type > 3 ) {
		type = LINEAR_KEY;
		//throw runtime_error("Invalid key type.");
	}

	//Read data based on the type of key
	NifStream( key.data, file, info );
	if ( type == TBC_KEY ) {
		//Uses TBC interpolation
		key.tension = ReadFloat( file );
		key.bias = ReadFloat( file );
		key.continuity = ReadFloat( file );
	}
}


void NifStream( Key<Quaternion> const & key, ostream& file, const NifInfo & info,  KeyType type ) {
	WriteFloat( key.time, file );

	//If key type is not 1, 2, or 3, throw an exception
	if ( type < 1 || type > 3 ) {
		type = LINEAR_KEY;
		//throw runtime_error("Invalid key type.");
	}

	//Read data based on the type of key
	NifStream( key.data, file, info );
	if ( type == TBC_KEY ) {
		//Uses TBC interpolation
		WriteFloat( key.tension, file);
		WriteFloat( key.bias, file);
		WriteFloat( key.continuity, file);
	}
}

static void FromIndexString(IndexString const &value, Header* header, unsigned int& idx)
{
	if (header == NULL)
		throw runtime_error("stream not properly configured");
	if (value.empty()) {
		idx = 0xffffffff;
	} else {
		size_t i = 0;
		for ( ; i < header->strings.size(); i++) {
			if (header->strings[i] == value)
				break;
		}
		if (i >= header->numStrings)
			header->numStrings = i;
		size_t len = value.length();
		if (header->maxStringLength < len)
			header->maxStringLength = len;
		header->strings.push_back(value);
		idx = i;
	}
}

static void ToIndexString(unsigned int idx, Header* header, IndexString & value)
{
	if (header == NULL)
		throw runtime_error("stream not properly configured");
	if ( idx == 0xffffffff ) {
		value.clear();
	} else if (idx >= 0 && idx <= header->strings.size()) {
		value = header->strings[idx];
	} else {
		throw runtime_error("invalid string index");
	}
}

void NifStream( IndexString & val, istream& in, const NifInfo & info ) {
	if (info.version >= VER_20_1_0_3) {
		std::streampos pos = in.tellg();

		ToIndexString(ReadUInt(in), hdrInfo::getInfo(in), val);
	} else {
		val = ReadString( in );
	}
}

void NifStream( IndexString const & val, ostream& out, const NifInfo & info ) {
	if (info.version >= VER_20_1_0_3) {
		unsigned idx = 0xffffffff;
		FromIndexString(val, hdrInfo::getInfo(out), idx);
		WriteInt(idx, out);
	} else {
		WriteString( val, out );
	}
}

ostream & operator<<( ostream & out, IndexString const & val ) {
	out << static_cast<string const &>(val);
	return out;
}

template <> void NifStream( Key<IndexString> & key, istream& file, const NifInfo & info, KeyType type )
{
	if (info.version >= VER_20_1_0_3) {
		Key<int> ikey;
		NifStream(ikey, file, info, type);
		key.time = ikey.time;
		ToIndexString(ikey.data, hdrInfo::getInfo(file), key.data);
		key.tension = ikey.tension;
		key.bias = ikey.bias;
		key.continuity = ikey.continuity;
	} else {
		Key<string> skey;
		NifStream(skey, file, info, type);
		key.time = skey.time;
		key.data = skey.data;
		key.tension = skey.tension;
		key.bias = skey.bias;
		key.continuity = skey.continuity;
	}
}

template <> void NifStream( Key<IndexString> const & key, ostream& file, const NifInfo & info,  KeyType type ) {
	if (info.version >= VER_20_1_0_3) {
		Key<unsigned int> ikey;
		ikey.time = key.time;
		ikey.tension = key.tension;
		ikey.bias = key.bias;
		ikey.continuity = key.continuity;
		FromIndexString(key.data, hdrInfo::getInfo(file), ikey.data);
		NifStream(ikey, file, info, type);
	} else {
		Key<string> skey;
		skey.time = key.time;
		skey.data = key.data;
		skey.tension = key.tension;
		skey.bias = key.bias;
		skey.continuity = key.continuity;
		NifStream(skey, file, info, type);
	}
}


const int strInfo::infoIdx = ios_base::xalloc();
const int hdrInfo::infoIdx = ios_base::xalloc();

std::streamsize NifStreamBuf::xsputn(const char_type *_Ptr, std::streamsize _Count) {
	pos += _Count;
	if (size < pos) size = pos;
	return _Count;
}

std::streampos NifStreamBuf::seekoff(std::streamoff offset, std::ios_base::seekdir dir, std::ios_base::openmode mode)
{	// change position by offset, according to way and mode
	switch (dir)
	{
	case std::ios_base::beg:
		pos = offset;
		return (pos >= 0 && pos < size) ? (streampos(-1)) : pos;
	case std::ios_base::cur:
		pos += offset;
		return (pos >= 0 && pos < size) ? (streampos(-1)) : pos;
	case std::ios_base::end:
		pos = size - offset;
		return (pos >= 0 && pos < size) ? (streampos(-1)) : pos;		
        default:
	        return streampos(-1);
	}
	return streampos(-1);
}

std::streampos NifStreamBuf::seekpos(std::streampos offset, std::ios_base::openmode mode)
{	// change to specified position, according to mode
	pos = offset;
	return (pos >= 0 && pos < size) ? (streampos(-1)) : pos;
}

void NifStream( Char8String & val, istream& in, const NifInfo & info ) {
	val.resize(8, '\x0');
	for (int i=0; i<8; ++i)
		in.read( &val[i], 1 );
}

void NifStream( Char8String const & val, ostream& out, const NifInfo & info ) {
	size_t i = 0, n = std::min<size_t>(8, val.size());
	for (i=0;i<n;++i)
		out.write( &val[i], 1 );
	for (;i<8;++i)
		out.write( "\x0", 1 );
}

ostream & operator<<( ostream & out, Char8String const & val ) {
	out << static_cast<string const &>(val);
	return out;
}

//InertiaMatrix
void NifStream( InertiaMatrix & val, istream& in, const NifInfo & info ) {
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 4; ++c) {
			val[r][c] = ReadFloat( in );
		}
	}
}

void NifStream( InertiaMatrix const & val, ostream& out, const NifInfo & info ) {
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 4; ++c) {
			WriteFloat( val[r][c], out );
		}
	}
}

//ByteColor4
void NifStream( ByteColor4 & val, istream& in, const NifInfo & info ) {
  val.r = ReadByte(in);
  val.g = ReadByte(in);
  val.b = ReadByte(in);
  val.a = ReadByte(in);
}

void NifStream( ByteColor4 const & val, ostream& out, const NifInfo & info ) {
  WriteByte( val.r, out);
  WriteByte( val.g, out);
  WriteByte( val.b, out);
  WriteByte( val.a, out);
}

ostream & operator<<( ostream & out, ByteColor4 const & val ) {
  out << "RGBA: " << val.r << " " << val.g << " " << val.b << " " << val.a;
  return out;
}

ostream & operator<<( ostream & out, hdrInfo const & val ) {
	out.pword(hdrInfo::infoIdx) = (void*)val.info;
	return (out);
}

istream & operator>>( istream & istr, hdrInfo & val ) {
	istr.pword(hdrInfo::infoIdx) = (void*)val.info;
	return (istr);
}


ostream & operator<<( ostream & out, strInfo const & val ) {
	out.pword(strInfo::infoIdx) = (void*)val.info;
	return (out);
}

istream & operator>>( istream & istr, strInfo & val ) {
	istr.pword(strInfo::infoIdx) = (void*)val.info;
	return (istr);
}

}
