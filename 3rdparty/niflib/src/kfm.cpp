//--Kfm Functions--//

#include "../include/kfm.h"
#include "../include/niflib.h"
#include "../include/NIF_IO.h"
#include "../include/obj/NiObject.h"

namespace Niflib {

void KfmEventString::Read( istream & in, unsigned int version ) {
	unk_int = ReadUInt(in);
	event = ReadString(in);
};

void KfmEventString::Write( ostream & out, unsigned int version ) {
	WriteUInt(unk_int, out);
	WriteString(event, out);
};

void KfmEvent::Read( istream & in, unsigned int version ) {
	id = ReadUInt(in);
	type = ReadUInt(in);
	if ( type != 5 ) {
		unk_float = ReadFloat(in);
		event_strings.resize(ReadUInt(in));
		for ( vector<KfmEventString>::iterator it = event_strings.begin(); it != event_strings.end(); it++ ) it->Read(in, version);
		unk_int3 = ReadUInt(in);
	};
};

void KfmAction::Read( istream & in, unsigned int version ) {
	if ( version <= VER_KFM_1_2_4b ) action_name = ReadString(in);
	action_filename = ReadString(in);
	unk_int1 = ReadUInt(in);
	events.resize(ReadUInt(in));
	for ( vector<KfmEvent>::iterator it = events.begin(); it != events.end(); it++ ) it->Read(in, version);
	unk_int2 = ReadUInt(in);
};

unsigned int Kfm::Read( string const & file_name ) {
	ifstream in( file_name.c_str(), ifstream::binary );
	unsigned int version = Read(in);
	if ( in.eof() )
		throw runtime_error("End of file reached prematurely. This KFM may be corrupt or improperly supported.");
	ReadByte( in ); // this should fail, and trigger the in.eof() flag
	if ( ! in.eof() )
		throw runtime_error("End of file not reached. This KFM may be corrupt or improperly supported.");
	return version;
};

unsigned int Kfm::Read( istream & in ) {
	//--Read Header--//
	char header_string[64];
	in.getline( header_string, 64 );
	string headerstr(header_string);

	// make sure this is a KFM file
	if ( headerstr.substr(0, 26) != ";Gamebryo KFM File Version" ) {
		version = VER_INVALID;
		return version;
	};

	// supported versions
	if ( headerstr == ";Gamebryo KFM File Version 2.0.0.0b" ) version = VER_KFM_2_0_0_0b;
	else if ( headerstr == ";Gamebryo KFM File Version 1.2.4b" ) version = VER_KFM_1_2_4b;
	//else if ( headerstr == ";Gamebryo KFM File Version 1.0" ) version = VER_KFM_1_0;
	//else if ( headerstr == ";Gamebryo KFM File Version 1.0\r" ) version = VER_KFM_1_0; // Windows eol style
	else {
		version = VER_UNSUPPORTED;
		return version;
	};
	
	//--Read remainder--//
	if (version == VER_KFM_1_0) {
		// TODO write a parser
	} else {
		if (version >= VER_KFM_2_0_0_0b) unk_byte = ReadByte(in);
		else unk_byte = 1;
		nif_filename = ReadString(in);
		master = ReadString(in);
		unk_int1 = ReadUInt(in);
		unk_int2 = ReadUInt(in);
		unk_float1 = ReadFloat(in);
		unk_float2 = ReadFloat(in);
		actions.resize(ReadUInt(in));
		unk_int3 = ReadUInt(in);
		for ( vector<KfmAction>::iterator it = actions.begin(); it != actions.end(); it++ ) it->Read(in, version);
	};

	// Retrieve action names
	if ( version >= VER_KFM_2_0_0_0b ) {
		string model_name = nif_filename.substr(0, nif_filename.length()-4); // strip .nif extension
		for ( vector<KfmAction>::iterator it = actions.begin(); it != actions.end(); it++ ) {
			string action_name = it->action_filename.substr(0, it->action_filename.length()-3); // strip .kf extension
			if (action_name.find( model_name + "_" ) == 0)
				action_name = action_name.substr(model_name.length() + 1, string::npos);
			if (action_name.find( master + "_" ) == 0)
				action_name = action_name.substr(master.length() + 1, string::npos);
			it->action_name = action_name;
		};
	};

	return version;
};

/*
void Kfm::Write( ostream & out, unsigned int version ) {
	if ( version == VER_KFM_1_0 ) {
		// handle this case seperately
		out << ";Gamebryo KFM File Version 1.0" << endl;
		// TODO write the rest of the data
	} else {
		if ( version == VER_KFM_1_2_4b )
			out.write(";Gamebryo KFM File Version 1.2.4b\n", 34);
		else if ( version == VER_KFM_2_0_0_0b )
			out.write(";Gamebryo KFM File Version 2.0.0.0b\n", 37);
		else throw runtime_error("Cannot write KFM file of this version.");
	};
};
*/

Ref<NiObject> Kfm::MergeActions( string const & path ) {
	// Read NIF file
	NiObjectRef nif = ReadNifTree( path + '\\' + nif_filename);
	
	// Read Kf files
	vector<NiObjectRef> kf;
	for ( vector<KfmAction>::iterator it = actions.begin(); it != actions.end(); it++ ) {
		string action_filename = path + '\\' + it->action_filename;
		// Check if the file exists.
		// Probably we should check some other field in the Kfm file to determine this...
		bool exists = false;
		fstream fin;
		fin.open(action_filename.c_str(), ios::in);
		if( fin.is_open() ) exists = true;
		fin.close();
		// Import it, if it exists.
		if (exists) kf.push_back( ReadNifTree(action_filename) );
	};
	
	// TODO: merge everything into the nif file
	return nif;
}

}
