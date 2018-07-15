#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <sstream> // stringstream

#include "niflib.h"
#include "obj/NiNode.h"
#include "obj/NiKeyframeController.h"

using namespace Niflib;
using namespace std;

BOOST_AUTO_TEST_SUITE(write_test_suite)

BOOST_AUTO_TEST_CASE(write_incomplete_tree_test)
{
  stringstream ss;

  // create a simple nif tree with back reference
  NiNodeRef node = new NiNode;
  NiKeyframeControllerRef ctrl = new NiKeyframeController;
  node->AddController(ctrl);
  BOOST_REQUIRE_EQUAL(ctrl->GetTarget(), node);
  // controller target is the node, but isn't in the tree
  // check that WriteNifTree does not throw
  BOOST_CHECK_NO_THROW(WriteNifTree(ss, ctrl));
  // check that written target is NULL
  ss.seekg(0);
  NiObjectRef root;
  BOOST_CHECK_NO_THROW(root = ReadNifTree(ss));
  NiKeyframeControllerRef ctrl2 = DynamicCast<NiKeyframeController>(root);
  BOOST_REQUIRE(ctrl2 != NULL);
  BOOST_CHECK(ctrl2->GetTarget() == NULL);
}

BOOST_AUTO_TEST_SUITE_END()
