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
#include "../../include/obj/Ni3dsAnimationNode.h"
#include "../../include/obj/NiObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type Ni3dsAnimationNode::TYPE("Ni3dsAnimationNode", &NiObject::TYPE );

Ni3dsAnimationNode::Ni3dsAnimationNode() : hasData(false), unknownShort((unsigned short)0), child(NULL), count((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

Ni3dsAnimationNode::~Ni3dsAnimationNode() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & Ni3dsAnimationNode::GetType() const {
	return TYPE;
}

NiObject * Ni3dsAnimationNode::Create() {
	return new Ni3dsAnimationNode;
}

void Ni3dsAnimationNode::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( name, in, info );
	NifStream( hasData, in, info );
	if ( hasData ) {
		for (unsigned int i2 = 0; i2 < 21; i2++) {
			NifStream( unknownFloats1[i2], in, info );
		};
		NifStream( unknownShort, in, info );
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		for (unsigned int i2 = 0; i2 < 12; i2++) {
			NifStream( unknownFloats2[i2], in, info );
		};
		NifStream( count, in, info );
		unknownArray.resize(count);
		for (unsigned int i2 = 0; i2 < unknownArray.size(); i2++) {
			for (unsigned int i3 = 0; i3 < 5; i3++) {
				NifStream( unknownArray[i2][i3], in, info );
			};
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void Ni3dsAnimationNode::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	count = (unsigned int)(unknownArray.size());
	NifStream( name, out, info );
	NifStream( hasData, out, info );
	if ( hasData ) {
		for (unsigned int i2 = 0; i2 < 21; i2++) {
			NifStream( unknownFloats1[i2], out, info );
		};
		NifStream( unknownShort, out, info );
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*child), out );
		} else {
			if ( child != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(child) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( child );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		for (unsigned int i2 = 0; i2 < 12; i2++) {
			NifStream( unknownFloats2[i2], out, info );
		};
		NifStream( count, out, info );
		for (unsigned int i2 = 0; i2 < unknownArray.size(); i2++) {
			for (unsigned int i3 = 0; i3 < 5; i3++) {
				NifStream( unknownArray[i2][i3], out, info );
			};
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string Ni3dsAnimationNode::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	count = (unsigned int)(unknownArray.size());
	out << "  Name:  " << name << endl;
	out << "  Has Data:  " << hasData << endl;
	if ( hasData ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < 21; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown Floats 1[" << i2 << "]:  " << unknownFloats1[i2] << endl;
			array_output_count++;
		};
		out << "    Unknown Short:  " << unknownShort << endl;
		out << "    Child:  " << child << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < 12; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown Floats 2[" << i2 << "]:  " << unknownFloats2[i2] << endl;
			array_output_count++;
		};
		out << "    Count:  " << count << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < unknownArray.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			for (unsigned int i3 = 0; i3 < 5; i3++) {
				if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
					break;
				};
				out << "        Unknown Array[" << i3 << "]:  " << unknownArray[i2][i3] << endl;
				array_output_count++;
			};
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void Ni3dsAnimationNode::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( hasData ) {
		child = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> Ni3dsAnimationNode::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( child != NULL )
		refs.push_back(StaticCast<NiObject>(child));
	return refs;
}

std::list<NiObject *> Ni3dsAnimationNode::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
