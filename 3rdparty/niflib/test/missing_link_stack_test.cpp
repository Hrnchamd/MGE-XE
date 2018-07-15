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

BOOST_AUTO_TEST_SUITE(missing_link_stack_test_suite)

BOOST_AUTO_TEST_CASE(missing_link_stack_simple_test)
{
  stringstream ss;
  stringstream ss2;

  // create a simple nif tree with a skin partition
  NiNodeRef root = new NiNode;
  NiNodeRef bone = new NiNode;
  root->SetName("Root");
  bone->SetName("Bone");
  NiTriStripsRef shape = new NiTriStrips;
  NiTriStripsDataRef data = new NiTriStripsData;
  // set hierarchy
  shape->SetData(data);
  root->AddChild(DynamicCast<NiAVObject>(shape));
  root->AddChild(DynamicCast<NiAVObject>(bone));
  // bind skin to bone
  {
    vector<NiNodeRef> bones;
    bones.push_back(bone);
    shape->BindSkin(bones);
  }
  // write
  list<NiObject *> missing_link_stack;
  BOOST_CHECK_NO_THROW(WriteNifTree(ss, shape, missing_link_stack, NifInfo(VER_20_0_0_5)));
  bool has_root = false;
  bool has_bone = false;
  // check that root and bone are in the missing link stack
  for (list<NiObject *>::iterator it =  missing_link_stack.begin(); it != missing_link_stack.end(); it++) {
    if ((*it) != NULL) {
      if (!has_root && (*it) == root) {
        has_root = true;
      } else if (!has_bone && (*it) == bone) {
        has_bone = true;
      } else {
        BOOST_CHECK(false);
      }
    };
  }
  BOOST_CHECK_EQUAL(has_root, true);
  BOOST_CHECK_EQUAL(has_bone, true);
  // read it again
  list<NiObjectRef> resolved_link_stack = ResolveMissingLinkStack(root, missing_link_stack);
  ss.seekg(0);
  NifInfo info;
  NiObjectRef new_root;
  BOOST_CHECK_NO_THROW(new_root = ReadNifTree(ss, resolved_link_stack, &info));
  NiTriStripsRef new_shape = DynamicCast<NiTriStrips>(new_root);
  // check for references to the old tree
  BOOST_CHECK(new_shape != NULL);
  BOOST_CHECK(new_shape->skinInstance != NULL);
  BOOST_CHECK_EQUAL(new_shape->skinInstance->skeletonRoot, root);
  BOOST_CHECK_EQUAL(new_shape->skinInstance->bones.size(), 1);
  BOOST_CHECK_EQUAL(new_shape->skinInstance->bones[0], bone);
}

BOOST_AUTO_TEST_CASE(missing_link_stack_clone_test) {
  stringstream ss;
  stringstream ss2;

  // create a simple nif tree with a skin partition
  NiNodeRef root = new NiNode;
  NiNodeRef bone = new NiNode;
  root->SetName("Root");
  bone->SetName("Bone");
  NiTriStripsRef shape = new NiTriStrips;
  NiTriStripsDataRef data = new NiTriStripsData;
  // set hierarchy
  shape->SetData(data);
  root->AddChild(DynamicCast<NiAVObject>(shape));
  root->AddChild(DynamicCast<NiAVObject>(bone));
  // bind skin to bone
  {
    vector<NiNodeRef> bones;
    bones.push_back(bone);
    shape->BindSkin(bones);
  }
  // target tree
  NiNodeRef root2 = new NiNode;
  NiNodeRef bone2 = new NiNode;
  root2->SetName("Root");
  bone2->SetName("Bone");
  root2->AddChild(DynamicCast<NiAVObject>(bone2));
  // clone
  NiTriStripsRef new_shape = DynamicCast<NiTriStrips>(CloneNifTree(shape, VER_20_0_0_5, 0, root2));
  // check for references to the target tree
  BOOST_CHECK(new_shape != NULL);
  BOOST_CHECK(new_shape->skinInstance != NULL);
  BOOST_CHECK_EQUAL(new_shape->skinInstance->skeletonRoot, root2);
  BOOST_CHECK_EQUAL(new_shape->skinInstance->bones.size(), 1);
  BOOST_CHECK_EQUAL(new_shape->skinInstance->bones[0], bone2);
}

BOOST_AUTO_TEST_SUITE_END()
