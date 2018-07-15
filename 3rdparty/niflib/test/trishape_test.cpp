#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <sstream> // stringstream

// evil hack to allow testing of private and protected data
#define private public
#define protected public 

#include "niflib.h"
#include "obj/NiNode.h"
#include "obj/NiTriShape.h"
#include "obj/NiTriShapeData.h"

using namespace Niflib;
using namespace std;

BOOST_AUTO_TEST_SUITE(trishape_test_suite)

BOOST_AUTO_TEST_CASE(trishape_match_test)
{
  stringstream ss;
  stringstream ss2;

  // create a simple nif tree with a trishape
  NiNodeRef root = new NiNode;
  NiTriShapeRef shape = new NiTriShape;
  NiTriShapeDataRef data = new NiTriShapeData;
  // set hierarchy
  shape->SetData(data);
  root->AddChild(DynamicCast<NiAVObject>(shape));
  // add triangles and vertices to the geometry
  {
    vector<Vector3> verts;
    vector<Vector3> norms;
    vector<Triangle> tris;
    // 0
    verts.push_back(Vector3(0, 0, 0));
    norms.push_back(Vector3(0, 0, 1));
    // 1
    verts.push_back(Vector3(0, 1, 0));
    norms.push_back(Vector3(0, 0, 1));
    // 2
    verts.push_back(Vector3(0, 0, 1));
    norms.push_back(Vector3(0, 1, 0));
    // 3 == 0
    verts.push_back(Vector3(0, 0, 0));
    norms.push_back(Vector3(0, 0, 1));
    // 4
    verts.push_back(Vector3(0, 1, 0)); 
    norms.push_back(Vector3(0, 1, 0));
    // 5 == 0
    verts.push_back(Vector3(0, 0, 0));
    norms.push_back(Vector3(0, 0, 1));
    // 6 == 2
    verts.push_back(Vector3(0, 0, 1));
    norms.push_back(Vector3(0, 1, 0));
    data->SetVertices(verts);
    data->SetNormals(norms);
  }
  // generate match groups and check them
  BOOST_CHECK_NO_THROW(data->DoMatchDetection());
  BOOST_CHECK_EQUAL(data->matchGroups.size(), 2);
  BOOST_CHECK_EQUAL(data->matchGroups[0].vertexIndices.size(), 3);
  BOOST_CHECK_EQUAL(data->matchGroups[0].vertexIndices[0], 0);
  BOOST_CHECK_EQUAL(data->matchGroups[0].vertexIndices[1], 3);
  BOOST_CHECK_EQUAL(data->matchGroups[0].vertexIndices[2], 5);
  BOOST_CHECK_EQUAL(data->matchGroups[1].vertexIndices.size(), 2);
  BOOST_CHECK_EQUAL(data->matchGroups[1].vertexIndices[0], 2);
  BOOST_CHECK_EQUAL(data->matchGroups[1].vertexIndices[1], 6);
}

BOOST_AUTO_TEST_SUITE_END()
