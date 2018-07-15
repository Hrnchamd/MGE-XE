#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <sstream> // stringstream

#include "niflib.h"
#include "obj/NiTriShape.h"
#include "obj/BSLightingShaderProperty.h"

using namespace Niflib;
using namespace std;

BOOST_AUTO_TEST_SUITE(bslightingshaderproperty_test_suite)

BOOST_AUTO_TEST_CASE(bslightingshaderproperty_test)
{
  stringstream ss;

  // create a simple nif tree with BSLightingShaderProperty
  NiTriShapeRef shape = new NiTriShape;
  BSLightingShaderPropertyRef prop = new BSLightingShaderProperty;
  shape->SetBSProperty(0, StaticCast<NiProperty>(prop));
  BOOST_CHECK_NO_THROW(WriteNifTree(ss, shape));
  ss.seekg(0);
  NiObjectRef root;
  BOOST_CHECK_NO_THROW(root = ReadNifTree(ss));
}

BOOST_AUTO_TEST_SUITE_END()
