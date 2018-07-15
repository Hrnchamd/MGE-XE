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
#include "../../include/obj/bhkMoppBvTreeShape.h"
#include "../../include/obj/bhkShape.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkMoppBvTreeShape::TYPE("bhkMoppBvTreeShape", &bhkBvTreeShape::TYPE );

bhkMoppBvTreeShape::bhkMoppBvTreeShape() : shape(NULL), material((HavokMaterial)0), skyrimMaterial((SkyrimHavokMaterial)0), unknownFloat(1.0f), moppDataSize((unsigned int)0), scale(0.0f), unknownByte1((byte)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkMoppBvTreeShape::~bhkMoppBvTreeShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkMoppBvTreeShape::GetType() const {
	return TYPE;
}

NiObject * bhkMoppBvTreeShape::Create() {
	return new bhkMoppBvTreeShape;
}

void bhkMoppBvTreeShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	bhkBvTreeShape::Read( in, link_stack, info );
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	if ( (info.userVersion < 12) ) {
		NifStream( material, in, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( skyrimMaterial, in, info );
	};
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( unknown8Bytes[i1], in, info );
	};
	NifStream( unknownFloat, in, info );
	NifStream( moppDataSize, in, info );
	NifStream( origin, in, info );
	NifStream( scale, in, info );
	if ( info.version <= 0x0A000100 ) {
		oldMoppData.resize((moppDataSize - 1));
		for (unsigned int i2 = 0; i2 < oldMoppData.size(); i2++) {
			NifStream( oldMoppData[i2], in, info );
		};
	};
	if ( info.version >= 0x0A000102 ) {
		moppData.resize(moppDataSize);
		for (unsigned int i2 = 0; i2 < moppData.size(); i2++) {
			NifStream( moppData[i2], in, info );
		};
	};
	if ( ( info.version >= 0x14020007 ) && ( (info.userVersion >= 12) ) ) {
		NifStream( unknownByte1, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkMoppBvTreeShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkBvTreeShape::Write( out, link_map, missing_link_stack, info );
	moppDataSize = moppDataSizeCalc(info);
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*shape), out );
	} else {
		if ( shape != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(shape) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( shape );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	if ( (info.userVersion < 12) ) {
		NifStream( material, out, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( skyrimMaterial, out, info );
	};
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		NifStream( unknown8Bytes[i1], out, info );
	};
	NifStream( unknownFloat, out, info );
	NifStream( moppDataSize, out, info );
	NifStream( origin, out, info );
	NifStream( scale, out, info );
	if ( info.version <= 0x0A000100 ) {
		for (unsigned int i2 = 0; i2 < oldMoppData.size(); i2++) {
			NifStream( oldMoppData[i2], out, info );
		};
	};
	if ( info.version >= 0x0A000102 ) {
		for (unsigned int i2 = 0; i2 < moppData.size(); i2++) {
			NifStream( moppData[i2], out, info );
		};
	};
	if ( ( info.version >= 0x14020007 ) && ( (info.userVersion >= 12) ) ) {
		NifStream( unknownByte1, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkMoppBvTreeShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkBvTreeShape::asString();
	out << "  Shape:  " << shape << endl;
	out << "  Material:  " << material << endl;
	out << "  Skyrim Material:  " << skyrimMaterial << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 8; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 8 Bytes[" << i1 << "]:  " << unknown8Bytes[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Float:  " << unknownFloat << endl;
	out << "  MOPP Data Size:  " << moppDataSize << endl;
	out << "  Origin:  " << origin << endl;
	out << "  Scale:  " << scale << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < oldMoppData.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Old MOPP Data[" << i1 << "]:  " << oldMoppData[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < moppData.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    MOPP Data[" << i1 << "]:  " << moppData[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Byte 1:  " << unknownByte1 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkMoppBvTreeShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkBvTreeShape::FixLinks( objects, link_stack, missing_link_stack, info );
	shape = FixLink<bhkShape>( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkMoppBvTreeShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkBvTreeShape::GetRefs();
	if ( shape != NULL )
		refs.push_back(StaticCast<NiObject>(shape));
	return refs;
}

std::list<NiObject *> bhkMoppBvTreeShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkBvTreeShape::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Ref<bhkShape > bhkMoppBvTreeShape::GetShape() const {
	return shape;
}

void bhkMoppBvTreeShape::SetShape( bhkShape * value ) {
	shape = value;
}

HavokMaterial bhkMoppBvTreeShape::GetMaterial() const {
	return material;
}

void bhkMoppBvTreeShape::SetMaterial( HavokMaterial value ) {
	material = value;
}

vector<byte> bhkMoppBvTreeShape::GetMoppCode() const {
	return moppData;
}

void bhkMoppBvTreeShape::SetMoppCode( vector<byte> & value ) {
	moppDataSize = value.size();
	moppData = value;
}

Vector3 bhkMoppBvTreeShape::GetMoppOrigin() const {
	return origin;
}

void bhkMoppBvTreeShape::SetMoppOrigin( Vector3 value ) {
	origin = value;
}

float bhkMoppBvTreeShape::GetMoppScale() const {
	return scale;
}

void bhkMoppBvTreeShape::SetMoppScale( float value ) {
	scale = value;
}

void bhkMoppBvTreeShape::CalcMassProperties( float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia )
{
	center = Vector3(0,0,0);
	mass = 0.0f, volume = 0.0f;
	inertia = InertiaMatrix::IDENTITY;

	if (shape != NULL)
		shape->CalcMassProperties(density, solid, mass, volume, center, inertia);
}

//--END CUSTOM CODE--//
