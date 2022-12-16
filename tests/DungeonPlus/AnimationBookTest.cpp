
#include <gtest/gtest.h>

#include <DungeonPlus/AnimationBook.hpp>


TEST(DungeonPlus_AnimationBookTest, can_be_created_without_blowing_up)
{
   DungeonPlus::AnimationBook animation_book;
}


TEST(DungeonPlus_AnimationBookTest, run__returns_the_expected_response)
{
   DungeonPlus::AnimationBook animation_book;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, animation_book.run());
}


