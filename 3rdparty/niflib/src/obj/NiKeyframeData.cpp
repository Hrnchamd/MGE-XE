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
#include "../../include/obj/NiKeyframeData.h"
#include "../../include/gen/KeyGroup.h"
#include "../../include/gen/KeyGroup.h"
#include "../../include/gen/KeyGroup.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiKeyframeData::TYPE("NiKeyframeData", &NiObject::TYPE );

NiKeyframeData::NiKeyframeData() : numRotationKeys((unsigned int)0), rotationType((KeyType)0), unknownFloat(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiKeyframeData::~NiKeyframeData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiKeyframeData::GetType() const {
	return TYPE;
}

NiObject * NiKeyframeData::Create() {
	return new NiKeyframeData;
}

void NiKeyframeData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Read( in, link_stack, info );
	NifStream( numRotationKeys, in, info );
	if ( (numRotationKeys != 0) ) {
		NifStream( rotationType, in, info );
	};
	if ( (rotationType != 4) ) {
		quaternionKeys.resize(numRotationKeys);
		for (unsigned int i2 = 0; i2 < quaternionKeys.size(); i2++) {
			NifStream( quaternionKeys[i2], in, info, rotationType );
		};
	};
	if ( info.version <= 0x0A010000 ) {
		if ( (rotationType == 4) ) {
			NifStream( unknownFloat, in, info );
		};
	};
	if ( (rotationType == 4) ) {
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			NifStream( xyzRotations[i2].numKeys, in, info );
			if ( (xyzRotations[i2].numKeys != 0) ) {
				NifStream( xyzRotations[i2].interpolation, in, info );
			};
			xyzRotations[i2].keys.resize(xyzRotations[i2].numKeys);
			for (unsigned int i3 = 0; i3 < xyzRotations[i2].keys.size(); i3++) {
				NifStream( xyzRotations[i2].keys[i3], in, info, xyzRotations[i2].interpolation );
			};
		};
	};
	NifStream( translations.numKeys, in, info );
	if ( (translations.numKeys != 0) ) {
		NifStream( translations.interpolation, in, info );
	};
	translations.keys.resize(translations.numKeys);
	for (unsigned int i1 = 0; i1 < translations.keys.size(); i1++) {
		NifStream( translations.keys[i1], in, info, translations.interpolation );
	};
	NifStream( scales.numKeys, in, info );
	if ( (scales.numKeys != 0) ) {
		NifStream( scales.interpolation, in, info );
	};
	scales.keys.resize(scales.numKeys);
	for (unsigned int i1 = 0; i1 < scales.keys.size(); i1++) {
		NifStream( scales.keys[i1], in, info, scales.interpolation );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiKeyframeData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	NifStream( numRotationKeys, out, info );
	if ( (numRotationKeys != 0) ) {
		NifStream( rotationType, out, info );
	};
	if ( (rotationType != 4) ) {
		for (unsigned int i2 = 0; i2 < quaternionKeys.size(); i2++) {
			NifStream( quaternionKeys[i2], out, info, rotationType );
		};
	};
	if ( info.version <= 0x0A010000 ) {
		if ( (rotationType == 4) ) {
			NifStream( unknownFloat, out, info );
		};
	};
	if ( (rotationType == 4) ) {
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			xyzRotations[i2].numKeys = (unsigned int)(xyzRotations[i2].keys.size());
			NifStream( xyzRotations[i2].numKeys, out, info );
			if ( (xyzRotations[i2].numKeys != 0) ) {
				NifStream( xyzRotations[i2].interpolation, out, info );
			};
			for (unsigned int i3 = 0; i3 < xyzRotations[i2].keys.size(); i3++) {
				NifStream( xyzRotations[i2].keys[i3], out, info, xyzRotations[i2].interpolation );
			};
		};
	};
	translations.numKeys = (unsigned int)(translations.keys.size());
	NifStream( translations.numKeys, out, info );
	if ( (translations.numKeys != 0) ) {
		NifStream( translations.interpolation, out, info );
	};
	for (unsigned int i1 = 0; i1 < translations.keys.size(); i1++) {
		NifStream( translations.keys[i1], out, info, translations.interpolation );
	};
	scales.numKeys = (unsigned int)(scales.keys.size());
	NifStream( scales.numKeys, out, info );
	if ( (scales.numKeys != 0) ) {
		NifStream( scales.interpolation, out, info );
	};
	for (unsigned int i1 = 0; i1 < scales.keys.size(); i1++) {
		NifStream( scales.keys[i1], out, info, scales.interpolation );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiKeyframeData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	out << "  Num Rotation Keys:  " << numRotationKeys << endl;
	if ( (numRotationKeys != 0) ) {
		out << "    Rotation Type:  " << rotationType << endl;
	};
	if ( (rotationType != 4) ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < quaternionKeys.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Quaternion Keys[" << i2 << "]:  " << quaternionKeys[i2] << endl;
			array_output_count++;
		};
	};
	if ( (rotationType == 4) ) {
		out << "    Unknown Float:  " << unknownFloat << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < 3; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			xyzRotations[i2].numKeys = (unsigned int)(xyzRotations[i2].keys.size());
			out << "      Num Keys:  " << xyzRotations[i2].numKeys << endl;
			if ( (xyzRotations[i2].numKeys != 0) ) {
				out << "        Interpolation:  " << xyzRotations[i2].interpolation << endl;
			};
			array_output_count = 0;
			for (unsigned int i3 = 0; i3 < xyzRotations[i2].keys.size(); i3++) {
				if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
					out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
					break;
				};
				if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
					break;
				};
				out << "        Keys[" << i3 << "]:  " << xyzRotations[i2].keys[i3] << endl;
				array_output_count++;
			};
		};
	};
	translations.numKeys = (unsigned int)(translations.keys.size());
	out << "  Num Keys:  " << translations.numKeys << endl;
	if ( (translations.numKeys != 0) ) {
		out << "    Interpolation:  " << translations.interpolation << endl;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < translations.keys.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Keys[" << i1 << "]:  " << translations.keys[i1] << endl;
		array_output_count++;
	};
	scales.numKeys = (unsigned int)(scales.keys.size());
	out << "  Num Keys:  " << scales.numKeys << endl;
	if ( (scales.numKeys != 0) ) {
		out << "    Interpolation:  " << scales.interpolation << endl;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < scales.keys.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Keys[" << i1 << "]:  " << scales.keys[i1] << endl;
		array_output_count++;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiKeyframeData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiKeyframeData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	return refs;
}

std::list<NiObject *> NiKeyframeData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

void NiKeyframeData::NormalizeKeys( float phase, float frequency ) {
	NormalizeKeyVector( this->translations.keys, phase, frequency );
	NormalizeKeyVector( this->scales.keys, phase, frequency );
	NormalizeKeyVector( this->quaternionKeys, phase, frequency );
	NormalizeKeyVector( this->xyzRotations[0].keys, phase, frequency );
	NormalizeKeyVector( this->xyzRotations[1].keys, phase, frequency );
	NormalizeKeyVector( this->xyzRotations[2].keys, phase, frequency );

}

KeyType NiKeyframeData::GetRotateType() const {
	return rotationType;
}

void NiKeyframeData::SetRotateType( KeyType t ) {
	rotationType = t;
	UpdateRotationKeyCount();
}

vector< Key<Quaternion> > NiKeyframeData::GetQuatRotateKeys() const {
	return quaternionKeys;
}

void NiKeyframeData::UpdateRotationKeyCount() {
	if ( rotationType == XYZ_ROTATION_KEY ) {
		numRotationKeys = 1;
	} else {
		numRotationKeys = (unsigned int)(quaternionKeys.size());
	}
};

void NiKeyframeData::SetQuatRotateKeys( const vector< Key<Quaternion> > & keys ) {
	quaternionKeys = keys;
	UpdateRotationKeyCount();
}

KeyType NiKeyframeData::GetXRotateType() const {
	return xyzRotations[0].interpolation;
}

void NiKeyframeData::SetXRotateType( KeyType t ) {
	xyzRotations[0].interpolation = t;
}

vector< Key<float> > NiKeyframeData::GetXRotateKeys() const {
	return xyzRotations[0].keys;
}

void NiKeyframeData::SetXRotateKeys( const vector< Key<float> > & keys ) {
	xyzRotations[0].keys = keys;
}

KeyType NiKeyframeData::GetYRotateType() const {
	return xyzRotations[1].interpolation;
}

void NiKeyframeData::SetYRotateType( KeyType t ) {
	xyzRotations[1].interpolation = t;
}

vector< Key<float> > NiKeyframeData::GetYRotateKeys() const {
	return xyzRotations[1].keys;
}

void NiKeyframeData::SetYRotateKeys( const vector< Key<float> > & keys ) {
	xyzRotations[1].keys = keys;
}

KeyType NiKeyframeData::GetZRotateType() const {
	return xyzRotations[2].interpolation;
}

void NiKeyframeData::SetZRotateType( KeyType t ) {
	xyzRotations[2].interpolation = t;
}

vector< Key<float> > NiKeyframeData::GetZRotateKeys() const {
	return xyzRotations[2].keys;
}

void NiKeyframeData::SetZRotateKeys( const vector< Key<float> > & keys ) {
	xyzRotations[2].keys = keys;
}

KeyType NiKeyframeData::GetTranslateType() const {
	return translations.interpolation;
}

void NiKeyframeData::SetTranslateType( KeyType t ) {
	translations.interpolation = t;
}

vector< Key<Vector3> > NiKeyframeData::GetTranslateKeys() const {
	return translations.keys;
}

void NiKeyframeData::SetTranslateKeys( vector< Key<Vector3> > const & keys ) {
	translations.keys = keys;
}

KeyType NiKeyframeData::GetScaleType() const {
	return scales.interpolation;
}

void NiKeyframeData::SetScaleType( KeyType t ) {
	scales.interpolation = t;
}

vector< Key<float> > NiKeyframeData::GetScaleKeys() const { 
	return scales.keys;
}

void NiKeyframeData::SetScaleKeys( vector< Key<float> > const & keys ) {
	scales.keys = keys;
}

//--END CUSTOM CODE--//
