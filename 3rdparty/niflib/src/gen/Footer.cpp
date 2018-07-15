/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/Footer.h"
#include "../../include/obj/NiObject.h"
using namespace Niflib;

//Constructor
Footer::Footer() : numRoots((unsigned int)0) {};

//Copy Constructor
Footer::Footer( const Footer & src ) {
	*this = src;
};

//Copy Operator
Footer & Footer::operator=( const Footer & src ) {
	this->numRoots = src.numRoots;
	this->roots = src.roots;
	return *this;
};

//Destructor
Footer::~Footer() {};

void Footer::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	unsigned int block_num;
	if ( info.version >= 0x0303000D ) {
		NifStream( numRoots, in, info );
		roots.resize(numRoots);
		for (unsigned int i2 = 0; i2 < roots.size(); i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
	};
}

void Footer::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	numRoots = (unsigned int)(roots.size());
	if ( info.version >= 0x0303000D ) {
		NifStream( numRoots, out, info );
		for (unsigned int i2 = 0; i2 < roots.size(); i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*roots[i2]), out );
			} else {
				if ( roots[i2] != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(roots[i2]) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( roots[i2] );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
	};
}

string Footer::asString( bool verbose ) const {
	stringstream out;
	unsigned int array_output_count = 0;
	numRoots = (unsigned int)(roots.size());
	out << "  Num Roots:  " << numRoots << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < roots.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Roots[" << i1 << "]:  " << roots[i1] << endl;
		array_output_count++;
	};
	return out.str();
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
