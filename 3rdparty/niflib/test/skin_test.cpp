#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <sstream> // stringstream

// evil hack to allow testing of private and protected data
#define private public
#define protected public 

#include "niflib.h"
#include "obj/NiNode.h"
#include "obj/NiSkinInstance.h"
#include "obj/NiTriStrips.h"
#include "obj/NiTriStripsData.h"

using namespace Niflib;
using namespace std;

BOOST_AUTO_TEST_SUITE(skin_test_suite)

BOOST_AUTO_TEST_CASE(write_skin_test)
{
  stringstream ss;
  stringstream ss2;

  // create a simple nif tree with a skin partition
  NiNodeRef root = new NiNode;
  NiNodeRef bone = new NiNode;
  NiTriStripsRef shape = new NiTriStrips;
  NiTriStripsDataRef data = new NiTriStripsData;
  // set hierarchy
  shape->SetData(data);
  root->AddChild(DynamicCast<NiAVObject>(shape));
  root->AddChild(DynamicCast<NiAVObject>(bone));
  // add a triangle to the geometry
  {
    vector<Vector3> verts;
    vector<Triangle> tris;
    verts.push_back(Vector3(0, 0, 0));
    verts.push_back(Vector3(0, 1, 0));
    verts.push_back(Vector3(0, 0, 1));
    tris.push_back(Triangle(0, 1, 2));
    data->SetVertices(verts);
    data->SetTriangles(tris);
  }
  // bind skin to bone
  {
    vector<NiNodeRef> bones;
    bones.push_back(bone);
    shape->BindSkin(bones);
    vector<SkinWeight> weights;
    SkinWeight sw;
    sw.weight = 1;
    sw.index = 0;
    weights.push_back(sw);
    sw.index = 1;
    weights.push_back(sw);
    sw.index = 2;
    weights.push_back(sw);
    shape->SetBoneWeights(0, weights);
    shape->GenHardwareSkinInfo();
  }
  // write, read, write, read, and check that nothing throws
  // (we only write the shape, without the bones; obviously skinning
  // will be lost but this is to check that it does not throw)
  NiObjectRef obj;
  BOOST_CHECK_NO_THROW(WriteNifTree(ss, shape, NifInfo(VER_20_0_0_5)));
  ss.seekg(0);
  BOOST_CHECK_NO_THROW(obj = ReadNifTree(ss));
  ss2.seekg(0);
  BOOST_CHECK_NO_THROW(WriteNifTree(ss2, obj, NifInfo(VER_20_0_0_5)));
  ss2.seekg(0);
  BOOST_CHECK_NO_THROW(obj = ReadNifTree(ss2));
}

BOOST_AUTO_TEST_SUITE_END()
