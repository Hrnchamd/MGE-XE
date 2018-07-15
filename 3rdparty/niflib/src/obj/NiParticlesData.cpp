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
#include "../../include/obj/NiParticlesData.h"
#include "../../include/obj/NiObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiParticlesData::TYPE("NiParticlesData", &NiGeometryData::TYPE );

NiParticlesData::NiParticlesData() : numParticles((unsigned short)0), particleRadius(0.0f), hasRadii(false), numActive((unsigned short)0), hasSizes(false), hasRotations(false), unknownByte1((byte)0), unknownLink(NULL), hasRotationAngles(false), hasRotationAxes(false), hasUvQuadrants(false), numUvQuadrants((byte)0), unknownByte2((byte)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiParticlesData::~NiParticlesData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiParticlesData::GetType() const {
	return TYPE;
}

NiObject * NiParticlesData::Create() {
	return new NiParticlesData;
}

void NiParticlesData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiGeometryData::Read( in, link_stack, info );
	if ( info.version <= 0x04000002 ) {
		NifStream( numParticles, in, info );
	};
	if ( info.version <= 0x0A000100 ) {
		NifStream( particleRadius, in, info );
	};
	if ( info.version >= 0x0A010000 ) {
		NifStream( hasRadii, in, info );
	};
	if ( ( info.version >= 0x0A010000 ) && ( (!((info.version >= 0x14020007) && (info.userVersion >= 11))) ) ) {
		if ( hasRadii ) {
			radii.resize(numVertices);
			for (unsigned int i3 = 0; i3 < radii.size(); i3++) {
				NifStream( radii[i3], in, info );
			};
		};
	};
	NifStream( numActive, in, info );
	NifStream( hasSizes, in, info );
	if ( (!((info.version >= 0x14020007) && (info.userVersion >= 11))) ) {
		if ( hasSizes ) {
			sizes.resize(numVertices);
			for (unsigned int i3 = 0; i3 < sizes.size(); i3++) {
				NifStream( sizes[i3], in, info );
			};
		};
	};
	if ( info.version >= 0x0A000100 ) {
		NifStream( hasRotations, in, info );
	};
	if ( ( info.version >= 0x0A000100 ) && ( (!((info.version >= 0x14020007) && (info.userVersion >= 11))) ) ) {
		if ( hasRotations ) {
			rotations.resize(numVertices);
			for (unsigned int i3 = 0; i3 < rotations.size(); i3++) {
				NifStream( rotations[i3], in, info );
			};
		};
	};
	if ( ((info.version >= 0x14020007) && (info.userVersion >= 12)) ) {
		NifStream( unknownByte1, in, info );
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	if ( info.version >= 0x14000004 ) {
		NifStream( hasRotationAngles, in, info );
	};
	if ( (!((info.version >= 0x14020007) && (info.userVersion >= 11))) ) {
		if ( hasRotationAngles ) {
			rotationAngles.resize(numVertices);
			for (unsigned int i3 = 0; i3 < rotationAngles.size(); i3++) {
				NifStream( rotationAngles[i3], in, info );
			};
		};
	};
	if ( info.version >= 0x14000004 ) {
		NifStream( hasRotationAxes, in, info );
	};
	if ( ( info.version >= 0x14000004 ) && ( (!((info.version >= 0x14020007) && (info.userVersion >= 11))) ) ) {
		if ( hasRotationAxes ) {
			rotationAxes.resize(numVertices);
			for (unsigned int i3 = 0; i3 < rotationAxes.size(); i3++) {
				NifStream( rotationAxes[i3], in, info );
			};
		};
	};
	if ( ((info.version >= 0x14020007) && (info.userVersion == 11)) ) {
		NifStream( hasUvQuadrants, in, info );
		NifStream( numUvQuadrants, in, info );
		if ( hasUvQuadrants ) {
			uvQuadrants.resize(numUvQuadrants);
			for (unsigned int i3 = 0; i3 < uvQuadrants.size(); i3++) {
				NifStream( uvQuadrants[i3], in, info );
			};
		};
	};
	if ( ((info.version == 0x14020007) && (info.userVersion >= 11)) ) {
		NifStream( unknownByte2, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiParticlesData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiGeometryData::Write( out, link_map, missing_link_stack, info );
	numUvQuadrants = (byte)(uvQuadrants.size());
	if ( info.version <= 0x04000002 ) {
		NifStream( numParticles, out, info );
	};
	if ( info.version <= 0x0A000100 ) {
		NifStream( particleRadius, out, info );
	};
	if ( info.version >= 0x0A010000 ) {
		NifStream( hasRadii, out, info );
	};
	if ( ( info.version >= 0x0A010000 ) && ( (!((info.version >= 0x14020007) && (info.userVersion >= 11))) ) ) {
		if ( hasRadii ) {
			for (unsigned int i3 = 0; i3 < radii.size(); i3++) {
				NifStream( radii[i3], out, info );
			};
		};
	};
	NifStream( numActive, out, info );
	NifStream( hasSizes, out, info );
	if ( (!((info.version >= 0x14020007) && (info.userVersion >= 11))) ) {
		if ( hasSizes ) {
			for (unsigned int i3 = 0; i3 < sizes.size(); i3++) {
				NifStream( sizes[i3], out, info );
			};
		};
	};
	if ( info.version >= 0x0A000100 ) {
		NifStream( hasRotations, out, info );
	};
	if ( ( info.version >= 0x0A000100 ) && ( (!((info.version >= 0x14020007) && (info.userVersion >= 11))) ) ) {
		if ( hasRotations ) {
			for (unsigned int i3 = 0; i3 < rotations.size(); i3++) {
				NifStream( rotations[i3], out, info );
			};
		};
	};
	if ( ((info.version >= 0x14020007) && (info.userVersion >= 12)) ) {
		NifStream( unknownByte1, out, info );
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
	if ( info.version >= 0x14000004 ) {
		NifStream( hasRotationAngles, out, info );
	};
	if ( (!((info.version >= 0x14020007) && (info.userVersion >= 11))) ) {
		if ( hasRotationAngles ) {
			for (unsigned int i3 = 0; i3 < rotationAngles.size(); i3++) {
				NifStream( rotationAngles[i3], out, info );
			};
		};
	};
	if ( info.version >= 0x14000004 ) {
		NifStream( hasRotationAxes, out, info );
	};
	if ( ( info.version >= 0x14000004 ) && ( (!((info.version >= 0x14020007) && (info.userVersion >= 11))) ) ) {
		if ( hasRotationAxes ) {
			for (unsigned int i3 = 0; i3 < rotationAxes.size(); i3++) {
				NifStream( rotationAxes[i3], out, info );
			};
		};
	};
	if ( ((info.version >= 0x14020007) && (info.userVersion == 11)) ) {
		NifStream( hasUvQuadrants, out, info );
		NifStream( numUvQuadrants, out, info );
		if ( hasUvQuadrants ) {
			for (unsigned int i3 = 0; i3 < uvQuadrants.size(); i3++) {
				NifStream( uvQuadrants[i3], out, info );
			};
		};
	};
	if ( ((info.version == 0x14020007) && (info.userVersion >= 11)) ) {
		NifStream( unknownByte2, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiParticlesData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiGeometryData::asString();
	numUvQuadrants = (byte)(uvQuadrants.size());
	out << "  Num Particles:  " << numParticles << endl;
	out << "  Particle Radius:  " << particleRadius << endl;
	out << "  Has Radii:  " << hasRadii << endl;
	if ( hasRadii ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < radii.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Radii[" << i2 << "]:  " << radii[i2] << endl;
			array_output_count++;
		};
	};
	out << "  Num Active:  " << numActive << endl;
	out << "  Has Sizes:  " << hasSizes << endl;
	if ( hasSizes ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < sizes.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Sizes[" << i2 << "]:  " << sizes[i2] << endl;
			array_output_count++;
		};
	};
	out << "  Has Rotations:  " << hasRotations << endl;
	if ( hasRotations ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < rotations.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Rotations[" << i2 << "]:  " << rotations[i2] << endl;
			array_output_count++;
		};
	};
	out << "  Unknown Byte 1:  " << unknownByte1 << endl;
	out << "  Unknown Link:  " << unknownLink << endl;
	out << "  Has Rotation Angles:  " << hasRotationAngles << endl;
	if ( hasRotationAngles ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < rotationAngles.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Rotation Angles[" << i2 << "]:  " << rotationAngles[i2] << endl;
			array_output_count++;
		};
	};
	out << "  Has Rotation Axes:  " << hasRotationAxes << endl;
	if ( hasRotationAxes ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < rotationAxes.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Rotation Axes[" << i2 << "]:  " << rotationAxes[i2] << endl;
			array_output_count++;
		};
	};
	out << "  Has UV Quadrants:  " << hasUvQuadrants << endl;
	out << "  Num UV Quadrants:  " << numUvQuadrants << endl;
	if ( hasUvQuadrants ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < uvQuadrants.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      UV Quadrants[" << i2 << "]:  " << uvQuadrants[i2] << endl;
			array_output_count++;
		};
	};
	out << "  Unknown Byte 2:  " << unknownByte2 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiParticlesData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiGeometryData::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( ((info.version >= 0x14020007) && (info.userVersion >= 12)) ) {
		unknownLink = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiParticlesData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiGeometryData::GetRefs();
	if ( unknownLink != NULL )
		refs.push_back(StaticCast<NiObject>(unknownLink));
	return refs;
}

std::list<NiObject *> NiParticlesData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiGeometryData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
//--END CUSTOM CODE--//
