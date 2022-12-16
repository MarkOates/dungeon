
#include <gtest/gtest.h>

#include <DungeonPlus/Animation.hpp>


TEST(DungeonPlus_AnimationTest, can_be_created_without_blowing_up)
{
   DungeonPlus::Animation animation;
}


TEST(DungeonPlus_AnimationTest, run__returns_the_expected_response)
{
   DungeonPlus::Animation animation;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, animation.run());
}


