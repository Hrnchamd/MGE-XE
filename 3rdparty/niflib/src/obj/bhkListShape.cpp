/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include "../../include/Inertia.h"
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/bhkListShape.h"
#include "../../include/obj/bhkShape.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkListShape::TYPE("bhkListShape", &bhkShapeCollection::TYPE );

bhkListShape::bhkListShape() : numSubShapes((unsigned int)0), material((HavokMaterial)0), skyrimMaterial((SkyrimHavokMaterial)0), numUnknownInts((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkListShape::~bhkListShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkListShape::GetType() const {
	return TYPE;
}

NiObject * bhkListShape::Create() {
	return new bhkListShape;
}

void bhkListShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	bhkShapeCollection::Read( in, link_stack, info );
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
	NifStream( numUnknownInts, in, info );
	unknownInts.resize(numUnknownInts);
	for (unsigned int i1 = 0; i1 < unknownInts.size(); i1++) {
		NifStream( unknownInts[i1], in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkListShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShapeCollection::Write( out, link_map, missing_link_stack, info );
	numUnknownInts = (unsigned int)(unknownInts.size());
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
	NifStream( numUnknownInts, out, info );
	for (unsigned int i1 = 0; i1 < unknownInts.size(); i1++) {
		NifStream( unknownInts[i1], out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkListShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkShapeCollection::asString();
	numUnknownInts = (unsigned int)(unknownInts.size());
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
	out << "  Num Unknown Ints:  " << numUnknownInts << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknownInts.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown Ints[" << i1 << "]:  " << unknownInts[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkListShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkShapeCollection::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < subShapes.size(); i1++) {
		subShapes[i1] = FixLink<bhkShape>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkListShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkShapeCollection::GetRefs();
	for (unsigned int i1 = 0; i1 < subShapes.size(); i1++) {
		if ( subShapes[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(subShapes[i1]));
	};
	return refs;
}

std::list<NiObject *> bhkListShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkShapeCollection::GetPtrs();
	for (unsigned int i1 = 0; i1 < subShapes.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

HavokMaterial bhkListShape::GetMaterial() const {
	return material;
}

void bhkListShape::SetMaterial( HavokMaterial value ) {
	material = value;
}

vector<Ref<bhkShape > > bhkListShape::GetSubShapes() const {
	return subShapes;
}

/*!
* Sets the child shape objects that this body is using.
* \param[in] shapes The shape objects being used by this body.
*/
void bhkListShape::SetSubShapes(const vector<Ref<bhkShape > >& shapes) {
	subShapes = shapes;

	// Becuase this vector matches the subshape vector
	unknownInts.resize(subShapes.size(), 0);
}

void bhkListShape::CalcMassProperties(float density, bool solid, float &mass, float &volume, Vector3 &center, InertiaMatrix& inertia)
{
	center = Vector3(0,0,0);
	mass = 0.0f;
	volume = 0.0f;
	inertia = InertiaMatrix::IDENTITY;

	vector<float> masses;
	vector<float> volumes;
	vector<Vector3> centers;
	vector<InertiaMatrix> inertias;
	vector<Matrix44> transforms;
	for (vector<bhkShapeRef>::iterator itr = subShapes.begin(); itr != subShapes.end(); ++itr)
	{
		float m; float v; Vector3 c; InertiaMatrix i;
		(*itr)->CalcMassProperties(density, solid, m, v, c, i);
		masses.push_back(m);
		volumes.push_back(v);
		centers.push_back(c);
		inertias.push_back(i);
		transforms.push_back(Matrix44::IDENTITY);
	}
	Inertia::CombineMassProperties(
		masses, volumes, centers, inertias, transforms, 
		mass, volume, center, inertia
		);
}
//--END CUSTOM CODE--//
