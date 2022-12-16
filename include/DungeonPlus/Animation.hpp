#pragma once


#include <DungeonPlus/AnimationFrame.hpp>
#include <cstdint>
#include <string>
#include <vector>


namespace DungeonPlus
{
   class Animation
   {
   public:
      static constexpr uint32_t PLAYMODE_UNDEF = 0;
      static constexpr uint32_t PLAYMODE_FORWARD = 0;

   private:
      std::string name;
      std::vector<AnimationFrame> frames;
      uint32_t playmode;
      float playhead;

   protected:


   public:
      Animation();
      ~Animation();

      void update();
      uint32_t get_frame_id_at(float time=0.0f);
      float calculate_duration();
   };
}



