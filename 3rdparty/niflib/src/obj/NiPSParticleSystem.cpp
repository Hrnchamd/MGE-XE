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
#include "../../include/obj/NiPSParticleSystem.h"
#include "../../include/obj/NiObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSParticleSystem::TYPE("NiPSParticleSystem", &NiAVObject::TYPE );

NiPSParticleSystem::NiPSParticleSystem() : unknown3((int)0), unknown4((int)0), unknown5((int)0), unknown6((int)0), unknown7((int)0), unknown8((int)0), unknown9((int)0), unknown10(0.0f), unknown11((int)0), unknown12((int)0), simulator(NULL), generator(NULL), unknown15((int)0), unknown16((int)0), unknown17((int)0), emitter(NULL), unknown19((int)0), unknown20((int)0), unknown21((int)0), unknown27((int)0), unknown28((int)0), unknown29((int)0), unknown30((int)0), unknown31((int)0), unknown32((int)0), unknown33((int)0), unknown34((int)0), unknown35((byte)0), unknown36((int)0), unknown37((short)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSParticleSystem::~NiPSParticleSystem() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSParticleSystem::GetType() const {
	return TYPE;
}

NiObject * NiPSParticleSystem::Create() {
	return new NiPSParticleSystem;
}

void NiPSParticleSystem::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiAVObject::Read( in, link_stack, info );
	NifStream( unknown3, in, info );
	unknown38.resize(unknown3);
	for (unsigned int i1 = 0; i1 < unknown38.size(); i1++) {
		NifStream( unknown38[i1], in, info );
	};
	NifStream( unknown4, in, info );
	NifStream( unknown5, in, info );
	unknown39.resize(unknown3);
	for (unsigned int i1 = 0; i1 < unknown39.size(); i1++) {
		NifStream( unknown39[i1], in, info );
	};
	NifStream( unknown6, in, info );
	NifStream( unknown7, in, info );
	NifStream( unknown8, in, info );
	NifStream( unknown9, in, info );
	NifStream( unknown10, in, info );
	NifStream( unknown11, in, info );
	NifStream( unknown12, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	if ( (unknown12 > 1) ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( unknown15, in, info );
	NifStream( unknown16, in, info );
	NifStream( unknown17, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( unknown19, in, info );
	NifStream( unknown20, in, info );
	NifStream( unknown21, in, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknown22[i1], in, info );
	};
	if ( info.version >= 0x1E000002 ) {
		NifStream( unknown27, in, info );
		NifStream( unknown28, in, info );
		NifStream( unknown29, in, info );
		NifStream( unknown30, in, info );
		NifStream( unknown31, in, info );
		NifStream( unknown32, in, info );
		NifStream( unknown33, in, info );
		NifStream( unknown34, in, info );
		NifStream( unknown35, in, info );
		NifStream( unknown36, in, info );
		NifStream( unknown37, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSParticleSystem::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiAVObject::Write( out, link_map, missing_link_stack, info );
	unknown3 = (int)(unknown38.size());
	NifStream( unknown3, out, info );
	for (unsigned int i1 = 0; i1 < unknown38.size(); i1++) {
		NifStream( unknown38[i1], out, info );
	};
	NifStream( unknown4, out, info );
	NifStream( unknown5, out, info );
	for (unsigned int i1 = 0; i1 < unknown39.size(); i1++) {
		NifStream( unknown39[i1], out, info );
	};
	NifStream( unknown6, out, info );
	NifStream( unknown7, out, info );
	NifStream( unknown8, out, info );
	NifStream( unknown9, out, info );
	NifStream( unknown10, out, info );
	NifStream( unknown11, out, info );
	NifStream( unknown12, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*simulator), out );
	} else {
		if ( simulator != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(simulator) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( simulator );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( (unknown12 > 1) ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*generator), out );
		} else {
			if ( generator != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(generator) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( generator );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( unknown15, out, info );
	NifStream( unknown16, out, info );
	NifStream( unknown17, out, info );
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*emitter), out );
	} else {
		if ( emitter != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(emitter) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( emitter );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	NifStream( unknown19, out, info );
	NifStream( unknown20, out, info );
	NifStream( unknown21, out, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknown22[i1], out, info );
	};
	if ( info.version >= 0x1E000002 ) {
		NifStream( unknown27, out, info );
		NifStream( unknown28, out, info );
		NifStream( unknown29, out, info );
		NifStream( unknown30, out, info );
		NifStream( unknown31, out, info );
		NifStream( unknown32, out, info );
		NifStream( unknown33, out, info );
		NifStream( unknown34, out, info );
		NifStream( unknown35, out, info );
		NifStream( unknown36, out, info );
		NifStream( unknown37, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSParticleSystem::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiAVObject::asString();
	unknown3 = (int)(unknown38.size());
	out << "  Unknown 3:  " << unknown3 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknown38.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 38[" << i1 << "]:  " << unknown38[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown 4:  " << unknown4 << endl;
	out << "  Unknown 5:  " << unknown5 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknown39.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 39[" << i1 << "]:  " << unknown39[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown 6:  " << unknown6 << endl;
	out << "  Unknown 7:  " << unknown7 << endl;
	out << "  Unknown 8:  " << unknown8 << endl;
	out << "  Unknown 9:  " << unknown9 << endl;
	out << "  Unknown 10:  " << unknown10 << endl;
	out << "  Unknown 11:  " << unknown11 << endl;
	out << "  Unknown 12:  " << unknown12 << endl;
	out << "  Simulator:  " << simulator << endl;
	if ( (unknown12 > 1) ) {
		out << "    Generator:  " << generator << endl;
	};
	out << "  Unknown 15:  " << unknown15 << endl;
	out << "  Unknown 16:  " << unknown16 << endl;
	out << "  Unknown 17:  " << unknown17 << endl;
	out << "  Emitter:  " << emitter << endl;
	out << "  Unknown 19:  " << unknown19 << endl;
	out << "  Unknown 20:  " << unknown20 << endl;
	out << "  Unknown 21:  " << unknown21 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 22[" << i1 << "]:  " << unknown22[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown 27:  " << unknown27 << endl;
	out << "  Unknown 28:  " << unknown28 << endl;
	out << "  Unknown 29:  " << unknown29 << endl;
	out << "  Unknown 30:  " << unknown30 << endl;
	out << "  Unknown 31:  " << unknown31 << endl;
	out << "  Unknown 32:  " << unknown32 << endl;
	out << "  Unknown 33:  " << unknown33 << endl;
	out << "  Unknown 34:  " << unknown34 << endl;
	out << "  Unknown 35:  " << unknown35 << endl;
	out << "  Unknown 36:  " << unknown36 << endl;
	out << "  Unknown 37:  " << unknown37 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSParticleSystem::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiAVObject::FixLinks( objects, link_stack, missing_link_stack, info );
	simulator = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	if ( (unknown12 > 1) ) {
		generator = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	};
	emitter = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSParticleSystem::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiAVObject::GetRefs();
	if ( simulator != NULL )
		refs.push_back(StaticCast<NiObject>(simulator));
	if ( generator != NULL )
		refs.push_back(StaticCast<NiObject>(generator));
	if ( emitter != NULL )
		refs.push_back(StaticCast<NiObject>(emitter));
	return refs;
}

std::list<NiObject *> NiPSParticleSystem::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiAVObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
