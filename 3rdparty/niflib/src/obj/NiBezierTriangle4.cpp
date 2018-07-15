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
#include "../../include/obj/NiBezierTriangle4.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiBezierTriangle4::TYPE("NiBezierTriangle4", &NiObject::TYPE );

NiBezierTriangle4::NiBezierTriangle4() : unknown2((unsigned short)0), unknown4((byte)0), unknown5((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiBezierTriangle4::~NiBezierTriangle4() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiBezierTriangle4::GetType() const {
	return TYPE;
}

NiObject * NiBezierTriangle4::Create() {
	return new NiBezierTriangle4;
}

void NiBezierTriangle4::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 6; i1++) {
		NifStream( unknown1[i1], in, info );
	};
	NifStream( unknown2, in, info );
	NifStream( matrix, in, info );
	NifStream( vector1, in, info );
	NifStream( vector2, in, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknown3[i1], in, info );
	};
	NifStream( unknown4, in, info );
	NifStream( unknown5, in, info );
	for (unsigned int i1 = 0; i1 < 24; i1++) {
		NifStream( unknown6[i1], in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiBezierTriangle4::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < 6; i1++) {
		NifStream( unknown1[i1], out, info );
	};
	NifStream( unknown2, out, info );
	NifStream( matrix, out, info );
	NifStream( vector1, out, info );
	NifStream( vector2, out, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknown3[i1], out, info );
	};
	NifStream( unknown4, out, info );
	NifStream( unknown5, out, info );
	for (unsigned int i1 = 0; i1 < 24; i1++) {
		NifStream( unknown6[i1], out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiBezierTriangle4::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 6; i1++) {
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
	out << "  Unknown 2:  " << unknown2 << endl;
	out << "  Matrix:  " << matrix << endl;
	out << "  Vector 1:  " << vector1 << endl;
	out << "  Vector 2:  " << vector2 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 3[" << i1 << "]:  " << unknown3[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown 4:  " << unknown4 << endl;
	out << "  Unknown 5:  " << unknown5 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 24; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 6[" << i1 << "]:  " << unknown6[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiBezierTriangle4::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBezierTriangle4::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiBezierTriangle4::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
