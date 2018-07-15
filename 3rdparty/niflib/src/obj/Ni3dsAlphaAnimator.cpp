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
#include "../../include/obj/Ni3dsAlphaAnimator.h"
#include "../../include/obj/NiObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type Ni3dsAlphaAnimator::TYPE("Ni3dsAlphaAnimator", &NiObject::TYPE );

Ni3dsAlphaAnimator::Ni3dsAlphaAnimator() : parent(NULL), num1((unsigned int)0), num2((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

Ni3dsAlphaAnimator::~Ni3dsAlphaAnimator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & Ni3dsAlphaAnimator::GetType() const {
	return TYPE;
}

NiObject * Ni3dsAlphaAnimator::Create() {
	return new Ni3dsAlphaAnimator;
}

void Ni3dsAlphaAnimator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 40; i1++) {
		NifStream( unknown1[i1], in, info );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( num1, in, info );
	NifStream( num2, in, info );
	unknown2.resize(num1);
	for (unsigned int i1 = 0; i1 < unknown2.size(); i1++) {
		unknown2[i1].resize(num2);
		for (unsigned int i2 = 0; i2 < unknown2[i1].size(); i2++) {
			NifStream( unknown2[i1][i2], in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void Ni3dsAlphaAnimator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	num2 = (unsigned int)((unknown2.size() > 0) ? unknown2[0].size() : 0);
	num1 = (unsigned int)(unknown2.size());
	for (unsigned int i1 = 0; i1 < 40; i1++) {
		NifStream( unknown1[i1], out, info );
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*parent), out );
	} else {
		if ( parent != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(parent) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( parent );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	NifStream( num1, out, info );
	NifStream( num2, out, info );
	for (unsigned int i1 = 0; i1 < unknown2.size(); i1++) {
		for (unsigned int i2 = 0; i2 < unknown2[i1].size(); i2++) {
			NifStream( unknown2[i1][i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string Ni3dsAlphaAnimator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	num2 = (unsigned int)((unknown2.size() > 0) ? unknown2[0].size() : 0);
	num1 = (unsigned int)(unknown2.size());
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 40; i1++) {
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
	out << "  Parent:  " << parent << endl;
	out << "  Num 1:  " << num1 << endl;
	out << "  Num 2:  " << num2 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknown2.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		for (unsigned int i2 = 0; i2 < unknown2[i1].size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown 2[" << i2 << "]:  " << unknown2[i1][i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void Ni3dsAlphaAnimator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	parent = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> Ni3dsAlphaAnimator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( parent != NULL )
		refs.push_back(StaticCast<NiObject>(parent));
	return refs;
}

std::list<NiObject *> Ni3dsAlphaAnimator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
