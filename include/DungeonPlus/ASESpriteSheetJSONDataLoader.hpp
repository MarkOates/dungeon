#pragma once


#include <DungeonPlus/Animation.hpp>
#include <DungeonPlus/AnimationFrame.hpp>
#include <cstdint>
#include <dungeon/models/sprite_sheet.hpp>
#include <map>
#include <string>
#include <vector>


namespace DungeonPlus
{
   class ASESpriteSheetJSONDataLoader
   {
   private:
      SpriteSheet* sprite_sheet;

   protected:


   public:
      ASESpriteSheetJSONDataLoader(SpriteSheet* sprite_sheet=nullptr);
      ~ASESpriteSheetJSONDataLoader();

      std::map<std::string, DungeonPlus::Animation> load();
      std::vector<DungeonPlus::AnimationFrame> _build_animation_frames_for(uint32_t start_frame=0, uint32_t end_frame=0, std::map<int, int> frame_data={});
      uint32_t _get_playmode_from_direction(std::string direction="[unset-direction]");
   };
}



