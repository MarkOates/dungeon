
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
   EXPECT_EQ(3, actual["blob"].get_num_frames());

   std::vector<DungeonPlus::AnimationFrame> blob_frames = actual["blob"].get_frames();
   EXPECT_EQ(1,   blob_frames[0].get_index());
   EXPECT_FLOAT_EQ(0.2, blob_frames[0].get_duration());
   EXPECT_EQ(2,   blob_frames[1].get_index());
   EXPECT_FLOAT_EQ(0.1, blob_frames[1].get_duration());
   EXPECT_EQ(3,   blob_frames[2].get_index());
   EXPECT_FLOAT_EQ(0.2, blob_frames[2].get_duration());

   EXPECT_EQ(DungeonPlus::Animation::PLAYMODE_FORWARD_PING_PONG, actual["blob"].get_playmode());


   std::vector<DungeonPlus::AnimationFrame> die_frames = actual["die"].get_frames();
   EXPECT_EQ(9,   die_frames[0].get_index());
   EXPECT_FLOAT_EQ(0.2, die_frames[0].get_duration());
   EXPECT_EQ(10,   die_frames[1].get_index());
   EXPECT_FLOAT_EQ(0.2, die_frames[1].get_duration());
   EXPECT_EQ(11,   die_frames[2].get_index());
   EXPECT_FLOAT_EQ(0.2, die_frames[2].get_duration());

   EXPECT_EQ(DungeonPlus::Animation::PLAYMODE_FORWARD_LOOP, actual["die"].get_playmode());
}


