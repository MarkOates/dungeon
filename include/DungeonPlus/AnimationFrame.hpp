#pragma once


#include <cstdint>


namespace DungeonPlus
{
   class AnimationFrame
   {
   private:
      uint32_t index;
      float duration;

   protected:


   public:
      AnimationFrame(uint32_t index=0, float duration=200);
      ~AnimationFrame();

      uint32_t get_index() const;
      float get_duration() const;
   };
}



