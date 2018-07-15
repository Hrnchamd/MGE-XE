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
#include "../../include/obj/NiParticleSystemController.h"
#include "../../include/gen/Particle.h"
#include "../../include/obj/NiColorData.h"
#include "../../include/obj/NiObject.h"
#include "../../include/obj/NiParticleModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiParticleSystemController::TYPE("NiParticleSystemController", &NiTimeController::TYPE );

NiParticleSystemController::NiParticleSystemController() : oldSpeed((unsigned int)0), speed(0.0f), speedRandom(0.0f), verticalDirection(0.0f), verticalAngle(0.0f), horizontalDirection(0.0f), horizontalAngle(0.0f), size(0.0f), emitStartTime(0.0f), emitStopTime(0.0f), unknownByte((byte)0), oldEmitRate((unsigned int)0), emitRate(0.0f), lifetime(0.0f), lifetimeRandom(0.0f), emitFlags((unsigned short)0), emitter(NULL), unknownShort2_((unsigned short)0), unknownFloat13_(0.0f), unknownInt1_((unsigned int)0), unknownInt2_((unsigned int)0), unknownShort3_((unsigned short)0), particleLifetime(0.0f), particleLink(NULL), particleTimestamp((unsigned int)0), particleUnknownShort((unsigned short)0), particleVertexId((unsigned short)0), numParticles((unsigned short)0), numValid((unsigned short)0), unknownLink(NULL), particleExtra(NULL), unknownLink2(NULL), trailer((byte)0), colorData(NULL), unknownFloat1(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiParticleSystemController::~NiParticleSystemController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiParticleSystemController::GetType() const {
	return TYPE;
}

NiObject * NiParticleSystemController::Create() {
	return new NiParticleSystemController;
}

void NiParticleSystemController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiTimeController::Read( in, link_stack, info );
	if ( info.version <= 0x03010000 ) {
		NifStream( oldSpeed, in, info );
	};
	if ( info.version >= 0x0303000D ) {
		NifStream( speed, in, info );
	};
	NifStream( speedRandom, in, info );
	NifStream( verticalDirection, in, info );
	NifStream( verticalAngle, in, info );
	NifStream( horizontalDirection, in, info );
	NifStream( horizontalAngle, in, info );
	NifStream( unknownNormal_, in, info );
	NifStream( unknownColor_, in, info );
	NifStream( size, in, info );
	NifStream( emitStartTime, in, info );
	NifStream( emitStopTime, in, info );
	if ( info.version >= 0x04000002 ) {
		NifStream( unknownByte, in, info );
	};
	if ( info.version <= 0x03010000 ) {
		NifStream( oldEmitRate, in, info );
	};
	if ( info.version >= 0x0303000D ) {
		NifStream( emitRate, in, info );
	};
	NifStream( lifetime, in, info );
	NifStream( lifetimeRandom, in, info );
	if ( info.version >= 0x04000002 ) {
		NifStream( emitFlags, in, info );
	};
	NifStream( startRandom, in, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	if ( info.version >= 0x04000002 ) {
		NifStream( unknownShort2_, in, info );
		NifStream( unknownFloat13_, in, info );
		NifStream( unknownInt1_, in, info );
		NifStream( unknownInt2_, in, info );
		NifStream( unknownShort3_, in, info );
	};
	if ( info.version <= 0x03010000 ) {
		NifStream( particleVelocity, in, info );
		NifStream( particleUnknownVector, in, info );
		NifStream( particleLifetime, in, info );
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		NifStream( particleTimestamp, in, info );
		NifStream( particleUnknownShort, in, info );
		NifStream( particleVertexId, in, info );
	};
	if ( info.version >= 0x04000002 ) {
		NifStream( numParticles, in, info );
		NifStream( numValid, in, info );
		particles.resize(numParticles);
		for (unsigned int i2 = 0; i2 < particles.size(); i2++) {
			NifStream( particles[i2].velocity, in, info );
			NifStream( particles[i2].unknownVector, in, info );
			NifStream( particles[i2].lifetime, in, info );
			NifStream( particles[i2].lifespan, in, info );
			NifStream( particles[i2].timestamp, in, info );
			NifStream( particles[i2].unknownShort, in, info );
			NifStream( particles[i2].vertexId, in, info );
		};
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	if ( info.version >= 0x04000002 ) {
		NifStream( trailer, in, info );
	};
	if ( info.version <= 0x03010000 ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		NifStream( unknownFloat1, in, info );
		unknownFloats2.resize(particleUnknownShort);
		for (unsigned int i2 = 0; i2 < unknownFloats2.size(); i2++) {
			NifStream( unknownFloats2[i2], in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiParticleSystemController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTimeController::Write( out, link_map, missing_link_stack, info );
	numParticles = (unsigned short)(particles.size());
	particleUnknownShort = (unsigned short)(unknownFloats2.size());
	if ( info.version <= 0x03010000 ) {
		NifStream( oldSpeed, out, info );
	};
	if ( info.version >= 0x0303000D ) {
		NifStream( speed, out, info );
	};
	NifStream( speedRandom, out, info );
	NifStream( verticalDirection, out, info );
	NifStream( verticalAngle, out, info );
	NifStream( horizontalDirection, out, info );
	NifStream( horizontalAngle, out, info );
	NifStream( unknownNormal_, out, info );
	NifStream( unknownColor_, out, info );
	NifStream( size, out, info );
	NifStream( emitStartTime, out, info );
	NifStream( emitStopTime, out, info );
	if ( info.version >= 0x04000002 ) {
		NifStream( unknownByte, out, info );
	};
	if ( info.version <= 0x03010000 ) {
		NifStream( oldEmitRate, out, info );
	};
	if ( info.version >= 0x0303000D ) {
		NifStream( emitRate, out, info );
	};
	NifStream( lifetime, out, info );
	NifStream( lifetimeRandom, out, info );
	if ( info.version >= 0x04000002 ) {
		NifStream( emitFlags, out, info );
	};
	NifStream( startRandom, out, info );
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
	if ( info.version >= 0x04000002 ) {
		NifStream( unknownShort2_, out, info );
		NifStream( unknownFloat13_, out, info );
		NifStream( unknownInt1_, out, info );
		NifStream( unknownInt2_, out, info );
		NifStream( unknownShort3_, out, info );
	};
	if ( info.version <= 0x03010000 ) {
		NifStream( particleVelocity, out, info );
		NifStream( particleUnknownVector, out, info );
		NifStream( particleLifetime, out, info );
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*particleLink), out );
		} else {
			if ( particleLink != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(particleLink) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( particleLink );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		NifStream( particleTimestamp, out, info );
		NifStream( particleUnknownShort, out, info );
		NifStream( particleVertexId, out, info );
	};
	if ( info.version >= 0x04000002 ) {
		NifStream( numParticles, out, info );
		NifStream( numValid, out, info );
		for (unsigned int i2 = 0; i2 < particles.size(); i2++) {
			NifStream( particles[i2].velocity, out, info );
			NifStream( particles[i2].unknownVector, out, info );
			NifStream( particles[i2].lifetime, out, info );
			NifStream( particles[i2].lifespan, out, info );
			NifStream( particles[i2].timestamp, out, info );
			NifStream( particles[i2].unknownShort, out, info );
			NifStream( particles[i2].vertexId, out, info );
		};
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*unknownLink), out );
		} else {
			if ( unknownLink != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(unknownLink) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( unknownLink );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*particleExtra), out );
	} else {
		if ( particleExtra != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(particleExtra) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( particleExtra );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*unknownLink2), out );
	} else {
		if ( unknownLink2 != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(unknownLink2) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( unknownLink2 );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( info.version >= 0x04000002 ) {
		NifStream( trailer, out, info );
	};
	if ( info.version <= 0x03010000 ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*colorData), out );
		} else {
			if ( colorData != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(colorData) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( colorData );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		NifStream( unknownFloat1, out, info );
		for (unsigned int i2 = 0; i2 < unknownFloats2.size(); i2++) {
			NifStream( unknownFloats2[i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiParticleSystemController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiTimeController::asString();
	numParticles = (unsigned short)(particles.size());
	particleUnknownShort = (unsigned short)(unknownFloats2.size());
	out << "  Old Speed:  " << oldSpeed << endl;
	out << "  Speed:  " << speed << endl;
	out << "  Speed Random:  " << speedRandom << endl;
	out << "  Vertical Direction:  " << verticalDirection << endl;
	out << "  Vertical Angle:  " << verticalAngle << endl;
	out << "  Horizontal Direction:  " << horizontalDirection << endl;
	out << "  Horizontal Angle:  " << horizontalAngle << endl;
	out << "  Unknown Normal?:  " << unknownNormal_ << endl;
	out << "  Unknown Color?:  " << unknownColor_ << endl;
	out << "  Size:  " << size << endl;
	out << "  Emit Start Time:  " << emitStartTime << endl;
	out << "  Emit Stop Time:  " << emitStopTime << endl;
	out << "  Unknown Byte:  " << unknownByte << endl;
	out << "  Old Emit Rate:  " << oldEmitRate << endl;
	out << "  Emit Rate:  " << emitRate << endl;
	out << "  Lifetime:  " << lifetime << endl;
	out << "  Lifetime Random:  " << lifetimeRandom << endl;
	out << "  Emit Flags:  " << emitFlags << endl;
	out << "  Start Random:  " << startRandom << endl;
	out << "  Emitter:  " << emitter << endl;
	out << "  Unknown Short 2?:  " << unknownShort2_ << endl;
	out << "  Unknown Float 13?:  " << unknownFloat13_ << endl;
	out << "  Unknown Int 1?:  " << unknownInt1_ << endl;
	out << "  Unknown Int 2?:  " << unknownInt2_ << endl;
	out << "  Unknown Short 3?:  " << unknownShort3_ << endl;
	out << "  Particle Velocity:  " << particleVelocity << endl;
	out << "  Particle Unknown Vector:  " << particleUnknownVector << endl;
	out << "  Particle Lifetime:  " << particleLifetime << endl;
	out << "  Particle Link:  " << particleLink << endl;
	out << "  Particle Timestamp:  " << particleTimestamp << endl;
	out << "  Particle Unknown Short:  " << particleUnknownShort << endl;
	out << "  Particle Vertex Id:  " << particleVertexId << endl;
	out << "  Num Particles:  " << numParticles << endl;
	out << "  Num Valid:  " << numValid << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < particles.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Velocity:  " << particles[i1].velocity << endl;
		out << "    Unknown Vector:  " << particles[i1].unknownVector << endl;
		out << "    Lifetime:  " << particles[i1].lifetime << endl;
		out << "    Lifespan:  " << particles[i1].lifespan << endl;
		out << "    Timestamp:  " << particles[i1].timestamp << endl;
		out << "    Unknown Short:  " << particles[i1].unknownShort << endl;
		out << "    Vertex ID:  " << particles[i1].vertexId << endl;
	};
	out << "  Unknown Link:  " << unknownLink << endl;
	out << "  Particle Extra:  " << particleExtra << endl;
	out << "  Unknown Link 2:  " << unknownLink2 << endl;
	out << "  Trailer:  " << trailer << endl;
	out << "  Color Data:  " << colorData << endl;
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknownFloats2.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Floats 2[" << i1 << "]:  " << unknownFloats2[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiParticleSystemController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTimeController::FixLinks( objects, link_stack, missing_link_stack, info );
	emitter = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	if ( info.version <= 0x03010000 ) {
		particleLink = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	};
	if ( info.version >= 0x04000002 ) {
		unknownLink = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	};
	particleExtra = FixLink<NiParticleModifier>( objects, link_stack, missing_link_stack, info );
	unknownLink2 = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	if ( info.version <= 0x03010000 ) {
		colorData = FixLink<NiColorData>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiParticleSystemController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiTimeController::GetRefs();
	if ( particleLink != NULL )
		refs.push_back(StaticCast<NiObject>(particleLink));
	if ( unknownLink != NULL )
		refs.push_back(StaticCast<NiObject>(unknownLink));
	if ( particleExtra != NULL )
		refs.push_back(StaticCast<NiObject>(particleExtra));
	if ( unknownLink2 != NULL )
		refs.push_back(StaticCast<NiObject>(unknownLink2));
	if ( colorData != NULL )
		refs.push_back(StaticCast<NiObject>(colorData));
	return refs;
}

std::list<NiObject *> NiParticleSystemController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiTimeController::GetPtrs();
	if ( emitter != NULL )
		ptrs.push_back((NiObject *)(emitter));
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
