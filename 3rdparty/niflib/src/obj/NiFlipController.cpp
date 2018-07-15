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
#include "../../include/obj/NiFlipController.h"
#include "../../include/obj/NiImage.h"
#include "../../include/obj/NiSourceTexture.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiFlipController::TYPE("NiFlipController", &NiFloatInterpController::TYPE );

NiFlipController::NiFlipController() : textureSlot((TexType)0), unknownInt2((unsigned int)0), delta(0.0f), numSources((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiFlipController::~NiFlipController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiFlipController::GetType() const {
	return TYPE;
}

NiObject * NiFlipController::Create() {
	return new NiFlipController;
}

void NiFlipController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiFloatInterpController::Read( in, link_stack, info );
	NifStream( textureSlot, in, info );
	if ( ( info.version >= 0x04000000 ) && ( info.version <= 0x0A010000 ) ) {
		NifStream( unknownInt2, in, info );
	};
	if ( info.version <= 0x0A010000 ) {
		NifStream( delta, in, info );
	};
	NifStream( numSources, in, info );
	if ( info.version >= 0x04000000 ) {
		sources.resize(numSources);
		for (unsigned int i2 = 0; i2 < sources.size(); i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
	};
	if ( info.version <= 0x03010000 ) {
		images.resize(numSources);
		for (unsigned int i2 = 0; i2 < images.size(); i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiFlipController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiFloatInterpController::Write( out, link_map, missing_link_stack, info );
	numSources = (unsigned int)(sources.size());
	NifStream( textureSlot, out, info );
	if ( ( info.version >= 0x04000000 ) && ( info.version <= 0x0A010000 ) ) {
		NifStream( unknownInt2, out, info );
	};
	if ( info.version <= 0x0A010000 ) {
		NifStream( delta, out, info );
	};
	NifStream( numSources, out, info );
	if ( info.version >= 0x04000000 ) {
		for (unsigned int i2 = 0; i2 < sources.size(); i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*sources[i2]), out );
			} else {
				if ( sources[i2] != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(sources[i2]) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( sources[i2] );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
	};
	if ( info.version <= 0x03010000 ) {
		for (unsigned int i2 = 0; i2 < images.size(); i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*images[i2]), out );
			} else {
				if ( images[i2] != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(images[i2]) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( images[i2] );
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

std::string NiFlipController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiFloatInterpController::asString();
	numSources = (unsigned int)(sources.size());
	out << "  Texture Slot:  " << textureSlot << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	out << "  Delta:  " << delta << endl;
	out << "  Num Sources:  " << numSources << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < sources.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Sources[" << i1 << "]:  " << sources[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < images.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Images[" << i1 << "]:  " << images[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiFlipController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiFloatInterpController::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( info.version >= 0x04000000 ) {
		for (unsigned int i2 = 0; i2 < sources.size(); i2++) {
			sources[i2] = FixLink<NiSourceTexture>( objects, link_stack, missing_link_stack, info );
		};
	};
	if ( info.version <= 0x03010000 ) {
		for (unsigned int i2 = 0; i2 < images.size(); i2++) {
			images[i2] = FixLink<NiImage>( objects, link_stack, missing_link_stack, info );
		};
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiFlipController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiFloatInterpController::GetRefs();
	for (unsigned int i1 = 0; i1 < sources.size(); i1++) {
		if ( sources[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(sources[i1]));
	};
	for (unsigned int i1 = 0; i1 < images.size(); i1++) {
		if ( images[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(images[i1]));
	};
	return refs;
}

std::list<NiObject *> NiFlipController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiFloatInterpController::GetPtrs();
	for (unsigned int i1 = 0; i1 < sources.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < images.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
