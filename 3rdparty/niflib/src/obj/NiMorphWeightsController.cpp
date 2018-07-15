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
#include "../../include/obj/NiMorphWeightsController.h"
#include "../../include/obj/NiObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiMorphWeightsController::TYPE("NiMorphWeightsController", &NiInterpController::TYPE );

NiMorphWeightsController::NiMorphWeightsController() : unknown2((int)0), numInterpolators((unsigned int)0), numTargets((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiMorphWeightsController::~NiMorphWeightsController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiMorphWeightsController::GetType() const {
	return TYPE;
}

NiObject * NiMorphWeightsController::Create() {
	return new NiMorphWeightsController;
}

void NiMorphWeightsController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiInterpController::Read( in, link_stack, info );
	NifStream( unknown2, in, info );
	NifStream( numInterpolators, in, info );
	interpolators.resize(numInterpolators);
	for (unsigned int i1 = 0; i1 < interpolators.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( numTargets, in, info );
	targetNames.resize(numTargets);
	for (unsigned int i1 = 0; i1 < targetNames.size(); i1++) {
		NifStream( targetNames[i1], in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiMorphWeightsController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiInterpController::Write( out, link_map, missing_link_stack, info );
	numTargets = (unsigned int)(targetNames.size());
	numInterpolators = (unsigned int)(interpolators.size());
	NifStream( unknown2, out, info );
	NifStream( numInterpolators, out, info );
	for (unsigned int i1 = 0; i1 < interpolators.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*interpolators[i1]), out );
		} else {
			if ( interpolators[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolators[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( interpolators[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( numTargets, out, info );
	for (unsigned int i1 = 0; i1 < targetNames.size(); i1++) {
		NifStream( targetNames[i1], out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiMorphWeightsController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiInterpController::asString();
	numTargets = (unsigned int)(targetNames.size());
	numInterpolators = (unsigned int)(interpolators.size());
	out << "  Unknown 2:  " << unknown2 << endl;
	out << "  Num Interpolators:  " << numInterpolators << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < interpolators.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Interpolators[" << i1 << "]:  " << interpolators[i1] << endl;
		array_output_count++;
	};
	out << "  Num Targets:  " << numTargets << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < targetNames.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Target Names[" << i1 << "]:  " << targetNames[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiMorphWeightsController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiInterpController::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < interpolators.size(); i1++) {
		interpolators[i1] = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiMorphWeightsController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiInterpController::GetRefs();
	for (unsigned int i1 = 0; i1 < interpolators.size(); i1++) {
		if ( interpolators[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(interpolators[i1]));
	};
	return refs;
}

std::list<NiObject *> NiMorphWeightsController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiInterpController::GetPtrs();
	for (unsigned int i1 = 0; i1 < interpolators.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
