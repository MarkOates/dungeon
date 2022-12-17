
#include <gtest/gtest.h>

#include <DungeonPlus/Gameplay.hpp>


TEST(DungeonPlus_GameplayTest, can_be_created_without_blowing_up)
{
   DungeonPlus::Gameplay gameplay;
}


TEST(DungeonPlus_GameplayTest, TYPE__has_the_expected_value)
{
   DungeonPlus::Gameplay gameplay;
   EXPECT_EQ("DungeonPlus/Gameplay", gameplay.get_type());
}


TEST(DungeonPlus_GameplayTest, type__has_the_expected_value_matching_TYPE)
{
   DungeonPlus::Gameplay gameplay;
   EXPECT_EQ(DungeonPlus::Gameplay::TYPE, gameplay.get_type());
}


