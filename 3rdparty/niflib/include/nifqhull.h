/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _NIF_QHULL_H
#define _NIF_QHULL_H
#pragma once

//--Includes--//
#include "nif_math.h"
#include <vector>

namespace Niflib {

class NifQHull {
public:

	static vector<Triangle> compute_convex_hull(const vector<Vector3>& verts);

private:
	explicit NifQHull();
};

}
#endif