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
#include "../../include/obj/bhkConvexListShape.h"
#include "../../include/obj/bhkConvexShape.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkConvexListShape::TYPE("bhkConvexListShape", &bhkShape::TYPE );

bhkConvexListShape::bhkConvexListShape() : numSubShapes((unsigned int)0), material((HavokMaterial)0), skyrimMaterial((SkyrimHavokMaterial)0), unknownFloats(6,(float)0.0,(float)0.0,(float)-0.0,(float)0.0,(float)0.0,(float)-0.0), unknownByte1((byte)0), unknownFloat1(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

bhkConvexListShape::~bhkConvexListShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & bhkConvexListShape::GetType() const {
	return TYPE;
}

NiObject * bhkConvexListShape::Create() {
	return new bhkConvexListShape;
}

void bhkConvexListShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	bhkShape::Read( in, link_stack, info );
	NifStream( numSubShapes, in, info );
	subShapes.resize(numSubShapes);
	for (unsigned int i1 = 0; i1 < subShapes.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	if ( (info.userVersion < 12) ) {
		NifStream( material, in, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( skyrimMaterial, in, info );
	};
	for (unsigned int i1 = 0; i1 < 6; i1++) {
		NifStream( unknownFloats[i1], in, info );
	};
	NifStream( unknownByte1, in, info );
	NifStream( unknownFloat1, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void bhkConvexListShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkShape::Write( out, link_map, missing_link_stack, info );
	numSubShapes = (unsigned int)(subShapes.size());
	NifStream( numSubShapes, out, info );
	for (unsigned int i1 = 0; i1 < subShapes.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*subShapes[i1]), out );
		} else {
			if ( subShapes[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(subShapes[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( subShapes[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( (info.userVersion < 12) ) {
		NifStream( material, out, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( skyrimMaterial, out, info );
	};
	for (unsigned int i1 = 0; i1 < 6; i1++) {
		NifStream( unknownFloats[i1], out, info );
	};
	NifStream( unknownByte1, out, info );
	NifStream( unknownFloat1, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string bhkConvexListShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkShape::asString();
	numSubShapes = (unsigned int)(subShapes.size());
	out << "  Num Sub Shapes:  " << numSubShapes << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < subShapes.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Sub Shapes[" << i1 << "]:  " << subShapes[i1] << endl;
		array_output_count++;
	};
	out << "  Material:  " << material << endl;
	out << "  Skyrim Material:  " << skyrimMaterial << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 6; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Floats[" << i1 << "]:  " << unknownFloats[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Byte 1:  " << unknownByte1 << endl;
	out << "  Unknown Float 1:  " << unknownFloat1 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void bhkConvexListShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	bhkShape::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < subShapes.size(); i1++) {
		subShapes[i1] = FixLink<bhkConvexShape>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkConvexListShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkShape::GetRefs();
	for (unsigned int i1 = 0; i1 < subShapes.size(); i1++) {
		if ( subShapes[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(subShapes[i1]));
	};
	return refs;
}

std::list<NiObject *> bhkConvexListShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkShape::GetPtrs();
	for (unsigned int i1 = 0; i1 < subShapes.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

HavokMaterial bhkConvexListShape::GetMaterial() const {
	return material;
}

void bhkConvexListShape::SetMaterial( HavokMaterial value ) {
	material = value;
}

vector<Ref<bhkConvexShape > > bhkConvexListShape::GetSubShapes() const {
	return subShapes;
}

/*!
 * Sets the child shape objects that this body is using.
 * \param[in] shapes The shape objects being used by this body.
 */
void bhkConvexListShape::SetSubShapes(const vector<Ref<bhkConvexShape > >& shapes) {
	subShapes = shapes;
}

//--END CUSTOM CODE--//
