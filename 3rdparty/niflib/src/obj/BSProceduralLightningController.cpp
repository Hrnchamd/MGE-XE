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
#include "../../include/obj/BSProceduralLightningController.h"
#include "../../include/obj/NiInterpolator.h"
using namespace Niflib;

//Definition of TYPE constant
const Type BSProceduralLightningController::TYPE("BSProceduralLightningController", &NiFloatInterpController::TYPE );

BSProceduralLightningController::BSProceduralLightningController() : interpolator2_Mutation(NULL), interpolator3(NULL), interpolator4(NULL), interpolator5(NULL), interpolator6(NULL), interpolator7(NULL), interpolator8(NULL), interpolator9_ArcOffset(NULL), unknownShort1((unsigned short)0), unknownShort2((unsigned short)0), unknownShort3((unsigned short)0), distanceWeight(0.0f), float2(0.0f), stripWidth(0.0f), fork(0.0f), float5(0.0f), byte1((byte)0), byte2((byte)0), byte3((byte)0), interpolator10_(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSProceduralLightningController::~BSProceduralLightningController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSProceduralLightningController::GetType() const {
	return TYPE;
}

NiObject * BSProceduralLightningController::Create() {
	return new BSProceduralLightningController;
}

void BSProceduralLightningController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiFloatInterpController::Read( in, link_stack, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( unknownShort1, in, info );
	NifStream( unknownShort2, in, info );
	NifStream( unknownShort3, in, info );
	NifStream( distanceWeight, in, info );
	NifStream( float2, in, info );
	NifStream( stripWidth, in, info );
	NifStream( fork, in, info );
	NifStream( float5, in, info );
	NifStream( byte1, in, info );
	NifStream( byte2, in, info );
	NifStream( byte3, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSProceduralLightningController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiFloatInterpController::Write( out, link_map, missing_link_stack, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*interpolator2_Mutation), out );
	} else {
		if ( interpolator2_Mutation != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolator2_Mutation) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( interpolator2_Mutation );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*interpolator3), out );
	} else {
		if ( interpolator3 != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolator3) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( interpolator3 );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*interpolator4), out );
	} else {
		if ( interpolator4 != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolator4) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( interpolator4 );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*interpolator5), out );
	} else {
		if ( interpolator5 != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolator5) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( interpolator5 );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*interpolator6), out );
	} else {
		if ( interpolator6 != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolator6) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( interpolator6 );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*interpolator7), out );
	} else {
		if ( interpolator7 != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolator7) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( interpolator7 );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*interpolator8), out );
	} else {
		if ( interpolator8 != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolator8) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( interpolator8 );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*interpolator9_ArcOffset), out );
	} else {
		if ( interpolator9_ArcOffset != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolator9_ArcOffset) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( interpolator9_ArcOffset );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	NifStream( unknownShort1, out, info );
	NifStream( unknownShort2, out, info );
	NifStream( unknownShort3, out, info );
	NifStream( distanceWeight, out, info );
	NifStream( float2, out, info );
	NifStream( stripWidth, out, info );
	NifStream( fork, out, info );
	NifStream( float5, out, info );
	NifStream( byte1, out, info );
	NifStream( byte2, out, info );
	NifStream( byte3, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*interpolator10_), out );
	} else {
		if ( interpolator10_ != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolator10_) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( interpolator10_ );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string BSProceduralLightningController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	out << NiFloatInterpController::asString();
	out << "  Interpolator 2: Mutation:  " << interpolator2_Mutation << endl;
	out << "  Interpolator 3:  " << interpolator3 << endl;
	out << "  Interpolator 4:  " << interpolator4 << endl;
	out << "  Interpolator 5:  " << interpolator5 << endl;
	out << "  Interpolator 6:  " << interpolator6 << endl;
	out << "  Interpolator 7:  " << interpolator7 << endl;
	out << "  Interpolator 8:  " << interpolator8 << endl;
	out << "  Interpolator 9: Arc Offset:  " << interpolator9_ArcOffset << endl;
	out << "  Unknown Short 1:  " << unknownShort1 << endl;
	out << "  Unknown Short 2:  " << unknownShort2 << endl;
	out << "  Unknown Short 3:  " << unknownShort3 << endl;
	out << "  Distance Weight:  " << distanceWeight << endl;
	out << "  Float 2:  " << float2 << endl;
	out << "  Strip Width:  " << stripWidth << endl;
	out << "  Fork:  " << fork << endl;
	out << "  Float 5:  " << float5 << endl;
	out << "  Byte 1:  " << byte1 << endl;
	out << "  Byte 2:  " << byte2 << endl;
	out << "  Byte 3:  " << byte3 << endl;
	out << "  Interpolator 10?:  " << interpolator10_ << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void BSProceduralLightningController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiFloatInterpController::FixLinks( objects, link_stack, missing_link_stack, info );
	interpolator2_Mutation = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
	interpolator3 = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
	interpolator4 = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
	interpolator5 = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
	interpolator6 = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
	interpolator7 = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
	interpolator8 = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
	interpolator9_ArcOffset = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
	interpolator10_ = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSProceduralLightningController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiFloatInterpController::GetRefs();
	if ( interpolator2_Mutation != NULL )
		refs.push_back(StaticCast<NiObject>(interpolator2_Mutation));
	if ( interpolator3 != NULL )
		refs.push_back(StaticCast<NiObject>(interpolator3));
	if ( interpolator4 != NULL )
		refs.push_back(StaticCast<NiObject>(interpolator4));
	if ( interpolator5 != NULL )
		refs.push_back(StaticCast<NiObject>(interpolator5));
	if ( interpolator6 != NULL )
		refs.push_back(StaticCast<NiObject>(interpolator6));
	if ( interpolator7 != NULL )
		refs.push_back(StaticCast<NiObject>(interpolator7));
	if ( interpolator8 != NULL )
		refs.push_back(StaticCast<NiObject>(interpolator8));
	if ( interpolator9_ArcOffset != NULL )
		refs.push_back(StaticCast<NiObject>(interpolator9_ArcOffset));
	if ( interpolator10_ != NULL )
		refs.push_back(StaticCast<NiObject>(interpolator10_));
	return refs;
}

std::list<NiObject *> BSProceduralLightningController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiFloatInterpController::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
