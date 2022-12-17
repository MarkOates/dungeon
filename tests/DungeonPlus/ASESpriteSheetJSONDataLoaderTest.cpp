
#include <gtest/gtest.h>

#include <DungeonPlus/ASESpriteSheetJSONDataLoader.hpp>


TEST(DungeonPlus_ASESpriteSheetJSONDataLoaderTest, can_be_created_without_blowing_up)
{
   DungeonPlus::ASESpriteSheetJSONDataLoader asesprite_sheet_jsondata_loader;
}


TEST(DungeonPlus_ASESpriteSheetJSONDataLoaderTest, load__will_not_blow_up)
{
   DungeonPlus::ASESpriteSheetJSONDataLoader asesprite_sheet_jsondata_loader;
   asesprite_sheet_jsondata_loader.load();
}


TEST(DungeonPlus_ASESpriteSheetJSONDataLoaderTest, load__fills_the_animation_book_with_the_expected_values)
{
   DungeonPlus::ASESpriteSheetJSONDataLoader asesprite_sheet_jsondata_loader;
   std::map<std::string, DungeonPlus::Animation> actual = asesprite_sheet_jsondata_loader.load();

   EXPECT_EQ(1, actual.count("blob"));
}


