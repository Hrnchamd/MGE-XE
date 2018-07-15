/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include "../../include/obj/NiBSplineBasisData.h"
#include "../../include/obj/NiBSplineData.h"
static const int SizeofValue = 1;
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiBSplineCompFloatInterpolator.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiBSplineCompFloatInterpolator::TYPE("NiBSplineCompFloatInterpolator", &NiBSplineFloatInterpolator::TYPE );

NiBSplineCompFloatInterpolator::NiBSplineCompFloatInterpolator() : base(0.0f), offset((unsigned int)0), bias(0.0f), multiplier(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiBSplineCompFloatInterpolator::~NiBSplineCompFloatInterpolator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiBSplineCompFloatInterpolator::GetType() const {
	return TYPE;
}

NiObject * NiBSplineCompFloatInterpolator::Create() {
	return new NiBSplineCompFloatInterpolator;
}

void NiBSplineCompFloatInterpolator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBSplineFloatInterpolator::Read( in, link_stack, info );
	NifStream( base, in, info );
	NifStream( offset, in, info );
	NifStream( bias, in, info );
	NifStream( multiplier, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBSplineCompFloatInterpolator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBSplineFloatInterpolator::Write( out, link_map, missing_link_stack, info );
	NifStream( base, out, info );
	NifStream( offset, out, info );
	NifStream( bias, out, info );
	NifStream( multiplier, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiBSplineCompFloatInterpolator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiBSplineFloatInterpolator::asString();
	out << "  Base:  " << base << endl;
	out << "  Offset:  " << offset << endl;
	out << "  Bias:  " << bias << endl;
	out << "  Multiplier:  " << multiplier << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBSplineCompFloatInterpolator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBSplineFloatInterpolator::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBSplineCompFloatInterpolator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiBSplineFloatInterpolator::GetRefs();
	return refs;
}

std::list<NiObject *> NiBSplineCompFloatInterpolator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiBSplineFloatInterpolator::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

float NiBSplineCompFloatInterpolator::GetBase() const {
	return base;
}

void NiBSplineCompFloatInterpolator::SetBase( float value ) {
	base = value;
}


float NiBSplineCompFloatInterpolator::GetBias() const {
	return bias;
}

void NiBSplineCompFloatInterpolator::SetBias( float value ) {
	bias = value;
}

float NiBSplineCompFloatInterpolator::GetMultiplier() const {
	return multiplier;
}

void NiBSplineCompFloatInterpolator::SetMultiplier( float value ) {
	multiplier = value;
}

vector< float > NiBSplineCompFloatInterpolator::GetControlData() const
{
	vector< float > value;
	if ((offset != USHRT_MAX) && splineData && basisData) { // has translation data
		int nctrl = basisData->GetNumControlPoints();
		int npts = nctrl * SizeofValue;
		vector<short> points = splineData->GetShortControlPointRange(offset, npts);
		value.reserve(nctrl);
		for (int i=0; i<npts; ) {
			float data = float(points[i++]) / float (32767) * multiplier + bias;
			value.push_back(data);
		}
	}
	return value;
}


vector< Key<float> > NiBSplineCompFloatInterpolator::SampleKeys(int npoints, int degree) const
{
	vector< Key<float> > value;
	if ((offset != USHRT_MAX) && splineData && basisData) // has rotation data
	{
		int nctrl = basisData->GetNumControlPoints();
		int npts = nctrl * SizeofValue;
		vector<short> points = splineData->GetShortControlPointRange(offset, npts);
		vector<float> control(npts);
		vector<float> output(npoints*SizeofValue);
		for (int i=0, j=0; i<nctrl; ++i) {
			control[i] = float(points[j++]) / float (32767);
		}
		// fit data
		bspline(nctrl-1, degree+1, SizeofValue, &control[0], &output[0], npoints);

		// copy to key
		float time = GetStartTime();
		float incr = (GetStopTime() - GetStartTime()) / float(npoints) ;
		value.reserve(npoints);
		for (int i=0, j=0; i<npoints; i++) {
			Key<float> key;
			key.time = time;
			key.backward_tangent = 0.0f;
			key.forward_tangent = 0.0f; 
			key.data = output[j++] * multiplier + bias;
			value.push_back(key);
			time += incr;
		}
	}
	return value;
}

int NiBSplineCompFloatInterpolator::GetNumControlPoints() const
{
	if (basisData)
	{
		return basisData->GetNumControlPoints();
	}
	return 0;
}

//--END CUSTOM CODE--//
