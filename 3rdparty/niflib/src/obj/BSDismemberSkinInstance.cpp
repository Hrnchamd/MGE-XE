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
#include "../../include/obj/BSDismemberSkinInstance.h"
#include "../../include/gen/BodyPartList.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSDismemberSkinInstance::TYPE("BSDismemberSkinInstance", &NiSkinInstance::TYPE );

BSDismemberSkinInstance::BSDismemberSkinInstance() : numPartitions((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSDismemberSkinInstance::~BSDismemberSkinInstance() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSDismemberSkinInstance::GetType() const {
	return TYPE;
}

NiObject * BSDismemberSkinInstance::Create() {
	return new BSDismemberSkinInstance;
}

void BSDismemberSkinInstance::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiSkinInstance::Read( in, link_stack, info );
	NifStream( numPartitions, in, info );
	partitions.resize(numPartitions);
	for (unsigned int i1 = 0; i1 < partitions.size(); i1++) {
		NifStream( partitions[i1].partFlag, in, info );
		NifStream( partitions[i1].bodyPart, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void BSDismemberSkinInstance::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiSkinInstance::Write( out, link_map, missing_link_stack, info );
	numPartitions = (int)(partitions.size());
	NifStream( numPartitions, out, info );
	for (unsigned int i1 = 0; i1 < partitions.size(); i1++) {
		NifStream( partitions[i1].partFlag, out, info );
		NifStream( partitions[i1].bodyPart, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string BSDismemberSkinInstance::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiSkinInstance::asString();
	numPartitions = (int)(partitions.size());
	out << "  Num Partitions:  " << numPartitions << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < partitions.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Part Flag:  " << partitions[i1].partFlag << endl;
		out << "    Body Part:  " << partitions[i1].bodyPart << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void BSDismemberSkinInstance::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiSkinInstance::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSDismemberSkinInstance::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiSkinInstance::GetRefs();
	return refs;
}

std::list<NiObject *> BSDismemberSkinInstance::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiSkinInstance::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

vector<BodyPartList > BSDismemberSkinInstance::GetPartitions() const {
   return partitions;
}

void BSDismemberSkinInstance::SetPartitions( const vector<BodyPartList >& value ) {
   partitions.clear();
   for(unsigned int i = 0; i < value.size(); i++) {
	   partitions.push_back(value[i]);
   }
}

//--END CUSTOM CODE--//
