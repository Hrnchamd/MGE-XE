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
#include "../../include/obj/bhkMeshShape.h"
#include "../../include/obj/NiTriStripsData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkMeshShape::TYPE("bhkMeshShape", &bhkShape::TYPE );

bhkMeshShape::bhkMeshShape() : numUnknownFloats((int)0), numStripsData((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

bhkMeshShape::~bhkMeshShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & bhkMeshShape::GetType() const {
	return TYPE;
}

NiObject * bhkMeshShape::Create() {
	return new bhkMeshShape;
}

void bhkMeshShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	bhkShape::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 9; i1++) {
		NifStream( unknown1[i1], in, info );
	};
	NifStream( numUnknownFloats, in, info );
	unknownFloats.resize(numUnknownFloats);
	for (unsigned int i1 = 0; i1 < unknownFloats.size(); i1++) {
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			NifStream( unknownFloats[i1][i2], in, info );
		};
	};
	for (unsigned int i1 = 0; i1 < 3; i1++) {
		NifStream( unknown2[i1], in, info );
	};
	if ( info.version <= 0x0A000100 ) {
		NifStream( numStripsData, in, info );
		stripsData.resize(numStripsData);
		for (unsigned int i2 = 0; i2 < stripsData.size(); i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void bhkMeshShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkShape::Write( out, link_map, missing_link_stack, info );
	numStripsData = (unsigned int)(stripsData.size());
	numUnknownFloats = (int)(unknownFloats.size());
	for (unsigned int i1 = 0; i1 < 9; i1++) {
		NifStream( unknown1[i1], out, info );
	};
	NifStream( numUnknownFloats, out, info );
	for (unsigned int i1 = 0; i1 < unknownFloats.size(); i1++) {
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			NifStream( unknownFloats[i1][i2], out, info );
		};
	};
	for (unsigned int i1 = 0; i1 < 3; i1++) {
		NifStream( unknown2[i1], out, info );
	};
	if ( info.version <= 0x0A000100 ) {
		NifStream( numStripsData, out, info );
		for (unsigned int i2 = 0; i2 < stripsData.size(); i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*stripsData[i2]), out );
			} else {
				if ( stripsData[i2] != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(stripsData[i2]) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( stripsData[i2] );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string bhkMeshShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkShape::asString();
	numStripsData = (unsigned int)(stripsData.size());
	numUnknownFloats = (int)(unknownFloats.size());
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 9; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 1[" << i1 << "]:  " << unknown1[i1] << endl;
		array_output_count++;
	};
	out << "  Num Unknown Floats:  " << numUnknownFloats << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknownFloats.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown Floats[" << i2 << "]:  " << unknownFloats[i1][i2] << endl;
			array_output_count++;
		};
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 3; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 2[" << i1 << "]:  " << unknown2[i1] << endl;
		array_output_count++;
	};
	out << "  Num Strips Data:  " << numStripsData << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < stripsData.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Strips Data[" << i1 << "]:  " << stripsData[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void bhkMeshShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkShape::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( info.version <= 0x0A000100 ) {
		for (unsigned int i2 = 0; i2 < stripsData.size(); i2++) {
			stripsData[i2] = FixLink<NiTriStripsData>( objects, link_stack, missing_link_stack, info );
		};
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkMeshShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkShape::GetRefs();
	for (unsigned int i1 = 0; i1 < stripsData.size(); i1++) {
		if ( stripsData[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(stripsData[i1]));
	};
	return refs;
}

std::list<NiObject *> bhkMeshShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkShape::GetPtrs();
	for (unsigned int i1 = 0; i1 < stripsData.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
