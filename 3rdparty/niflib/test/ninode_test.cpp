#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <sstream> // stringstream

// evil hack to allow testing of private and protected data
#define private public
#define protected public 

#include "niflib.h"
#include "obj/NiNode.h"

using namespace Niflib;
using namespace std;

BOOST_AUTO_TEST_SUITE(ninode_test_suite)

// this test only compiles against a static niflib build
/*
BOOST_AUTO_TEST_CASE(ninode_setskinflag_test)
{
  NiNodeRef node = new NiNode;
  node->SetSkinFlag(false);
  BOOST_CHECK_EQUAL(node->flags, 8);
  node->SetSkinFlag(false);
  BOOST_CHECK_EQUAL(node->flags, 8);
  node->SetSkinFlag(true);
  BOOST_CHECK_EQUAL(node->flags, 0);
  node->SetSkinFlag(true);
  BOOST_CHECK_EQUAL(node->flags, 0);
}
*/

// mock test to stop boost from complaining
BOOST_AUTO_TEST_CASE(ninode_test)
{
}

BOOST_AUTO_TEST_SUITE_END()
