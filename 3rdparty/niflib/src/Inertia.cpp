/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#include "../include/Inertia.h"
#include "../include/nifqhull.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace Niflib;

static Inertia::fnCalcMassPropertiesSphere extCalcMassPropertiesSphereRoutine = NULL;
static Inertia::fnCalcMassPropertiesBox extCalcMassPropertiesBoxRoutine = NULL;
static Inertia::fnCalcMassPropertiesCylinder extCalcMassPropertiesCylinderRoutine = NULL;
static Inertia::fnCalcMassPropertiesCapsule extCalcMassPropertiesCapsuleRoutine = NULL;
static Inertia::fnCalcMassPropertiesPolyhedron extCalcMassPropertiesPolyhedronRoutine = NULL;
static Inertia::fnCombineMassProperties extCombineMassPropertiesRoutine = NULL;

void Inertia::SetCalcMassPropertiesSphere(Inertia::fnCalcMassPropertiesSphere extRoutine) {
	extCalcMassPropertiesSphereRoutine = extRoutine;
}

void Inertia::SetCalcMassPropertiesBox(Inertia::fnCalcMassPropertiesBox extRoutine) {
	extCalcMassPropertiesBoxRoutine = extRoutine;
}

void Inertia::SetCalcMassPropertiesCylinder(Inertia::fnCalcMassPropertiesCylinder extRoutine) {
	extCalcMassPropertiesCylinderRoutine = extRoutine;
}

void Inertia::SetCalcMassPropertiesCapsule(Inertia::fnCalcMassPropertiesCapsule extRoutine) {
	extCalcMassPropertiesCapsuleRoutine = extRoutine;
}

void Inertia::SetCalcMassPropertiesPolyhedron(Inertia::fnCalcMassPropertiesPolyhedron extRoutine) {
	extCalcMassPropertiesPolyhedronRoutine = extRoutine;
}

/*! Define external mass property combination routine */
void Inertia::SetCombineMassProperties(Inertia::fnCombineMassProperties extRoutine) {
	extCombineMassPropertiesRoutine = extRoutine;
}



void Inertia::CalcMassPropertiesSphere(float radius, 
								   float density, bool solid, 
								   float& mass, float& volume, Vector3& center, InertiaMatrix &inertia)
{
	if (extCalcMassPropertiesSphereRoutine) {
		extCalcMassPropertiesSphereRoutine(radius, density, solid, mass, volume, center, inertia);
		return;
	}
	float inertiaScalar;
    if (solid) {
        mass = density * (4.0f * float(M_PI) * pow(radius, 3.0f)) / 3.0f;
        inertiaScalar = (2.0f * mass * pow(radius, 2.0f)) / 5.0f;
	} else {
        mass = density * 4.0f * float(M_PI) * pow(radius, 2.0f);
        inertiaScalar = (2.0f * mass * pow(radius, 2.0f)) / 3.0f;
	}
	center = Vector3();
	inertia = InertiaMatrix::IDENTITY;
	inertia[0][0] = inertia[1][1] = inertia[2][2] = inertiaScalar;
}



void Inertia::CalcMassPropertiesBox(Vector3 size, 
								float density, bool solid,
								float& mass, float& volume, Vector3& center, InertiaMatrix &inertia)
{
	if (extCalcMassPropertiesBoxRoutine) {
		extCalcMassPropertiesBoxRoutine(size, density, solid, mass, volume, center, inertia);
		return;
	}

	Vector3 tmp;
    if (solid)
	{
        mass = density * (size[0] * size[1] * size[2]);
        tmp[0] = mass * pow(size[0], 2.0f) / 12.0f;
		tmp[1] = mass * pow(size[1], 2.0f) / 12.0f;
		tmp[2] = mass * pow(size[2], 2.0f) / 12.0f;
	}
    else
	{
        mass = density * ((size[0]*size[1]*2.0f) + (size[0]*size[2]*2.0f) + (size[1]*size[2]*2.0f));
		tmp[0] = mass * pow(size[0], 2.0f) / 6.0f;
		tmp[1] = mass * pow(size[1], 2.0f) / 6.0f;
		tmp[2] = mass * pow(size[2], 2.0f) / 6.0f;
		//TODO: just guessing here, calculate it
	}
	inertia = InertiaMatrix::IDENTITY;
	inertia[0][0] = tmp[1] + tmp[2];
	inertia[1][1] = tmp[2] + tmp[0];
	inertia[2][2] = tmp[0] + tmp[1];
	center = Vector3();
}

void Inertia::CalcMassPropertiesCylinder(Vector3 startAxis, Vector3 endAxis, float radius,
									 float density, bool solid,
									 float& mass, float& volume, Vector3& center, InertiaMatrix &inertia)
{
	if (extCalcMassPropertiesCylinderRoutine) {
		extCalcMassPropertiesCylinderRoutine(startAxis, endAxis, radius, density, solid, mass, volume, center, inertia);
		return;
	}
	float height = (startAxis - endAxis).Magnitude();
	center = (startAxis + endAxis) / 2.0f;

	inertia = InertiaMatrix::IDENTITY;
	if (solid)
	{
		mass = density * height * float(M_PI) * pow(radius, 2.0f);
		inertia[0][0] = 
		inertia[1][1] = mass * (3.0f * pow(radius, 3.0f) + pow(height, 2.0f)) / 12.0f;
		inertia[2][2] = mass * (pow(radius, 2.0f)) / 2.0f;
	}
	else
	{
		mass = density * height * float(M_PI) * pow(radius, 2.0f);
		inertia[0][0] = 
		inertia[1][1] = mass * (6.0f * pow(radius, 3.0f) + pow(height, 2.0f)) / 12.0f;
		inertia[2][2] = mass * (pow(radius, 2.0f));
	}
}

void Inertia::CalcMassPropertiesCapsule(Vector3 startAxis, Vector3 endAxis, float radius, 
									float density, bool solid,
									float& mass, float& volume, Vector3& center, InertiaMatrix &inertia)
{
	if (extCalcMassPropertiesCapsuleRoutine) {
		extCalcMassPropertiesCapsuleRoutine(startAxis, endAxis, radius, density, solid, mass, volume, center, inertia);
		return;
	}

	float height = (startAxis - endAxis).Magnitude();
	center = (startAxis + endAxis) / 2.0f;

    // cylinder + caps, and caps have volume of a sphere
	inertia = InertiaMatrix::IDENTITY;
	if (solid)
	{
		mass = density * (height * float(M_PI) * pow(radius, 2.0f) + (4.0f * float(M_PI) * pow(radius, 3.0f)) / 3.0f);
		inertia[0][0] = mass * (3.0f * pow(radius, 3.0f) + pow(height, 2.0f)) / 12.0f;
		inertia[1][1] = inertia[0][0];
		inertia[2][2] = mass * (pow(radius, 2.0f)) / 2.0f;
	}
	else
	{
		mass = density * (height * 2.0f * float(M_PI) * radius + 2.0f * float(M_PI) * pow(radius, 2.0f));
		inertia[0][0] = mass * (6.0f * pow(radius, 2.0f) + pow(height, 2.0f)) / 12.0f;
		inertia[1][1] = inertia[0][0];
		inertia[2][2] = mass * pow(radius, 2.0f);
	}
}

//
// References
// ----------
//
// Jonathan Blow, Atman J Binstock
// "How to find the inertia tensor (or other mass properties) of a 3D solid body represented by a triangle mesh"
// http://number-none.com/blow/inertia/bb_inertia.doc
//
// David Eberly
// "Polyhedral Mass Properties (Revisited)"
// http://www.geometrictools.com//LibPhysics/RigidBody/Wm4PolyhedralMassProperties.pdf
//
// The function is an implementation of the Blow and Binstock algorithm,
// extended for the case where the polygon is a surface (set parameter
// solid = False).
void Inertia::CalcMassPropertiesPolyhedron(const vector<Vector3>& vertices, 
											 const vector<Triangle>& triangles, 
											 float density, bool solid,
											 float& mass, float& volume, Vector3& center, InertiaMatrix &inertia)
{
	if (extCalcMassPropertiesPolyhedronRoutine) {
		extCalcMassPropertiesPolyhedronRoutine(
			int(vertices.size()), &vertices[0],
			int(triangles.size()), triangles.empty() ? NULL : &triangles[0],
			density, solid, mass, volume, center, inertia);
		return;
	}

	vector<Triangle>::const_iterator triBegin, triEnd;
	vector<Triangle> tris;
	if (triangles.size() == 0)
	{
		tris = NifQHull::compute_convex_hull(vertices);
		triBegin = tris.begin();
		triEnd = tris.end();
	}
	else
	{
		triBegin = triangles.begin();
		triEnd = triangles.end();
	}

    // 120 times the covariance matrix of the canonical tetrahedron
    // (0,0,0),(1,0,0),(0,1,0),(0,0,1)
    // integrate(integrate(integrate(z*z, x=0..1-y-z), y=0..1-z), z=0..1) = 1/120
    // integrate(integrate(integrate(y*z, x=0..1-y-z), y=0..1-z), z=0..1) = 1/60
    Matrix33 covariance_canonical(	2.0f, 1.0f, 1.0f, 
									1.0f, 2.0f, 1.0f, 
									1.0f, 1.0f, 2.0f );
    vector<Matrix44> covariances;
    vector<float> masses;
    vector<Vector3> centers;

    // for each triangle
    // construct a tetrahedron from triangle + (0,0,0)
    // find its matrix, mass, and center (for density = 1, will be corrected at
    // the end of the algorithm)
	for (vector<Triangle>::const_iterator itr=triBegin, end=triEnd; itr != end; ++itr)
	{
        // Calc vertices
        const Vector3& vert0 = vertices[ (*itr)[0] ];
		const Vector3& vert1 = vertices[ (*itr)[1] ];
		const Vector3& vert2 = vertices[ (*itr)[2] ];

        // construct a transform matrix that converts the canonical tetrahedron
        // into (0,0,0),vert0,vert1,vert2
		Matrix44 transform_transposed(Matrix33(
			vert0[0], vert0[1], vert0[2],
			vert1[0], vert1[1], vert1[2],
			vert2[0], vert2[1], vert2[2]));
		Matrix44 transform = transform_transposed.Transpose();

        // find the covariance matrix of the transformed tetrahedron/triangle
        if (solid)
		{
            // we shall be needing the determinant more than once, so
            // precalculate it
			float determinant = transform.Determinant();

            // C' = det(A) * A * C * A^T
			covariances.push_back( transform * covariance_canonical * transform_transposed * determinant );
            // m = det(A) / 6.0
            masses.push_back(determinant / 6.0f);
            // find center of gravity of the tetrahedron
			centers.push_back(
				Vector3(0.25f * (vert0[0] + vert1[0] + vert2[0]),
						0.25f * (vert0[1] + vert1[1] + vert2[1]),
						0.25f * (vert0[2] + vert1[2] + vert2[2]))
				);
		} else {
            // find center of gravity of the triangle
			Vector3 com( (vert0[0] + vert1[0] + vert2[0]) / 3.0f,
						 (vert0[1] + vert1[1] + vert2[1]) / 3.0f,
						 (vert0[2] + vert1[2] + vert2[2]) / 3.0f);
			centers.push_back( com );

            // find mass of triangle
            // mass is surface, which is half the norm of cross product
            // of two edges
			float calc_mass = ((vert1 - vert0) ^ (vert2 - vert0)).Magnitude() / 2.0f;
			masses.push_back( calc_mass );

            // find covariance at center of this triangle
            // (this is approximate only as it replaces triangle with point mass
            // TODO: find better way)
			Matrix33 calc_c( com[0]*com[0], com[0]*com[1], com[0]*com[2],
							 com[1]*com[0], com[1]*com[1], com[1]*com[2],
							 com[2]*com[0], com[2]*com[1], com[2]*com[2]);
            covariances.push_back( Matrix44(calc_c) );
		}
	}
    // accumulate the results
	mass = std::accumulate(masses.begin(), masses.end(), 0.0f);
    if (mass < 0.0001f)
	{
        // dimension is probably badly chosen
        //raise ZeroDivisionError("mass is zero (consider calculating inertia with a lower dimension)")
        //printf("WARNING: mass is zero");
		mass = 0.0f, volume = 0.0f;
		center = Vector3();
		inertia = InertiaMatrix::IDENTITY;
		return;
	}

    // weighed average of centers with masses
	center = Vector3();
	for (size_t i = 0; i<masses.size(); ++i)
		center += (centers[i] * (masses[i] / mass) );

    // add covariances, and correct the values
	Matrix44 total_covariance;
	if (solid)
	{
		for (size_t i = 0; i<covariances.size(); ++i)
			total_covariance *= covariances[i];
	}


    // translate covariance to center of gravity:
    // C' = C - m * ( x dx^T + dx x^T + dx dx^T )
    // with x the translation vector and dx the center of gravity

	Matrix44 translate_correction(
		Matrix33( center[0]*center[0], center[0]*center[1], center[0]*center[2],
				 center[1]*center[0], center[1]*center[1], center[1]*center[2],
				 center[2]*center[0], center[2]*center[1], center[2]*center[2]
				) 
		);
	translate_correction *= mass;

    total_covariance = total_covariance - translate_correction;

    // convert covariance matrix into inertia tensor
	float trace = total_covariance[0][0] + total_covariance[1][1] + total_covariance[2][2];
	Matrix44 trace_matrix;
	trace_matrix[0][0] = trace_matrix[1][1] = trace_matrix[2][2] = trace;
		
	// correct for given density
    inertia = InertiaMatrix((trace_matrix - total_covariance).GetRotation()) * density;
    mass *= density;
}

void Inertia::CombineMassProperties( 
	vector<float> masses, 
	vector<float> volumes, 
	vector<Vector3> centers, 
	vector<InertiaMatrix> inertias, 
	vector<Matrix44> transforms, 
	float& mass, float& volume, Vector3& center, InertiaMatrix &inertia )
{
	if (extCombineMassPropertiesRoutine) {
		extCombineMassPropertiesRoutine(
			int(masses.size()),
			&masses[0], &volumes[0], &centers[0], &inertias[0], &transforms[0],
			mass, volume, center, inertia);
		return;
	}

	for (size_t i=0; i < masses.size(); ++i) {
		mass += masses[i];
	}
	// TODO: doubt this inertia calculation is even remotely close
	for (size_t i=0; i < masses.size(); ++i) {
		center += centers[i] * (masses[i] / mass);
		inertia *= inertias[i];
	}

}
