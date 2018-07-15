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
#include "obj/NiSkinPartition.h"
#include "obj/NiTriStrips.h"
#include "obj/NiTriStripsData.h"

using namespace Niflib;
using namespace std;

BOOST_AUTO_TEST_SUITE(skinpart_test_suite)

BOOST_AUTO_TEST_CASE(write_skinpart_test)
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
  // check number of triangles
  NiSkinInstanceRef skininst = shape->GetSkinInstance();
  BOOST_REQUIRE(skininst != NULL);
  NiSkinPartitionRef skinpart = skininst->GetSkinPartition();
  BOOST_REQUIRE(skinpart != NULL);
  BOOST_REQUIRE_EQUAL(skinpart->GetNumPartitions(), 1);
  BOOST_CHECK_EQUAL(skinpart->skinPartitionBlocks[0].numTriangles, 1);
  // write, read, write, read, and check that numTriangles is still 1
  // (the first write checks that GenHardwareSkinInfo sets the
  // triangle list; the second write checks that this works even
  // without GenHardwareSkinInfo)
  NiObjectRef obj;
  BOOST_CHECK_NO_THROW(WriteNifTree(ss, root, NifInfo(VER_20_0_0_5)));
  ss.seekg(0);
  BOOST_CHECK_NO_THROW(obj = ReadNifTree(ss));
  ss2.seekg(0);
  BOOST_CHECK_NO_THROW(WriteNifTree(ss2, obj, NifInfo(VER_20_0_0_5)));
  ss2.seekg(0);
  BOOST_CHECK_NO_THROW(obj = ReadNifTree(ss2));
  root = DynamicCast<NiNode>(obj);
  BOOST_REQUIRE(root != NULL);
  BOOST_REQUIRE_EQUAL(root->GetChildren().size(), 2);
  shape = DynamicCast<NiTriStrips>(root->GetChildren()[0]);
  BOOST_REQUIRE(shape != NULL);
  skininst = shape->GetSkinInstance();
  BOOST_REQUIRE(skininst != NULL);
  skinpart = skininst->GetSkinPartition();
  BOOST_REQUIRE(skinpart != NULL);
  BOOST_REQUIRE_EQUAL(skinpart->GetNumPartitions(), 1);
  BOOST_CHECK_EQUAL(skinpart->skinPartitionBlocks[0].numTriangles, 1);
}

BOOST_AUTO_TEST_CASE(skinpart_triangles_partnum_test)
{
  // create a simple skin partition
  NiSkinPartitionRef skinpart = new NiSkinPartition;
  skinpart->SetNumPartitions(1);
  vector<Vector3> verts;
  vector<Triangle> tris;
  verts.push_back(Vector3(0, 0, 0));
  verts.push_back(Vector3(0, 1, 0));
  verts.push_back(Vector3(0, 0, 1));
  tris.push_back(Triangle(0, 1, 2));
  BOOST_CHECK_THROW(skinpart->SetTriangles(5, tris), std::out_of_range);
  BOOST_CHECK_NO_THROW(skinpart->SetTriangles(0, tris));
}

BOOST_AUTO_TEST_CASE(skinpart_triangles_numtriangles_test)
{
  // create a simple skin partition
  NiSkinPartitionRef skinpart = new NiSkinPartition;
  skinpart->SetNumPartitions(1);
  vector<Vector3> verts;
  vector<Triangle> tris;
  verts.push_back(Vector3(0, 0, 0));
  verts.push_back(Vector3(0, 1, 0));
  verts.push_back(Vector3(0, 0, 1));
  tris.push_back(Triangle(0, 1, 2));
  skinpart->SetTriangles(0, tris);
  BOOST_CHECK_EQUAL(skinpart->skinPartitionBlocks[0].numTriangles, 1);
}

BOOST_AUTO_TEST_CASE(skinpart_setstripcount_numstrips)
{
  // create a simple skin partition
  NiSkinPartitionRef skinpart = new NiSkinPartition;
  skinpart->SetNumPartitions(1);
  skinpart->SetStripCount(0, 3);
  BOOST_CHECK_EQUAL(skinpart->skinPartitionBlocks[0].numStrips, 3);
}

BOOST_AUTO_TEST_SUITE_END()
