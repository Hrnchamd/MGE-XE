/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include <algorithm>
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiMultiTargetTransformController.h"
#include "../../include/obj/NiAVObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiMultiTargetTransformController::TYPE("NiMultiTargetTransformController", &NiInterpController::TYPE );

NiMultiTargetTransformController::NiMultiTargetTransformController() : numExtraTargets((unsigned short)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiMultiTargetTransformController::~NiMultiTargetTransformController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiMultiTargetTransformController::GetType() const {
	return TYPE;
}

NiObject * NiMultiTargetTransformController::Create() {
	return new NiMultiTargetTransformController;
}

void NiMultiTargetTransformController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiInterpController::Read( in, link_stack, info );
	NifStream( numExtraTargets, in, info );
	extraTargets.resize(numExtraTargets);
	for (unsigned int i1 = 0; i1 < extraTargets.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiMultiTargetTransformController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiInterpController::Write( out, link_map, missing_link_stack, info );
	numExtraTargets = (unsigned short)(extraTargets.size());
	NifStream( numExtraTargets, out, info );
	for (unsigned int i1 = 0; i1 < extraTargets.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*extraTargets[i1]), out );
		} else {
			if ( extraTargets[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(extraTargets[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( extraTargets[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiMultiTargetTransformController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiInterpController::asString();
	numExtraTargets = (unsigned short)(extraTargets.size());
	out << "  Num Extra Targets:  " << numExtraTargets << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < extraTargets.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Extra Targets[" << i1 << "]:  " << extraTargets[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiMultiTargetTransformController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiInterpController::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < extraTargets.size(); i1++) {
		extraTargets[i1] = FixLink<NiAVObject>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiMultiTargetTransformController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiInterpController::GetRefs();
	for (unsigned int i1 = 0; i1 < extraTargets.size(); i1++) {
	};
	return refs;
}

std::list<NiObject *> NiMultiTargetTransformController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiInterpController::GetPtrs();
	for (unsigned int i1 = 0; i1 < extraTargets.size(); i1++) {
		if ( extraTargets[i1] != NULL )
			ptrs.push_back((NiObject *)(extraTargets[i1]));
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

vector<NiAVObjectRef> NiMultiTargetTransformController::GetExtraTargets() const {
   vector<NiAVObjectRef> retval;
   size_t n = extraTargets.size();
   retval.reserve(n);
   for (size_t i=0; i<n; ++i)
      retval.push_back( NiAVObjectRef(extraTargets[i]) );
	return retval;
}

void NiMultiTargetTransformController::SetExtraTargets( const vector< Ref<NiAVObject> > & value ) {
   extraTargets.clear();
   size_t n = value.size();
   extraTargets.reserve(n);
   for (size_t i=0; i<n; ++i)
      extraTargets.push_back( value[i] );
   extraTargets.erase(std::remove(extraTargets.begin(), extraTargets.end(), (NiAVObject*)NULL), extraTargets.end());
}

bool NiMultiTargetTransformController::AddExtraTarget( NiAVObject *target ) {
  vector<NiAVObject *>& targets = extraTargets;
  vector<NiAVObject *>::iterator itr = std::find(targets.begin(), targets.end(), target);
  if (itr == targets.end()) {
    targets.push_back(target);
    numExtraTargets++;

    return true;
  }

  return false;
}

bool NiMultiTargetTransformController::RemoveExtraTarget( NiAVObject *target ) {
  vector<NiAVObject *>& targets = extraTargets;
  vector<NiAVObject *>::iterator itr = std::find(targets.begin(), targets.end(), target);
  if (itr == targets.end()) {
    targets.erase(itr);
    numExtraTargets--;

    return true;
  }

  return false;
}

bool NiMultiTargetTransformController::ReplaceExtraTarget( NiAVObject *newtarget, NiAVObject *oldtarget ) {
  vector<NiAVObject *>& targets = extraTargets;
  vector<NiAVObject *>::iterator itr = std::find(targets.begin(), targets.end(), oldtarget);
  if (itr != targets.end()) {
    *itr = newtarget;

    return true;
  }

  return false;
}


//--END CUSTOM CODE--//
