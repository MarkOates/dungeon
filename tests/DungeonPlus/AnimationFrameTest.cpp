
#include <gtest/gtest.h>

#include <DungeonPlus/AnimationFrame.hpp>


TEST(DungeonPlus_AnimationFrameTest, can_be_created_without_blowing_up)
{
   DungeonPlus::AnimationFrame animation_frame;
}


TEST(DungeonPlus_AnimationFrameTest, run__returns_the_expected_response)
{
   DungeonPlus::AnimationFrame animation_frame;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, animation_frame.run());
}


