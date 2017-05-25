/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#include "../include/NIF_IO.h"
#include "../include/niflib.h"
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

	int tmp;
	in.read( (char*)&tmp, 4 );
	return tmp;
}

unsigned int ReadUInt( istream& in ){

	unsigned int tmp;
	in.read( (char*)&tmp, 4 );
	return tmp;
}

unsigned short ReadUShort( istream& in ){

	unsigned short tmp;
	in.read( (char*)&tmp, 2 );
	return tmp;
}

short ReadShort( istream& in ){

	short tmp;
	in.read( (char*)&tmp, 2 );
	return tmp;
}

byte ReadByte( istream& in ){

	byte tmp;
	in.read( (char*)&tmp, 1 );
	return tmp;
}
float ReadFloat( istream &in ){

	float tmp;
	in.read( reinterpret_cast<char*>(&tmp), sizeof(tmp) );
	return tmp;
}

string ReadString( istream &in ) {
	unsigned int len = ReadUInt( in );
	string out;
	if ( len > 10000 )
	    throw runtime_error("String too long. Not a NIF file or unsupported format?");
	if ( len > 0 ) {
	    out.resize(len);
		in.read( (char*)&out[0], len );
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

	char * byte_ver = (char*)&(info.version);
	int int_ver[4] = { byte_ver[3], byte_ver[2], byte_ver[1], byte_ver[0] };

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
	NifStream( key.data, file );
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
	NifStream( key.data, file );
	if ( type == TBC_KEY ) {
		//Uses TBC interpolation
		WriteFloat( key.tension, file);
		WriteFloat( key.bias, file);
		WriteFloat( key.continuity, file);
	}
}

}
