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

static const int SizeofQuat = 4;
static const int SizeofTrans = 3;
static const int SizeofScale = 1;

//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiBSplineCompTransformInterpolator.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiBSplineCompTransformInterpolator::TYPE("NiBSplineCompTransformInterpolator", &NiBSplineTransformInterpolator::TYPE );

NiBSplineCompTransformInterpolator::NiBSplineCompTransformInterpolator() : translationBias(0.0f), translationMultiplier(0.0f), rotationBias(0.0f), rotationMultiplier(0.0f), scaleBias(0.0f), scaleMultiplier(0.0f) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiBSplineCompTransformInterpolator::~NiBSplineCompTransformInterpolator() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiBSplineCompTransformInterpolator::GetType() const {
	return TYPE;
}

NiObject * NiBSplineCompTransformInterpolator::Create() {
	return new NiBSplineCompTransformInterpolator;
}

void NiBSplineCompTransformInterpolator::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBSplineTransformInterpolator::Read( in, link_stack, info );
	NifStream( translationBias, in, info );
	NifStream( translationMultiplier, in, info );
	NifStream( rotationBias, in, info );
	NifStream( rotationMultiplier, in, info );
	NifStream( scaleBias, in, info );
	NifStream( scaleMultiplier, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBSplineCompTransformInterpolator::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBSplineTransformInterpolator::Write( out, link_map, missing_link_stack, info );
	NifStream( translationBias, out, info );
	NifStream( translationMultiplier, out, info );
	NifStream( rotationBias, out, info );
	NifStream( rotationMultiplier, out, info );
	NifStream( scaleBias, out, info );
	NifStream( scaleMultiplier, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiBSplineCompTransformInterpolator::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiBSplineTransformInterpolator::asString();
	out << "  Translation Bias:  " << translationBias << endl;
	out << "  Translation Multiplier:  " << translationMultiplier << endl;
	out << "  Rotation Bias:  " << rotationBias << endl;
	out << "  Rotation Multiplier:  " << rotationMultiplier << endl;
	out << "  Scale Bias:  " << scaleBias << endl;
	out << "  Scale Multiplier:  " << scaleMultiplier << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiBSplineCompTransformInterpolator::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiBSplineTransformInterpolator::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiBSplineCompTransformInterpolator::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiBSplineTransformInterpolator::GetRefs();
	return refs;
}

std::list<NiObject *> NiBSplineCompTransformInterpolator::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiBSplineTransformInterpolator::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

float NiBSplineCompTransformInterpolator::GetTranslateBias() const {
	return translationBias;
}

void NiBSplineCompTransformInterpolator::SetTranslateBias( float value ) {
	translationBias = value;
}

float NiBSplineCompTransformInterpolator::GetTranslateMultiplier() const {
	return translationMultiplier;
}

void NiBSplineCompTransformInterpolator::SetTranslateMultiplier( float value ) {
	translationMultiplier = value;
}

float NiBSplineCompTransformInterpolator::GetRotationBias() const {
	return rotationBias;
}

void NiBSplineCompTransformInterpolator::SetRotationBias( float value ) {
	rotationBias = value;
}

float NiBSplineCompTransformInterpolator::GetRotationMultiplier() const {
	return rotationMultiplier;
}

void NiBSplineCompTransformInterpolator::SetRotationMultiplier( float value ) {
	rotationMultiplier = value;
}

float NiBSplineCompTransformInterpolator::GetScaleBias() const {
	return scaleBias;
}

void NiBSplineCompTransformInterpolator::SetScaleBias( float value ) {
	scaleBias = value;
}

float NiBSplineCompTransformInterpolator::GetScaleMultiplier() const {
	return scaleMultiplier;
}

void NiBSplineCompTransformInterpolator::SetScaleMultiplier( float value ) {
	scaleMultiplier = value;
}

vector< Quaternion > NiBSplineCompTransformInterpolator::GetQuatRotateControlData() const
{
   vector< Quaternion > value;
   if ((rotationOffset != USHRT_MAX) && splineData && basisData) { // has rotation data
      int nctrl = basisData->GetNumControlPoints();
      int npts = nctrl * SizeofQuat;
      vector<short> points = splineData->GetShortControlPointRange(rotationOffset, npts);
      value.reserve(nctrl);
      for (int i=0; i<npts; ) {
         Quaternion key;
         key.w = float(points[i++]) / float (32767) * rotationMultiplier + rotationBias;
         key.x = float(points[i++]) / float (32767) * rotationMultiplier + rotationBias;
         key.y = float(points[i++]) / float (32767) * rotationMultiplier + rotationBias;
         key.z = float(points[i++]) / float (32767) * rotationMultiplier + rotationBias;
         value.push_back(key);
      }
   }
   return value;
}

vector< Vector3 > NiBSplineCompTransformInterpolator::GetTranslateControlData() const
{
   vector< Vector3 > value;
   if ((translationOffset != USHRT_MAX) && splineData && basisData) { // has translation data
      int nctrl = basisData->GetNumControlPoints();
      int npts = nctrl * SizeofTrans;
      vector<short> points = splineData->GetShortControlPointRange(translationOffset, npts);
      value.reserve(nctrl);
      for (int i=0; i<npts; ) {
         Vector3 key;
         key.x = float(points[i++]) / float (32767) * translationMultiplier + translationBias;
         key.y = float(points[i++]) / float (32767) * translationMultiplier + translationBias;
         key.z = float(points[i++]) / float (32767) * translationMultiplier + translationBias;
         value.push_back(key);
      }
   }
   return value;
}

vector< float > NiBSplineCompTransformInterpolator::GetScaleControlData() const
{
   vector< float > value;
   if ((scaleOffset != USHRT_MAX) && splineData && basisData) { // has translation data
      int nctrl = basisData->GetNumControlPoints();
      int npts = nctrl * SizeofScale;
      vector<short> points = splineData->GetShortControlPointRange(scaleOffset, npts);
      value.reserve(nctrl);
      for (int i=0; i<npts; ) {
         float data = float(points[i++]) / float (32767) * scaleMultiplier + scaleBias;
         value.push_back(data);
      }
   }
   return value;
}

vector< Key<Quaternion> > NiBSplineCompTransformInterpolator::SampleQuatRotateKeys(int npoints, int degree) const
{
   vector< Key<Quaternion> > value;
   if ((rotationOffset != USHRT_MAX) && splineData && basisData) { // has rotation data
      int nctrl = basisData->GetNumControlPoints();
      int npts = nctrl * SizeofQuat;
      vector<short> points = splineData->GetShortControlPointRange(rotationOffset, npts);
      vector<float> control(npts);
      vector<float> output(npoints*SizeofQuat);
      for (int i=0, j=0; i<nctrl; ++i) {
         for (int k=0; k<SizeofQuat; ++k)
            control[i*SizeofQuat + k] = float(points[j++]) / float (32767);
      }
      if (degree>=nctrl)
         degree = nctrl - 1;
      // fit data
      bspline(nctrl-1, degree+1, SizeofQuat, &control[0], &output[0], npoints);

      // copy to key
      float time = GetStartTime();
      float incr = (GetStopTime() - GetStartTime()) / float(npoints) ;
      value.reserve(npoints);
      for (int i=0, j=0; i<npoints; i++) {
         Key<Quaternion> key;
         key.time = time;
         key.backward_tangent.Set(1.0f,0.0f,0.0f,0.0f);
         key.forward_tangent.Set(1.0f,0.0f,0.0f,0.0f); 
         key.data.w = output[j++] * rotationMultiplier + rotationBias;
         key.data.x = output[j++] * rotationMultiplier + rotationBias;
         key.data.y = output[j++] * rotationMultiplier + rotationBias;
         key.data.z = output[j++] * rotationMultiplier + rotationBias;
         value.push_back(key);
         time += incr;
      }
   }
   return value;
}

vector< Key<Vector3> > NiBSplineCompTransformInterpolator::SampleTranslateKeys(int npoints, int degree) const
{
   vector< Key<Vector3> > value;
   if ((translationOffset != USHRT_MAX) && splineData && basisData) { // has rotation data
      int nctrl = basisData->GetNumControlPoints();
      int npts = nctrl * SizeofTrans;
      vector<short> points = splineData->GetShortControlPointRange(translationOffset, npts);
      vector<float> control(npts);
      vector<float> output(npoints*SizeofTrans);
      for (int i=0, j=0; i<nctrl; ++i) {
         for (int k=0; k<SizeofTrans; ++k)
            control[i*SizeofTrans + k] = float(points[j++]) / float (32767);
      }
      // fit data
      bspline(nctrl-1, degree+1, SizeofTrans, &control[0], &output[0], npoints);

      // copy to key
      float time = GetStartTime();
      float incr = (GetStopTime() - GetStartTime()) / float(npoints) ;
      value.reserve(npoints);
      for (int i=0, j=0; i<npoints; i++) {
         Key<Vector3> key;
         key.time = time;
         key.backward_tangent.Set(0.0f,0.0f,0.0f);
         key.forward_tangent.Set(0.0f,0.0f,0.0f); 
         key.data.x = output[j++] * translationMultiplier + translationBias;
         key.data.y = output[j++] * translationMultiplier + translationBias;
         key.data.z = output[j++] * translationMultiplier + translationBias;
         value.push_back(key);
         time += incr;
      }
   }
   return value;
}

vector< Key<float> > NiBSplineCompTransformInterpolator::SampleScaleKeys(int npoints, int degree) const
{
   vector< Key<float> > value;
   if ((scaleOffset != USHRT_MAX) && splineData && basisData) // has rotation data
   {
      int nctrl = basisData->GetNumControlPoints();
      int npts = nctrl * SizeofScale;
      vector<short> points = splineData->GetShortControlPointRange(scaleOffset, npts);
      vector<float> control(npts);
      vector<float> output(npoints*SizeofScale);
      for (int i=0, j=0; i<nctrl; ++i) {
         control[i] = float(points[j++]) / float (32767);
      }
      // fit data
      bspline(nctrl-1, degree+1, SizeofScale, &control[0], &output[0], npoints);

      // copy to key
      float time = GetStartTime();
      float incr = (GetStopTime() - GetStartTime()) / float(npoints) ;
      value.reserve(npoints);
      for (int i=0, j=0; i<npoints; i++) {
         Key<float> key;
         key.time = time;
         key.backward_tangent = 0.0f;
         key.forward_tangent = 0.0f; 
         key.data = output[j++] * scaleMultiplier + scaleBias;
         value.push_back(key);
         time += incr;
      }
   }
   return value;
}

int NiBSplineCompTransformInterpolator::GetNumControlPoints() const
{
   if (basisData)
   {
      return basisData->GetNumControlPoints();
   }
   return 0;
}

//--END CUSTOM CODE--//
