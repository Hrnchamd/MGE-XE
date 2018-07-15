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

BOOST_AUTO_TEST_SUITE(numuvsets_test_suite)

BOOST_AUTO_TEST_CASE(numuvsets_write_test)
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
  // set flag
  data->SetTspaceFlag(1);
  // write and read
  NiObjectRef obj;
  BOOST_CHECK_NO_THROW(WriteNifTree(ss, root, NifInfo(VER_20_0_0_5)));
  ss.seekg(0);
  BOOST_CHECK_NO_THROW(obj = ReadNifTree(ss));
  // check flag
  root = DynamicCast<NiNode>(obj);
  BOOST_REQUIRE(root != NULL);
  BOOST_REQUIRE_EQUAL(root->GetChildren().size(), 1);
  shape = DynamicCast<NiTriShape>(root->GetChildren()[0]);
  BOOST_REQUIRE(shape != NULL);
  data = DynamicCast<NiTriShapeData>(shape->GetData());
  BOOST_REQUIRE(data != NULL);
  BOOST_CHECK_EQUAL(data->GetTspaceFlag(), 1);
}

BOOST_AUTO_TEST_SUITE_END()
