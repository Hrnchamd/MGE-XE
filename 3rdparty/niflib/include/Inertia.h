/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _NIF_INERTIA_H
#define _NIF_INERTIA_H
#pragma once

//--Includes--//
#include "nif_math.h"
#include <vector>

namespace Niflib {

class Inertia {
public:

	/*! Return mass and inertia matrix for a sphere of given radius and
	 *	density.
	 */
	static void CalcMassPropertiesSphere(
		float radius, 
		float density, bool solid, 
		float& mass, float& volume, Vector3& center, InertiaMatrix &inertia);

	/*! Return mass and inertia matrix for a box of given size and
	 *   density.
	 */
	static void CalcMassPropertiesBox(
		Vector3 size, 
		float density, bool solid, 
		float& mass, float& volume, Vector3& center, InertiaMatrix &inertia);
	/*! Return mass and inertia matrix for a cylinder of given radius, 
	 *   height and density.
	 */
	static void CalcMassPropertiesCylinder(
		Vector3 startAxis, Vector3 endAxis, float radius,
		float density, bool solid,
		float& mass, float& volume, Vector3& center, InertiaMatrix &inertia);

	/*! Return mass and inertia matrix for a capsule of given radius, 
	 *	height and density.
	 */
	static void CalcMassPropertiesCapsule(
		Vector3 startAxis, Vector3 endAxis, float radius,
		float density, bool solid,
		float& mass, float& volume, Vector3& center, InertiaMatrix &inertia);

	/*! Return mass and inertia matrix for a complex polyhedron
	 */
	static void CalcMassPropertiesPolyhedron(
		const vector<Vector3>& vertices, 
		const vector<Triangle>& triangles, 
		float density, bool solid,
		float& mass, float& volume, Vector3& center, InertiaMatrix &inertia);

	/*! Combine mass properties for a number of objects */
	static void CombineMassProperties(
		vector<float> masses, 
		vector<float> volumes, 
		vector<Vector3> centers, 
		vector<InertiaMatrix> inertias,
		vector<Matrix44> transforms,
		float& mass, float& volume, Vector3& center, InertiaMatrix &inertia);

public:

// gcc does not like __stdcall
#ifdef __GNUC__
# define NIFLIB_STDCALL
#else
# define NIFLIB_STDCALL __stdcall
#endif

	// Define external strategy helpers

	/*! Return mass and inertia matrix for a sphere of given radius and
	*	density.
	*/
	typedef void (NIFLIB_STDCALL * fnCalcMassPropertiesSphere)(
		float radius, 
		float density, bool solid, 
		float& mass, float& volume, Vector3& center, InertiaMatrix &inertia);

	/*! Return mass and inertia matrix for a box of given size and
	*   density.
	*/
	typedef void (NIFLIB_STDCALL * fnCalcMassPropertiesBox)(
		Vector3 size, 
		float density, bool solid, 
		float& mass, float& volume, Vector3& center, InertiaMatrix &inertia);

	/*! Return mass and inertia matrix for a cylinder of given radius, 
	*   height and density.
	*/
	typedef void (NIFLIB_STDCALL * fnCalcMassPropertiesCylinder)(
		Vector3 startAxis, Vector3 endAxis, float radius,
		float density, bool solid,
		float& mass, float& volume, Vector3& center, InertiaMatrix &inertia);

	/*! Return mass and inertia matrix for a capsule of given radius, 
	*	height and density.
	*/
	typedef void (NIFLIB_STDCALL * fnCalcMassPropertiesCapsule)(
		Vector3 startAxis, Vector3 endAxis, float radius,  
		float density, bool solid,
		float& mass, float& volume, Vector3& center, InertiaMatrix &inertia);

	/*! Return mass and inertia matrix for a capsule of given radius, 
	*	height and density.
	*/
	typedef void (NIFLIB_STDCALL * fnCalcMassPropertiesPolyhedron)(
		int nVerts, Vector3 const* verts, 
		int nTris, Triangle const* tris,
		float density, bool solid,
		float& mass, float& volume, Vector3& center, InertiaMatrix &inertia);

	/*! Combine mass properties for a number of objects */
	typedef void (NIFLIB_STDCALL * fnCombineMassProperties)(
		int nItems,
		float* masses, float* volumes, Vector3* centers, InertiaMatrix* inertias, Matrix44* transforms,
		float& mass, float& volume, Vector3& center, InertiaMatrix &inertia);

	/*! Define external MassProperty calculation method for Sphere */
	static void SetCalcMassPropertiesSphere(fnCalcMassPropertiesSphere extRoutine);

	/*! Define external MassProperty calculation method for Box */
	static void SetCalcMassPropertiesBox(fnCalcMassPropertiesBox extRoutine);

	/*! Define external MassProperty calculation method for Cylinder */
	static void SetCalcMassPropertiesCylinder(fnCalcMassPropertiesCylinder extRoutine);

	/*! Define external MassProperty calculation method for Capsule */
	static void SetCalcMassPropertiesCapsule(fnCalcMassPropertiesCapsule extRoutine);

	/*! Define external MassProperty calculation method for Polyhedron */
	static void SetCalcMassPropertiesPolyhedron(fnCalcMassPropertiesPolyhedron extRoutine);

	/*! Define external mass property combination routine */
	static void SetCombineMassProperties(fnCombineMassProperties extRoutine);
	

private:
	explicit Inertia();
};

}
#endif
