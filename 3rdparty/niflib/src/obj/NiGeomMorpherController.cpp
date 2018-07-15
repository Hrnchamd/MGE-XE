/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include "../../include/obj/NiKeyBasedInterpolator.h"
#include "../../include/obj/NiGeometry.h"
#include "../../include/obj/NiGeometryData.h"
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiGeomMorpherController.h"
#include "../../include/gen/MorphWeight.h"
#include "../../include/obj/NiInterpolator.h"
#include "../../include/obj/NiInterpolator.h"
#include "../../include/obj/NiMorphData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiGeomMorpherController::TYPE("NiGeomMorpherController", &NiInterpController::TYPE );

NiGeomMorpherController::NiGeomMorpherController() : extraFlags((unsigned short)0), unknown2((byte)0), data(NULL), alwaysUpdate((byte)0), numInterpolators((unsigned int)0), numUnknownInts((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiGeomMorpherController::~NiGeomMorpherController() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiGeomMorpherController::GetType() const {
	return TYPE;
}

NiObject * NiGeomMorpherController::Create() {
	return new NiGeomMorpherController;
}

void NiGeomMorpherController::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiInterpController::Read( in, link_stack, info );
	if ( info.version >= 0x0A000102 ) {
		NifStream( extraFlags, in, info );
	};
	if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
		NifStream( unknown2, in, info );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	NifStream( alwaysUpdate, in, info );
	if ( info.version >= 0x0A01006A ) {
		NifStream( numInterpolators, in, info );
	};
	if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x14000005 ) ) {
		interpolators.resize(numInterpolators);
		for (unsigned int i2 = 0; i2 < interpolators.size(); i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
	};
	if ( info.version >= 0x14010003 ) {
		interpolatorWeights.resize(numInterpolators);
		for (unsigned int i2 = 0; i2 < interpolatorWeights.size(); i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
			NifStream( interpolatorWeights[i2].weight_, in, info );
		};
	};
	if ( ( info.version >= 0x14000004 ) && ( info.version <= 0x14000005 ) && ( (info.userVersion >= 10) ) ) {
		NifStream( numUnknownInts, in, info );
		unknownInts.resize(numUnknownInts);
		for (unsigned int i2 = 0; i2 < unknownInts.size(); i2++) {
			NifStream( unknownInts[i2], in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	// Synchronize the interpolator and morphweight structures.
	if (info.version >= 0x14020007)
	{
		interpolators.resize(numInterpolators);
		for (unsigned int i2 = 0; i2 < numInterpolators; i2++) {
			interpolators[i2] = interpolatorWeights[i2].interpolator;
		}
	}
	else
	{
		interpolatorWeights.resize(numInterpolators);
		for (unsigned int i2 = 0; i2 < numInterpolators; i2++) {
			interpolatorWeights[i2].interpolator = interpolators[i2];
		}
	}
	//--END CUSTOM CODE--//
}

void NiGeomMorpherController::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiInterpController::Write( out, link_map, missing_link_stack, info );
	numUnknownInts = (unsigned int)(unknownInts.size());
	numInterpolators = (unsigned int)(interpolators.size());
	if ( info.version >= 0x0A000102 ) {
		NifStream( extraFlags, out, info );
	};
	if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
		NifStream( unknown2, out, info );
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*data), out );
	} else {
		if ( data != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(data) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( data );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	NifStream( alwaysUpdate, out, info );
	if ( info.version >= 0x0A01006A ) {
		NifStream( numInterpolators, out, info );
	};
	if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x14000005 ) ) {
		for (unsigned int i2 = 0; i2 < interpolators.size(); i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*interpolators[i2]), out );
			} else {
				if ( interpolators[i2] != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolators[i2]) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( interpolators[i2] );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
	};
	if ( info.version >= 0x14010003 ) {
		for (unsigned int i2 = 0; i2 < interpolatorWeights.size(); i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*interpolatorWeights[i2].interpolator), out );
			} else {
				if ( interpolatorWeights[i2].interpolator != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(interpolatorWeights[i2].interpolator) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( interpolatorWeights[i2].interpolator );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
			NifStream( interpolatorWeights[i2].weight_, out, info );
		};
	};
	if ( ( info.version >= 0x14000004 ) && ( info.version <= 0x14000005 ) && ( (info.userVersion >= 10) ) ) {
		NifStream( numUnknownInts, out, info );
		for (unsigned int i2 = 0; i2 < unknownInts.size(); i2++) {
			NifStream( unknownInts[i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiGeomMorpherController::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiInterpController::asString();
	numUnknownInts = (unsigned int)(unknownInts.size());
	numInterpolators = (unsigned int)(interpolators.size());
	out << "  Extra Flags:  " << extraFlags << endl;
	out << "  Unknown 2:  " << unknown2 << endl;
	out << "  Data:  " << data << endl;
	out << "  Always Update:  " << alwaysUpdate << endl;
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
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < interpolatorWeights.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Interpolator:  " << interpolatorWeights[i1].interpolator << endl;
		out << "    Weight?:  " << interpolatorWeights[i1].weight_ << endl;
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

void NiGeomMorpherController::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiInterpController::FixLinks( objects, link_stack, missing_link_stack, info );
	data = FixLink<NiMorphData>( objects, link_stack, missing_link_stack, info );
	if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x14000005 ) ) {
		for (unsigned int i2 = 0; i2 < interpolators.size(); i2++) {
			interpolators[i2] = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
		};
	};
	if ( info.version >= 0x14010003 ) {
		for (unsigned int i2 = 0; i2 < interpolatorWeights.size(); i2++) {
			interpolatorWeights[i2].interpolator = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
		};
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiGeomMorpherController::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiInterpController::GetRefs();
	if ( data != NULL )
		refs.push_back(StaticCast<NiObject>(data));
	for (unsigned int i1 = 0; i1 < interpolators.size(); i1++) {
		if ( interpolators[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(interpolators[i1]));
	};
	for (unsigned int i1 = 0; i1 < interpolatorWeights.size(); i1++) {
		if ( interpolatorWeights[i1].interpolator != NULL )
			refs.push_back(StaticCast<NiObject>(interpolatorWeights[i1].interpolator));
	};
	return refs;
}

std::list<NiObject *> NiGeomMorpherController::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiInterpController::GetPtrs();
	for (unsigned int i1 = 0; i1 < interpolators.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < interpolatorWeights.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

void NiGeomMorpherController::NormalizeKeys() {

	//Normalize any keys that are stored in Morph Data
	if ( data != NULL ) {
		data->NormalizeKeys( this->phase, this->frequency );
	}

	//Normalize any keys stored in float interpolators
	for ( size_t i = 0; i < this->interpolators.size(); ++i ) {
		NiKeyBasedInterpolatorRef keyBased = DynamicCast<NiKeyBasedInterpolator>(interpolators[i]);
		if ( keyBased != NULL ) {
			keyBased->NormalizeKeys( this->phase, this->frequency );
		}
	}

	//Call the NiTimeController version of this function to normalize the start
	//and stop times and reset the phase and frequency
	NiTimeController::NormalizeKeys();
}

vector< Ref<NiInterpolator> > NiGeomMorpherController::GetInterpolators() const {
	return interpolators;
}

void NiGeomMorpherController::SetInterpolators( const vector< Ref<NiInterpolator> > & n ) {
	numInterpolators = (unsigned int)(n.size());
	interpolators = n;

	// synchronize interpolator weights.  Weights will sync later
	interpolatorWeights.resize(numInterpolators);
	for ( size_t i = 0; i < numInterpolators; ++i ) {
		interpolatorWeights[i].interpolator = interpolators[i];
	}
}

Ref<NiMorphData> NiGeomMorpherController::GetData() const {
	return data;
}

void NiGeomMorpherController::SetData( NiMorphData * n ) {
	data = n;
}

// Calculate bounding sphere using minimum-volume axis-align bounding box.  Its fast but not a very good fit.
static void CalcAxisAlignedBox(vector<Vector3> const & vertices, Vector3& center, float& radius)
{
	//--Calculate center & radius--//

	//Set lows and highs to first vertex
	Vector3 lows = vertices[ 0 ];
	Vector3 highs = vertices[ 0 ];

	if (radius != 0.0f) // Initialize from previous box
	{
		lows = Vector3(center.x - radius, center.y - radius, center.z - radius);
		highs = Vector3(center.x + radius, center.y + radius, center.z + radius);
	}

	//Iterate through the vertices, adjusting the stored values
	//if a vertex with lower or higher values is found
	for ( unsigned int i = 0; i < vertices.size(); ++i ) {
		const Vector3 & v = vertices[ i ];

		if ( v.x > highs.x ) highs.x = v.x;
		else if ( v.x < lows.x ) lows.x = v.x;

		if ( v.y > highs.y ) highs.y = v.y;
		else if ( v.y < lows.y ) lows.y = v.y;

		if ( v.z > highs.z ) highs.z = v.z;
		else if ( v.z < lows.z ) lows.z = v.z;
	}

	//Now we know the extent of the shape, so the center will be the average
	//of the lows and highs
	center = (highs + lows) / 2.0f;

	//The radius will be the largest distance from the center
	Vector3 diff;
	float dist2(0.0f), maxdist2(0.0f);
	for ( unsigned int i = 0; i < vertices.size(); ++i ) {
		const Vector3 & v = vertices[ i ];

		diff = center - v;
		dist2 = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
		if ( dist2 > maxdist2 ) maxdist2 = dist2;
	};
	radius = sqrt(maxdist2);
}

void NiGeomMorpherController::UpdateModelBound() {
	if (NiGeometryRef geom = DynamicCast<NiGeometry>(target))
	{
		if (NiGeometryDataRef gdata = geom->GetData())
		{
			Vector3 center = gdata->GetCenter();
			float radius = gdata->GetRadius();
			int nmorph = data->GetMorphCount();
			for (int i=0; i<nmorph; i++)
			{
				CalcAxisAlignedBox(data->GetMorphVerts(i), center, radius);
			}
			gdata->SetBound(center, radius);
		}
	}
}


//--END CUSTOM CODE--//
