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
#include "../../include/obj/BSTreadTransfInterpolator.h"
#include "../../include/gen/BSTreadTransform.h"
#include "../../include/gen/BSTreadTransformData.h"
#include "../../include/gen/BSTreadTransformData.h"
#include "../../include/obj/NiFloatData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSTreadTransfInterpolator::TYPE("BSTreadTransfInterpolator", &NiInterpolator::TYPE );

BSTreadTransfInterpolator::BSTreadTransfInterpolator() : numTreadTransforms((int)0), data(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSTreadTransfInterpolator::~BSTreadTransfInterpolator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSTreadTransfInterpolator::GetType() const {
	return TYPE;
}

NiObject * BSTreadTransfInterpolator::Create() {
	return new BSTreadTransfInterpolator;
}

void BSTreadTransfInterpolator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiInterpolator::Read( in, link_stack, info );
	NifStream( numTreadTransforms, in, info );
	treadTransforms.resize(numTreadTransforms);
	for (unsigned int i1 = 0; i1 < treadTransforms.size(); i1++) {
		NifStream( treadTransforms[i1].name, in, info );
		NifStream( treadTransforms[i1].transform1.translation, in, info );
		NifStream( treadTransforms[i1].transform1.rotation, in, info );
		NifStream( treadTransforms[i1].transform1.scale, in, info );
		NifStream( treadTransforms[i1].transform2.translation, in, info );
		NifStream( treadTransforms[i1].transform2.rotation, in, info );
		NifStream( treadTransforms[i1].transform2.scale, in, info );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSTreadTransfInterpolator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiInterpolator::Write( out, link_map, missing_link_stack, info );
	numTreadTransforms = (int)(treadTransforms.size());
	NifStream( numTreadTransforms, out, info );
	for (unsigned int i1 = 0; i1 < treadTransforms.size(); i1++) {
		NifStream( treadTransforms[i1].name, out, info );
		NifStream( treadTransforms[i1].transform1.translation, out, info );
		NifStream( treadTransforms[i1].transform1.rotation, out, info );
		NifStream( treadTransforms[i1].transform1.scale, out, info );
		NifStream( treadTransforms[i1].transform2.translation, out, info );
		NifStream( treadTransforms[i1].transform2.rotation, out, info );
		NifStream( treadTransforms[i1].transform2.scale, out, info );
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*data), out );
	} else {
		if ( data != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(data) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( data );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSTreadTransfInterpolator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiInterpolator::asString();
	numTreadTransforms = (int)(treadTransforms.size());
	out << "  Num Tread Transforms:  " << numTreadTransforms << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < treadTransforms.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Name:  " << treadTransforms[i1].name << endl;
		out << "    Translation:  " << treadTransforms[i1].transform1.translation << endl;
		out << "    Rotation:  " << treadTransforms[i1].transform1.rotation << endl;
		out << "    Scale:  " << treadTransforms[i1].transform1.scale << endl;
		out << "    Translation:  " << treadTransforms[i1].transform2.translation << endl;
		out << "    Rotation:  " << treadTransforms[i1].transform2.rotation << endl;
		out << "    Scale:  " << treadTransforms[i1].transform2.scale << endl;
	};
	out << "  Data:  " << data << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSTreadTransfInterpolator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiInterpolator::FixLinks( objects, link_stack, missing_link_stack, info );
	data = FixLink<NiFloatData>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSTreadTransfInterpolator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiInterpolator::GetRefs();
	if ( data != NULL )
		refs.push_back(StaticCast<NiObject>(data));
	return refs;
}

std::list<NiObject *> BSTreadTransfInterpolator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiInterpolator::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
