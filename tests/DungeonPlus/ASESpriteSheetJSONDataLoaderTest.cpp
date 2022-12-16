
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


